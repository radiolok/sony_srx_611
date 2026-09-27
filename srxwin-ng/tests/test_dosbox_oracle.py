"""Stage-1 gate (spec §6): the original DOS tools work against srx_fake, and srx_link
sends byte-identical requests for the same operations.
"""

from __future__ import annotations

import io
import json
from pathlib import Path

import pytest
from conftest import CORPUS

from srx_dosbox.golden import LANGS, compile_many
from srx_dosbox.runner import DosBox
from srx_fake.controller import FakeController
from srx_fake.server import FakeServer
from srx_formats.header import Kind
from srx_link.frame import FrameReader
from srx_link.session import HistoryRecord, Session
from srx_link.transport import LoopbackTransport

pytestmark = pytest.mark.dosbox

OBJ = (CORPUS / "golden/lun/T1.OBJ").read_bytes()
DAT = (CORPUS / "golden/pon/T1.DAT").read_bytes()
HIST = [HistoryRecord(401, 1, 23, 2026, 9, 27, 10, 11, 12),
        HistoryRecord(0, 0, 0, 1999, 1, 2, 3, 4, 5)]


def host_frames(journal: str) -> list[bytes]:
    """Requests the host sent, from a journal written on the fake side ('rx')."""
    r = FrameReader()
    out: list[bytes] = []
    for line in journal.splitlines():
        e = json.loads(line)
        if e["dir"] == "rx":
            out += r.feed(bytes.fromhex(e["hex"]))
    return out


def our_frames(ctl: FakeController, op: str) -> list[bytes]:
    j = io.StringIO()
    s = Session(LoopbackTransport(ctl.feed), journal=j, timeout=1, allow_write=True)
    if op == "send":
        s.send(1, Kind.OBJ, OBJ, pad=ord("1"))
        s.send(1, Kind.DAT, DAT, pad=ord("1"))
    elif op == "scan":
        s.scan()
    elif op == "recall":
        s.recall(1, Kind.OBJ)
        s.recall(1, Kind.DAT)
    elif op == "hist":
        s.history()
    elif op == "fdel":
        s.delete_program(1)
    return [bytes.fromhex(json.loads(x)["hex"]) for x in j.getvalue().splitlines()
            if json.loads(x)["dir"] == "tx"]


@pytest.fixture(scope="module")
def oracle(tmp_path_factory: pytest.TempPathFactory) -> dict[str, object]:
    ctl = FakeController(history=list(HIST))
    steps = {
        "send": ["SEND -L -T1 -RO -FT1 < _YES.TXT", "SEND -L -T1 -RD -FT1 < _YES.TXT"],
        "scan": ["FILES -L"],
        "recall": ["RECALL -L -T1 -RA -FR1 < _YES.TXT"],
        "hist": ["HIST -L"],
        "fdel": ["FDEL -L -T1 < _YES.TXT", "FILES -L"],
    }
    db = DosBox(tmp_path_factory.mktemp("oracle"))
    db.put("T1.OBJ", OBJ)
    db.put("T1.DAT", DAT)
    frames: dict[str, list[bytes]] = {}
    screens: list[str] = []
    stores: dict[str, dict[tuple[int, int], bytes]] = {}
    # One DOSBox-X launch per step so each step's traffic is journalled separately.
    for name, cmds in steps.items():
        stores[name] = dict(ctl.programs)  # state *before* the step
        j = io.StringIO()
        srv = FakeServer(ctl, journal=j).start()
        try:
            r = db.run(cmds, serial_port=srv.port, timeout=60)
        finally:
            srv.stop()
        assert not r.timed_out, f"{name}: DOSBox-X timed out"
        frames[name] = host_frames(j.getvalue())
        screens += r.screens
    return {"frames": frames, "screens": screens, "stores": stores, "ctl": ctl, "db": db}


def test_original_tools_work_against_fake(oracle: dict[str, object]) -> None:
    sc: list[str] = oracle["screens"]  # type: ignore[assignment]
    send1, send2, files1, recall, hist, fdel, files2 = sc
    assert "Transmission complete." in send1 and "Transmission complete." in send2
    assert "1 program types. total 149 bytes" in files1
    assert " 1 " in files1.splitlines()[-2]  # FILES prints the reply's type byte
    assert "Transmission complete." in recall
    assert "E 401" in hist and "2026" in hist
    assert "is deleted" in fdel
    assert "NONE" in files2 and "program types" not in files2
    db: DosBox = oracle["db"]  # type: ignore[assignment]
    assert db.get("R1.OBJ") == OBJ and db.get("R1.DAT") == DAT
    assert oracle["ctl"].programs == {}  # type: ignore[attr-defined]


@pytest.mark.parametrize("op", ["send", "scan", "recall", "hist", "fdel"])
def test_srx_link_frames_equal_original(oracle: dict[str, object], op: str) -> None:
    frames: dict[str, list[bytes]] = oracle["frames"]  # type: ignore[assignment]
    stores: dict[str, dict[tuple[int, int], bytes]] = oracle["stores"]  # type: ignore[assignment]
    expected = frames[op]
    if op == "fdel":
        expected = [f for f in expected if f[2] == 0x06]  # the trailing FILES is not ours
    ctl = FakeController(programs=dict(stores[op]), history=list(HIST))
    assert our_frames(ctl, op) == expected


def test_golden_is_reproducible(tmp_path: Path) -> None:
    """The oracle is deterministic: re-running the originals reproduces corpus/golden."""
    for key, lang in LANGS.items():
        srcs = sorted((CORPUS / key).glob("*" + lang.src_ext))
        for name, files in compile_many(lang, srcs, work=tmp_path).items():
            for suffix, data in files.items():
                golden = CORPUS / "golden" / key / (name + suffix)
                assert golden.read_bytes() == data, golden
