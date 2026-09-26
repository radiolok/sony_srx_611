/*
 * Sony SRX-611 firmware - C equivalents (Hex-Rays) - prefix 'record'
 * Source image: ROM1-C.bin (80486 real mode, OS+/386 V2.0)
 * Generated from IDA database ROM1-C.bin.i64
 * Functions in this file: 3
 */

/* ============================================================================
 * record_get_field  @ 0x1278C   size=0x11E   pop_rank=9/1298
 * calls=79 callers=42
 * note: Read a field from a 20-byte record table @0x3C080 (switch on field id arg4) | [SRX-611] pop_rank=9/1298, sites=79, callers=42, callees=1, size=0x11E
 * --- original assembly (address: bytes  mnemonic) ---------------------------
 * 0001278C: 55                       push    ebp
 * 0001278D: 89 E5                    mov     ebp, esp
 * 0001278F: 83 EC 0C                 sub     esp, 0Ch
 * 00012792: 8A 45 0C                 mov     al, [ebp+arg_4]
 * 00012795: 04 A7                    add     al, 0A7h; switch with an invalid jump table
 * 00012797: 3C 06                    cmp     al, 6
 * 00012799: 0F 87 BD 00 00 00        ja      def_12869; jumptable 00012869 default case
 * 0001279F: E9 C0 00 00 00           jmp     loc_12864
 * 000127A4: 33 C0                    xor     eax, eax
 * 000127A6: 8A 45 08                 mov     al, [ebp+arg_0]
 * 000127A9: 8D 04 80                 lea     eax, [eax+eax*4]
 * 000127AC: C1 E0 02                 shl     eax, 2
 * 000127AF: 80 B8 80 C0 03 00 01     cmp     byte ptr [eax+3C080h], 1
 * 000127B6: 74 0C                    jz      short loc_127C4
 * 000127B8: 66 B8 BC 36              mov     ax, 36BCh
 * 000127BC: E9 E5 00 00 00           jmp     loc_128A6
 * 000127C1: 90 90 90                 align 4
 * 000127C4: 8B 80 88 C0 03 00        mov     eax, dword ptr ds:loc_3C088[eax]
 * 000127CA: 89 45 FC                 mov     [ebp+var_4], eax
 * 000127CD: E9 BE 00 00 00           jmp     loc_12890
 * 000127D2: 90 90                    align 4
 * 000127D4: 33 C0                    xor     eax, eax
 * 000127D6: 8A 45 08                 mov     al, [ebp+arg_0]
 * 000127D9: 8D 04 80                 lea     eax, [eax+eax*4]
 * 000127DC: C1 E0 02                 shl     eax, 2
 * 000127DF: 80 B8 81 C0 03 00 01     cmp     byte ptr [eax+3C081h], 1
 * 000127E6: 74 0C                    jz      short loc_127F4
 * 000127E8: 66 B8 BC 36              mov     ax, 36BCh
 * 000127EC: E9 B5 00 00 00           jmp     loc_128A6
 * 000127F1: 90 90 90                 align 4
 * 000127F4: 8B 80 88 C0 03 00        mov     eax, dword ptr ds:loc_3C088[eax]
 * 000127FA: 89 45 FC                 mov     [ebp+var_4], eax
 * 000127FD: E9 8E 00 00 00           jmp     loc_12890
 * 00012802: 90 90                    align 4
 * 00012804: 33 C0                    xor     eax, eax
 * 00012806: 8A 45 08                 mov     al, [ebp+arg_0]
 * 00012809: 8D 04 80                 lea     eax, [eax+eax*4]
 * 0001280C: C1 E0 02                 shl     eax, 2
 * 0001280F: 80 B8 30 C0 03 00 01     cmp     ds:byte_3C030[eax], 1
 * 00012816: 74 0C                    jz      short loc_12824
 * 00012818: 66 B8 BC 36              mov     ax, 36BCh
 * 0001281C: E9 85 00 00 00           jmp     loc_128A6
 * 00012821: 90 90 90                 align 4
 * 00012824: 8B 80 38 C0 03 00        mov     eax, ds:dword_3C038[eax]
 * 0001282A: 89 45 FC                 mov     [ebp+var_4], eax
 * 0001282D: EB 61                    jmp     short loc_12890
 * 0001282F: 90 90 90 90 90           db 5 dup(90h)
 * 00012834: 80 3D 18 C0 03 00 01     cmp     ds:byte_3C018, 1
 * 0001283B: 74 07                    jz      short loc_12844
 * 0001283D: 66 B8 BC 36              mov     ax, 36BCh
 * 00012841: EB 63                    jmp     short loc_128A6
 * 00012843: 90                       align 4
 * 00012844: A1 20 C0 03 00           mov     eax, ds:dword_3C020
 * 00012849: 89 45 FC                 mov     [ebp+var_4], eax
 * 0001284C: EB 42                    jmp     short loc_12890
 * 0001284E: 90 90 90 90 90 90        db 6 dup(90h)
 * 00012854: 2B C0                    sub     eax, eax
 * 00012856: EB 4E                    jmp     short loc_128A6
 * 00012858: 90 90 90 90              db 4 dup(90h)
 * 0001285C: 66 B8 BB 36              mov     ax, 36BBh; jumptable 00012869 default case
 * 00012860: EB 44                    jmp     short loc_128A6
 * 00012862: 90 90                    align 4
 * 00012864: 25 FF 00 00 00           and     eax, 0FFh
 * 00012869: 2E FF 24 85 74 28 E1 FF  jmp     dword ptr cs:[eax*4-1ED78Ch]; switch jump
 * 00012871: 90 90 90                 align 4
 * 00012874: 54                       push    esp
 * 00012875: 28 E1                    sub     cl, ah
 * 00012877: FF 54 28 E1              call    dword ptr [eax+ebp-1Fh]
 * 0001287B: FF 54 28 E1              call    dword ptr [eax+ebp-1Fh]
 * 0001287F: FF A4 27 E1 FF D4 27     jmp     dword ptr [edi+27D4FFE1h]
 * 00012886: E1 FF 04 28              dw 0FFE1h
 * 0001288A: E1 FF 34 28              dw 0FFE1h
 * 0001288E: E1 FF                    dw 0FFE1h
 * 00012890: 89 04 24                 mov     [esp+0Ch+var_C], eax
 * 00012893: E8 B3 BA 0B 00           call    os_syscall_90h_37h
 * 00012898: 23 C0                    and     eax, eax
 * 0001289A: 74 08                    jz      short loc_128A4
 * 0001289C: 66 B8 B0 36              mov     ax, 36B0h
 * 000128A0: EB 04                    jmp     short loc_128A6
 * 000128A2: 90 90                    align 4
 * 000128A4: 2B C0                    sub     eax, eax
 * 000128A6: 89 EC                    mov     esp, ebp
 * 000128A8: 5D                       pop     ebp
 * 000128A9: C3                       retn
 * ========================================================================== */
