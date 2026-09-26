/*
 * Sony SRX-611 firmware - C equivalents (Hex-Rays) - prefix 'disp'
 * Source image: ROM1-C.bin (80486 real mode, OS+/386 V2.0)
 * Generated from IDA database ROM1-C.bin.i64
 * Functions in this file: 3
 */

/* ============================================================================
 * disp_CDB64  @ 0xCDB64   size=0x19   pop_rank=30/1298
 * calls=25 callers=15
 * note: [SRX-611] pop_rank=30/1298, sites=25, callers=15, callees=1, size=0x19
 * --- original assembly (address: bytes  mnemonic) ---------------------------
 * 000CDB64: 55                       push    ebp
 * 000CDB65: 89 E5                    mov     ebp, esp
 * 000CDB67: 6A 00                    push    0
 * 000CDB69: 6A 00                    push    0
 * 000CDB6B: 6A 61                    push    61h ; 'a'
 * 000CDB6D: FF 75 10                 push    [ebp+arg_8]
 * 000CDB70: FF 75 0C                 push    [ebp+arg_4]
 * 000CDB73: FF 75 08                 push    [ebp+arg_0]
 * 000CDB76: E8 3D FF FF FF           call    disp_CDAB8
 * 000CDB7B: C9                       leave
 * 000CDB7C: C3                       retn
 * ========================================================================== */
// [SRX-611] pop_rank=30/1298, sites=25, callers=15, callees=1, size=0x19
int __cdecl disp_CDB64(int a1, int a2, int a3)
{
  return disp_CDAB8(a1, a2, a3, 97, 0, 0);
}


/* ============================================================================
 * disp_C3D04  @ 0xC3D04   size=0x66   pop_rank=35/1298
 * calls=23 callers=5
 * note: [SRX-611] pop_rank=35/1298, sites=23, callers=5, callees=1, size=0x66
 * --- original assembly (address: bytes  mnemonic) ---------------------------
 * 000C3D04: 55                       push    ebp
 * 000C3D05: 89 E5                    mov     ebp, esp
 * 000C3D07: 83 EC 0C                 sub     esp, 0Ch
 * 000C3D0A: A1 E4 75 00 00           mov     eax, dword ptr ds:loc_75E4
 * 000C3D0F: 33 C9                    xor     ecx, ecx
 * 000C3D11: 8A 55 08                 mov     dl, [ebp+arg_0]
 * 000C3D14: 8B 80 48 1E 00 00        mov     eax, [eax+1E48h]
 * 000C3D1A: 88 D1                    mov     cl, dl
 * 000C3D1C: 66 3B 48 18              cmp     cx, [eax+18h]
 * 000C3D20: 76 0A                    jbe     short loc_C3D2C
 * 000C3D22: 66 B8 CC 32              mov     ax, 32CCh
 * 000C3D26: EB 3E                    jmp     short loc_C3D66
 * 000C3D28: 90 90 90 90              db 4 dup(90h)
 * 000C3D2C: 33 C9                    xor     ecx, ecx
 * 000C3D2E: 66 8B 48 12              mov     cx, [eax+12h]
 * 000C3D32: 03 C8                    add     ecx, eax
 * 000C3D34: 33 C0                    xor     eax, eax
 * 000C3D36: 88 D0                    mov     al, dl
 * 000C3D38: C1 E0 04                 shl     eax, 4
 * 000C3D3B: 89 4D FC                 mov     [ebp+var_4], ecx
 * 000C3D3E: 03 C1                    add     eax, ecx
 * 000C3D40: 89 45 FC                 mov     [ebp+var_4], eax
 * 000C3D43: 8B 4D 10                 mov     ecx, [ebp+arg_8]
 * 000C3D46: 8A 10                    mov     dl, [eax]
 * 000C3D48: 88 11                    mov     [ecx], dl
 * 000C3D4A: 66 8B 50 01              mov     dx, [eax+1]
 * 000C3D4E: 83 C0 03                 add     eax, 3
 * 000C3D51: 66 89 51 01              mov     [ecx+1], dx
 * 000C3D55: 8B 4D 0C                 mov     ecx, [ebp+arg_4]
 * 000C3D58: 89 0C 24                 mov     [esp+0Ch+var_C], ecx
 * 000C3D5B: 89 44 24 04              mov     [esp+0Ch+var_8], eax
 * 000C3D5F: E8 F8 A7 00 00           call    strcpy
 * 000C3D64: 2B C0                    sub     eax, eax
 * 000C3D66: 89 EC                    mov     esp, ebp
 * 000C3D68: 5D                       pop     ebp
 * 000C3D69: C3                       retn
 * ========================================================================== */
