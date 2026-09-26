/*
 * Sony SRX-611 firmware - LUNA object-code interpreter/decoder - prefix 'fn'
 * Source: ROM1-C.bin (80486 real mode, OS+/386 V2.0)
 * Functions: 6. The LUNA language compiles robot programs to object code;
 * this cluster decodes opcodes/tokens and formats operands.
 */

/* ============================================================================
 * fn_C7C14  @ 0xC7C14   size=0x444   callers=17
 * note: [SRX-611] pop_rank=56/1298, sites=17, callers=17, callees=12, size=0x444
 * --- original assembly (address: bytes  mnemonic) ---------------------------
 * 000C7C14: 55                       push    ebp
 * 000C7C15: 89 E5                    mov     ebp, esp
 * 000C7C17: 83 EC 50                 sub     esp, 50h
 * 000C7C1A: 8B 45 14                 mov     eax, [ebp+arg_C]
 * 000C7C1D: 66 C7 45 EE 00 00        mov     [ebp+var_12], 0
 * 000C7C23: 57                       push    edi
 * 000C7C24: 56                       push    esi
 * 000C7C25: 53                       push    ebx
 * 000C7C26: 83 EC 10                 sub     esp, 10h
 * 000C7C29: 80 7D 08 00              cmp     [ebp+arg_0], 0
 * 000C7C2D: 8D 70 01                 lea     esi, [eax+1]
 * 000C7C30: 75 12                    jnz     short loc_C7C44
 * 000C7C32: 66 8B 15 B0 F1 00 00     mov     dx, word ptr ds:loc_F1AC+4
 * 000C7C39: 66 89 10                 mov     [eax], dx
 * 000C7C3C: 89 75 14                 mov     [ebp+arg_C], esi
 * 000C7C3F: 8D 4E 01                 lea     ecx, [esi+1]
 * 000C7C42: EB 04                    jmp     short loc_C7C48
 * 000C7C44: 89 F1                    mov     ecx, esi
 * 000C7C46: 89 C6                    mov     esi, eax
 * 000C7C48: 8B 5D 10                 mov     ebx, [ebp+arg_8]
 * 000C7C4B: 80 3B C8                 cmp     byte ptr [ebx], 0C8h
 * 000C7C4E: 75 14                    jnz     short loc_C7C64
 * 000C7C50: C6 06 3A                 mov     byte ptr [esi], 3Ah ; ':'
 * 000C7C53: 89 4D 14                 mov     [ebp+arg_C], ecx
 * 000C7C56: 43                       inc     ebx
 * 000C7C57: 89 5D 10                 mov     [ebp+arg_8], ebx
 * 000C7C5A: 8D 41 01                 lea     eax, [ecx+1]
 * 000C7C5D: EB 09                    jmp     short loc_C7C68
 * 000C7C5F: 90 90 90 90 90           db 5 dup(90h)
 * 000C7C64: 89 C8                    mov     eax, ecx
 * 000C7C66: 89 F1                    mov     ecx, esi
 * 000C7C68: 66 8B 15 B4 F1 00 00     mov     dx, word ptr ds:loc_F1B4
 * 000C7C6F: 66 89 11                 mov     [ecx], dx
 * 000C7C72: 80 7D 08 00              cmp     [ebp+arg_0], 0
 * 000C7C76: 89 45 14                 mov     [ebp+arg_C], eax
 * 000C7C79: 75 0E                    jnz     short loc_C7C89
 * 000C7C7B: 66 8B 15 B0 F1 00 00     mov     dx, word ptr ds:loc_F1AC+4
 * 000C7C82: 66 89 10                 mov     [eax], dx
 * 000C7C85: 40                       inc     eax
 * 000C7C86: 89 45 14                 mov     [ebp+arg_C], eax
 * 000C7C89: 89 1C 24                 mov     [esp+6Ch+var_6C], ebx
 * 000C7C8C: 8D 45 B8                 lea     eax, [ebp+var_48]
 * 000C7C8F: 89 44 24 04              mov     [esp+6Ch+var_68], eax
 * 000C7C93: E8 C4 03 00 00           call    fn_C805C
 * 000C7C98: 66 89 45 EE              mov     [ebp+var_12], ax
 * 000C7C9C: 66 23 C0                 and     ax, ax
 * 000C7C9F: 74 0B                    jz      short loc_C7CAC
 * 000C7CA1: E9 A5 03 00 00           jmp     loc_C804B
 * 000C7CA6: 90 90 90 90 90 90        db 6 dup(90h)
 * 000C7CAC: C6 45 B3 00              mov     [ebp+var_4D], 0
 * 000C7CB0: 8A 45 B3                 mov     al, [ebp+var_4D]
 * 000C7CB3: 33 D2                    xor     edx, edx
 * 000C7CB5: 88 C2                    mov     dl, al
 * 000C7CB7: 03 D5                    add     edx, ebp
 * 000C7CB9: 80 7A B9 FF              cmp     byte ptr [edx-47h], 0FFh
 * 000C7CBD: 74 05                    jz      short loc_C7CC4
 * 000C7CBF: 40                       inc     eax
 * 000C7CC0: EB F1                    jmp     short loc_C7CB3
 * 000C7CC2: 90 90                    align 4
 * 000C7CC4: C6 45 B2 01              mov     [ebp+var_4E], 1
 * 000C7CC8: 8A 4D B2                 mov     cl, [ebp+var_4E]
 * 000C7CCB: 89 4D F4                 mov     [ebp+var_C], ecx
 * 000C7CCE: 88 45 B3                 mov     [ebp+var_4D], al
 * 000C7CD1: 8B 7D 0C                 mov     edi, [ebp+arg_4]
 * 000C7CD4: C7 45 FC 01 00 00 00     mov     [ebp+var_4], 1
 * 000C7CDB: 89 45 F8                 mov     [ebp+var_8], eax
 * 000C7CDE: 8B 75 14                 mov     esi, [ebp+arg_C]
 * 000C7CE1: 66 8B 4D EE              mov     cx, [ebp+var_12]
 * 000C7CE5: 89 5D F0                 mov     [ebp+var_10], ebx
 * 000C7CE8: EB 1B                    jmp     short loc_C7D05
 * 000C7CEA: 90 90                    align 4
 * 000C7CEC: 33 D2                    xor     edx, edx
 * 000C7CEE: 88 CA                    mov     dl, cl
 * 000C7CF0: 03 D5                    add     edx, ebp
 * 000C7CF2: C7 45 F4 00 00 00 00     mov     [ebp+var_C], 0
 * 000C7CF9: C7 45 FC 00 00 00 00     mov     [ebp+var_4], 0
 * 000C7D00: 89 4D F8                 mov     [ebp+var_8], ecx
 * 000C7D03: 89 C1                    mov     ecx, eax
 * 000C7D05: 33 DB                    xor     ebx, ebx
 * 000C7D07: 8A 5A B8                 mov     bl, [edx-48h]
 * 000C7D0A: 03 5D F0                 add     ebx, [ebp+var_10]
 * 000C7D0D: 8A 03                    mov     al, [ebx]
 * 000C7D0F: 04 40                    add     al, 40h ; '@'; switch with an invalid jump table
 * 000C7D11: 3C 07                    cmp     al, 7
 * 000C7D13: 0F 87 C3 02 00 00        ja      def_C8001; jumptable 000C8001 default case
 * 000C7D19: E9 DE 02 00 00           jmp     loc_C7FFC
 * 000C7D1E: 90 90 90 90 90 90        db 6 dup(90h)
 * 000C7D24: 8A 45 08                 mov     al, [ebp+arg_0]
 * 000C7D27: 89 04 24                 mov     [esp+6Ch+var_6C], eax
 * 000C7D2A: 89 7C 24 04              mov     [esp+6Ch+var_68], edi
 * 000C7D2E: 89 74 24 08              mov     [esp+6Ch+var_64], esi
 * 000C7D32: 8D 43 01                 lea     eax, [ebx+1]
 * 000C7D35: 89 44 24 0C              mov     [esp+6Ch+var_60], eax
 * 000C7D39: E8 EE 08 00 00           call    fn_C862C
 * 000C7D3E: 66 23 C0                 and     ax, ax
 * 000C7D41: 74 21                    jz      short loc_C7D64
 * 000C7D43: 8B 4D F4                 mov     ecx, [ebp+var_C]
 * 000C7D46: 88 4D B2                 mov     [ebp+var_4E], cl
 * 000C7D49: 8B 4D F8                 mov     ecx, [ebp+var_8]
 * 000C7D4C: 89 75 14                 mov     [ebp+arg_C], esi
 * 000C7D4F: 88 4D B3                 mov     [ebp+var_4D], cl
 * 000C7D52: 89 5D B4                 mov     [ebp+var_4C], ebx
 * 000C7D55: 66 89 45 EE              mov     [ebp+var_12], ax
 * 000C7D59: E9 ED 02 00 00           jmp     loc_C804B
 * 000C7D5E: 90 90 90 90 90 90        db 6 dup(90h)
 * 000C7D64: 80 7D F8 00              cmp     byte ptr [ebp+var_8], 0
 * 000C7D68: 74 12                    jz      short loc_C7D7C
 * 000C7D6A: 8A 0E                    mov     cl, [esi]
 * 000C7D6C: 80 F9 2A                 cmp     cl, 2Ah ; '*'
 * 000C7D6F: 74 0B                    jz      short loc_C7D7C
 * 000C7D71: 80 F9 2B                 cmp     cl, 2Bh ; '+'
 * 000C7D74: 74 06                    jz      short loc_C7D7C
 * 000C7D76: 4E                       dec     esi
 * 000C7D77: EB F1                    jmp     short loc_C7D6A
 * 000C7D79: 90 90 90                 align 4
 * 000C7D7C: E9 AB 02 00 00           jmp     loc_C802C
 * 000C7D81: 90 90 90                 align 4
 * 000C7D84: 8A 45 08                 mov     al, [ebp+arg_0]
 * 000C7D87: 89 04 24                 mov     [esp+6Ch+var_6C], eax
 * 000C7D8A: 89 7C 24 04              mov     [esp+6Ch+var_68], edi
 * 000C7D8E: 89 74 24 08              mov     [esp+6Ch+var_64], esi
 * 000C7D92: 8D 43 01                 lea     eax, [ebx+1]
 * 000C7D95: 89 44 24 0C              mov     [esp+6Ch+var_60], eax
 * 000C7D99: E8 2E 09 00 00           call    fn_C86CC
 * 000C7D9E: 66 23 C0                 and     ax, ax
 * 000C7DA1: 74 21                    jz      short loc_C7DC4
 * 000C7DA3: 8B 4D F4                 mov     ecx, [ebp+var_C]
 * 000C7DA6: 88 4D B2                 mov     [ebp+var_4E], cl
 * 000C7DA9: 8B 4D F8                 mov     ecx, [ebp+var_8]
 * 000C7DAC: 89 75 14                 mov     [ebp+arg_C], esi
 * 000C7DAF: 88 4D B3                 mov     [ebp+var_4D], cl
 * 000C7DB2: 89 5D B4                 mov     [ebp+var_4C], ebx
 * 000C7DB5: 66 89 45 EE              mov     [ebp+var_12], ax
 * 000C7DB9: E9 8D 02 00 00           jmp     loc_C804B
 * 000C7DBE: 90 90 90 90 90 90        db 6 dup(90h)
 * 000C7DC4: 80 7D F8 00              cmp     byte ptr [ebp+var_8], 0
 * 000C7DC8: 74 12                    jz      short loc_C7DDC
 * 000C7DCA: 8A 0E                    mov     cl, [esi]
 * 000C7DCC: 80 F9 2A                 cmp     cl, 2Ah ; '*'
 * 000C7DCF: 74 0B                    jz      short loc_C7DDC
 * 000C7DD1: 80 F9 2B                 cmp     cl, 2Bh ; '+'
 * 000C7DD4: 74 06                    jz      short loc_C7DDC
 * 000C7DD6: 4E                       dec     esi
 * 000C7DD7: EB F1                    jmp     short loc_C7DCA
 * 000C7DD9: 90 90 90                 align 4
 * 000C7DDC: E9 4B 02 00 00           jmp     loc_C802C
 * 000C7DE1: 90 90 90                 align 4
 * 000C7DE4: 8A 45 08                 mov     al, [ebp+arg_0]
 * 000C7DE7: 89 04 24                 mov     [esp+6Ch+var_6C], eax
 * 000C7DEA: 89 7C 24 04              mov     [esp+6Ch+var_68], edi
 * 000C7DEE: 89 74 24 08              mov     [esp+6Ch+var_64], esi
 * 000C7DF2: 8D 43 01                 lea     eax, [ebx+1]
 * 000C7DF5: 89 44 24 0C              mov     [esp+6Ch+var_60], eax
 * 000C7DF9: E8 BE 03 00 00           call    fn_C81BC
 * 000C7DFE: 66 23 C0                 and     ax, ax
 * 000C7E01: 74 21                    jz      short loc_C7E24
 * 000C7E03: 8B 4D F4                 mov     ecx, [ebp+var_C]
 * 000C7E06: 88 4D B2                 mov     [ebp+var_4E], cl
 * 000C7E09: 8B 4D F8                 mov     ecx, [ebp+var_8]
 * 000C7E0C: 89 75 14                 mov     [ebp+arg_C], esi
 * 000C7E0F: 88 4D B3                 mov     [ebp+var_4D], cl
 * 000C7E12: 89 5D B4                 mov     [ebp+var_4C], ebx
 * 000C7E15: 66 89 45 EE              mov     [ebp+var_12], ax
 * 000C7E19: E9 2D 02 00 00           jmp     loc_C804B
 * 000C7E1E: 90 90 90 90 90 90        db 6 dup(90h)
 * 000C7E24: E9 03 02 00 00           jmp     loc_C802C
 * 000C7E29: 90 90 90                 align 4
 * 000C7E2C: 8A 45 08                 mov     al, [ebp+arg_0]
 * 000C7E2F: 89 04 24                 mov     [esp+6Ch+var_6C], eax
 * 000C7E32: 89 7C 24 04              mov     [esp+6Ch+var_68], edi
 * 000C7E36: 89 74 24 08              mov     [esp+6Ch+var_64], esi
 * 000C7E3A: 8D 43 01                 lea     eax, [ebx+1]
 * 000C7E3D: 89 44 24 0C              mov     [esp+6Ch+var_60], eax
 * 000C7E41: E8 26 04 00 00           call    fn_C826C
 * 000C7E46: 66 23 C0                 and     ax, ax
 * 000C7E49: 74 21                    jz      short loc_C7E6C
 * 000C7E4B: 8B 4D F4                 mov     ecx, [ebp+var_C]
 * 000C7E4E: 88 4D B2                 mov     [ebp+var_4E], cl
 * 000C7E51: 8B 4D F8                 mov     ecx, [ebp+var_8]
 * 000C7E54: 89 75 14                 mov     [ebp+arg_C], esi
 * 000C7E57: 88 4D B3                 mov     [ebp+var_4D], cl
 * 000C7E5A: 89 5D B4                 mov     [ebp+var_4C], ebx
 * 000C7E5D: 66 89 45 EE              mov     [ebp+var_12], ax
 * 000C7E61: E9 E5 01 00 00           jmp     loc_C804B
 * 000C7E66: 90 90 90 90 90 90        db 6 dup(90h)
 * 000C7E6C: E9 BB 01 00 00           jmp     loc_C802C
 * 000C7E71: 90 90 90                 align 4
 * 000C7E74: 8D 4B 01                 lea     ecx, [ebx+1]
 * 000C7E77: 80 7D FC 01              cmp     byte ptr [ebp+var_4], 1
 * 000C7E7B: 74 0B                    jz      short loc_C7E88
 * 000C7E7D: 80 3E 2B                 cmp     byte ptr [esi], 2Bh ; '+'
 * 000C7E80: 75 22                    jnz     short loc_C7EA4
 * 000C7E82: 80 7E FF 2A              cmp     byte ptr [esi-1], 2Ah ; '*'
 * 000C7E86: 74 1C                    jz      short loc_C7EA4
 * 000C7E88: 8A 45 08                 mov     al, [ebp+arg_0]
 * 000C7E8B: 89 04 24                 mov     [esp+6Ch+var_6C], eax
 * 000C7E8E: 89 7C 24 04              mov     [esp+6Ch+var_68], edi
 * 000C7E92: 89 74 24 08              mov     [esp+6Ch+var_64], esi
 * 000C7E96: 89 4C 24 0C              mov     [esp+6Ch+var_60], ecx
 * 000C7E9A: E8 4D 05 00 00           call    fn_C83EC
 * 000C7E9F: EB 1B                    jmp     short loc_C7EBC
 * 000C7EA1: 90 90 90                 align 4
 * 000C7EA4: 8A 45 08                 mov     al, [ebp+arg_0]
 * 000C7EA7: 89 04 24                 mov     [esp+6Ch+var_6C], eax
 * 000C7EAA: 89 7C 24 04              mov     [esp+6Ch+var_68], edi
 * 000C7EAE: 89 74 24 08              mov     [esp+6Ch+var_64], esi
 * 000C7EB2: 89 4C 24 0C              mov     [esp+6Ch+var_60], ecx
 * 000C7EB6: E8 69 04 00 00           call    fn_C8324
 * 000C7EBB: 46                       inc     esi
 * 000C7EBC: 66 23 C0                 and     ax, ax
 * 000C7EBF: 74 1B                    jz      short loc_C7EDC
 * 000C7EC1: 8B 4D F4                 mov     ecx, [ebp+var_C]
 * 000C7EC4: 88 4D B2                 mov     [ebp+var_4E], cl
 * 000C7EC7: 8B 4D F8                 mov     ecx, [ebp+var_8]
 * 000C7ECA: 89 75 14                 mov     [ebp+arg_C], esi
 * 000C7ECD: 88 4D B3                 mov     [ebp+var_4D], cl
 * 000C7ED0: 89 5D B4                 mov     [ebp+var_4C], ebx
 * 000C7ED3: 66 89 45 EE              mov     [ebp+var_12], ax
 * 000C7ED7: E9 6F 01 00 00           jmp     loc_C804B
 * 000C7EDC: E9 4B 01 00 00           jmp     loc_C802C
 * 000C7EE1: 90 90 90                 align 4
 * 000C7EE4: 8D 4B 01                 lea     ecx, [ebx+1]
 * 000C7EE7: 80 7D FC 01              cmp     byte ptr [ebp+var_4], 1
 * 000C7EEB: 74 0B                    jz      short loc_C7EF8
 * 000C7EED: 80 3E 2B                 cmp     byte ptr [esi], 2Bh ; '+'
 * 000C7EF0: 75 22                    jnz     short loc_C7F14
 * 000C7EF2: 80 7E FF 2A              cmp     byte ptr [esi-1], 2Ah ; '*'
 * 000C7EF6: 74 1C                    jz      short loc_C7F14
 * 000C7EF8: 8A 45 08                 mov     al, [ebp+arg_0]
 * 000C7EFB: 89 04 24                 mov     [esp+6Ch+var_6C], eax
 * 000C7EFE: 89 7C 24 04              mov     [esp+6Ch+var_68], edi
 * 000C7F02: 89 74 24 08              mov     [esp+6Ch+var_64], esi
 * 000C7F06: 89 4C 24 0C              mov     [esp+6Ch+var_60], ecx
 * 000C7F0A: E8 65 06 00 00           call    fn_C8574
 * 000C7F0F: EB 1B                    jmp     short loc_C7F2C
 * 000C7F11: 90 90 90                 align 4
 * 000C7F14: 8A 45 08                 mov     al, [ebp+arg_0]
 * 000C7F17: 89 04 24                 mov     [esp+6Ch+var_6C], eax
 * 000C7F1A: 89 7C 24 04              mov     [esp+6Ch+var_68], edi
 * 000C7F1E: 89 74 24 08              mov     [esp+6Ch+var_64], esi
 * 000C7F22: 89 4C 24 0C              mov     [esp+6Ch+var_60], ecx
 * 000C7F26: E8 71 05 00 00           call    fn_C849C
 * 000C7F2B: 46                       inc     esi
 * 000C7F2C: 66 23 C0                 and     ax, ax
 * 000C7F2F: 74 1B                    jz      short loc_C7F4C
 * 000C7F31: 8B 4D F4                 mov     ecx, [ebp+var_C]
 * 000C7F34: 88 4D B2                 mov     [ebp+var_4E], cl
 * 000C7F37: 8B 4D F8                 mov     ecx, [ebp+var_8]
 * 000C7F3A: 89 75 14                 mov     [ebp+arg_C], esi
 * 000C7F3D: 88 4D B3                 mov     [ebp+var_4D], cl
 * 000C7F40: 89 5D B4                 mov     [ebp+var_4C], ebx
 * 000C7F43: 66 89 45 EE              mov     [ebp+var_12], ax
 * 000C7F47: E9 FF 00 00 00           jmp     loc_C804B
 * 000C7F4C: E9 DB 00 00 00           jmp     loc_C802C
 * 000C7F51: 90 90 90                 align 4
 * 000C7F54: 89 34 24                 mov     [esp+6Ch+var_6C], esi
 * 000C7F57: E8 38 02 00 00           call    fn_C8194
 * 000C7F5C: 66 23 C0                 and     ax, ax
 * 000C7F5F: 74 1B                    jz      short loc_C7F7C
 * 000C7F61: 8B 4D F4                 mov     ecx, [ebp+var_C]
 * 000C7F64: 88 4D B2                 mov     [ebp+var_4E], cl
 * 000C7F67: 8B 4D F8                 mov     ecx, [ebp+var_8]
 * 000C7F6A: 89 75 14                 mov     [ebp+arg_C], esi
 * 000C7F6D: 88 4D B3                 mov     [ebp+var_4D], cl
 * 000C7F70: 89 5D B4                 mov     [ebp+var_4C], ebx
 * 000C7F73: 66 89 45 EE              mov     [ebp+var_12], ax
 * 000C7F77: E9 CF 00 00 00           jmp     loc_C804B
 * 000C7F7C: 46                       inc     esi
 * 000C7F7D: E9 AA 00 00 00           jmp     loc_C802C
 * 000C7F82: 90 90                    align 4
 * 000C7F84: 80 7D FC 01              cmp     byte ptr [ebp+var_4], 1
 * 000C7F88: 74 0B                    jz      short loc_C7F95
 * 000C7F8A: 80 3E 2B                 cmp     byte ptr [esi], 2Bh ; '+'
 * 000C7F8D: 75 15                    jnz     short loc_C7FA4
 * 000C7F8F: 80 7E FF 2A              cmp     byte ptr [esi-1], 2Ah ; '*'
 * 000C7F93: 74 0F                    jz      short loc_C7FA4
 * 000C7F95: 89 34 24                 mov     [esp+6Ch+var_6C], esi
 * 000C7F98: E8 CF 01 00 00           call    fn_C816C
 * 000C7F9D: 46                       inc     esi
 * 000C7F9E: EB 0F                    jmp     short loc_C7FAF
 * 000C7FA0: 90 90 90 90              db 4 dup(90h)
 * 000C7FA4: 89 34 24                 mov     [esp+6Ch+var_6C], esi
 * 000C7FA7: E8 90 01 00 00           call    fn_C813C
 * 000C7FAC: 83 C6 02                 add     esi, 2
 * 000C7FAF: 66 23 C0                 and     ax, ax
 * 000C7FB2: 74 20                    jz      short loc_C7FD4
 * 000C7FB4: 8B 4D F4                 mov     ecx, [ebp+var_C]
 * 000C7FB7: 88 4D B2                 mov     [ebp+var_4E], cl
 * 000C7FBA: 8B 4D F8                 mov     ecx, [ebp+var_8]
 * 000C7FBD: 89 75 14                 mov     [ebp+arg_C], esi
 * 000C7FC0: 88 4D B3                 mov     [ebp+var_4D], cl
 * 000C7FC3: 89 5D B4                 mov     [ebp+var_4C], ebx
 * 000C7FC6: 66 89 45 EE              mov     [ebp+var_12], ax
 * 000C7FCA: E9 7C 00 00 00           jmp     loc_C804B
 * 000C7FCF: 90 90 90 90 90           db 5 dup(90h)
 * 000C7FD4: EB 56                    jmp     short loc_C802C
 * 000C7FD6: 90 90 90 90 90 90        db 6 dup(90h)
 * 000C7FDC: 8B 45 F4                 mov     eax, [ebp+var_C]; jumptable 000C8001 default case
 * 000C7FDF: 88 45 B2                 mov     [ebp+var_4E], al
 * 000C7FE2: 8B 45 F8                 mov     eax, [ebp+var_8]
 * 000C7FE5: 88 45 B3                 mov     [ebp+var_4D], al
 * 000C7FE8: 89 75 14                 mov     [ebp+arg_C], esi
 * 000C7FEB: 89 5D B4                 mov     [ebp+var_4C], ebx
 * 000C7FEE: 66 B8 2D 33              mov     ax, 332Dh
 * 000C7FF2: 66 89 4D EE              mov     [ebp+var_12], cx
 * 000C7FF6: EB 53                    jmp     short loc_C804B
 * 000C7FF8: 90 90 90 90              db 4 dup(90h)
 * 000C7FFC: 25 FF 00 00 00           and     eax, 0FFh
 * 000C8001: 2E FF 24 85 0C 80 EC FF  jmp     dword ptr cs:[eax*4-137FF4h]; switch jump
 * 000C8009: 90 90 90                 align 4
 * 000C800C: 24 7D                    and     al, 7Dh
 * 000C800E: EC                       in      al, dx
 * 000C800F: FF 84 7D EC FF E4 7D     inc     [ebp+edi*2+arg_7DE4FFE4]
 * 000C8016: EC                       in      al, dx
 * 000C8017: FF 2C 7E                 jmp     fword ptr [esi+edi*2]
 * 000C801A: EC FF                    dw 0FFECh
 * 000C801C: 74 7E                    jz      short loc_C809C
 * 000C801E: EC                       in      al, dx
 * 000C801F: FF E4 7E                 jmp     esp
 * 000C8022: EC FF 54                 dw 0FFECh
 * 000C8025: 7F EC FF 84 7F           db 7Fh, 0ECh, 0FFh
 * 000C802A: EC FF                    dw 0FFECh
 * 000C802C: 8B 4D F8                 mov     ecx, [ebp+var_8]
 * 000C802F: 22 C9                    and     cl, cl
 * 000C8031: 8D 49 FF                 lea     ecx, [ecx-1]
 * 000C8034: 0F 85 B2 FC FF FF        jnz     loc_C7CEC
 * 000C803A: 89 75 14                 mov     [ebp+arg_C], esi
 * 000C803D: C6 45 B2 00              mov     [ebp+var_4E], 0
 * 000C8041: 88 4D B3                 mov     [ebp+var_4D], cl
 * 000C8044: 89 5D B4                 mov     [ebp+var_4C], ebx
 * 000C8047: 66 89 45 EE              mov     [ebp+var_12], ax
 * 000C804B: 8B 5D A4                 mov     ebx, [ebp+var_5C]
 * 000C804E: 8B 75 A8                 mov     esi, [ebp+var_58]
 * 000C8051: 8B 7D AC                 mov     edi, [ebp+var_54]
 * 000C8054: 89 EC                    mov     esp, ebp
 * 000C8056: 5D                       pop     ebp
 * 000C8057: C3                       retn
 * ========================================================================== */
