"""Regenerate corpus/golden with the original SRXWIN tools in DOSBox-X.

Usage: python tools/golden/make_golden.py [lun|pon|plc ...]
"""

import sys
from pathlib import Path

from srx_dosbox.golden import make_golden

root = Path(__file__).resolve().parents[2]
for p in make_golden(root / "corpus", sys.argv[1:] or None):
    print(p.relative_to(root))
