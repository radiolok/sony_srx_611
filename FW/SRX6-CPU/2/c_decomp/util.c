/*
 * Sony SRX-611 firmware - C equivalents (Hex-Rays) - prefix 'util'
 * Source image: ROM1-C.bin (80486 real mode, OS+/386 V2.0)
 * Generated from IDA database ROM1-C.bin.i64
 * Functions in this file: 7
 */

/* ============================================================================
 * util_653FC  @ 0x653FC   size=0x53   pop_rank=22/1298
 * calls=31 callers=16
 * note: [SRX-611] pop_rank=22/1298, sites=31, callers=16, callees=0, size=0x53, leaf
 * --- original assembly (address: bytes  mnemonic) ---------------------------
 * 000653FC: 55                       push    ebp
 * 000653FD: 89 E5                    mov     ebp, esp
 * 000653FF: 83 EC 04                 sub     esp, 4
 * 00065402: 8B 55 08                 mov     edx, [ebp+arg_0]
 * 00065405: 66 C7 45 FE 00 00        mov     [ebp+var_2], 0
 * 0006540B: 2B C0                    sub     eax, eax
 * 0006540D: 66 8B 8A 20 14 00 00     mov     cx, [edx+1420h]
 * 00065414: 66 83 F9 6F              cmp     cx, 6Fh ; 'o'
 * 00065418: 75 02                    jnz     short loc_6541C
 * 0006541A: EB 2F                    jmp     short loc_6544B
 * 0006541C: 66 83 F9 6E              cmp     cx, 6Eh ; 'n'
 * 00065420: 75 02                    jnz     short loc_65424
 * 00065422: EB 27                    jmp     short loc_6544B
 * 00065424: 66 81 F9 A4 00           cmp     cx, 0A4h
 * 00065429: 75 09                    jnz     short loc_65434
 * 0006542B: EB 1E                    jmp     short loc_6544B
 * 0006542D: 90 90 90 90 90 90 90     db 7 dup(90h)
 * 00065434: 66 81 F9 A5 00           cmp     cx, 0A5h
 * 00065439: 75 09                    jnz     short loc_65444
 * 0006543B: EB 0E                    jmp     short loc_6544B
 * 0006543D: 90 90 90 90 90 90 90     db 7 dup(90h)
 * 00065444: 66 89 8A 22 14 00 00     mov     [edx+1422h], cx
 * 0006544B: 89 EC                    mov     esp, ebp
 * 0006544D: 5D                       pop     ebp
 * 0006544E: C3                       retn
 * ========================================================================== */
// [SRX-611] pop_rank=22/1298, sites=31, callers=16, callees=0, size=0x53, leaf
int __cdecl util_653FC(int a1)
{
  int result; // eax
  __int16 v2; // cx

  result = 0;
  v2 = *(_WORD *)(a1 + 5152);
  if ( v2 != 111 && v2 != 110 && v2 != 164 && v2 != 165 )
    *(_WORD *)(a1 + 5154) = v2;
  return result;
}


