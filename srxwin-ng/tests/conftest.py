from __future__ import annotations

import shutil
from pathlib import Path

import pytest

from srx_dosbox.runner import find_srxwin

ROOT = Path(__file__).resolve().parents[1]
CORPUS = ROOT / "corpus"


def pytest_collection_modifyitems(config: pytest.Config, items: list[pytest.Item]) -> None:
    if shutil.which("dosbox-x") and find_srxwin():
        return
    skip = pytest.mark.skip(reason="dosbox-x or original SRXWIN EXEs not available")
    for item in items:
        if "dosbox" in item.keywords:
            item.add_marker(skip)
