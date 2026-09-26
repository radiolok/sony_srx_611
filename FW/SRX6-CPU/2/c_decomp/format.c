/*
 * Sony SRX-611 firmware - C equivalents (Hex-Rays) - prefix 'format'
 * Source image: ROM1-C.bin (80486 real mode, OS+/386 V2.0)
 * Generated from IDA database ROM1-C.bin.i64
 * Functions in this file: 2
 */

/* ============================================================================
 * format_dispatch  @ 0xC8854   size=0x134   pop_rank=6/1298
 * calls=116 callers=10
 * note: Dispatch/format by type selector (arg0): branches to C898C/C8B24/C8C9C/C8D54/... passing 4 args | [SRX-611] pop_rank=6/1298, sites=116, callers=10, callees=6, size=0x134
 * --- original assembly (address: bytes  mnemonic) ---------------------------
 * 000C8854: 55                       push    ebp
 * 000C8855: 89 E5                    mov     ebp, esp
 * 000C8857: 83 EC 14                 sub     esp, 14h
 * 000C885A: 8A 45 08                 mov     al, [ebp+arg_0]
 * 000C885D: 22 C0                    and     al, al
 * 000C885F: 0F 84 CF 00 00 00        jz      loc_C8934
 * 000C8865: E9 F2 00 00 00           jmp     loc_C895C
 * 000C886A: 90 90                    align 4
 * 000C886C: 8B 45 0C                 mov     eax, [ebp+arg_4]
 * 000C886F: 89 04 24                 mov     [esp+14h+var_14], eax
 * 000C8872: 8B 45 10                 mov     eax, [ebp+arg_8]
 * 000C8875: 89 44 24 04              mov     [esp+14h+var_10], eax
 * 000C8879: 8B 45 14                 mov     eax, [ebp+arg_C]
 * 000C887C: 89 44 24 08              mov     [esp+14h+var_C], eax
 * 000C8880: 8B 45 18                 mov     eax, [ebp+arg_10]
 * 000C8883: 89 44 24 0C              mov     [esp+14h+var_8], eax
 * 000C8887: E8 00 01 00 00           call    os_C898C
 * 000C888C: E9 F3 00 00 00           jmp     loc_C8984
 * 000C8891: 90 90 90                 align 4
 * 000C8894: 8B 45 0C                 mov     eax, [ebp+arg_4]
 * 000C8897: 89 04 24                 mov     [esp+14h+var_14], eax
 * 000C889A: 8B 45 10                 mov     eax, [ebp+arg_8]
 * 000C889D: 89 44 24 04              mov     [esp+14h+var_10], eax
 * 000C88A1: 8B 45 14                 mov     eax, [ebp+arg_C]
 * 000C88A4: 89 44 24 08              mov     [esp+14h+var_C], eax
 * 000C88A8: 8B 45 18                 mov     eax, [ebp+arg_10]
 * 000C88AB: 89 44 24 0C              mov     [esp+14h+var_8], eax
 * 000C88AF: E8 70 02 00 00           call    os_C8B24
 * 000C88B4: E9 CB 00 00 00           jmp     loc_C8984
 * 000C88B9: 90 90 90                 align 4
 * 000C88BC: 8B 45 0C                 mov     eax, [ebp+arg_4]
 * 000C88BF: 89 04 24                 mov     [esp+14h+var_14], eax
 * 000C88C2: 8B 45 10                 mov     eax, [ebp+arg_8]
 * 000C88C5: 89 44 24 04              mov     [esp+14h+var_10], eax
 * 000C88C9: 8B 45 14                 mov     eax, [ebp+arg_C]
 * 000C88CC: 89 44 24 08              mov     [esp+14h+var_C], eax
 * 000C88D0: 8B 45 18                 mov     eax, [ebp+arg_10]
 * 000C88D3: 89 44 24 0C              mov     [esp+14h+var_8], eax
 * 000C88D7: E8 C0 03 00 00           call    os_C8C9C
 * 000C88DC: E9 A3 00 00 00           jmp     loc_C8984
 * 000C88E1: 90 90 90                 align 4
 * 000C88E4: 8B 45 0C                 mov     eax, [ebp+arg_4]
 * 000C88E7: 89 04 24                 mov     [esp+14h+var_14], eax
 * 000C88EA: 8B 45 10                 mov     eax, [ebp+arg_8]
 * 000C88ED: 89 44 24 04              mov     [esp+14h+var_10], eax
 * 000C88F1: 8B 45 14                 mov     eax, [ebp+arg_C]
 * 000C88F4: 89 44 24 08              mov     [esp+14h+var_C], eax
 * 000C88F8: 8B 45 18                 mov     eax, [ebp+arg_10]
 * 000C88FB: 89 44 24 0C              mov     [esp+14h+var_8], eax
 * 000C88FF: E8 50 04 00 00           call    os_C8D54
 * 000C8904: E9 7B 00 00 00           jmp     loc_C8984
 * 000C8909: 90 90 90                 align 4
 * 000C890C: 8B 45 0C                 mov     eax, [ebp+arg_4]
 * 000C890F: 89 04 24                 mov     [esp+14h+var_14], eax
 * 000C8912: 8B 45 10                 mov     eax, [ebp+arg_8]
 * 000C8915: 89 44 24 04              mov     [esp+14h+var_10], eax
 * 000C8919: 8B 45 14                 mov     eax, [ebp+arg_C]
 * 000C891C: 89 44 24 08              mov     [esp+14h+var_C], eax
 * 000C8920: 8B 45 18                 mov     eax, [ebp+arg_10]
 * 000C8923: 89 44 24 0C              mov     [esp+14h+var_8], eax
 * 000C8927: E8 E0 04 00 00           call    os_C8E0C
 * 000C892C: EB 56                    jmp     short loc_C8984
 * 000C892E: 90 90 90 90 90 90        db 6 dup(90h)
 * 000C8934: 8B 45 0C                 mov     eax, [ebp+arg_4]
 * 000C8937: 89 04 24                 mov     [esp+14h+var_14], eax
 * 000C893A: 8B 45 10                 mov     eax, [ebp+arg_8]
 * 000C893D: 89 44 24 04              mov     [esp+14h+var_10], eax
 * 000C8941: 8B 45 14                 mov     eax, [ebp+arg_C]
 * 000C8944: 89 44 24 08              mov     [esp+14h+var_C], eax
 * 000C8948: 8B 45 18                 mov     eax, [ebp+arg_10]
 * 000C894B: 89 44 24 0C              mov     [esp+14h+var_8], eax
 * 000C894F: E8 A8 05 00 00           call    os_C8EFC
 * 000C8954: EB 2E                    jmp     short loc_C8984
 * 000C8956: 90 90 90 90 90 90        db 6 dup(90h)
 * 000C895C: 3C 07                    cmp     al, 7
 * 000C895E: 0F 84 08 FF FF FF        jz      loc_C886C
 * 000C8964: 3C 0D                    cmp     al, 0Dh
 * 000C8966: 0F 84 28 FF FF FF        jz      loc_C8894
 * 000C896C: 3C 18                    cmp     al, 18h
 * 000C896E: 0F 84 48 FF FF FF        jz      loc_C88BC
 * 000C8974: 3C 19                    cmp     al, 19h
 * 000C8976: 0F 84 68 FF FF FF        jz      loc_C88E4
 * 000C897C: 3C 24                    cmp     al, 24h ; '$'
 * 000C897E: 74 8C                    jz      short loc_C890C
 * 000C8980: 66 B8 29 50              mov     ax, 5029h
 * 000C8984: 89 EC                    mov     esp, ebp
 * 000C8986: 5D                       pop     ebp
 * 000C8987: C3                       retn
 * ========================================================================== */
