/*
 * Sony SRX-611 firmware - LUNA object-code interpreter/decoder - prefix 'util'
 * Source: ROM1-C.bin (80486 real mode, OS+/386 V2.0)
 * Functions: 33. The LUNA language compiles robot programs to object code;
 * this cluster decodes opcodes/tokens and formats operands.
 */

/* ============================================================================
 * util_61DBC  @ 0x61DBC   size=0x92   callers=16
 * note: [SRX-611] pop_rank=63/1298, sites=16, callers=8, callees=0, size=0x92, leaf
 * --- original assembly (address: bytes  mnemonic) ---------------------------
 * 00061DBC: 55                       push    ebp
 * 00061DBD: 89 E5                    mov     ebp, esp
 * 00061DBF: 83 EC 08                 sub     esp, 8
 * 00061DC2: C6 45 F9 03              mov     [ebp+var_7], 3
 * 00061DC6: 8A 45 F9                 mov     al, [ebp+var_7]
 * 00061DC9: 57                       push    edi
 * 00061DCA: 56                       push    esi
 * 00061DCB: 53                       push    ebx
 * 00061DCC: 66 C7 45 FA 64 00        mov     [ebp+var_6], 64h ; 'd'
 * 00061DD2: 8B 4D 10                 mov     ecx, [ebp+arg_8]
 * 00061DD5: 8A 5D 08                 mov     bl, [ebp+arg_0]
 * 00061DD8: 66 BF 64 00              mov     di, 64h ; 'd'
 * 00061DDC: 89 45 FC                 mov     [ebp+var_4], eax
 * 00061DDF: 66 83 FF 01              cmp     di, 1
 * 00061DE3: 72 4F                    jb      short loc_61E34
 * 00061DE5: 89 DE                    mov     esi, ebx
 * 00061DE7: 66 81 E6 FF 00           and     si, 0FFh
 * 00061DEC: 8A 45 0C                 mov     al, [ebp+arg_4]
 * 00061DEF: 3A 45 FC                 cmp     al, byte ptr [ebp+var_4]
 * 00061DF2: 72 1C                    jb      short loc_61E10
 * 00061DF4: 66 3B F7                 cmp     si, di
 * 00061DF7: 72 13                    jb      short loc_61E0C
 * 00061DF9: 33 C0                    xor     eax, eax
 * 00061DFB: 88 D8                    mov     al, bl
 * 00061DFD: 99                       cdq
 * 00061DFE: 81 E7 FF FF 00 00        and     edi, 0FFFFh
 * 00061E04: F7 FF                    idiv    edi
 * 00061E06: 04 30                    add     al, 30h ; '0'
 * 00061E08: 88 01                    mov     [ecx], al
 * 00061E0A: EB 03                    jmp     short loc_61E0F
 * 00061E0C: C6 01 30                 mov     byte ptr [ecx], 30h ; '0'
 * 00061E0F: 41                       inc     ecx
 * 00061E10: 66 89 F0                 mov     ax, si
 * 00061E13: 2B D2                    sub     edx, edx
 * 00061E15: 66 F7 F7                 div     di
 * 00061E18: 66 89 F8                 mov     ax, di
 * 00061E1B: 66 BE 0A 00              mov     si, 0Ah
 * 00061E1F: 89 D3                    mov     ebx, edx
 * 00061E21: 2B D2                    sub     edx, edx
 * 00061E23: 66 F7 F6                 div     si
 * 00061E26: FE 4D FC                 dec     byte ptr [ebp+var_4]
 * 00061E29: 89 C7                    mov     edi, eax
 * 00061E2B: EB B2                    jmp     short loc_61DDF
 * 00061E2D: 90 90 90 90 90 90 90     db 7 dup(90h)
 * 00061E34: 88 5D 08                 mov     [ebp+arg_0], bl
 * 00061E37: 5B                       pop     ebx
 * 00061E38: 66 89 7D FA              mov     [ebp+var_6], di
 * 00061E3C: 5E                       pop     esi
 * 00061E3D: 8B 45 FC                 mov     eax, [ebp+var_4]
 * 00061E40: 5F                       pop     edi
 * 00061E41: 89 4D 10                 mov     [ebp+arg_8], ecx
 * 00061E44: 88 45 F9                 mov     [ebp+var_7], al
 * 00061E47: C6 01 00                 mov     byte ptr [ecx], 0
 * 00061E4A: 89 EC                    mov     esp, ebp
 * 00061E4C: 5D                       pop     ebp
 * 00061E4D: C3                       retn
 * ========================================================================== */
// [SRX-611] pop_rank=63/1298, sites=16, callers=8, callees=0, size=0x92, leaf
int __usercall util_61DBC@<eax>(int a1@<eax>, char a2, unsigned __int8 a3, _BYTE *a4)
{
  __int16 v5; // bx
  unsigned __int16 v6; // di
  int result; // eax
  int v8; // [esp+10h] [ebp-4h]

  LOBYTE(a1) = 3;
  LOBYTE(v5) = a2;
  v6 = 100;
  v8 = a1;
  while ( v6 )
  {
    if ( a3 >= (unsigned __int8)v8 )
    {
      if ( (unsigned __int8)v5 < v6 )
        *a4 = 48;
      else
        *a4 = (unsigned __int8)v5 / (int)v6 + 48;
      ++a4;
    }
    v5 = (unsigned __int8)v5 % v6;
    LOBYTE(v8) = v8 - 1;
    v6 /= 0xAu;
  }
  result = v8;
  *a4 = 0;
  return result;
}


/* ============================================================================
 * util_C5F6C  @ 0xC5F6C   size=0xA2   callers=2
 * note: [SRX-611] pop_rank=351/1298, sites=2, callers=2, callees=1, size=0xA2
 * --- original assembly (address: bytes  mnemonic) ---------------------------
 * 000C5F6C: 55                       push    ebp
 * 000C5F6D: 89 E5                    mov     ebp, esp
 * 000C5F6F: 83 EC 04                 sub     esp, 4
 * 000C5F72: 57                       push    edi
 * 000C5F73: 56                       push    esi
 * 000C5F74: 8B 75 0C                 mov     esi, [ebp+arg_4]
 * 000C5F77: 53                       push    ebx
 * 000C5F78: C6 06 52                 mov     byte ptr [esi], 52h ; 'R'
 * 000C5F7B: 83 EC 0C                 sub     esp, 0Ch
 * 000C5F7E: 8B 5D 08                 mov     ebx, [ebp+arg_0]
 * 000C5F81: 8D 4E 01                 lea     ecx, [esi+1]
 * 000C5F84: 8A 43 01                 mov     al, [ebx+1]
 * 000C5F87: 3C 63                    cmp     al, 63h ; 'c'
 * 000C5F89: 8B 7D 10                 mov     edi, [ebp+arg_8]
 * 000C5F8C: 77 3E                    ja      short loc_C5FCC
 * 000C5F8E: 89 04 24                 mov     [esp+1Ch+var_1C], eax
 * 000C5F91: C7 44 24 04 02 00 00 00  mov     [esp+1Ch+var_18], 2
 * 000C5F99: 89 4C 24 08              mov     [esp+1Ch+var_14], ecx
 * 000C5F9D: E8 1A BE F9 FF           call    util_61DBC
 * 000C5FA2: 8A 43 02                 mov     al, [ebx+2]
 * 000C5FA5: 89 04 24                 mov     [esp+1Ch+var_1C], eax
 * 000C5FA8: C7 44 24 04 02 00 00 00  mov     [esp+1Ch+var_18], 2
 * 000C5FB0: 8D 46 03                 lea     eax, [esi+3]
 * 000C5FB3: 89 44 24 08              mov     [esp+1Ch+var_14], eax
 * 000C5FB7: E8 00 BE F9 FF           call    util_61DBC
 * 000C5FBC: C6 46 05 00              mov     byte ptr [esi+5], 0
 * 000C5FC0: C6 07 05                 mov     byte ptr [edi], 5
 * 000C5FC3: EB 3C                    jmp     short loc_C6001
 * 000C5FC5: 90 90 90 90 90 90 90     db 7 dup(90h)
 * 000C5FCC: 89 04 24                 mov     [esp+1Ch+var_1C], eax
 * 000C5FCF: C7 44 24 04 03 00 00 00  mov     [esp+1Ch+var_18], 3
 * 000C5FD7: 89 4C 24 08              mov     [esp+1Ch+var_14], ecx
 * 000C5FDB: E8 DC BD F9 FF           call    util_61DBC
 * 000C5FE0: 8A 43 02                 mov     al, [ebx+2]
 * 000C5FE3: 89 04 24                 mov     [esp+1Ch+var_1C], eax
 * 000C5FE6: C7 44 24 04 02 00 00 00  mov     [esp+1Ch+var_18], 2
 * 000C5FEE: 8D 46 04                 lea     eax, [esi+4]
 * 000C5FF1: 89 44 24 08              mov     [esp+1Ch+var_14], eax
 * 000C5FF5: E8 C2 BD F9 FF           call    util_61DBC
 * 000C5FFA: C6 46 06 00              mov     byte ptr [esi+6], 0
 * 000C5FFE: C6 07 06                 mov     byte ptr [edi], 6
 * 000C6001: 8B 5D F0                 mov     ebx, [ebp+var_10]
 * 000C6004: 8B 75 F4                 mov     esi, [ebp+var_C]
 * 000C6007: 8B 7D F8                 mov     edi, [ebp+var_8]
 * 000C600A: 89 EC                    mov     esp, ebp
 * 000C600C: 5D                       pop     ebp
 * 000C600D: C3                       retn
 * ========================================================================== */
// [SRX-611] pop_rank=351/1298, sites=2, callers=2, callees=1, size=0xA2
int __cdecl util_C5F6C(int a1, _BYTE *a2, _BYTE *a3)
{
  unsigned __int8 v3; // al
  int result; // eax

  *a2 = 82;
  v3 = *(_BYTE *)(a1 + 1);
  if ( v3 > 0x63u )
  {
    util_61DBC(v3, v3, 3u, a2 + 1);
    result = util_61DBC((_BYTE)a2 + 4, *(_BYTE *)(a1 + 2), 2u, a2 + 4);
    a2[6] = 0;
    *a3 = 6;
  }
  else
  {
    util_61DBC(v3, v3, 2u, a2 + 1);
    result = util_61DBC((_BYTE)a2 + 3, *(_BYTE *)(a1 + 2), 2u, a2 + 3);
    a2[5] = 0;
    *a3 = 5;
  }
  return result;
}


/* ============================================================================
 * util_C6014  @ 0xC6014   size=0xA2   callers=2
 * note: [SRX-611] pop_rank=352/1298, sites=2, callers=2, callees=1, size=0xA2
 * --- original assembly (address: bytes  mnemonic) ---------------------------
 * 000C6014: 55                       push    ebp
 * 000C6015: 89 E5                    mov     ebp, esp
 * 000C6017: 83 EC 04                 sub     esp, 4
 * 000C601A: 57                       push    edi
 * 000C601B: 56                       push    esi
 * 000C601C: 8B 75 0C                 mov     esi, [ebp+arg_4]
 * 000C601F: 53                       push    ebx
 * 000C6020: C6 06 4B                 mov     byte ptr [esi], 4Bh ; 'K'
 * 000C6023: 83 EC 0C                 sub     esp, 0Ch
 * 000C6026: 8B 5D 08                 mov     ebx, [ebp+arg_0]
 * 000C6029: 8D 4E 01                 lea     ecx, [esi+1]
 * 000C602C: 8A 43 01                 mov     al, [ebx+1]
 * 000C602F: 3C 63                    cmp     al, 63h ; 'c'
 * 000C6031: 8B 7D 10                 mov     edi, [ebp+arg_8]
 * 000C6034: 77 3E                    ja      short loc_C6074
 * 000C6036: 89 04 24                 mov     [esp+1Ch+var_1C], eax
 * 000C6039: C7 44 24 04 02 00 00 00  mov     [esp+1Ch+var_18], 2
 * 000C6041: 89 4C 24 08              mov     [esp+1Ch+var_14], ecx
 * 000C6045: E8 72 BD F9 FF           call    util_61DBC
 * 000C604A: 8A 43 02                 mov     al, [ebx+2]
 * 000C604D: 89 04 24                 mov     [esp+1Ch+var_1C], eax
 * 000C6050: C7 44 24 04 02 00 00 00  mov     [esp+1Ch+var_18], 2
 * 000C6058: 8D 46 03                 lea     eax, [esi+3]
 * 000C605B: 89 44 24 08              mov     [esp+1Ch+var_14], eax
 * 000C605F: E8 58 BD F9 FF           call    util_61DBC
 * 000C6064: C6 46 05 00              mov     byte ptr [esi+5], 0
 * 000C6068: C6 07 05                 mov     byte ptr [edi], 5
 * 000C606B: EB 3C                    jmp     short loc_C60A9
 * 000C606D: 90 90 90 90 90 90 90     db 7 dup(90h)
 * 000C6074: 89 04 24                 mov     [esp+1Ch+var_1C], eax
 * 000C6077: C7 44 24 04 03 00 00 00  mov     [esp+1Ch+var_18], 3
 * 000C607F: 89 4C 24 08              mov     [esp+1Ch+var_14], ecx
 * 000C6083: E8 34 BD F9 FF           call    util_61DBC
 * 000C6088: 8A 43 02                 mov     al, [ebx+2]
 * 000C608B: 89 04 24                 mov     [esp+1Ch+var_1C], eax
 * 000C608E: C7 44 24 04 02 00 00 00  mov     [esp+1Ch+var_18], 2
 * 000C6096: 8D 46 04                 lea     eax, [esi+4]
 * 000C6099: 89 44 24 08              mov     [esp+1Ch+var_14], eax
 * 000C609D: E8 1A BD F9 FF           call    util_61DBC
 * 000C60A2: C6 46 06 00              mov     byte ptr [esi+6], 0
 * 000C60A6: C6 07 06                 mov     byte ptr [edi], 6
 * 000C60A9: 8B 5D F0                 mov     ebx, [ebp+var_10]
 * 000C60AC: 8B 75 F4                 mov     esi, [ebp+var_C]
 * 000C60AF: 8B 7D F8                 mov     edi, [ebp+var_8]
 * 000C60B2: 89 EC                    mov     esp, ebp
 * 000C60B4: 5D                       pop     ebp
 * 000C60B5: C3                       retn
 * ========================================================================== */
// [SRX-611] pop_rank=352/1298, sites=2, callers=2, callees=1, size=0xA2
int __cdecl util_C6014(int a1, _BYTE *a2, _BYTE *a3)
{
  unsigned __int8 v3; // al
  int result; // eax

  *a2 = 75;
  v3 = *(_BYTE *)(a1 + 1);
  if ( v3 > 0x63u )
  {
    util_61DBC(v3, v3, 3u, a2 + 1);
    result = util_61DBC((_BYTE)a2 + 4, *(_BYTE *)(a1 + 2), 2u, a2 + 4);
    a2[6] = 0;
    *a3 = 6;
  }
  else
  {
    util_61DBC(v3, v3, 2u, a2 + 1);
    result = util_61DBC((_BYTE)a2 + 3, *(_BYTE *)(a1 + 2), 2u, a2 + 3);
    a2[5] = 0;
    *a3 = 5;
  }
  return result;
}


/* ============================================================================
 * util_C60BC  @ 0xC60BC   size=0x3E   callers=2
 * note: [SRX-611] pop_rank=437/1298, sites=2, callers=2, callees=1, size=0x3E
 * --- original assembly (address: bytes  mnemonic) ---------------------------
 * 000C60BC: 55                       push    ebp
 * 000C60BD: 89 E5                    mov     ebp, esp
 * 000C60BF: 83 EC 04                 sub     esp, 4
 * 000C60C2: 56                       push    esi
 * 000C60C3: 8B 75 0C                 mov     esi, [ebp+arg_4]
 * 000C60C6: 83 EC 0C                 sub     esp, 0Ch
 * 000C60C9: C6 06 54                 mov     byte ptr [esi], 54h ; 'T'
 * 000C60CC: 8B 45 08                 mov     eax, [ebp+arg_0]
 * 000C60CF: 8A 40 01                 mov     al, [eax+1]
 * 000C60D2: 89 04 24                 mov     [esp+14h+var_14], eax
 * 000C60D5: C7 44 24 04 03 00 00 00  mov     [esp+14h+var_10], 3
 * 000C60DD: 8D 46 01                 lea     eax, [esi+1]
 * 000C60E0: 89 44 24 08              mov     [esp+14h+var_C], eax
 * 000C60E4: E8 D3 BC F9 FF           call    util_61DBC
 * 000C60E9: C6 46 04 00              mov     byte ptr [esi+4], 0
 * 000C60ED: 8B 45 10                 mov     eax, [ebp+arg_8]
 * 000C60F0: C6 00 04                 mov     byte ptr [eax], 4
 * 000C60F3: 8B 75 F8                 mov     esi, [ebp+var_8]
 * 000C60F6: 89 EC                    mov     esp, ebp
 * 000C60F8: 5D                       pop     ebp
 * 000C60F9: C3                       retn
 * ========================================================================== */
// [SRX-611] pop_rank=437/1298, sites=2, callers=2, callees=1, size=0x3E
_BYTE *__cdecl util_C60BC(int a1, _BYTE *a2, _BYTE *a3)
{
  _BYTE *result; // eax

  *a2 = 84;
  util_61DBC((int)(a2 + 1), *(_BYTE *)(a1 + 1), 3u, a2 + 1);
  a2[4] = 0;
  result = a3;
  *a3 = 4;
  return result;
}


/* ============================================================================
 * util_C60FC  @ 0xC60FC   size=0x3E   callers=2
 * note: [SRX-611] pop_rank=438/1298, sites=2, callers=2, callees=1, size=0x3E
 * --- original assembly (address: bytes  mnemonic) ---------------------------
 * 000C60FC: 55                       push    ebp
 * 000C60FD: 89 E5                    mov     ebp, esp
 * 000C60FF: 83 EC 04                 sub     esp, 4
 * 000C6102: 56                       push    esi
 * 000C6103: 8B 75 0C                 mov     esi, [ebp+arg_4]
 * 000C6106: 83 EC 0C                 sub     esp, 0Ch
 * 000C6109: C6 06 43                 mov     byte ptr [esi], 43h ; 'C'
 * 000C610C: 8B 45 08                 mov     eax, [ebp+arg_0]
 * 000C610F: 8A 40 01                 mov     al, [eax+1]
 * 000C6112: 89 04 24                 mov     [esp+14h+var_14], eax
 * 000C6115: C7 44 24 04 03 00 00 00  mov     [esp+14h+var_10], 3
 * 000C611D: 8D 46 01                 lea     eax, [esi+1]
 * 000C6120: 89 44 24 08              mov     [esp+14h+var_C], eax
 * 000C6124: E8 93 BC F9 FF           call    util_61DBC
 * 000C6129: C6 46 04 00              mov     byte ptr [esi+4], 0
 * 000C612D: 8B 45 10                 mov     eax, [ebp+arg_8]
 * 000C6130: C6 00 04                 mov     byte ptr [eax], 4
 * 000C6133: 8B 75 F8                 mov     esi, [ebp+var_8]
 * 000C6136: 89 EC                    mov     esp, ebp
 * 000C6138: 5D                       pop     ebp
 * 000C6139: C3                       retn
 * ========================================================================== */
// [SRX-611] pop_rank=438/1298, sites=2, callers=2, callees=1, size=0x3E
_BYTE *__cdecl util_C60FC(int a1, _BYTE *a2, _BYTE *a3)
{
  _BYTE *result; // eax

  *a2 = 67;
  util_61DBC((int)(a2 + 1), *(_BYTE *)(a1 + 1), 3u, a2 + 1);
  a2[4] = 0;
  result = a3;
  *a3 = 4;
  return result;
}


/* ============================================================================
 * util_C613C  @ 0xC613C   size=0x57   callers=2
 * note: [SRX-611] pop_rank=425/1298, sites=2, callers=2, callees=1, size=0x57
 * --- original assembly (address: bytes  mnemonic) ---------------------------
 * 000C613C: 55                       push    ebp
 * 000C613D: 89 E5                    mov     ebp, esp
 * 000C613F: 83 EC 04                 sub     esp, 4
 * 000C6142: 57                       push    edi
 * 000C6143: 56                       push    esi
 * 000C6144: 83 EC 08                 sub     esp, 8
 * 000C6147: 8B 75 0C                 mov     esi, [ebp+arg_4]
 * 000C614A: 33 C9                    xor     ecx, ecx
 * 000C614C: C6 06 49                 mov     byte ptr [esi], 49h ; 'I'
 * 000C614F: 8B 45 08                 mov     eax, [ebp+arg_0]
 * 000C6152: 8A 48 01                 mov     cl, [eax+1]
 * 000C6155: 8B 40 02                 mov     eax, [eax+2]
 * 000C6158: 25 FF 00 00 00           and     eax, 0FFh
 * 000C615D: 8D 44 C8 01              lea     eax, [eax+ecx*8+1]
 * 000C6161: 66 89 45 FE              mov     [ebp+var_2], ax
 * 000C6165: 89 04 24                 mov     [esp+14h+var_14], eax
 * 000C6168: 8D 46 01                 lea     eax, [esi+1]
 * 000C616B: 89 44 24 04              mov     [esp+14h+var_10], eax
 * 000C616F: E8 E0 BC F9 FF           call    util_61E54
 * 000C6174: 2B C0                    sub     eax, eax
 * 000C6176: B9 FF FF FF FF           mov     ecx, 0FFFFFFFFh
 * 000C617B: 89 F7                    mov     edi, esi
 * 000C617D: F2 AE                    repne scasb
 * 000C617F: F7 D9                    neg     ecx
 * 000C6181: 83 E9 02                 sub     ecx, 2
 * 000C6184: 8B 45 10                 mov     eax, [ebp+arg_8]
 * 000C6187: 88 08                    mov     [eax], cl
 * 000C6189: 8B 75 F4                 mov     esi, [ebp+var_C]
 * 000C618C: 8B 7D F8                 mov     edi, [ebp+var_8]
 * 000C618F: 89 EC                    mov     esp, ebp
 * 000C6191: 5D                       pop     ebp
 * 000C6192: C3                       retn
 * ========================================================================== */
// [SRX-611] pop_rank=425/1298, sites=2, callers=2, callees=1, size=0x57
_BYTE *__cdecl util_C613C(int a1, char *a2, _BYTE *a3)
{
  _BYTE *result; // eax

  *a2 = 73;
  util_61E54((unsigned __int8)*(_DWORD *)(a1 + 2) + 8 * *(unsigned __int8 *)(a1 + 1) + 1, a2 + 1);
  result = a3;
  *a3 = strlen(a2);
  return result;
}


/* ============================================================================
 * util_C6194  @ 0xC6194   size=0x57   callers=2
 * note: [SRX-611] pop_rank=426/1298, sites=2, callers=2, callees=1, size=0x57
 * --- original assembly (address: bytes  mnemonic) ---------------------------
 * 000C6194: 55                       push    ebp
 * 000C6195: 89 E5                    mov     ebp, esp
 * 000C6197: 83 EC 04                 sub     esp, 4
 * 000C619A: 57                       push    edi
 * 000C619B: 56                       push    esi
 * 000C619C: 83 EC 08                 sub     esp, 8
 * 000C619F: 8B 75 0C                 mov     esi, [ebp+arg_4]
 * 000C61A2: 33 C9                    xor     ecx, ecx
 * 000C61A4: C6 06 4C                 mov     byte ptr [esi], 4Ch ; 'L'
 * 000C61A7: 8B 45 08                 mov     eax, [ebp+arg_0]
 * 000C61AA: 8A 48 01                 mov     cl, [eax+1]
 * 000C61AD: 8B 40 02                 mov     eax, [eax+2]
 * 000C61B0: 25 FF 00 00 00           and     eax, 0FFh
 * 000C61B5: 8D 44 C8 01              lea     eax, [eax+ecx*8+1]
 * 000C61B9: 66 89 45 FE              mov     [ebp+var_2], ax
 * 000C61BD: 89 04 24                 mov     [esp+14h+var_14], eax
 * 000C61C0: 8D 46 01                 lea     eax, [esi+1]
 * 000C61C3: 89 44 24 04              mov     [esp+14h+var_10], eax
 * 000C61C7: E8 88 BC F9 FF           call    util_61E54
 * 000C61CC: 2B C0                    sub     eax, eax
 * 000C61CE: B9 FF FF FF FF           mov     ecx, 0FFFFFFFFh
 * 000C61D3: 89 F7                    mov     edi, esi
 * 000C61D5: F2 AE                    repne scasb
 * 000C61D7: F7 D9                    neg     ecx
 * 000C61D9: 83 E9 02                 sub     ecx, 2
 * 000C61DC: 8B 45 10                 mov     eax, [ebp+arg_8]
 * 000C61DF: 88 08                    mov     [eax], cl
 * 000C61E1: 8B 75 F4                 mov     esi, [ebp+var_C]
 * 000C61E4: 8B 7D F8                 mov     edi, [ebp+var_8]
 * 000C61E7: 89 EC                    mov     esp, ebp
 * 000C61E9: 5D                       pop     ebp
 * 000C61EA: C3                       retn
 * ========================================================================== */
