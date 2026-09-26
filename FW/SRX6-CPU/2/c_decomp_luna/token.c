/*
 * Sony SRX-611 firmware - LUNA object-code interpreter/decoder - prefix 'token'
 * Source: ROM1-C.bin (80486 real mode, OS+/386 V2.0)
 * Functions: 1. The LUNA language compiles robot programs to object code;
 * this cluster decodes opcodes/tokens and formats operands.
 */

/* ============================================================================
 * token_dispatch  @ 0xC5CC4   size=0x2A6   callers=42
 * note: Token/type dispatch using a jump table (switch on input byte) | [SRX-611] pop_rank=13/1298, sites=42, callers=26, callees=11, size=0x2A6
 * --- original assembly (address: bytes  mnemonic) ---------------------------
 * 000C5CC4: 55                       push    ebp
 * 000C5CC5: 89 E5                    mov     ebp, esp
 * 000C5CC7: 83 EC 14                 sub     esp, 14h
 * 000C5CCA: 8B 45 08                 mov     eax, [ebp+arg_0]
 * 000C5CCD: 66 C7 45 FA 00 00        mov     [ebp+var_6], 0
 * 000C5CD3: 57                       push    edi
 * 000C5CD4: 56                       push    esi
 * 000C5CD5: 8B 10                    mov     edx, [eax]
 * 000C5CD7: 53                       push    ebx
 * 000C5CD8: 83 EC 0C                 sub     esp, 0Ch
 * 000C5CDB: 89 55 F4                 mov     [ebp+var_C], edx
 * 000C5CDE: 66 8B 58 04              mov     bx, [eax+4]
 * 000C5CE2: 8B 7D 0C                 mov     edi, [ebp+arg_4]
 * 000C5CE5: 2B C9                    sub     ecx, ecx
 * 000C5CE7: 66 89 5D F2              mov     [ebp+var_E], bx
 * 000C5CEB: 2B F6                    sub     esi, esi
 * 000C5CED: 8A 07                    mov     al, [edi]
 * 000C5CEF: 3C 80                    cmp     al, 80h
 * 000C5CF1: 0F 83 F5 01 00 00        jnb     loc_C5EEC
 * 000C5CF7: 3C 21                    cmp     al, 21h; switch with an invalid jump table
 * 000C5CF9: 0F 87 45 01 00 00        ja      def_C5E59; jumptable 000C5E59 default case
 * 000C5CFF: E9 50 01 00 00           jmp     loc_C5E54
 * 000C5D04: 89 3C 24                 mov     [esp+2Ch+var_2C], edi
 * 000C5D07: 8B 45 10                 mov     eax, [ebp+arg_8]
 * 000C5D0A: 89 44 24 04              mov     [esp+2Ch+var_28], eax
 * 000C5D0E: 8B 45 14                 mov     eax, [ebp+arg_C]
 * 000C5D11: 89 44 24 08              mov     [esp+2Ch+var_24], eax
 * 000C5D15: E8 52 02 00 00           call    util_C5F6C
 * 000C5D1A: 2B C0                    sub     eax, eax
 * 000C5D1C: E9 3C 02 00 00           jmp     loc_C5F5D
 * 000C5D21: 90 90 90                 align 4
 * 000C5D24: 89 3C 24                 mov     [esp+2Ch+var_2C], edi
 * 000C5D27: 8B 45 10                 mov     eax, [ebp+arg_8]
 * 000C5D2A: 89 44 24 04              mov     [esp+2Ch+var_28], eax
 * 000C5D2E: 8B 45 14                 mov     eax, [ebp+arg_C]
 * 000C5D31: 89 44 24 08              mov     [esp+2Ch+var_24], eax
 * 000C5D35: E8 DA 02 00 00           call    util_C6014
 * 000C5D3A: 2B C0                    sub     eax, eax
 * 000C5D3C: E9 1C 02 00 00           jmp     loc_C5F5D
 * 000C5D41: 90 90 90                 align 4
 * 000C5D44: 89 3C 24                 mov     [esp+2Ch+var_2C], edi
 * 000C5D47: 8B 45 10                 mov     eax, [ebp+arg_8]
 * 000C5D4A: 89 44 24 04              mov     [esp+2Ch+var_28], eax
 * 000C5D4E: 8B 45 14                 mov     eax, [ebp+arg_C]
 * 000C5D51: 89 44 24 08              mov     [esp+2Ch+var_24], eax
 * 000C5D55: E8 62 03 00 00           call    util_C60BC
 * 000C5D5A: 2B C0                    sub     eax, eax
 * 000C5D5C: E9 FC 01 00 00           jmp     loc_C5F5D
 * 000C5D61: 90 90 90                 align 4
 * 000C5D64: 89 3C 24                 mov     [esp+2Ch+var_2C], edi
 * 000C5D67: 8B 45 10                 mov     eax, [ebp+arg_8]
 * 000C5D6A: 89 44 24 04              mov     [esp+2Ch+var_28], eax
 * 000C5D6E: 8B 45 14                 mov     eax, [ebp+arg_C]
 * 000C5D71: 89 44 24 08              mov     [esp+2Ch+var_24], eax
 * 000C5D75: E8 82 03 00 00           call    util_C60FC
 * 000C5D7A: 2B C0                    sub     eax, eax
 * 000C5D7C: E9 DC 01 00 00           jmp     loc_C5F5D
 * 000C5D81: 90 90 90                 align 4
 * 000C5D84: 89 3C 24                 mov     [esp+2Ch+var_2C], edi
 * 000C5D87: 8B 45 10                 mov     eax, [ebp+arg_8]
 * 000C5D8A: 89 44 24 04              mov     [esp+2Ch+var_28], eax
 * 000C5D8E: 8B 45 14                 mov     eax, [ebp+arg_C]
 * 000C5D91: 89 44 24 08              mov     [esp+2Ch+var_24], eax
 * 000C5D95: E8 A2 03 00 00           call    util_C613C
 * 000C5D9A: 2B C0                    sub     eax, eax
 * 000C5D9C: E9 BC 01 00 00           jmp     loc_C5F5D
 * 000C5DA1: 90 90 90                 align 4
 * 000C5DA4: 89 3C 24                 mov     [esp+2Ch+var_2C], edi
 * 000C5DA7: 8B 45 10                 mov     eax, [ebp+arg_8]
 * 000C5DAA: 89 44 24 04              mov     [esp+2Ch+var_28], eax
 * 000C5DAE: 8B 45 14                 mov     eax, [ebp+arg_C]
 * 000C5DB1: 89 44 24 08              mov     [esp+2Ch+var_24], eax
 * 000C5DB5: E8 DA 03 00 00           call    util_C6194
 * 000C5DBA: 2B C0                    sub     eax, eax
 * 000C5DBC: E9 9C 01 00 00           jmp     loc_C5F5D
 * 000C5DC1: 90 90 90                 align 4
 * 000C5DC4: 89 3C 24                 mov     [esp+2Ch+var_2C], edi
 * 000C5DC7: 8B 45 10                 mov     eax, [ebp+arg_8]
 * 000C5DCA: 89 44 24 04              mov     [esp+2Ch+var_28], eax
 * 000C5DCE: 8B 45 14                 mov     eax, [ebp+arg_C]
 * 000C5DD1: 89 44 24 08              mov     [esp+2Ch+var_24], eax
 * 000C5DD5: E8 12 04 00 00           call    util_C61EC
 * 000C5DDA: 2B C0                    sub     eax, eax
 * 000C5DDC: E9 7C 01 00 00           jmp     loc_C5F5D
 * 000C5DE1: 90 90 90                 align 4
 * 000C5DE4: 89 3C 24                 mov     [esp+2Ch+var_2C], edi
 * 000C5DE7: 8B 45 10                 mov     eax, [ebp+arg_8]
 * 000C5DEA: 89 44 24 04              mov     [esp+2Ch+var_28], eax
 * 000C5DEE: 8B 45 14                 mov     eax, [ebp+arg_C]
 * 000C5DF1: 89 44 24 08              mov     [esp+2Ch+var_24], eax
 * 000C5DF5: E8 4A 04 00 00           call    util_C6244
 * 000C5DFA: 2B C0                    sub     eax, eax
 * 000C5DFC: E9 5C 01 00 00           jmp     loc_C5F5D
 * 000C5E01: 90 90 90                 align 4
 * 000C5E04: 89 3C 24                 mov     [esp+2Ch+var_2C], edi
 * 000C5E07: 8B 45 10                 mov     eax, [ebp+arg_8]
 * 000C5E0A: 89 44 24 04              mov     [esp+2Ch+var_28], eax
 * 000C5E0E: 8B 45 14                 mov     eax, [ebp+arg_C]
 * 000C5E11: 89 44 24 08              mov     [esp+2Ch+var_24], eax
 * 000C5E15: E8 92 04 00 00           call    util_C62AC
 * 000C5E1A: 2B C0                    sub     eax, eax
 * 000C5E1C: E9 3C 01 00 00           jmp     loc_C5F5D
 * 000C5E21: 90 90 90                 align 4
 * 000C5E24: 89 3C 24                 mov     [esp+2Ch+var_2C], edi
 * 000C5E27: 8B 45 10                 mov     eax, [ebp+arg_8]
 * 000C5E2A: 89 44 24 04              mov     [esp+2Ch+var_28], eax
 * 000C5E2E: 8B 45 14                 mov     eax, [ebp+arg_C]
 * 000C5E31: 89 44 24 08              mov     [esp+2Ch+var_24], eax
 * 000C5E35: E8 E2 04 00 00           call    util_C631C
 * 000C5E3A: 2B C0                    sub     eax, eax
 * 000C5E3C: E9 1C 01 00 00           jmp     loc_C5F5D
 * 000C5E41: 90 90 90                 align 4
 * 000C5E44: 66 B8 2D 33              mov     ax, 332Dh; jumptable 000C5E59 default case
 * 000C5E48: E9 10 01 00 00           jmp     loc_C5F5D
 * 000C5E4D: 90 90 90 90 90 90 90     db 7 dup(90h)
 * 000C5E54: 25 FF 00 00 00           and     eax, 0FFh
 * 000C5E59: 2E FF 24 85 64 5E EC FF  jmp     dword ptr cs:[eax*4-13A19Ch]; switch jump
 * 000C5E61: 90 90 90                 align 4
 * 000C5E64: 24 5D                    and     al, 5Dh
 * 000C5E66: EC                       in      al, dx
 * 000C5E67: FF 04 5D EC FF A4 5D     inc     dword ptr ds:5DA4FFECh[ebx*2]
 * 000C5E6E: EC                       in      al, dx
 * 000C5E6F: FF 44 5D EC              inc     [ebp+ebx*2+var_14]
 * 000C5E73: FF 64 5D EC              jmp     [ebp+ebx*2+var_14]
 * 000C5E77: FF 84 5D EC FF 44 5E     inc     [ebp+ebx*2+arg_5E44FFE4]
 * 000C5E7E: EC                       in      al, dx
 * 000C5E7F: FF 44 5E EC              inc     dword ptr [esi+ebx*2-14h]
 * 000C5E83: FF 44 5E EC              inc     dword ptr [esi+ebx*2-14h]
 * 000C5E87: FF 44 5E EC              inc     dword ptr [esi+ebx*2-14h]
 * 000C5E8B: FF 44 5E EC              inc     dword ptr [esi+ebx*2-14h]
 * 000C5E8F: FF 44 5E EC              inc     dword ptr [esi+ebx*2-14h]
 * 000C5E93: FF 44 5E EC              inc     dword ptr [esi+ebx*2-14h]
 * 000C5E97: FF 44 5E EC              inc     dword ptr [esi+ebx*2-14h]
 * 000C5E9B: FF 44 5E EC              inc     dword ptr [esi+ebx*2-14h]
 * 000C5E9F: FF 44 5E EC              inc     dword ptr [esi+ebx*2-14h]
 * 000C5EA3: FF 24 5E                 jmp     dword ptr [esi+ebx*2]
 * 000C5EA6: EC FF                    dw 0FFECh
 * 000C5EA8: 04 5E                    add     al, 5Eh ; '^'
 * 000C5EAA: EC                       in      al, dx
 * 000C5EAB: FF 44 5E EC              inc     dword ptr [esi+ebx*2-14h]
 * 000C5EAF: FF 44 5E EC              inc     dword ptr [esi+ebx*2-14h]
 * 000C5EB3: FF 44 5E EC              inc     dword ptr [esi+ebx*2-14h]
 * 000C5EB7: FF 44 5E EC              inc     dword ptr [esi+ebx*2-14h]
 * 000C5EBB: FF 44 5E EC              inc     dword ptr [esi+ebx*2-14h]
 * 000C5EBF: FF 44 5E EC              inc     dword ptr [esi+ebx*2-14h]
 * 000C5EC3: FF 44 5E EC              inc     dword ptr [esi+ebx*2-14h]
 * 000C5EC7: FF 44 5E EC              inc     dword ptr [esi+ebx*2-14h]
 * 000C5ECB: FF 44 5E EC              inc     dword ptr [esi+ebx*2-14h]
 * 000C5ECF: FF 44 5E EC              inc     dword ptr [esi+ebx*2-14h]
 * 000C5ED3: FF 44 5E EC              inc     dword ptr [esi+ebx*2-14h]
 * 000C5ED7: FF 44 5E EC              inc     dword ptr [esi+ebx*2-14h]
 * 000C5EDB: FF 44 5E EC              inc     dword ptr [esi+ebx*2-14h]
 * 000C5EDF: FF 44 5E EC              inc     dword ptr [esi+ebx*2-14h]
 * 000C5EE3: FF C4                    inc     esp
 * 000C5EE5: 5D                       pop     ebp
 * 000C5EE6: EC                       in      al, dx
 * 000C5EE7: FF E4 5D                 jmp     esp
 * 000C5EEA: EC FF                    dw 0FFECh
 * 000C5EEC: 66 23 DB                 and     bx, bx
 * 000C5EEF: 75 0B                    jnz     short loc_C5EFC
 * 000C5EF1: 66 B8 2E 33              mov     ax, 332Eh
 * 000C5EF5: EB 66                    jmp     short loc_C5F5D
 * 000C5EF7: 90 90 90 90 90           db 5 dup(90h)
 * 000C5EFC: 66 89 4D F8              mov     [ebp+var_8], cx
 * 000C5F00: 2B C9                    sub     ecx, ecx
 * 000C5F02: 89 5D FC                 mov     [ebp+var_4], ebx
 * 000C5F05: 66 3B 4D FC              cmp     cx, word ptr [ebp+var_4]
 * 000C5F09: 73 21                    jnb     short loc_C5F2C
 * 000C5F0B: 38 02                    cmp     [edx], al
 * 000C5F0D: 75 15                    jnz     short loc_C5F24
 * 000C5F0F: 66 8B 5F 01              mov     bx, [edi+1]
 * 000C5F13: 66 39 5A 01              cmp     [edx+1], bx
 * 000C5F17: 75 0B                    jnz     short loc_C5F24
 * 000C5F19: 89 55 F4                 mov     [ebp+var_C], edx
 * 000C5F1C: 66 89 4D F8              mov     [ebp+var_8], cx
 * 000C5F20: EB 11                    jmp     short loc_C5F33
 * 000C5F22: 90 90                    align 4
 * 000C5F24: 41                       inc     ecx
 * 000C5F25: 83 C2 10                 add     edx, 10h
 * 000C5F28: EB DB                    jmp     short loc_C5F05
 * 000C5F2A: 90 90                    align 4
 * 000C5F2C: 89 55 F4                 mov     [ebp+var_C], edx
 * 000C5F2F: 66 89 4D F8              mov     [ebp+var_8], cx
 * 000C5F33: 2B C0                    sub     eax, eax
 * 000C5F35: B9 FF FF FF FF           mov     ecx, 0FFFFFFFFh
 * 000C5F3A: 8D 7A 03                 lea     edi, [edx+3]
 * 000C5F3D: F2 AE                    repne scasb
 * 000C5F3F: F7 D9                    neg     ecx
 * 000C5F41: 83 E9 02                 sub     ecx, 2
 * 000C5F44: 8B 45 14                 mov     eax, [ebp+arg_C]
 * 000C5F47: 83 C2 03                 add     edx, 3
 * 000C5F4A: 88 08                    mov     [eax], cl
 * 000C5F4C: 8B 45 10                 mov     eax, [ebp+arg_8]
 * 000C5F4F: 89 04 24                 mov     [esp+2Ch+var_2C], eax
 * 000C5F52: 89 54 24 04              mov     [esp+2Ch+var_28], edx
 * 000C5F56: E8 01 86 00 00           call    strcpy
 * 000C5F5B: 89 F0                    mov     eax, esi
 * 000C5F5D: 8B 5D E0                 mov     ebx, [ebp+var_20]
 * 000C5F60: 8B 75 E4                 mov     esi, [ebp+var_1C]
 * 000C5F63: 8B 7D E8                 mov     edi, [ebp+var_18]
 * 000C5F66: 89 EC                    mov     esp, ebp
 * 000C5F68: 5D                       pop     ebp
 * 000C5F69: C3                       retn
 * ========================================================================== */
