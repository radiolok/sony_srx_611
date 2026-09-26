/*
 * Sony SRX-611 firmware - C equivalents (Hex-Rays) - prefix 'db'
 * Source image: ROM1-C.bin (80486 real mode, OS+/386 V2.0)
 * Generated from IDA database ROM1-C.bin.i64
 * Functions in this file: 9
 */

/* ============================================================================
 * db_var_get  @ 0xBAEDC   size=0xF8   pop_rank=2/1298
 * calls=292 callers=50
 * note: Get variable by field id (used for point/param fetch) | [SRX-611] pop_rank=2/1298, sites=292, callers=50, callees=1, size=0xF8
 * --- original assembly (address: bytes  mnemonic) ---------------------------
 * 000BAEDC: 55                       push    ebp
 * 000BAEDD: 89 E5                    mov     ebp, esp
 * 000BAEDF: 81 EC 14 01 00 00        sub     esp, 114h
 * 000BAEE5: 8B 55 10                 mov     edx, [ebp+arg_8]
 * 000BAEE8: C6 85 F7 FE FF FF 00     mov     [ebp+var_109], 0
 * 000BAEEF: 57                       push    edi
 * 000BAEF0: 56                       push    esi
 * 000BAEF1: 83 EC 08                 sub     esp, 8
 * 000BAEF4: 66 C7 45 FE 00 00        mov     [ebp+var_2], 0
 * 000BAEFA: 89 95 F0 FE FF FF        mov     [ebp+var_110], edx
 * 000BAF00: 89 D1                    mov     ecx, edx
 * 000BAF02: 8A 85 F7 FE FF FF        mov     al, [ebp+var_109]
 * 000BAF08: 80 39 00                 cmp     byte ptr [ecx], 0
 * 000BAF0B: 74 27                    jz      short loc_BAF34
 * 000BAF0D: 3C FA                    cmp     al, 0FAh
 * 000BAF0F: 76 1B                    jbe     short loc_BAF2C
 * 000BAF11: 89 8D F0 FE FF FF        mov     [ebp+var_110], ecx
 * 000BAF17: 88 85 F7 FE FF FF        mov     [ebp+var_109], al
 * 000BAF1D: 66 B8 E9 03              mov     ax, 3E9h
 * 000BAF21: E9 9E 00 00 00           jmp     loc_BAFC4
 * 000BAF26: 90 90 90 90 90 90        db 6 dup(90h)
 * 000BAF2C: 40                       inc     eax
 * 000BAF2D: 41                       inc     ecx
 * 000BAF2E: EB D8                    jmp     short loc_BAF08
 * 000BAF30: 90 90 90 90              db 4 dup(90h)
 * 000BAF34: 89 8D F0 FE FF FF        mov     [ebp+var_110], ecx
 * 000BAF3A: 88 85 F7 FE FF FF        mov     [ebp+var_109], al
 * 000BAF40: C6 85 F8 FE FF FF 1B     mov     [ebp+var_108], 1Bh
 * 000BAF47: 89 D6                    mov     esi, edx
 * 000BAF49: 8D 48 05                 lea     ecx, [eax+5]
 * 000BAF4C: 88 8D F9 FE FF FF        mov     [ebp+var_107], cl
 * 000BAF52: 8A 4D 08                 mov     cl, [ebp+arg_0]
 * 000BAF55: FC                       cld
 * 000BAF56: 88 8D FB FE FF FF        mov     [ebp+var_105], cl
 * 000BAF5C: 8A 4D 0C                 mov     cl, [ebp+arg_4]
 * 000BAF5F: 88 8D FC FE FF FF        mov     [ebp+var_104], cl
 * 000BAF65: 33 C9                    xor     ecx, ecx
 * 000BAF67: 88 C1                    mov     cl, al
 * 000BAF69: 0F AC CA 02              shrd    edx, ecx, 2
 * 000BAF6D: C1 E9 02                 shr     ecx, 2
 * 000BAF70: C6 85 FA FE FF FF 60     mov     [ebp+var_106], 60h ; '`'
 * 000BAF77: 8D BD FD FE FF FF        lea     edi, [ebp+var_103]
 * 000BAF7D: F3 A5                    rep movsd
 * 000BAF7F: 0F A4 D1 02              shld    ecx, edx, 2
 * 000BAF83: F3 A4                    rep movsb
 * 000BAF85: 8D 85 F8 FE FF FF        lea     eax, [ebp+var_108]
 * 000BAF8B: 89 04 24                 mov     [esp+124h+var_124], eax
 * 000BAF8E: E8 59 06 00 00           call    db_access
 * 000BAF93: 66 89 45 FE              mov     [ebp+var_2], ax
 * 000BAF97: 66 23 C0                 and     ax, ax
 * 000BAF9A: 74 08                    jz      short loc_BAFA4
 * 000BAF9C: EB 26                    jmp     short loc_BAFC4
 * 000BAF9E: 90 90 90 90 90 90        db 6 dup(90h)
 * 000BAFA4: 8A 8D FB FE FF FF        mov     cl, [ebp+var_105]
 * 000BAFAA: 22 C9                    and     cl, cl
 * 000BAFAC: 74 16                    jz      short loc_BAFC4
 * 000BAFAE: 33 C0                    xor     eax, eax
 * 000BAFB0: 88 C8                    mov     al, cl
 * 000BAFB2: 66 05 20 4E              add     ax, 4E20h
 * 000BAFB6: 25 FF FF 00 00           and     eax, 0FFFFh
 * 000BAFBB: EB 07                    jmp     short loc_BAFC4
 * 000BAFBD: 90 90 90 90 90 90 90     db 7 dup(90h)
 * 000BAFC4: 8B B5 E4 FE FF FF        mov     esi, [ebp+var_11C]
 * 000BAFCA: 8B BD E8 FE FF FF        mov     edi, [ebp+var_118]
 * 000BAFD0: 89 EC                    mov     esp, ebp
 * 000BAFD2: 5D                       pop     ebp
 * 000BAFD3: C3                       retn
 * ========================================================================== */
