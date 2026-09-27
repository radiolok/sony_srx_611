"""Golden runner (spec §5.3): original compilers/decompilers as the oracle.

For every source ``corpus/<lang>/NAME.<EXT>`` it produces, in ``corpus/golden/<lang>/``:

- ``NAME.<BIN>``      the compiler output (.OBJ / .DAT / .COD), if any
- ``NAME.ERR``        the compiler error file, if any
- ``NAME.SCR``        the compiler screen (UTF-8)
- ``NAME.DEC.<EXT>``  the decompiler output for NAME.<BIN> (ANNUL / DISPON / DPLC)

Goldens are regenerated only by this script, never edited by hand (spec §7.1 rule 5).
"""

from __future__ import annotations

import shutil
import tempfile
from dataclasses import dataclass
from pathlib import Path

from .runner import DosBox


@dataclass(frozen=True)
class Lang:
    name: str
    src_ext: str
    bin_ext: str
    compile: str  # "{n}" = base name
    decompile: str


LANGS = {
    "lun": Lang("lun", ".LUN", ".OBJ", "LUNNA {n} -E", "ANNUL {n} < _YES.TXT"),
    "pon": Lang("pon", ".PON", ".DAT", "POINT {n}", "DISPON {n} < _YES.TXT"),
    "plc": Lang("plc", ".PLC", ".COD", "PLC {n}", "DPLC {n} < _YES.TXT"),
}


def dos_name(p: Path) -> str:
    n = p.stem.upper()
    if len(n) > 8 or not n.replace("_", "").isalnum():
        raise ValueError(f"{p.name}: corpus names must be DOS 8.3")
    return n


def compile_many(lang: Lang, sources: list[Path], work: Path | None = None
                 ) -> dict[str, dict[str, bytes]]:
    """Compile then decompile ``sources`` with the originals. Returns name -> {suffix: data}."""
    tmp = Path(tempfile.mkdtemp(prefix="srxgold_", dir=work))
    try:
        cdir, ddir = tmp / "c", tmp / "d"
        db = DosBox(cdir)
        names = []
        for s in sources:
            n = dos_name(s)
            names.append(n)
            db.put(n + lang.src_ext, s.read_bytes())
        res = db.run([lang.compile.format(n=n) for n in names], timeout=30 + 5 * len(names))
        if res.timed_out:
            raise RuntimeError(f"DOSBox-X timed out compiling {lang.name}")
        out: dict[str, dict[str, bytes]] = {}
        bins: dict[str, bytes] = {}
        for n, screen in zip(names, res.screens, strict=True):
            o: dict[str, bytes] = {".SCR": (screen + "\n").encode("utf-8")}
            for ext in (lang.bin_ext, ".ERR"):
                d = db.get(n + ext)
                if d is not None:
                    o[ext] = d
            if lang.bin_ext in o:
                bins[n] = o[lang.bin_ext]
            out[n] = o
        for n, text in decompile_many(lang, bins, ddir).items():
            out[n][".DEC" + lang.src_ext] = text
        return out
    finally:
        shutil.rmtree(tmp, ignore_errors=True)


def decompile_many(lang: Lang, bins: dict[str, bytes], work: Path | None = None
                   ) -> dict[str, bytes]:
    """Decompile {NAME: binary} with the original decompiler. Returns {NAME: source}."""
    if not bins:
        return {}
    tmp = None if work else Path(tempfile.mkdtemp(prefix="srxdec_"))
    try:
        db = DosBox(work or tmp)
        for n, data in bins.items():
            db.put(n + lang.bin_ext, data)
        res = db.run([lang.decompile.format(n=n) for n in bins], timeout=30 + 5 * len(bins))
        if res.timed_out:
            raise RuntimeError(f"DOSBox-X timed out decompiling {lang.name}")
        return {n: d for n in bins if (d := db.get(n + lang.src_ext)) is not None}
    finally:
        if tmp:
            shutil.rmtree(tmp, ignore_errors=True)


def make_golden(corpus: Path, langs: list[str] | None = None) -> list[Path]:
    """Regenerate ``corpus/golden``. Returns the files written."""
    written = []
    for key in langs or list(LANGS):
        lang = LANGS[key]
        srcs = sorted(p for p in (corpus / key).glob("*") if p.suffix.upper() == lang.src_ext)
        if not srcs:
            continue
        gdir = corpus / "golden" / key
        if gdir.exists():
            shutil.rmtree(gdir)
        gdir.mkdir(parents=True)
        for n, files in compile_many(lang, srcs).items():
            for suffix, data in files.items():
                p = gdir / (n + suffix)
                p.write_bytes(data)
                written.append(p)
    return written