/* Hex-Rays unavailable for 0xC7C14 (fn_C7C14); see assembly above. */
void fn_C7C14(void) { /* jump-table handler */ }


/* ============================================================================
 * fn_C805C  @ 0xC805C   size=0xDD   callers=1
 * note: [SRX-611] pop_rank=607/1298, sites=1, callers=1, callees=0, size=0xDD, leaf
 * --- original assembly (address: bytes  mnemonic) ---------------------------
 * 000C805C: 55                       push    ebp
 * 000C805D: 89 E5                    mov     ebp, esp
 * 000C805F: 83 EC 10                 sub     esp, 10h
 * 000C8062: 8B 45 08                 mov     eax, [ebp+arg_0]
 * 000C8065: C6 45 F7 00              mov     [ebp+var_9], 0
 * 000C8069: 57                       push    edi
 * 000C806A: 56                       push    esi
 * 000C806B: 53                       push    ebx
 * 000C806C: 66 C7 45 FE 00 00        mov     [ebp+var_2], 0
 * 000C8072: 2B FF                    sub     edi, edi
 * 000C8074: 89 45 F8                 mov     [ebp+var_8], eax
 * 000C8077: 8B 4D 0C                 mov     ecx, [ebp+arg_4]
 * 000C807A: 8A 55 F7                 mov     dl, [ebp+var_9]
 * 000C807D: 89 C6                    mov     esi, eax
 * 000C807F: 80 38 CF                 cmp     byte ptr [eax], 0CFh
 * 000C8082: 0F 84 9C 00 00 00        jz      loc_C8124
 * 000C8088: 88 11                    mov     [ecx], dl
 * 000C808A: 8A 18                    mov     bl, [eax]
 * 000C808C: 80 C3 40                 add     bl, 40h ; '@'; switch with an invalid jump table
 * 000C808F: 80 FB 07                 cmp     bl, 7
 * 000C8092: 77 48                    ja      short def_C80F0; jumptable 000C80F0 default case
 * 000C8094: E9 53 00 00 00           jmp     loc_C80EC
 * 000C8099: 90 90 90                 align 4
 * 000C809C: 80 C2 04                 add     dl, 4
 * 000C809F: E9 74 00 00 00           jmp     loc_C8118
 * 000C80A4: 80 C2 04                 add     dl, 4
 * 000C80A7: E9 6C 00 00 00           jmp     loc_C8118
 * 000C80AC: 80 C2 04                 add     dl, 4
 * 000C80AF: E9 64 00 00 00           jmp     loc_C8118
 * 000C80B4: 80 C2 04                 add     dl, 4
 * 000C80B7: EB 5F                    jmp     short loc_C8118
 * 000C80B9: 90 90 90                 align 4
 * 000C80BC: 80 C2 04                 add     dl, 4
 * 000C80BF: EB 57                    jmp     short loc_C8118
 * 000C80C1: 90 90 90                 align 4
 * 000C80C4: 80 C2 04                 add     dl, 4
 * 000C80C7: EB 4F                    jmp     short loc_C8118
 * 000C80C9: 90 90 90                 align 4
 * 000C80CC: 42                       inc     edx
 * 000C80CD: EB 49                    jmp     short loc_C8118
 * 000C80CF: 90 90 90 90 90           db 5 dup(90h)
 * 000C80D4: 42                       inc     edx
 * 000C80D5: EB 41                    jmp     short loc_C8118
 * 000C80D7: 90 90 90 90 90           db 5 dup(90h)
 * 000C80DC: 89 4D 0C                 mov     [ebp+arg_4], ecx; jumptable 000C80F0 default case
 * 000C80DF: 88 55 F7                 mov     [ebp+var_9], dl
 * 000C80E2: 89 45 F8                 mov     [ebp+var_8], eax
 * 000C80E5: 66 B8 2D 33              mov     ax, 332Dh
 * 000C80E9: EB 47                    jmp     short loc_C8132
 * 000C80EB: 90                       align 4
 * 000C80EC: 33 C0                    xor     eax, eax
 * 000C80EE: 88 D8                    mov     al, bl
 * 000C80F0: 2E FF 24 85 F8 80 EC FF 9C jmp     dword ptr cs:[eax*4-137F08h]; switch jump
 * 000C80F9: 80 EC FF                 db 80h, 0ECh, 0FFh
 * 000C80FC: A4 80 EC FF AC 80 EC FF B4 80 EC FF BC 80 EC FF C4 80 EC FF CC 80 EC FF D4 80 EC FF dd 0FFEC80A4h, 0FFEC80ACh, 0FFEC80B4h, 0FFEC80BCh, 0FFEC80C4h
 * 000C8118: 41                       inc     ecx
 * 000C8119: 33 C0                    xor     eax, eax
 * 000C811B: 88 D0                    mov     al, dl
 * 000C811D: 03 C6                    add     eax, esi
 * 000C811F: E9 5B FF FF FF           jmp     loc_C807F
 * 000C8124: 89 45 F8                 mov     [ebp+var_8], eax
 * 000C8127: 89 4D 0C                 mov     [ebp+arg_4], ecx
 * 000C812A: 88 55 F7                 mov     [ebp+var_9], dl
 * 000C812D: 89 F8                    mov     eax, edi
 * 000C812F: C6 01 FF                 mov     byte ptr [ecx], 0FFh
 * 000C8132: 5B                       pop     ebx
 * 000C8133: 5E                       pop     esi
 * 000C8134: 5F                       pop     edi
 * 000C8135: 89 EC                    mov     esp, ebp
 * 000C8137: 5D                       pop     ebp
 * 000C8138: C3                       retn
 * ========================================================================== */
