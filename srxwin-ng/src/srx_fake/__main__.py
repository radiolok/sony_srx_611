"""``srx-fake``: run the fake controller on a TCP port.

Example: ``srx-fake --port 5000 --state ./fakestate`` then point DOSBox-X at it with
``serial1=nullmodem server:127.0.0.1 port:5000`` or use ``srx --tcp 127.0.0.1:5000``.
"""

from __future__ import annotations

import argparse
import logging
from pathlib import Path

from .controller import FakeController
from .server import FakeServer


def main() -> None:
    ap = argparse.ArgumentParser(prog="srx-fake", description=__doc__)
    ap.add_argument("--host", default="127.0.0.1")
    ap.add_argument("--port", type=int, default=5000)
    ap.add_argument("--state", type=Path, help="directory that persists the program store")
    ap.add_argument("--journal", type=Path, help="append the byte journal (JSON Lines)")
    ap.add_argument("-v", "--verbose", action="store_true")
    a = ap.parse_args()
    logging.basicConfig(level=logging.INFO if a.verbose else logging.WARNING)
    ctl = FakeController(state_dir=a.state)
    if a.state and a.state.exists():
        ctl.load_dir(a.state)
    journal = open(a.journal, "a", encoding="utf-8") if a.journal else None
    srv = FakeServer(ctl, a.host, a.port, journal)
    print(f"srx-fake listening on {a.host}:{srv.port} ({len(ctl.programs)} programs)")
    try:
        srv.serve_forever()
    except KeyboardInterrupt:
        pass


if __name__ == "__main__":
    main()