// Get variable by field id (used for point/param fetch) | [SRX-611] pop_rank=2/1298, sites=292, callers=50, callees=1, size=0xF8
__int16 __cdecl db_var_get(unsigned __int8 a1, char a2, _BYTE *a3)
{
  _BYTE *v3; // ecx
  unsigned __int8 v4; // al
  __int16 result; // ax
  unsigned __int64 v6; // rt0
  int v7; // ecx
  _BYTE v8[3]; // [esp+1Ch] [ebp-108h] BYREF
  unsigned __int8 v9; // [esp+1Fh] [ebp-105h]
  char v10; // [esp+20h] [ebp-104h]
  _DWORD v11[64]; // [esp+21h] [ebp-103h] BYREF
  __int16 v12; // [esp+122h] [ebp-2h]

  v12 = 0;
  v3 = a3;
  v4 = 0;
  while ( *v3 )
  {
    if ( v4 > 0xFAu )
      return 1001;
    ++v4;
    ++v3;
  }
  v8[0] = 27;
  v8[1] = v4 + 5;
  v9 = a1;
  v10 = a2;
  LODWORD(v6) = a3;
  HIDWORD(v6) = v4;
  v7 = v4 >> 2;
  v8[2] = 96;
  qmemcpy(v11, a3, 4 * v7);
  qmemcpy(&v11[v7], &a3[4 * v7], (unsigned __int64)(unsigned int)(v6 >> 2) >> 30);
  result = db_access(v8);
  v12 = result;
  if ( !result )
  {
    if ( v9 )
      return v9 + 20000;
  }
  return result;
}


/* ============================================================================
 * db_get_field92  @ 0xBB3C4   size=0x5C   pop_rank=14/1298
 * calls=42 callers=26
 * note: DB accessor for field id 0x92 (0x1B record header) | [SRX-611] pop_rank=14/1298, sites=42, callers=26, callees=1, size=0x5C
 * --- original assembly (address: bytes  mnemonic) ---------------------------
 * 000BB3C4: 55                       push    ebp
 * 000BB3C5: 89 E5                    mov     ebp, esp
 * 000BB3C7: 8A 45 08                 mov     al, [ebp+arg_0]
 * 000BB3CA: 88 45 FB                 mov     [ebp+var_5], al
 * 000BB3CD: 83 EC 14                 sub     esp, 14h
 * 000BB3D0: 8A 45 0C                 mov     al, [ebp+arg_4]
 * 000BB3D3: C6 45 F8 1B              mov     [ebp+var_8], 1Bh
 * 000BB3D7: 88 45 FC                 mov     [ebp+var_4], al
 * 000BB3DA: 66 C7 45 FE 00 00        mov     [ebp+var_2], 0
 * 000BB3E0: C6 45 F9 05              mov     [ebp+var_7], 5
 * 000BB3E4: C6 45 FA 92              mov     [ebp+var_6], 92h
 * 000BB3E8: 8D 45 F8                 lea     eax, [ebp+var_8]
 * 000BB3EB: 89 04 24                 mov     [esp+14h+var_14], eax
 * 000BB3EE: E8 F9 01 00 00           call    db_access
 * 000BB3F3: 66 89 45 FE              mov     [ebp+var_2], ax
 * 000BB3F7: 66 23 C0                 and     ax, ax
 * 000BB3FA: 74 08                    jz      short loc_BB404
 * 000BB3FC: EB 1E                    jmp     short loc_BB41C
 * 000BB3FE: 90 90 90 90 90 90        db 6 dup(90h)
 * 000BB404: 8A 4D FB                 mov     cl, [ebp+var_5]
 * 000BB407: 22 C9                    and     cl, cl
 * 000BB409: 74 11                    jz      short loc_BB41C
 * 000BB40B: 33 C0                    xor     eax, eax
 * 000BB40D: 88 C8                    mov     al, cl
 * 000BB40F: 66 05 20 4E              add     ax, 4E20h
 * 000BB413: 25 FF FF 00 00           and     eax, 0FFFFh
 * 000BB418: EB 02                    jmp     short loc_BB41C
 * 000BB41A: 90 90                    align 4
 * 000BB41C: 89 EC                    mov     esp, ebp
 * 000BB41E: 5D                       pop     ebp
 * 000BB41F: C3                       retn
 * ========================================================================== */
// DB accessor for field id 0x92 (0x1B record header) | [SRX-611] pop_rank=14/1298, sites=42, callers=26, callees=1, size=0x5C
int __cdecl db_get_field92(unsigned __int8 a1, char a2)
{
  int result; // eax
  _BYTE v3[3]; // [esp+Ch] [ebp-8h] BYREF
  unsigned __int8 v4; // [esp+Fh] [ebp-5h]
  char v5; // [esp+10h] [ebp-4h]
  __int16 v6; // [esp+12h] [ebp-2h]

  v4 = a1;
  v3[0] = 27;
  v5 = a2;
  v6 = 0;
  v3[1] = 5;
  v3[2] = -110;
  result = db_access(v3);
  v6 = result;
  if ( !(_WORD)result )
  {
    if ( v4 )
      return (unsigned __int16)(v4 + 20000);
  }
  return result;
}


