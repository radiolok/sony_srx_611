"""Rebase ROM1-C.bin.i64 from 0x0 to its link address 0xFFE00000, then reanalyse.

Why: the CPU firmware is 32-bit code linked at 0xFFE00000. Its switch jump tables hold absolute
0xFFExxxxx entries (e.g. token_dispatch: jmp [eax*4+0FFEC5E64h]), which IDA cannot resolve while
the segment starts at 0 (AGENTS.md §8.2). After the rebase, runtime address = 0xFFE00000 + file
offset; all docs keep using FILE OFFSETS, so subtract 0xFFE00000 when copying addresses into docs.

Run on a COPY of the database first (this changes every address):
  & "C:\\Program Files\\IDA Professional 9.0\\idat.exe" -A -L"rebase.log" -S"rebase_ffe00000.py" "<copy>\\ROM1-C.bin.i64"
The database is saved on exit. Check rebase.log for the before/after switch counts.
"""
import ida_auto
import ida_bytes
import ida_ida
import ida_pro
import ida_segment
import idautils
import idc

BASE = 0xFFE00000


def count_bad_switches():
    bad = 0
    for ea in idautils.Heads(ida_ida.inf_get_min_ea(), ida_ida.inf_get_max_ea()):
        if ida_bytes.is_code(ida_bytes.get_flags(ea)) and 'invalid jump table' in (idc.get_cmt(ea, 0) or '') + (idc.generate_disasm_line(ea, 0) or ''):
            bad += 1
    return bad


def main():
    lo = ida_ida.inf_get_min_ea()
    print('[rebase] min_ea=0x%X max_ea=0x%X' % (lo, ida_ida.inf_get_max_ea()))
    if lo != 0:
        print('[rebase] database is not based at 0 (already rebased?) - nothing done')
        return
    seg = ida_segment.getseg(0)
    print('[rebase] seg bitness=%d (2 = 32-bit)' % seg.bitness)
    before = count_bad_switches()
    rc = ida_segment.rebase_program(BASE, ida_segment.MSF_FIXONCE)
    print('[rebase] rebase_program rc=%d (0 = MOVE_SEGM_OK)' % rc)
    if rc != 0:
        return
    ida_auto.plan_range(ida_ida.inf_get_min_ea(), ida_ida.inf_get_max_ea())
    ida_auto.auto_wait()
    after = count_bad_switches()
    print('[rebase] new min_ea=0x%X; "invalid jump table" sites: before=%d after=%d'
          % (ida_ida.inf_get_min_ea(), before, after))
    print('[rebase] token_dispatch now at 0x%X, name=%s'
          % (BASE + 0xC5CC4, idc.get_name(BASE + 0xC5CC4)))


main()
ida_pro.qexit(0)
