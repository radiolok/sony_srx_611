# Pendant remote control for the emulator

Lets an agent or script drive the emulated teach pendant step by step and read the LCD.

| File | Purpose |
|---|---|
| `tpctl.lua` | MAME autoboot script. Every frame it polls `/work/cmd`; it executes the commands in order and appends results to `/work/out`. |
| `tp.sh` | Sends a batch of commands, waits for them to finish, appends the raw output to a log, and prints the screens. |
| `tpfmt.py` | Converts the `dump` output to text: JIS X 0201 katakana, plus the pendant glyphs `│ ▶ ↑ ↓`. |

Commands, one per line:

- `key <col> <rows> [ms]`: press a key and release it.
- `raw <col> <rows>`: set a column and hold it (modifiers, the key-sheet bit `raw 6 2` = English).
- `wait <ms>`, `dump [tag]` (LCD).
- `peek <addr> <n>`: CPU bytes. `tppeek`: pendant RAM.
- `cmds`, `keys`, `serlog`, `ctl`: TP command counts, key codes, ch1 bytes, 8251/8254 writes.
- `find16`, `find32`, `codeptrs`, `pcs <frames>`: RAM search and PC histogram.
- `quit`.

Example:

```sh
mkdir -p work nvram
docker run -d --name srxtp --user "$(id -u):$(id -g)" -v "$PWD/nvram:/nvram" \
  -v "$PWD/emu/tools/tp:/lua:ro" -v "$PWD/work:/work" \
  srx-c61-emu srx_c61 -video none -sound none -autoboot_script /lua/tpctl.lua
TP_WORK=$PWD/work emu/tools/tp/tp.sh session.log "raw 6 2" "wait 14000" "dump boot"
```

Key map and menu screens: `doc/tp_menu_walkthrough.md`.

Note: Lua read taps on the i386 program space do not fire, while write taps do.