/* ============================================================================
 * db_field_1  @ 0xBA6CC   size=0x54   pop_rank=18/1298
 * calls=34 callers=13
 * note: Database field accessor (id 1) | [SRX-611] pop_rank=18/1298, sites=34, callers=13, callees=1, size=0x54
 * --- original assembly (address: bytes  mnemonic) ---------------------------
 * 000BA6CC: 55                       push    ebp
 * 000BA6CD: 89 E5                    mov     ebp, esp
 * 000BA6CF: 83 EC 14                 sub     esp, 14h
 * 000BA6D2: 8A 45 08                 mov     al, [ebp+arg_0]
 * 000BA6D5: C6 45 F8 1B              mov     [ebp+var_8], 1Bh
 * 000BA6D9: 88 45 FB                 mov     [ebp+var_5], al
 * 000BA6DC: 66 C7 45 FE 00 00        mov     [ebp+var_2], 0
 * 000BA6E2: C6 45 F9 04              mov     [ebp+var_7], 4
 * 000BA6E6: C6 45 FA 31              mov     [ebp+var_6], 31h ; '1'
 * 000BA6EA: 8D 45 F8                 lea     eax, [ebp+var_8]
 * 000BA6ED: 89 04 24                 mov     [esp+14h+var_14], eax
 * 000BA6F0: E8 F7 0E 00 00           call    db_access
 * 000BA6F5: 66 89 45 FE              mov     [ebp+var_2], ax
 * 000BA6F9: 66 23 C0                 and     ax, ax
 * 000BA6FC: 74 06                    jz      short loc_BA704
 * 000BA6FE: EB 1C                    jmp     short loc_BA71C
 * 000BA700: 90 90 90 90              db 4 dup(90h)
 * 000BA704: 8A 4D FB                 mov     cl, [ebp+var_5]
 * 000BA707: 22 C9                    and     cl, cl
 * 000BA709: 74 11                    jz      short loc_BA71C
 * 000BA70B: 33 C0                    xor     eax, eax
 * 000BA70D: 88 C8                    mov     al, cl
 * 000BA70F: 66 05 20 4E              add     ax, 4E20h
 * 000BA713: 25 FF FF 00 00           and     eax, 0FFFFh
 * 000BA718: EB 02                    jmp     short loc_BA71C
 * 000BA71A: 90 90                    align 4
 * 000BA71C: 89 EC                    mov     esp, ebp
 * 000BA71E: 5D                       pop     ebp
 * 000BA71F: C3                       retn
 * ========================================================================== */
// Database field accessor (id 1) | [SRX-611] pop_rank=18/1298, sites=34, callers=13, callees=1, size=0x54
int __cdecl db_field_1(unsigned __int8 a1)
{
  int result; // eax
  _BYTE v2[3]; // [esp+Ch] [ebp-8h] BYREF
  unsigned __int8 v3; // [esp+Fh] [ebp-5h]
  __int16 v4; // [esp+12h] [ebp-2h]

  v2[0] = 27;
  v3 = a1;
  v4 = 0;
  v2[1] = 4;
  v2[2] = 49;
  result = db_access(v2);
  v4 = result;
  if ( !(_WORD)result )
  {
    if ( v3 )
      return (unsigned __int16)(v3 + 20000);
  }
  return result;
}


/* ============================================================================
 * db_field_2  @ 0xBA724   size=0x54   pop_rank=19/1298
 * calls=34 callers=13
 * note: Database field accessor (id 2) | [SRX-611] pop_rank=19/1298, sites=34, callers=13, callees=1, size=0x54
 * --- original assembly (address: bytes  mnemonic) ---------------------------
 * 000BA724: 55                       push    ebp
 * 000BA725: 89 E5                    mov     ebp, esp
 * 000BA727: 83 EC 14                 sub     esp, 14h
 * 000BA72A: 8A 45 08                 mov     al, [ebp+arg_0]
 * 000BA72D: C6 45 F8 1B              mov     [ebp+var_8], 1Bh
 * 000BA731: 88 45 FB                 mov     [ebp+var_5], al
 * 000BA734: 66 C7 45 FE 00 00        mov     [ebp+var_2], 0
 * 000BA73A: C6 45 F9 04              mov     [ebp+var_7], 4
 * 000BA73E: C6 45 FA 32              mov     [ebp+var_6], 32h ; '2'
 * 000BA742: 8D 45 F8                 lea     eax, [ebp+var_8]
 * 000BA745: 89 04 24                 mov     [esp+14h+var_14], eax
 * 000BA748: E8 9F 0E 00 00           call    db_access
 * 000BA74D: 66 89 45 FE              mov     [ebp+var_2], ax
 * 000BA751: 66 23 C0                 and     ax, ax
 * 000BA754: 74 06                    jz      short loc_BA75C
 * 000BA756: EB 1C                    jmp     short loc_BA774
 * 000BA758: 90 90 90 90              db 4 dup(90h)
 * 000BA75C: 8A 4D FB                 mov     cl, [ebp+var_5]
 * 000BA75F: 22 C9                    and     cl, cl
 * 000BA761: 74 11                    jz      short loc_BA774
 * 000BA763: 33 C0                    xor     eax, eax
 * 000BA765: 88 C8                    mov     al, cl
 * 000BA767: 66 05 20 4E              add     ax, 4E20h
 * 000BA76B: 25 FF FF 00 00           and     eax, 0FFFFh
 * 000BA770: EB 02                    jmp     short loc_BA774
 * 000BA772: 90 90                    align 4
 * 000BA774: 89 EC                    mov     esp, ebp
 * 000BA776: 5D                       pop     ebp
 * 000BA777: C3                       retn
 * ========================================================================== */
// Database field accessor (id 2) | [SRX-611] pop_rank=19/1298, sites=34, callers=13, callees=1, size=0x54
int __cdecl db_field_2(unsigned __int8 a1)
{
  int result; // eax
  _BYTE v2[3]; // [esp+Ch] [ebp-8h] BYREF
  unsigned __int8 v3; // [esp+Fh] [ebp-5h]
  __int16 v4; // [esp+12h] [ebp-2h]

  v2[0] = 27;
  v3 = a1;
  v4 = 0;
  v2[1] = 4;
  v2[2] = 50;
  result = db_access(v2);
  v4 = result;
  if ( !(_WORD)result )
  {
    if ( v3 )
      return (unsigned __int16)(v3 + 20000);
  }
  return result;
}


