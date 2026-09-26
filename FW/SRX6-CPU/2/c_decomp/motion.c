/*
 * Sony SRX-611 firmware - C equivalents (Hex-Rays) - prefix 'motion'
 * Source image: ROM1-C.bin (80486 real mode, OS+/386 V2.0)
 * Generated from IDA database ROM1-C.bin.i64
 * Functions in this file: 4
 */

/* ============================================================================
 * motion_BB13C  @ 0xBB13C   size=0x64   pop_rank=29/1298
 * calls=25 callers=18
 * note: [SRX-611] pop_rank=29/1298, sites=25, callers=18, callees=1, size=0x64
 * --- original assembly (address: bytes  mnemonic) ---------------------------
 * 000BB13C: 55                       push    ebp
 * 000BB13D: 89 E5                    mov     ebp, esp
 * 000BB13F: 8A 45 08                 mov     al, [ebp+arg_0]
 * 000BB142: 88 45 F7                 mov     [ebp+var_9], al
 * 000BB145: 8A 45 0C                 mov     al, [ebp+arg_4]
 * 000BB148: 83 EC 14                 sub     esp, 14h
 * 000BB14B: 88 45 F8                 mov     [ebp+var_8], al
 * 000BB14E: 8A 45 10                 mov     al, [ebp+arg_8]
 * 000BB151: 88 45 F9                 mov     [ebp+var_7], al
 * 000BB154: 8A 45 14                 mov     al, [ebp+arg_C]
 * 000BB157: C6 45 F4 1B              mov     [ebp+var_C], 1Bh
 * 000BB15B: 88 45 FA                 mov     [ebp+var_6], al
 * 000BB15E: 66 C7 45 FE 00 00        mov     [ebp+var_2], 0
 * 000BB164: C6 45 F5 07              mov     [ebp+var_B], 7
 * 000BB168: C6 45 F6 79              mov     [ebp+var_A], 79h ; 'y'
 * 000BB16C: 8D 45 F4                 lea     eax, [ebp+var_C]
 * 000BB16F: 89 04 24                 mov     [esp+14h+var_14], eax
 * 000BB172: E8 75 04 00 00           call    db_access
 * 000BB177: 66 89 45 FE              mov     [ebp+var_2], ax
 * 000BB17B: 66 23 C0                 and     ax, ax
 * 000BB17E: 74 04                    jz      short loc_BB184
 * 000BB180: EB 1A                    jmp     short loc_BB19C
 * 000BB182: 90 90                    align 4
 * 000BB184: 8A 4D F7                 mov     cl, [ebp+var_9]
 * 000BB187: 22 C9                    and     cl, cl
 * 000BB189: 74 11                    jz      short loc_BB19C
 * 000BB18B: 33 C0                    xor     eax, eax
 * 000BB18D: 88 C8                    mov     al, cl
 * 000BB18F: 66 05 20 4E              add     ax, 4E20h
 * 000BB193: 25 FF FF 00 00           and     eax, 0FFFFh
 * 000BB198: EB 02                    jmp     short loc_BB19C
 * 000BB19A: 90 90                    align 4
 * 000BB19C: 89 EC                    mov     esp, ebp
 * 000BB19E: 5D                       pop     ebp
 * 000BB19F: C3                       retn
 * ========================================================================== */
// [SRX-611] pop_rank=29/1298, sites=25, callers=18, callees=1, size=0x64
__int16 __cdecl motion_BB13C(unsigned __int8 a1, char a2, char a3, char a4)
{
  __int16 result; // ax
  _BYTE v5[3]; // [esp+8h] [ebp-Ch] BYREF
  unsigned __int8 v6; // [esp+Bh] [ebp-9h]
  char v7; // [esp+Ch] [ebp-8h]
  char v8; // [esp+Dh] [ebp-7h]
  char v9; // [esp+Eh] [ebp-6h]
  __int16 v10; // [esp+12h] [ebp-2h]

  v6 = a1;
  v7 = a2;
  v8 = a3;
  v5[0] = 27;
  v9 = a4;
  v10 = 0;
  v5[1] = 7;
  v5[2] = 121;
  result = db_access(v5);
  v10 = result;
  if ( !result )
  {
    if ( v6 )
      return v6 + 20000;
  }
  return result;
}


