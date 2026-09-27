"""Fake SRX controller: frame handlers + a simple program store (spec §5.2 step 4).

Behaviour follows docs/spec/PROTOCOL.md. Where the real controller is unknown the choice
is marked ``# HYPOTHESIS:`` and must be revisited once hardware sessions are recorded.
"""

from __future__ import annotations

import logging
import struct
from dataclasses import dataclass, field
from pathlib import Path

from srx_formats.header import Kind, parse_header
from srx_link import frame
from srx_link.session import BLOCK, HistoryRecord

log = logging.getLogger(__name__)

OK, S_SUM, S_CMD, S_SIZE, S_EXEC, S_BLOCK = 0, 1, 3, 4, 6, 7
S_EMPTY, S_RUNNING, S_MEMFULL, S_NOHIST = 10, 11, 12, 15
MEMORY_LIMIT = 0x10000  # spec §2: OBJ/DAT <= 64 KB


@dataclass
class _Upload:
    type: int
    kind: int
    total: int
    name: bytes
    data: bytearray = field(default_factory=bytearray)
    next_block: int = 1


@dataclass
class FakeController:
    programs: dict[tuple[int, int], bytes] = field(default_factory=dict)
    history: list[HistoryRecord] = field(default_factory=list)
    controller_id: bytes = b"SRX611FK\0"
    running: set[int] = field(default_factory=set)  # types whose program "executes"
    state_dir: Path | None = None
    _upload: _Upload | None = None
    _reader: frame.FrameReader = field(default_factory=frame.FrameReader)

    # -- store --------------------------------------------------------------------------

    @staticmethod
    def key(type_: int, kind: int) -> tuple[int, int]:
        # HYPOTHESIS: the system program has one slot; FILES asks (0,5F), SEND uses (100,5F).
        return (100, kind) if kind == Kind.SYS else (type_, kind)

    def put(self, type_: int, kind: int, data: bytes) -> None:
        self.programs[self.key(type_, kind)] = bytes(data)
        self._save()

    def load_dir(self, path: Path) -> None:
        for f in sorted(path.glob("*_*.bin")):
            t, k = f.stem.split("_")
            self.programs[(int(t), int(k, 16))] = f.read_bytes()

    def _save(self) -> None:
        if not self.state_dir:
            return
        self.state_dir.mkdir(parents=True, exist_ok=True)
        for f in self.state_dir.glob("*_*.bin"):
            f.unlink()
        for (t, k), data in self.programs.items():
            (self.state_dir / f"{t:03d}_{k:02X}.bin").write_bytes(data)

    # -- wire ---------------------------------------------------------------------------

    def feed(self, data: bytes) -> bytes:
        """Consume host bytes, return the controller's reply bytes."""
        out = b""
        for raw in self._reader.feed(data):
            out += self.handle(raw)
        return out

    def handle(self, raw: bytes) -> bytes:
        cmd = raw[2] if len(raw) > 2 else 0
        if frame.checksum(raw[:-1]) != raw[-1]:
            return frame.build_reply(cmd, S_SUM)
        req = frame.Frame(raw)
        fn = getattr(self, f"cmd_{cmd:02x}", None)
        if fn is None:
            log.info("unknown command %02X", cmd)
            return frame.build_reply(cmd, S_CMD)
        status, payload = fn(req.args)
        return frame.build_reply(cmd, status, payload)

    # -- handlers: return (status, payload) ---------------------------------------------

    def cmd_05(self, a: bytes) -> tuple[int, bytes]:
        if len(a) != 2:
            return S_SIZE, b""
        data = self.programs.get(self.key(a[0], a[1]))
        if data is None:
            return S_EMPTY, b""
        h = parse_header(data)
        # FILES.EXE prints byte +4 as "TYPE NO." [E]; size = transferred length [E].
        return OK, struct.pack("<BI", a[0], h.total) + h.name.encode("ascii") + b"\0"

    def cmd_06(self, a: bytes) -> tuple[int, bytes]:
        if len(a) != 2:
            return S_SIZE, b""
        if self._upload:
            return S_EXEC, b""
        k = self.key(a[0], a[1])
        if k not in self.programs:
            return S_EMPTY, b""
        if a[0] in self.running:
            return S_RUNNING, b""
        del self.programs[k]
        self._save()
        return OK, b""

    def cmd_01(self, a: bytes) -> tuple[int, bytes]:
        if len(a) != 15:
            return S_SIZE, b""
        type_, kind, total = struct.unpack_from("<BBI", a)
        if type_ in self.running:
            return S_RUNNING, b""
        if total > MEMORY_LIMIT:
            return S_MEMFULL, b""
        self._upload = _Upload(type_, kind, total, a[6:14])
        return OK, b""

    def cmd_02(self, a: bytes) -> tuple[int, bytes]:
        up = self._upload
        if len(a) < 5 or up is None:
            return S_BLOCK, b""
        type_, kind, block, last = struct.unpack_from("<BBHB", a)
        if (type_, kind, block) != (up.type, up.kind, up.next_block):
            self._upload = None
            return S_BLOCK, b""
        up.data += a[5:]
        up.next_block += 1
        if last:
            self._upload = None
            if len(up.data) != up.total:
                return S_SIZE, b""
            self.put(up.type, up.kind, bytes(up.data))
        return OK, b""

    def cmd_04(self, a: bytes) -> tuple[int, bytes]:
        if len(a) != 4:
            return S_SIZE, b""
        type_, kind, block = struct.unpack("<BBH", a)
        data = self.programs.get(self.key(type_, kind))
        if data is None:
            return S_EMPTY, b""
        n = max(1, (len(data) + BLOCK - 1) // BLOCK)
        if not 1 <= block <= n:
            return S_BLOCK, b""
        chunk = data[(block - 1) * BLOCK: block * BLOCK]
        return OK, bytes([block == n]) + chunk

    def cmd_15(self, a: bytes) -> tuple[int, bytes]:
        return OK, self.controller_id

    def cmd_14(self, a: bytes) -> tuple[int, bytes]:
        if len(a) != 1:
            return S_SIZE, b""
        if a[0] >= len(self.history):
            return S_NOHIST, b""
        return OK, self.history[a[0]].pack()