/* ============================================================================
 * db_field_4  @ 0xBA96C   size=0xE0   pop_rank=20/1298
 * calls=33 callers=13
 * note: Database field accessor (id 4) | [SRX-611] pop_rank=20/1298, sites=33, callers=13, callees=1, size=0xE0
 * --- original assembly (address: bytes  mnemonic) ---------------------------
 * 000BA96C: 55                       push    ebp
 * 000BA96D: 89 E5                    mov     ebp, esp
 * 000BA96F: 81 EC 0C 01 00 00        sub     esp, 10Ch
 * 000BA975: 8B 55 08                 mov     edx, [ebp+arg_0]
 * 000BA978: C6 85 FF FE FF FF 00     mov     [ebp+var_101], 0
 * 000BA97F: 57                       push    edi
 * 000BA980: 56                       push    esi
 * 000BA981: 83 EC 08                 sub     esp, 8
 * 000BA984: 66 C7 45 FE 00 00        mov     [ebp+var_2], 0
 * 000BA98A: 89 95 F8 FE FF FF        mov     [ebp+var_108], edx
 * 000BA990: 89 D1                    mov     ecx, edx
 * 000BA992: 8A 85 FF FE FF FF        mov     al, [ebp+var_101]
 * 000BA998: 80 39 00                 cmp     byte ptr [ecx], 0
 * 000BA99B: 74 27                    jz      short loc_BA9C4
 * 000BA99D: 3C FA                    cmp     al, 0FAh
 * 000BA99F: 76 1B                    jbe     short loc_BA9BC
 * 000BA9A1: 89 8D F8 FE FF FF        mov     [ebp+var_108], ecx
 * 000BA9A7: 88 85 FF FE FF FF        mov     [ebp+var_101], al
 * 000BA9AD: 66 B8 E9 03              mov     ax, 3E9h
 * 000BA9B1: E9 86 00 00 00           jmp     loc_BAA3C
 * 000BA9B6: 90 90 90 90 90 90        db 6 dup(90h)
 * 000BA9BC: 40                       inc     eax
 * 000BA9BD: 41                       inc     ecx
 * 000BA9BE: EB D8                    jmp     short loc_BA998
 * 000BA9C0: 90 90 90 90              db 4 dup(90h)
 * 000BA9C4: 89 8D F8 FE FF FF        mov     [ebp+var_108], ecx
 * 000BA9CA: 88 85 FF FE FF FF        mov     [ebp+var_101], al
 * 000BA9D0: C6 85 00 FF FF FF 1B     mov     [ebp+var_100], 1Bh
 * 000BA9D7: 89 D6                    mov     esi, edx
 * 000BA9D9: 8D 48 03                 lea     ecx, [eax+3]
 * 000BA9DC: 88 8D 01 FF FF FF        mov     [ebp+var_FF], cl
 * 000BA9E2: 33 C9                    xor     ecx, ecx
 * 000BA9E4: 88 C1                    mov     cl, al
 * 000BA9E6: 0F AC CA 02              shrd    edx, ecx, 2
 * 000BA9EA: C1 E9 02                 shr     ecx, 2
 * 000BA9ED: FC                       cld
 * 000BA9EE: C6 85 02 FF FF FF 42     mov     [ebp+var_FE], 42h ; 'B'
 * 000BA9F5: 8D BD 03 FF FF FF        lea     edi, [ebp+var_FD]
 * 000BA9FB: F3 A5                    rep movsd
 * 000BA9FD: 0F A4 D1 02              shld    ecx, edx, 2
 * 000BAA01: F3 A4                    rep movsb
 * 000BAA03: 8D 85 00 FF FF FF        lea     eax, [ebp+var_100]
 * 000BAA09: 89 04 24                 mov     [esp+11Ch+var_11C], eax
 * 000BAA0C: E8 DB 0B 00 00           call    db_access
 * 000BAA11: 66 89 45 FE              mov     [ebp+var_2], ax
 * 000BAA15: 66 23 C0                 and     ax, ax
 * 000BAA18: 74 02                    jz      short loc_BAA1C
 * 000BAA1A: EB 20                    jmp     short loc_BAA3C
 * 000BAA1C: 8A 8D 03 FF FF FF        mov     cl, [ebp+var_FD]
 * 000BAA22: 22 C9                    and     cl, cl
 * 000BAA24: 74 16                    jz      short loc_BAA3C
 * 000BAA26: 33 C0                    xor     eax, eax
 * 000BAA28: 88 C8                    mov     al, cl
 * 000BAA2A: 66 05 20 4E              add     ax, 4E20h
 * 000BAA2E: 25 FF FF 00 00           and     eax, 0FFFFh
 * 000BAA33: EB 07                    jmp     short loc_BAA3C
 * 000BAA35: 90 90 90 90 90 90 90     db 7 dup(90h)
 * 000BAA3C: 8B B5 EC FE FF FF        mov     esi, [ebp+var_114]
 * 000BAA42: 8B BD F0 FE FF FF        mov     edi, [ebp+var_110]
 * 000BAA48: 89 EC                    mov     esp, ebp
 * 000BAA4A: 5D                       pop     ebp
 * 000BAA4B: C3                       retn
 * ========================================================================== */
// Database field accessor (id 4) | [SRX-611] pop_rank=20/1298, sites=33, callers=13, callees=1, size=0xE0
__int16 __cdecl db_field_4(_BYTE *a1)
{
  _BYTE *v1; // ecx
  unsigned __int8 v2; // al
  __int16 result; // ax
  unsigned __int64 v4; // rt0
  int v5; // ecx
  _BYTE v6[3]; // [esp+1Ch] [ebp-100h] BYREF
  unsigned __int8 v7[251]; // [esp+1Fh] [ebp-FDh] BYREF
  __int16 v8; // [esp+11Ah] [ebp-2h]

  v8 = 0;
  v1 = a1;
  v2 = 0;
  while ( *v1 )
  {
    if ( v2 > 0xFAu )
      return 1001;
    ++v2;
    ++v1;
  }
  v6[0] = 27;
  v6[1] = v2 + 3;
  LODWORD(v4) = a1;
  HIDWORD(v4) = v2;
  v5 = v2 >> 2;
  v6[2] = 66;
  qmemcpy(v7, a1, 4 * v5);
  qmemcpy(&v7[4 * v5], &a1[4 * v5], (unsigned __int64)(unsigned int)(v4 >> 2) >> 30);
  result = db_access(v6);
  v8 = result;
  if ( !result )
  {
    if ( v7[0] )
      return v7[0] + 20000;
  }
  return result;
}