/* ============================================================================
 * motion_BE2B4  @ 0xBE2B4   size=0x22E   pop_rank=40/1298
 * calls=21 callers=21
 * note: [SRX-611] pop_rank=40/1298, sites=21, callers=21, callees=9, size=0x22E
 * --- original assembly (address: bytes  mnemonic) ---------------------------
 * 000BE2B4: 55                       push    ebp
 * 000BE2B5: 89 E5                    mov     ebp, esp
 * 000BE2B7: 83 EC 14                 sub     esp, 14h
 * 000BE2BA: 8D 45 F1                 lea     eax, [ebp+var_F]
 * 000BE2BD: 57                       push    edi
 * 000BE2BE: 56                       push    esi
 * 000BE2BF: 53                       push    ebx
 * 000BE2C0: 83 EC 0C                 sub     esp, 0Ch
 * 000BE2C3: 89 04 24                 mov     [esp+2Ch+var_2C], eax
 * 000BE2C6: E8 D1 20 F5 FF           call    task_1039C
 * 000BE2CB: 80 3D D8 75 00 00 01     cmp     byte ptr ds:loc_75D6+2, 1
 * 000BE2D2: 75 10                    jnz     short loc_BE2E4
 * 000BE2D4: 66 B8 52 46              mov     ax, 4652h
 * 000BE2D8: E9 F8 01 00 00           jmp     loc_BE4D5
 * 000BE2DD: 90 90 90 90 90 90 90     db 7 dup(90h)
 * 000BE2E4: 8D 45 FB                 lea     eax, [ebp+var_5]
 * 000BE2E7: 89 04 24                 mov     [esp+2Ch+var_2C], eax
 * 000BE2EA: E8 15 CA F4 FF           call    plc_AD04
 * 000BE2EF: A1 D4 75 00 00           mov     eax, dword ptr ds:loc_75D0+4
 * 000BE2F4: 89 04 24                 mov     [esp+2Ch+var_2C], eax
 * 000BE2F7: 2B F6                    sub     esi, esi
 * 000BE2F9: 89 74 24 04              mov     [esp+2Ch+var_28], esi
 * 000BE2FD: 89 74 24 08              mov     [esp+2Ch+var_24], esi
 * 000BE301: E8 56 00 01 00           call    os_syscall_90h_36h
 * 000BE306: C6 45 FA 00              mov     [ebp+var_6], 0
 * 000BE30A: C7 45 F4 01 00 00 00     mov     [ebp+var_C], 1
 * 000BE311: 66 8B 45 F2              mov     ax, [ebp+var_E]
 * 000BE315: 89 45 FC                 mov     [ebp+var_4], eax
 * 000BE318: C7 45 F4 01 00 00 00     mov     [ebp+var_C], 1
 * 000BE31F: 8A 5D FA                 mov     bl, [ebp+var_6]
 * 000BE322: 33 C0                    xor     eax, eax
 * 000BE324: 8A 45 FB                 mov     al, [ebp+var_5]
 * 000BE327: 39 45 F4                 cmp     [ebp+var_C], eax
 * 000BE32A: 0F 8F 8C 01 00 00        jg      loc_BE4BC
 * 000BE330: 8B 7D F4                 mov     edi, [ebp+var_C]
 * 000BE333: 81 E7 FF 00 00 00        and     edi, 0FFh
 * 000BE339: 89 3C 24                 mov     [esp+2Ch+var_2C], edi
 * 000BE33C: 8D 45 F9                 lea     eax, [ebp+var_7]
 * 000BE33F: 89 44 24 04              mov     [esp+2Ch+var_28], eax
 * 000BE343: E8 D8 DB F7 FF           call    motion_3BF20
 * 000BE348: 66 23 C0                 and     ax, ax
 * 000BE34B: 74 17                    jz      short loc_BE364
 * 000BE34D: 8B 45 FC                 mov     eax, [ebp+var_4]
 * 000BE350: 66 89 45 F2              mov     [ebp+var_E], ax
 * 000BE354: 88 5D FA                 mov     [ebp+var_6], bl
 * 000BE357: 2B C0                    sub     eax, eax
 * 000BE359: E9 77 01 00 00           jmp     loc_BE4D5
 * 000BE35E: 90 90 90 90 90 90        db 6 dup(90h)
 * 000BE364: 0A 5D F9                 or      bl, [ebp+var_7]
 * 000BE367: F6 C3 BF                 test    bl, 0BFh
 * 000BE36A: 0F 84 DC 00 00 00        jz      loc_BE44C
 * 000BE370: 89 3C 24                 mov     [esp+2Ch+var_2C], edi
 * 000BE373: E8 D8 E1 F7 FF           call    motion_3C550
 * 000BE378: 66 23 C0                 and     ax, ax
 * 000BE37B: 74 1F                    jz      short loc_BE39C
 * 000BE37D: 66 C7 45 F2 00 00        mov     [ebp+var_E], 0
 * 000BE383: 88 5D FA                 mov     [ebp+var_6], bl
 * 000BE386: 66 C7 45 F2 51 46        mov     [ebp+var_E], 4651h
 * 000BE38C: 66 BE 51 46              mov     si, 4651h
 * 000BE390: E9 31 01 00 00           jmp     loc_BE4C6
 * 000BE395: 90 90 90 90 90 90 90     db 7 dup(90h)
 * 000BE39C: C7 04 24 0A 00 00 00     mov     [esp+2Ch+var_2C], 0Ah
 * 000BE3A3: E8 35 00 01 00           call    os_syscall_90h_3Ch
 * 000BE3A8: 89 3C 24                 mov     [esp+2Ch+var_2C], edi
 * 000BE3AB: 8D 45 F9                 lea     eax, [ebp+var_7]
 * 000BE3AE: 89 44 24 04              mov     [esp+2Ch+var_28], eax
 * 000BE3B2: E8 69 DB F7 FF           call    motion_3BF20
 * 000BE3B7: 8A 5D F9                 mov     bl, [ebp+var_7]
 * 000BE3BA: F6 C3 BF                 test    bl, 0BFh
 * 000BE3BD: 74 25                    jz      short loc_BE3E4
 * 000BE3BF: 66 BF 51 46              mov     di, 4651h
 * 000BE3C3: F6 C3 01                 test    bl, 1
 * 000BE3C6: 75 17                    jnz     short loc_BE3DF
 * 000BE3C8: 80 25 D1 75 00 00 FD     and     byte ptr ds:loc_75D0+1, 0FDh
 * 000BE3CF: C7 04 24 01 00 00 00     mov     [esp+2Ch+var_2C], 1
 * 000BE3D6: 89 74 24 04              mov     [esp+2Ch+var_28], esi
 * 000BE3DA: E8 C5 2D F5 FF           call    motion_111A4
 * 000BE3DF: E9 CA 00 00 00           jmp     loc_BE4AE
 * 000BE3E4: C6 05 D0 75 00 00 00     mov     byte ptr ds:loc_75D0, 0
 * 000BE3EB: C6 05 D1 75 00 00 00     mov     byte ptr ds:loc_75D0+1, 0
 * 000BE3F2: C7 04 24 01 00 00 00     mov     [esp+2Ch+var_2C], 1
 * 000BE3F9: 89 74 24 04              mov     [esp+2Ch+var_28], esi
 * 000BE3FD: E8 A2 2D F5 FF           call    motion_111A4
 * 000BE402: C7 04 24 02 00 00 00     mov     [esp+2Ch+var_2C], 2
 * 000BE409: 89 74 24 04              mov     [esp+2Ch+var_28], esi
 * 000BE40D: E8 92 2D F5 FF           call    motion_111A4
 * 000BE412: 80 7D F1 01              cmp     [ebp+var_F], 1
 * 000BE416: 75 14                    jnz     short loc_BE42C
 * 000BE418: C7 04 24 07 00 00 00     mov     [esp+2Ch+var_2C], 7
 * 000BE41F: C7 44 24 04 01 00 00 00  mov     [esp+2Ch+var_28], 1
 * 000BE427: E8 78 2D F5 FF           call    motion_111A4
 * 000BE42C: C7 04 24 01 00 00 00     mov     [esp+2Ch+var_2C], 1
 * 000BE433: C7 44 24 04 03 00 00 00  mov     [esp+2Ch+var_28], 3
 * 000BE43B: 89 74 24 08              mov     [esp+2Ch+var_24], esi
 * 000BE43F: E8 D8 A0 F4 FF           call    motion_851C
 * 000BE444: 2B FF                    sub     edi, edi
 * 000BE446: EB 66                    jmp     short loc_BE4AE
 * 000BE448: 90 90 90 90              db 4 dup(90h)
 * 000BE44C: C6 05 D0 75 00 00 00     mov     byte ptr ds:loc_75D0, 0
 * 000BE453: C6 05 D1 75 00 00 00     mov     byte ptr ds:loc_75D0+1, 0
 * 000BE45A: C7 04 24 01 00 00 00     mov     [esp+2Ch+var_2C], 1
 * 000BE461: 89 74 24 04              mov     [esp+2Ch+var_28], esi
 * 000BE465: E8 3A 2D F5 FF           call    motion_111A4
 * 000BE46A: C7 04 24 02 00 00 00     mov     [esp+2Ch+var_2C], 2
 * 000BE471: 89 74 24 04              mov     [esp+2Ch+var_28], esi
 * 000BE475: E8 2A 2D F5 FF           call    motion_111A4
 * 000BE47A: 80 7D F1 01              cmp     [ebp+var_F], 1
 * 000BE47E: 75 14                    jnz     short loc_BE494
 * 000BE480: C7 04 24 07 00 00 00     mov     [esp+2Ch+var_2C], 7
 * 000BE487: C7 44 24 04 01 00 00 00  mov     [esp+2Ch+var_28], 1
 * 000BE48F: E8 10 2D F5 FF           call    motion_111A4
 * 000BE494: C7 04 24 01 00 00 00     mov     [esp+2Ch+var_2C], 1
 * 000BE49B: C7 44 24 04 03 00 00 00  mov     [esp+2Ch+var_28], 3
 * 000BE4A3: 89 74 24 08              mov     [esp+2Ch+var_24], esi
 * 000BE4A7: E8 70 A0 F4 FF           call    motion_851C
 * 000BE4AC: 2B FF                    sub     edi, edi
 * 000BE4AE: FF 45 F4                 inc     [ebp+var_C]
 * 000BE4B1: 89 7D FC                 mov     [ebp+var_4], edi
 * 000BE4B4: E9 69 FE FF FF           jmp     loc_BE322
 * 000BE4B9: 90 90 90                 align 4
 * 000BE4BC: 8B 75 FC                 mov     esi, [ebp+var_4]
 * 000BE4BF: 66 89 75 F2              mov     [ebp+var_E], si
 * 000BE4C3: 88 5D FA                 mov     [ebp+var_6], bl
 * 000BE4C6: A1 D4 75 00 00           mov     eax, dword ptr ds:loc_75D0+4
 * 000BE4CB: 89 04 24                 mov     [esp+2Ch+var_2C], eax
 * 000BE4CE: E8 78 FE 00 00           call    os_syscall_90h_37h
 * 000BE4D3: 89 F0                    mov     eax, esi
 * 000BE4D5: 8B 5D E0                 mov     ebx, [ebp+var_20]
 * 000BE4D8: 8B 75 E4                 mov     esi, [ebp+var_1C]
 * 000BE4DB: 8B 7D E8                 mov     edi, [ebp+var_18]
 * 000BE4DE: 89 EC                    mov     esp, ebp
 * 000BE4E0: 5D                       pop     ebp
 * 000BE4E1: C3                       retn
 * ========================================================================== */