/* ============================================================================
 * util_61CD4  @ 0x61CD4   size=0xE8   pop_rank=34/1298
 * calls=23 callers=13
 * note: [SRX-611] pop_rank=34/1298, sites=23, callers=13, callees=0, size=0xE8, leaf
 * --- original assembly (address: bytes  mnemonic) ---------------------------
 * 00061CD4: 55                       push    ebp
 * 00061CD5: 89 E5                    mov     ebp, esp
 * 00061CD7: 83 EC 18                 sub     esp, 18h
 * 00061CDA: 8A 45 08                 mov     al, [ebp+arg_0]
 * 00061CDD: C6 45 E9 03              mov     [ebp+var_17], 3
 * 00061CE1: 57                       push    edi
 * 00061CE2: 56                       push    esi
 * 00061CE3: 53                       push    ebx
 * 00061CE4: C6 45 E8 00              mov     [ebp+var_18], 0
 * 00061CE8: 89 45 F0                 mov     [ebp+var_10], eax
 * 00061CEB: 8A 55 E9                 mov     dl, [ebp+var_17]
 * 00061CEE: 2B C0                    sub     eax, eax
 * 00061CF0: 66 C7 45 EA 64 00        mov     [ebp+var_16], 64h ; 'd'
 * 00061CF6: 8A 5D E8                 mov     bl, [ebp+var_18]
 * 00061CF9: 8B 4D 10                 mov     ecx, [ebp+arg_8]
 * 00061CFC: 66 BE 64 00              mov     si, 64h ; 'd'
 * 00061D00: 89 55 F4                 mov     [ebp+var_C], edx
 * 00061D03: 66 83 FE 01              cmp     si, 1
 * 00061D07: 0F 82 8F 00 00 00        jb      loc_61D9C
 * 00061D0D: 66 83 FE 01              cmp     si, 1
 * 00061D11: 75 04                    jnz     short loc_61D17
 * 00061D13: B3 01                    mov     bl, 1
 * 00061D15: B0 01                    mov     al, 1
 * 00061D17: 33 D2                    xor     edx, edx
 * 00061D19: 8A 55 F0                 mov     dl, byte ptr [ebp+var_10]
 * 00061D1C: 89 55 FC                 mov     [ebp+var_4], edx
 * 00061D1F: 8A 55 0C                 mov     dl, [ebp+arg_4]
 * 00061D22: 3A 55 F4                 cmp     dl, byte ptr [ebp+var_C]
 * 00061D25: 72 45                    jb      short loc_61D6C
 * 00061D27: 66 39 75 FC              cmp     word ptr [ebp+var_4], si
 * 00061D2B: 72 1F                    jb      short loc_61D4C
 * 00061D2D: 33 C0                    xor     eax, eax
 * 00061D2F: 8A 45 F0                 mov     al, byte ptr [ebp+var_10]
 * 00061D32: 99                       cdq
 * 00061D33: 81 E6 FF FF 00 00        and     esi, 0FFFFh
 * 00061D39: B3 01                    mov     bl, 1
 * 00061D3B: F7 FE                    idiv    esi
 * 00061D3D: 04 30                    add     al, 30h ; '0'
 * 00061D3F: 88 01                    mov     [ecx], al
 * 00061D41: B0 01                    mov     al, 1
 * 00061D43: EB 1A                    jmp     short loc_61D5F
 * 00061D45: 90 90 90 90 90 90 90     db 7 dup(90h)
 * 00061D4C: 22 C0                    and     al, al
 * 00061D4E: 75 0C                    jnz     short loc_61D5C
 * 00061D50: C6 01 20                 mov     byte ptr [ecx], 20h ; ' '
 * 00061D53: EB 0A                    jmp     short loc_61D5F
 * 00061D55: 90 90 90 90 90 90 90     db 7 dup(90h)
 * 00061D5C: C6 01 30                 mov     byte ptr [ecx], 30h ; '0'
 * 00061D5F: 41                       inc     ecx
 * 00061D60: 89 5D EC                 mov     [ebp+var_14], ebx
 * 00061D63: 89 45 F8                 mov     [ebp+var_8], eax
 * 00061D66: EB 0A                    jmp     short loc_61D72
 * 00061D68: 90 90 90 90              db 4 dup(90h)
 * 00061D6C: 89 5D EC                 mov     [ebp+var_14], ebx
 * 00061D6F: 89 45 F8                 mov     [ebp+var_8], eax
 * 00061D72: 66 8B 45 FC              mov     ax, word ptr [ebp+var_4]
 * 00061D76: 2B D2                    sub     edx, edx
 * 00061D78: 66 F7 F6                 div     si
 * 00061D7B: 66 89 F0                 mov     ax, si
 * 00061D7E: 66 BB 0A 00              mov     bx, 0Ah
 * 00061D82: 89 D7                    mov     edi, edx
 * 00061D84: 2B D2                    sub     edx, edx
 * 00061D86: 66 F7 F3                 div     bx
 * 00061D89: FE 4D F4                 dec     byte ptr [ebp+var_C]
 * 00061D8C: 8B 5D EC                 mov     ebx, [ebp+var_14]
 * 00061D8F: 89 7D F0                 mov     [ebp+var_10], edi
 * 00061D92: 89 C6                    mov     esi, eax
 * 00061D94: 8B 45 F8                 mov     eax, [ebp+var_8]
 * 00061D97: E9 67 FF FF FF           jmp     loc_61D03
 * 00061D9C: 8B 45 F0                 mov     eax, [ebp+var_10]
 * 00061D9F: 88 5D E8                 mov     [ebp+var_18], bl
 * 00061DA2: 5B                       pop     ebx
 * 00061DA3: 66 89 75 EA              mov     [ebp+var_16], si
 * 00061DA7: 89 4D 10                 mov     [ebp+arg_8], ecx
 * 00061DAA: 88 45 08                 mov     [ebp+arg_0], al
 * 00061DAD: 5E                       pop     esi
 * 00061DAE: 8B 45 F4                 mov     eax, [ebp+var_C]
 * 00061DB1: 88 45 E9                 mov     [ebp+var_17], al
 * 00061DB4: C6 01 00                 mov     byte ptr [ecx], 0
 * 00061DB7: 5F                       pop     edi
 * 00061DB8: 89 EC                    mov     esp, ebp
 * 00061DBA: 5D                       pop     ebp
 * 00061DBB: C3                       retn
 * ========================================================================== */
