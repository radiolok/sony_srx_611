"""Session: the only way to talk to a controller (PROTOCOL.md §6-7, LNK-03..07)."""

from __future__ import annotations

import json
import logging
import struct
import time
from dataclasses import dataclass
from enum import Enum
from typing import IO

from srx_formats.header import Kind, parse_header

from . import frame
from .errors import EmptySlotError, NoHistoryError, SafetyError, raise_for_status
from .transport import Transport

log = logging.getLogger(__name__)

BLOCK = 128
BYTE_TIMEOUT = 5.0  # host tools: 0x5B BIOS ticks per byte


class Danger(Enum):
    READ = "read"
    WRITE = "write"
    MOTION = "motion"


PROTECTED_KINDS = {Kind.CTR}  # spec §8.1: .CTR (and .KEE) writes are blocked


@dataclass(frozen=True)
class DirEntry:
    type: int
    kind: int
    attr: int
    size: int
    name: str


@dataclass(frozen=True)
class HistoryRecord:
    code: int
    task: int
    line: int
    year: int
    month: int
    day: int
    hour: int
    minute: int
    second: int

    @classmethod
    def unpack(cls, p: bytes) -> HistoryRecord:
        p = p.ljust(12, b"\0")
        code, task, line, year, month, day, hh, mm, ss = struct.unpack_from("<HBHHBBBBB", p)
        return cls(code, task, line, year, month, day, hh, mm, ss)

    def pack(self) -> bytes:
        return struct.pack("<HBHHBBBBB", self.code, self.task, self.line, self.year,
                           self.month, self.day, self.hour, self.minute, self.second)


def effective_kind(type_: int, kind: int) -> int:
    """SEND/RECALL force kind 5F for the system program (type 100)."""
    return Kind.SYS if type_ == 100 else kind


def files_scan_order(max_type: int = 15) -> list[tuple[int, int]]:
    """(type, kind) pairs in the order FILES.EXE queries them (PROTOCOL.md §6)."""
    order: list[tuple[int, int]] = [(0, int(Kind.SYS))] + [(t, int(Kind.COD)) for t in range(4)]
    for t in range(max_type + 1):
        order += [(t, int(Kind.OBJ)), (t, int(Kind.DAT))]
    return order


def fdel_plan(type_: int) -> list[tuple[int, int]]:
    """(type, kind) pairs FDEL.EXE ``-T<type>`` deletes, in order (PROTOCOL.md §6)."""
    if 90 <= type_ <= 99:
        return [(type_, Kind.COD)]
    if type_ == 100:
        return [(100, Kind.SYS), (100, Kind.DAT)]
    return [(type_, Kind.OBJ), (type_, Kind.DAT)]