/*
 * Manually reconstructed (invalid switch jump table at 0xC5E59).
 * LUNA object-code token dispatcher:
 *   arg0 = descriptor { void *table; uint16_t count; }
 *   arg1 = token bytes, arg2 = output text buffer, arg3 = output length.
 * token[0] < 0x80  -> dispatch on token type to the per-type formatter
 *                     util_C5F6C .. util_C631C (each emits a mnemonic/operand).
 * token[0] >= 0x80 -> linear search of 16-byte entries {u8 code; u16 sel; char text[]}
 *                     and copy the matching entry's text (strcpy).
 * Returns 0x332D (bad token type) or 0x332E (empty table) on error.
 */
int token_dispatch(void *desc, const uint8_t *tok, char *out, uint8_t *outlen)
{
    uint8_t *tbl = *(uint8_t **)desc;
    uint16_t count = *(uint16_t *)((uint8_t *)desc + 4);
    uint8_t c = tok[0];

    if (c < 0x80u) {
        switch (c) {
        case 0:  util_C5F6C(tok, out, outlen); return 0;
        case 1:  util_C6014(tok, out, outlen); return 0;
        case 2:  util_C60BC(tok, out, outlen); return 0;
        case 3:  util_C60FC(tok, out, outlen); return 0;
        case 4:  util_C613C(tok, out, outlen); return 0;
        case 5:  util_C6194(tok, out, outlen); return 0;
        case 6:  util_C61EC(tok, out, outlen); return 0;
        case 7:  util_C6244(tok, out, outlen); return 0;
        case 8:  util_C62AC(tok, out, outlen); return 0;
        case 9:  util_C631C(tok, out, outlen); return 0;
        default: return 0x332D;
        }
    }
    if (count == 0)
        return 0x332E;
    for (uint16_t i = 0; i < count; i++, tbl += 16) {
        if (tbl[0] == c && *(uint16_t *)(tbl + 1) == *(const uint16_t *)(tok + 1)) {
            *outlen = (uint8_t)strlen((const char *)tbl + 3);
            strcpy(out, (const char *)tbl + 3);
            return 0;
        }
    }
    return 0;
}


