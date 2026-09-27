# SRXWIN-NG

A modern replacement for the Sony SRXWIN host toolchain (SRX-611 SCARA controller).
The specification (Russian) is [`../doc/SRXWIN-NG.md`](../doc/SRXWIN-NG.md), and the
wire protocol is [`docs/spec/PROTOCOL.md`](docs/spec/PROTOCOL.md).

**Status (2026-09-27): stage 0 + stage 1 done without hardware.**
- The original DOS tools run headless in DOSBox-X.
- A fake controller (`srx-fake`) passes the stage-1 gate: the original SEND, FILES,
  RECALL, HIST and FDEL work against it.
- `srx_link` sends byte-identical requests.
- The `srx` CLI covers the DOS-tool set. Compiling still uses the original compilers
  (spec §6: the "first useful point").
- Nothing has been tried on a real controller yet.

## Setup (Linux)

```sh
sudo apt install dosbox-x          # oracle for tests and the temporary compiler backend
python3 -m venv .venv && .venv/bin/pip install -e '.[dev]'
.venv/bin/python -m pytest         # ~10 s; DOSBox tests auto-skip if dosbox-x is missing
.venv/bin/ruff check src tests tools && .venv/bin/mypy
```

The original EXEs are read from `../SRXWIN/` (or `$SRXWIN_DIR`) and MD5-checked by
`tests/test_originals.py`. They are not copied into `vendor/`.

## Usage

```sh
srx-fake --port 5000 --state ./fakestate &           # fake controller
srx --tcp 127.0.0.1:5000 files                       # FILES
srx compile PROG.LUN PROG.PON                        # LUNNA / POINT in DOSBox-X
srx --tcp 127.0.0.1:5000 send PROG.obj 2 --yes       # SEND (auto-backs-up the old copy)
srx --tcp 127.0.0.1:5000 recall 2 -o out/            # RECALL (.OBJ + .DAT)
srx --tcp 127.0.0.1:5000 backup ./backup             # every program + manifest.json
srx --tcp 127.0.0.1:5000 hist                        # error history
srx --tcp 127.0.0.1:5000 delete 2 --yes              # FDEL -T2
srx decompile out/T1.OBJ                             # ANNUL / DISPON / DPLC
```
- For a real controller, use `--port /dev/ttyUSB0` (9600 8N2, DTR/RTS raised, DSR checked).
- `--journal FILE` writes every byte as JSON Lines, which can be replayed with
  `ReplayTransport`.
- Exit codes: 0 ok, 1 controller error / refused, 2 link, 3 compile.
- **Before the first real connection, read spec §8** (backup with the original tools
  first; no `.CTR` writes; only commands seen in recorded sessions).

To run the original tools against the fake by hand:
`serial1=nullmodem server:127.0.0.1 port:5000` in a DOSBox-X config.

## Layout

| Path | Contents |
|---|---|
| `src/srx_link/` | frames, status → exceptions, transports (serial, TCP/nullmodem, replay, loopback), `Session` with danger classes and journal |
| `src/srx_formats/` | common file header (`.OBJ/.DAT/.CDT/.COD/.CTR`) |
| `src/srx_fake/` | fake controller + TCP server in DOSBox-X nullmodem format |
| `src/srx_dosbox/` | DOSBox-X runner (screen capture via `SCRDUMP.COM`) and golden runner |
| `src/srx_cli/` | `srx` command |
| `tools/golden/make_golden.py` | regenerate `corpus/golden/` with the originals |
| `corpus/{lun,pon,plc}/` | corpus sources (self-written; `*ERR*` = negative cases) |
| `corpus/golden/` | oracle outputs: `.OBJ/.DAT/.COD`, `.ERR`, `.SCR` screen, `.DEC.*` decompiled |
| `docs/spec/` | `PROTOCOL.md`, `FORMATS.md` |

Deviations from spec §3:
- One Python distribution with several import packages, instead of separate
  `packages/*`.
- `fake_controller` and the golden runner live under `src/` so the tests can import
  them.
- CI is GitHub Actions: `../.github/workflows/srxwin-ng.yml`. It runs ruff + mypy, the
  full suite with the DOSBox-X oracle on Ubuntu 24.04 (Python 3.12 and 3.14; it fails
  if the oracle tests were skipped), and the non-DOSBox tests on Windows.

## Oracle notes (things that bite)

- LUNNA and POINT write to video memory, so stdout redirection is empty. The runner dumps
  B800:0000 after each command. LUNNA clears the screen on exit, so use its `-E` `.ERR`
  file instead.
- SEND, RECALL, FDEL and the decompilers ask `(y/n)`. Feed `< _YES.TXT`, which the runner
  creates.
- On SIGTERM, DOSBox-X shows a "quit anyway?" prompt while a program runs, so the runner
  always uses SIGKILL.
- A tool started without a controller waits forever on COM1. Always pass `serial_port`
  or keep serial off.

## Next steps (hardware-free)

1. Stage 3: `.DAT` and `.COD` formats and the DISPON/DPLC equivalents, driven by a growing
   corpus (one file per keyword; see `doc/LUNA_token_map.md`).
2. Stage 5: resolve the SRXMONIE monitoring commands. The firmware handler table is at
   `0x51828`. Extend `srx_fake` so SRXMONIE in Win 3.11/86Box can connect.
3. Stage 1 on hardware (needs the robot): record FILES/RECALL/HIST with a sniffer, and
   check the `05` reply and history-record hypotheses in `PROTOCOL.md`.