// [SRX-611] pop_rank=426/1298, sites=2, callers=2, callees=1, size=0x57
_BYTE *__cdecl util_C6194(int a1, char *a2, _BYTE *a3)
{
  _BYTE *result; // eax

  *a2 = 76;
  util_61E54((unsigned __int8)*(_DWORD *)(a1 + 2) + 8 * *(unsigned __int8 *)(a1 + 1) + 1, a2 + 1);
  result = a3;
  *a3 = strlen(a2);
  return result;
}


/* ============================================================================
 * util_C62AC  @ 0xC62AC   size=0x69   callers=2
 * note: [SRX-611] pop_rank=403/1298, sites=2, callers=2, callees=1, size=0x69
 * --- original assembly (address: bytes  mnemonic) ---------------------------
 * 000C62AC: 55                       push    ebp
 * 000C62AD: 89 E5                    mov     ebp, esp
 * 000C62AF: 57                       push    edi
 * 000C62B0: 8B 7D 0C                 mov     edi, [ebp+arg_4]
 * 000C62B3: 56                       push    esi
 * 000C62B4: 83 EC 0C                 sub     esp, 0Ch
 * 000C62B7: C6 07 52                 mov     byte ptr [edi], 52h ; 'R'
 * 000C62BA: 8B 45 08                 mov     eax, [ebp+arg_0]
 * 000C62BD: 8B 75 10                 mov     esi, [ebp+arg_8]
 * 000C62C0: 8A 48 01                 mov     cl, [eax+1]
 * 000C62C3: 80 F9 63                 cmp     cl, 63h ; 'c'
 * 000C62C6: 8D 47 01                 lea     eax, [edi+1]
 * 000C62C9: 77 21                    ja      short loc_C62EC
 * 000C62CB: 89 0C 24                 mov     [esp+14h+var_14], ecx
 * 000C62CE: C7 44 24 04 02 00 00 00  mov     [esp+14h+var_10], 2
 * 000C62D6: 89 44 24 08              mov     [esp+14h+var_C], eax
 * 000C62DA: E8 DD BA F9 FF           call    util_61DBC
 * 000C62DF: C6 47 03 43              mov     byte ptr [edi+3], 43h ; 'C'
 * 000C62E3: C6 47 04 00              mov     byte ptr [edi+4], 0
 * 000C62E7: C6 06 04                 mov     byte ptr [esi], 4
 * 000C62EA: EB 1F                    jmp     short loc_C630B
 * 000C62EC: 89 0C 24                 mov     [esp+14h+var_14], ecx
 * 000C62EF: C7 44 24 04 03 00 00 00  mov     [esp+14h+var_10], 3
 * 000C62F7: 89 44 24 08              mov     [esp+14h+var_C], eax
 * 000C62FB: E8 BC BA F9 FF           call    util_61DBC
 * 000C6300: C6 47 04 43              mov     byte ptr [edi+4], 43h ; 'C'
 * 000C6304: C6 47 05 00              mov     byte ptr [edi+5], 0
 * 000C6308: C6 06 05                 mov     byte ptr [esi], 5
 * 000C630B: 8B 75 F8                 mov     esi, [ebp+var_8]
 * 000C630E: 8B 7D FC                 mov     edi, [ebp+var_4]
 * 000C6311: 89 EC                    mov     esp, ebp
 * 000C6313: 5D                       pop     ebp
 * 000C6314: C3                       retn
 * ========================================================================== */
// [SRX-611] pop_rank=403/1298, sites=2, callers=2, callees=1, size=0x69
int __cdecl util_C62AC(int a1, _BYTE *a2, _BYTE *a3)
{
  char v3; // cl
  int v4; // eax
  int result; // eax

  *a2 = 82;
  v3 = *(_BYTE *)(a1 + 1);
  v4 = (int)(a2 + 1);
  if ( (unsigned __int8)v3 > 0x63u )
  {
    result = util_61DBC(v4, v3, 3u, a2 + 1);
    a2[4] = 67;
    a2[5] = 0;
    *a3 = 5;
  }
  else
  {
    result = util_61DBC(v4, v3, 2u, a2 + 1);
    a2[3] = 67;
    a2[4] = 0;
    *a3 = 4;
  }
  return result;
}


/* ============================================================================
 * util_C631C  @ 0xC631C   size=0x69   callers=2
 * note: [SRX-611] pop_rank=404/1298, sites=2, callers=2, callees=1, size=0x69
 * --- original assembly (address: bytes  mnemonic) ---------------------------
 * 000C631C: 55                       push    ebp
 * 000C631D: 89 E5                    mov     ebp, esp
 * 000C631F: 57                       push    edi
 * 000C6320: 8B 7D 0C                 mov     edi, [ebp+arg_4]
 * 000C6323: 56                       push    esi
 * 000C6324: 83 EC 0C                 sub     esp, 0Ch
 * 000C6327: C6 07 4B                 mov     byte ptr [edi], 4Bh ; 'K'
 * 000C632A: 8B 45 08                 mov     eax, [ebp+arg_0]
 * 000C632D: 8B 75 10                 mov     esi, [ebp+arg_8]
 * 000C6330: 8A 48 01                 mov     cl, [eax+1]
 * 000C6333: 80 F9 63                 cmp     cl, 63h ; 'c'
 * 000C6336: 8D 47 01                 lea     eax, [edi+1]
 * 000C6339: 77 21                    ja      short loc_C635C
 * 000C633B: 89 0C 24                 mov     [esp+14h+var_14], ecx
 * 000C633E: C7 44 24 04 02 00 00 00  mov     [esp+14h+var_10], 2
 * 000C6346: 89 44 24 08              mov     [esp+14h+var_C], eax
 * 000C634A: E8 6D BA F9 FF           call    util_61DBC
 * 000C634F: C6 47 03 43              mov     byte ptr [edi+3], 43h ; 'C'
 * 000C6353: C6 47 04 00              mov     byte ptr [edi+4], 0
 * 000C6357: C6 06 04                 mov     byte ptr [esi], 4
 * 000C635A: EB 1F                    jmp     short loc_C637B
 * 000C635C: 89 0C 24                 mov     [esp+14h+var_14], ecx
 * 000C635F: C7 44 24 04 03 00 00 00  mov     [esp+14h+var_10], 3
 * 000C6367: 89 44 24 08              mov     [esp+14h+var_C], eax
 * 000C636B: E8 4C BA F9 FF           call    util_61DBC
 * 000C6370: C6 47 04 43              mov     byte ptr [edi+4], 43h ; 'C'
 * 000C6374: C6 47 05 00              mov     byte ptr [edi+5], 0
 * 000C6378: C6 06 05                 mov     byte ptr [esi], 5
 * 000C637B: 8B 75 F8                 mov     esi, [ebp+var_8]
 * 000C637E: 8B 7D FC                 mov     edi, [ebp+var_4]
 * 000C6381: 89 EC                    mov     esp, ebp
 * 000C6383: 5D                       pop     ebp
 * 000C6384: C3                       retn
 * ========================================================================== */
// [SRX-611] pop_rank=404/1298, sites=2, callers=2, callees=1, size=0x69
int __cdecl util_C631C(int a1, _BYTE *a2, _BYTE *a3)
{
  char v3; // cl
  int v4; // eax
  int result; // eax

  *a2 = 75;
  v3 = *(_BYTE *)(a1 + 1);
  v4 = (int)(a2 + 1);
  if ( (unsigned __int8)v3 > 0x63u )
  {
    result = util_61DBC(v4, v3, 3u, a2 + 1);
    a2[4] = 67;
    a2[5] = 0;
    *a3 = 5;
  }
  else
  {
    result = util_61DBC(v4, v3, 2u, a2 + 1);
    a2[3] = 67;
    a2[4] = 0;
    *a3 = 4;
  }
  return result;
}


/* ============================================================================
 * util_C643C  @ 0xC643C   size=0x7E   callers=2
 * note: [SRX-611] pop_rank=371/1298, sites=2, callers=2, callees=0, size=0x7E, leaf
 * --- original assembly (address: bytes  mnemonic) ---------------------------
 * 000C643C: 55                       push    ebp
 * 000C643D: 89 E5                    mov     ebp, esp
 * 000C643F: 8B 45 08                 mov     eax, [ebp+arg_0]
 * 000C6442: 83 EC 04                 sub     esp, 4
 * 000C6445: 8A 00                    mov     al, [eax]
 * 000C6447: 3C 01                    cmp     al, 1
 * 000C6449: 74 04                    jz      short loc_C644F
 * 000C644B: 3C 81                    cmp     al, 81h
 * 000C644D: 75 05                    jnz     short loc_C6454
 * 000C644F: B0 01                    mov     al, 1
 * 000C6451: EB 63                    jmp     short loc_C64B6
 * 000C6453: 90                       align 4
 * 000C6454: 22 C0                    and     al, al
 * 000C6456: 74 04                    jz      short loc_C645C
 * 000C6458: 3C 80                    cmp     al, 80h
 * 000C645A: 75 08                    jnz     short loc_C6464
 * 000C645C: B0 01                    mov     al, 1
 * 000C645E: EB 56                    jmp     short loc_C64B6
 * 000C6460: 90 90 90 90              db 4 dup(90h)
 * 000C6464: 3C 03                    cmp     al, 3
 * 000C6466: 74 04                    jz      short loc_C646C
 * 000C6468: 3C 83                    cmp     al, 83h
 * 000C646A: 75 08                    jnz     short loc_C6474
 * 000C646C: B0 01                    mov     al, 1
 * 000C646E: EB 46                    jmp     short loc_C64B6
 * 000C6470: 90 90 90 90              db 4 dup(90h)
 * 000C6474: 3C 04                    cmp     al, 4
 * 000C6476: 74 04                    jz      short loc_C647C
 * 000C6478: 3C 84                    cmp     al, 84h
 * 000C647A: 75 08                    jnz     short loc_C6484
 * 000C647C: B0 01                    mov     al, 1
 * 000C647E: EB 36                    jmp     short loc_C64B6
 * 000C6480: 90 90 90 90              db 4 dup(90h)
 * 000C6484: 3C 05                    cmp     al, 5
 * 000C6486: 74 04                    jz      short loc_C648C
 * 000C6488: 3C 85                    cmp     al, 85h
 * 000C648A: 75 08                    jnz     short loc_C6494
 * 000C648C: B0 01                    mov     al, 1
 * 000C648E: EB 26                    jmp     short loc_C64B6
 * 000C6490: 90 90 90 90              db 4 dup(90h)
 * 000C6494: 3C 02                    cmp     al, 2
 * 000C6496: 74 04                    jz      short loc_C649C
 * 000C6498: 3C 82                    cmp     al, 82h
 * 000C649A: 75 08                    jnz     short loc_C64A4
 * 000C649C: B0 01                    mov     al, 1
 * 000C649E: EB 16                    jmp     short loc_C64B6
 * 000C64A0: 90 90 90 90              db 4 dup(90h)
 * 000C64A4: 3C 06                    cmp     al, 6
 * 000C64A6: 74 04                    jz      short loc_C64AC
 * 000C64A8: 3C 86                    cmp     al, 86h
 * 000C64AA: 75 08                    jnz     short loc_C64B4
 * 000C64AC: B0 01                    mov     al, 1
 * 000C64AE: EB 06                    jmp     short loc_C64B6
 * 000C64B0: 90 90 90 90              db 4 dup(90h)
 * 000C64B4: 2B C0                    sub     eax, eax
 * 000C64B6: 89 EC                    mov     esp, ebp
 * 000C64B8: 5D                       pop     ebp
 * 000C64B9: C3                       retn
 * ========================================================================== */
// [SRX-611] pop_rank=371/1298, sites=2, callers=2, callees=0, size=0x7E, leaf
char __cdecl util_C643C(char *a1)
{
  char v1; // al

  v1 = *a1;
  if ( *a1 == 1 || v1 == -127 )
    return 1;
  switch ( v1 )
  {
    case 0:
    case -128:
      return 1;
    case 3:
    case -125:
      return 1;
    case 4:
    case -124:
      return 1;
    case 5:
    case -123:
      return 1;
    case 2:
    case -126:
      return 1;
    case 6:
    case -122:
      return 1;
  }
  return 0;
}


/* ============================================================================
 * util_C6A3C  @ 0xC6A3C   size=0x17   callers=2
 * note: [SRX-611] pop_rank=754/1298, sites=1, callers=1, callees=0, size=0x17, leaf
 * --- original assembly (address: bytes  mnemonic) ---------------------------
 * 000C6A3C: 55                       push    ebp
 * 000C6A3D: 89 E5                    mov     ebp, esp
 * 000C6A3F: 83 EC 04                 sub     esp, 4
 * 000C6A42: 8B 45 08                 mov     eax, [ebp+arg_0]
 * 000C6A45: 8B 15 2C F1 00 00        mov     edx, dword ptr ds:loc_F12C
 * 000C6A4B: 89 10                    mov     [eax], edx
 * 000C6A4D: 2B C0                    sub     eax, eax
 * 000C6A4F: 89 EC                    mov     esp, ebp
 * 000C6A51: 5D                       pop     ebp
 * 000C6A52: C3                       retn
 * ========================================================================== */
// [SRX-611] pop_rank=754/1298, sites=1, callers=1, callees=0, size=0x17, leaf
int __cdecl util_C6A3C(_DWORD *a1)
{
  *a1 = loc_F12C;
  return 0;
}


/* ============================================================================
 * util_C6AEC  @ 0xC6AEC   size=0x5C   callers=2
 * note: [SRX-611] pop_rank=697/1298, sites=1, callers=1, callees=1, size=0x5C
 * --- original assembly (address: bytes  mnemonic) ---------------------------
 * 000C6AEC: 55                       push    ebp
 * 000C6AED: 89 E5                    mov     ebp, esp
 * 000C6AEF: 8B 45 14                 mov     eax, [ebp+arg_C]
 * 000C6AF2: 66 8B 15 30 F1 00 00     mov     dx, word ptr ds:loc_F12E+2
 * 000C6AF9: 83 EC 14                 sub     esp, 14h
 * 000C6AFC: 66 C7 45 FE 00 00        mov     [ebp+var_2], 0
 * 000C6B02: 66 89 10                 mov     [eax], dx
 * 000C6B05: 8A 15 32 F1 00 00        mov     dl, byte ptr ds:loc_F132
 * 000C6B0B: 88 50 02                 mov     [eax+2], dl
 * 000C6B0E: 83 C0 02                 add     eax, 2
 * 000C6B11: 8A 4D 08                 mov     cl, [ebp+arg_0]
 * 000C6B14: 89 45 14                 mov     [ebp+arg_C], eax
 * 000C6B17: 89 0C 24                 mov     [esp+14h+var_14], ecx
 * 000C6B1A: 8B 4D 0C                 mov     ecx, [ebp+arg_4]
 * 000C6B1D: 89 4C 24 04              mov     [esp+14h+var_10], ecx
 * 000C6B21: 8B 4D 10                 mov     ecx, [ebp+arg_8]
 * 000C6B24: 41                       inc     ecx
 * 000C6B25: 89 4C 24 08              mov     [esp+14h+var_C], ecx
 * 000C6B29: 89 44 24 0C              mov     [esp+14h+var_8], eax
 * 000C6B2D: E8 E2 10 00 00           call    fn_C7C14
 * 000C6B32: 66 89 45 FE              mov     [ebp+var_2], ax
 * 000C6B36: 66 23 C0                 and     ax, ax
 * 000C6B39: 74 09                    jz      short loc_C6B44
 * 000C6B3B: EB 07                    jmp     short loc_C6B44
 * 000C6B3D: 90 90 90 90 90 90 90     db 7 dup(90h)
 * 000C6B44: 89 EC                    mov     esp, ebp
 * 000C6B46: 5D                       pop     ebp
 * 000C6B47: C3                       retn
 * ========================================================================== */
// [SRX-611] pop_rank=697/1298, sites=1, callers=1, callees=1, size=0x5C
int __cdecl util_C6AEC(char a1, int a2, int a3, int a4)
{
  *(_WORD *)a4 = *(&loc_F12E + 1);
  *(_BYTE *)(a4 + 2) = loc_F132;
  return fn_C7C14(a1, a2, a3 + 1, a4 + 2);
}


/* ============================================================================
 * util_C6B4C  @ 0xC6B4C   size=0x17   callers=2
 * note: [SRX-611] pop_rank=755/1298, sites=1, callers=1, callees=0, size=0x17, leaf
 * --- original assembly (address: bytes  mnemonic) ---------------------------
 * 000C6B4C: 55                       push    ebp
 * 000C6B4D: 89 E5                    mov     ebp, esp
 * 000C6B4F: 83 EC 04                 sub     esp, 4
 * 000C6B52: 8B 45 08                 mov     eax, [ebp+arg_0]
 * 000C6B55: 8B 15 34 F1 00 00        mov     edx, dword ptr ds:loc_F134
 * 000C6B5B: 89 10                    mov     [eax], edx
 * 000C6B5D: 2B C0                    sub     eax, eax
 * 000C6B5F: 89 EC                    mov     esp, ebp
 * 000C6B61: 5D                       pop     ebp
 * 000C6B62: C3                       retn
 * ========================================================================== */
// [SRX-611] pop_rank=755/1298, sites=1, callers=1, callees=0, size=0x17, leaf
int __cdecl util_C6B4C(_DWORD *a1)
{
  *a1 = loc_F134;
  return 0;
}


/* ============================================================================
 * util_C6B64  @ 0xC6B64   size=0xB5   callers=2
 * note: [SRX-611] pop_rank=638/1298, sites=1, callers=1, callees=3, size=0xB5
 * --- original assembly (address: bytes  mnemonic) ---------------------------
 * 000C6B64: 55                       push    ebp
 * 000C6B65: 89 E5                    mov     ebp, esp
 * 000C6B67: 83 EC 18                 sub     esp, 18h
 * 000C6B6A: 66 C7 45 FE 00 00        mov     [ebp+var_2], 0
 * 000C6B70: 8B 15 38 F1 00 00        mov     edx, dword ptr ds:loc_F138
 * 000C6B76: 57                       push    edi
 * 000C6B77: 56                       push    esi
 * 000C6B78: 53                       push    ebx
 * 000C6B79: 83 EC 10                 sub     esp, 10h
 * 000C6B7C: 8B 75 14                 mov     esi, [ebp+arg_C]
 * 000C6B7F: 89 16                    mov     [esi], edx
 * 000C6B81: 83 C6 03                 add     esi, 3
 * 000C6B84: 8B 5D 0C                 mov     ebx, [ebp+arg_4]
 * 000C6B87: 89 75 14                 mov     [ebp+arg_C], esi
 * 000C6B8A: 89 1C 24                 mov     [esp+34h+var_34], ebx
 * 000C6B8D: 8B 7D 10                 mov     edi, [ebp+arg_8]
 * 000C6B90: 8D 47 01                 lea     eax, [edi+1]
 * 000C6B93: 89 44 24 04              mov     [esp+34h+var_30], eax
 * 000C6B97: 8D 45 F0                 lea     eax, [ebp+var_10]
 * 000C6B9A: 89 44 24 08              mov     [esp+34h+var_2C], eax
 * 000C6B9E: 8D 45 EF                 lea     eax, [ebp+var_11]
 * 000C6BA1: 89 44 24 0C              mov     [esp+34h+var_28], eax
 * 000C6BA5: E8 1A F1 FF FF           call    token_dispatch
 * 000C6BAA: 66 89 45 FE              mov     [ebp+var_2], ax
 * 000C6BAE: 66 23 C0                 and     ax, ax
 * 000C6BB1: 74 09                    jz      short loc_C6BBC
 * 000C6BB3: EB 57                    jmp     short loc_C6C0C
 * 000C6BB5: 90 90 90 90 90 90 90     db 7 dup(90h)
 * 000C6BBC: 89 34 24                 mov     [esp+34h+var_34], esi
 * 000C6BBF: 8D 45 F0                 lea     eax, [ebp+var_10]
 * 000C6BC2: 89 44 24 04              mov     [esp+34h+var_30], eax
 * 000C6BC6: E8 91 79 00 00           call    strcpy
 * 000C6BCB: 33 C0                    xor     eax, eax
 * 000C6BCD: 8A 45 EF                 mov     al, [ebp+var_11]
 * 000C6BD0: 03 C6                    add     eax, esi
 * 000C6BD2: 89 45 14                 mov     [ebp+arg_C], eax
 * 000C6BD5: 66 8B 15 3C F1 00 00     mov     dx, word ptr ds:loc_F13A+2
 * 000C6BDC: 66 89 10                 mov     [eax], dx
 * 000C6BDF: 40                       inc     eax
 * 000C6BE0: 83 C7 04                 add     edi, 4
 * 000C6BE3: 89 45 14                 mov     [ebp+arg_C], eax
 * 000C6BE6: 8A 4D 08                 mov     cl, [ebp+arg_0]
 * 000C6BE9: 89 0C 24                 mov     [esp+34h+var_34], ecx
 * 000C6BEC: 89 5C 24 04              mov     [esp+34h+var_30], ebx
 * 000C6BF0: 89 7C 24 08              mov     [esp+34h+var_2C], edi
 * 000C6BF4: 89 44 24 0C              mov     [esp+34h+var_28], eax
 * 000C6BF8: E8 17 10 00 00           call    fn_C7C14
 * 000C6BFD: 66 89 45 FE              mov     [ebp+var_2], ax
 * 000C6C01: 66 23 C0                 and     ax, ax
 * 000C6C04: 74 06                    jz      short loc_C6C0C
 * 000C6C06: EB 04                    jmp     short loc_C6C0C
 * 000C6C08: 90 90 90 90              db 4 dup(90h)
 * 000C6C0C: 8B 5D DC                 mov     ebx, [ebp+var_24]
 * 000C6C0F: 8B 75 E0                 mov     esi, [ebp+var_20]
 * 000C6C12: 8B 7D E4                 mov     edi, [ebp+var_1C]
 * 000C6C15: 89 EC                    mov     esp, ebp
 * 000C6C17: 5D                       pop     ebp
 * 000C6C18: C3                       retn
 * ========================================================================== */
// [SRX-611] pop_rank=638/1298, sites=1, callers=1, callees=3, size=0xB5
int __cdecl util_C6B64(char a1, int a2, int a3, _DWORD *a4)
{
  char *v4; // esi
  int result; // eax
  char *v6; // eax
  int v7; // ecx
  unsigned __int8 v8; // [esp+23h] [ebp-11h] BYREF
  char v9[14]; // [esp+24h] [ebp-10h] BYREF
  __int16 v10; // [esp+32h] [ebp-2h]

  v10 = 0;
  *a4 = loc_F138;
  v4 = (char *)a4 + 3;
  result = token_dispatch(a2, a3 + 1, v9, &v8);
  v10 = result;
  if ( !(_WORD)result )
  {
    strcpy(v4, v9);
    v6 = &v4[v8];
    *(_WORD *)v6 = *(&loc_F13A + 1);
    LOBYTE(v7) = a1;
    return fn_C7C14(v7, a2, a3 + 4, v6 + 1);
  }
  return result;
}


/* ============================================================================
 * util_C6C1C  @ 0xC6C1C   size=0x8F   callers=2
 * note: [SRX-611] pop_rank=667/1298, sites=1, callers=1, callees=2, size=0x8F
 * --- original assembly (address: bytes  mnemonic) ---------------------------
 * 000C6C1C: 55                       push    ebp
 * 000C6C1D: 89 E5                    mov     ebp, esp
 * 000C6C1F: 83 EC 18                 sub     esp, 18h
 * 000C6C22: 8B 15 40 F1 00 00        mov     edx, dword ptr ds:loc_F140
 * 000C6C28: 66 C7 45 FE 00 00        mov     [ebp+var_2], 0
 * 000C6C2E: 57                       push    edi
 * 000C6C2F: 56                       push    esi
 * 000C6C30: 8B 75 10                 mov     esi, [ebp+arg_8]
 * 000C6C33: 89 16                    mov     [esi], edx
 * 000C6C35: 53                       push    ebx
 * 000C6C36: 83 EC 10                 sub     esp, 10h
 * 000C6C39: 8A 15 44 F1 00 00        mov     dl, byte ptr ds:loc_F144
 * 000C6C3F: 88 56 04                 mov     [esi+4], dl
 * 000C6C42: 83 C6 04                 add     esi, 4
 * 000C6C45: 8B 45 08                 mov     eax, [ebp+arg_0]
 * 000C6C48: 89 75 10                 mov     [ebp+arg_8], esi
 * 000C6C4B: 89 04 24                 mov     [esp+34h+var_34], eax
 * 000C6C4E: 8B 45 0C                 mov     eax, [ebp+arg_4]
 * 000C6C51: 40                       inc     eax
 * 000C6C52: 89 44 24 04              mov     [esp+34h+var_30], eax
 * 000C6C56: 8D 7D F0                 lea     edi, [ebp+var_10]
 * 000C6C59: 89 7C 24 08              mov     [esp+34h+var_2C], edi
 * 000C6C5D: 8D 45 EF                 lea     eax, [ebp+var_11]
 * 000C6C60: 89 44 24 0C              mov     [esp+34h+var_28], eax
 * 000C6C64: E8 5B F0 FF FF           call    token_dispatch
 * 000C6C69: 89 C3                    mov     ebx, eax
 * 000C6C6B: 66 89 5D FE              mov     [ebp+var_2], bx
 * 000C6C6F: 66 23 DB                 and     bx, bx
 * 000C6C72: 74 08                    jz      short loc_C6C7C
 * 000C6C74: 89 D8                    mov     eax, ebx
 * 000C6C76: EB 26                    jmp     short loc_C6C9E
 * 000C6C78: 90 90 90 90              db 4 dup(90h)
 * 000C6C7C: 89 34 24                 mov     [esp+34h+var_34], esi
 * 000C6C7F: 89 7C 24 04              mov     [esp+34h+var_30], edi
 * 000C6C83: E8 D4 78 00 00           call    strcpy
 * 000C6C88: 33 C0                    xor     eax, eax
 * 000C6C8A: 8A 45 EF                 mov     al, [ebp+var_11]
 * 000C6C8D: 03 C6                    add     eax, esi
 * 000C6C8F: 89 45 10                 mov     [ebp+arg_8], eax
 * 000C6C92: 66 8B 15 3C F1 00 00     mov     dx, word ptr ds:loc_F13A+2
 * 000C6C99: 66 89 10                 mov     [eax], dx
 * 000C6C9C: 89 D8                    mov     eax, ebx
 * 000C6C9E: 8B 5D DC                 mov     ebx, [ebp+var_24]
 * 000C6CA1: 8B 75 E0                 mov     esi, [ebp+var_20]
 * 000C6CA4: 8B 7D E4                 mov     edi, [ebp+var_1C]
 * 000C6CA7: 89 EC                    mov     esp, ebp
 * 000C6CA9: 5D                       pop     ebp
 * 000C6CAA: C3                       retn
 * ========================================================================== */