/* Hex-Rays unavailable for 0xC805C (fn_C805C); see assembly above. */
void fn_C805C(void) { /* jump-table handler */ }


/* ============================================================================
 * fn_C813C  @ 0xC813C   size=0x2E   callers=1
 * note: [SRX-611] pop_rank=732/1298, sites=1, callers=1, callees=1, size=0x2E
 * --- original assembly (address: bytes  mnemonic) ---------------------------
 * 000C813C: 55                       push    ebp
 * 000C813D: 89 E5                    mov     ebp, esp
 * 000C813F: 56                       push    esi
 * 000C8140: 83 EC 08                 sub     esp, 8
 * 000C8143: 8B 75 08                 mov     esi, [ebp+arg_0]
 * 000C8146: 89 34 24                 mov     [esp+0Ch+var_C], esi
 * 000C8149: C7 44 24 04 03 00 00 00  mov     [esp+0Ch+var_8], 3
 * 000C8151: E8 26 06 00 00           call    util_C877C
 * 000C8156: C6 06 28                 mov     byte ptr [esi], 28h ; '('
 * 000C8159: C6 46 01 2B              mov     byte ptr [esi+1], 2Bh ; '+'
 * 000C815D: C6 46 02 29              mov     byte ptr [esi+2], 29h ; ')'
 * 000C8161: 2B C0                    sub     eax, eax
 * 000C8163: 8B 75 FC                 mov     esi, [ebp+var_4]
 * 000C8166: 89 EC                    mov     esp, ebp
 * 000C8168: 5D                       pop     ebp
 * 000C8169: C3                       retn
 * ========================================================================== */