// [SRX-611] pop_rank=35/1298, sites=23, callers=5, callees=1, size=0x66
__int16 __cdecl disp_C3D04(unsigned __int8 a1, int a2, int a3)
{
  int v3; // eax
  int v5; // [esp+8h] [ebp-4h]

  v3 = *(_DWORD *)(loc_75E4 + 7752);
  if ( a1 > (unsigned int)*(_WORD *)(v3 + 24) )
    return 13004;
  v5 = v3 + *(unsigned __int16 *)(v3 + 18) + 16 * a1;
  *(_BYTE *)a3 = *(_BYTE *)v5;
  *(_WORD *)(a3 + 1) = *(_WORD *)(v5 + 1);
  strcpy(a2, v5 + 3);
  return 0;
}


/* ============================================================================
 * disp_62084  @ 0x62084   size=0x78   pop_rank=43/1298
 * calls=21 callers=12
 * note: [SRX-611] pop_rank=43/1298, sites=21, callers=12, callees=0, size=0x78, leaf
 * --- original assembly (address: bytes  mnemonic) ---------------------------
 * 00062084: 55                       push    ebp
 * 00062085: 89 E5                    mov     ebp, esp
 * 00062087: 83 EC 04                 sub     esp, 4
 * 0006208A: 66 C7 45 FE 00 10        mov     [ebp+var_2], 1000h
 * 00062090: 8B 4D 0C                 mov     ecx, [ebp+arg_4]
 * 00062093: 57                       push    edi
 * 00062094: 56                       push    esi
 * 00062095: 66 8B 45 FC              mov     ax, [ebp+var_4]
 * 00062099: 66 8B 55 08              mov     dx, [ebp+arg_0]
 * 0006209D: 66 BE 00 10              mov     si, 1000h
 * 000620A1: 66 83 FE 01              cmp     si, 1
 * 000620A5: 72 3D                    jb      short loc_620E4
 * 000620A7: 66 3B D6                 cmp     dx, si
 * 000620AA: 72 28                    jb      short loc_620D4
 * 000620AC: 66 89 D0                 mov     ax, dx
 * 000620AF: 2B D2                    sub     edx, edx
 * 000620B1: 66 F7 F6                 div     si
 * 000620B4: 89 C7                    mov     edi, eax
 * 000620B6: 66 83 FF 0A              cmp     di, 0Ah
 * 000620BA: 73 08                    jnb     short loc_620C4
 * 000620BC: 8D 47 30                 lea     eax, [edi+30h]
 * 000620BF: 88 01                    mov     [ecx], al
 * 000620C1: EB 06                    jmp     short loc_620C9
 * 000620C3: 90                       align 4
 * 000620C4: 8D 47 37                 lea     eax, [edi+37h]
 * 000620C7: 88 01                    mov     [ecx], al
 * 000620C9: 89 F8                    mov     eax, edi
 * 000620CB: EB 0A                    jmp     short loc_620D7
 * 000620CD: 90 90 90 90 90 90 90     db 7 dup(90h)
 * 000620D4: C6 01 30                 mov     byte ptr [ecx], 30h ; '0'
 * 000620D7: 41                       inc     ecx
 * 000620D8: 66 C1 EE 04              shr     si, 4
 * 000620DC: EB C3                    jmp     short loc_620A1
 * 000620DE: 90 90 90 90 90 90        db 6 dup(90h)
 * 000620E4: 66 89 75 FE              mov     [ebp+var_2], si
 * 000620E8: 89 4D 0C                 mov     [ebp+arg_4], ecx
 * 000620EB: 66 89 55 08              mov     [ebp+arg_0], dx
 * 000620EF: 5E                       pop     esi
 * 000620F0: 66 89 45 FC              mov     [ebp+var_4], ax
 * 000620F4: C6 01 00                 mov     byte ptr [ecx], 0
 * 000620F7: 5F                       pop     edi
 * 000620F8: 89 EC                    mov     esp, ebp
 * 000620FA: 5D                       pop     ebp
 * 000620FB: C3                       retn
 * ========================================================================== */
// [SRX-611] pop_rank=43/1298, sites=21, callers=12, callees=0, size=0x78, leaf
unsigned __int16 __cdecl disp_62084(unsigned __int16 a1, _BYTE *a2)
{
  unsigned __int16 result; // ax
  unsigned __int16 i; // si
  unsigned __int16 v6; // [esp+8h] [ebp-4h]

  result = v6;
  for ( i = 4096; i; i >>= 4 )
  {
    if ( a1 < i )
    {
      *a2 = 48;
    }
    else
    {
      result = a1 / i;
      a1 %= i;
      if ( result >= 0xAu )
        *a2 = result + 55;
      else
        *a2 = result + 48;
    }
    ++a2;
  }
  *a2 = 0;
  return result;
}