// [SRX-611] pop_rank=667/1298, sites=1, callers=1, callees=2, size=0x8F
int __cdecl util_C6C1C(int a1, int a2, int a3)
{
  char *v3; // esi
  int result; // eax
  int v5; // ebx
  unsigned __int8 v6; // [esp+23h] [ebp-11h] BYREF
  char v7[14]; // [esp+24h] [ebp-10h] BYREF
  __int16 v8; // [esp+32h] [ebp-2h]

  v8 = 0;
  *(_DWORD *)a3 = loc_F140;
  *(_BYTE *)(a3 + 4) = loc_F144;
  v3 = (char *)(a3 + 4);
  result = token_dispatch(a1, a2 + 1, v7, &v6);
  v5 = result;
  v8 = result;
  if ( !(_WORD)result )
  {
    strcpy(v3, v7);
    *(_WORD *)&v3[v6] = *(&loc_F13A + 1);
    return v5;
  }
  return result;
}


/* ============================================================================
 * util_C6CAC  @ 0xC6CAC   size=0xD5   callers=2
 * note: [SRX-611] pop_rank=333/1298, sites=2, callers=2, callees=4, size=0xD5
 * --- original assembly (address: bytes  mnemonic) ---------------------------
 * 000C6CAC: 55                       push    ebp
 * 000C6CAD: 89 E5                    mov     ebp, esp
 * 000C6CAF: 83 EC 18                 sub     esp, 18h
 * 000C6CB2: 66 C7 45 FE 00 00        mov     [ebp+var_2], 0
 * 000C6CB8: 66 8B 15 48 F1 00 00     mov     dx, ds:word_F148
 * 000C6CBF: 57                       push    edi
 * 000C6CC0: 56                       push    esi
 * 000C6CC1: 53                       push    ebx
 * 000C6CC2: 83 EC 10                 sub     esp, 10h
 * 000C6CC5: 8B 7D 14                 mov     edi, [ebp+arg_C]
 * 000C6CC8: 66 89 17                 mov     [edi], dx
 * 000C6CCB: 8B 75 10                 mov     esi, [ebp+arg_8]
 * 000C6CCE: 47                       inc     edi
 * 000C6CCF: 89 7D 14                 mov     [ebp+arg_C], edi
 * 000C6CD2: 8A 46 02                 mov     al, [esi+2]
 * 000C6CD5: 89 04 24                 mov     [esp+34h+var_34], eax
 * 000C6CD8: C7 44 24 04 03 00 00 00  mov     [esp+34h+var_30], 3
 * 000C6CE0: 89 7C 24 08              mov     [esp+34h+var_2C], edi
 * 000C6CE4: E8 D3 B0 F9 FF           call    util_61DBC
 * 000C6CE9: 83 C7 03                 add     edi, 3
 * 000C6CEC: 89 7D 14                 mov     [ebp+arg_C], edi
 * 000C6CEF: C6 07 28                 mov     byte ptr [edi], 28h ; '('
 * 000C6CF2: 47                       inc     edi
 * 000C6CF3: 89 7D 14                 mov     [ebp+arg_C], edi
 * 000C6CF6: 8B 5D 0C                 mov     ebx, [ebp+arg_4]
 * 000C6CF9: 89 1C 24                 mov     [esp+34h+var_34], ebx
 * 000C6CFC: 8D 46 04                 lea     eax, [esi+4]
 * 000C6CFF: 89 44 24 04              mov     [esp+34h+var_30], eax
 * 000C6D03: 8D 45 F0                 lea     eax, [ebp+var_10]
 * 000C6D06: 89 44 24 08              mov     [esp+34h+var_2C], eax
 * 000C6D0A: 8D 45 EF                 lea     eax, [ebp+var_11]
 * 000C6D0D: 89 44 24 0C              mov     [esp+34h+var_28], eax
 * 000C6D11: E8 AE EF FF FF           call    token_dispatch
 * 000C6D16: 66 89 45 FE              mov     [ebp+var_2], ax
 * 000C6D1A: 66 23 C0                 and     ax, ax
 * 000C6D1D: 74 05                    jz      short loc_C6D24
 * 000C6D1F: EB 53                    jmp     short loc_C6D74
 * 000C6D21: 90 90 90                 align 4
 * 000C6D24: 89 3C 24                 mov     [esp+34h+var_34], edi
 * 000C6D27: 8D 45 F0                 lea     eax, [ebp+var_10]
 * 000C6D2A: 89 44 24 04              mov     [esp+34h+var_30], eax
 * 000C6D2E: E8 29 78 00 00           call    strcpy
 * 000C6D33: 33 C0                    xor     eax, eax
 * 000C6D35: 8A 45 EF                 mov     al, [ebp+var_11]
 * 000C6D38: 03 C7                    add     eax, edi
 * 000C6D3A: 89 45 14                 mov     [ebp+arg_C], eax
 * 000C6D3D: 66 8B 15 3C F1 00 00     mov     dx, word ptr ds:loc_F13A+2
 * 000C6D44: 66 89 10                 mov     [eax], dx
 * 000C6D47: 40                       inc     eax
 * 000C6D48: 83 C6 07                 add     esi, 7
 * 000C6D4B: 89 45 14                 mov     [ebp+arg_C], eax
 * 000C6D4E: 8A 4D 08                 mov     cl, [ebp+arg_0]
 * 000C6D51: 89 0C 24                 mov     [esp+34h+var_34], ecx
 * 000C6D54: 89 5C 24 04              mov     [esp+34h+var_30], ebx
 * 000C6D58: 89 74 24 08              mov     [esp+34h+var_2C], esi
 * 000C6D5C: 89 44 24 0C              mov     [esp+34h+var_28], eax
 * 000C6D60: E8 AF 0E 00 00           call    fn_C7C14
 * 000C6D65: 66 89 45 FE              mov     [ebp+var_2], ax
 * 000C6D69: 66 23 C0                 and     ax, ax
 * 000C6D6C: 74 06                    jz      short loc_C6D74
 * 000C6D6E: EB 04                    jmp     short loc_C6D74
 * 000C6D70: 90 90 90 90              db 4 dup(90h)
 * 000C6D74: 8B 5D DC                 mov     ebx, [ebp+var_24]
 * 000C6D77: 8B 75 E0                 mov     esi, [ebp+var_20]
 * 000C6D7A: 8B 7D E4                 mov     edi, [ebp+var_1C]
 * 000C6D7D: 89 EC                    mov     esp, ebp
 * 000C6D7F: 5D                       pop     ebp
 * 000C6D80: C3                       retn
 * ========================================================================== */
// [SRX-611] pop_rank=333/1298, sites=2, callers=2, callees=4, size=0xD5
int __usercall util_C6CAC@<eax>(__int16 a1@<ax>, char a2, int a3, int a4, int a5)
{
  char *v5; // edi
  int result; // eax
  char *v7; // eax
  int v8; // ecx
  unsigned __int8 v9; // [esp+23h] [ebp-11h] BYREF
  char v10[14]; // [esp+24h] [ebp-10h] BYREF
  __int16 v11; // [esp+32h] [ebp-2h]

  v11 = 0;
  *(_WORD *)a5 = -28528;
  LOBYTE(a1) = *(_BYTE *)(a4 + 2);
  util_61DBC(a1, a1, 3u, (_BYTE *)(a5 + 1));
  *(_BYTE *)(a5 + 4) = 40;
  v5 = (char *)(a5 + 5);
  result = token_dispatch(a3, a4 + 4, v10, &v9);
  v11 = result;
  if ( !(_WORD)result )
  {
    strcpy(v5, v10);
    v7 = &v5[v9];
    *(_WORD *)v7 = *(&loc_F13A + 1);
    LOBYTE(v8) = a2;
    return fn_C7C14(v8, a3, a4 + 7, v7 + 1);
  }
  return result;
}


/* ============================================================================
 * util_C6D84  @ 0xC6D84   size=0xD5   callers=2
 * note: [SRX-611] pop_rank=334/1298, sites=2, callers=2, callees=4, size=0xD5
 * --- original assembly (address: bytes  mnemonic) ---------------------------
 * 000C6D84: 55                       push    ebp
 * 000C6D85: 89 E5                    mov     ebp, esp
 * 000C6D87: 83 EC 18                 sub     esp, 18h
 * 000C6D8A: 66 C7 45 FE 00 00        mov     [ebp+var_2], 0
 * 000C6D90: 66 8B 15 4C F1 00 00     mov     dx, word ptr ds:loc_F14C
 * 000C6D97: 57                       push    edi
 * 000C6D98: 56                       push    esi
 * 000C6D99: 53                       push    ebx
 * 000C6D9A: 83 EC 10                 sub     esp, 10h
 * 000C6D9D: 8B 7D 14                 mov     edi, [ebp+arg_C]
 * 000C6DA0: 66 89 17                 mov     [edi], dx
 * 000C6DA3: 8B 75 10                 mov     esi, [ebp+arg_8]
 * 000C6DA6: 47                       inc     edi
 * 000C6DA7: 89 7D 14                 mov     [ebp+arg_C], edi
 * 000C6DAA: 8A 46 02                 mov     al, [esi+2]
 * 000C6DAD: 89 04 24                 mov     [esp+34h+var_34], eax
 * 000C6DB0: C7 44 24 04 03 00 00 00  mov     [esp+34h+var_30], 3
 * 000C6DB8: 89 7C 24 08              mov     [esp+34h+var_2C], edi
 * 000C6DBC: E8 FB AF F9 FF           call    util_61DBC
 * 000C6DC1: 83 C7 03                 add     edi, 3
 * 000C6DC4: 89 7D 14                 mov     [ebp+arg_C], edi
 * 000C6DC7: C6 07 28                 mov     byte ptr [edi], 28h ; '('
 * 000C6DCA: 47                       inc     edi
 * 000C6DCB: 89 7D 14                 mov     [ebp+arg_C], edi
 * 000C6DCE: 8B 5D 0C                 mov     ebx, [ebp+arg_4]
 * 000C6DD1: 89 1C 24                 mov     [esp+34h+var_34], ebx
 * 000C6DD4: 8D 46 04                 lea     eax, [esi+4]
 * 000C6DD7: 89 44 24 04              mov     [esp+34h+var_30], eax
 * 000C6DDB: 8D 45 F0                 lea     eax, [ebp+var_10]
 * 000C6DDE: 89 44 24 08              mov     [esp+34h+var_2C], eax
 * 000C6DE2: 8D 45 EF                 lea     eax, [ebp+var_11]
 * 000C6DE5: 89 44 24 0C              mov     [esp+34h+var_28], eax
 * 000C6DE9: E8 D6 EE FF FF           call    token_dispatch
 * 000C6DEE: 66 89 45 FE              mov     [ebp+var_2], ax
 * 000C6DF2: 66 23 C0                 and     ax, ax
 * 000C6DF5: 74 05                    jz      short loc_C6DFC
 * 000C6DF7: EB 53                    jmp     short loc_C6E4C
 * 000C6DF9: 90 90 90                 align 4
 * 000C6DFC: 89 3C 24                 mov     [esp+34h+var_34], edi
 * 000C6DFF: 8D 45 F0                 lea     eax, [ebp+var_10]
 * 000C6E02: 89 44 24 04              mov     [esp+34h+var_30], eax
 * 000C6E06: E8 51 77 00 00           call    strcpy
 * 000C6E0B: 33 C0                    xor     eax, eax
 * 000C6E0D: 8A 45 EF                 mov     al, [ebp+var_11]
 * 000C6E10: 03 C7                    add     eax, edi
 * 000C6E12: 89 45 14                 mov     [ebp+arg_C], eax
 * 000C6E15: 66 8B 15 3C F1 00 00     mov     dx, word ptr ds:loc_F13A+2
 * 000C6E1C: 66 89 10                 mov     [eax], dx
 * 000C6E1F: 40                       inc     eax
 * 000C6E20: 83 C6 07                 add     esi, 7
 * 000C6E23: 89 45 14                 mov     [ebp+arg_C], eax
 * 000C6E26: 8A 4D 08                 mov     cl, [ebp+arg_0]
 * 000C6E29: 89 0C 24                 mov     [esp+34h+var_34], ecx
 * 000C6E2C: 89 5C 24 04              mov     [esp+34h+var_30], ebx
 * 000C6E30: 89 74 24 08              mov     [esp+34h+var_2C], esi
 * 000C6E34: 89 44 24 0C              mov     [esp+34h+var_28], eax
 * 000C6E38: E8 D7 0D 00 00           call    fn_C7C14
 * 000C6E3D: 66 89 45 FE              mov     [ebp+var_2], ax
 * 000C6E41: 66 23 C0                 and     ax, ax
 * 000C6E44: 74 06                    jz      short loc_C6E4C
 * 000C6E46: EB 04                    jmp     short loc_C6E4C
 * 000C6E48: 90 90 90 90              db 4 dup(90h)
 * 000C6E4C: 8B 5D DC                 mov     ebx, [ebp+var_24]
 * 000C6E4F: 8B 75 E0                 mov     esi, [ebp+var_20]
 * 000C6E52: 8B 7D E4                 mov     edi, [ebp+var_1C]
 * 000C6E55: 89 EC                    mov     esp, ebp
 * 000C6E57: 5D                       pop     ebp
 * 000C6E58: C3                       retn
 * ========================================================================== */
// [SRX-611] pop_rank=334/1298, sites=2, callers=2, callees=4, size=0xD5
int __usercall util_C6D84@<eax>(__int16 a1@<ax>, char a2, int a3, int a4, int a5)
{
  char *v5; // edi
  int result; // eax
  char *v7; // eax
  int v8; // ecx
  unsigned __int8 v9; // [esp+23h] [ebp-11h] BYREF
  char v10[14]; // [esp+24h] [ebp-10h] BYREF
  __int16 v11; // [esp+32h] [ebp-2h]

  v11 = 0;
  *(_WORD *)a5 = loc_F14C;
  LOBYTE(a1) = *(_BYTE *)(a4 + 2);
  util_61DBC(a1, a1, 3u, (_BYTE *)(a5 + 1));
  *(_BYTE *)(a5 + 4) = 40;
  v5 = (char *)(a5 + 5);
  result = token_dispatch(a3, a4 + 4, v10, &v9);
  v11 = result;
  if ( !(_WORD)result )
  {
    strcpy(v5, v10);
    v7 = &v5[v9];
    *(_WORD *)v7 = *(&loc_F13A + 1);
    LOBYTE(v8) = a2;
    return fn_C7C14(v8, a3, a4 + 7, v7 + 1);
  }
  return result;
}


/* ============================================================================
 * util_C6E5C  @ 0xC6E5C   size=0x105   callers=2
 * note: [SRX-611] pop_rank=322/1298, sites=2, callers=2, callees=3, size=0x105
 * --- original assembly (address: bytes  mnemonic) ---------------------------
 * 000C6E5C: 55                       push    ebp
 * 000C6E5D: 89 E5                    mov     ebp, esp
 * 000C6E5F: 83 EC 18                 sub     esp, 18h
 * 000C6E62: 8B 15 50 F1 00 00        mov     edx, dword ptr ds:loc_F14C+4
 * 000C6E68: 66 C7 45 FE 00 00        mov     [ebp+var_2], 0
 * 000C6E6E: 57                       push    edi
 * 000C6E6F: 56                       push    esi
 * 000C6E70: 8B 75 14                 mov     esi, [ebp+arg_C]
 * 000C6E73: 89 16                    mov     [esi], edx
 * 000C6E75: 53                       push    ebx
 * 000C6E76: 83 EC 10                 sub     esp, 10h
 * 000C6E79: 8A 15 54 F1 00 00        mov     dl, byte ptr ds:loc_F153+1
 * 000C6E7F: 88 56 04                 mov     [esi+4], dl
 * 000C6E82: 83 C6 04                 add     esi, 4
 * 000C6E85: 8B 5D 0C                 mov     ebx, [ebp+arg_4]
 * 000C6E88: 89 75 14                 mov     [ebp+arg_C], esi
 * 000C6E8B: 89 1C 24                 mov     [esp+34h+var_34], ebx
 * 000C6E8E: 8B 45 10                 mov     eax, [ebp+arg_8]
 * 000C6E91: 40                       inc     eax
 * 000C6E92: 89 44 24 04              mov     [esp+34h+var_30], eax
 * 000C6E96: 8D 7D F0                 lea     edi, [ebp+var_10]
 * 000C6E99: 89 7C 24 08              mov     [esp+34h+var_2C], edi
 * 000C6E9D: 8D 45 EF                 lea     eax, [ebp+var_11]
 * 000C6EA0: 89 44 24 0C              mov     [esp+34h+var_28], eax
 * 000C6EA4: E8 1B EE FF FF           call    token_dispatch
 * 000C6EA9: 66 89 45 FE              mov     [ebp+var_2], ax
 * 000C6EAD: 66 23 C0                 and     ax, ax
 * 000C6EB0: 74 0A                    jz      short loc_C6EBC
 * 000C6EB2: E9 9D 00 00 00           jmp     loc_C6F54
 * 000C6EB7: 90 90 90 90 90           db 5 dup(90h)
 * 000C6EBC: 89 34 24                 mov     [esp+34h+var_34], esi
 * 000C6EBF: 89 7C 24 04              mov     [esp+34h+var_30], edi
 * 000C6EC3: E8 94 76 00 00           call    strcpy
 * 000C6EC8: 33 C0                    xor     eax, eax
 * 000C6ECA: 8A 45 EF                 mov     al, [ebp+var_11]
 * 000C6ECD: 03 C6                    add     eax, esi
 * 000C6ECF: 89 45 14                 mov     [ebp+arg_C], eax
 * 000C6ED2: C6 00 2C                 mov     byte ptr [eax], 2Ch ; ','
 * 000C6ED5: 8D 70 01                 lea     esi, [eax+1]
 * 000C6ED8: 89 75 14                 mov     [ebp+arg_C], esi
 * 000C6EDB: 89 1C 24                 mov     [esp+34h+var_34], ebx
 * 000C6EDE: 8B 45 10                 mov     eax, [ebp+arg_8]
 * 000C6EE1: 83 C0 04                 add     eax, 4
 * 000C6EE4: 89 7C 24 08              mov     [esp+34h+var_2C], edi
 * 000C6EE8: 89 44 24 04              mov     [esp+34h+var_30], eax
 * 000C6EEC: 8D 45 EF                 lea     eax, [ebp+var_11]
 * 000C6EEF: 89 44 24 0C              mov     [esp+34h+var_28], eax
 * 000C6EF3: E8 CC ED FF FF           call    token_dispatch
 * 000C6EF8: 66 89 45 FE              mov     [ebp+var_2], ax
 * 000C6EFC: 66 23 C0                 and     ax, ax
 * 000C6EFF: 74 03                    jz      short loc_C6F04
 * 000C6F01: EB 51                    jmp     short loc_C6F54
 * 000C6F03: 90                       align 4
 * 000C6F04: 89 34 24                 mov     [esp+34h+var_34], esi
 * 000C6F07: 89 7C 24 04              mov     [esp+34h+var_30], edi
 * 000C6F0B: E8 4C 76 00 00           call    strcpy
 * 000C6F10: 33 C0                    xor     eax, eax
 * 000C6F12: 8A 45 EF                 mov     al, [ebp+var_11]
 * 000C6F15: 03 C6                    add     eax, esi
 * 000C6F17: 89 45 14                 mov     [ebp+arg_C], eax
 * 000C6F1A: 66 8B 15 3C F1 00 00     mov     dx, word ptr ds:loc_F13A+2
 * 000C6F21: 66 89 10                 mov     [eax], dx
 * 000C6F24: 40                       inc     eax
 * 000C6F25: 8A 4D 08                 mov     cl, [ebp+arg_0]
 * 000C6F28: 89 45 14                 mov     [ebp+arg_C], eax
 * 000C6F2B: 89 0C 24                 mov     [esp+34h+var_34], ecx
 * 000C6F2E: 89 5C 24 04              mov     [esp+34h+var_30], ebx
 * 000C6F32: 8B 4D 10                 mov     ecx, [ebp+arg_8]
 * 000C6F35: 83 C1 07                 add     ecx, 7
 * 000C6F38: 89 44 24 0C              mov     [esp+34h+var_28], eax
 * 000C6F3C: 89 4C 24 08              mov     [esp+34h+var_2C], ecx
 * 000C6F40: E8 CF 0C 00 00           call    fn_C7C14
 * 000C6F45: 66 89 45 FE              mov     [ebp+var_2], ax
 * 000C6F49: 66 23 C0                 and     ax, ax
 * 000C6F4C: 74 06                    jz      short loc_C6F54
 * 000C6F4E: EB 04                    jmp     short loc_C6F54
 * 000C6F50: 90 90 90 90              db 4 dup(90h)
 * 000C6F54: 8B 5D DC                 mov     ebx, [ebp+var_24]
 * 000C6F57: 8B 75 E0                 mov     esi, [ebp+var_20]
 * 000C6F5A: 8B 7D E4                 mov     edi, [ebp+var_1C]
 * 000C6F5D: 89 EC                    mov     esp, ebp
 * 000C6F5F: 5D                       pop     ebp
 * 000C6F60: C3                       retn
 * ========================================================================== */
// [SRX-611] pop_rank=322/1298, sites=2, callers=2, callees=3, size=0x105
int __cdecl util_C6E5C(char a1, int a2, int a3, int a4)
{
  char *v4; // esi
  int result; // eax
  char *v6; // eax
  char *v7; // esi
  char *v8; // eax
  int v9; // ecx
  unsigned __int8 v10; // [esp+23h] [ebp-11h] BYREF
  char v11[14]; // [esp+24h] [ebp-10h] BYREF
  __int16 v12; // [esp+32h] [ebp-2h]

  v12 = 0;
  *(_DWORD *)a4 = *(&loc_F14C + 1);
  *(_BYTE *)(a4 + 4) = *(&loc_F153 + 1);
  v4 = (char *)(a4 + 4);
  result = token_dispatch(a2, a3 + 1, v11, &v10);
  v12 = result;
  if ( !(_WORD)result )
  {
    strcpy(v4, v11);
    v6 = &v4[v10];
    *v6 = 44;
    v7 = v6 + 1;
    result = token_dispatch(a2, a3 + 4, v11, &v10);
    v12 = result;
    if ( !(_WORD)result )
    {
      strcpy(v7, v11);
      v8 = &v7[v10];
      *(_WORD *)v8 = *(&loc_F13A + 1);
      LOBYTE(v9) = a1;
      return fn_C7C14(v9, a2, a3 + 7, v8 + 1);
    }
  }
  return result;
}