// [SRX-611] pop_rank=732/1298, sites=1, callers=1, callees=1, size=0x2E
int __cdecl fn_C813C(char *a1)
{
  util_C877C(a1, 3u);
  *a1 = 40;
  a1[1] = 43;
  a1[2] = 41;
  return 0;
}


/* ============================================================================
 * fn_C816C  @ 0xC816C   size=0x26   callers=1
 * note: [SRX-611] pop_rank=739/1298, sites=1, callers=1, callees=1, size=0x26
 * --- original assembly (address: bytes  mnemonic) ---------------------------
 * 000C816C: 55                       push    ebp
 * 000C816D: 89 E5                    mov     ebp, esp
 * 000C816F: 56                       push    esi
 * 000C8170: 83 EC 08                 sub     esp, 8
 * 000C8173: 8B 75 08                 mov     esi, [ebp+arg_0]
 * 000C8176: 89 34 24                 mov     [esp+0Ch+var_C], esi
 * 000C8179: C7 44 24 04 01 00 00 00  mov     [esp+0Ch+var_8], 1
 * 000C8181: E8 F6 05 00 00           call    util_C877C
 * 000C8186: C6 06 2B                 mov     byte ptr [esi], 2Bh ; '+'
 * 000C8189: 2B C0                    sub     eax, eax
 * 000C818B: 8B 75 FC                 mov     esi, [ebp+var_4]
 * 000C818E: 89 EC                    mov     esp, ebp
 * 000C8190: 5D                       pop     ebp
 * 000C8191: C3                       retn
 * ========================================================================== */