// [SRX-611] pop_rank=34/1298, sites=23, callers=13, callees=0, size=0xE8, leaf
int __usercall util_61CD4@<eax>(int a1@<edx>, int a2@<ebx>, char a3, unsigned __int8 a4, _BYTE *a5)
{
  int v5; // eax
  unsigned __int16 v7; // si
  int result; // eax
  int v9; // [esp+10h] [ebp-14h]
  __int16 v10; // [esp+14h] [ebp-10h]
  int v11; // [esp+18h] [ebp-Ch]
  int v12; // [esp+1Ch] [ebp-8h]

  LOBYTE(v10) = a3;
  LOBYTE(a1) = 3;
  v5 = 0;
  LOBYTE(a2) = 0;
  v7 = 100;
  v11 = a1;
  while ( v7 )
  {
    if ( v7 == 1 )
    {
      LOBYTE(a2) = 1;
      LOBYTE(v5) = 1;
    }
    if ( a4 < (unsigned __int8)v11 )
    {
      v9 = a2;
      v12 = v5;
    }
    else
    {
      if ( (unsigned __int8)v10 < v7 )
      {
        if ( (_BYTE)v5 )
          *a5 = 48;
        else
          *a5 = 32;
      }
      else
      {
        LOBYTE(a2) = 1;
        v5 = (unsigned __int8)v10 / (int)v7;
        *a5 = v5 + 48;
        LOBYTE(v5) = 1;
      }
      ++a5;
      v9 = a2;
      v12 = v5;
    }
    LOBYTE(v11) = v11 - 1;
    a2 = v9;
    v10 = (unsigned __int8)v10 % v7;
    v7 /= 0xAu;
    v5 = v12;
  }
  result = v11;
  *a5 = 0;
  return result;
}


/* ============================================================================
 * util_6735C  @ 0x6735C   size=0x4F   pop_rank=36/1298
 * calls=23 callers=5
 * note: [SRX-611] pop_rank=36/1298, sites=23, callers=5, callees=0, size=0x4F, leaf
 * --- original assembly (address: bytes  mnemonic) ---------------------------
 * 0006735C: 55                       push    ebp
 * 0006735D: 89 E5                    mov     ebp, esp
 * 0006735F: 83 EC 04                 sub     esp, 4
 * 00067362: 66 C7 45 FE 00 00        mov     [ebp+var_2], 0
 * 00067368: 8B 4D 08                 mov     ecx, [ebp+arg_0]
 * 0006736B: 56                       push    esi
 * 0006736C: 83 EC 0C                 sub     esp, 0Ch
 * 0006736F: 89 0C 24                 mov     [esp+14h+var_14], ecx
 * 00067372: 66 8B 45 0C              mov     ax, [ebp+arg_4]
 * 00067376: 89 44 24 04              mov     [esp+14h+var_10], eax
 * 0006737A: 33 C0                    xor     eax, eax
 * 0006737C: 8B 75 10                 mov     esi, [ebp+arg_8]
 * 0006737F: 89 74 24 08              mov     [esp+14h+var_C], esi
 * 00067383: 66 8B 81 20 14 00 00     mov     ax, [ecx+1420h]
 * 0006738A: FF 14 85 78 12 00 00     call    ds:dword_1278[eax*4]
 * 00067391: 66 89 45 FE              mov     [ebp+var_2], ax
 * 00067395: 66 23 C0                 and     ax, ax
 * 00067398: 74 0A                    jz      short loc_673A4
 * 0006739A: 66 8B 15 40 80 00 00     mov     dx, word ptr ds:loc_8040
 * 000673A1: 66 89 16                 mov     [esi], dx
 * 000673A4: 8B 75 F8                 mov     esi, [ebp+var_8]
 * 000673A7: 89 EC                    mov     esp, ebp
 * 000673A9: 5D                       pop     ebp
 * 000673AA: C3                       retn
 * ========================================================================== */