/* ============================================================================
 * util_C6F64  @ 0xC6F64   size=0x105   callers=2
 * note: [SRX-611] pop_rank=323/1298, sites=2, callers=2, callees=3, size=0x105
 * --- original assembly (address: bytes  mnemonic) ---------------------------
 * 000C6F64: 55                       push    ebp
 * 000C6F65: 89 E5                    mov     ebp, esp
 * 000C6F67: 83 EC 18                 sub     esp, 18h
 * 000C6F6A: 8B 15 58 F1 00 00        mov     edx, dword ptr ds:loc_F157+1
 * 000C6F70: 66 C7 45 FE 00 00        mov     [ebp+var_2], 0
 * 000C6F76: 57                       push    edi
 * 000C6F77: 56                       push    esi
 * 000C6F78: 8B 75 14                 mov     esi, [ebp+arg_C]
 * 000C6F7B: 89 16                    mov     [esi], edx
 * 000C6F7D: 53                       push    ebx
 * 000C6F7E: 83 EC 10                 sub     esp, 10h
 * 000C6F81: 8A 15 5C F1 00 00        mov     dl, byte ptr ds:loc_F15C
 * 000C6F87: 88 56 04                 mov     [esi+4], dl
 * 000C6F8A: 83 C6 04                 add     esi, 4
 * 000C6F8D: 8B 5D 0C                 mov     ebx, [ebp+arg_4]
 * 000C6F90: 89 75 14                 mov     [ebp+arg_C], esi
 * 000C6F93: 89 1C 24                 mov     [esp+34h+var_34], ebx
 * 000C6F96: 8B 45 10                 mov     eax, [ebp+arg_8]
 * 000C6F99: 40                       inc     eax
 * 000C6F9A: 89 44 24 04              mov     [esp+34h+var_30], eax
 * 000C6F9E: 8D 7D F0                 lea     edi, [ebp+var_10]
 * 000C6FA1: 89 7C 24 08              mov     [esp+34h+var_2C], edi
 * 000C6FA5: 8D 45 EF                 lea     eax, [ebp+var_11]
 * 000C6FA8: 89 44 24 0C              mov     [esp+34h+var_28], eax
 * 000C6FAC: E8 13 ED FF FF           call    token_dispatch
 * 000C6FB1: 66 89 45 FE              mov     [ebp+var_2], ax
 * 000C6FB5: 66 23 C0                 and     ax, ax
 * 000C6FB8: 74 0A                    jz      short loc_C6FC4
 * 000C6FBA: E9 9D 00 00 00           jmp     loc_C705C
 * 000C6FBF: 90 90 90 90 90           db 5 dup(90h)
 * 000C6FC4: 89 34 24                 mov     [esp+34h+var_34], esi
 * 000C6FC7: 89 7C 24 04              mov     [esp+34h+var_30], edi
 * 000C6FCB: E8 8C 75 00 00           call    strcpy
 * 000C6FD0: 33 C0                    xor     eax, eax
 * 000C6FD2: 8A 45 EF                 mov     al, [ebp+var_11]
 * 000C6FD5: 03 C6                    add     eax, esi
 * 000C6FD7: 89 45 14                 mov     [ebp+arg_C], eax
 * 000C6FDA: C6 00 2C                 mov     byte ptr [eax], 2Ch ; ','
 * 000C6FDD: 8D 70 01                 lea     esi, [eax+1]
 * 000C6FE0: 89 75 14                 mov     [ebp+arg_C], esi
 * 000C6FE3: 89 1C 24                 mov     [esp+34h+var_34], ebx
 * 000C6FE6: 8B 45 10                 mov     eax, [ebp+arg_8]
 * 000C6FE9: 83 C0 04                 add     eax, 4
 * 000C6FEC: 89 7C 24 08              mov     [esp+34h+var_2C], edi
 * 000C6FF0: 89 44 24 04              mov     [esp+34h+var_30], eax
 * 000C6FF4: 8D 45 EF                 lea     eax, [ebp+var_11]
 * 000C6FF7: 89 44 24 0C              mov     [esp+34h+var_28], eax
 * 000C6FFB: E8 C4 EC FF FF           call    token_dispatch
 * 000C7000: 66 89 45 FE              mov     [ebp+var_2], ax
 * 000C7004: 66 23 C0                 and     ax, ax
 * 000C7007: 74 03                    jz      short loc_C700C
 * 000C7009: EB 51                    jmp     short loc_C705C
 * 000C700B: 90                       align 4
 * 000C700C: 89 34 24                 mov     [esp+34h+var_34], esi
 * 000C700F: 89 7C 24 04              mov     [esp+34h+var_30], edi
 * 000C7013: E8 44 75 00 00           call    strcpy
 * 000C7018: 33 C0                    xor     eax, eax
 * 000C701A: 8A 45 EF                 mov     al, [ebp+var_11]
 * 000C701D: 03 C6                    add     eax, esi
 * 000C701F: 89 45 14                 mov     [ebp+arg_C], eax
 * 000C7022: 66 8B 15 3C F1 00 00     mov     dx, word ptr ds:loc_F13A+2
 * 000C7029: 66 89 10                 mov     [eax], dx
 * 000C702C: 40                       inc     eax
 * 000C702D: 8A 4D 08                 mov     cl, [ebp+arg_0]
 * 000C7030: 89 45 14                 mov     [ebp+arg_C], eax
 * 000C7033: 89 0C 24                 mov     [esp+34h+var_34], ecx
 * 000C7036: 89 5C 24 04              mov     [esp+34h+var_30], ebx
 * 000C703A: 8B 4D 10                 mov     ecx, [ebp+arg_8]
 * 000C703D: 83 C1 07                 add     ecx, 7
 * 000C7040: 89 44 24 0C              mov     [esp+34h+var_28], eax
 * 000C7044: 89 4C 24 08              mov     [esp+34h+var_2C], ecx
 * 000C7048: E8 C7 0B 00 00           call    fn_C7C14
 * 000C704D: 66 89 45 FE              mov     [ebp+var_2], ax
 * 000C7051: 66 23 C0                 and     ax, ax
 * 000C7054: 74 06                    jz      short loc_C705C
 * 000C7056: EB 04                    jmp     short loc_C705C
 * 000C7058: 90 90 90 90              db 4 dup(90h)
 * 000C705C: 8B 5D DC                 mov     ebx, [ebp+var_24]
 * 000C705F: 8B 75 E0                 mov     esi, [ebp+var_20]
 * 000C7062: 8B 7D E4                 mov     edi, [ebp+var_1C]
 * 000C7065: 89 EC                    mov     esp, ebp
 * 000C7067: 5D                       pop     ebp
 * 000C7068: C3                       retn
 * ========================================================================== */
// [SRX-611] pop_rank=323/1298, sites=2, callers=2, callees=3, size=0x105
int __cdecl util_C6F64(char a1, int a2, int a3, int a4)
{
  char *v4; // esi
  int result; // eax
  char *v6; // eax
  char *v7; // esi
  char *v8; // eax
  int v9; // ecx
  unsigned __int8 v10; // [esp+23h] [ebp-11h] BYREF
  char v11[14]; // [esp+24h] [ebp-10h] BYREF
  __int16 v12; // [esp+32h] [ebp-2h]

  v12 = 0;
  *(_DWORD *)a4 = *(_DWORD *)((char *)&loc_F157 + 1);
  *(_BYTE *)(a4 + 4) = loc_F15C;
  v4 = (char *)(a4 + 4);
  result = token_dispatch(a2, a3 + 1, v11, &v10);
  v12 = result;
  if ( !(_WORD)result )
  {
    strcpy(v4, v11);
    v6 = &v4[v10];
    *v6 = 44;
    v7 = v6 + 1;
    result = token_dispatch(a2, a3 + 4, v11, &v10);
    v12 = result;
    if ( !(_WORD)result )
    {
      strcpy(v7, v11);
      v8 = &v7[v10];
      *(_WORD *)v8 = *(&loc_F13A + 1);
      LOBYTE(v9) = a1;
      return fn_C7C14(v9, a2, a3 + 7, v8 + 1);
    }
  }
  return result;
}


/* ============================================================================
 * util_C706C  @ 0xC706C   size=0xBD   callers=2
 * note: [SRX-611] pop_rank=341/1298, sites=2, callers=2, callees=3, size=0xBD
 * --- original assembly (address: bytes  mnemonic) ---------------------------
 * 000C706C: 55                       push    ebp
 * 000C706D: 89 E5                    mov     ebp, esp
 * 000C706F: 83 EC 18                 sub     esp, 18h
 * 000C7072: 66 C7 45 FE 00 00        mov     [ebp+var_2], 0
 * 000C7078: 8B 15 60 F1 00 00        mov     edx, dword ptr ds:loc_F15F+1
 * 000C707E: 57                       push    edi
 * 000C707F: 56                       push    esi
 * 000C7080: 8B 75 14                 mov     esi, [ebp+arg_C]
 * 000C7083: 89 16                    mov     [esi], edx
 * 000C7085: 53                       push    ebx
 * 000C7086: 83 EC 10                 sub     esp, 10h
 * 000C7089: 8A 15 64 F1 00 00        mov     dl, byte ptr ds:loc_F162+2
 * 000C708F: 88 56 04                 mov     [esi+4], dl
 * 000C7092: 83 C6 04                 add     esi, 4
 * 000C7095: 8B 5D 0C                 mov     ebx, [ebp+arg_4]
 * 000C7098: 89 75 14                 mov     [ebp+arg_C], esi
 * 000C709B: 89 1C 24                 mov     [esp+34h+var_34], ebx
 * 000C709E: 8B 7D 10                 mov     edi, [ebp+arg_8]
 * 000C70A1: 8D 47 01                 lea     eax, [edi+1]
 * 000C70A4: 89 44 24 04              mov     [esp+34h+var_30], eax
 * 000C70A8: 8D 45 F0                 lea     eax, [ebp+var_10]
 * 000C70AB: 89 44 24 08              mov     [esp+34h+var_2C], eax
 * 000C70AF: 8D 45 EF                 lea     eax, [ebp+var_11]
 * 000C70B2: 89 44 24 0C              mov     [esp+34h+var_28], eax
 * 000C70B6: E8 09 EC FF FF           call    token_dispatch
 * 000C70BB: 66 89 45 FE              mov     [ebp+var_2], ax
 * 000C70BF: 66 23 C0                 and     ax, ax
 * 000C70C2: 74 08                    jz      short loc_C70CC
 * 000C70C4: EB 56                    jmp     short loc_C711C
 * 000C70C6: 90 90 90 90 90 90        db 6 dup(90h)
 * 000C70CC: 89 34 24                 mov     [esp+34h+var_34], esi
 * 000C70CF: 8D 45 F0                 lea     eax, [ebp+var_10]
 * 000C70D2: 89 44 24 04              mov     [esp+34h+var_30], eax
 * 000C70D6: E8 81 74 00 00           call    strcpy
 * 000C70DB: 33 C0                    xor     eax, eax
 * 000C70DD: 8A 45 EF                 mov     al, [ebp+var_11]
 * 000C70E0: 03 C6                    add     eax, esi
 * 000C70E2: 89 45 14                 mov     [ebp+arg_C], eax
 * 000C70E5: 66 8B 15 3C F1 00 00     mov     dx, word ptr ds:loc_F13A+2
 * 000C70EC: 66 89 10                 mov     [eax], dx
 * 000C70EF: 40                       inc     eax
 * 000C70F0: 83 C7 04                 add     edi, 4
 * 000C70F3: 89 45 14                 mov     [ebp+arg_C], eax
 * 000C70F6: 8A 4D 08                 mov     cl, [ebp+arg_0]
 * 000C70F9: 89 0C 24                 mov     [esp+34h+var_34], ecx
 * 000C70FC: 89 5C 24 04              mov     [esp+34h+var_30], ebx
 * 000C7100: 89 7C 24 08              mov     [esp+34h+var_2C], edi
 * 000C7104: 89 44 24 0C              mov     [esp+34h+var_28], eax
 * 000C7108: E8 07 0B 00 00           call    fn_C7C14
 * 000C710D: 66 89 45 FE              mov     [ebp+var_2], ax
 * 000C7111: 66 23 C0                 and     ax, ax
 * 000C7114: 74 06                    jz      short loc_C711C
 * 000C7116: EB 04                    jmp     short loc_C711C
 * 000C7118: 90 90 90 90              db 4 dup(90h)
 * 000C711C: 8B 5D DC                 mov     ebx, [ebp+var_24]
 * 000C711F: 8B 75 E0                 mov     esi, [ebp+var_20]
 * 000C7122: 8B 7D E4                 mov     edi, [ebp+var_1C]
 * 000C7125: 89 EC                    mov     esp, ebp
 * 000C7127: 5D                       pop     ebp
 * 000C7128: C3                       retn
 * ========================================================================== */
// [SRX-611] pop_rank=341/1298, sites=2, callers=2, callees=3, size=0xBD
int __cdecl util_C706C(char a1, int a2, int a3, int a4)
{
  char *v4; // esi
  int result; // eax
  char *v6; // eax
  int v7; // ecx
  unsigned __int8 v8; // [esp+23h] [ebp-11h] BYREF
  char v9[14]; // [esp+24h] [ebp-10h] BYREF
  __int16 v10; // [esp+32h] [ebp-2h]

  v10 = 0;
  *(_DWORD *)a4 = *(_DWORD *)((char *)&loc_F15F + 1);
  *(_BYTE *)(a4 + 4) = *(&loc_F162 + 2);
  v4 = (char *)(a4 + 4);
  result = token_dispatch(a2, a3 + 1, v9, &v8);
  v10 = result;
  if ( !(_WORD)result )
  {
    strcpy(v4, v9);
    v6 = &v4[v8];
    *(_WORD *)v6 = *(&loc_F13A + 1);
    LOBYTE(v7) = a1;
    return fn_C7C14(v7, a2, a3 + 4, v6 + 1);
  }
  return result;
}


/* ============================================================================
 * util_C712C  @ 0xC712C   size=0xBD   callers=2
 * note: [SRX-611] pop_rank=342/1298, sites=2, callers=2, callees=3, size=0xBD
 * --- original assembly (address: bytes  mnemonic) ---------------------------
 * 000C712C: 55                       push    ebp
 * 000C712D: 89 E5                    mov     ebp, esp
 * 000C712F: 83 EC 18                 sub     esp, 18h
 * 000C7132: 66 C7 45 FE 00 00        mov     [ebp+var_2], 0
 * 000C7138: 8B 15 68 F1 00 00        mov     edx, dword ptr ds:loc_F167+1
 * 000C713E: 57                       push    edi
 * 000C713F: 56                       push    esi
 * 000C7140: 8B 75 14                 mov     esi, [ebp+arg_C]
 * 000C7143: 89 16                    mov     [esi], edx
 * 000C7145: 53                       push    ebx
 * 000C7146: 83 EC 10                 sub     esp, 10h
 * 000C7149: 8A 15 6C F1 00 00        mov     dl, byte ptr ds:loc_F16A+2
 * 000C714F: 88 56 04                 mov     [esi+4], dl
 * 000C7152: 83 C6 04                 add     esi, 4
 * 000C7155: 8B 5D 0C                 mov     ebx, [ebp+arg_4]
 * 000C7158: 89 75 14                 mov     [ebp+arg_C], esi
 * 000C715B: 89 1C 24                 mov     [esp+34h+var_34], ebx
 * 000C715E: 8B 7D 10                 mov     edi, [ebp+arg_8]
 * 000C7161: 8D 47 01                 lea     eax, [edi+1]
 * 000C7164: 89 44 24 04              mov     [esp+34h+var_30], eax
 * 000C7168: 8D 45 F0                 lea     eax, [ebp+var_10]
 * 000C716B: 89 44 24 08              mov     [esp+34h+var_2C], eax
 * 000C716F: 8D 45 EF                 lea     eax, [ebp+var_11]
 * 000C7172: 89 44 24 0C              mov     [esp+34h+var_28], eax
 * 000C7176: E8 49 EB FF FF           call    token_dispatch
 * 000C717B: 66 89 45 FE              mov     [ebp+var_2], ax
 * 000C717F: 66 23 C0                 and     ax, ax
 * 000C7182: 74 08                    jz      short loc_C718C
 * 000C7184: EB 56                    jmp     short loc_C71DC
 * 000C7186: 90 90 90 90 90 90        db 6 dup(90h)
 * 000C718C: 89 34 24                 mov     [esp+34h+var_34], esi
 * 000C718F: 8D 45 F0                 lea     eax, [ebp+var_10]
 * 000C7192: 89 44 24 04              mov     [esp+34h+var_30], eax
 * 000C7196: E8 C1 73 00 00           call    strcpy
 * 000C719B: 33 C0                    xor     eax, eax
 * 000C719D: 8A 45 EF                 mov     al, [ebp+var_11]
 * 000C71A0: 03 C6                    add     eax, esi
 * 000C71A2: 89 45 14                 mov     [ebp+arg_C], eax
 * 000C71A5: 66 8B 15 3C F1 00 00     mov     dx, word ptr ds:loc_F13A+2
 * 000C71AC: 66 89 10                 mov     [eax], dx
 * 000C71AF: 40                       inc     eax
 * 000C71B0: 83 C7 04                 add     edi, 4
 * 000C71B3: 89 45 14                 mov     [ebp+arg_C], eax
 * 000C71B6: 8A 4D 08                 mov     cl, [ebp+arg_0]
 * 000C71B9: 89 0C 24                 mov     [esp+34h+var_34], ecx
 * 000C71BC: 89 5C 24 04              mov     [esp+34h+var_30], ebx
 * 000C71C0: 89 7C 24 08              mov     [esp+34h+var_2C], edi
 * 000C71C4: 89 44 24 0C              mov     [esp+34h+var_28], eax
 * 000C71C8: E8 47 0A 00 00           call    fn_C7C14
 * 000C71CD: 66 89 45 FE              mov     [ebp+var_2], ax
 * 000C71D1: 66 23 C0                 and     ax, ax
 * 000C71D4: 74 06                    jz      short loc_C71DC
 * 000C71D6: EB 04                    jmp     short loc_C71DC
 * 000C71D8: 90 90 90 90              db 4 dup(90h)
 * 000C71DC: 8B 5D DC                 mov     ebx, [ebp+var_24]
 * 000C71DF: 8B 75 E0                 mov     esi, [ebp+var_20]
 * 000C71E2: 8B 7D E4                 mov     edi, [ebp+var_1C]
 * 000C71E5: 89 EC                    mov     esp, ebp
 * 000C71E7: 5D                       pop     ebp
 * 000C71E8: C3                       retn
 * ========================================================================== */
// [SRX-611] pop_rank=342/1298, sites=2, callers=2, callees=3, size=0xBD
int __cdecl util_C712C(char a1, int a2, int a3, int a4)
{
  char *v4; // esi
  int result; // eax
  char *v6; // eax
  int v7; // ecx
  unsigned __int8 v8; // [esp+23h] [ebp-11h] BYREF
  char v9[14]; // [esp+24h] [ebp-10h] BYREF
  __int16 v10; // [esp+32h] [ebp-2h]

  v10 = 0;
  *(_DWORD *)a4 = *(_DWORD *)((char *)&loc_F167 + 1);
  *(_BYTE *)(a4 + 4) = *(&loc_F16A + 2);
  v4 = (char *)(a4 + 4);
  result = token_dispatch(a2, a3 + 1, v9, &v8);
  v10 = result;
  if ( !(_WORD)result )
  {
    strcpy(v4, v9);
    v6 = &v4[v8];
    *(_WORD *)v6 = *(&loc_F13A + 1);
    LOBYTE(v7) = a1;
    return fn_C7C14(v7, a2, a3 + 4, v6 + 1);
  }
  return result;
}


/* ============================================================================
 * util_C71EC  @ 0xC71EC   size=0xBD   callers=2
 * note: [SRX-611] pop_rank=343/1298, sites=2, callers=2, callees=3, size=0xBD
 * --- original assembly (address: bytes  mnemonic) ---------------------------
 * 000C71EC: 55                       push    ebp
 * 000C71ED: 89 E5                    mov     ebp, esp
 * 000C71EF: 83 EC 18                 sub     esp, 18h
 * 000C71F2: 66 C7 45 FE 00 00        mov     [ebp+var_2], 0
 * 000C71F8: 8B 15 70 F1 00 00        mov     edx, dword ptr ds:loc_F16A+6
 * 000C71FE: 57                       push    edi
 * 000C71FF: 56                       push    esi
 * 000C7200: 8B 75 14                 mov     esi, [ebp+arg_C]
 * 000C7203: 89 16                    mov     [esi], edx
 * 000C7205: 53                       push    ebx
 * 000C7206: 83 EC 10                 sub     esp, 10h
 * 000C7209: 66 8B 15 74 F1 00 00     mov     dx, word ptr ds:loc_F174
 * 000C7210: 66 89 56 04              mov     [esi+4], dx
 * 000C7214: 83 C6 05                 add     esi, 5
 * 000C7217: 8B 5D 0C                 mov     ebx, [ebp+arg_4]
 * 000C721A: 89 75 14                 mov     [ebp+arg_C], esi
 * 000C721D: 89 1C 24                 mov     [esp+34h+var_34], ebx
 * 000C7220: 8B 7D 10                 mov     edi, [ebp+arg_8]
 * 000C7223: 8D 47 01                 lea     eax, [edi+1]
 * 000C7226: 89 44 24 04              mov     [esp+34h+var_30], eax
 * 000C722A: 8D 45 F0                 lea     eax, [ebp+var_10]
 * 000C722D: 89 44 24 08              mov     [esp+34h+var_2C], eax
 * 000C7231: 8D 45 EF                 lea     eax, [ebp+var_11]
 * 000C7234: 89 44 24 0C              mov     [esp+34h+var_28], eax
 * 000C7238: E8 87 EA FF FF           call    token_dispatch
 * 000C723D: 66 89 45 FE              mov     [ebp+var_2], ax
 * 000C7241: 66 23 C0                 and     ax, ax
 * 000C7244: 74 06                    jz      short loc_C724C
 * 000C7246: EB 54                    jmp     short loc_C729C
 * 000C7248: 90 90 90 90              db 4 dup(90h)
 * 000C724C: 89 34 24                 mov     [esp+34h+var_34], esi
 * 000C724F: 8D 45 F0                 lea     eax, [ebp+var_10]
 * 000C7252: 89 44 24 04              mov     [esp+34h+var_30], eax
 * 000C7256: E8 01 73 00 00           call    strcpy
 * 000C725B: 33 C0                    xor     eax, eax
 * 000C725D: 8A 45 EF                 mov     al, [ebp+var_11]
 * 000C7260: 03 C6                    add     eax, esi
 * 000C7262: 89 45 14                 mov     [ebp+arg_C], eax
 * 000C7265: 66 8B 15 3C F1 00 00     mov     dx, word ptr ds:loc_F13A+2
 * 000C726C: 66 89 10                 mov     [eax], dx
 * 000C726F: 40                       inc     eax
 * 000C7270: 83 C7 04                 add     edi, 4
 * 000C7273: 89 45 14                 mov     [ebp+arg_C], eax
 * 000C7276: 8A 4D 08                 mov     cl, [ebp+arg_0]
 * 000C7279: 89 0C 24                 mov     [esp+34h+var_34], ecx
 * 000C727C: 89 5C 24 04              mov     [esp+34h+var_30], ebx
 * 000C7280: 89 7C 24 08              mov     [esp+34h+var_2C], edi
 * 000C7284: 89 44 24 0C              mov     [esp+34h+var_28], eax
 * 000C7288: E8 87 09 00 00           call    fn_C7C14
 * 000C728D: 66 89 45 FE              mov     [ebp+var_2], ax
 * 000C7291: 66 23 C0                 and     ax, ax
 * 000C7294: 74 06                    jz      short loc_C729C
 * 000C7296: EB 04                    jmp     short loc_C729C
 * 000C7298: 90 90 90 90              db 4 dup(90h)
 * 000C729C: 8B 5D DC                 mov     ebx, [ebp+var_24]
 * 000C729F: 8B 75 E0                 mov     esi, [ebp+var_20]
 * 000C72A2: 8B 7D E4                 mov     edi, [ebp+var_1C]
 * 000C72A5: 89 EC                    mov     esp, ebp
 * 000C72A7: 5D                       pop     ebp
 * 000C72A8: C3                       retn
 * ========================================================================== */
// [SRX-611] pop_rank=343/1298, sites=2, callers=2, callees=3, size=0xBD
int __cdecl util_C71EC(char a1, int a2, int a3, int a4)
{
  char *v4; // esi
  int result; // eax
  char *v6; // eax
  int v7; // ecx
  unsigned __int8 v8; // [esp+23h] [ebp-11h] BYREF
  char v9[14]; // [esp+24h] [ebp-10h] BYREF
  __int16 v10; // [esp+32h] [ebp-2h]

  v10 = 0;
  *(_DWORD *)a4 = *(_DWORD *)((char *)&loc_F16A + 6);
  *(_WORD *)(a4 + 4) = loc_F174;
  v4 = (char *)(a4 + 5);
  result = token_dispatch(a2, a3 + 1, v9, &v8);
  v10 = result;
  if ( !(_WORD)result )
  {
    strcpy(v4, v9);
    v6 = &v4[v8];
    *(_WORD *)v6 = *(&loc_F13A + 1);
    LOBYTE(v7) = a1;
    return fn_C7C14(v7, a2, a3 + 4, v6 + 1);
  }
  return result;
}