// [SRX-611] pop_rank=739/1298, sites=1, callers=1, callees=1, size=0x26
int __cdecl fn_C816C(char *a1)
{
  util_C877C(a1, 1u);
  *a1 = 43;
  return 0;
}


/* ============================================================================
 * fn_C8194  @ 0xC8194   size=0x26   callers=1
 * note: [SRX-611] pop_rank=740/1298, sites=1, callers=1, callees=1, size=0x26
 * --- original assembly (address: bytes  mnemonic) ---------------------------
 * 000C8194: 55                       push    ebp
 * 000C8195: 89 E5                    mov     ebp, esp
 * 000C8197: 56                       push    esi
 * 000C8198: 83 EC 08                 sub     esp, 8
 * 000C819B: 8B 75 08                 mov     esi, [ebp+arg_0]
 * 000C819E: 89 34 24                 mov     [esp+0Ch+var_C], esi
 * 000C81A1: C7 44 24 04 01 00 00 00  mov     [esp+0Ch+var_8], 1
 * 000C81A9: E8 CE 05 00 00           call    util_C877C
 * 000C81AE: C6 06 2A                 mov     byte ptr [esi], 2Ah ; '*'
 * 000C81B1: 2B C0                    sub     eax, eax
 * 000C81B3: 8B 75 FC                 mov     esi, [ebp+var_4]
 * 000C81B6: 89 EC                    mov     esp, ebp
 * 000C81B8: 5D                       pop     ebp
 * 000C81B9: C3                       retn
 * ========================================================================== */
