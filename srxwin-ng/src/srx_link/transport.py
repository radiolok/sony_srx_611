"""Byte transports (requirement LNK-01): serial port, TCP, replay, in-process."""

from __future__ import annotations

import json
import socket
import time
from collections.abc import Callable
from typing import Any, Protocol

from .errors import LinkError, LinkTimeout


class Transport(Protocol):
    def write(self, data: bytes) -> None: ...
    def read(self, n: int, timeout: float) -> bytes:
        """Return exactly ``n`` bytes or raise LinkTimeout."""
        ...
    def close(self) -> None: ...


class NullModemCodec:
    """DOSBox-X nullmodem (non-transparent) byte stuffing, PROTOCOL.md §8.

    ``FF FF`` is a literal FF; ``FF x`` carries control lines of the sender:
    bit0 RTS, bit1 DTR, bit2 break. The receiver sees them as CTS/DSR.
    """

    def __init__(self) -> None:
        self._esc = False
        self.peer_lines = 0

    @staticmethod
    def encode(data: bytes) -> bytes:
        return data.replace(b"\xff", b"\xff\xff")

    @staticmethod
    def control(rts: bool = True, dtr: bool = True) -> bytes:
        return bytes([0xFF, (1 if rts else 0) | (2 if dtr else 0)])

    def decode(self, data: bytes) -> bytes:
        out = bytearray()
        for b in data:
            if self._esc:
                self._esc = False
                if b == 0xFF:
                    out.append(b)
                else:
                    self.peer_lines = b
            elif b == 0xFF:
                self._esc = True
            else:
                out.append(b)
        return bytes(out)


class _Buffered:
    """Common read-exactly logic on top of a ``_recv(timeout) -> bytes`` primitive."""

    def __init__(self) -> None:
        self._rx = bytearray()

    def _recv(self, timeout: float) -> bytes:
        raise NotImplementedError

    def read(self, n: int, timeout: float) -> bytes:
        deadline = time.monotonic() + timeout
        while len(self._rx) < n:
            left = deadline - time.monotonic()
            if left <= 0:
                raise LinkTimeout(f"receive timeout ({len(self._rx)}/{n} bytes)")
            self._rx += self._recv(left)
        out = bytes(self._rx[:n])
        del self._rx[:n]
        return out


class TcpTransport(_Buffered):
    """TCP link to ``srx_fake`` (or anything speaking the nullmodem format)."""

    def __init__(self, host: str, port: int, nullmodem: bool = True,
                 connect_timeout: float = 5.0) -> None:
        super().__init__()
        self._sock = socket.create_connection((host, port), timeout=connect_timeout)
        self._sock.setsockopt(socket.IPPROTO_TCP, socket.TCP_NODELAY, 1)
        self._codec = NullModemCodec() if nullmodem else None
        if self._codec:
            self._sock.sendall(NullModemCodec.control(rts=True, dtr=True))

    def write(self, data: bytes) -> None:
        self._sock.sendall(self._codec.encode(data) if self._codec else data)

    def _recv(self, timeout: float) -> bytes:
        self._sock.settimeout(timeout)
        try:
            d = self._sock.recv(4096)
        except TimeoutError:
            return b""
        if not d:
            raise LinkError("connection closed by peer")
        return self._codec.decode(d) if self._codec else d

    def close(self) -> None:
        self._sock.close()


class SerialTransport(_Buffered):
    """Physical COM port / USB-UART (LNK-02): 9600 8N2, DTR+RTS on, DSR checked."""

    def __init__(self, port: str, baudrate: int = 9600, stopbits: int = 2,
                 check_dsr: bool = True) -> None:
        super().__init__()
        import serial  # imported lazily: tests and the fake controller do not need it

        self._ser: Any = serial.Serial(port, baudrate=baudrate, bytesize=8, parity="N",
                                       stopbits=stopbits, timeout=0.05)
        self._ser.dtr = True
        self._ser.rts = True
        self._check_dsr = check_dsr

    def write(self, data: bytes) -> None:
        if self._check_dsr:
            deadline = time.monotonic() + 5.0
            while not self._ser.dsr:
                if time.monotonic() > deadline:
                    raise LinkError("DSR is low: check the cable (DOS 1020)")
                time.sleep(0.01)
        self._ser.write(data)
        self._ser.flush()

    def _recv(self, timeout: float) -> bytes:
        self._ser.timeout = min(timeout, 0.2)
        return bytes(self._ser.read(max(1, self._ser.in_waiting)))

    def close(self) -> None:
        self._ser.close()


class LoopbackTransport(_Buffered):
    """In-process link: every write is handed to ``handler`` and its output is queued."""

    def __init__(self, handler: Callable[[bytes], bytes]) -> None:
        super().__init__()
        self._handler = handler
        self._pending = b""

    def write(self, data: bytes) -> None:
        self._pending += self._handler(data)

    def _recv(self, timeout: float) -> bytes:
        d, self._pending = self._pending, b""
        if not d:
            raise LinkTimeout("loopback: no reply")
        return d

    def close(self) -> None:
        pass


class ReplayTransport(_Buffered):
    """Replay a Session journal (JSON Lines, LNK-07). Writes must match the recording."""

    def __init__(self, path: str) -> None:
        super().__init__()
        with open(path, encoding="utf-8") as f:
            self._events = [json.loads(line) for line in f if line.strip()]
        self._i = 0

    def _next(self, direction: str) -> bytes:
        if self._i >= len(self._events) or self._events[self._i]["dir"] != direction:
            raise LinkError(f"replay: expected {direction} at event {self._i}")
        e = self._events[self._i]
        self._i += 1
        return bytes.fromhex(e["hex"])

    def write(self, data: bytes) -> None:
        want = self._next("tx")
        if want != data:
            raise LinkError(f"replay mismatch: sent {data.hex(' ')}, recorded {want.hex(' ')}")

    def _recv(self, timeout: float) -> bytes:
        return self._next("rx")

    def close(self) -> None:
        pass