/* ============================================================================
 * util_C72AC  @ 0xC72AC   size=0x155   callers=2
 * note: [SRX-611] pop_rank=310/1298, sites=2, callers=2, callees=3, size=0x155
 * --- original assembly (address: bytes  mnemonic) ---------------------------
 * 000C72AC: 55                       push    ebp
 * 000C72AD: 89 E5                    mov     ebp, esp
 * 000C72AF: 83 EC 18                 sub     esp, 18h
 * 000C72B2: 8B 15 78 F1 00 00        mov     edx, dword ptr ds:loc_F176+2
 * 000C72B8: 66 C7 45 FE 00 00        mov     [ebp+var_2], 0
 * 000C72BE: 57                       push    edi
 * 000C72BF: 56                       push    esi
 * 000C72C0: 8B 75 14                 mov     esi, [ebp+arg_C]
 * 000C72C3: 89 16                    mov     [esi], edx
 * 000C72C5: 53                       push    ebx
 * 000C72C6: 83 EC 10                 sub     esp, 10h
 * 000C72C9: 66 8B 15 7C F1 00 00     mov     dx, word ptr ds:loc_F179+3
 * 000C72D0: 66 89 56 04              mov     [esi+4], dx
 * 000C72D4: 83 C6 05                 add     esi, 5
 * 000C72D7: 8B 5D 0C                 mov     ebx, [ebp+arg_4]
 * 000C72DA: 89 75 14                 mov     [ebp+arg_C], esi
 * 000C72DD: 89 1C 24                 mov     [esp+34h+var_34], ebx
 * 000C72E0: 8B 45 10                 mov     eax, [ebp+arg_8]
 * 000C72E3: 83 C0 02                 add     eax, 2
 * 000C72E6: 89 44 24 04              mov     [esp+34h+var_30], eax
 * 000C72EA: 8D 7D F0                 lea     edi, [ebp+var_10]
 * 000C72ED: 89 7C 24 08              mov     [esp+34h+var_2C], edi
 * 000C72F1: 8D 45 EF                 lea     eax, [ebp+var_11]
 * 000C72F4: 89 44 24 0C              mov     [esp+34h+var_28], eax
 * 000C72F8: E8 C7 E9 FF FF           call    token_dispatch
 * 000C72FD: 66 89 45 FE              mov     [ebp+var_2], ax
 * 000C7301: 66 23 C0                 and     ax, ax
 * 000C7304: 74 06                    jz      short loc_C730C
 * 000C7306: E9 E9 00 00 00           jmp     loc_C73F4
 * 000C730B: 90                       align 4
 * 000C730C: 89 34 24                 mov     [esp+34h+var_34], esi
 * 000C730F: 89 7C 24 04              mov     [esp+34h+var_30], edi
 * 000C7313: E8 44 72 00 00           call    strcpy
 * 000C7318: 33 C0                    xor     eax, eax
 * 000C731A: 8A 45 EF                 mov     al, [ebp+var_11]
 * 000C731D: 03 C6                    add     eax, esi
 * 000C731F: 89 45 14                 mov     [ebp+arg_C], eax
 * 000C7322: C6 00 2C                 mov     byte ptr [eax], 2Ch ; ','
 * 000C7325: 8D 70 01                 lea     esi, [eax+1]
 * 000C7328: 89 75 14                 mov     [ebp+arg_C], esi
 * 000C732B: 89 1C 24                 mov     [esp+34h+var_34], ebx
 * 000C732E: 8B 45 10                 mov     eax, [ebp+arg_8]
 * 000C7331: 83 C0 05                 add     eax, 5
 * 000C7334: 89 7C 24 08              mov     [esp+34h+var_2C], edi
 * 000C7338: 89 44 24 04              mov     [esp+34h+var_30], eax
 * 000C733C: 8D 45 EF                 lea     eax, [ebp+var_11]
 * 000C733F: 89 44 24 0C              mov     [esp+34h+var_28], eax
 * 000C7343: E8 7C E9 FF FF           call    token_dispatch
 * 000C7348: 66 89 45 FE              mov     [ebp+var_2], ax
 * 000C734C: 66 23 C0                 and     ax, ax
 * 000C734F: 74 0B                    jz      short loc_C735C
 * 000C7351: E9 9E 00 00 00           jmp     loc_C73F4
 * 000C7356: 90 90 90 90 90 90        db 6 dup(90h)
 * 000C735C: 89 34 24                 mov     [esp+34h+var_34], esi
 * 000C735F: 89 7C 24 04              mov     [esp+34h+var_30], edi
 * 000C7363: E8 F4 71 00 00           call    strcpy
 * 000C7368: 33 C0                    xor     eax, eax
 * 000C736A: 8A 45 EF                 mov     al, [ebp+var_11]
 * 000C736D: 03 C6                    add     eax, esi
 * 000C736F: 89 45 14                 mov     [ebp+arg_C], eax
 * 000C7372: C6 00 2C                 mov     byte ptr [eax], 2Ch ; ','
 * 000C7375: 8D 70 01                 lea     esi, [eax+1]
 * 000C7378: 89 75 14                 mov     [ebp+arg_C], esi
 * 000C737B: 89 1C 24                 mov     [esp+34h+var_34], ebx
 * 000C737E: 8B 45 10                 mov     eax, [ebp+arg_8]
 * 000C7381: 83 C0 08                 add     eax, 8
 * 000C7384: 89 7C 24 08              mov     [esp+34h+var_2C], edi
 * 000C7388: 89 44 24 04              mov     [esp+34h+var_30], eax
 * 000C738C: 8D 45 EF                 lea     eax, [ebp+var_11]
 * 000C738F: 89 44 24 0C              mov     [esp+34h+var_28], eax
 * 000C7393: E8 2C E9 FF FF           call    token_dispatch
 * 000C7398: 66 89 45 FE              mov     [ebp+var_2], ax
 * 000C739C: 66 23 C0                 and     ax, ax
 * 000C739F: 74 03                    jz      short loc_C73A4
 * 000C73A1: EB 51                    jmp     short loc_C73F4
 * 000C73A3: 90                       align 4
 * 000C73A4: 89 34 24                 mov     [esp+34h+var_34], esi
 * 000C73A7: 89 7C 24 04              mov     [esp+34h+var_30], edi
 * 000C73AB: E8 AC 71 00 00           call    strcpy
 * 000C73B0: 33 C0                    xor     eax, eax
 * 000C73B2: 8A 45 EF                 mov     al, [ebp+var_11]
 * 000C73B5: 03 C6                    add     eax, esi
 * 000C73B7: 89 45 14                 mov     [ebp+arg_C], eax
 * 000C73BA: 66 8B 15 3C F1 00 00     mov     dx, word ptr ds:loc_F13A+2
 * 000C73C1: 66 89 10                 mov     [eax], dx
 * 000C73C4: 40                       inc     eax
 * 000C73C5: 8A 4D 08                 mov     cl, [ebp+arg_0]
 * 000C73C8: 89 45 14                 mov     [ebp+arg_C], eax
 * 000C73CB: 89 0C 24                 mov     [esp+34h+var_34], ecx
 * 000C73CE: 89 5C 24 04              mov     [esp+34h+var_30], ebx
 * 000C73D2: 8B 4D 10                 mov     ecx, [ebp+arg_8]
 * 000C73D5: 83 C1 0B                 add     ecx, 0Bh
 * 000C73D8: 89 44 24 0C              mov     [esp+34h+var_28], eax
 * 000C73DC: 89 4C 24 08              mov     [esp+34h+var_2C], ecx
 * 000C73E0: E8 2F 08 00 00           call    fn_C7C14
 * 000C73E5: 66 89 45 FE              mov     [ebp+var_2], ax
 * 000C73E9: 66 23 C0                 and     ax, ax
 * 000C73EC: 74 06                    jz      short loc_C73F4
 * 000C73EE: EB 04                    jmp     short loc_C73F4
 * 000C73F0: 90 90 90 90              db 4 dup(90h)
 * 000C73F4: 8B 5D DC                 mov     ebx, [ebp+var_24]
 * 000C73F7: 8B 75 E0                 mov     esi, [ebp+var_20]
 * 000C73FA: 8B 7D E4                 mov     edi, [ebp+var_1C]
 * 000C73FD: 89 EC                    mov     esp, ebp
 * 000C73FF: 5D                       pop     ebp
 * 000C7400: C3                       retn
 * ========================================================================== */
// [SRX-611] pop_rank=310/1298, sites=2, callers=2, callees=3, size=0x155
int __cdecl util_C72AC(char a1, int a2, int a3, int a4)
{
  char *v4; // esi
  int result; // eax
  char *v6; // eax
  char *v7; // esi
  char *v8; // eax
  char *v9; // esi
  char *v10; // eax
  int v11; // ecx
  unsigned __int8 v12; // [esp+23h] [ebp-11h] BYREF
  char v13[14]; // [esp+24h] [ebp-10h] BYREF
  __int16 v14; // [esp+32h] [ebp-2h]

  v14 = 0;
  *(_DWORD *)a4 = *(_DWORD *)((char *)&loc_F176 + 2);
  *(_WORD *)(a4 + 4) = *(_WORD *)((char *)&loc_F179 + 3);
  v4 = (char *)(a4 + 5);
  result = token_dispatch(a2, a3 + 2, v13, &v12);
  v14 = result;
  if ( !(_WORD)result )
  {
    strcpy(v4, v13);
    v6 = &v4[v12];
    *v6 = 44;
    v7 = v6 + 1;
    result = token_dispatch(a2, a3 + 5, v13, &v12);
    v14 = result;
    if ( !(_WORD)result )
    {
      strcpy(v7, v13);
      v8 = &v7[v12];
      *v8 = 44;
      v9 = v8 + 1;
      result = token_dispatch(a2, a3 + 8, v13, &v12);
      v14 = result;
      if ( !(_WORD)result )
      {
        strcpy(v9, v13);
        v10 = &v9[v12];
        *(_WORD *)v10 = *(&loc_F13A + 1);
        LOBYTE(v11) = a1;
        return fn_C7C14(v11, a2, a3 + 11, v10 + 1);
      }
    }
  }
  return result;
}


/* ============================================================================
 * util_C7404  @ 0xC7404   size=0x155   callers=2
 * note: [SRX-611] pop_rank=311/1298, sites=2, callers=2, callees=3, size=0x155
 * --- original assembly (address: bytes  mnemonic) ---------------------------
 * 000C7404: 55                       push    ebp
 * 000C7405: 89 E5                    mov     ebp, esp
 * 000C7407: 83 EC 18                 sub     esp, 18h
 * 000C740A: 8B 15 80 F1 00 00        mov     edx, dword ptr ds:loc_F180
 * 000C7410: 66 C7 45 FE 00 00        mov     [ebp+var_2], 0
 * 000C7416: 57                       push    edi
 * 000C7417: 56                       push    esi
 * 000C7418: 8B 75 14                 mov     esi, [ebp+arg_C]
 * 000C741B: 89 16                    mov     [esi], edx
 * 000C741D: 53                       push    ebx
 * 000C741E: 83 EC 10                 sub     esp, 10h
 * 000C7421: 8A 15 84 F1 00 00        mov     dl, byte ptr ds:loc_F183+1
 * 000C7427: 88 56 04                 mov     [esi+4], dl
 * 000C742A: 83 C6 04                 add     esi, 4
 * 000C742D: 8B 5D 0C                 mov     ebx, [ebp+arg_4]
 * 000C7430: 89 75 14                 mov     [ebp+arg_C], esi
 * 000C7433: 89 1C 24                 mov     [esp+34h+var_34], ebx
 * 000C7436: 8B 45 10                 mov     eax, [ebp+arg_8]
 * 000C7439: 83 C0 02                 add     eax, 2
 * 000C743C: 89 44 24 04              mov     [esp+34h+var_30], eax
 * 000C7440: 8D 7D F0                 lea     edi, [ebp+var_10]
 * 000C7443: 89 7C 24 08              mov     [esp+34h+var_2C], edi
 * 000C7447: 8D 45 EF                 lea     eax, [ebp+var_11]
 * 000C744A: 89 44 24 0C              mov     [esp+34h+var_28], eax
 * 000C744E: E8 71 E8 FF FF           call    token_dispatch
 * 000C7453: 66 89 45 FE              mov     [ebp+var_2], ax
 * 000C7457: 66 23 C0                 and     ax, ax
 * 000C745A: 74 08                    jz      short loc_C7464
 * 000C745C: E9 EB 00 00 00           jmp     loc_C754C
 * 000C7461: 90 90 90                 align 4
 * 000C7464: 89 34 24                 mov     [esp+34h+var_34], esi
 * 000C7467: 89 7C 24 04              mov     [esp+34h+var_30], edi
 * 000C746B: E8 EC 70 00 00           call    strcpy
 * 000C7470: 33 C0                    xor     eax, eax
 * 000C7472: 8A 45 EF                 mov     al, [ebp+var_11]
 * 000C7475: 03 C6                    add     eax, esi
 * 000C7477: 89 45 14                 mov     [ebp+arg_C], eax
 * 000C747A: C6 00 2C                 mov     byte ptr [eax], 2Ch ; ','
 * 000C747D: 8D 70 01                 lea     esi, [eax+1]
 * 000C7480: 89 75 14                 mov     [ebp+arg_C], esi
 * 000C7483: 89 1C 24                 mov     [esp+34h+var_34], ebx
 * 000C7486: 8B 45 10                 mov     eax, [ebp+arg_8]
 * 000C7489: 83 C0 05                 add     eax, 5
 * 000C748C: 89 7C 24 08              mov     [esp+34h+var_2C], edi
 * 000C7490: 89 44 24 04              mov     [esp+34h+var_30], eax
 * 000C7494: 8D 45 EF                 lea     eax, [ebp+var_11]
 * 000C7497: 89 44 24 0C              mov     [esp+34h+var_28], eax
 * 000C749B: E8 24 E8 FF FF           call    token_dispatch
 * 000C74A0: 66 89 45 FE              mov     [ebp+var_2], ax
 * 000C74A4: 66 23 C0                 and     ax, ax
 * 000C74A7: 74 0B                    jz      short loc_C74B4
 * 000C74A9: E9 9E 00 00 00           jmp     loc_C754C
 * 000C74AE: 90 90 90 90 90 90        db 6 dup(90h)
 * 000C74B4: 89 34 24                 mov     [esp+34h+var_34], esi
 * 000C74B7: 89 7C 24 04              mov     [esp+34h+var_30], edi
 * 000C74BB: E8 9C 70 00 00           call    strcpy
 * 000C74C0: 33 C0                    xor     eax, eax
 * 000C74C2: 8A 45 EF                 mov     al, [ebp+var_11]
 * 000C74C5: 03 C6                    add     eax, esi
 * 000C74C7: 89 45 14                 mov     [ebp+arg_C], eax
 * 000C74CA: C6 00 2C                 mov     byte ptr [eax], 2Ch ; ','
 * 000C74CD: 8D 70 01                 lea     esi, [eax+1]
 * 000C74D0: 89 75 14                 mov     [ebp+arg_C], esi
 * 000C74D3: 89 1C 24                 mov     [esp+34h+var_34], ebx
 * 000C74D6: 8B 45 10                 mov     eax, [ebp+arg_8]
 * 000C74D9: 83 C0 08                 add     eax, 8
 * 000C74DC: 89 7C 24 08              mov     [esp+34h+var_2C], edi
 * 000C74E0: 89 44 24 04              mov     [esp+34h+var_30], eax
 * 000C74E4: 8D 45 EF                 lea     eax, [ebp+var_11]
 * 000C74E7: 89 44 24 0C              mov     [esp+34h+var_28], eax
 * 000C74EB: E8 D4 E7 FF FF           call    token_dispatch
 * 000C74F0: 66 89 45 FE              mov     [ebp+var_2], ax
 * 000C74F4: 66 23 C0                 and     ax, ax
 * 000C74F7: 74 03                    jz      short loc_C74FC
 * 000C74F9: EB 51                    jmp     short loc_C754C
 * 000C74FB: 90                       align 4
 * 000C74FC: 89 34 24                 mov     [esp+34h+var_34], esi
 * 000C74FF: 89 7C 24 04              mov     [esp+34h+var_30], edi
 * 000C7503: E8 54 70 00 00           call    strcpy
 * 000C7508: 33 C0                    xor     eax, eax
 * 000C750A: 8A 45 EF                 mov     al, [ebp+var_11]
 * 000C750D: 03 C6                    add     eax, esi
 * 000C750F: 89 45 14                 mov     [ebp+arg_C], eax
 * 000C7512: 66 8B 15 3C F1 00 00     mov     dx, word ptr ds:loc_F13A+2
 * 000C7519: 66 89 10                 mov     [eax], dx
 * 000C751C: 40                       inc     eax
 * 000C751D: 8A 4D 08                 mov     cl, [ebp+arg_0]
 * 000C7520: 89 45 14                 mov     [ebp+arg_C], eax
 * 000C7523: 89 0C 24                 mov     [esp+34h+var_34], ecx
 * 000C7526: 89 5C 24 04              mov     [esp+34h+var_30], ebx
 * 000C752A: 8B 4D 10                 mov     ecx, [ebp+arg_8]
 * 000C752D: 83 C1 0B                 add     ecx, 0Bh
 * 000C7530: 89 44 24 0C              mov     [esp+34h+var_28], eax
 * 000C7534: 89 4C 24 08              mov     [esp+34h+var_2C], ecx
 * 000C7538: E8 D7 06 00 00           call    fn_C7C14
 * 000C753D: 66 89 45 FE              mov     [ebp+var_2], ax
 * 000C7541: 66 23 C0                 and     ax, ax
 * 000C7544: 74 06                    jz      short loc_C754C
 * 000C7546: EB 04                    jmp     short loc_C754C
 * 000C7548: 90 90 90 90              db 4 dup(90h)
 * 000C754C: 8B 5D DC                 mov     ebx, [ebp+var_24]
 * 000C754F: 8B 75 E0                 mov     esi, [ebp+var_20]
 * 000C7552: 8B 7D E4                 mov     edi, [ebp+var_1C]
 * 000C7555: 89 EC                    mov     esp, ebp
 * 000C7557: 5D                       pop     ebp
 * 000C7558: C3                       retn
 * ========================================================================== */
// [SRX-611] pop_rank=311/1298, sites=2, callers=2, callees=3, size=0x155
int __cdecl util_C7404(char a1, int a2, int a3, int a4)
{
  char *v4; // esi
  int result; // eax
  char *v6; // eax
  char *v7; // esi
  char *v8; // eax
  char *v9; // esi
  char *v10; // eax
  int v11; // ecx
  unsigned __int8 v12; // [esp+23h] [ebp-11h] BYREF
  char v13[14]; // [esp+24h] [ebp-10h] BYREF
  __int16 v14; // [esp+32h] [ebp-2h]

  v14 = 0;
  *(_DWORD *)a4 = loc_F180;
  *(_BYTE *)(a4 + 4) = *(&loc_F183 + 1);
  v4 = (char *)(a4 + 4);
  result = token_dispatch(a2, a3 + 2, v13, &v12);
  v14 = result;
  if ( !(_WORD)result )
  {
    strcpy(v4, v13);
    v6 = &v4[v12];
    *v6 = 44;
    v7 = v6 + 1;
    result = token_dispatch(a2, a3 + 5, v13, &v12);
    v14 = result;
    if ( !(_WORD)result )
    {
      strcpy(v7, v13);
      v8 = &v7[v12];
      *v8 = 44;
      v9 = v8 + 1;
      result = token_dispatch(a2, a3 + 8, v13, &v12);
      v14 = result;
      if ( !(_WORD)result )
      {
        strcpy(v9, v13);
        v10 = &v9[v12];
        *(_WORD *)v10 = *(&loc_F13A + 1);
        LOBYTE(v11) = a1;
        return fn_C7C14(v11, a2, a3 + 11, v10 + 1);
      }
    }
  }
  return result;
}


/* ============================================================================
 * util_C755C  @ 0xC755C   size=0x155   callers=2
 * note: [SRX-611] pop_rank=312/1298, sites=2, callers=2, callees=3, size=0x155
 * --- original assembly (address: bytes  mnemonic) ---------------------------
 * 000C755C: 55                       push    ebp
 * 000C755D: 89 E5                    mov     ebp, esp
 * 000C755F: 83 EC 18                 sub     esp, 18h
 * 000C7562: 8B 15 88 F1 00 00        mov     edx, ds:dword_F188
 * 000C7568: 66 C7 45 FE 00 00        mov     [ebp+var_2], 0
 * 000C756E: 57                       push    edi
 * 000C756F: 56                       push    esi
 * 000C7570: 8B 75 14                 mov     esi, [ebp+arg_C]
 * 000C7573: 89 16                    mov     [esi], edx
 * 000C7575: 53                       push    ebx
 * 000C7576: 83 EC 10                 sub     esp, 10h
 * 000C7579: 8A 15 8C F1 00 00        mov     dl, byte ptr ds:os_F18C
 * 000C757F: 88 56 04                 mov     [esi+4], dl
 * 000C7582: 83 C6 04                 add     esi, 4
 * 000C7585: 8B 5D 0C                 mov     ebx, [ebp+arg_4]
 * 000C7588: 89 75 14                 mov     [ebp+arg_C], esi
 * 000C758B: 89 1C 24                 mov     [esp+34h+var_34], ebx
 * 000C758E: 8B 45 10                 mov     eax, [ebp+arg_8]
 * 000C7591: 83 C0 02                 add     eax, 2
 * 000C7594: 89 44 24 04              mov     [esp+34h+var_30], eax
 * 000C7598: 8D 7D F0                 lea     edi, [ebp+var_10]
 * 000C759B: 89 7C 24 08              mov     [esp+34h+var_2C], edi
 * 000C759F: 8D 45 EF                 lea     eax, [ebp+var_11]
 * 000C75A2: 89 44 24 0C              mov     [esp+34h+var_28], eax
 * 000C75A6: E8 19 E7 FF FF           call    token_dispatch
 * 000C75AB: 66 89 45 FE              mov     [ebp+var_2], ax
 * 000C75AF: 66 23 C0                 and     ax, ax
 * 000C75B2: 74 08                    jz      short loc_C75BC
 * 000C75B4: E9 EB 00 00 00           jmp     loc_C76A4
 * 000C75B9: 90 90 90                 align 4
 * 000C75BC: 89 34 24                 mov     [esp+34h+var_34], esi
 * 000C75BF: 89 7C 24 04              mov     [esp+34h+var_30], edi
 * 000C75C3: E8 94 6F 00 00           call    strcpy
 * 000C75C8: 33 C0                    xor     eax, eax
 * 000C75CA: 8A 45 EF                 mov     al, [ebp+var_11]
 * 000C75CD: 03 C6                    add     eax, esi
 * 000C75CF: 89 45 14                 mov     [ebp+arg_C], eax
 * 000C75D2: C6 00 2C                 mov     byte ptr [eax], 2Ch ; ','
 * 000C75D5: 8D 70 01                 lea     esi, [eax+1]
 * 000C75D8: 89 75 14                 mov     [ebp+arg_C], esi
 * 000C75DB: 89 1C 24                 mov     [esp+34h+var_34], ebx
 * 000C75DE: 8B 45 10                 mov     eax, [ebp+arg_8]
 * 000C75E1: 83 C0 05                 add     eax, 5
 * 000C75E4: 89 7C 24 08              mov     [esp+34h+var_2C], edi
 * 000C75E8: 89 44 24 04              mov     [esp+34h+var_30], eax
 * 000C75EC: 8D 45 EF                 lea     eax, [ebp+var_11]
 * 000C75EF: 89 44 24 0C              mov     [esp+34h+var_28], eax
 * 000C75F3: E8 CC E6 FF FF           call    token_dispatch
 * 000C75F8: 66 89 45 FE              mov     [ebp+var_2], ax
 * 000C75FC: 66 23 C0                 and     ax, ax
 * 000C75FF: 74 0B                    jz      short loc_C760C
 * 000C7601: E9 9E 00 00 00           jmp     loc_C76A4
 * 000C7606: 90 90 90 90 90 90        db 6 dup(90h)
 * 000C760C: 89 34 24                 mov     [esp+34h+var_34], esi
 * 000C760F: 89 7C 24 04              mov     [esp+34h+var_30], edi
 * 000C7613: E8 44 6F 00 00           call    strcpy
 * 000C7618: 33 C0                    xor     eax, eax
 * 000C761A: 8A 45 EF                 mov     al, [ebp+var_11]
 * 000C761D: 03 C6                    add     eax, esi
 * 000C761F: 89 45 14                 mov     [ebp+arg_C], eax
 * 000C7622: C6 00 2C                 mov     byte ptr [eax], 2Ch ; ','
 * 000C7625: 8D 70 01                 lea     esi, [eax+1]
 * 000C7628: 89 75 14                 mov     [ebp+arg_C], esi
 * 000C762B: 89 1C 24                 mov     [esp+34h+var_34], ebx
 * 000C762E: 8B 45 10                 mov     eax, [ebp+arg_8]
 * 000C7631: 83 C0 08                 add     eax, 8
 * 000C7634: 89 7C 24 08              mov     [esp+34h+var_2C], edi
 * 000C7638: 89 44 24 04              mov     [esp+34h+var_30], eax
 * 000C763C: 8D 45 EF                 lea     eax, [ebp+var_11]
 * 000C763F: 89 44 24 0C              mov     [esp+34h+var_28], eax
 * 000C7643: E8 7C E6 FF FF           call    token_dispatch
 * 000C7648: 66 89 45 FE              mov     [ebp+var_2], ax
 * 000C764C: 66 23 C0                 and     ax, ax
 * 000C764F: 74 03                    jz      short loc_C7654
 * 000C7651: EB 51                    jmp     short loc_C76A4
 * 000C7653: 90                       align 4
 * 000C7654: 89 34 24                 mov     [esp+34h+var_34], esi
 * 000C7657: 89 7C 24 04              mov     [esp+34h+var_30], edi
 * 000C765B: E8 FC 6E 00 00           call    strcpy
 * 000C7660: 33 C0                    xor     eax, eax
 * 000C7662: 8A 45 EF                 mov     al, [ebp+var_11]
 * 000C7665: 03 C6                    add     eax, esi
 * 000C7667: 89 45 14                 mov     [ebp+arg_C], eax
 * 000C766A: 66 8B 15 3C F1 00 00     mov     dx, word ptr ds:loc_F13A+2
 * 000C7671: 66 89 10                 mov     [eax], dx
 * 000C7674: 40                       inc     eax
 * 000C7675: 8A 4D 08                 mov     cl, [ebp+arg_0]
 * 000C7678: 89 45 14                 mov     [ebp+arg_C], eax
 * 000C767B: 89 0C 24                 mov     [esp+34h+var_34], ecx
 * 000C767E: 89 5C 24 04              mov     [esp+34h+var_30], ebx
 * 000C7682: 8B 4D 10                 mov     ecx, [ebp+arg_8]
 * 000C7685: 83 C1 0B                 add     ecx, 0Bh
 * 000C7688: 89 44 24 0C              mov     [esp+34h+var_28], eax
 * 000C768C: 89 4C 24 08              mov     [esp+34h+var_2C], ecx
 * 000C7690: E8 7F 05 00 00           call    fn_C7C14
 * 000C7695: 66 89 45 FE              mov     [ebp+var_2], ax
 * 000C7699: 66 23 C0                 and     ax, ax
 * 000C769C: 74 06                    jz      short loc_C76A4
 * 000C769E: EB 04                    jmp     short loc_C76A4
 * 000C76A0: 90 90 90 90              db 4 dup(90h)
 * 000C76A4: 8B 5D DC                 mov     ebx, [ebp+var_24]
 * 000C76A7: 8B 75 E0                 mov     esi, [ebp+var_20]
 * 000C76AA: 8B 7D E4                 mov     edi, [ebp+var_1C]
 * 000C76AD: 89 EC                    mov     esp, ebp
 * 000C76AF: 5D                       pop     ebp
 * 000C76B0: C3                       retn
 * ========================================================================== */