// [SRX-611] pop_rank=740/1298, sites=1, callers=1, callees=1, size=0x26
int __cdecl fn_C8194(char *a1)
{
  util_C877C(a1, 1u);
  *a1 = 42;
  return 0;
}


/* ============================================================================
 * fn_C81BC  @ 0xC81BC   size=0xAC   callers=1
 * note: [SRX-611] pop_rank=647/1298, sites=1, callers=1, callees=3, size=0xAC
 * --- original assembly (address: bytes  mnemonic) ---------------------------
 * 000C81BC: 55                       push    ebp
 * 000C81BD: 89 E5                    mov     ebp, esp
 * 000C81BF: 83 EC 18                 sub     esp, 18h
 * 000C81C2: 8B 45 0C                 mov     eax, [ebp+arg_4]
 * 000C81C5: 66 C7 45 FE 00 00        mov     [ebp+var_2], 0
 * 000C81CB: 57                       push    edi
 * 000C81CC: 56                       push    esi
 * 000C81CD: 53                       push    ebx
 * 000C81CE: 83 EC 10                 sub     esp, 10h
 * 000C81D1: 89 04 24                 mov     [esp+34h+var_34], eax
 * 000C81D4: 8B 45 14                 mov     eax, [ebp+arg_C]
 * 000C81D7: 89 44 24 04              mov     [esp+34h+var_30], eax
 * 000C81DB: 8D 75 F0                 lea     esi, [ebp+var_10]
 * 000C81DE: 89 74 24 08              mov     [esp+34h+var_2C], esi
 * 000C81E2: 8D 45 EF                 lea     eax, [ebp+var_11]
 * 000C81E5: 89 44 24 0C              mov     [esp+34h+var_28], eax
 * 000C81E9: E8 D6 DA FF FF           call    token_dispatch
 * 000C81EE: 89 C7                    mov     edi, eax
 * 000C81F0: 66 89 7D FE              mov     [ebp+var_2], di
 * 000C81F4: 66 23 FF                 and     di, di
 * 000C81F7: 74 0B                    jz      short loc_C8204
 * 000C81F9: 89 F8                    mov     eax, edi
 * 000C81FB: EB 5E                    jmp     short loc_C825B
 * 000C81FD: 90 90 90 90 90 90 90     db 7 dup(90h)
 * 000C8204: 8B 5D 10                 mov     ebx, [ebp+arg_8]
 * 000C8207: 8A 45 EF                 mov     al, [ebp+var_11]
 * 000C820A: 80 7D 08 01              cmp     [ebp+arg_0], 1
 * 000C820E: 75 2C                    jnz     short loc_C823C
 * 000C8210: 89 1C 24                 mov     [esp+34h+var_34], ebx
 * 000C8213: 04 02                    add     al, 2
 * 000C8215: 89 44 24 04              mov     [esp+34h+var_30], eax
 * 000C8219: E8 5E 05 00 00           call    util_C877C
 * 000C821E: C6 03 2A                 mov     byte ptr [ebx], 2Ah ; '*'
 * 000C8221: C6 43 01 20              mov     byte ptr [ebx+1], 20h ; ' '
 * 000C8225: 83 C3 02                 add     ebx, 2
 * 000C8228: 89 74 24 04              mov     [esp+34h+var_30], esi
 * 000C822C: 89 1C 24                 mov     [esp+34h+var_34], ebx
 * 000C822F: E8 A0 05 00 00           call    util_C87D4
 * 000C8234: EB 23                    jmp     short loc_C8259
 * 000C8236: 90 90 90 90 90 90        db 6 dup(90h)
 * 000C823C: 89 1C 24                 mov     [esp+34h+var_34], ebx
 * 000C823F: 40                       inc     eax
 * 000C8240: 89 44 24 04              mov     [esp+34h+var_30], eax
 * 000C8244: E8 33 05 00 00           call    util_C877C
 * 000C8249: C6 03 2A                 mov     byte ptr [ebx], 2Ah ; '*'
 * 000C824C: 43                       inc     ebx
 * 000C824D: 89 1C 24                 mov     [esp+34h+var_34], ebx
 * 000C8250: 89 74 24 04              mov     [esp+34h+var_30], esi
 * 000C8254: E8 7B 05 00 00           call    util_C87D4
 * 000C8259: 89 F8                    mov     eax, edi
 * 000C825B: 8B 5D DC                 mov     ebx, [ebp+var_24]
 * 000C825E: 8B 75 E0                 mov     esi, [ebp+var_20]
 * 000C8261: 8B 7D E4                 mov     edi, [ebp+var_1C]
 * 000C8264: 89 EC                    mov     esp, ebp
 * 000C8266: 5D                       pop     ebp
 * 000C8267: C3                       retn
 * ========================================================================== */
// [SRX-611] pop_rank=647/1298, sites=1, callers=1, callees=3, size=0xAC
int __cdecl fn_C81BC(char a1, int a2, char *a3, int a4)
{
  int result; // eax
  int v5; // edi
  char v6; // [esp+23h] [ebp-11h] BYREF
  _BYTE v7[14]; // [esp+24h] [ebp-10h] BYREF
  __int16 v8; // [esp+32h] [ebp-2h]

  v8 = 0;
  result = token_dispatch(a2, a4, v7, &v6);
  v5 = result;
  v8 = result;
  if ( !(_WORD)result )
  {
    if ( a1 == 1 )
    {
      util_C877C(a3, v6 + 2);
      *a3 = 42;
      a3[1] = 32;
      util_C87D4(a3 + 2, v7);
    }
    else
    {
      util_C877C(a3, v6 + 1);
      *a3 = 42;
      util_C87D4(a3 + 1, v7);
    }
    return v5;
  }
  return result;
}