/* ============================================================================
 * db_field_get  @ 0xBA66C   size=0x5C   pop_rank=24/1298
 * calls=27 callers=19
 * note: Get typed database field by id | [SRX-611] pop_rank=24/1298, sites=27, callers=19, callees=1, size=0x5C
 * --- original assembly (address: bytes  mnemonic) ---------------------------
 * 000BA66C: 55                       push    ebp
 * 000BA66D: 89 E5                    mov     ebp, esp
 * 000BA66F: 8A 45 08                 mov     al, [ebp+arg_0]
 * 000BA672: 88 45 FB                 mov     [ebp+var_5], al
 * 000BA675: 83 EC 14                 sub     esp, 14h
 * 000BA678: 8A 45 0C                 mov     al, [ebp+arg_4]
 * 000BA67B: C6 45 F8 1B              mov     [ebp+var_8], 1Bh
 * 000BA67F: 88 45 FC                 mov     [ebp+var_4], al
 * 000BA682: 66 C7 45 FE 00 00        mov     [ebp+var_2], 0
 * 000BA688: C6 45 F9 05              mov     [ebp+var_7], 5
 * 000BA68C: C6 45 FA 30              mov     [ebp+var_6], 30h ; '0'
 * 000BA690: 8D 45 F8                 lea     eax, [ebp+var_8]
 * 000BA693: 89 04 24                 mov     [esp+14h+var_14], eax
 * 000BA696: E8 51 0F 00 00           call    db_access
 * 000BA69B: 66 89 45 FE              mov     [ebp+var_2], ax
 * 000BA69F: 66 23 C0                 and     ax, ax
 * 000BA6A2: 74 08                    jz      short loc_BA6AC
 * 000BA6A4: EB 1E                    jmp     short loc_BA6C4
 * 000BA6A6: 90 90 90 90 90 90        db 6 dup(90h)
 * 000BA6AC: 8A 4D FB                 mov     cl, [ebp+var_5]
 * 000BA6AF: 22 C9                    and     cl, cl
 * 000BA6B1: 74 11                    jz      short loc_BA6C4
 * 000BA6B3: 33 C0                    xor     eax, eax
 * 000BA6B5: 88 C8                    mov     al, cl
 * 000BA6B7: 66 05 20 4E              add     ax, 4E20h
 * 000BA6BB: 25 FF FF 00 00           and     eax, 0FFFFh
 * 000BA6C0: EB 02                    jmp     short loc_BA6C4
 * 000BA6C2: 90 90                    align 4
 * 000BA6C4: 89 EC                    mov     esp, ebp
 * 000BA6C6: 5D                       pop     ebp
 * 000BA6C7: C3                       retn
 * ========================================================================== */
// Get typed database field by id | [SRX-611] pop_rank=24/1298, sites=27, callers=19, callees=1, size=0x5C
int __cdecl db_field_get(unsigned __int8 a1, char a2)
{
  int result; // eax
  _BYTE v3[3]; // [esp+Ch] [ebp-8h] BYREF
  unsigned __int8 v4; // [esp+Fh] [ebp-5h]
  char v5; // [esp+10h] [ebp-4h]
  __int16 v6; // [esp+12h] [ebp-2h]

  v4 = a1;
  v3[0] = 27;
  v5 = a2;
  v6 = 0;
  v3[1] = 5;
  v3[2] = 48;
  result = db_access(v3);
  v6 = result;
  if ( !(_WORD)result )
  {
    if ( v4 )
      return (unsigned __int16)(v4 + 20000);
  }
  return result;
}


/* ============================================================================
 * db_get_field33  @ 0xBA77C   size=0x54   pop_rank=26/1298
 * calls=26 callers=10
 * note: DB accessor for field id 0x33 (0x1B record header) | [SRX-611] pop_rank=26/1298, sites=26, callers=10, callees=1, size=0x54
 * --- original assembly (address: bytes  mnemonic) ---------------------------
 * 000BA77C: 55                       push    ebp
 * 000BA77D: 89 E5                    mov     ebp, esp
 * 000BA77F: 83 EC 14                 sub     esp, 14h
 * 000BA782: 8A 45 08                 mov     al, [ebp+arg_0]
 * 000BA785: C6 45 F8 1B              mov     [ebp+var_8], 1Bh
 * 000BA789: 88 45 FB                 mov     [ebp+var_5], al
 * 000BA78C: 66 C7 45 FE 00 00        mov     [ebp+var_2], 0
 * 000BA792: C6 45 F9 04              mov     [ebp+var_7], 4
 * 000BA796: C6 45 FA 33              mov     [ebp+var_6], 33h ; '3'
 * 000BA79A: 8D 45 F8                 lea     eax, [ebp+var_8]
 * 000BA79D: 89 04 24                 mov     [esp+14h+var_14], eax
 * 000BA7A0: E8 47 0E 00 00           call    db_access
 * 000BA7A5: 66 89 45 FE              mov     [ebp+var_2], ax
 * 000BA7A9: 66 23 C0                 and     ax, ax
 * 000BA7AC: 74 06                    jz      short loc_BA7B4
 * 000BA7AE: EB 1C                    jmp     short loc_BA7CC
 * 000BA7B0: 90 90 90 90              db 4 dup(90h)
 * 000BA7B4: 8A 4D FB                 mov     cl, [ebp+var_5]
 * 000BA7B7: 22 C9                    and     cl, cl
 * 000BA7B9: 74 11                    jz      short loc_BA7CC
 * 000BA7BB: 33 C0                    xor     eax, eax
 * 000BA7BD: 88 C8                    mov     al, cl
 * 000BA7BF: 66 05 20 4E              add     ax, 4E20h
 * 000BA7C3: 25 FF FF 00 00           and     eax, 0FFFFh
 * 000BA7C8: EB 02                    jmp     short loc_BA7CC
 * 000BA7CA: 90 90                    align 4
 * 000BA7CC: 89 EC                    mov     esp, ebp
 * 000BA7CE: 5D                       pop     ebp
 * 000BA7CF: C3                       retn
 * ========================================================================== */
