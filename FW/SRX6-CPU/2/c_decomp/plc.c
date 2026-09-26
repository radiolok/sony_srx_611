/*
 * Sony SRX-611 firmware - C equivalents (Hex-Rays) - prefix 'plc'
 * Source image: ROM1-C.bin (80486 real mode, OS+/386 V2.0)
 * Generated from IDA database ROM1-C.bin.i64
 * Functions in this file: 1
 */

/* ============================================================================
 * plc_AD04  @ 0xAD04   size=0x2E   pop_rank=39/1298
 * calls=22 callers=22
 * note: [SRX-611] pop_rank=39/1298, sites=22, callers=22, callees=0, size=0x2E, leaf
 * --- original assembly (address: bytes  mnemonic) ---------------------------
 * 0000AD04: 55                       push    ebp
 * 0000AD05: 89 E5                    mov     ebp, esp
 * 0000AD07: 83 EC 04                 sub     esp, 4
 * 0000AD0A: 8B 45 08                 mov     eax, [ebp+arg_0]
 * 0000AD0D: 8A 0D 50 4A 00 00        mov     cl, byte ptr ds:loc_4A4E+2
 * 0000AD13: 88 08                    mov     [eax], cl
 * 0000AD15: 80 3D 50 4A 00 00 06     cmp     byte ptr ds:loc_4A4E+2, 6
 * 0000AD1C: 76 0E                    jbe     short loc_AD2C
 * 0000AD1E: C6 00 01                 mov     byte ptr [eax], 1
 * 0000AD21: 66 B8 08 2B              mov     ax, 2B08h
 * 0000AD25: EB 07                    jmp     short loc_AD2E
 * 0000AD27: 90 90 90 90 90           db 5 dup(90h)
 * 0000AD2C: 2B C0                    sub     eax, eax
 * 0000AD2E: 89 EC                    mov     esp, ebp
 * 0000AD30: 5D                       pop     ebp
 * 0000AD31: C3                       retn
 * ========================================================================== */
// [SRX-611] pop_rank=39/1298, sites=22, callers=22, callees=0, size=0x2E, leaf
__int16 __cdecl plc_AD04(_BYTE *a1)
{
  *a1 = *(&loc_4A4E + 2);
  if ( *(&loc_4A4E + 2) <= 6u )
    return 0;
  *a1 = 1;
  return 11016;
}