// [SRX-611] pop_rank=312/1298, sites=2, callers=2, callees=3, size=0x155
int __cdecl util_C755C(char a1, int a2, int a3, int a4)
{
  char *v4; // esi
  int result; // eax
  char *v6; // eax
  char *v7; // esi
  char *v8; // eax
  char *v9; // esi
  char *v10; // eax
  int v11; // ecx
  unsigned __int8 v12; // [esp+23h] [ebp-11h] BYREF
  char v13[14]; // [esp+24h] [ebp-10h] BYREF
  __int16 v14; // [esp+32h] [ebp-2h]

  v14 = 0;
  *(_DWORD *)a4 = -1869574000;
  *(_BYTE *)(a4 + 4) = *(_BYTE *)os_F18C;
  v4 = (char *)(a4 + 4);
  result = token_dispatch(a2, a3 + 2, v13, &v12);
  v14 = result;
  if ( !(_WORD)result )
  {
    strcpy(v4, v13);
    v6 = &v4[v12];
    *v6 = 44;
    v7 = v6 + 1;
    result = token_dispatch(a2, a3 + 5, v13, &v12);
    v14 = result;
    if ( !(_WORD)result )
    {
      strcpy(v7, v13);
      v8 = &v7[v12];
      *v8 = 44;
      v9 = v8 + 1;
      result = token_dispatch(a2, a3 + 8, v13, &v12);
      v14 = result;
      if ( !(_WORD)result )
      {
        strcpy(v9, v13);
        v10 = &v9[v12];
        *(_WORD *)v10 = *(&loc_F13A + 1);
        LOBYTE(v11) = a1;
        return fn_C7C14(v11, a2, a3 + 11, v10 + 1);
      }
    }
  }
  return result;
}


/* ============================================================================
 * util_C76B4  @ 0xC76B4   size=0x155   callers=2
 * note: [SRX-611] pop_rank=313/1298, sites=2, callers=2, callees=3, size=0x155
 * --- original assembly (address: bytes  mnemonic) ---------------------------
 * 000C76B4: 55                       push    ebp
 * 000C76B5: 89 E5                    mov     ebp, esp
 * 000C76B7: 83 EC 18                 sub     esp, 18h
 * 000C76BA: 8B 15 90 F1 00 00        mov     edx, dword ptr ds:loc_F18F+1
 * 000C76C0: 66 C7 45 FE 00 00        mov     [ebp+var_2], 0
 * 000C76C6: 57                       push    edi
 * 000C76C7: 56                       push    esi
 * 000C76C8: 8B 75 14                 mov     esi, [ebp+arg_C]
 * 000C76CB: 89 16                    mov     [esi], edx
 * 000C76CD: 53                       push    ebx
 * 000C76CE: 83 EC 10                 sub     esp, 10h
 * 000C76D1: 66 8B 15 94 F1 00 00     mov     dx, word ptr ds:loc_F194
 * 000C76D8: 66 89 56 04              mov     [esi+4], dx
 * 000C76DC: 83 C6 05                 add     esi, 5
 * 000C76DF: 8B 5D 0C                 mov     ebx, [ebp+arg_4]
 * 000C76E2: 89 75 14                 mov     [ebp+arg_C], esi
 * 000C76E5: 89 1C 24                 mov     [esp+34h+var_34], ebx
 * 000C76E8: 8B 45 10                 mov     eax, [ebp+arg_8]
 * 000C76EB: 83 C0 02                 add     eax, 2
 * 000C76EE: 89 44 24 04              mov     [esp+34h+var_30], eax
 * 000C76F2: 8D 7D F0                 lea     edi, [ebp+var_10]
 * 000C76F5: 89 7C 24 08              mov     [esp+34h+var_2C], edi
 * 000C76F9: 8D 45 EF                 lea     eax, [ebp+var_11]
 * 000C76FC: 89 44 24 0C              mov     [esp+34h+var_28], eax
 * 000C7700: E8 BF E5 FF FF           call    token_dispatch
 * 000C7705: 66 89 45 FE              mov     [ebp+var_2], ax
 * 000C7709: 66 23 C0                 and     ax, ax
 * 000C770C: 74 06                    jz      short loc_C7714
 * 000C770E: E9 E9 00 00 00           jmp     loc_C77FC
 * 000C7713: 90                       align 4
 * 000C7714: 89 34 24                 mov     [esp+34h+var_34], esi
 * 000C7717: 89 7C 24 04              mov     [esp+34h+var_30], edi
 * 000C771B: E8 3C 6E 00 00           call    strcpy
 * 000C7720: 33 C0                    xor     eax, eax
 * 000C7722: 8A 45 EF                 mov     al, [ebp+var_11]
 * 000C7725: 03 C6                    add     eax, esi
 * 000C7727: 89 45 14                 mov     [ebp+arg_C], eax
 * 000C772A: C6 00 2C                 mov     byte ptr [eax], 2Ch ; ','
 * 000C772D: 8D 70 01                 lea     esi, [eax+1]
 * 000C7730: 89 75 14                 mov     [ebp+arg_C], esi
 * 000C7733: 89 1C 24                 mov     [esp+34h+var_34], ebx
 * 000C7736: 8B 45 10                 mov     eax, [ebp+arg_8]
 * 000C7739: 83 C0 05                 add     eax, 5
 * 000C773C: 89 7C 24 08              mov     [esp+34h+var_2C], edi
 * 000C7740: 89 44 24 04              mov     [esp+34h+var_30], eax
 * 000C7744: 8D 45 EF                 lea     eax, [ebp+var_11]
 * 000C7747: 89 44 24 0C              mov     [esp+34h+var_28], eax
 * 000C774B: E8 74 E5 FF FF           call    token_dispatch
 * 000C7750: 66 89 45 FE              mov     [ebp+var_2], ax
 * 000C7754: 66 23 C0                 and     ax, ax
 * 000C7757: 74 0B                    jz      short loc_C7764
 * 000C7759: E9 9E 00 00 00           jmp     loc_C77FC
 * 000C775E: 90 90 90 90 90 90        db 6 dup(90h)
 * 000C7764: 89 34 24                 mov     [esp+34h+var_34], esi
 * 000C7767: 89 7C 24 04              mov     [esp+34h+var_30], edi
 * 000C776B: E8 EC 6D 00 00           call    strcpy
 * 000C7770: 33 C0                    xor     eax, eax
 * 000C7772: 8A 45 EF                 mov     al, [ebp+var_11]
 * 000C7775: 03 C6                    add     eax, esi
 * 000C7777: 89 45 14                 mov     [ebp+arg_C], eax
 * 000C777A: C6 00 2C                 mov     byte ptr [eax], 2Ch ; ','
 * 000C777D: 8D 70 01                 lea     esi, [eax+1]
 * 000C7780: 89 75 14                 mov     [ebp+arg_C], esi
 * 000C7783: 89 1C 24                 mov     [esp+34h+var_34], ebx
 * 000C7786: 8B 45 10                 mov     eax, [ebp+arg_8]
 * 000C7789: 83 C0 08                 add     eax, 8
 * 000C778C: 89 7C 24 08              mov     [esp+34h+var_2C], edi
 * 000C7790: 89 44 24 04              mov     [esp+34h+var_30], eax
 * 000C7794: 8D 45 EF                 lea     eax, [ebp+var_11]
 * 000C7797: 89 44 24 0C              mov     [esp+34h+var_28], eax
 * 000C779B: E8 24 E5 FF FF           call    token_dispatch
 * 000C77A0: 66 89 45 FE              mov     [ebp+var_2], ax
 * 000C77A4: 66 23 C0                 and     ax, ax
 * 000C77A7: 74 03                    jz      short loc_C77AC
 * 000C77A9: EB 51                    jmp     short loc_C77FC
 * 000C77AB: 90                       align 4
 * 000C77AC: 89 34 24                 mov     [esp+34h+var_34], esi
 * 000C77AF: 89 7C 24 04              mov     [esp+34h+var_30], edi
 * 000C77B3: E8 A4 6D 00 00           call    strcpy
 * 000C77B8: 33 C0                    xor     eax, eax
 * 000C77BA: 8A 45 EF                 mov     al, [ebp+var_11]
 * 000C77BD: 03 C6                    add     eax, esi
 * 000C77BF: 89 45 14                 mov     [ebp+arg_C], eax
 * 000C77C2: 66 8B 15 3C F1 00 00     mov     dx, word ptr ds:loc_F13A+2
 * 000C77C9: 66 89 10                 mov     [eax], dx
 * 000C77CC: 40                       inc     eax
 * 000C77CD: 8A 4D 08                 mov     cl, [ebp+arg_0]
 * 000C77D0: 89 45 14                 mov     [ebp+arg_C], eax
 * 000C77D3: 89 0C 24                 mov     [esp+34h+var_34], ecx
 * 000C77D6: 89 5C 24 04              mov     [esp+34h+var_30], ebx
 * 000C77DA: 8B 4D 10                 mov     ecx, [ebp+arg_8]
 * 000C77DD: 83 C1 0B                 add     ecx, 0Bh
 * 000C77E0: 89 44 24 0C              mov     [esp+34h+var_28], eax
 * 000C77E4: 89 4C 24 08              mov     [esp+34h+var_2C], ecx
 * 000C77E8: E8 27 04 00 00           call    fn_C7C14
 * 000C77ED: 66 89 45 FE              mov     [ebp+var_2], ax
 * 000C77F1: 66 23 C0                 and     ax, ax
 * 000C77F4: 74 06                    jz      short loc_C77FC
 * 000C77F6: EB 04                    jmp     short loc_C77FC
 * 000C77F8: 90 90 90 90              db 4 dup(90h)
 * 000C77FC: 8B 5D DC                 mov     ebx, [ebp+var_24]
 * 000C77FF: 8B 75 E0                 mov     esi, [ebp+var_20]
 * 000C7802: 8B 7D E4                 mov     edi, [ebp+var_1C]
 * 000C7805: 89 EC                    mov     esp, ebp
 * 000C7807: 5D                       pop     ebp
 * 000C7808: C3                       retn
 * ========================================================================== */
// [SRX-611] pop_rank=313/1298, sites=2, callers=2, callees=3, size=0x155
int __cdecl util_C76B4(char a1, int a2, int a3, int a4)
{
  char *v4; // esi
  int result; // eax
  char *v6; // eax
  char *v7; // esi
  char *v8; // eax
  char *v9; // esi
  char *v10; // eax
  int v11; // ecx
  unsigned __int8 v12; // [esp+23h] [ebp-11h] BYREF
  char v13[14]; // [esp+24h] [ebp-10h] BYREF
  __int16 v14; // [esp+32h] [ebp-2h]

  v14 = 0;
  *(_DWORD *)a4 = *(_DWORD *)((char *)&loc_F18F + 1);
  *(_WORD *)(a4 + 4) = loc_F194;
  v4 = (char *)(a4 + 5);
  result = token_dispatch(a2, a3 + 2, v13, &v12);
  v14 = result;
  if ( !(_WORD)result )
  {
    strcpy(v4, v13);
    v6 = &v4[v12];
    *v6 = 44;
    v7 = v6 + 1;
    result = token_dispatch(a2, a3 + 5, v13, &v12);
    v14 = result;
    if ( !(_WORD)result )
    {
      strcpy(v7, v13);
      v8 = &v7[v12];
      *v8 = 44;
      v9 = v8 + 1;
      result = token_dispatch(a2, a3 + 8, v13, &v12);
      v14 = result;
      if ( !(_WORD)result )
      {
        strcpy(v9, v13);
        v10 = &v9[v12];
        *(_WORD *)v10 = *(&loc_F13A + 1);
        LOBYTE(v11) = a1;
        return fn_C7C14(v11, a2, a3 + 11, v10 + 1);
      }
    }
  }
  return result;
}


/* ============================================================================
 * util_C780C  @ 0xC780C   size=0x155   callers=2
 * note: [SRX-611] pop_rank=314/1298, sites=2, callers=2, callees=3, size=0x155
 * --- original assembly (address: bytes  mnemonic) ---------------------------
 * 000C780C: 55                       push    ebp
 * 000C780D: 89 E5                    mov     ebp, esp
 * 000C780F: 83 EC 18                 sub     esp, 18h
 * 000C7812: 8B 15 98 F1 00 00        mov     edx, dword ptr ds:loc_F198
 * 000C7818: 66 C7 45 FE 00 00        mov     [ebp+var_2], 0
 * 000C781E: 57                       push    edi
 * 000C781F: 56                       push    esi
 * 000C7820: 8B 75 14                 mov     esi, [ebp+arg_C]
 * 000C7823: 89 16                    mov     [esi], edx
 * 000C7825: 53                       push    ebx
 * 000C7826: 83 EC 10                 sub     esp, 10h
 * 000C7829: 66 8B 15 9C F1 00 00     mov     dx, word ptr ds:loc_F19B+1
 * 000C7830: 66 89 56 04              mov     [esi+4], dx
 * 000C7834: 83 C6 05                 add     esi, 5
 * 000C7837: 8B 5D 0C                 mov     ebx, [ebp+arg_4]
 * 000C783A: 89 75 14                 mov     [ebp+arg_C], esi
 * 000C783D: 89 1C 24                 mov     [esp+34h+var_34], ebx
 * 000C7840: 8B 45 10                 mov     eax, [ebp+arg_8]
 * 000C7843: 83 C0 02                 add     eax, 2
 * 000C7846: 89 44 24 04              mov     [esp+34h+var_30], eax
 * 000C784A: 8D 7D F0                 lea     edi, [ebp+var_10]
 * 000C784D: 89 7C 24 08              mov     [esp+34h+var_2C], edi
 * 000C7851: 8D 45 EF                 lea     eax, [ebp+var_11]
 * 000C7854: 89 44 24 0C              mov     [esp+34h+var_28], eax
 * 000C7858: E8 67 E4 FF FF           call    token_dispatch
 * 000C785D: 66 89 45 FE              mov     [ebp+var_2], ax
 * 000C7861: 66 23 C0                 and     ax, ax
 * 000C7864: 74 06                    jz      short loc_C786C
 * 000C7866: E9 E9 00 00 00           jmp     loc_C7954
 * 000C786B: 90                       align 4
 * 000C786C: 89 34 24                 mov     [esp+34h+var_34], esi
 * 000C786F: 89 7C 24 04              mov     [esp+34h+var_30], edi
 * 000C7873: E8 E4 6C 00 00           call    strcpy
 * 000C7878: 33 C0                    xor     eax, eax
 * 000C787A: 8A 45 EF                 mov     al, [ebp+var_11]
 * 000C787D: 03 C6                    add     eax, esi
 * 000C787F: 89 45 14                 mov     [ebp+arg_C], eax
 * 000C7882: C6 00 2C                 mov     byte ptr [eax], 2Ch ; ','
 * 000C7885: 8D 70 01                 lea     esi, [eax+1]
 * 000C7888: 89 75 14                 mov     [ebp+arg_C], esi
 * 000C788B: 89 1C 24                 mov     [esp+34h+var_34], ebx
 * 000C788E: 8B 45 10                 mov     eax, [ebp+arg_8]
 * 000C7891: 83 C0 05                 add     eax, 5
 * 000C7894: 89 7C 24 08              mov     [esp+34h+var_2C], edi
 * 000C7898: 89 44 24 04              mov     [esp+34h+var_30], eax
 * 000C789C: 8D 45 EF                 lea     eax, [ebp+var_11]
 * 000C789F: 89 44 24 0C              mov     [esp+34h+var_28], eax
 * 000C78A3: E8 1C E4 FF FF           call    token_dispatch
 * 000C78A8: 66 89 45 FE              mov     [ebp+var_2], ax
 * 000C78AC: 66 23 C0                 and     ax, ax
 * 000C78AF: 74 0B                    jz      short loc_C78BC
 * 000C78B1: E9 9E 00 00 00           jmp     loc_C7954
 * 000C78B6: 90 90 90 90 90 90        db 6 dup(90h)
 * 000C78BC: 89 34 24                 mov     [esp+34h+var_34], esi
 * 000C78BF: 89 7C 24 04              mov     [esp+34h+var_30], edi
 * 000C78C3: E8 94 6C 00 00           call    strcpy
 * 000C78C8: 33 C0                    xor     eax, eax
 * 000C78CA: 8A 45 EF                 mov     al, [ebp+var_11]
 * 000C78CD: 03 C6                    add     eax, esi
 * 000C78CF: 89 45 14                 mov     [ebp+arg_C], eax
 * 000C78D2: C6 00 2C                 mov     byte ptr [eax], 2Ch ; ','
 * 000C78D5: 8D 70 01                 lea     esi, [eax+1]
 * 000C78D8: 89 75 14                 mov     [ebp+arg_C], esi
 * 000C78DB: 89 1C 24                 mov     [esp+34h+var_34], ebx
 * 000C78DE: 8B 45 10                 mov     eax, [ebp+arg_8]
 * 000C78E1: 83 C0 08                 add     eax, 8
 * 000C78E4: 89 7C 24 08              mov     [esp+34h+var_2C], edi
 * 000C78E8: 89 44 24 04              mov     [esp+34h+var_30], eax
 * 000C78EC: 8D 45 EF                 lea     eax, [ebp+var_11]
 * 000C78EF: 89 44 24 0C              mov     [esp+34h+var_28], eax
 * 000C78F3: E8 CC E3 FF FF           call    token_dispatch
 * 000C78F8: 66 89 45 FE              mov     [ebp+var_2], ax
 * 000C78FC: 66 23 C0                 and     ax, ax
 * 000C78FF: 74 03                    jz      short loc_C7904
 * 000C7901: EB 51                    jmp     short loc_C7954
 * 000C7903: 90                       align 4
 * 000C7904: 89 34 24                 mov     [esp+34h+var_34], esi
 * 000C7907: 89 7C 24 04              mov     [esp+34h+var_30], edi
 * 000C790B: E8 4C 6C 00 00           call    strcpy
 * 000C7910: 33 C0                    xor     eax, eax
 * 000C7912: 8A 45 EF                 mov     al, [ebp+var_11]
 * 000C7915: 03 C6                    add     eax, esi
 * 000C7917: 89 45 14                 mov     [ebp+arg_C], eax
 * 000C791A: 66 8B 15 3C F1 00 00     mov     dx, word ptr ds:loc_F13A+2
 * 000C7921: 66 89 10                 mov     [eax], dx
 * 000C7924: 40                       inc     eax
 * 000C7925: 8A 4D 08                 mov     cl, [ebp+arg_0]
 * 000C7928: 89 45 14                 mov     [ebp+arg_C], eax
 * 000C792B: 89 0C 24                 mov     [esp+34h+var_34], ecx
 * 000C792E: 89 5C 24 04              mov     [esp+34h+var_30], ebx
 * 000C7932: 8B 4D 10                 mov     ecx, [ebp+arg_8]
 * 000C7935: 83 C1 0B                 add     ecx, 0Bh
 * 000C7938: 89 44 24 0C              mov     [esp+34h+var_28], eax
 * 000C793C: 89 4C 24 08              mov     [esp+34h+var_2C], ecx
 * 000C7940: E8 CF 02 00 00           call    fn_C7C14
 * 000C7945: 66 89 45 FE              mov     [ebp+var_2], ax
 * 000C7949: 66 23 C0                 and     ax, ax
 * 000C794C: 74 06                    jz      short loc_C7954
 * 000C794E: EB 04                    jmp     short loc_C7954
 * 000C7950: 90 90 90 90              db 4 dup(90h)
 * 000C7954: 8B 5D DC                 mov     ebx, [ebp+var_24]
 * 000C7957: 8B 75 E0                 mov     esi, [ebp+var_20]
 * 000C795A: 8B 7D E4                 mov     edi, [ebp+var_1C]
 * 000C795D: 89 EC                    mov     esp, ebp
 * 000C795F: 5D                       pop     ebp
 * 000C7960: C3                       retn
 * ========================================================================== */
// [SRX-611] pop_rank=314/1298, sites=2, callers=2, callees=3, size=0x155
int __cdecl util_C780C(char a1, int a2, int a3, int a4)
{
  char *v4; // esi
  int result; // eax
  char *v6; // eax
  char *v7; // esi
  char *v8; // eax
  char *v9; // esi
  char *v10; // eax
  int v11; // ecx
  unsigned __int8 v12; // [esp+23h] [ebp-11h] BYREF
  char v13[14]; // [esp+24h] [ebp-10h] BYREF
  __int16 v14; // [esp+32h] [ebp-2h]

  v14 = 0;
  *(_DWORD *)a4 = loc_F198;
  *(_WORD *)(a4 + 4) = *(_WORD *)((char *)&loc_F19B + 1);
  v4 = (char *)(a4 + 5);
  result = token_dispatch(a2, a3 + 2, v13, &v12);
  v14 = result;
  if ( !(_WORD)result )
  {
    strcpy(v4, v13);
    v6 = &v4[v12];
    *v6 = 44;
    v7 = v6 + 1;
    result = token_dispatch(a2, a3 + 5, v13, &v12);
    v14 = result;
    if ( !(_WORD)result )
    {
      strcpy(v7, v13);
      v8 = &v7[v12];
      *v8 = 44;
      v9 = v8 + 1;
      result = token_dispatch(a2, a3 + 8, v13, &v12);
      v14 = result;
      if ( !(_WORD)result )
      {
        strcpy(v9, v13);
        v10 = &v9[v12];
        *(_WORD *)v10 = *(&loc_F13A + 1);
        LOBYTE(v11) = a1;
        return fn_C7C14(v11, a2, a3 + 11, v10 + 1);
      }
    }
  }
  return result;
}