// [SRX-611] pop_rank=40/1298, sites=21, callers=21, callees=9, size=0x22E
// write access to const memory has been detected, the output may be wrong!
__int16 motion_BE2B4()
{
  int v1; // eax
  char v2; // bl
  int v3; // edi
  __int16 v4; // si
  char v5; // [esp+1Dh] [ebp-Fh] BYREF
  __int16 v6; // [esp+1Eh] [ebp-Eh]
  int v7; // [esp+20h] [ebp-Ch]
  char v8; // [esp+25h] [ebp-7h] BYREF
  char v9; // [esp+26h] [ebp-6h]
  unsigned __int8 v10; // [esp+27h] [ebp-5h] BYREF
  int v11; // [esp+28h] [ebp-4h]

  task_1039C(&v5);
  if ( *(&loc_75D6 + 2) == 1 )
    return 18002;
  plc_AD04(&v10);
  v1 = os_syscall_90h_36h(*(&loc_75D0 + 1), 0, 0);
  v9 = 0;
  LOWORD(v1) = v6;
  v11 = v1;
  v7 = 1;
  v2 = 0;
  while ( v7 <= v10 )
  {
    v3 = (unsigned __int8)v7;
    if ( (unsigned __int16)motion_3BF20(v7, &v8) )
    {
      v6 = v11;
      v9 = v2;
      return 0;
    }
    v2 |= v8;
    if ( (v2 & 0xBF) == 0 )
    {
      loc_75D0 = 0;
      *(&loc_75D0 + 1) = 0;
      motion_111A4(1, 0);
      motion_111A4(2, 0);
      if ( v5 == 1 )
        motion_111A4(7, 1);
      goto LABEL_19;
    }
    if ( (unsigned __int16)motion_3C550(v3) )
    {
      v9 = v2;
      v6 = 18001;
      v4 = 18001;
      goto LABEL_22;
    }
    os_syscall_90h_3Ch(10);
    motion_3BF20(v3, &v8);
    v2 = v8;
    if ( (v8 & 0xBF) == 0 )
    {
      loc_75D0 = 0;
      *(&loc_75D0 + 1) = 0;
      motion_111A4(1, 0);
      motion_111A4(2, 0);
      if ( v5 == 1 )
        motion_111A4(7, 1);
LABEL_19:
      motion_851C(1, 3, 0);
      v3 = 0;
      goto LABEL_20;
    }
    LOWORD(v3) = 18001;
    if ( (v8 & 1) == 0 )
    {
      *(&loc_75D0 + 1) &= ~2u;
      motion_111A4(1, 0);
    }
LABEL_20:
    ++v7;
    v11 = v3;
  }
  v4 = v11;
  v6 = v11;
  v9 = v2;
LABEL_22:
  os_syscall_90h_37h(*(&loc_75D0 + 1));
  return v4;
}