/*
 * Manually reconstructed from the assembly above (Hex-Rays could not parse the
 * invalid switch jump table at 0x12869).
 *   arg0 = record index (0-based), arg1 = field selector; switch index = (field + 0xA7) & 0xFF.
 * Record tables: 20-byte entries at 0x3C080 (flag @+0/+1, value @+8) and at 0x3C030.
 * A field is valid only when its flag byte equals 1, otherwise return 0x36BC.
 * On success the value is forwarded to os_syscall_90h_37h; syscall failure -> 0x36B0.
 */
int record_get_field(uint8_t idx, uint8_t field)
{
    uint8_t *rec = (uint8_t *)(0x3C080u + (uint32_t)idx * 20u);
    uint8_t *alt = (uint8_t *)(0x3C030u + (uint32_t)idx * 20u);
    uint32_t val;

    switch ((uint8_t)(field + 0xA7u)) {
    case 0: if (rec[0x00] != 1) return 0x36BC; val = *(uint32_t *)(rec + 8); break;
    case 1: if (rec[0x01] != 1) return 0x36BC; val = *(uint32_t *)(rec + 8); break;
    case 2: if (alt[0x00] != 1) return 0x36BC; val = *(uint32_t *)(alt + 8); break;
    case 3: if (*(uint8_t *)0x3C018u != 1) return 0x36BC; val = *(uint32_t *)0x3C020u; break;
    case 4: return 0;
    default: return 0x36BB;                 /* illegal field */
    }

    if (os_syscall_90h_37h(val) != 0)
        return 0x36B0;
    return 0;
}