// Dispatch/format by type selector (arg0): branches to C898C/C8B24/C8C9C/C8D54/... passing 4 args | [SRX-611] pop_rank=6/1298, sites=116, callers=10, callees=6, size=0x134
__int16 __cdecl format_dispatch(char a1, int a2, int a3, int a4, int a5)
{
  switch ( a1 )
  {
    case 0:
      return os_C8EFC(a2, a3, a4);
    case 7:
      return os_C898C(a2, a3, a4, a5);
    case 13:
      return os_C8B24(a2, a3, a4, a5);
    case 24:
      return os_C8C9C(a2, a3, a4, a5);
    case 25:
      return os_C8D54(a2, a3, a4, a5);
    case 36:
      return os_C8E0C(a2, a3, a4, a5);
  }
  return 20521;
}


/* ============================================================================
 * format_real  @ 0x72994   size=0x179   pop_rank=17/1298
 * calls=36 callers=13
 * note: FPU float-to-string formatting (decimal point, range checks) | [SRX-611] pop_rank=17/1298, sites=36, callers=13, callees=1, size=0x179
 * --- original assembly (address: bytes  mnemonic) ---------------------------
 * 00072994: 55                       push    ebp
 * 00072995: 89 E5                    mov     ebp, esp
 * 00072997: 83 EC 20                 sub     esp, 20h
 * 0007299A: 66 C7 45 EE 00 00        mov     [ebp+var_12], 0
 * 000729A0: 66 C7 45 E4 01 00        mov     [ebp+var_1C], 1
 * 000729A6: 57                       push    edi
 * 000729A7: 56                       push    esi
 * 000729A8: 53                       push    ebx
 * 000729A9: 66 BB 01 00              mov     bx, 1
 * 000729AD: 66 C7 45 E6 00 00        mov     [ebp+var_1A], 0
 * 000729B3: 8B 4D 10                 mov     ecx, [ebp+arg_8]
 * 000729B6: 2B C0                    sub     eax, eax
 * 000729B8: 66 83 F8 07              cmp     ax, 7
 * 000729BC: 77 0E                    ja      short loc_729CC
 * 000729BE: 25 FF FF 00 00           and     eax, 0FFFFh
 * 000729C3: C6 04 01 20              mov     byte ptr [ecx+eax], 20h ; ' '
 * 000729C7: 40                       inc     eax
 * 000729C8: EB EE                    jmp     short loc_729B8
 * 000729CA: 90 90                    align 4
 * 000729CC: 66 89 45 E6              mov     [ebp+var_1A], ax
 * 000729D0: C6 41 08 00              mov     byte ptr [ecx+8], 0
 * 000729D4: C6 41 04 2E              mov     byte ptr [ecx+4], 2Eh ; '.'
 * 000729D8: DD 45 08                 fld     [ebp+arg_0]
 * 000729DB: DC 15 6C 29 E7 FF        fcom    qword ptr ds:0FFE7296Ch
 * 000729E1: DF E0                    fnstsw  ax
 * 000729E3: 9E                       sahf
 * 000729E4: 73 0E                    jnb     short loc_729F4
 * 000729E6: DC 15 74 29 E7 FF        fcom    qword ptr ds:0FFE72974h
 * 000729EC: DF E0                    fnstsw  ax
 * 000729EE: 9E                       sahf
 * 000729EF: 77 1B                    ja      short loc_72A0C
 * 000729F1: EB 09                    jmp     short loc_729FC
 * 000729F3: 90                       align 4
 * 000729F4: DD D8                    fstp    st
 * 000729F6: EB 06                    jmp     short loc_729FE
 * 000729F8: 90 90 90 90              db 4 dup(90h)
 * 000729FC: DD D8                    fstp    st
 * 000729FE: 66 B8 0F 0A              mov     ax, 0A0Fh
 * 00072A02: E9 FF 00 00 00           jmp     loc_72B06
 * 00072A07: 90 90 90 90 90           db 5 dup(90h)
 * 00072A0C: D9 E4                    ftst
 * 00072A0E: DF E0                    fnstsw  ax
 * 00072A10: 9E                       sahf
 * 00072A11: 75 19                    jnz     short loc_72A2C
 * 00072A13: DD D8                    fstp    st
 * 00072A15: C6 41 03 30              mov     byte ptr [ecx+3], 30h ; '0'
 * 00072A19: C6 41 05 30              mov     byte ptr [ecx+5], 30h ; '0'
 * 00072A1D: C6 41 06 30              mov     byte ptr [ecx+6], 30h ; '0'
 * 00072A21: 2B C0                    sub     eax, eax
 * 00072A23: C6 41 07 30              mov     byte ptr [ecx+7], 30h ; '0'
 * 00072A27: E9 DA 00 00 00           jmp     loc_72B06
 * 00072A2C: D9 E4                    ftst
 * 00072A2E: DF E0                    fnstsw  ax
 * 00072A30: 9E                       sahf
 * 00072A31: 73 13                    jnb     short loc_72A46
 * 00072A33: DC 0D 7C 29 E7 FF        fmul    qword ptr ds:0FFE7297Ch
 * 00072A39: 66 C7 45 E4 FF FF        mov     [ebp+var_1C], 0FFFFh
 * 00072A3F: 66 BB FF FF              mov     bx, 0FFFFh
 * 00072A43: DD 55 08                 fst     [ebp+arg_0]
 * 00072A46: DC 0D 84 29 E7 FF        fmul    qword ptr ds:0FFE72984h
 * 00072A4C: DC 05 8C 29 E7 FF        fadd    qword ptr ds:0FFE7298Ch
 * 00072A52: E8 7D B3 05 00           call    fpu_ftoi
 * 00072A57: 89 45 E8                 mov     [ebp+var_18], eax
 * 00072A5A: 99                       cdq
 * 00072A5B: BE 0A 00 00 00           mov     esi, 0Ah
 * 00072A60: F7 FE                    idiv    esi
 * 00072A62: 80 C2 30                 add     dl, 30h ; '0'
 * 00072A65: 88 51 07                 mov     [ecx+7], dl
 * 00072A68: 89 45 E8                 mov     [ebp+var_18], eax
 * 00072A6B: 99                       cdq
 * 00072A6C: F7 FE                    idiv    esi
 * 00072A6E: 80 C2 30                 add     dl, 30h ; '0'
 * 00072A71: 88 51 06                 mov     [ecx+6], dl
 * 00072A74: 89 45 E8                 mov     [ebp+var_18], eax
 * 00072A77: 99                       cdq
 * 00072A78: F7 FE                    idiv    esi
 * 00072A7A: 80 C2 30                 add     dl, 30h ; '0'
 * 00072A7D: 89 C7                    mov     edi, eax
 * 00072A7F: 88 51 05                 mov     [ecx+5], dl
 * 00072A82: 89 F8                    mov     eax, edi
 * 00072A84: 99                       cdq
 * 00072A85: 89 7D E8                 mov     [ebp+var_18], edi
 * 00072A88: F7 FE                    idiv    esi
 * 00072A8A: 80 C2 30                 add     dl, 30h ; '0'
 * 00072A8D: 23 FF                    and     edi, edi
 * 00072A8F: 88 51 03                 mov     [ecx+3], dl
 * 00072A92: 75 10                    jnz     short loc_72AA4
 * 00072A94: 22 DB                    and     bl, bl
 * 00072A96: 7D 04                    jge     short loc_72A9C
 * 00072A98: C6 41 02 2D              mov     byte ptr [ecx+2], 2Dh ; '-'
 * 00072A9C: 2B C0                    sub     eax, eax
 * 00072A9E: EB 66                    jmp     short loc_72B06
 * 00072AA0: 90 90 90 90              db 4 dup(90h)
 * 00072AA4: 89 45 E8                 mov     [ebp+var_18], eax
 * 00072AA7: 23 C0                    and     eax, eax
 * 00072AA9: 75 11                    jnz     short loc_72ABC
 * 00072AAB: 22 DB                    and     bl, bl
 * 00072AAD: 7D 04                    jge     short loc_72AB3
 * 00072AAF: C6 41 02 2D              mov     byte ptr [ecx+2], 2Dh ; '-'
 * 00072AB3: 2B C0                    sub     eax, eax
 * 00072AB5: EB 4F                    jmp     short loc_72B06
 * 00072AB7: 90 90 90 90 90           db 5 dup(90h)
 * 00072ABC: 99                       cdq
 * 00072ABD: F7 FE                    idiv    esi
 * 00072ABF: 80 C2 30                 add     dl, 30h ; '0'
 * 00072AC2: 88 51 02                 mov     [ecx+2], dl
 * 00072AC5: 89 45 E8                 mov     [ebp+var_18], eax
 * 00072AC8: 23 C0                    and     eax, eax
 * 00072ACA: 75 10                    jnz     short loc_72ADC
 * 00072ACC: 22 DB                    and     bl, bl
 * 00072ACE: 7D 04                    jge     short loc_72AD4
 * 00072AD0: C6 41 01 2D              mov     byte ptr [ecx+1], 2Dh ; '-'
 * 00072AD4: 2B C0                    sub     eax, eax
 * 00072AD6: EB 2E                    jmp     short loc_72B06
 * 00072AD8: 90 90 90 90              db 4 dup(90h)
 * 00072ADC: 99                       cdq
 * 00072ADD: F7 FE                    idiv    esi
 * 00072ADF: 80 C2 30                 add     dl, 30h ; '0'
 * 00072AE2: 88 51 01                 mov     [ecx+1], dl
 * 00072AE5: 89 45 E8                 mov     [ebp+var_18], eax
 * 00072AE8: 23 C0                    and     eax, eax
 * 00072AEA: 75 10                    jnz     short loc_72AFC
 * 00072AEC: 22 DB                    and     bl, bl
 * 00072AEE: 7D 03                    jge     short loc_72AF3
 * 00072AF0: C6 01 2D                 mov     byte ptr [ecx], 2Dh ; '-'
 * 00072AF3: 2B C0                    sub     eax, eax
 * 00072AF5: EB 0F                    jmp     short loc_72B06
 * 00072AF7: 90 90 90 90 90           db 5 dup(90h)
 * 00072AFC: 99                       cdq
 * 00072AFD: F7 FE                    idiv    esi
 * 00072AFF: 80 C2 30                 add     dl, 30h ; '0'
 * 00072B02: 88 11                    mov     [ecx], dl
 * 00072B04: 2B C0                    sub     eax, eax
 * 00072B06: 5B                       pop     ebx
 * 00072B07: 5E                       pop     esi
 * 00072B08: 5F                       pop     edi
 * 00072B09: 89 EC                    mov     esp, ebp
 * 00072B0B: 5D                       pop     ebp
 * 00072B0C: C3                       retn
 * ========================================================================== */