class Session:
    def __init__(self, transport: Transport, *, journal: IO[str] | None = None,
                 allow_write: bool = False, allow_motion: bool = False,
                 timeout: float = BYTE_TIMEOUT) -> None:
        self.t = transport
        self.journal = journal
        self.allow_write = allow_write
        self.allow_motion = allow_motion
        self.timeout = timeout
        self._t0 = time.monotonic()

    # -- plumbing ---------------------------------------------------------------------

    def close(self) -> None:
        self.t.close()

    def __enter__(self) -> Session:
        return self

    def __exit__(self, *exc: object) -> None:
        self.close()

    def _log(self, direction: str, data: bytes) -> None:
        if self.journal:
            self.journal.write(json.dumps({"t": round(time.monotonic() - self._t0, 4),
                                           "dir": direction, "hex": data.hex()}) + "\n")
            self.journal.flush()

    def _guard(self, danger: Danger, kind: int | None = None) -> None:
        if danger is Danger.WRITE:
            if not self.allow_write:
                raise SafetyError("WRITE operation refused: session opened read-only")
            if kind in PROTECTED_KINDS:
                raise SafetyError(f"WRITE of kind {kind:02X} is blocked by policy (spec §8.1)")
        if danger is Danger.MOTION and not self.allow_motion:
            raise SafetyError("MOTION operation refused (needs --i-am-at-the-estop)")

    def transact(self, cmd: int, args: bytes = b"", *, danger: Danger,
                 kind: int | None = None) -> frame.Frame:
        """Send one request, return the validated reply (status not yet checked)."""
        self._guard(danger, kind)
        req = frame.build(cmd, args)
        self._log("tx", req)
        self.t.write(req)
        head = self.t.read(2, self.timeout)
        if head[0] != frame.ESC or head[1] < frame.MIN_REPLY_LEN:
            self._log("rx", head)
            raise frame.FrameError(f"bad reply head {head.hex(' ')}")
        rest = self.t.read(head[1] - 2, self.timeout)
        self._log("rx", head + rest)
        rep = frame.parse(head + rest)
        if rep.cmd != cmd:
            log.warning("reply echoes cmd %02X, expected %02X", rep.cmd, cmd)
        return rep

    def call(self, cmd: int, args: bytes = b"", *, danger: Danger,
             kind: int | None = None) -> bytes:
        rep = self.transact(cmd, args, danger=danger, kind=kind)
        raise_for_status(rep.status, cmd)
        return rep.payload

    # -- DOS-tool command set -----------------------------------------------------------

    def directory(self, type_: int, kind: int) -> DirEntry | None:
        """Command 05. None = empty slot (status 10)."""
        try:
            p = self.call(0x05, bytes([type_, kind]), danger=Danger.READ)
        except EmptySlotError:
            return None
        attr = p[0] if p else 0
        size = struct.unpack_from("<I", p, 1)[0] if len(p) >= 5 else 0
        name = p[5:].split(b"\0", 1)[0].decode("ascii", "replace").rstrip()
        return DirEntry(type_, kind, attr, size, name)

    def scan(self, max_type: int = 15) -> list[DirEntry]:
        return [e for t, k in files_scan_order(max_type)
                if (e := self.directory(t, k)) is not None]

    def recall_block(self, type_: int, kind: int, block: int) -> tuple[bool, bytes]:
        p = self.call(0x04, struct.pack("<BBH", type_, kind, block), danger=Danger.READ)
        return bool(p[0]), p[1:]

    def recall(self, type_: int, kind: int) -> bytes:
        """Command 04: read a whole file."""
        kind = effective_kind(type_, kind)
        # QUIRK: RECALL.EXE fetches block 1 once just for the header, then again in the loop.
        _, first = self.recall_block(type_, kind, 1)
        total = parse_header(first).total
        data = bytearray()
        block = 1
        while len(data) < total:
            last, chunk = self.recall_block(type_, kind, block)
            data += chunk
            block += 1
            if last:
                break
        if len(data) < total or not last:
            raise frame.FrameError(f"recall incomplete: {len(data)}/{total}, last={last}")
        return bytes(data[:total])

    def send(self, type_: int, kind: int, data: bytes, *, pad: int = 0) -> None:
        """Commands 01 + 02: write a whole file (WRITE).

        ``pad`` is start-frame byte 17. QUIRK: SEND.EXE leaves it uninitialised; in
        practice it holds the 2nd character of the ``-F`` file-name argument.
        """
        kind = effective_kind(type_, kind)
        self._guard(Danger.WRITE, kind)
        h = parse_header(data)
        image = data[: h.total]
        name = data[4:12]
        self.call(0x01, struct.pack("<BBI", type_, kind, h.total) + name + bytes([pad]),
                  danger=Danger.WRITE, kind=kind)
        block = 1
        for off in range(0, len(image), BLOCK):
            chunk = image[off:off + BLOCK]
            last = off + BLOCK >= len(image)
            self.call(0x02, struct.pack("<BBHB", type_, kind, block, last) + chunk,
                      danger=Danger.WRITE, kind=kind)
            block += 1

    def delete(self, type_: int, kind: int) -> bool:
        """Command 06 (WRITE). Returns False if the slot was already empty."""
        try:
            self.call(0x06, bytes([type_, kind]), danger=Danger.WRITE, kind=kind)
        except EmptySlotError:
            return False
        return True

    def delete_program(self, type_: int) -> list[tuple[int, int]]:
        """Delete everything FDEL.EXE ``-T<type>`` deletes; returns the slots removed."""
        return [(t, k) for t, k in fdel_plan(type_) if self.delete(t, k)]

    def history_id(self) -> bytes:
        """Command 15: 9-byte controller ID used as the .HST base name."""
        return self.call(0x15, danger=Danger.READ)

    def history_record(self, idx: int) -> HistoryRecord | None:
        try:
            return HistoryRecord.unpack(self.call(0x14, bytes([idx]), danger=Danger.READ))
        except NoHistoryError:
            return None

    def history(self) -> list[HistoryRecord]:
        out = []
        for i in range(20):
            r = self.history_record(i)
            if r is None:
                break
            out.append(r)
        return out