/* ============================================================================
 * record_get_field2  @ 0x1265C   size=0x12E   pop_rank=12/1298
 * calls=46 callers=40
 * note: Read a field from the 20-byte record table @0x3C080 (variant of record_get_field) | [SRX-611] pop_rank=12/1298, sites=46, callers=40, callees=1, size=0x12E
 * --- original assembly (address: bytes  mnemonic) ---------------------------
 * 0001265C: 55                       push    ebp
 * 0001265D: 89 E5                    mov     ebp, esp
 * 0001265F: 83 EC 14                 sub     esp, 14h
 * 00012662: 8A 45 0C                 mov     al, [ebp+arg_4]
 * 00012665: 04 A7                    add     al, 0A7h; switch with an invalid jump table
 * 00012667: 3C 06                    cmp     al, 6
 * 00012669: 0F 87 C5 00 00 00        ja      def_12741; jumptable 00012741 default case
 * 0001266F: E9 C8 00 00 00           jmp     loc_1273C
 * 00012674: 33 C0                    xor     eax, eax
 * 00012676: 8A 45 08                 mov     al, [ebp+arg_0]
 * 00012679: 8D 04 80                 lea     eax, [eax+eax*4]
 * 0001267C: C1 E0 02                 shl     eax, 2
 * 0001267F: 80 B8 80 C0 03 00 01     cmp     byte ptr [eax+3C080h], 1
 * 00012686: 74 0C                    jz      short loc_12694
 * 00012688: 66 B8 BC 36              mov     ax, 36BCh
 * 0001268C: E9 F5 00 00 00           jmp     loc_12786
 * 00012691: 90 90 90                 align 4
 * 00012694: 8B 80 88 C0 03 00        mov     eax, dword ptr ds:loc_3C088[eax]
 * 0001269A: 89 45 FC                 mov     [ebp+var_4], eax
 * 0001269D: E9 C6 00 00 00           jmp     loc_12768
 * 000126A2: 90 90                    align 4
 * 000126A4: 33 C0                    xor     eax, eax
 * 000126A6: 8A 45 08                 mov     al, [ebp+arg_0]
 * 000126A9: 8D 04 80                 lea     eax, [eax+eax*4]
 * 000126AC: C1 E0 02                 shl     eax, 2
 * 000126AF: 80 B8 81 C0 03 00 01     cmp     byte ptr [eax+3C081h], 1
 * 000126B6: 74 0C                    jz      short loc_126C4
 * 000126B8: 66 B8 BC 36              mov     ax, 36BCh
 * 000126BC: E9 C5 00 00 00           jmp     loc_12786
 * 000126C1: 90 90 90                 align 4
 * 000126C4: 8B 80 88 C0 03 00        mov     eax, dword ptr ds:loc_3C088[eax]
 * 000126CA: 89 45 FC                 mov     [ebp+var_4], eax
 * 000126CD: E9 96 00 00 00           jmp     loc_12768
 * 000126D2: 90 90                    align 4
 * 000126D4: 33 C0                    xor     eax, eax
 * 000126D6: 8A 45 08                 mov     al, [ebp+arg_0]
 * 000126D9: 8D 04 80                 lea     eax, [eax+eax*4]
 * 000126DC: C1 E0 02                 shl     eax, 2
 * 000126DF: 80 B8 30 C0 03 00 01     cmp     ds:byte_3C030[eax], 1
 * 000126E6: 74 0C                    jz      short loc_126F4
 * 000126E8: 66 B8 BC 36              mov     ax, 36BCh
 * 000126EC: E9 95 00 00 00           jmp     loc_12786
 * 000126F1: 90 90 90                 align 4
 * 000126F4: 8B 80 38 C0 03 00        mov     eax, ds:dword_3C038[eax]
 * 000126FA: 89 45 FC                 mov     [ebp+var_4], eax
 * 000126FD: EB 69                    jmp     short loc_12768
 * 000126FF: 90 90 90 90 90           db 5 dup(90h)
 * 00012704: 80 3D 18 C0 03 00 01     cmp     ds:byte_3C018, 1
 * 0001270B: 74 0F                    jz      short loc_1271C
 * 0001270D: 66 B8 BC 36              mov     ax, 36BCh
 * 00012711: E9 70 00 00 00           jmp     loc_12786
 * 00012716: 90 90 90 90 90 90        db 6 dup(90h)
 * 0001271C: A1 20 C0 03 00           mov     eax, ds:dword_3C020
 * 00012721: 89 45 FC                 mov     [ebp+var_4], eax
 * 00012724: EB 42                    jmp     short loc_12768
 * 00012726: 90 90 90 90 90 90        db 6 dup(90h)
 * 0001272C: 2B C0                    sub     eax, eax
 * 0001272E: EB 56                    jmp     short loc_12786
 * 00012730: 90 90 90 90              db 4 dup(90h)
 * 00012734: 66 B8 BB 36              mov     ax, 36BBh; jumptable 00012741 default case
 * 00012738: EB 4C                    jmp     short loc_12786
 * 0001273A: 90 90                    align 4
 * 0001273C: 25 FF 00 00 00           and     eax, 0FFh
 * 00012741: 2E FF 24 85 4C 27 E1 FF  jmp     dword ptr cs:[eax*4-1ED8B4h]; switch jump
 * 00012749: 90 90 90 2C 27           align 4
 * 0001274E: E1 FF 2C 27              dw 0FFE1h
 * 00012752: E1 FF 2C 27              dw 0FFE1h
 * 00012756: E1 FF                    dw 0FFE1h
 * 00012758: 74 26 E1 FF A4 26 E1 FF D4 26 E1 FF 04 27 E1 FF dd 0FFE12674h, 0FFE126A4h, 0FFE126D4h, 0FFE12704h
 * 00012768: 89 04 24                 mov     [esp+14h+var_14], eax
 * 0001276B: 2B C0                    sub     eax, eax
 * 0001276D: 89 44 24 04              mov     [esp+14h+var_10], eax
 * 00012771: 89 44 24 08              mov     [esp+14h+var_C], eax
 * 00012775: E8 E2 BB 0B 00           call    os_syscall_90h_36h
 * 0001277A: 23 C0                    and     eax, eax
 * 0001277C: 74 06                    jz      short loc_12784
 * 0001277E: 66 B8 B0 36              mov     ax, 36B0h
 * 00012782: EB 02                    jmp     short loc_12786
 * 00012784: 2B C0                    sub     eax, eax
 * 00012786: 89 EC                    mov     esp, ebp
 * 00012788: 5D                       pop     ebp
 * 00012789: C3                       retn
 * ========================================================================== */