// [SRX-611] pop_rank=36/1298, sites=23, callers=5, callees=0, size=0x4F, leaf
int __cdecl util_6735C(int a1, __int16 a2, _WORD *a3)
{
  int result; // eax

  result = ((int (__stdcall *)(int, __int16, _WORD *))dword_1278[*(unsigned __int16 *)(a1 + 5152)])(a1, a2, a3);
  if ( (_WORD)result )
    *a3 = loc_8040;
  return result;
}


/* ============================================================================
 * util_61C0C  @ 0x61C0C   size=0xC7   pop_rank=41/1298
 * calls=21 callers=19
 * note: [SRX-611] pop_rank=41/1298, sites=21, callers=19, callees=0, size=0xC7, leaf
 * --- original assembly (address: bytes  mnemonic) ---------------------------
 * 00061C0C: 55                       push    ebp
 * 00061C0D: 89 E5                    mov     ebp, esp
 * 00061C0F: 83 EC 10                 sub     esp, 10h
 * 00061C12: 2B C0                    sub     eax, eax
 * 00061C14: 8A 55 08                 mov     dl, [ebp+arg_0]
 * 00061C17: 57                       push    edi
 * 00061C18: 56                       push    esi
 * 00061C19: 53                       push    ebx
 * 00061C1A: 66 C7 45 F6 64 00        mov     [ebp+var_A], 64h ; 'd'
 * 00061C20: 66 BF 64 00              mov     di, 64h ; 'd'
 * 00061C24: C6 45 F5 00              mov     [ebp+var_B], 0
 * 00061C28: 8B 75 0C                 mov     esi, [ebp+arg_4]
 * 00061C2B: 22 D2                    and     dl, dl
 * 00061C2D: 75 15                    jnz     short loc_61C44
 * 00061C2F: 66 8B 15 E8 78 00 00     mov     dx, ds:word_78E8
 * 00061C36: 66 89 16                 mov     [esi], dx
 * 00061C39: E9 8E 00 00 00           jmp     loc_61CCC
 * 00061C3E: 90 90 90 90 90 90        db 6 dup(90h)
 * 00061C44: 8A 5D F5                 mov     bl, [ebp+var_B]
 * 00061C47: 66 83 FF 01              cmp     di, 1
 * 00061C4B: 72 6F                    jb      short loc_61CBC
 * 00061C4D: 33 C9                    xor     ecx, ecx
 * 00061C4F: 88 D1                    mov     cl, dl
 * 00061C51: 66 3B CF                 cmp     cx, di
 * 00061C54: 72 2E                    jb      short loc_61C84
 * 00061C56: 33 C0                    xor     eax, eax
 * 00061C58: 88 D0                    mov     al, dl
 * 00061C5A: 99                       cdq
 * 00061C5B: 81 E7 FF FF 00 00        and     edi, 0FFFFh
 * 00061C61: F7 FF                    idiv    edi
 * 00061C63: 04 30                    add     al, 30h ; '0'
 * 00061C65: 88 06                    mov     [esi], al
 * 00061C67: 2B D2                    sub     edx, edx
 * 00061C69: 66 89 C8                 mov     ax, cx
 * 00061C6C: 66 F7 F7                 div     di
 * 00061C6F: 46                       inc     esi
 * 00061C70: B1 01                    mov     cl, 1
 * 00061C72: C7 45 FC 01 00 00 00     mov     [ebp+var_4], 1
 * 00061C79: 89 55 F8                 mov     [ebp+var_8], edx
 * 00061C7C: EB 26                    jmp     short loc_61CA4
 * 00061C7E: 90 90 90 90 90 90        db 6 dup(90h)
 * 00061C84: 3C 01                    cmp     al, 1
 * 00061C86: 75 14                    jnz     short loc_61C9C
 * 00061C88: C6 06 30                 mov     byte ptr [esi], 30h ; '0'
 * 00061C8B: 46                       inc     esi
 * 00061C8C: 89 D9                    mov     ecx, ebx
 * 00061C8E: 89 55 F8                 mov     [ebp+var_8], edx
 * 00061C91: 89 45 FC                 mov     [ebp+var_4], eax
 * 00061C94: EB 0E                    jmp     short loc_61CA4
 * 00061C96: 90 90 90 90 90 90        db 6 dup(90h)
 * 00061C9C: 89 D9                    mov     ecx, ebx
 * 00061C9E: 89 55 F8                 mov     [ebp+var_8], edx
 * 00061CA1: 89 45 FC                 mov     [ebp+var_4], eax
 * 00061CA4: 66 89 F8                 mov     ax, di
 * 00061CA7: 66 BB 0A 00              mov     bx, 0Ah
 * 00061CAB: 2B D2                    sub     edx, edx
 * 00061CAD: 66 F7 F3                 div     bx
 * 00061CB0: 89 CB                    mov     ebx, ecx
 * 00061CB2: 8B 55 F8                 mov     edx, [ebp+var_8]
 * 00061CB5: 89 C7                    mov     edi, eax
 * 00061CB7: 8B 45 FC                 mov     eax, [ebp+var_4]
 * 00061CBA: EB 8B                    jmp     short loc_61C47
 * 00061CBC: 89 75 0C                 mov     [ebp+arg_4], esi
 * 00061CBF: 88 55 08                 mov     [ebp+arg_0], dl
 * 00061CC2: 88 5D F5                 mov     [ebp+var_B], bl
 * 00061CC5: 66 89 7D F6              mov     [ebp+var_A], di
 * 00061CC9: C6 06 00                 mov     byte ptr [esi], 0
 * 00061CCC: 5B                       pop     ebx
 * 00061CCD: 5E                       pop     esi
 * 00061CCE: 5F                       pop     edi
 * 00061CCF: 89 EC                    mov     esp, ebp
 * 00061CD1: 5D                       pop     ebp
 * 00061CD2: C3                       retn
 * ========================================================================== */
