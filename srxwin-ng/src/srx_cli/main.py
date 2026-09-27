"""``srx``: console replacement for SEND / RECALL / FILES / FDEL / HIST (CLI-01..12).

Link selection: ``--port /dev/ttyUSB0`` (real controller) or ``--tcp 127.0.0.1:5000``
(srx-fake). Exit codes (CLI-12): 0 ok, 1 controller error, 2 link error, 3 compile error.
"""

from __future__ import annotations

import datetime as dt
import json
import sys
from collections.abc import Iterator
from contextlib import contextmanager
from pathlib import Path
from typing import Annotated, Any

import typer

from srx_formats.header import EXT_TO_KIND, Kind, parse_header
from srx_link import ControllerError, LinkError, SafetyError, Session
from srx_link.frame import FrameError
from srx_link.session import files_scan_order
from srx_link.transport import SerialTransport, TcpTransport, Transport

app = typer.Typer(add_completion=False, no_args_is_help=True, help=__doc__)

KIND_BY_LETTER = {"O": Kind.OBJ, "D": Kind.DAT, "C": Kind.CDT, "P": Kind.COD}
_opts: dict[str, Any] = {}


@app.callback()
def _main(
    port: Annotated[str | None, typer.Option(help="Serial port (COM3, /dev/ttyUSB0)")] = None,
    tcp: Annotated[str | None, typer.Option(help="HOST:PORT of srx-fake")] = None,
    journal: Annotated[Path | None, typer.Option(help="Append byte journal (JSONL)")] = None,
    as_json: Annotated[bool, typer.Option("--json", help="Machine-readable output")] = False,
) -> None:
    _opts.update(port=port, tcp=tcp, journal=journal, json=as_json)


def _out(obj: Any, text: str) -> None:
    typer.echo(json.dumps(obj) if _opts["json"] else text)


def _fail(code: int, msg: str) -> None:
    typer.echo(f"error: {msg}", err=True)
    raise typer.Exit(code)


@contextmanager
def _session(write: bool = False) -> Iterator[Session]:
    t: Transport
    try:
        if _opts["tcp"]:
            host, p = _opts["tcp"].rsplit(":", 1)
            t = TcpTransport(host, int(p))
        elif _opts["port"]:
            t = SerialTransport(_opts["port"])
        else:
            _fail(2, "give --port or --tcp")
    except OSError as e:
        _fail(2, f"cannot open link: {e}")
    jf = open(_opts["journal"], "a", encoding="utf-8") if _opts["journal"] else None
    try:
        with Session(t, journal=jf, allow_write=write) as s:
            yield s
    except ControllerError as e:
        _fail(1, str(e))
    except SafetyError as e:
        _fail(1, f"refused: {e}")
    except (LinkError, FrameError, OSError) as e:
        _fail(2, f"link: {e}")
    finally:
        if jf:
            jf.close()


def _kinds(r: str) -> list[int]:
    r = r.upper()
    return [Kind.OBJ, Kind.DAT] if r == "A" else [KIND_BY_LETTER[r]]


@app.command()
def files() -> None:
    """List programs in the controller (FILES)."""
    with _session() as s:
        entries = s.scan()
    rows = [{"type": e.type, "kind": f"{e.kind:02X}", "ext": Kind(e.kind).ext,
             "name": e.name, "size": e.size} for e in entries]
    text = "\n".join(f"{r['type']:4d}  {r['ext']:5s} {r['name']:8s} {r['size']:7d}" for r in rows)
    _out(rows, text or "(no programs)")


@app.command()
def recall(type_: Annotated[int, typer.Argument(metavar="TYPE")],
           kind: Annotated[str, typer.Option("-r", help="O,D,C,P or A=O+D")] = "A",
           out: Annotated[Path, typer.Option("-o", help="Output directory")] = Path("."),
           ) -> None:
    """Read program TYPE from the controller (RECALL)."""
    written = []
    with _session() as s:
        for k in _kinds(kind):
            data = s.recall(type_, k)
            p = out / f"{parse_header(data).name or f'T{type_}'}{Kind(k).ext}"
            p.write_bytes(data)
            written.append(str(p))
    _out(written, "\n".join(written))


@app.command()
def hist(out: Annotated[Path | None, typer.Option("-o", help="Save as text")] = None) -> None:
    """Read the error history (HIST)."""
    with _session() as s:
        recs = s.history()
    lines = [f"E{r.code:03d} task {r.task:2d} line {r.line:5d}  "
             f"{r.year:04d}-{r.month:02d}-{r.day:02d} {r.hour:02d}:{r.minute:02d}:{r.second:02d}"
             for r in recs]
    if out:
        out.write_text("\n".join(lines) + "\n")
    _out([r.__dict__ for r in recs], "\n".join(lines) or "(no history)")


