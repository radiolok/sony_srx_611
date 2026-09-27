"""Run original SRXWIN DOS tools headless in DOSBox-X (spec §5.1, §5.3 golden runner).

Several tools (LUNNA, POINT) write straight to video memory, so stdout redirection
captures nothing. After each command we run SCRDUMP.COM, which copies the 80x25 text
page at B800:0000 to a file, and decode it as Shift-JIS.
"""

from __future__ import annotations

import os
import shutil
import subprocess
import tempfile
from dataclasses import dataclass
from pathlib import Path

# push ds / mov ax,B800h / mov ds,ax / mov ah,40h / mov bx,1 / mov cx,4000 / xor dx,dx /
# int 21h / pop ds / mov ax,4C00h / int 21h
SCRDUMP_COM = bytes.fromhex("1EB800B88ED8B440BB0100B9A00F31D2CD211FB8004CCD21")

DOSBOX = shutil.which("dosbox-x")


def find_srxwin() -> Path | None:
    """Directory with the original EXEs: $SRXWIN_DIR or <repo>/SRXWIN."""
    env = os.environ.get("SRXWIN_DIR")
    if env:
        return Path(env)
    for p in Path(__file__).resolve().parents:
        if (p / "SRXWIN" / "LUNNA.EXE").is_file():
            return p / "SRXWIN"
    return None


def decode_screen(raw: bytes) -> str:
    """80x25 text page (char, attr pairs) -> text, trailing blanks and lines stripped."""
    chars = bytes(raw[i] for i in range(0, min(len(raw), 4000), 2))
    lines = []
    for r in range(25):
        row = chars[r * 80:(r + 1) * 80]
        lines.append(row.decode("shift_jis", "replace").rstrip())
    return "\n".join(lines).rstrip("\n")


@dataclass
class DosResult:
    screens: list[str]
    timed_out: bool
    workdir: Path


class DosBox:
    """One DOSBox-X invocation = a batch of DOS commands in ``workdir`` mounted as C:."""

    def __init__(self, workdir: Path | None = None, srxwin: Path | None = None) -> None:
        if DOSBOX is None:
            raise RuntimeError("dosbox-x not found in PATH")
        self.workdir = workdir or Path(tempfile.mkdtemp(prefix="srxdos_"))
        self.workdir.mkdir(parents=True, exist_ok=True)
        self.srxwin = srxwin or find_srxwin()
        if self.srxwin is None:
            raise RuntimeError("original SRXWIN EXEs not found (set SRXWIN_DIR)")

    def put(self, name: str, data: bytes) -> Path:
        p = self.workdir / name.upper()
        p.write_bytes(data)
        return p

    def get(self, name: str) -> bytes | None:
        p = self.workdir / name.upper()
        return p.read_bytes() if p.exists() else None

    def run(self, commands: list[str], *, serial_port: int | None = None,
            timeout: float = 60.0) -> DosResult:
        """Run ``commands`` (each followed by a screen dump). ``serial_port`` connects
        COM1 to a nullmodem server on 127.0.0.1 (e.g. srx_fake)."""
        exes = {c.split()[0].upper() for c in commands}
        for exe in exes:
            src = self.srxwin / f"{exe}.EXE"  # type: ignore[operator]
            if src.is_file():
                shutil.copy(src, self.workdir / src.name)
        (self.workdir / "SCRDUMP.COM").write_bytes(SCRDUMP_COM)
        # Answers for "(y/n)" prompts: use ``TOOL args < _YES.TXT``.
        (self.workdir / "_YES.TXT").write_bytes(b"y" * 64)
        bat = ["@echo off"]
        for i, c in enumerate(commands):
            bat += ["cls", c, f"SCRDUMP > _SCR{i}.BIN"]
        (self.workdir / "_RUN.BAT").write_bytes("\r\n".join(bat).encode() + b"\r\n")
        for f in self.workdir.glob("_SCR*.BIN"):
            f.unlink()

        serial = (f"nullmodem server:127.0.0.1 port:{serial_port}" if serial_port
                  else "disabled")
        conf = self.workdir / "_dosbox.conf"
        conf.write_text("[sdl]\noutput=surface\n[dosbox]\nmemsize=16\n[cpu]\ncycles=max\n"
                        f"[serial]\nserial1={serial}\nserial2=disabled\n"
                        "[autoexec]\n")
        env = dict(os.environ, SDL_VIDEODRIVER="dummy", SDL_AUDIODRIVER="dummy")
        assert DOSBOX is not None
        argv = [DOSBOX, "-silent", "-nopromptfolder", "-conf", str(conf),
                "-c", f"mount c \"{self.workdir}\"", "-c", "c:", "-c", "_RUN.BAT",
                "-c", "exit"]
        timed_out = False
        # SIGTERM makes DOSBox-X ask "quit anyway?" while a program runs: always SIGKILL.
        with subprocess.Popen(argv, env=env, stdout=subprocess.DEVNULL,
                              stderr=subprocess.DEVNULL) as proc:
            try:
                proc.wait(timeout)
            except subprocess.TimeoutExpired:
                proc.kill()
                proc.wait()
                timed_out = True
        screens = []
        for i in range(len(commands)):
            raw = self.get(f"_SCR{i}.BIN")
            screens.append(decode_screen(raw) if raw else "")
        return DosResult(screens, timed_out, self.workdir)
