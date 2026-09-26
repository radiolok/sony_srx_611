/*
 * Sony SRX-611 firmware - C equivalents (Hex-Rays) - prefix 'fpu'
 * Source image: ROM1-C.bin (80486 real mode, OS+/386 V2.0)
 * Generated from IDA database ROM1-C.bin.i64
 * Functions in this file: 1
 */

/* ============================================================================
 * fpu_ftoi  @ 0xCDDD4   size=0x30   pop_rank=7/1298
 * calls=108 callers=30
 * note: FPU float->int conversion (rounding mode 0x0C) | [SRX-611] pop_rank=7/1298, sites=108, callers=30, callees=0, size=0x30, leaf
 * --- original assembly (address: bytes  mnemonic) ---------------------------
 * 000CDDD4: 83 EC 0C                 sub     esp, 0Ch
 * 000CDDD7: D9 7C 24 08              fnstcw  [esp+0Ch+var_4]
 * 000CDDDB: 9B                       wait
 * 000CDDDC: 66 8B 44 24 08           mov     ax, [esp+0Ch+var_4]
 * 000CDDE1: 66 83 4C 24 09 0C        or      [esp+0Ch+var_4+1], 0Ch
 * 000CDDE7: 9B                       wait
 * 000CDDE8: D9 6C 24 08              fldcw   [esp+0Ch+var_4]
 * 000CDDEC: DF 3C 24                 fistp   [esp+0Ch+var_C]
 * 000CDDEF: 66 89 44 24 08           mov     [esp+0Ch+var_4], ax
 * 000CDDF4: 9B                       wait
 * 000CDDF5: D9 6C 24 08              fldcw   [esp+0Ch+var_4]
 * 000CDDF9: 8B 04 24                 mov     eax, dword ptr [esp+0Ch+var_C]
 * 000CDDFC: 8B 54 24 04              mov     edx, dword ptr [esp+0Ch+var_C+4]
 * 000CDE00: 83 C4 0C                 add     esp, 0Ch
 * 000CDE03: C3                       retn
 * ========================================================================== */
// FPU float->int conversion (rounding mode 0x0C) | [SRX-611] pop_rank=7/1298, sites=108, callers=30, callees=0, size=0x30, leaf
__int64 __usercall fpu_ftoi@<edx:eax>(long double a1@<st0>)
{
  return (__int64)a1;
}