// DB accessor for field id 0x33 (0x1B record header) | [SRX-611] pop_rank=26/1298, sites=26, callers=10, callees=1, size=0x54
int __cdecl db_get_field33(unsigned __int8 a1)
{
  int result; // eax
  _BYTE v2[3]; // [esp+Ch] [ebp-8h] BYREF
  unsigned __int8 v3; // [esp+Fh] [ebp-5h]
  __int16 v4; // [esp+12h] [ebp-2h]

  v2[0] = 27;
  v3 = a1;
  v4 = 0;
  v2[1] = 4;
  v2[2] = 51;
  result = db_access(v2);
  v4 = result;
  if ( !(_WORD)result )
  {
    if ( v3 )
      return (unsigned __int16)(v3 + 20000);
  }
  return result;
}


/* ============================================================================
 * db_access  @ 0xBB5EC   size=0x147   pop_rank=37/1298
 * calls=22 callers=22
 * note: Generic parameter/variable database access (0x1B record header) | [SRX-611] pop_rank=37/1298, sites=22, callers=22, callees=4, size=0x147
 * --- original assembly (address: bytes  mnemonic) ---------------------------
 * 000BB5EC: 55                       push    ebp
 * 000BB5ED: 89 E5                    mov     ebp, esp
 * 000BB5EF: 83 EC 14                 sub     esp, 14h
 * 000BB5F2: 57                       push    edi
 * 000BB5F3: 56                       push    esi
 * 000BB5F4: 53                       push    ebx
 * 000BB5F5: 83 EC 0C                 sub     esp, 0Ch
 * 000BB5F8: E8 87 D2 F4 FF           call    db_8884
 * 000BB5FD: 3C 01                    cmp     al, 1
 * 000BB5FF: 75 0B                    jnz     short loc_BB60C
 * 000BB601: 66 B8 16 0A              mov     ax, 0A16h
 * 000BB605: E9 1C 01 00 00           jmp     loc_BB726
 * 000BB60A: 90 90                    align 4
 * 000BB60C: 66 C7 45 F2 04 00        mov     [ebp+var_E], 4
 * 000BB612: 8D 45 F2                 lea     eax, [ebp+var_E]
 * 000BB615: 89 45 F8                 mov     [ebp+var_8], eax
 * 000BB618: C7 04 24 01 00 01 00     mov     [esp+2Ch+var_2C], 10001h
 * 000BB61F: 8D 75 F8                 lea     esi, [ebp+var_8]
 * 000BB622: 89 74 24 04              mov     [esp+2Ch+var_28], esi
 * 000BB626: 8D 7D F4                 lea     edi, [ebp+var_C]
 * 000BB629: 89 7C 24 08              mov     [esp+2Ch+var_24], edi
 * 000BB62D: E8 09 2F 01 00           call    os_syscall_91h_06h
 * 000BB632: 8B 5D 08                 mov     ebx, [ebp+arg_0]
 * 000BB635: 8A 43 01                 mov     al, [ebx+1]
 * 000BB638: 88 45 F1                 mov     [ebp+var_F], al
 * 000BB63B: 8D 45 F1                 lea     eax, [ebp+var_F]
 * 000BB63E: 89 45 F8                 mov     [ebp+var_8], eax
 * 000BB641: 89 5D FC                 mov     [ebp+var_4], ebx
 * 000BB644: C7 04 24 01 00 01 00     mov     [esp+2Ch+var_2C], 10001h
 * 000BB64B: 89 74 24 04              mov     [esp+2Ch+var_28], esi
 * 000BB64F: 89 7C 24 08              mov     [esp+2Ch+var_24], edi
 * 000BB653: E8 C8 2E 01 00           call    os_syscall_91h_05h
 * 000BB658: 23 C0                    and     eax, eax
 * 000BB65A: 74 10                    jz      short loc_BB66C
 * 000BB65C: 66 B8 16 0A              mov     ax, 0A16h
 * 000BB660: E9 C1 00 00 00           jmp     loc_BB726
 * 000BB665: 90 90 90 90 90 90 90     db 7 dup(90h)
 * 000BB66C: 83 7D F4 00              cmp     [ebp+var_C], 0
 * 000BB670: 74 0A                    jz      short loc_BB67C
 * 000BB672: 66 B8 11 0A              mov     ax, 0A11h
 * 000BB676: E9 AB 00 00 00           jmp     loc_BB726
 * 000BB67B: 90                       align 4
 * 000BB67C: C6 45 F1 01              mov     [ebp+var_F], 1
 * 000BB680: 8D 45 F1                 lea     eax, [ebp+var_F]
 * 000BB683: 89 45 F8                 mov     [ebp+var_8], eax
 * 000BB686: 89 5D FC                 mov     [ebp+var_4], ebx
 * 000BB689: C7 04 24 01 00 01 00     mov     [esp+2Ch+var_2C], 10001h
 * 000BB690: 89 74 24 04              mov     [esp+2Ch+var_28], esi
 * 000BB694: 89 7C 24 08              mov     [esp+2Ch+var_24], edi
 * 000BB698: E8 68 2E 01 00           call    os_syscall_91h_04h
 * 000BB69D: 23 C0                    and     eax, eax
 * 000BB69F: 74 0B                    jz      short loc_BB6AC
 * 000BB6A1: 66 B8 16 0A              mov     ax, 0A16h
 * 000BB6A5: E9 7C 00 00 00           jmp     loc_BB726
 * 000BB6AA: 90 90                    align 4
 * 000BB6AC: 83 7D F4 00              cmp     [ebp+var_C], 0
 * 000BB6B0: 74 0A                    jz      short loc_BB6BC
 * 000BB6B2: 66 B8 05 00              mov     ax, 5
 * 000BB6B6: EB 6E                    jmp     short loc_BB726
 * 000BB6B8: 90 90 90 90              db 4 dup(90h)
 * 000BB6BC: 80 3B 1B                 cmp     byte ptr [ebx], 1Bh
 * 000BB6BF: 74 0B                    jz      short loc_BB6CC
 * 000BB6C1: 66 B8 12 0A              mov     ax, 0A12h
 * 000BB6C5: EB 5F                    jmp     short loc_BB726
 * 000BB6C7: 90 90 90 90 90           db 5 dup(90h)
 * 000BB6CC: 8D 43 01                 lea     eax, [ebx+1]
 * 000BB6CF: 89 45 FC                 mov     [ebp+var_4], eax
 * 000BB6D2: C7 04 24 01 00 01 00     mov     [esp+2Ch+var_2C], 10001h
 * 000BB6D9: 89 74 24 04              mov     [esp+2Ch+var_28], esi
 * 000BB6DD: 89 7C 24 08              mov     [esp+2Ch+var_24], edi
 * 000BB6E1: E8 1F 2E 01 00           call    os_syscall_91h_04h
 * 000BB6E6: 23 C0                    and     eax, eax
 * 000BB6E8: 74 0A                    jz      short loc_BB6F4
 * 000BB6EA: 66 B8 16 0A              mov     ax, 0A16h
 * 000BB6EE: EB 36                    jmp     short loc_BB726
 * 000BB6F0: 90 90 90 90              db 4 dup(90h)
 * 000BB6F4: 8A 43 01                 mov     al, [ebx+1]
 * 000BB6F7: 04 FE                    add     al, 0FEh
 * 000BB6F9: 83 C3 02                 add     ebx, 2
 * 000BB6FC: 88 45 F1                 mov     [ebp+var_F], al
 * 000BB6FF: 89 5D FC                 mov     [ebp+var_4], ebx
 * 000BB702: C7 04 24 01 00 01 00     mov     [esp+2Ch+var_2C], 10001h
 * 000BB709: 89 74 24 04              mov     [esp+2Ch+var_28], esi
 * 000BB70D: 89 7C 24 08              mov     [esp+2Ch+var_24], edi
 * 000BB711: E8 EF 2D 01 00           call    os_syscall_91h_04h
 * 000BB716: 23 C0                    and     eax, eax
 * 000BB718: 74 0A                    jz      short loc_BB724
 * 000BB71A: 66 B8 16 0A              mov     ax, 0A16h
 * 000BB71E: EB 06                    jmp     short loc_BB726
 * 000BB720: 90 90 90 90              db 4 dup(90h)
 * 000BB724: 2B C0                    sub     eax, eax
 * 000BB726: 8B 5D E0                 mov     ebx, [ebp+var_20]
 * 000BB729: 8B 75 E4                 mov     esi, [ebp+var_1C]
 * 000BB72C: 8B 7D E8                 mov     edi, [ebp+var_18]
 * 000BB72F: 89 EC                    mov     esp, ebp
 * 000BB731: 5D                       pop     ebp
 * 000BB732: C3                       retn
 * ========================================================================== */
