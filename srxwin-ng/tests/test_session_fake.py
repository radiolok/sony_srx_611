import io
import json
from pathlib import Path

import pytest
from conftest import CORPUS

from srx_fake.controller import FakeController
from srx_fake.server import FakeServer
from srx_formats.header import Kind
from srx_link import errors
from srx_link.session import HistoryRecord, Session
from srx_link.transport import LoopbackTransport, ReplayTransport, TcpTransport

OBJ = (CORPUS / "golden/lun/T1.OBJ").read_bytes()
DAT = (CORPUS / "golden/pon/T1.DAT").read_bytes()


def big_obj(n: int = 1000) -> bytes:
    """Synthetic multi-block .OBJ: header + n-14 bytes, size2 = 0."""
    body = bytes(i & 0xFF for i in range(n - 14))
    return bytes([Kind.OBJ, 0]) + n.to_bytes(2, "little") + b"BIG     " + b"\0\0" + body


def session(ctl: FakeController, **kw: object) -> Session:
    return Session(LoopbackTransport(ctl.feed), timeout=1, **kw)  # type: ignore[arg-type]


def test_send_recall_roundtrip_and_directory() -> None:
    ctl = FakeController()
    s = session(ctl, allow_write=True)
    s.send(3, Kind.OBJ, OBJ)
    s.send(3, Kind.DAT, DAT)
    s.send(4, Kind.OBJ, big_obj())
    assert s.recall(3, Kind.OBJ) == OBJ
    assert s.recall(3, Kind.DAT) == DAT
    assert s.recall(4, Kind.OBJ) == big_obj()
    names = [(e.type, e.kind, e.size, e.name) for e in s.scan()]
    assert names == [(3, Kind.OBJ, 114, "T1"), (3, Kind.DAT, 35, "T1"),
                     (4, Kind.OBJ, 1000, "BIG")]


def test_delete_program_follows_fdel_plan() -> None:
    ctl = FakeController(programs={(1, Kind.OBJ): OBJ, (1, Kind.DAT): DAT})
    s = session(ctl, allow_write=True)
    assert s.delete_program(1) == [(1, Kind.OBJ), (1, Kind.DAT)]
    assert s.delete_program(1) == []
    assert ctl.programs == {}


def test_running_program_cannot_be_deleted() -> None:
    ctl = FakeController(programs={(1, Kind.OBJ): OBJ}, running={1})
    with pytest.raises(errors.ProgramRunningError):
        session(ctl, allow_write=True).delete(1, Kind.OBJ)


def test_recall_missing_is_empty_slot() -> None:
    with pytest.raises(errors.EmptySlotError):
        session(FakeController()).recall(7, Kind.OBJ)


def test_history() -> None:
    recs = [HistoryRecord(401, 1, 23, 2026, 9, 27, 10, 11, 12)]
    s = session(FakeController(history=recs))
    assert s.history() == recs
    assert s.history_id() == b"SRX611FK\0"


def test_write_needs_permission_and_ctr_is_blocked() -> None:
    ctl = FakeController()
    with pytest.raises(errors.SafetyError):
        session(ctl).send(1, Kind.OBJ, OBJ)
    with pytest.raises(errors.SafetyError):
        session(ctl, allow_write=True).send(1, Kind.CTR, OBJ)
    with pytest.raises(errors.SafetyError):
        session(ctl).delete(1, Kind.OBJ)
    assert ctl.programs == {}


def test_journal_replays(tmp_path: Path) -> None:
    j = io.StringIO()
    ctl = FakeController(programs={(2, Kind.DAT): DAT})
    session(ctl, journal=j).recall(2, Kind.DAT)
    lines = [json.loads(x) for x in j.getvalue().splitlines()]
    assert {x["dir"] for x in lines} == {"tx", "rx"}
    path = tmp_path / "replay.jsonl"
    path.write_text(j.getvalue())
    assert Session(ReplayTransport(str(path)), timeout=1).recall(2, Kind.DAT) == DAT


def test_tcp_nullmodem_transport() -> None:
    ctl = FakeController(programs={(0, Kind.OBJ): OBJ})
    srv = FakeServer(ctl).start()
    try:
        with Session(TcpTransport("127.0.0.1", srv.port), timeout=2, allow_write=True) as s:
            assert s.recall(0, Kind.OBJ) == OBJ
            data = bytes([Kind.DAT, 0, 20, 0]) + b"FF      " + b"\xff" * 8  # FF stuffing
            s.send(5, Kind.DAT, data)
            assert s.recall(5, Kind.DAT) == data
        assert srv.host_lines == 3  # we raised RTS + DTR
    finally:
        srv.stop()