@app.command()
def backup(dest: Annotated[Path, typer.Argument()],
           max_type: Annotated[int, typer.Option(help="Highest LUNA type to scan")] = 15) -> None:
    """Read every program found by the FILES scan into DEST (CLI-04)."""
    dest.mkdir(parents=True, exist_ok=True)
    manifest = []
    with _session() as s:
        for t, k in files_scan_order(max_type):
            e = s.directory(t, k)
            if e is None:
                continue
            data = s.recall(t, k)
            p = dest / f"{t:03d}_{Kind(k).name}{Kind(k).ext}"
            p.write_bytes(data)
            manifest.append({"type": t, "kind": k, "name": e.name, "file": p.name,
                             "size": len(data)})
    (dest / "manifest.json").write_text(json.dumps(
        {"created": dt.datetime.now().isoformat(timespec="seconds"), "files": manifest},
        indent=1))
    _out(manifest, f"{len(manifest)} files saved to {dest}")


def _confirm(msg: str, yes: bool) -> None:
    if not yes and not typer.confirm(msg):
        raise typer.Exit(1)


def _pre_backup(s: Session, slots: list[tuple[int, int]]) -> None:
    """CLI-11: keep the controller's current version before overwriting/deleting it."""
    d = Path("srx_backups") / dt.datetime.now().strftime("%Y%m%d-%H%M%S")
    for t, k in slots:
        if s.directory(t, k) is not None:
            d.mkdir(parents=True, exist_ok=True)
            (d / f"{t:03d}_{Kind(k).name}{Kind(k).ext}").write_bytes(s.recall(t, k))
            typer.echo(f"saved previous {t}/{Kind(k).name} to {d}", err=True)


@app.command()
def send(file: Annotated[Path, typer.Argument(exists=True, dir_okay=False)],
         type_: Annotated[int, typer.Argument(metavar="TYPE")],
         yes: Annotated[bool, typer.Option("--yes", help="Do not ask")] = False) -> None:
    """Write FILE (.OBJ/.DAT/.CDT/.COD) to program TYPE (SEND, WRITE class)."""
    kind = EXT_TO_KIND.get(file.suffix.upper())
    if kind is None:
        _fail(1, f"unsupported file type {file.suffix}")
        return
    data = file.read_bytes()
    _confirm(f"Send {file.name} ({len(data)} bytes) to type {type_}?", yes)
    with _session(write=True) as s:
        _pre_backup(s, [(type_, kind)])
        s.send(type_, kind, data)
    _out({"sent": str(file), "type": type_}, "Transmission complete.")


@app.command()
def delete(type_: Annotated[int, typer.Argument(metavar="TYPE")],
           yes: Annotated[bool, typer.Option("--yes", help="Do not ask")] = False) -> None:
    """Delete program TYPE like FDEL -T (WRITE class)."""
    from srx_link.session import fdel_plan

    _confirm(f"Delete type {type_}?", yes)
    with _session(write=True) as s:
        _pre_backup(s, fdel_plan(type_))
        gone = s.delete_program(type_)
    _out([{"type": t, "kind": k} for t, k in gone], f"deleted {len(gone)} file(s)")


# -- compilers: temporary DOSBox-X backend (spec §6: compile with the original) ------------

@app.command()
def compile(src: Annotated[list[Path], typer.Argument(exists=True, dir_okay=False)]) -> None:
    """Compile .LUN/.PON/.PLC with the original compilers in DOSBox-X (CLI-09)."""
    _run_lang(src, decompile=False)


@app.command()
def decompile(src: Annotated[list[Path], typer.Argument(exists=True, dir_okay=False)]) -> None:
    """Decompile .OBJ/.DAT/.COD with ANNUL/DISPON/DPLC in DOSBox-X (CLI-09)."""
    _run_lang(src, decompile=True)


def _run_lang(srcs: list[Path], decompile: bool) -> None:
    from srx_dosbox.golden import LANGS, compile_many, decompile_many, dos_name

    by_ext = {(lang.bin_ext if decompile else lang.src_ext): lang for lang in LANGS.values()}
    rc = 0
    for p in srcs:
        lang = by_ext.get(p.suffix.upper())
        if lang is None:
            _fail(3, f"{p}: unknown extension")
            return
        if len(p.stem) > 8:
            _fail(3, f"{p}: DOS tools need an 8.3 file name")
        if decompile:
            text = decompile_many(lang, {dos_name(p): p.read_bytes()}).get(dos_name(p))
            if text is None:
                rc = 3
                typer.echo(f"{p}: decompiler produced nothing", err=True)
                continue
            outp = p.with_name(p.stem + ".dec" + lang.src_ext.lower())
            outp.write_bytes(text)
            typer.echo(f"{p} -> {outp}")
            continue
        res = compile_many(lang, [p])[dos_name(p)]
        err = res.get(".ERR", b"").decode("shift_jis", "replace")
        if lang.bin_ext in res:
            p.with_suffix(lang.bin_ext.lower()).write_bytes(res[lang.bin_ext])
            typer.echo(f"{p} -> {p.with_suffix(lang.bin_ext.lower())}")
        else:
            rc = 3
            typer.echo(err.strip() or res[".SCR"].decode().strip(), err=True)
    if rc:
        raise typer.Exit(rc)


def main() -> None:  # pragma: no cover
    app(sys.argv[1:])