// FPU float-to-string formatting (decimal point, range checks) | [SRX-611] pop_rank=17/1298, sites=36, callers=13, callees=1, size=0x179
__int16 __cdecl format_real(double a1, _BYTE *a2)
{
  char v2; // bl
  unsigned __int16 i; // ax
  long double v4; // fst7
  __int16 result; // ax
  long double v6; // fst7
  int v7; // eax
  _BYTE *v8; // ecx
  int v9; // edi
  int v10; // eax
  int v11; // eax
  int v12; // et2
  int v13; // eax
  int v14; // et2

  v2 = 1;
  for ( i = 0; i <= 7u; ++i )
    a2[i] = 32;
  a2[8] = 0;
  a2[4] = 46;
  v4 = a1;
  if ( a1 >= (long double)MEMORY[0xFFE7296C] || v4 <= MEMORY[0xFFE72974] )
    return 2575;
  if ( v4 == 0.0 )
  {
    a2[3] = 48;
    a2[5] = 48;
    a2[6] = 48;
    result = 0;
    a2[7] = 48;
  }
  else
  {
    if ( v4 < 0.0 )
    {
      v4 = v4 * MEMORY[0xFFE7297C];
      v2 = -1;
    }
    v6 = v4 * MEMORY[0xFFE72984] + MEMORY[0xFFE7298C];
    v7 = fpu_ftoi(*(double *)&v6);
    v8[7] = v7 % 10 + 48;
    v8[6] = v7 / 10 % 10 + 48;
    v9 = v7 / 10 / 10 / 10;
    v8[5] = v7 / 10 / 10 % 10 + 48;
    v10 = v9 / 10;
    v8[3] = v9 % 10 + 48;
    if ( v9 )
    {
      if ( v10 )
      {
        v12 = v10 % 10;
        v11 = v10 / 10;
        v8[2] = v12 + 48;
        if ( v11 )
        {
          v14 = v11 % 10;
          v13 = v11 / 10;
          v8[1] = v14 + 48;
          if ( v13 )
          {
            *v8 = v13 % 10 + 48;
            return 0;
          }
          else
          {
            if ( v2 < 0 )
              *v8 = 45;
            return 0;
          }
        }
        else
        {
          if ( v2 < 0 )
            v8[1] = 45;
          return 0;
        }
      }
      else
      {
        if ( v2 < 0 )
          v8[2] = 45;
        return 0;
      }
    }
    else
    {
      if ( v2 < 0 )
        v8[2] = 45;
      return 0;
    }
  }
  return result;
}