/* ============================================================================
 * motion_885C  @ 0x885C   size=0x26   pop_rank=44/1298
 * calls=21 callers=10
 * note: [SRX-611] pop_rank=44/1298, sites=21, callers=10, callees=0, size=0x26, leaf
 * --- original assembly (address: bytes  mnemonic) ---------------------------
 * 0000885C: 55                       push    ebp
 * 0000885D: 89 E5                    mov     ebp, esp
 * 0000885F: F6 05 09 4A 00 00 10     test    byte ptr ds:loc_4A08+1, 10h
 * 00008866: 75 09                    jnz     short loc_8871
 * 00008868: F6 05 0D 4A 00 00 10     test    byte ptr ds:loc_4A0B+2, 10h
 * 0000886F: 74 0B                    jz      short loc_887C
 * 00008871: B0 01                    mov     al, 1
 * 00008873: EB 09                    jmp     short loc_887E
 * 00008875: 90 90 90                 align 4
 * 00008878: 90 90 90 90              dd 90909090h
 * 0000887C: 2B C0                    sub     eax, eax
 * 0000887E: 89 EC                    mov     esp, ebp
 * 00008880: 5D                       pop     ebp
 * 00008881: C3                       retn
 * ========================================================================== */
// [SRX-611] pop_rank=44/1298, sites=21, callers=10, callees=0, size=0x26, leaf
bool motion_885C()
{
  return (*(&loc_4A08 + 1) & 0x10) != 0 || (*(&loc_4A0B + 2) & 0x10) != 0;
}


