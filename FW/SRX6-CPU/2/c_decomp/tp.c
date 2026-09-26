/*
 * Sony SRX-611 firmware - C equivalents (Hex-Rays) - prefix 'tp'
 * Source image: ROM1-C.bin (80486 real mode, OS+/386 V2.0)
 * Generated from IDA database ROM1-C.bin.i64
 * Functions in this file: 1
 */

/* ============================================================================
 * tp_19CDC  @ 0x19CDC   size=0x69   pop_rank=49/1298
 * calls=19 callers=14
 * note: [SRX-611] pop_rank=49/1298, sites=19, callers=14, callees=0, size=0x69, leaf
 * --- original assembly (address: bytes  mnemonic) ---------------------------
 * 00019CDC: 55                       push    ebp
 * 00019CDD: 89 E5                    mov     ebp, esp
 * 00019CDF: 83 EC 04                 sub     esp, 4
 * 00019CE2: 8A 45 08                 mov     al, [ebp+arg_0]
 * 00019CE5: 3C 01                    cmp     al, 1
 * 00019CE7: 72 08                    jb      short loc_19CF1
 * 00019CE9: 3C 12                    cmp     al, 12h
 * 00019CEB: 77 04                    ja      short loc_19CF1
 * 00019CED: 3C 09                    cmp     al, 9
 * 00019CEF: 75 0B                    jnz     short loc_19CFC
 * 00019CF1: 66 B8 EA 2E              mov     ax, 2EEAh
 * 00019CF5: EB 4A                    jmp     short loc_19D41
 * 00019CF7: 90 90 90 90 90           db 5 dup(90h)
 * 00019CFC: 25 FF 00 00 00           and     eax, 0FFh
 * 00019D01: 8B 4D 0C                 mov     ecx, [ebp+arg_4]
 * 00019D04: 8D 14 80                 lea     edx, [eax+eax*4]
 * 00019D07: C1 E2 02                 shl     edx, 2
 * 00019D0A: 8D 82 DC 72 00 00        lea     eax, [edx+72DCh]
 * 00019D10: 89 45 FC                 mov     [ebp+var_4], eax
 * 00019D13: 66 C7 01 00 00           mov     word ptr [ecx], 0
 * 00019D18: 80 BA DC 72 00 00 01     cmp     byte ptr [edx+72DCh], 1
 * 00019D1F: 75 1E                    jnz     short loc_19D3F
 * 00019D21: 66 8B 82 E2 72 00 00     mov     ax, [edx+72E2h]
 * 00019D28: A8 02                    test    al, 2
 * 00019D2A: 74 10                    jz      short loc_19D3C
 * 00019D2C: 66 25 F3 FF              and     ax, 0FFF3h
 * 00019D30: 66 89 01                 mov     [ecx], ax
 * 00019D33: EB 0A                    jmp     short loc_19D3F
 * 00019D35: 90 90 90 90 90 90 90     db 7 dup(90h)
 * 00019D3C: 66 89 01                 mov     [ecx], ax
 * 00019D3F: 2B C0                    sub     eax, eax
 * 00019D41: 89 EC                    mov     esp, ebp
 * 00019D43: 5D                       pop     ebp
 * 00019D44: C3                       retn
 * ========================================================================== */
// [SRX-611] pop_rank=49/1298, sites=19, callers=14, callees=0, size=0x69, leaf
__int16 __cdecl tp_19CDC(unsigned __int8 a1, __int16 *a2)
{
  __int16 v3; // ax

  if ( !a1 || a1 > 0x12u || a1 == 9 )
    return 12010;
  *a2 = 0;
  if ( *((_BYTE *)&loc_72DC + 20 * a1) == 1 )
  {
    v3 = word_72E2[10 * a1];
    if ( (v3 & 2) != 0 )
      v3 &= 0xFFF3u;
    *a2 = v3;
  }
  return 0;
}