// [SRX-611] pop_rank=41/1298, sites=21, callers=19, callees=0, size=0xC7, leaf
int __usercall util_61C0C@<eax>(unsigned int a1@<edx>, int a2@<ebx>, char a3, _WORD *a4)
{
  int result; // eax
  unsigned __int16 v5; // di
  _BYTE *v6; // esi
  int v7; // ecx
  unsigned int v8; // [esp+14h] [ebp-8h]
  int v9; // [esp+18h] [ebp-4h]

  result = 0;
  LOBYTE(a1) = a3;
  v5 = 100;
  v6 = a4;
  if ( a3 )
  {
    LOBYTE(a2) = 0;
    while ( v5 )
    {
      v7 = (unsigned __int8)a1;
      if ( (unsigned __int8)a1 < v5 )
      {
        if ( (_BYTE)result == 1 )
          *v6++ = 48;
        v7 = a2;
        v8 = a1;
        v9 = result;
      }
      else
      {
        *v6++ = (unsigned __int8)a1 / (int)v5 + 48;
        LOBYTE(v7) = 1;
        v9 = 1;
        v8 = (unsigned __int8)a1 % v5;
      }
      a2 = v7;
      a1 = v8;
      v5 /= 0xAu;
      result = v9;
    }
    *v6 = 0;
  }
  else
  {
    *a4 = -140;
  }
  return result;
}


/* ============================================================================
 * util_33420  @ 0x33420   size=0x2E   pop_rank=42/1298
 * calls=21 callers=19
 * note: [SRX-611] pop_rank=42/1298, sites=21, callers=19, callees=0, size=0x2E, leaf
 * --- original assembly (address: bytes  mnemonic) ---------------------------
 * 00033420: 55                       push    ebp
 * 00033421: 89 E5                    mov     ebp, esp
 * 00033423: 83 EC 04                 sub     esp, 4
 * 00033426: 8B 45 08                 mov     eax, [ebp+arg_0]
 * 00033429: 2B C9                    sub     ecx, ecx
 * 0003342B: 66 89 08                 mov     [eax], cx
 * 0003342E: 66 89 48 02              mov     [eax+2], cx
 * 00033432: 66 89 48 04              mov     [eax+4], cx
 * 00033436: 66 89 48 06              mov     [eax+6], cx
 * 0003343A: 66 89 48 08              mov     [eax+8], cx
 * 0003343E: 66 89 48 0A              mov     [eax+0Ah], cx
 * 00033442: 66 89 48 0C              mov     [eax+0Ch], cx
 * 00033446: 66 89 48 0E              mov     [eax+0Eh], cx
 * 0003344A: 89 EC                    mov     esp, ebp
 * 0003344C: 5D                       pop     ebp
 * 0003344D: C3                       retn
 * ========================================================================== */
