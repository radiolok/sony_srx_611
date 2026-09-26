/*
 * Sony SRX-611 firmware - C equivalents (Hex-Rays) - prefix 'flag'
 * Source image: ROM1-C.bin (80486 real mode, OS+/386 V2.0)
 * Generated from IDA database ROM1-C.bin.i64
 * Functions in this file: 1
 */

/* ============================================================================
 * flag_get  @ 0x3BEC8   size=0x51   pop_rank=28/1298
 * calls=25 callers=20
 * note: Validate index and read a flag word from a record | [SRX-611] pop_rank=28/1298, sites=25, callers=20, callees=0, size=0x51, leaf
 * --- original assembly (address: bytes  mnemonic) ---------------------------
 * 0003BEC8: 55                       push    ebp
 * 0003BEC9: 89 E5                    mov     ebp, esp
 * 0003BECB: 83 EC 04                 sub     esp, 4
 * 0003BECE: 8A 45 08                 mov     al, [ebp+arg_0]
 * 0003BED1: 22 C0                    and     al, al
 * 0003BED3: 74 04                    jz      short loc_3BED9
 * 0003BED5: 3C 08                    cmp     al, 8
 * 0003BED7: 76 07                    jbe     short loc_3BEE0
 * 0003BED9: 66 B8 80 40              mov     ax, 4080h
 * 0003BEDD: EB 36                    jmp     short loc_3BF15
 * 0003BEDF: 90                       align 10h
 * 0003BEE0: 25 FF 00 00 00           and     eax, 0FFh
 * 0003BEE5: 80 B8 CB 74 00 00 01     cmp     byte ptr [eax+74CBh], 1
 * 0003BEEC: 74 0A                    jz      short loc_3BEF8
 * 0003BEEE: 66 B8 80 40              mov     ax, 4080h
 * 0003BEF2: EB 21                    jmp     short loc_3BF15
 * 0003BEF4: 90 90 90 90              align 8
 * 0003BEF8: 8B 04 85 A8 74 00 00     mov     eax, dword ptr ds:loc_74A7+1[eax*4]
 * 0003BEFF: 8B 4D 0C                 mov     ecx, [ebp+arg_4]
 * 0003BF02: 66 F7 40 02 FF FF        test    word ptr [eax+2], 0FFFFh
 * 0003BF08: 74 06                    jz      short loc_3BF10
 * 0003BF0A: C6 01 01                 mov     byte ptr [ecx], 1
 * 0003BF0D: EB 04                    jmp     short loc_3BF13
 * 0003BF0F: 90                       align 10h
 * 0003BF10: C6 01 00                 mov     byte ptr [ecx], 0
 * 0003BF13: 2B C0                    sub     eax, eax
 * 0003BF15: 89 EC                    mov     esp, ebp
 * 0003BF17: 5D                       pop     ebp
 * 0003BF18: C3                       retn
 * ========================================================================== */
// Validate index and read a flag word from a record | [SRX-611] pop_rank=28/1298, sites=25, callers=20, callees=0, size=0x51, leaf
__int16 __cdecl flag_get(unsigned __int8 a1, _BYTE *a2)
{
  if ( !a1 || a1 > 8u )
    return 16512;
  if ( *((_BYTE *)&loc_74C4 + a1 + 7) != 1 )
    return 16512;
  if ( *(_WORD *)(*(_DWORD *)((char *)&loc_74A7 + 4 * a1 + 1) + 2) )
    *a2 = 1;
  else
    *a2 = 0;
  return 0;
}


