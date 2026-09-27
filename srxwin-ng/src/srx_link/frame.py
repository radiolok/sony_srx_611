"""Frame layer: ``1B LEN CMD ... SUM`` (docs/spec/PROTOCOL.md §2)."""

from __future__ import annotations

from dataclasses import dataclass

ESC = 0x1B
MIN_REPLY_LEN = 5
MAX_FRAME_LEN = 0xFF


class FrameError(Exception):
    """Malformed frame received (host-side: DOS 1023/1024/1025)."""


def checksum(data: bytes) -> int:
    return sum(data) & 0xFF


def build(cmd: int, args: bytes = b"") -> bytes:
    """Build a request frame ``1B LEN CMD args SUM``."""
    n = len(args) + 4
    if n > MAX_FRAME_LEN:
        raise ValueError(f"frame too long: {n}")
    body = bytes([ESC, n, cmd]) + args
    return body + bytes([checksum(body)])


def build_reply(cmd: int, status: int, payload: bytes = b"") -> bytes:
    """Build a reply frame ``1B LEN CMD STATUS payload SUM`` (controller side)."""
    return build(cmd, bytes([status]) + payload)


@dataclass(frozen=True)
class Frame:
    raw: bytes

    @property
    def length(self) -> int:
        return self.raw[1]

    @property
    def cmd(self) -> int:
        return self.raw[2]

    @property
    def args(self) -> bytes:
        """Bytes between CMD and SUM (for a reply: STATUS + payload)."""
        return self.raw[3:-1]

    @property
    def status(self) -> int:
        return self.raw[3]

    @property
    def payload(self) -> bytes:
        return self.raw[4:-1]


def parse(raw: bytes) -> Frame:
    """Validate a complete frame; raise FrameError if it is malformed."""
    if len(raw) < 4 or raw[0] != ESC:
        raise FrameError("ESC code error")
    if raw[1] != len(raw):
        raise FrameError(f"LEN {raw[1]} != {len(raw)}")
    if checksum(raw[:-1]) != raw[-1]:
        raise FrameError("check sum error")
    return Frame(raw)


class FrameReader:
    """Incremental byte-stream deframer (used by the fake controller)."""

    def __init__(self) -> None:
        self._buf = bytearray()

    def feed(self, data: bytes) -> list[bytes]:
        """Return complete raw frames; junk before an ESC is dropped."""
        out: list[bytes] = []
        self._buf += data
        while self._buf:
            if self._buf[0] != ESC:
                del self._buf[0]
                continue
            if len(self._buf) < 2:
                break
            n = self._buf[1]
            if n < 4:
                del self._buf[0]
                continue
            if len(self._buf) < n:
                break
            out.append(bytes(self._buf[:n]))
            del self._buf[:n]
        return out