// [SRX-611] pop_rank=42/1298, sites=21, callers=19, callees=0, size=0x2E, leaf
_WORD *__cdecl util_33420(_WORD *a1)
{
  _WORD *result; // eax

  result = a1;
  *a1 = 0;
  a1[1] = 0;
  a1[2] = 0;
  a1[3] = 0;
  a1[4] = 0;
  a1[5] = 0;
  a1[6] = 0;
  a1[7] = 0;
  return result;
}


/* ============================================================================
 * util_C4ED4  @ 0xC4ED4   size=0x74   pop_rank=47/1298
 * calls=20 callers=14
 * note: [SRX-611] pop_rank=47/1298, sites=20, callers=14, callees=0, size=0x74, leaf
 * --- original assembly (address: bytes  mnemonic) ---------------------------
 * 000C4ED4: 55                       push    ebp
 * 000C4ED5: 89 E5                    mov     ebp, esp
 * 000C4ED7: 83 EC 04                 sub     esp, 4
 * 000C4EDA: 8B 4D 08                 mov     ecx, [ebp+arg_0]
 * 000C4EDD: 8A 01                    mov     al, [ecx]
 * 000C4EDF: 24 7F                    and     al, 7Fh
 * 000C4EE1: 3C 10                    cmp     al, 10h
 * 000C4EE3: 74 1F                    jz      short loc_C4F04
 * 000C4EE5: EB 4D                    jmp     short loc_C4F34
 * 000C4EE7: 90 90 90 90 90           db 5 dup(90h)
 * 000C4EEC: 33 C0                    xor     eax, eax
 * 000C4EEE: 8A 41 01                 mov     al, [ecx+1]
 * 000C4EF1: 66 8B 0C 45 C8 66 00 00  mov     cx, word ptr ds:loc_66C7+1[eax*2]
 * 000C4EF9: 8B 45 0C                 mov     eax, [ebp+arg_4]
 * 000C4EFC: 66 89 08                 mov     [eax], cx
 * 000C4EFF: 2B C0                    sub     eax, eax
 * 000C4F01: EB 41                    jmp     short loc_C4F44
 * 000C4F03: 90                       align 4
 * 000C4F04: 33 C0                    xor     eax, eax
 * 000C4F06: 8A 41 01                 mov     al, [ecx+1]
 * 000C4F09: 8B 4D 0C                 mov     ecx, [ebp+arg_4]
 * 000C4F0C: 66 8B 04 45 C8 64 00 00  mov     ax, word ptr ds:loc_64C7+1[eax*2]
 * 000C4F14: 66 89 01                 mov     [ecx], ax
 * 000C4F17: 2B C0                    sub     eax, eax
 * 000C4F19: EB 29                    jmp     short loc_C4F44
 * 000C4F1B: 90                       align 4
 * 000C4F1C: 66 8B 41 01              mov     ax, [ecx+1]
 * 000C4F20: 8B 4D 0C                 mov     ecx, [ebp+arg_4]
 * 000C4F23: 66 89 01                 mov     [ecx], ax
 * 000C4F26: 2B C0                    sub     eax, eax
 * 000C4F28: EB 1A                    jmp     short loc_C4F44
 * 000C4F2A: 90 90                    align 4
 * 000C4F2C: 66 B8 C8 00              mov     ax, 0C8h
 * 000C4F30: EB 12                    jmp     short loc_C4F44
 * 000C4F32: 90 90                    align 4
 * 000C4F34: 3C 11                    cmp     al, 11h
 * 000C4F36: 74 B4                    jz      short loc_C4EEC
 * 000C4F38: 3C 20                    cmp     al, 20h ; ' '
 * 000C4F3A: 74 E0                    jz      short loc_C4F1C
 * 000C4F3C: 3C 21                    cmp     al, 21h ; '!'
 * 000C4F3E: 74 DC                    jz      short loc_C4F1C
 * 000C4F40: EB EA                    jmp     short loc_C4F2C
 * 000C4F42: 90 90                    align 4
 * 000C4F44: 89 EC                    mov     esp, ebp
 * 000C4F46: 5D                       pop     ebp
 * 000C4F47: C3                       retn
 * ========================================================================== */
