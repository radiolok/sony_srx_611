"""TCP server for FakeController, speaking the DOSBox-X nullmodem format (PROTOCOL.md §8)."""

from __future__ import annotations

import json
import logging
import socket
import threading
import time
from typing import IO

from srx_link.transport import NullModemCodec

from .controller import FakeController

log = logging.getLogger(__name__)


class FakeServer:
    """Serves one connection at a time, forever (DOSBox-X reconnects per launch)."""

    def __init__(self, ctl: FakeController, host: str = "127.0.0.1", port: int = 0,
                 journal: IO[str] | None = None) -> None:
        self.ctl = ctl
        self.journal = journal
        self._srv = socket.socket()
        self._srv.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        self._srv.bind((host, port))
        self._srv.listen(1)
        self.port: int = self._srv.getsockname()[1]
        self._stop = threading.Event()
        self._thread: threading.Thread | None = None
        self._t0 = time.monotonic()
        self.host_lines = 0  # last control byte from the host (bit0 RTS, bit1 DTR)

    def _log(self, direction: str, data: bytes) -> None:
        if self.journal and data:
            self.journal.write(json.dumps({"t": round(time.monotonic() - self._t0, 4),
                                           "dir": direction, "hex": data.hex()}) + "\n")
            self.journal.flush()

    def serve_forever(self) -> None:
        self._srv.settimeout(0.2)
        while not self._stop.is_set():
            try:
                conn, addr = self._srv.accept()
            except TimeoutError:
                continue
            log.info("connection from %s", addr)
            with conn:
                self._serve(conn)

    def _serve(self, conn: socket.socket) -> None:
        codec = NullModemCodec()
        conn.setsockopt(socket.IPPROTO_TCP, socket.TCP_NODELAY, 1)
        conn.sendall(NullModemCodec.control(rts=True, dtr=True))  # host sees CTS+DSR
        conn.settimeout(0.2)
        while not self._stop.is_set():
            try:
                d = conn.recv(4096)
            except TimeoutError:
                continue
            except OSError:
                return
            if not d:
                return
            data = codec.decode(d)
            self.host_lines = codec.peer_lines
            self._log("rx", data)  # from the controller's point of view: host -> us
            out = self.ctl.feed(data)
            if out:
                self._log("tx", out)
                conn.sendall(NullModemCodec.encode(out))

    def start(self) -> FakeServer:
        self._thread = threading.Thread(target=self.serve_forever, daemon=True)
        self._thread.start()
        return self

    def stop(self) -> None:
        self._stop.set()
        if self._thread:
            self._thread.join(2)
        self._srv.close()
