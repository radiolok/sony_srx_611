/*
 * Sony SRX-611 firmware - C equivalents (Hex-Rays) - prefix 'int'
 * Source image: ROM1-C.bin (80486 real mode, OS+/386 V2.0)
 * Generated from IDA database ROM1-C.bin.i64
 * Functions in this file: 2
 */

/* ============================================================================
 * int_restore  @ 0xCDE0C   size=0x7   pop_rank=4/1298
 * calls=150 callers=144
 * note: Restore EFLAGS (critical section exit) | [SRX-611] pop_rank=4/1298, sites=150, callers=144, callees=0, size=0x7, leaf
 * --- original assembly (address: bytes  mnemonic) ---------------------------
 * 000CDE0C: 8B 44 24 04              mov     eax, [esp+arg_0]
 * 000CDE10: 50                       push    eax
 * 000CDE11: 9D                       popf
 * 000CDE12: C3                       retn
 * ========================================================================== */
// Restore EFLAGS (critical section exit) | [SRX-611] pop_rank=4/1298, sites=150, callers=144, callees=0, size=0x7, leaf
unsigned int __cdecl int_restore(unsigned int a1)
{
  unsigned int result; // eax

  result = a1;
  __writeeflags(a1);
  return result;
}


/* ============================================================================
 * int_disable  @ 0xCDE08   size=0x4   pop_rank=5/1298
 * calls=149 callers=144
 * note: Save EFLAGS and disable interrupts (critical section enter) | [SRX-611] pop_rank=5/1298, sites=149, callers=144, callees=0, size=0x4, leaf
 * --- original assembly (address: bytes  mnemonic) ---------------------------
 * 000CDE08: 9C                       pushf
 * 000CDE09: 58                       pop     eax
 * 000CDE0A: FA                       cli
 * 000CDE0B: C3                       retn
 * ========================================================================== */
// Save EFLAGS and disable interrupts (critical section enter) | [SRX-611] pop_rank=5/1298, sites=149, callers=144, callees=0, size=0x4, leaf
unsigned int int_disable()
{
  unsigned int v0; // kr00_4
  unsigned int result; // eax

  v0 = __getcallerseflags();
  result = v0;
  _disable();
  return result;
}