// Generic parameter/variable database access (0x1B record header) | [SRX-611] pop_rank=37/1298, sites=22, callers=22, callees=4, size=0x147
__int16 __cdecl db_access(_BYTE *a1)
{
  char v2; // [esp+1Dh] [ebp-Fh] BYREF
  __int16 v3; // [esp+1Eh] [ebp-Eh] BYREF
  int v4; // [esp+20h] [ebp-Ch] BYREF
  __int16 *v5; // [esp+24h] [ebp-8h] BYREF
  _BYTE *v6; // [esp+28h] [ebp-4h]

  if ( (unsigned __int8)db_8884() == 1 )
    return 2582;
  v3 = 4;
  v5 = &v3;
  os_syscall_91h_06h(65537, &v5, &v4);
  v2 = a1[1];
  v5 = (__int16 *)&v2;
  v6 = a1;
  if ( os_syscall_91h_05h(65537, &v5, &v4) )
    return 2582;
  if ( v4 )
    return 2577;
  v2 = 1;
  v5 = (__int16 *)&v2;
  v6 = a1;
  if ( os_syscall_91h_04h(65537, &v5, &v4) )
    return 2582;
  if ( v4 )
    return 5;
  if ( *a1 != 27 )
    return 2578;
  v6 = a1 + 1;
  if ( os_syscall_91h_04h(65537, &v5, &v4) )
    return 2582;
  v2 = a1[1] - 2;
  v6 = a1 + 2;
  if ( os_syscall_91h_04h(65537, &v5, &v4) )
    return 2582;
  else
    return 0;
}


