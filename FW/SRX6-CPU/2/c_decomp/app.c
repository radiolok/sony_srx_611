/*
 * Sony SRX-611 firmware - C equivalents (Hex-Rays) - prefix 'app'
 * Source image: ROM1-C.bin (80486 real mode, OS+/386 V2.0)
 * Generated from IDA database ROM1-C.bin.i64
 * Functions in this file: 1
 */

/* ============================================================================
 * app_83F4  @ 0x83F4   size=0x15   pop_rank=33/1298
 * calls=24 callers=11
 * note: [SRX-611] pop_rank=33/1298, sites=24, callers=11, callees=0, size=0x15, leaf
 * --- original assembly (address: bytes  mnemonic) ---------------------------
 * 000083F4: 55                       push    ebp
 * 000083F5: 89 E5                    mov     ebp, esp
 * 000083F7: 83 EC 04                 sub     esp, 4
 * 000083FA: 8B 45 08                 mov     eax, [ebp+arg_0]
 * 000083FD: 8A 0D 08 FB 03 00        mov     cl, ds:byte_3FB08
 * 00008403: 88 08                    mov     [eax], cl
 * 00008405: 89 EC                    mov     esp, ebp
 * 00008407: 5D                       pop     ebp
 * 00008408: C3                       retn
 * ========================================================================== */
// [SRX-611] pop_rank=33/1298, sites=24, callers=11, callees=0, size=0x15, leaf
_BYTE *__cdecl app_83F4(_BYTE *a1)
{
  _BYTE *result; // eax

  result = a1;
  *a1 = -117;
  return result;
}