/*
 * Manually reconstructed from the assembly above (invalid switch jump table at 0x12741).
 * Same field/record logic as record_get_field, but the success path passes
 * (value, 0, 0) to os_syscall_90h_36h instead.
 */
int record_get_field2(uint8_t idx, uint8_t field)
{
    uint8_t *rec = (uint8_t *)(0x3C080u + (uint32_t)idx * 20u);
    uint8_t *alt = (uint8_t *)(0x3C030u + (uint32_t)idx * 20u);
    uint32_t val;

    switch ((uint8_t)(field + 0xA7u)) {
    case 0: if (rec[0x00] != 1) return 0x36BC; val = *(uint32_t *)(rec + 8); break;
    case 1: if (rec[0x01] != 1) return 0x36BC; val = *(uint32_t *)(rec + 8); break;
    case 2: if (alt[0x00] != 1) return 0x36BC; val = *(uint32_t *)(alt + 8); break;
    case 3: if (*(uint8_t *)0x3C018u != 1) return 0x36BC; val = *(uint32_t *)0x3C020u; break;
    case 4: return 0;
    default: return 0x36BB;                 /* illegal field */
    }

    if (os_syscall_90h_36h(val, 0, 0) != 0)
        return 0x36B0;
    return 0;
}


/* ============================================================================
 * record_get_pair  @ 0xBA24   size=0x89   pop_rank=27/1298
 * calls=26 callers=8
 * note: Read a 16-byte record, return two dwords | [SRX-611] pop_rank=27/1298, sites=26, callers=8, callees=0, size=0x89, leaf
 * --- original assembly (address: bytes  mnemonic) ---------------------------
 * 0000BA24: 55                       push    ebp
 * 0000BA25: 89 E5                    mov     ebp, esp
 * 0000BA27: 83 EC 04                 sub     esp, 4
 * 0000BA2A: 8A 4D 08                 mov     cl, [ebp+arg_0]
 * 0000BA2D: 80 F9 01                 cmp     cl, 1
 * 0000BA30: 72 08                    jb      short loc_BA3A
 * 0000BA32: 3A 0D 50 4A 00 00        cmp     cl, byte ptr ds:loc_4A4E+2
 * 0000BA38: 76 0A                    jbe     short loc_BA44
 * 0000BA3A: 66 B8 0C 2B              mov     ax, 2B0Ch
 * 0000BA3E: EB 69                    jmp     short loc_BAA9
 * 0000BA40: 90 90 90 90              db 4 dup(90h)
 * 0000BA44: 8A 45 0C                 mov     al, [ebp+arg_4]
 * 0000BA47: 22 C0                    and     al, al
 * 0000BA49: 74 04                    jz      short loc_BA4F
 * 0000BA4B: 3C 04                    cmp     al, 4
 * 0000BA4D: 76 0D                    jbe     short loc_BA5C
 * 0000BA4F: 66 B8 0F 2B              mov     ax, 2B0Fh
 * 0000BA53: EB 54                    jmp     short loc_BAA9
 * 0000BA55: 90 90 90 90 90 90 90     db 7 dup(90h)
 * 0000BA5C: 8A 55 10                 mov     dl, [ebp+arg_8]
 * 0000BA5F: 80 FA 01                 cmp     dl, 1
 * 0000BA62: 76 08                    jbe     short loc_BA6C
 * 0000BA64: 66 B8 15 2B              mov     ax, 2B15h
 * 0000BA68: EB 3F                    jmp     short loc_BAA9
 * 0000BA6A: 90 90                    align 4
 * 0000BA6C: 25 FF 00 00 00           and     eax, 0FFh
 * 0000BA71: C1 E0 04                 shl     eax, 4
 * 0000BA74: 83 C0 F0                 add     eax, 0FFFFFFF0h
 * 0000BA77: 81 E2 FF 00 00 00        and     edx, 0FFh
 * 0000BA7D: 8D 14 D0                 lea     edx, [eax+edx*8]
 * 0000BA80: 33 C0                    xor     eax, eax
 * 0000BA82: 88 C8                    mov     al, cl
 * 0000BA84: 89 C1                    mov     ecx, eax
 * 0000BA86: C1 E1 06                 shl     ecx, 6
 * 0000BA89: 2B C8                    sub     ecx, eax
 * 0000BA8B: 8D 0C 88                 lea     ecx, [eax+ecx*4]
 * 0000BA8E: C1 E1 02                 shl     ecx, 2
 * 0000BA91: 8B 84 11 F0 46 00 00     mov     eax, [ecx+edx+46F0h]
 * 0000BA98: 8B 94 11 F4 46 00 00     mov     edx, [ecx+edx+46F4h]
 * 0000BA9F: 8B 4D 14                 mov     ecx, [ebp+arg_C]
 * 0000BAA2: 89 01                    mov     [ecx], eax
 * 0000BAA4: 89 51 04                 mov     [ecx+4], edx
 * 0000BAA7: 2B C0                    sub     eax, eax
 * 0000BAA9: 89 EC                    mov     esp, ebp
 * 0000BAAB: 5D                       pop     ebp
 * 0000BAAC: C3                       retn
 * ========================================================================== */
// Read a 16-byte record, return two dwords | [SRX-611] pop_rank=27/1298, sites=26, callers=8, callees=0, size=0x89, leaf
__int16 __cdecl record_get_pair(unsigned __int8 a1, unsigned __int8 a2, unsigned __int8 a3, _DWORD *a4)
{
  int v5; // edx
  int v6; // ecx
  int v7; // eax
  int v8; // edx

  if ( !a1 || a1 > *(&loc_4A4E + 2) )
    return 11020;
  if ( !a2 || a2 > 4u )
    return 11023;
  if ( a3 > 1u )
    return 11029;
  v5 = 16 * a2 - 16 + 8 * a3;
  v6 = 1012 * a1;
  v7 = *(_DWORD *)(v6 + v5 + 18160);
  v8 = *(_DWORD *)(v6 + v5 + 18164);
  *a4 = v7;
  a4[1] = v8;
  return 0;
}