/* ============================================================================
 * db_field_3  @ 0xBA88C   size=0xE0   pop_rank=45/1298
 * calls=21 callers=7
 * note: Database field accessor (id 3) | [SRX-611] pop_rank=45/1298, sites=21, callers=7, callees=1, size=0xE0
 * --- original assembly (address: bytes  mnemonic) ---------------------------
 * 000BA88C: 55                       push    ebp
 * 000BA88D: 89 E5                    mov     ebp, esp
 * 000BA88F: 81 EC 0C 01 00 00        sub     esp, 10Ch
 * 000BA895: 8B 55 08                 mov     edx, [ebp+arg_0]
 * 000BA898: C6 85 FF FE FF FF 00     mov     [ebp+var_101], 0
 * 000BA89F: 57                       push    edi
 * 000BA8A0: 56                       push    esi
 * 000BA8A1: 83 EC 08                 sub     esp, 8
 * 000BA8A4: 66 C7 45 FE 00 00        mov     [ebp+var_2], 0
 * 000BA8AA: 89 95 F8 FE FF FF        mov     [ebp+var_108], edx
 * 000BA8B0: 89 D1                    mov     ecx, edx
 * 000BA8B2: 8A 85 FF FE FF FF        mov     al, [ebp+var_101]
 * 000BA8B8: 80 39 00                 cmp     byte ptr [ecx], 0
 * 000BA8BB: 74 27                    jz      short loc_BA8E4
 * 000BA8BD: 3C FA                    cmp     al, 0FAh
 * 000BA8BF: 76 1B                    jbe     short loc_BA8DC
 * 000BA8C1: 89 8D F8 FE FF FF        mov     [ebp+var_108], ecx
 * 000BA8C7: 88 85 FF FE FF FF        mov     [ebp+var_101], al
 * 000BA8CD: 66 B8 E9 03              mov     ax, 3E9h
 * 000BA8D1: E9 86 00 00 00           jmp     loc_BA95C
 * 000BA8D6: 90 90 90 90 90 90        db 6 dup(90h)
 * 000BA8DC: 40                       inc     eax
 * 000BA8DD: 41                       inc     ecx
 * 000BA8DE: EB D8                    jmp     short loc_BA8B8
 * 000BA8E0: 90 90 90 90              db 4 dup(90h)
 * 000BA8E4: 89 8D F8 FE FF FF        mov     [ebp+var_108], ecx
 * 000BA8EA: 88 85 FF FE FF FF        mov     [ebp+var_101], al
 * 000BA8F0: C6 85 00 FF FF FF 1B     mov     [ebp+var_100], 1Bh
 * 000BA8F7: 89 D6                    mov     esi, edx
 * 000BA8F9: 8D 48 03                 lea     ecx, [eax+3]
 * 000BA8FC: 88 8D 01 FF FF FF        mov     [ebp+var_FF], cl
 * 000BA902: 33 C9                    xor     ecx, ecx
 * 000BA904: 88 C1                    mov     cl, al
 * 000BA906: 0F AC CA 02              shrd    edx, ecx, 2
 * 000BA90A: C1 E9 02                 shr     ecx, 2
 * 000BA90D: FC                       cld
 * 000BA90E: C6 85 02 FF FF FF 41     mov     [ebp+var_FE], 41h ; 'A'
 * 000BA915: 8D BD 03 FF FF FF        lea     edi, [ebp+var_FD]
 * 000BA91B: F3 A5                    rep movsd
 * 000BA91D: 0F A4 D1 02              shld    ecx, edx, 2
 * 000BA921: F3 A4                    rep movsb
 * 000BA923: 8D 85 00 FF FF FF        lea     eax, [ebp+var_100]
 * 000BA929: 89 04 24                 mov     [esp+11Ch+var_11C], eax
 * 000BA92C: E8 BB 0C 00 00           call    db_access
 * 000BA931: 66 89 45 FE              mov     [ebp+var_2], ax
 * 000BA935: 66 23 C0                 and     ax, ax
 * 000BA938: 74 02                    jz      short loc_BA93C
 * 000BA93A: EB 20                    jmp     short loc_BA95C
 * 000BA93C: 8A 8D 03 FF FF FF        mov     cl, [ebp+var_FD]
 * 000BA942: 22 C9                    and     cl, cl
 * 000BA944: 74 16                    jz      short loc_BA95C
 * 000BA946: 33 C0                    xor     eax, eax
 * 000BA948: 88 C8                    mov     al, cl
 * 000BA94A: 66 05 20 4E              add     ax, 4E20h
 * 000BA94E: 25 FF FF 00 00           and     eax, 0FFFFh
 * 000BA953: EB 07                    jmp     short loc_BA95C
 * 000BA955: 90 90 90 90 90 90 90     db 7 dup(90h)
 * 000BA95C: 8B B5 EC FE FF FF        mov     esi, [ebp+var_114]
 * 000BA962: 8B BD F0 FE FF FF        mov     edi, [ebp+var_110]
 * 000BA968: 89 EC                    mov     esp, ebp
 * 000BA96A: 5D                       pop     ebp
 * 000BA96B: C3                       retn
 * ========================================================================== */
// Database field accessor (id 3) | [SRX-611] pop_rank=45/1298, sites=21, callers=7, callees=1, size=0xE0
__int16 __cdecl db_field_3(_BYTE *a1)
{
  _BYTE *v1; // ecx
  unsigned __int8 v2; // al
  __int16 result; // ax
  unsigned __int64 v4; // rt0
  int v5; // ecx
  _BYTE v6[3]; // [esp+1Ch] [ebp-100h] BYREF
  unsigned __int8 v7[251]; // [esp+1Fh] [ebp-FDh] BYREF
  __int16 v8; // [esp+11Ah] [ebp-2h]

  v8 = 0;
  v1 = a1;
  v2 = 0;
  while ( *v1 )
  {
    if ( v2 > 0xFAu )
      return 1001;
    ++v2;
    ++v1;
  }
  v6[0] = 27;
  v6[1] = v2 + 3;
  LODWORD(v4) = a1;
  HIDWORD(v4) = v2;
  v5 = v2 >> 2;
  v6[2] = 65;
  qmemcpy(v7, a1, 4 * v5);
  qmemcpy(&v7[4 * v5], &a1[4 * v5], (unsigned __int64)(unsigned int)(v4 >> 2) >> 30);
  result = db_access(v6);
  v8 = result;
  if ( !result )
  {
    if ( v7[0] )
      return v7[0] + 20000;
  }
  return result;
}