// [SRX-611] pop_rank=47/1298, sites=20, callers=14, callees=0, size=0x74, leaf
__int16 __cdecl util_C4ED4(_BYTE *a1, _WORD *a2)
{
  char v2; // al

  v2 = *a1 & 0x7F;
  switch ( v2 )
  {
    case 16:
      *a2 = *(_WORD *)((char *)&loc_64C7 + 2 * (unsigned __int8)a1[1] + 1);
      return 0;
    case 17:
      *a2 = *(_WORD *)((char *)&loc_66C7 + 2 * (unsigned __int8)a1[1] + 1);
      return 0;
    case 32:
    case 33:
      *a2 = *(_WORD *)(a1 + 1);
      return 0;
    default:
      return 200;
  }
}


/* ============================================================================
 * util_C877C  @ 0xC877C   size=0x55   pop_rank=50/1298
 * calls=19 callers=11
 * note: [SRX-611] pop_rank=50/1298, sites=19, callers=11, callees=0, size=0x55, leaf
 * --- original assembly (address: bytes  mnemonic) ---------------------------
 * 000C877C: 55                       push    ebp
 * 000C877D: 89 E5                    mov     ebp, esp
 * 000C877F: 83 EC 08                 sub     esp, 8
 * 000C8782: 66 C7 45 FA 00 00        mov     [ebp+var_6], 0
 * 000C8788: 2B C0                    sub     eax, eax
 * 000C878A: 56                       push    esi
 * 000C878B: 8B 75 08                 mov     esi, [ebp+arg_0]
 * 000C878E: 8A 0E                    mov     cl, [esi]
 * 000C8790: 8D 50 01                 lea     edx, [eax+1]
 * 000C8793: 22 C9                    and     cl, cl
 * 000C8795: 74 05                    jz      short loc_C879C
 * 000C8797: 46                       inc     esi
 * 000C8798: 89 D0                    mov     eax, edx
 * 000C879A: EB F2                    jmp     short loc_C878E
 * 000C879C: 89 75 08                 mov     [ebp+arg_0], esi
 * 000C879F: 66 89 45 FA              mov     [ebp+var_6], ax
 * 000C87A3: 66 89 55 FA              mov     [ebp+var_6], dx
 * 000C87A7: 33 C0                    xor     eax, eax
 * 000C87A9: 8A 45 0C                 mov     al, [ebp+arg_4]
 * 000C87AC: 03 C6                    add     eax, esi
 * 000C87AE: 89 45 FC                 mov     [ebp+var_4], eax
 * 000C87B1: EB 03                    jmp     short loc_C87B6
 * 000C87B3: 90                       align 4
 * 000C87B4: 8A 0E                    mov     cl, [esi]
 * 000C87B6: 88 08                    mov     [eax], cl
 * 000C87B8: 4E                       dec     esi
 * 000C87B9: 48                       dec     eax
 * 000C87BA: 66 23 D2                 and     dx, dx
 * 000C87BD: 8D 52 FF                 lea     edx, [edx-1]
 * 000C87C0: 75 F2                    jnz     short loc_C87B4
 * 000C87C2: 89 75 08                 mov     [ebp+arg_0], esi
 * 000C87C5: 66 89 55 FA              mov     [ebp+var_6], dx
 * 000C87C9: 89 45 FC                 mov     [ebp+var_4], eax
 * 000C87CC: 5E                       pop     esi
 * 000C87CD: 89 EC                    mov     esp, ebp
 * 000C87CF: 5D                       pop     ebp
 * 000C87D0: C3                       retn
 * ========================================================================== */
// [SRX-611] pop_rank=50/1298, sites=19, callers=11, callees=0, size=0x55, leaf
char *__cdecl util_C877C(char *a1, unsigned __int8 a2)
{
  int i; // eax
  char v4; // cl
  int v5; // edx
  char *result; // eax

  for ( i = 0; ; ++i )
  {
    v4 = *a1;
    v5 = i + 1;
    if ( !*a1 )
      break;
    ++a1;
  }
  result = &a1[a2];
  while ( 1 )
  {
    *result = v4;
    --a1;
    --result;
    if ( (_WORD)v5-- == 0 )
      break;
    v4 = *a1;
  }
  return result;
}