/* ============================================================================
 * util_C7964  @ 0xC7964   size=0x155   callers=2
 * note: [SRX-611] pop_rank=315/1298, sites=2, callers=2, callees=3, size=0x155
 * --- original assembly (address: bytes  mnemonic) ---------------------------
 * 000C7964: 55                       push    ebp
 * 000C7965: 89 E5                    mov     ebp, esp
 * 000C7967: 83 EC 18                 sub     esp, 18h
 * 000C796A: 8B 15 A0 F1 00 00        mov     edx, dword ptr ds:loc_F1A0
 * 000C7970: 66 C7 45 FE 00 00        mov     [ebp+var_2], 0
 * 000C7976: 57                       push    edi
 * 000C7977: 56                       push    esi
 * 000C7978: 8B 75 14                 mov     esi, [ebp+arg_C]
 * 000C797B: 89 16                    mov     [esi], edx
 * 000C797D: 53                       push    ebx
 * 000C797E: 83 EC 10                 sub     esp, 10h
 * 000C7981: 66 8B 15 A4 F1 00 00     mov     dx, word ptr ds:loc_F1A0+4
 * 000C7988: 66 89 56 04              mov     [esi+4], dx
 * 000C798C: 83 C6 05                 add     esi, 5
 * 000C798F: 8B 5D 0C                 mov     ebx, [ebp+arg_4]
 * 000C7992: 89 75 14                 mov     [ebp+arg_C], esi
 * 000C7995: 89 1C 24                 mov     [esp+34h+var_34], ebx
 * 000C7998: 8B 45 10                 mov     eax, [ebp+arg_8]
 * 000C799B: 83 C0 02                 add     eax, 2
 * 000C799E: 89 44 24 04              mov     [esp+34h+var_30], eax
 * 000C79A2: 8D 7D F0                 lea     edi, [ebp+var_10]
 * 000C79A5: 89 7C 24 08              mov     [esp+34h+var_2C], edi
 * 000C79A9: 8D 45 EF                 lea     eax, [ebp+var_11]
 * 000C79AC: 89 44 24 0C              mov     [esp+34h+var_28], eax
 * 000C79B0: E8 0F E3 FF FF           call    token_dispatch
 * 000C79B5: 66 89 45 FE              mov     [ebp+var_2], ax
 * 000C79B9: 66 23 C0                 and     ax, ax
 * 000C79BC: 74 06                    jz      short loc_C79C4
 * 000C79BE: E9 E9 00 00 00           jmp     loc_C7AAC
 * 000C79C3: 90                       align 4
 * 000C79C4: 89 34 24                 mov     [esp+34h+var_34], esi
 * 000C79C7: 89 7C 24 04              mov     [esp+34h+var_30], edi
 * 000C79CB: E8 8C 6B 00 00           call    strcpy
 * 000C79D0: 33 C0                    xor     eax, eax
 * 000C79D2: 8A 45 EF                 mov     al, [ebp+var_11]
 * 000C79D5: 03 C6                    add     eax, esi
 * 000C79D7: 89 45 14                 mov     [ebp+arg_C], eax
 * 000C79DA: C6 00 2C                 mov     byte ptr [eax], 2Ch ; ','
 * 000C79DD: 8D 70 01                 lea     esi, [eax+1]
 * 000C79E0: 89 75 14                 mov     [ebp+arg_C], esi
 * 000C79E3: 89 1C 24                 mov     [esp+34h+var_34], ebx
 * 000C79E6: 8B 45 10                 mov     eax, [ebp+arg_8]
 * 000C79E9: 83 C0 05                 add     eax, 5
 * 000C79EC: 89 7C 24 08              mov     [esp+34h+var_2C], edi
 * 000C79F0: 89 44 24 04              mov     [esp+34h+var_30], eax
 * 000C79F4: 8D 45 EF                 lea     eax, [ebp+var_11]
 * 000C79F7: 89 44 24 0C              mov     [esp+34h+var_28], eax
 * 000C79FB: E8 C4 E2 FF FF           call    token_dispatch
 * 000C7A00: 66 89 45 FE              mov     [ebp+var_2], ax
 * 000C7A04: 66 23 C0                 and     ax, ax
 * 000C7A07: 74 0B                    jz      short loc_C7A14
 * 000C7A09: E9 9E 00 00 00           jmp     loc_C7AAC
 * 000C7A0E: 90 90 90 90 90 90        db 6 dup(90h)
 * 000C7A14: 89 34 24                 mov     [esp+34h+var_34], esi
 * 000C7A17: 89 7C 24 04              mov     [esp+34h+var_30], edi
 * 000C7A1B: E8 3C 6B 00 00           call    strcpy
 * 000C7A20: 33 C0                    xor     eax, eax
 * 000C7A22: 8A 45 EF                 mov     al, [ebp+var_11]
 * 000C7A25: 03 C6                    add     eax, esi
 * 000C7A27: 89 45 14                 mov     [ebp+arg_C], eax
 * 000C7A2A: C6 00 2C                 mov     byte ptr [eax], 2Ch ; ','
 * 000C7A2D: 8D 70 01                 lea     esi, [eax+1]
 * 000C7A30: 89 75 14                 mov     [ebp+arg_C], esi
 * 000C7A33: 89 1C 24                 mov     [esp+34h+var_34], ebx
 * 000C7A36: 8B 45 10                 mov     eax, [ebp+arg_8]
 * 000C7A39: 83 C0 08                 add     eax, 8
 * 000C7A3C: 89 7C 24 08              mov     [esp+34h+var_2C], edi
 * 000C7A40: 89 44 24 04              mov     [esp+34h+var_30], eax
 * 000C7A44: 8D 45 EF                 lea     eax, [ebp+var_11]
 * 000C7A47: 89 44 24 0C              mov     [esp+34h+var_28], eax
 * 000C7A4B: E8 74 E2 FF FF           call    token_dispatch
 * 000C7A50: 66 89 45 FE              mov     [ebp+var_2], ax
 * 000C7A54: 66 23 C0                 and     ax, ax
 * 000C7A57: 74 03                    jz      short loc_C7A5C
 * 000C7A59: EB 51                    jmp     short loc_C7AAC
 * 000C7A5B: 90                       align 4
 * 000C7A5C: 89 34 24                 mov     [esp+34h+var_34], esi
 * 000C7A5F: 89 7C 24 04              mov     [esp+34h+var_30], edi
 * 000C7A63: E8 F4 6A 00 00           call    strcpy
 * 000C7A68: 33 C0                    xor     eax, eax
 * 000C7A6A: 8A 45 EF                 mov     al, [ebp+var_11]
 * 000C7A6D: 03 C6                    add     eax, esi
 * 000C7A6F: 89 45 14                 mov     [ebp+arg_C], eax
 * 000C7A72: 66 8B 15 3C F1 00 00     mov     dx, word ptr ds:loc_F13A+2
 * 000C7A79: 66 89 10                 mov     [eax], dx
 * 000C7A7C: 40                       inc     eax
 * 000C7A7D: 8A 4D 08                 mov     cl, [ebp+arg_0]
 * 000C7A80: 89 45 14                 mov     [ebp+arg_C], eax
 * 000C7A83: 89 0C 24                 mov     [esp+34h+var_34], ecx
 * 000C7A86: 89 5C 24 04              mov     [esp+34h+var_30], ebx
 * 000C7A8A: 8B 4D 10                 mov     ecx, [ebp+arg_8]
 * 000C7A8D: 83 C1 0B                 add     ecx, 0Bh
 * 000C7A90: 89 44 24 0C              mov     [esp+34h+var_28], eax
 * 000C7A94: 89 4C 24 08              mov     [esp+34h+var_2C], ecx
 * 000C7A98: E8 77 01 00 00           call    fn_C7C14
 * 000C7A9D: 66 89 45 FE              mov     [ebp+var_2], ax
 * 000C7AA1: 66 23 C0                 and     ax, ax
 * 000C7AA4: 74 06                    jz      short loc_C7AAC
 * 000C7AA6: EB 04                    jmp     short loc_C7AAC
 * 000C7AA8: 90 90 90 90              db 4 dup(90h)
 * 000C7AAC: 8B 5D DC                 mov     ebx, [ebp+var_24]
 * 000C7AAF: 8B 75 E0                 mov     esi, [ebp+var_20]
 * 000C7AB2: 8B 7D E4                 mov     edi, [ebp+var_1C]
 * 000C7AB5: 89 EC                    mov     esp, ebp
 * 000C7AB7: 5D                       pop     ebp
 * 000C7AB8: C3                       retn
 * ========================================================================== */
// [SRX-611] pop_rank=315/1298, sites=2, callers=2, callees=3, size=0x155
int __cdecl util_C7964(char a1, int a2, int a3, int a4)
{
  char *v4; // esi
  int result; // eax
  char *v6; // eax
  char *v7; // esi
  char *v8; // eax
  char *v9; // esi
  char *v10; // eax
  int v11; // ecx
  unsigned __int8 v12; // [esp+23h] [ebp-11h] BYREF
  char v13[14]; // [esp+24h] [ebp-10h] BYREF
  __int16 v14; // [esp+32h] [ebp-2h]

  v14 = 0;
  *(_DWORD *)a4 = loc_F1A0;
  *(_WORD *)(a4 + 4) = *(&loc_F1A0 + 2);
  v4 = (char *)(a4 + 5);
  result = token_dispatch(a2, a3 + 2, v13, &v12);
  v14 = result;
  if ( !(_WORD)result )
  {
    strcpy(v4, v13);
    v6 = &v4[v12];
    *v6 = 44;
    v7 = v6 + 1;
    result = token_dispatch(a2, a3 + 5, v13, &v12);
    v14 = result;
    if ( !(_WORD)result )
    {
      strcpy(v7, v13);
      v8 = &v7[v12];
      *v8 = 44;
      v9 = v8 + 1;
      result = token_dispatch(a2, a3 + 8, v13, &v12);
      v14 = result;
      if ( !(_WORD)result )
      {
        strcpy(v9, v13);
        v10 = &v9[v12];
        *(_WORD *)v10 = *(&loc_F13A + 1);
        LOBYTE(v11) = a1;
        return fn_C7C14(v11, a2, a3 + 11, v10 + 1);
      }
    }
  }
  return result;
}


/* ============================================================================
 * util_C7ABC  @ 0xC7ABC   size=0x155   callers=2
 * note: [SRX-611] pop_rank=316/1298, sites=2, callers=2, callees=3, size=0x155
 * --- original assembly (address: bytes  mnemonic) ---------------------------
 * 000C7ABC: 55                       push    ebp
 * 000C7ABD: 89 E5                    mov     ebp, esp
 * 000C7ABF: 83 EC 18                 sub     esp, 18h
 * 000C7AC2: 8B 15 A8 F1 00 00        mov     edx, dword ptr ds:loc_F1A8
 * 000C7AC8: 66 C7 45 FE 00 00        mov     [ebp+var_2], 0
 * 000C7ACE: 57                       push    edi
 * 000C7ACF: 56                       push    esi
 * 000C7AD0: 8B 75 14                 mov     esi, [ebp+arg_C]
 * 000C7AD3: 89 16                    mov     [esi], edx
 * 000C7AD5: 53                       push    ebx
 * 000C7AD6: 83 EC 10                 sub     esp, 10h
 * 000C7AD9: 66 8B 15 AC F1 00 00     mov     dx, word ptr ds:loc_F1AC
 * 000C7AE0: 66 89 56 04              mov     [esi+4], dx
 * 000C7AE4: 83 C6 05                 add     esi, 5
 * 000C7AE7: 8B 5D 0C                 mov     ebx, [ebp+arg_4]
 * 000C7AEA: 89 75 14                 mov     [ebp+arg_C], esi
 * 000C7AED: 89 1C 24                 mov     [esp+34h+var_34], ebx
 * 000C7AF0: 8B 45 10                 mov     eax, [ebp+arg_8]
 * 000C7AF3: 83 C0 02                 add     eax, 2
 * 000C7AF6: 89 44 24 04              mov     [esp+34h+var_30], eax
 * 000C7AFA: 8D 7D F0                 lea     edi, [ebp+var_10]
 * 000C7AFD: 89 7C 24 08              mov     [esp+34h+var_2C], edi
 * 000C7B01: 8D 45 EF                 lea     eax, [ebp+var_11]
 * 000C7B04: 89 44 24 0C              mov     [esp+34h+var_28], eax
 * 000C7B08: E8 B7 E1 FF FF           call    token_dispatch
 * 000C7B0D: 66 89 45 FE              mov     [ebp+var_2], ax
 * 000C7B11: 66 23 C0                 and     ax, ax
 * 000C7B14: 74 06                    jz      short loc_C7B1C
 * 000C7B16: E9 E9 00 00 00           jmp     loc_C7C04
 * 000C7B1B: 90                       align 4
 * 000C7B1C: 89 34 24                 mov     [esp+34h+var_34], esi
 * 000C7B1F: 89 7C 24 04              mov     [esp+34h+var_30], edi
 * 000C7B23: E8 34 6A 00 00           call    strcpy
 * 000C7B28: 33 C0                    xor     eax, eax
 * 000C7B2A: 8A 45 EF                 mov     al, [ebp+var_11]
 * 000C7B2D: 03 C6                    add     eax, esi
 * 000C7B2F: 89 45 14                 mov     [ebp+arg_C], eax
 * 000C7B32: C6 00 2C                 mov     byte ptr [eax], 2Ch ; ','
 * 000C7B35: 8D 70 01                 lea     esi, [eax+1]
 * 000C7B38: 89 75 14                 mov     [ebp+arg_C], esi
 * 000C7B3B: 89 1C 24                 mov     [esp+34h+var_34], ebx
 * 000C7B3E: 8B 45 10                 mov     eax, [ebp+arg_8]
 * 000C7B41: 83 C0 05                 add     eax, 5
 * 000C7B44: 89 7C 24 08              mov     [esp+34h+var_2C], edi
 * 000C7B48: 89 44 24 04              mov     [esp+34h+var_30], eax
 * 000C7B4C: 8D 45 EF                 lea     eax, [ebp+var_11]
 * 000C7B4F: 89 44 24 0C              mov     [esp+34h+var_28], eax
 * 000C7B53: E8 6C E1 FF FF           call    token_dispatch
 * 000C7B58: 66 89 45 FE              mov     [ebp+var_2], ax
 * 000C7B5C: 66 23 C0                 and     ax, ax
 * 000C7B5F: 74 0B                    jz      short loc_C7B6C
 * 000C7B61: E9 9E 00 00 00           jmp     loc_C7C04
 * 000C7B66: 90 90 90 90 90 90        db 6 dup(90h)
 * 000C7B6C: 89 34 24                 mov     [esp+34h+var_34], esi
 * 000C7B6F: 89 7C 24 04              mov     [esp+34h+var_30], edi
 * 000C7B73: E8 E4 69 00 00           call    strcpy
 * 000C7B78: 33 C0                    xor     eax, eax
 * 000C7B7A: 8A 45 EF                 mov     al, [ebp+var_11]
 * 000C7B7D: 03 C6                    add     eax, esi
 * 000C7B7F: 89 45 14                 mov     [ebp+arg_C], eax
 * 000C7B82: C6 00 2C                 mov     byte ptr [eax], 2Ch ; ','
 * 000C7B85: 8D 70 01                 lea     esi, [eax+1]
 * 000C7B88: 89 75 14                 mov     [ebp+arg_C], esi
 * 000C7B8B: 89 1C 24                 mov     [esp+34h+var_34], ebx
 * 000C7B8E: 8B 45 10                 mov     eax, [ebp+arg_8]
 * 000C7B91: 83 C0 08                 add     eax, 8
 * 000C7B94: 89 7C 24 08              mov     [esp+34h+var_2C], edi
 * 000C7B98: 89 44 24 04              mov     [esp+34h+var_30], eax
 * 000C7B9C: 8D 45 EF                 lea     eax, [ebp+var_11]
 * 000C7B9F: 89 44 24 0C              mov     [esp+34h+var_28], eax
 * 000C7BA3: E8 1C E1 FF FF           call    token_dispatch
 * 000C7BA8: 66 89 45 FE              mov     [ebp+var_2], ax
 * 000C7BAC: 66 23 C0                 and     ax, ax
 * 000C7BAF: 74 03                    jz      short loc_C7BB4
 * 000C7BB1: EB 51                    jmp     short loc_C7C04
 * 000C7BB3: 90                       align 4
 * 000C7BB4: 89 34 24                 mov     [esp+34h+var_34], esi
 * 000C7BB7: 89 7C 24 04              mov     [esp+34h+var_30], edi
 * 000C7BBB: E8 9C 69 00 00           call    strcpy
 * 000C7BC0: 33 C0                    xor     eax, eax
 * 000C7BC2: 8A 45 EF                 mov     al, [ebp+var_11]
 * 000C7BC5: 03 C6                    add     eax, esi
 * 000C7BC7: 89 45 14                 mov     [ebp+arg_C], eax
 * 000C7BCA: 66 8B 15 3C F1 00 00     mov     dx, word ptr ds:loc_F13A+2
 * 000C7BD1: 66 89 10                 mov     [eax], dx
 * 000C7BD4: 40                       inc     eax
 * 000C7BD5: 8A 4D 08                 mov     cl, [ebp+arg_0]
 * 000C7BD8: 89 45 14                 mov     [ebp+arg_C], eax
 * 000C7BDB: 89 0C 24                 mov     [esp+34h+var_34], ecx
 * 000C7BDE: 89 5C 24 04              mov     [esp+34h+var_30], ebx
 * 000C7BE2: 8B 4D 10                 mov     ecx, [ebp+arg_8]
 * 000C7BE5: 83 C1 0B                 add     ecx, 0Bh
 * 000C7BE8: 89 44 24 0C              mov     [esp+34h+var_28], eax
 * 000C7BEC: 89 4C 24 08              mov     [esp+34h+var_2C], ecx
 * 000C7BF0: E8 1F 00 00 00           call    fn_C7C14
 * 000C7BF5: 66 89 45 FE              mov     [ebp+var_2], ax
 * 000C7BF9: 66 23 C0                 and     ax, ax
 * 000C7BFC: 74 06                    jz      short loc_C7C04
 * 000C7BFE: EB 04                    jmp     short loc_C7C04
 * 000C7C00: 90 90 90 90              db 4 dup(90h)
 * 000C7C04: 8B 5D DC                 mov     ebx, [ebp+var_24]
 * 000C7C07: 8B 75 E0                 mov     esi, [ebp+var_20]
 * 000C7C0A: 8B 7D E4                 mov     edi, [ebp+var_1C]
 * 000C7C0D: 89 EC                    mov     esp, ebp
 * 000C7C0F: 5D                       pop     ebp
 * 000C7C10: C3                       retn
 * ========================================================================== */
// [SRX-611] pop_rank=316/1298, sites=2, callers=2, callees=3, size=0x155
int __cdecl util_C7ABC(char a1, int a2, int a3, int a4)
{
  char *v4; // esi
  int result; // eax
  char *v6; // eax
  char *v7; // esi
  char *v8; // eax
  char *v9; // esi
  char *v10; // eax
  int v11; // ecx
  unsigned __int8 v12; // [esp+23h] [ebp-11h] BYREF
  char v13[14]; // [esp+24h] [ebp-10h] BYREF
  __int16 v14; // [esp+32h] [ebp-2h]

  v14 = 0;
  *(_DWORD *)a4 = loc_F1A8;
  *(_WORD *)(a4 + 4) = loc_F1AC;
  v4 = (char *)(a4 + 5);
  result = token_dispatch(a2, a3 + 2, v13, &v12);
  v14 = result;
  if ( !(_WORD)result )
  {
    strcpy(v4, v13);
    v6 = &v4[v12];
    *v6 = 44;
    v7 = v6 + 1;
    result = token_dispatch(a2, a3 + 5, v13, &v12);
    v14 = result;
    if ( !(_WORD)result )
    {
      strcpy(v7, v13);
      v8 = &v7[v12];
      *v8 = 44;
      v9 = v8 + 1;
      result = token_dispatch(a2, a3 + 8, v13, &v12);
      v14 = result;
      if ( !(_WORD)result )
      {
        strcpy(v9, v13);
        v10 = &v9[v12];
        *(_WORD *)v10 = *(&loc_F13A + 1);
        LOBYTE(v11) = a1;
        return fn_C7C14(v11, a2, a3 + 11, v10 + 1);
      }
    }
  }
  return result;
}


/* ============================================================================
 * util_C61EC  @ 0xC61EC   size=0x58   callers=1
 * note: [SRX-611] pop_rank=700/1298, sites=1, callers=1, callees=2, size=0x58
 * --- original assembly (address: bytes  mnemonic) ---------------------------
 * 000C61EC: 55                       push    ebp
 * 000C61ED: 89 E5                    mov     ebp, esp
 * 000C61EF: 83 EC 10                 sub     esp, 10h
 * 000C61F2: 8B 45 08                 mov     eax, [ebp+arg_0]
 * 000C61F5: 66 C7 45 F6 00 00        mov     [ebp+var_A], 0
 * 000C61FB: 56                       push    esi
 * 000C61FC: 83 EC 08                 sub     esp, 8
 * 000C61FF: 66 8B 40 01              mov     ax, [eax+1]
 * 000C6203: 89 04 24                 mov     [esp+1Ch+var_1C], eax
 * 000C6206: 8D 75 F8                 lea     esi, [ebp+var_8]
 * 000C6209: 89 74 24 04              mov     [esp+1Ch+var_18], esi
 * 000C620D: E8 42 BC F9 FF           call    util_61E54
 * 000C6212: 8B 45 0C                 mov     eax, [ebp+arg_4]
 * 000C6215: 89 04 24                 mov     [esp+1Ch+var_1C], eax
 * 000C6218: 89 74 24 04              mov     [esp+1Ch+var_18], esi
 * 000C621C: E8 3B 83 00 00           call    strcpy
 * 000C6221: 2B C0                    sub     eax, eax
 * 000C6223: 25 FF FF 00 00           and     eax, 0FFFFh
 * 000C6228: 80 7C 05 F8 00           cmp     [ebp+eax+var_8], 0
 * 000C622D: 74 05                    jz      short loc_C6234
 * 000C622F: 40                       inc     eax
 * 000C6230: EB F1                    jmp     short loc_C6223
 * 000C6232: 90 90                    align 4
 * 000C6234: 8B 4D 10                 mov     ecx, [ebp+arg_8]
 * 000C6237: 66 89 45 F6              mov     [ebp+var_A], ax
 * 000C623B: 88 01                    mov     [ecx], al
 * 000C623D: 8B 75 EC                 mov     esi, [ebp+var_14]
 * 000C6240: 89 EC                    mov     esp, ebp
 * 000C6242: 5D                       pop     ebp
 * 000C6243: C3                       retn
 * ========================================================================== */
// [SRX-611] pop_rank=700/1298, sites=1, callers=1, callees=2, size=0x58
int __cdecl util_C61EC(int a1, char *a2, _BYTE *a3)
{
  int result; // eax
  char v4[8]; // [esp+14h] [ebp-8h] BYREF

  util_61E54(*(_WORD *)(a1 + 1), v4);
  strcpy(a2, v4);
  for ( LOWORD(result) = 0; ; LOWORD(result) = result + 1 )
  {
    result = (unsigned __int16)result;
    if ( !v4[(unsigned __int16)result] )
      break;
  }
  *a3 = result;
  return result;
}


/* ============================================================================
 * util_C6244  @ 0xC6244   size=0x63   callers=1
 * note: [SRX-611] pop_rank=688/1298, sites=1, callers=1, callees=1, size=0x63
 * --- original assembly (address: bytes  mnemonic) ---------------------------
 * 000C6244: 55                       push    ebp
 * 000C6245: 89 E5                    mov     ebp, esp
 * 000C6247: 83 EC 04                 sub     esp, 4
 * 000C624A: 8B 4D 08                 mov     ecx, [ebp+arg_0]
 * 000C624D: 57                       push    edi
 * 000C624E: 56                       push    esi
 * 000C624F: 83 EC 08                 sub     esp, 8
 * 000C6252: 66 8B 41 01              mov     ax, [ecx+1]
 * 000C6256: 8B 75 0C                 mov     esi, [ebp+arg_4]
 * 000C6259: 8B 7D 10                 mov     edi, [ebp+arg_8]
 * 000C625C: 66 3D 00 A0              cmp     ax, 0A000h
 * 000C6260: 73 1A                    jnb     short loc_C627C
 * 000C6262: 89 04 24                 mov     [esp+14h+var_14], eax
 * 000C6265: 89 74 24 04              mov     [esp+14h+var_10], esi
 * 000C6269: E8 16 BE F9 FF           call    disp_62084
 * 000C626E: C6 46 04 48              mov     byte ptr [esi+4], 48h ; 'H'
 * 000C6272: C6 46 05 00              mov     byte ptr [esi+5], 0
 * 000C6276: C6 07 05                 mov     byte ptr [edi], 5
 * 000C6279: EB 22                    jmp     short loc_C629D
 * 000C627B: 90                       align 4
 * 000C627C: C6 06 30                 mov     byte ptr [esi], 30h ; '0'
 * 000C627F: 66 8B 41 01              mov     ax, [ecx+1]
 * 000C6283: 89 04 24                 mov     [esp+14h+var_14], eax
 * 000C6286: 8D 46 01                 lea     eax, [esi+1]
 * 000C6289: 89 44 24 04              mov     [esp+14h+var_10], eax
 * 000C628D: E8 F2 BD F9 FF           call    disp_62084
 * 000C6292: C6 46 05 48              mov     byte ptr [esi+5], 48h ; 'H'
 * 000C6296: C6 46 06 00              mov     byte ptr [esi+6], 0
 * 000C629A: C6 07 06                 mov     byte ptr [edi], 6
 * 000C629D: 8B 75 F4                 mov     esi, [ebp+var_C]
 * 000C62A0: 8B 7D F8                 mov     edi, [ebp+var_8]
 * 000C62A3: 89 EC                    mov     esp, ebp
 * 000C62A5: 5D                       pop     ebp
 * 000C62A6: C3                       retn
 * ========================================================================== */