/* ============================================================================
 * motion_BB364  @ 0xBB364   size=0x5C   pop_rank=48/1298
 * calls=20 callers=3
 * note: [SRX-611] pop_rank=48/1298, sites=20, callers=3, callees=1, size=0x5C
 * --- original assembly (address: bytes  mnemonic) ---------------------------
 * 000BB364: 55                       push    ebp
 * 000BB365: 89 E5                    mov     ebp, esp
 * 000BB367: 8A 45 08                 mov     al, [ebp+arg_0]
 * 000BB36A: 88 45 FB                 mov     [ebp+var_5], al
 * 000BB36D: 83 EC 14                 sub     esp, 14h
 * 000BB370: 8A 45 0C                 mov     al, [ebp+arg_4]
 * 000BB373: C6 45 F8 1B              mov     [ebp+var_8], 1Bh
 * 000BB377: 88 45 FC                 mov     [ebp+var_4], al
 * 000BB37A: 66 C7 45 FE 00 00        mov     [ebp+var_2], 0
 * 000BB380: C6 45 F9 05              mov     [ebp+var_7], 5
 * 000BB384: C6 45 FA 91              mov     [ebp+var_6], 91h
 * 000BB388: 8D 45 F8                 lea     eax, [ebp+var_8]
 * 000BB38B: 89 04 24                 mov     [esp+14h+var_14], eax
 * 000BB38E: E8 59 02 00 00           call    db_access
 * 000BB393: 66 89 45 FE              mov     [ebp+var_2], ax
 * 000BB397: 66 23 C0                 and     ax, ax
 * 000BB39A: 74 08                    jz      short loc_BB3A4
 * 000BB39C: EB 1E                    jmp     short loc_BB3BC
 * 000BB39E: 90 90 90 90 90 90        db 6 dup(90h)
 * 000BB3A4: 8A 4D FB                 mov     cl, [ebp+var_5]
 * 000BB3A7: 22 C9                    and     cl, cl
 * 000BB3A9: 74 11                    jz      short loc_BB3BC
 * 000BB3AB: 33 C0                    xor     eax, eax
 * 000BB3AD: 88 C8                    mov     al, cl
 * 000BB3AF: 66 05 20 4E              add     ax, 4E20h
 * 000BB3B3: 25 FF FF 00 00           and     eax, 0FFFFh
 * 000BB3B8: EB 02                    jmp     short loc_BB3BC
 * 000BB3BA: 90 90                    align 4
 * 000BB3BC: 89 EC                    mov     esp, ebp
 * 000BB3BE: 5D                       pop     ebp
 * 000BB3BF: C3                       retn
 * ========================================================================== */
// [SRX-611] pop_rank=48/1298, sites=20, callers=3, callees=1, size=0x5C
__int16 __cdecl motion_BB364(unsigned __int8 a1, char a2)
{
  __int16 result; // ax
  _BYTE v3[3]; // [esp+Ch] [ebp-8h] BYREF
  unsigned __int8 v4; // [esp+Fh] [ebp-5h]
  char v5; // [esp+10h] [ebp-4h]
  __int16 v6; // [esp+12h] [ebp-2h]

  v4 = a1;
  v3[0] = 27;
  v5 = a2;
  v6 = 0;
  v3[1] = 5;
  v3[2] = -111;
  result = db_access(v3);
  v6 = result;
  if ( !result )
  {
    if ( v4 )
      return v4 + 20000;
  }
  return result;
}