// [SRX-611] pop_rank=688/1298, sites=1, callers=1, callees=1, size=0x63
unsigned __int16 __cdecl util_C6244(int a1, _BYTE *a2, _BYTE *a3)
{
  unsigned __int16 v3; // ax
  unsigned __int16 result; // ax

  v3 = *(_WORD *)(a1 + 1);
  if ( v3 >= 0xA000u )
  {
    *a2 = 48;
    result = disp_62084(*(_WORD *)(a1 + 1), a2 + 1);
    a2[5] = 72;
    a2[6] = 0;
    *a3 = 6;
  }
  else
  {
    result = disp_62084(v3, a2);
    a2[4] = 72;
    a2[5] = 0;
    *a3 = 5;
  }
  return result;
}


/* ============================================================================
 * util_C667C  @ 0xC667C   size=0x3BA   callers=1
 * note: [SRX-611] pop_rank=527/1298, sites=1, callers=1, callees=20, size=0x3BA
 * --- original assembly (address: bytes  mnemonic) ---------------------------
 * 000C667C: 55                       push    ebp
 * 000C667D: 89 E5                    mov     ebp, esp
 * 000C667F: 83 EC 0C                 sub     esp, 0Ch
 * 000C6682: 8B 4D 10                 mov     ecx, [ebp+arg_8]
 * 000C6685: 66 C7 45 FE 00 00        mov     [ebp+var_2], 0
 * 000C668B: 57                       push    edi
 * 000C668C: 56                       push    esi
 * 000C668D: 83 EC 10                 sub     esp, 10h
 * 000C6690: 83 C1 04                 add     ecx, 4
 * 000C6693: 89 4D F8                 mov     [ebp+var_8], ecx
 * 000C6696: 8A 01                    mov     al, [ecx]
 * 000C6698: 04 30                    add     al, 30h ; '0'; switch with an invalid jump table
 * 000C669A: 3C 0F                    cmp     al, 0Fh
 * 000C669C: 0F 87 2A 03 00 00        ja      def_C69E1; jumptable 000C69E1 default case
 * 000C66A2: E9 35 03 00 00           jmp     loc_C69DC
 * 000C66A7: 90 90 90 90 90           db 5 dup(90h)
 * 000C66AC: 8B 45 14                 mov     eax, [ebp+arg_C]
 * 000C66AF: 89 04 24                 mov     [esp+24h+var_24], eax
 * 000C66B2: E8 85 03 00 00           call    util_C6A3C
 * 000C66B7: 66 89 45 FE              mov     [ebp+var_2], ax
 * 000C66BB: E9 6C 03 00 00           jmp     loc_C6A2C
 * 000C66C0: 90 90 90 90              db 4 dup(90h)
 * 000C66C4: 8A 45 08                 mov     al, [ebp+arg_0]
 * 000C66C7: 89 04 24                 mov     [esp+24h+var_24], eax
 * 000C66CA: 8B 45 0C                 mov     eax, [ebp+arg_4]
 * 000C66CD: 89 44 24 04              mov     [esp+24h+var_20], eax
 * 000C66D1: 89 4C 24 08              mov     [esp+24h+var_1C], ecx
 * 000C66D5: 8B 45 14                 mov     eax, [ebp+arg_C]
 * 000C66D8: 89 44 24 0C              mov     [esp+24h+var_18], eax
 * 000C66DC: E8 0B 04 00 00           call    util_C6AEC
 * 000C66E1: 66 89 45 FE              mov     [ebp+var_2], ax
 * 000C66E5: E9 42 03 00 00           jmp     loc_C6A2C
 * 000C66EA: 90 90                    align 4
 * 000C66EC: 8B 45 14                 mov     eax, [ebp+arg_C]
 * 000C66EF: 89 04 24                 mov     [esp+24h+var_24], eax
 * 000C66F2: E8 55 04 00 00           call    util_C6B4C
 * 000C66F7: 66 89 45 FE              mov     [ebp+var_2], ax
 * 000C66FB: E9 2C 03 00 00           jmp     loc_C6A2C
 * 000C6700: 90 90 90 90              db 4 dup(90h)
 * 000C6704: 8A 45 08                 mov     al, [ebp+arg_0]
 * 000C6707: 89 04 24                 mov     [esp+24h+var_24], eax
 * 000C670A: 8B 45 0C                 mov     eax, [ebp+arg_4]
 * 000C670D: 89 44 24 04              mov     [esp+24h+var_20], eax
 * 000C6711: 89 4C 24 08              mov     [esp+24h+var_1C], ecx
 * 000C6715: 8B 45 14                 mov     eax, [ebp+arg_C]
 * 000C6718: 89 44 24 0C              mov     [esp+24h+var_18], eax
 * 000C671C: E8 43 04 00 00           call    util_C6B64
 * 000C6721: 66 89 45 FE              mov     [ebp+var_2], ax
 * 000C6725: E9 02 03 00 00           jmp     loc_C6A2C
 * 000C672A: 90 90                    align 4
 * 000C672C: 8B 45 0C                 mov     eax, [ebp+arg_4]
 * 000C672F: 89 04 24                 mov     [esp+24h+var_24], eax
 * 000C6732: 89 4C 24 04              mov     [esp+24h+var_20], ecx
 * 000C6736: 8B 45 14                 mov     eax, [ebp+arg_C]
 * 000C6739: 89 44 24 08              mov     [esp+24h+var_1C], eax
 * 000C673D: E8 DA 04 00 00           call    util_C6C1C
 * 000C6742: 66 89 45 FE              mov     [ebp+var_2], ax
 * 000C6746: E9 E1 02 00 00           jmp     loc_C6A2C
 * 000C674B: 90                       align 4
 * 000C674C: 8A 45 08                 mov     al, [ebp+arg_0]
 * 000C674F: 89 04 24                 mov     [esp+24h+var_24], eax
 * 000C6752: 8B 45 0C                 mov     eax, [ebp+arg_4]
 * 000C6755: 89 44 24 04              mov     [esp+24h+var_20], eax
 * 000C6759: 89 4C 24 08              mov     [esp+24h+var_1C], ecx
 * 000C675D: 8B 45 14                 mov     eax, [ebp+arg_C]
 * 000C6760: 89 44 24 0C              mov     [esp+24h+var_18], eax
 * 000C6764: E8 EB 02 00 00           call    util_C6A54
 * 000C6769: 66 89 45 FE              mov     [ebp+var_2], ax
 * 000C676D: E9 BA 02 00 00           jmp     loc_C6A2C
 * 000C6772: 90 90                    align 4
 * 000C6774: 8A 45 08                 mov     al, [ebp+arg_0]
 * 000C6777: 89 04 24                 mov     [esp+24h+var_24], eax
 * 000C677A: 8B 45 0C                 mov     eax, [ebp+arg_4]
 * 000C677D: 89 44 24 04              mov     [esp+24h+var_20], eax
 * 000C6781: 89 4C 24 08              mov     [esp+24h+var_1C], ecx
 * 000C6785: 8B 45 14                 mov     eax, [ebp+arg_C]
 * 000C6788: 89 44 24 0C              mov     [esp+24h+var_18], eax
 * 000C678C: E8 1B 05 00 00           call    util_C6CAC
 * 000C6791: 66 89 45 FE              mov     [ebp+var_2], ax
 * 000C6795: E9 92 02 00 00           jmp     loc_C6A2C
 * 000C679A: 90 90                    align 4
 * 000C679C: 8A 45 08                 mov     al, [ebp+arg_0]
 * 000C679F: 89 04 24                 mov     [esp+24h+var_24], eax
 * 000C67A2: 8B 45 0C                 mov     eax, [ebp+arg_4]
 * 000C67A5: 89 44 24 04              mov     [esp+24h+var_20], eax
 * 000C67A9: 89 4C 24 08              mov     [esp+24h+var_1C], ecx
 * 000C67AD: 8B 45 14                 mov     eax, [ebp+arg_C]
 * 000C67B0: 89 44 24 0C              mov     [esp+24h+var_18], eax
 * 000C67B4: E8 CB 05 00 00           call    util_C6D84
 * 000C67B9: 66 89 45 FE              mov     [ebp+var_2], ax
 * 000C67BD: E9 6A 02 00 00           jmp     loc_C6A2C
 * 000C67C2: 90 90                    align 4
 * 000C67C4: 8A 45 08                 mov     al, [ebp+arg_0]
 * 000C67C7: 89 04 24                 mov     [esp+24h+var_24], eax
 * 000C67CA: 8B 45 0C                 mov     eax, [ebp+arg_4]
 * 000C67CD: 89 44 24 04              mov     [esp+24h+var_20], eax
 * 000C67D1: 89 4C 24 08              mov     [esp+24h+var_1C], ecx
 * 000C67D5: 8B 45 14                 mov     eax, [ebp+arg_C]
 * 000C67D8: 89 44 24 0C              mov     [esp+24h+var_18], eax
 * 000C67DC: E8 7B 06 00 00           call    util_C6E5C
 * 000C67E1: 66 89 45 FE              mov     [ebp+var_2], ax
 * 000C67E5: E9 42 02 00 00           jmp     loc_C6A2C
 * 000C67EA: 90 90                    align 4
 * 000C67EC: 8A 45 08                 mov     al, [ebp+arg_0]
 * 000C67EF: 89 04 24                 mov     [esp+24h+var_24], eax
 * 000C67F2: 8B 45 0C                 mov     eax, [ebp+arg_4]
 * 000C67F5: 89 44 24 04              mov     [esp+24h+var_20], eax
 * 000C67F9: 89 4C 24 08              mov     [esp+24h+var_1C], ecx
 * 000C67FD: 8B 45 14                 mov     eax, [ebp+arg_C]
 * 000C6800: 89 44 24 0C              mov     [esp+24h+var_18], eax
 * 000C6804: E8 5B 07 00 00           call    util_C6F64
 * 000C6809: 66 89 45 FE              mov     [ebp+var_2], ax
 * 000C680D: E9 1A 02 00 00           jmp     loc_C6A2C
 * 000C6812: 90 90                    align 4
 * 000C6814: 8A 45 08                 mov     al, [ebp+arg_0]
 * 000C6817: 89 04 24                 mov     [esp+24h+var_24], eax
 * 000C681A: 8B 45 0C                 mov     eax, [ebp+arg_4]
 * 000C681D: 89 44 24 04              mov     [esp+24h+var_20], eax
 * 000C6821: 89 4C 24 08              mov     [esp+24h+var_1C], ecx
 * 000C6825: 8B 45 14                 mov     eax, [ebp+arg_C]
 * 000C6828: 89 44 24 0C              mov     [esp+24h+var_18], eax
 * 000C682C: E8 FB 08 00 00           call    util_C712C
 * 000C6831: 66 89 45 FE              mov     [ebp+var_2], ax
 * 000C6835: E9 F2 01 00 00           jmp     loc_C6A2C
 * 000C683A: 90 90                    align 4
 * 000C683C: 8A 45 08                 mov     al, [ebp+arg_0]
 * 000C683F: 89 04 24                 mov     [esp+24h+var_24], eax
 * 000C6842: 8B 45 0C                 mov     eax, [ebp+arg_4]
 * 000C6845: 89 44 24 04              mov     [esp+24h+var_20], eax
 * 000C6849: 89 4C 24 08              mov     [esp+24h+var_1C], ecx
 * 000C684D: 8B 45 14                 mov     eax, [ebp+arg_C]
 * 000C6850: 89 44 24 0C              mov     [esp+24h+var_18], eax
 * 000C6854: E8 13 08 00 00           call    util_C706C
 * 000C6859: 66 89 45 FE              mov     [ebp+var_2], ax
 * 000C685D: E9 CA 01 00 00           jmp     loc_C6A2C
 * 000C6862: 90 90                    align 4
 * 000C6864: 8A 45 08                 mov     al, [ebp+arg_0]
 * 000C6867: 89 04 24                 mov     [esp+24h+var_24], eax
 * 000C686A: 8B 45 0C                 mov     eax, [ebp+arg_4]
 * 000C686D: 89 44 24 04              mov     [esp+24h+var_20], eax
 * 000C6871: 89 4C 24 08              mov     [esp+24h+var_1C], ecx
 * 000C6875: 8B 45 14                 mov     eax, [ebp+arg_C]
 * 000C6878: 89 44 24 0C              mov     [esp+24h+var_18], eax
 * 000C687C: E8 6B 09 00 00           call    util_C71EC
 * 000C6881: 66 89 45 FE              mov     [ebp+var_2], ax
 * 000C6885: E9 A2 01 00 00           jmp     loc_C6A2C
 * 000C688A: 90 90                    align 4
 * 000C688C: 8A 41 01                 mov     al, [ecx+1]
 * 000C688F: 3C 06                    cmp     al, 6; switch with an invalid jump table
 * 000C6891: 0F 87 E5 00 00 00        ja      def_C699D; jumptable 000C699D default case
 * 000C6897: E9 F0 00 00 00           jmp     loc_C698C
 * 000C689C: 89 14 24                 mov     [esp+24h+var_24], edx
 * 000C689F: 89 74 24 04              mov     [esp+24h+var_20], esi
 * 000C68A3: 89 4C 24 08              mov     [esp+24h+var_1C], ecx
 * 000C68A7: 89 44 24 0C              mov     [esp+24h+var_18], eax
 * 000C68AB: E8 FC 09 00 00           call    util_C72AC
 * 000C68B0: 66 89 45 FE              mov     [ebp+var_2], ax
 * 000C68B4: E9 0B 01 00 00           jmp     loc_C69C4
 * 000C68B9: 90 90 90                 align 4
 * 000C68BC: 89 14 24                 mov     [esp+24h+var_24], edx
 * 000C68BF: 89 74 24 04              mov     [esp+24h+var_20], esi
 * 000C68C3: 89 4C 24 08              mov     [esp+24h+var_1C], ecx
 * 000C68C7: 89 44 24 0C              mov     [esp+24h+var_18], eax
 * 000C68CB: E8 34 0B 00 00           call    util_C7404
 * 000C68D0: 66 89 45 FE              mov     [ebp+var_2], ax
 * 000C68D4: E9 EB 00 00 00           jmp     loc_C69C4
 * 000C68D9: 90 90 90                 align 4
 * 000C68DC: 89 14 24                 mov     [esp+24h+var_24], edx
 * 000C68DF: 89 74 24 04              mov     [esp+24h+var_20], esi
 * 000C68E3: 89 4C 24 08              mov     [esp+24h+var_1C], ecx
 * 000C68E7: 89 44 24 0C              mov     [esp+24h+var_18], eax
 * 000C68EB: E8 6C 0C 00 00           call    util_C755C
 * 000C68F0: 66 89 45 FE              mov     [ebp+var_2], ax
 * 000C68F4: E9 CB 00 00 00           jmp     loc_C69C4
 * 000C68F9: 90 90 90                 align 4
 * 000C68FC: 89 14 24                 mov     [esp+24h+var_24], edx
 * 000C68FF: 89 74 24 04              mov     [esp+24h+var_20], esi
 * 000C6903: 89 4C 24 08              mov     [esp+24h+var_1C], ecx
 * 000C6907: 89 44 24 0C              mov     [esp+24h+var_18], eax
 * 000C690B: E8 A4 0D 00 00           call    util_C76B4
 * 000C6910: 66 89 45 FE              mov     [ebp+var_2], ax
 * 000C6914: E9 AB 00 00 00           jmp     loc_C69C4
 * 000C6919: 90 90 90                 align 4
 * 000C691C: 89 14 24                 mov     [esp+24h+var_24], edx
 * 000C691F: 89 74 24 04              mov     [esp+24h+var_20], esi
 * 000C6923: 89 4C 24 08              mov     [esp+24h+var_1C], ecx
 * 000C6927: 89 44 24 0C              mov     [esp+24h+var_18], eax
 * 000C692B: E8 DC 0E 00 00           call    util_C780C
 * 000C6930: 66 89 45 FE              mov     [ebp+var_2], ax
 * 000C6934: E9 8B 00 00 00           jmp     loc_C69C4
 * 000C6939: 90 90 90                 align 4
 * 000C693C: 89 14 24                 mov     [esp+24h+var_24], edx
 * 000C693F: 89 74 24 04              mov     [esp+24h+var_20], esi
 * 000C6943: 89 4C 24 08              mov     [esp+24h+var_1C], ecx
 * 000C6947: 89 44 24 0C              mov     [esp+24h+var_18], eax
 * 000C694B: E8 14 10 00 00           call    util_C7964
 * 000C6950: 66 89 45 FE              mov     [ebp+var_2], ax
 * 000C6954: EB 6E                    jmp     short loc_C69C4
 * 000C6956: 90 90 90 90 90 90        db 6 dup(90h)
 * 000C695C: 89 14 24                 mov     [esp+24h+var_24], edx
 * 000C695F: 89 74 24 04              mov     [esp+24h+var_20], esi
 * 000C6963: 89 4C 24 08              mov     [esp+24h+var_1C], ecx
 * 000C6967: 89 44 24 0C              mov     [esp+24h+var_18], eax
 * 000C696B: E8 4C 11 00 00           call    util_C7ABC
 * 000C6970: 66 89 45 FE              mov     [ebp+var_2], ax
 * 000C6974: EB 4E                    jmp     short loc_C69C4
 * 000C6976: 90 90 90 90 90 90        db 6 dup(90h)
 * 000C697C: 66 C7 45 FE 2D 33        mov     [ebp+var_2], 332Dh; jumptable 000C699D default case
 * 000C6982: 66 B8 2D 33              mov     ax, 332Dh
 * 000C6986: EB 3C                    jmp     short loc_C69C4
 * 000C6988: 90 90 90 90              db 4 dup(90h)
 * 000C698C: 89 C7                    mov     edi, eax
 * 000C698E: 81 E7 FF 00 00 00        and     edi, 0FFh
 * 000C6994: 8B 45 14                 mov     eax, [ebp+arg_C]
 * 000C6997: 8A 55 08                 mov     dl, [ebp+arg_0]
 * 000C699A: 8B 75 0C                 mov     esi, [ebp+arg_4]
 * 000C699D: 2E FF 24 BD A8 69 EC FF  jmp     dword ptr cs:[edi*4-139658h]; switch jump
 * 000C69A5: 90 90 90 9C              align 4
 * 000C69A9: 68 EC FF BC 68           db 68h, 0ECh, 0FFh
 * 000C69AE: EC FF DC                 dw 0FFECh
 * 000C69B1: 68 EC FF FC              db 68h, 0ECh, 0FFh
 * 000C69B5: 68 EC FF 1C 69           db 68h, 0ECh, 0FFh
 * 000C69BA: EC FF 3C 69              dw 0FFECh
 * 000C69BE: EC FF 5C                 dw 0FFECh
 * 000C69C1: 69 EC FF                 db 69h, 0ECh, 0FFh
 * 000C69C4: EB 66                    jmp     short loc_C6A2C
 * 000C69C6: 90 90 90 90 90 90        db 6 dup(90h)
 * 000C69CC: 66 C7 45 FE 2D 33        mov     [ebp+var_2], 332Dh; jumptable 000C69E1 default case
 * 000C69D2: 66 B8 2D 33              mov     ax, 332Dh
 * 000C69D6: EB 54                    jmp     short loc_C6A2C
 * 000C69D8: 90 90 90 90              db 4 dup(90h)
 * 000C69DC: 25 FF 00 00 00           and     eax, 0FFh
 * 000C69E1: 2E FF 24 85 EC 69 EC FF  jmp     dword ptr cs:[eax*4-139614h]; switch jump
 * 000C69E9: 90 90 90 AC              align 4
 * 000C69ED: 66 EC FF C4              db 66h, 0ECh, 0FFh
 * 000C69F1: 66 EC FF                 db 66h, 0ECh, 0FFh
 * 000C69F4: EC 66 EC FF 04 67 EC FF 2C 67 EC FF 4C 67 EC FF 74 67 EC FF 9C 67 EC FF CC 69 EC FF CC 69 EC FF C4 67 EC FF EC 67 EC FF 14 68 EC FF 3C 68 EC FF 64 68 EC FF 8C 68 EC FF dd 0FFEC66ECh, 0FFEC6704h, 0FFEC672Ch, 0FFEC674Ch, 0FFEC6774h
 * 000C6A2C: 8B 75 EC                 mov     esi, [ebp+var_14]
 * 000C6A2F: 8B 7D F0                 mov     edi, [ebp+var_10]
 * 000C6A32: 89 EC                    mov     esp, ebp
 * 000C6A34: 5D                       pop     ebp
 * 000C6A35: C3                       retn
 * ========================================================================== */
/* Hex-Rays unavailable for 0xC667C (util_C667C); see assembly above. */
void util_C667C(void) { /* jump-table handler */ }


/* ============================================================================
 * util_C6A54  @ 0xC6A54   size=0x95   callers=1
 * note: [SRX-611] pop_rank=664/1298, sites=1, callers=1, callees=3, size=0x95
 * --- original assembly (address: bytes  mnemonic) ---------------------------
 * 000C6A54: 55                       push    ebp
 * 000C6A55: 89 E5                    mov     ebp, esp
 * 000C6A57: 83 EC 18                 sub     esp, 18h
 * 000C6A5A: 66 C7 45 FE 00 00        mov     [ebp+var_2], 0
 * 000C6A60: 57                       push    edi
 * 000C6A61: 56                       push    esi
 * 000C6A62: 53                       push    ebx
 * 000C6A63: 83 EC 10                 sub     esp, 10h
 * 000C6A66: 8B 7D 0C                 mov     edi, [ebp+arg_4]
 * 000C6A69: 89 3C 24                 mov     [esp+34h+var_34], edi
 * 000C6A6C: 8B 75 10                 mov     esi, [ebp+arg_8]
 * 000C6A6F: 8D 46 01                 lea     eax, [esi+1]
 * 000C6A72: 89 44 24 04              mov     [esp+34h+var_30], eax
 * 000C6A76: 8D 45 F0                 lea     eax, [ebp+var_10]
 * 000C6A79: 89 44 24 08              mov     [esp+34h+var_2C], eax
 * 000C6A7D: 8D 45 EF                 lea     eax, [ebp+var_11]
 * 000C6A80: 89 44 24 0C              mov     [esp+34h+var_28], eax
 * 000C6A84: E8 3B F2 FF FF           call    token_dispatch
 * 000C6A89: 66 89 45 FE              mov     [ebp+var_2], ax
 * 000C6A8D: 66 23 C0                 and     ax, ax
 * 000C6A90: 74 02                    jz      short loc_C6A94
 * 000C6A92: EB 48                    jmp     short loc_C6ADC
 * 000C6A94: 8B 5D 14                 mov     ebx, [ebp+arg_C]
 * 000C6A97: 89 1C 24                 mov     [esp+34h+var_34], ebx
 * 000C6A9A: 8D 45 F0                 lea     eax, [ebp+var_10]
 * 000C6A9D: 89 44 24 04              mov     [esp+34h+var_30], eax
 * 000C6AA1: E8 B6 7A 00 00           call    strcpy
 * 000C6AA6: 33 C0                    xor     eax, eax
 * 000C6AA8: 8A 45 EF                 mov     al, [ebp+var_11]
 * 000C6AAB: 03 C3                    add     eax, ebx
 * 000C6AAD: 83 C6 04                 add     esi, 4
 * 000C6AB0: 89 45 14                 mov     [ebp+arg_C], eax
 * 000C6AB3: 8A 4D 08                 mov     cl, [ebp+arg_0]
 * 000C6AB6: 89 0C 24                 mov     [esp+34h+var_34], ecx
 * 000C6AB9: 89 7C 24 04              mov     [esp+34h+var_30], edi
 * 000C6ABD: 89 74 24 08              mov     [esp+34h+var_2C], esi
 * 000C6AC1: 89 44 24 0C              mov     [esp+34h+var_28], eax
 * 000C6AC5: E8 4A 11 00 00           call    fn_C7C14
 * 000C6ACA: 66 89 45 FE              mov     [ebp+var_2], ax
 * 000C6ACE: 66 23 C0                 and     ax, ax
 * 000C6AD1: 74 09                    jz      short loc_C6ADC
 * 000C6AD3: EB 07                    jmp     short loc_C6ADC
 * 000C6AD5: 90 90 90 90 90 90 90     db 7 dup(90h)
 * 000C6ADC: 8B 5D DC                 mov     ebx, [ebp+var_24]
 * 000C6ADF: 8B 75 E0                 mov     esi, [ebp+var_20]
 * 000C6AE2: 8B 7D E4                 mov     edi, [ebp+var_1C]
 * 000C6AE5: 89 EC                    mov     esp, ebp
 * 000C6AE7: 5D                       pop     ebp
 * 000C6AE8: C3                       retn
 * ========================================================================== */
// [SRX-611] pop_rank=664/1298, sites=1, callers=1, callees=3, size=0x95
int __cdecl util_C6A54(char a1, int a2, int a3, char *a4)
{
  int result; // eax
  int v5; // ecx
  unsigned __int8 v6; // [esp+23h] [ebp-11h] BYREF
  char v7[14]; // [esp+24h] [ebp-10h] BYREF
  __int16 v8; // [esp+32h] [ebp-2h]

  v8 = 0;
  result = token_dispatch(a2, a3 + 1, v7, &v6);
  v8 = result;
  if ( !(_WORD)result )
  {
    strcpy(a4, v7);
    LOBYTE(v5) = a1;
    return fn_C7C14(v5, a2, a3 + 4, &a4[v6]);
  }
  return result;
}


