/*
 * Sony SRX-611 firmware - LUNA object-code interpreter/decoder - prefix 'point'
 * Source: ROM1-C.bin (80486 real mode, OS+/386 V2.0)
 * Functions: 1. The LUNA language compiles robot programs to object code;
 * this cluster decodes opcodes/tokens and formats operands.
 */

/* ============================================================================
 * point_var_dispatch  @ 0x6F7DC   size=0x116B   callers=1
 * note: Point/variable string lookup + jump-table dispatch | [SRX-611] pop_rank=767/1298, sites=0, callers=0, callees=1, size=0x116B
 * --- original assembly (address: bytes  mnemonic) ---------------------------
 * 0006F7DC: 55                       push    ebp
 * 0006F7DD: 89 E5                    mov     ebp, esp
 * 0006F7DF: 83 EC 08                 sub     esp, 8
 * 0006F7E2: 66 C7 45 FE 00 00        mov     [ebp+var_2], 0
 * 0006F7E8: 57                       push    edi
 * 0006F7E9: 56                       push    esi
 * 0006F7EA: 53                       push    ebx
 * 0006F7EB: 83 EC 08                 sub     esp, 8
 * 0006F7EE: 8B 5D 10                 mov     ebx, [ebp+arg_8]
 * 0006F7F1: 33 C0                    xor     eax, eax
 * 0006F7F3: 89 1C 24                 mov     [esp+1Ch+var_1C], ebx
 * 0006F7F6: 8B 7D 08                 mov     edi, [ebp+arg_0]
 * 0006F7F9: 8A 47 05                 mov     al, [edi+5]
 * 0006F7FC: 8B 04 C5 DC 26 00 00     mov     eax, ds:dword_26DC[eax*8]
 * 0006F803: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 0006F807: E8 50 ED 05 00           call    strcpy
 * 0006F80C: 8B 75 14                 mov     esi, [ebp+arg_C]
 * 0006F80F: 89 34 24                 mov     [esp+1Ch+var_1C], esi
 * 0006F812: 33 C0                    xor     eax, eax
 * 0006F814: 8A 47 05                 mov     al, [edi+5]
 * 0006F817: 8B 04 C5 E0 26 00 00     mov     eax, ds:dword_26E0[eax*8]
 * 0006F81E: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 0006F822: E8 35 ED 05 00           call    strcpy
 * 0006F827: 66 8B 45 0C              mov     ax, [ebp+arg_4]
 * 0006F82B: 66 05 FF 6F              add     ax, 6FFFh; switch with an invalid jump table
 * 0006F82F: 66 83 F8 48              cmp     ax, 48h
 * 0006F833: 0F 87 FF 10 00 00        ja      def_70809; jumptable 00070809 default case
 * 0006F839: E9 C6 0F 00 00           jmp     loc_70804
 * 0006F83E: 90 90 90 90 90 90        db 6 dup(90h)
 * 0006F844: 89 1C 24                 mov     [esp+1Ch+var_1C], ebx
 * 0006F847: 33 C0                    xor     eax, eax
 * 0006F849: 8A 47 05                 mov     al, [edi+5]
 * 0006F84C: 8B 04 C5 14 23 00 00     mov     eax, ds:dword_2314[eax*8]
 * 0006F853: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 0006F857: E8 00 ED 05 00           call    strcpy
 * 0006F85C: 89 34 24                 mov     [esp+1Ch+var_1C], esi
 * 0006F85F: 33 C0                    xor     eax, eax
 * 0006F861: 8A 47 05                 mov     al, [edi+5]
 * 0006F864: 8B 04 C5 18 23 00 00     mov     eax, ds:dword_2318[eax*8]
 * 0006F86B: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 0006F86F: E8 E8 EC 05 00           call    strcpy
 * 0006F874: E9 BF 10 00 00           jmp     def_70809; jumptable 00070809 default case
 * 0006F879: 90 90 90                 align 4
 * 0006F87C: 89 1C 24                 mov     [esp+1Ch+var_1C], ebx
 * 0006F87F: 33 C0                    xor     eax, eax
 * 0006F881: 8A 47 05                 mov     al, [edi+5]
 * 0006F884: 8B 04 C5 24 23 00 00     mov     eax, ds:dword_2324[eax*8]
 * 0006F88B: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 0006F88F: E8 C8 EC 05 00           call    strcpy
 * 0006F894: 89 34 24                 mov     [esp+1Ch+var_1C], esi
 * 0006F897: 33 C0                    xor     eax, eax
 * 0006F899: 8A 47 05                 mov     al, [edi+5]
 * 0006F89C: 8B 04 C5 28 23 00 00     mov     eax, ds:dword_2328[eax*8]
 * 0006F8A3: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 0006F8A7: E8 B0 EC 05 00           call    strcpy
 * 0006F8AC: E9 87 10 00 00           jmp     def_70809; jumptable 00070809 default case
 * 0006F8B1: 90 90 90                 align 4
 * 0006F8B4: 89 1C 24                 mov     [esp+1Ch+var_1C], ebx
 * 0006F8B7: 33 C0                    xor     eax, eax
 * 0006F8B9: 8A 47 05                 mov     al, [edi+5]
 * 0006F8BC: 8B 04 C5 34 23 00 00     mov     eax, ds:dword_2334[eax*8]
 * 0006F8C3: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 0006F8C7: E8 90 EC 05 00           call    strcpy
 * 0006F8CC: 89 34 24                 mov     [esp+1Ch+var_1C], esi
 * 0006F8CF: 33 C0                    xor     eax, eax
 * 0006F8D1: 8A 47 05                 mov     al, [edi+5]
 * 0006F8D4: 8B 04 C5 38 23 00 00     mov     eax, ds:dword_2338[eax*8]
 * 0006F8DB: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 0006F8DF: E8 78 EC 05 00           call    strcpy
 * 0006F8E4: E9 4F 10 00 00           jmp     def_70809; jumptable 00070809 default case
 * 0006F8E9: 90 90 90                 align 4
 * 0006F8EC: 89 1C 24                 mov     [esp+1Ch+var_1C], ebx
 * 0006F8EF: 33 C0                    xor     eax, eax
 * 0006F8F1: 8A 47 05                 mov     al, [edi+5]
 * 0006F8F4: 8B 04 C5 44 23 00 00     mov     eax, ds:dword_2344[eax*8]
 * 0006F8FB: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 0006F8FF: E8 58 EC 05 00           call    strcpy
 * 0006F904: 89 34 24                 mov     [esp+1Ch+var_1C], esi
 * 0006F907: 33 C0                    xor     eax, eax
 * 0006F909: 8A 47 05                 mov     al, [edi+5]
 * 0006F90C: 8B 04 C5 48 23 00 00     mov     eax, ds:dword_2348[eax*8]
 * 0006F913: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 0006F917: E8 40 EC 05 00           call    strcpy
 * 0006F91C: E9 17 10 00 00           jmp     def_70809; jumptable 00070809 default case
 * 0006F921: 90 90 90                 align 4
 * 0006F924: 89 1C 24                 mov     [esp+1Ch+var_1C], ebx
 * 0006F927: 33 C0                    xor     eax, eax
 * 0006F929: 8A 47 05                 mov     al, [edi+5]
 * 0006F92C: 8B 04 C5 54 23 00 00     mov     eax, ds:dword_2354[eax*8]
 * 0006F933: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 0006F937: E8 20 EC 05 00           call    strcpy
 * 0006F93C: 89 34 24                 mov     [esp+1Ch+var_1C], esi
 * 0006F93F: 33 C0                    xor     eax, eax
 * 0006F941: 8A 47 05                 mov     al, [edi+5]
 * 0006F944: 8B 04 C5 58 23 00 00     mov     eax, ds:dword_2358[eax*8]
 * 0006F94B: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 0006F94F: E8 08 EC 05 00           call    strcpy
 * 0006F954: E9 DF 0F 00 00           jmp     def_70809; jumptable 00070809 default case
 * 0006F959: 90 90 90                 align 4
 * 0006F95C: 89 1C 24                 mov     [esp+1Ch+var_1C], ebx
 * 0006F95F: 33 C0                    xor     eax, eax
 * 0006F961: 8A 47 05                 mov     al, [edi+5]
 * 0006F964: 8B 04 C5 64 23 00 00     mov     eax, ds:dword_2364[eax*8]
 * 0006F96B: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 0006F96F: E8 E8 EB 05 00           call    strcpy
 * 0006F974: 89 34 24                 mov     [esp+1Ch+var_1C], esi
 * 0006F977: 33 C0                    xor     eax, eax
 * 0006F979: 8A 47 05                 mov     al, [edi+5]
 * 0006F97C: 8B 04 C5 68 23 00 00     mov     eax, ds:dword_2368[eax*8]
 * 0006F983: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 0006F987: E8 D0 EB 05 00           call    strcpy
 * 0006F98C: E9 A7 0F 00 00           jmp     def_70809; jumptable 00070809 default case
 * 0006F991: 90 90 90                 align 4
 * 0006F994: 89 1C 24                 mov     [esp+1Ch+var_1C], ebx
 * 0006F997: 33 C0                    xor     eax, eax
 * 0006F999: 8A 47 05                 mov     al, [edi+5]
 * 0006F99C: 8B 04 C5 74 23 00 00     mov     eax, ds:dword_2374[eax*8]
 * 0006F9A3: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 0006F9A7: E8 B0 EB 05 00           call    strcpy
 * 0006F9AC: 89 34 24                 mov     [esp+1Ch+var_1C], esi
 * 0006F9AF: 33 C0                    xor     eax, eax
 * 0006F9B1: 8A 47 05                 mov     al, [edi+5]
 * 0006F9B4: 8B 04 C5 78 23 00 00     mov     eax, ds:dword_2378[eax*8]
 * 0006F9BB: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 0006F9BF: E8 98 EB 05 00           call    strcpy
 * 0006F9C4: E9 6F 0F 00 00           jmp     def_70809; jumptable 00070809 default case
 * 0006F9C9: 90 90 90                 align 4
 * 0006F9CC: 89 1C 24                 mov     [esp+1Ch+var_1C], ebx
 * 0006F9CF: 33 C0                    xor     eax, eax
 * 0006F9D1: 8A 47 05                 mov     al, [edi+5]
 * 0006F9D4: 8B 04 C5 94 23 00 00     mov     eax, ds:dword_2394[eax*8]
 * 0006F9DB: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 0006F9DF: E8 78 EB 05 00           call    strcpy
 * 0006F9E4: 89 34 24                 mov     [esp+1Ch+var_1C], esi
 * 0006F9E7: 33 C0                    xor     eax, eax
 * 0006F9E9: 8A 47 05                 mov     al, [edi+5]
 * 0006F9EC: 8B 04 C5 98 23 00 00     mov     eax, ds:dword_2398[eax*8]
 * 0006F9F3: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 0006F9F7: E8 60 EB 05 00           call    strcpy
 * 0006F9FC: E9 37 0F 00 00           jmp     def_70809; jumptable 00070809 default case
 * 0006FA01: 90 90 90                 align 4
 * 0006FA04: 89 1C 24                 mov     [esp+1Ch+var_1C], ebx
 * 0006FA07: 33 C0                    xor     eax, eax
 * 0006FA09: 8A 47 05                 mov     al, [edi+5]
 * 0006FA0C: 8B 04 C5 A4 23 00 00     mov     eax, ds:dword_23A4[eax*8]
 * 0006FA13: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 0006FA17: E8 40 EB 05 00           call    strcpy
 * 0006FA1C: 89 34 24                 mov     [esp+1Ch+var_1C], esi
 * 0006FA1F: 33 C0                    xor     eax, eax
 * 0006FA21: 8A 47 05                 mov     al, [edi+5]
 * 0006FA24: 8B 04 C5 A8 23 00 00     mov     eax, ds:dword_23A8[eax*8]
 * 0006FA2B: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 0006FA2F: E8 28 EB 05 00           call    strcpy
 * 0006FA34: E9 FF 0E 00 00           jmp     def_70809; jumptable 00070809 default case
 * 0006FA39: 90 90 90                 align 4
 * 0006FA3C: 89 1C 24                 mov     [esp+1Ch+var_1C], ebx
 * 0006FA3F: 33 C0                    xor     eax, eax
 * 0006FA41: 8A 47 05                 mov     al, [edi+5]
 * 0006FA44: 8B 04 C5 B4 23 00 00     mov     eax, dword ptr ds:unk_23B4[eax*8]
 * 0006FA4B: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 0006FA4F: E8 08 EB 05 00           call    strcpy
 * 0006FA54: 89 34 24                 mov     [esp+1Ch+var_1C], esi
 * 0006FA57: 33 C0                    xor     eax, eax
 * 0006FA59: 8A 47 05                 mov     al, [edi+5]
 * 0006FA5C: 8B 04 C5 B8 23 00 00     mov     eax, dword ptr ds:loc_23B8[eax*8]
 * 0006FA63: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 0006FA67: E8 F0 EA 05 00           call    strcpy
 * 0006FA6C: E9 C7 0E 00 00           jmp     def_70809; jumptable 00070809 default case
 * 0006FA71: 90 90 90                 align 4
 * 0006FA74: 89 1C 24                 mov     [esp+1Ch+var_1C], ebx
 * 0006FA77: 33 C0                    xor     eax, eax
 * 0006FA79: 8A 47 05                 mov     al, [edi+5]
 * 0006FA7C: 8B 04 C5 C4 23 00 00     mov     eax, dword ptr ds:locret_23C4[eax*8]
 * 0006FA83: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 0006FA87: E8 D0 EA 05 00           call    strcpy
 * 0006FA8C: 89 34 24                 mov     [esp+1Ch+var_1C], esi
 * 0006FA8F: 33 C0                    xor     eax, eax
 * 0006FA91: 8A 47 05                 mov     al, [edi+5]
 * 0006FA94: 8B 04 C5 C8 23 00 00     mov     eax, dword ptr ds:loc_23C8[eax*8]
 * 0006FA9B: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 0006FA9F: E8 B8 EA 05 00           call    strcpy
 * 0006FAA4: E9 8F 0E 00 00           jmp     def_70809; jumptable 00070809 default case
 * 0006FAA9: 90 90 90                 align 4
 * 0006FAAC: 89 1C 24                 mov     [esp+1Ch+var_1C], ebx
 * 0006FAAF: 33 C0                    xor     eax, eax
 * 0006FAB1: 8A 47 05                 mov     al, [edi+5]
 * 0006FAB4: 8B 04 C5 D4 23 00 00     mov     eax, dword ptr ds:loc_23D4[eax*8]
 * 0006FABB: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 0006FABF: E8 98 EA 05 00           call    strcpy
 * 0006FAC4: 89 34 24                 mov     [esp+1Ch+var_1C], esi
 * 0006FAC7: 33 C0                    xor     eax, eax
 * 0006FAC9: 8A 47 05                 mov     al, [edi+5]
 * 0006FACC: 8B 04 C5 D8 23 00 00     mov     eax, dword ptr ds:loc_23D7+1[eax*8]
 * 0006FAD3: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 0006FAD7: E8 80 EA 05 00           call    strcpy
 * 0006FADC: E9 57 0E 00 00           jmp     def_70809; jumptable 00070809 default case
 * 0006FAE1: 90 90 90                 align 4
 * 0006FAE4: 89 1C 24                 mov     [esp+1Ch+var_1C], ebx
 * 0006FAE7: 33 C0                    xor     eax, eax
 * 0006FAE9: 8A 47 05                 mov     al, [edi+5]
 * 0006FAEC: 8B 04 C5 E4 23 00 00     mov     eax, dword ptr ds:loc_23E0+4[eax*8]
 * 0006FAF3: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 0006FAF7: E8 60 EA 05 00           call    strcpy
 * 0006FAFC: 89 34 24                 mov     [esp+1Ch+var_1C], esi
 * 0006FAFF: 33 C0                    xor     eax, eax
 * 0006FB01: 8A 47 05                 mov     al, [edi+5]
 * 0006FB04: 8B 04 C5 E8 23 00 00     mov     eax, dword ptr ds:util_23E8[eax*8]
 * 0006FB0B: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 0006FB0F: E8 48 EA 05 00           call    strcpy
 * 0006FB14: E9 1F 0E 00 00           jmp     def_70809; jumptable 00070809 default case
 * 0006FB19: 90 90 90                 align 4
 * 0006FB1C: 89 1C 24                 mov     [esp+1Ch+var_1C], ebx
 * 0006FB1F: 33 C0                    xor     eax, eax
 * 0006FB21: 8A 47 05                 mov     al, [edi+5]
 * 0006FB24: 8B 04 C5 F4 23 00 00     mov     eax, dword ptr ds:loc_23F2+2[eax*8]
 * 0006FB2B: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 0006FB2F: E8 28 EA 05 00           call    strcpy
 * 0006FB34: 89 34 24                 mov     [esp+1Ch+var_1C], esi
 * 0006FB37: 33 C0                    xor     eax, eax
 * 0006FB39: 8A 47 05                 mov     al, [edi+5]
 * 0006FB3C: 8B 04 C5 F8 23 00 00     mov     eax, dword ptr ds:loc_23F7+1[eax*8]
 * 0006FB43: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 0006FB47: E8 10 EA 05 00           call    strcpy
 * 0006FB4C: E9 E7 0D 00 00           jmp     def_70809; jumptable 00070809 default case
 * 0006FB51: 90 90 90                 align 4
 * 0006FB54: 89 1C 24                 mov     [esp+1Ch+var_1C], ebx
 * 0006FB57: 33 C0                    xor     eax, eax
 * 0006FB59: 8A 47 05                 mov     al, [edi+5]
 * 0006FB5C: 8B 04 C5 04 24 00 00     mov     eax, dword ptr ds:loc_2403+1[eax*8]
 * 0006FB63: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 0006FB67: E8 F0 E9 05 00           call    strcpy
 * 0006FB6C: 89 34 24                 mov     [esp+1Ch+var_1C], esi
 * 0006FB6F: 33 C0                    xor     eax, eax
 * 0006FB71: 8A 47 05                 mov     al, [edi+5]
 * 0006FB74: 8B 04 C5 08 24 00 00     mov     eax, dword ptr ds:loc_2407+1[eax*8]
 * 0006FB7B: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 0006FB7F: E8 D8 E9 05 00           call    strcpy
 * 0006FB84: E9 AF 0D 00 00           jmp     def_70809; jumptable 00070809 default case
 * 0006FB89: 90 90 90                 align 4
 * 0006FB8C: 89 1C 24                 mov     [esp+1Ch+var_1C], ebx
 * 0006FB8F: 33 C0                    xor     eax, eax
 * 0006FB91: 8A 47 05                 mov     al, [edi+5]
 * 0006FB94: 8B 04 C5 14 24 00 00     mov     eax, dword ptr ds:locret_2414[eax*8]
 * 0006FB9B: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 0006FB9F: E8 B8 E9 05 00           call    strcpy
 * 0006FBA4: 89 34 24                 mov     [esp+1Ch+var_1C], esi
 * 0006FBA7: 33 C0                    xor     eax, eax
 * 0006FBA9: 8A 47 05                 mov     al, [edi+5]
 * 0006FBAC: 8B 04 C5 18 24 00 00     mov     eax, dword ptr ds:loc_2418[eax*8]
 * 0006FBB3: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 0006FBB7: E8 A0 E9 05 00           call    strcpy
 * 0006FBBC: E9 77 0D 00 00           jmp     def_70809; jumptable 00070809 default case
 * 0006FBC1: 90 90 90                 align 4
 * 0006FBC4: 89 1C 24                 mov     [esp+1Ch+var_1C], ebx
 * 0006FBC7: 33 C0                    xor     eax, eax
 * 0006FBC9: 8A 47 05                 mov     al, [edi+5]
 * 0006FBCC: 8B 04 C5 24 24 00 00     mov     eax, dword ptr ds:loc_2424[eax*8]
 * 0006FBD3: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 0006FBD7: E8 80 E9 05 00           call    strcpy
 * 0006FBDC: 89 34 24                 mov     [esp+1Ch+var_1C], esi
 * 0006FBDF: 33 C0                    xor     eax, eax
 * 0006FBE1: 8A 47 05                 mov     al, [edi+5]
 * 0006FBE4: 8B 04 C5 28 24 00 00     mov     eax, dword ptr ds:loc_2427+1[eax*8]
 * 0006FBEB: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 0006FBEF: E8 68 E9 05 00           call    strcpy
 * 0006FBF4: E9 3F 0D 00 00           jmp     def_70809; jumptable 00070809 default case
 * 0006FBF9: 90 90 90                 align 4
 * 0006FBFC: 89 1C 24                 mov     [esp+1Ch+var_1C], ebx
 * 0006FBFF: 33 C0                    xor     eax, eax
 * 0006FC01: 8A 47 05                 mov     al, [edi+5]
 * 0006FC04: 8B 04 C5 34 24 00 00     mov     eax, dword ptr ds:loc_2434[eax*8]
 * 0006FC0B: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 0006FC0F: E8 48 E9 05 00           call    strcpy
 * 0006FC14: 89 34 24                 mov     [esp+1Ch+var_1C], esi
 * 0006FC17: 33 C0                    xor     eax, eax
 * 0006FC19: 8A 47 05                 mov     al, [edi+5]
 * 0006FC1C: 8B 04 C5 38 24 00 00     mov     eax, dword ptr ds:loc_2436+2[eax*8]
 * 0006FC23: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 0006FC27: E8 30 E9 05 00           call    strcpy
 * 0006FC2C: E9 07 0D 00 00           jmp     def_70809; jumptable 00070809 default case
 * 0006FC31: 90 90 90                 align 4
 * 0006FC34: 89 1C 24                 mov     [esp+1Ch+var_1C], ebx
 * 0006FC37: 33 C0                    xor     eax, eax
 * 0006FC39: 8A 47 05                 mov     al, [edi+5]
 * 0006FC3C: 8B 04 C5 44 24 00 00     mov     eax, dword ptr ds:loc_2442+2[eax*8]
 * 0006FC43: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 0006FC47: E8 10 E9 05 00           call    strcpy
 * 0006FC4C: 89 34 24                 mov     [esp+1Ch+var_1C], esi
 * 0006FC4F: 33 C0                    xor     eax, eax
 * 0006FC51: 8A 47 05                 mov     al, [edi+5]
 * 0006FC54: 8B 04 C5 48 24 00 00     mov     eax, dword ptr ds:loc_2447+1[eax*8]
 * 0006FC5B: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 0006FC5F: E8 F8 E8 05 00           call    strcpy
 * 0006FC64: E9 CF 0C 00 00           jmp     def_70809; jumptable 00070809 default case
 * 0006FC69: 90 90 90                 align 4
 * 0006FC6C: 89 1C 24                 mov     [esp+1Ch+var_1C], ebx
 * 0006FC6F: 33 C0                    xor     eax, eax
 * 0006FC71: 8A 47 05                 mov     al, [edi+5]
 * 0006FC74: 8B 04 C5 54 24 00 00     mov     eax, dword ptr ds:loc_244C+8[eax*8]
 * 0006FC7B: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 0006FC7F: E8 D8 E8 05 00           call    strcpy
 * 0006FC84: 89 34 24                 mov     [esp+1Ch+var_1C], esi
 * 0006FC87: 33 C0                    xor     eax, eax
 * 0006FC89: 8A 47 05                 mov     al, [edi+5]
 * 0006FC8C: 8B 04 C5 58 24 00 00     mov     eax, dword ptr ds:loc_2458[eax*8]
 * 0006FC93: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 0006FC97: E8 C0 E8 05 00           call    strcpy
 * 0006FC9C: E9 97 0C 00 00           jmp     def_70809; jumptable 00070809 default case
 * 0006FCA1: 90 90 90                 align 4
 * 0006FCA4: 89 1C 24                 mov     [esp+1Ch+var_1C], ebx
 * 0006FCA7: 33 C0                    xor     eax, eax
 * 0006FCA9: 8A 47 05                 mov     al, [edi+5]
 * 0006FCAC: 8B 04 C5 64 24 00 00     mov     eax, dword ptr ds:loc_2463+1[eax*8]
 * 0006FCB3: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 0006FCB7: E8 A0 E8 05 00           call    strcpy
 * 0006FCBC: 89 34 24                 mov     [esp+1Ch+var_1C], esi
 * 0006FCBF: 33 C0                    xor     eax, eax
 * 0006FCC1: 8A 47 05                 mov     al, [edi+5]
 * 0006FCC4: 8B 04 C5 68 24 00 00     mov     eax, dword ptr ds:loc_2468[eax*8]
 * 0006FCCB: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 0006FCCF: E8 88 E8 05 00           call    strcpy
 * 0006FCD4: E9 5F 0C 00 00           jmp     def_70809; jumptable 00070809 default case
 * 0006FCD9: 90 90 90                 align 4
 * 0006FCDC: 89 1C 24                 mov     [esp+1Ch+var_1C], ebx
 * 0006FCDF: 33 C0                    xor     eax, eax
 * 0006FCE1: 8A 47 05                 mov     al, [edi+5]
 * 0006FCE4: 8B 04 C5 74 24 00 00     mov     eax, dword ptr ds:loc_2471+3[eax*8]
 * 0006FCEB: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 0006FCEF: E8 68 E8 05 00           call    strcpy
 * 0006FCF4: 89 34 24                 mov     [esp+1Ch+var_1C], esi
 * 0006FCF7: 33 C0                    xor     eax, eax
 * 0006FCF9: 8A 47 05                 mov     al, [edi+5]
 * 0006FCFC: 8B 04 C5 78 24 00 00     mov     eax, dword ptr ds:loc_2476+2[eax*8]
 * 0006FD03: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 0006FD07: E8 50 E8 05 00           call    strcpy
 * 0006FD0C: E9 27 0C 00 00           jmp     def_70809; jumptable 00070809 default case
 * 0006FD11: 90 90 90                 align 4
 * 0006FD14: 89 1C 24                 mov     [esp+1Ch+var_1C], ebx
 * 0006FD17: 33 C0                    xor     eax, eax
 * 0006FD19: 8A 47 05                 mov     al, [edi+5]
 * 0006FD1C: 8B 04 C5 84 24 00 00     mov     eax, dword ptr ds:loc_2481+3[eax*8]
 * 0006FD23: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 0006FD27: E8 30 E8 05 00           call    strcpy
 * 0006FD2C: 89 34 24                 mov     [esp+1Ch+var_1C], esi
 * 0006FD2F: 33 C0                    xor     eax, eax
 * 0006FD31: 8A 47 05                 mov     al, [edi+5]
 * 0006FD34: 8B 04 C5 88 24 00 00     mov     eax, dword ptr ds:loc_2488[eax*8]
 * 0006FD3B: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 0006FD3F: E8 18 E8 05 00           call    strcpy
 * 0006FD44: E9 EF 0B 00 00           jmp     def_70809; jumptable 00070809 default case
 * 0006FD49: 90 90 90                 align 4
 * 0006FD4C: 89 1C 24                 mov     [esp+1Ch+var_1C], ebx
 * 0006FD4F: 33 C0                    xor     eax, eax
 * 0006FD51: 8A 47 05                 mov     al, [edi+5]
 * 0006FD54: 8B 04 C5 94 24 00 00     mov     eax, dword ptr ds:loc_2494[eax*8]
 * 0006FD5B: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 0006FD5F: E8 F8 E7 05 00           call    strcpy
 * 0006FD64: 89 34 24                 mov     [esp+1Ch+var_1C], esi
 * 0006FD67: 33 C0                    xor     eax, eax
 * 0006FD69: 8A 47 05                 mov     al, [edi+5]
 * 0006FD6C: 8B 04 C5 98 24 00 00     mov     eax, dword ptr ds:loc_2496+2[eax*8]
 * 0006FD73: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 0006FD77: E8 E0 E7 05 00           call    strcpy
 * 0006FD7C: E9 B7 0B 00 00           jmp     def_70809; jumptable 00070809 default case
 * 0006FD81: 90 90 90                 align 4
 * 0006FD84: 89 1C 24                 mov     [esp+1Ch+var_1C], ebx
 * 0006FD87: 33 C0                    xor     eax, eax
 * 0006FD89: 8A 47 05                 mov     al, [edi+5]
 * 0006FD8C: 8B 04 C5 A4 24 00 00     mov     eax, dword ptr ds:loc_24A4[eax*8]
 * 0006FD93: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 0006FD97: E8 C0 E7 05 00           call    strcpy
 * 0006FD9C: 89 34 24                 mov     [esp+1Ch+var_1C], esi
 * 0006FD9F: 33 C0                    xor     eax, eax
 * 0006FDA1: 8A 47 05                 mov     al, [edi+5]
 * 0006FDA4: 8B 04 C5 A8 24 00 00     mov     eax, dword ptr ds:loc_24A4+4[eax*8]
 * 0006FDAB: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 0006FDAF: E8 A8 E7 05 00           call    strcpy
 * 0006FDB4: E9 7F 0B 00 00           jmp     def_70809; jumptable 00070809 default case
 * 0006FDB9: 90 90 90                 align 4
 * 0006FDBC: 89 1C 24                 mov     [esp+1Ch+var_1C], ebx
 * 0006FDBF: 33 C0                    xor     eax, eax
 * 0006FDC1: 8A 47 05                 mov     al, [edi+5]
 * 0006FDC4: 8B 04 C5 B4 24 00 00     mov     eax, dword ptr ds:loc_24B2+2[eax*8]
 * 0006FDCB: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 0006FDCF: E8 88 E7 05 00           call    strcpy
 * 0006FDD4: 89 34 24                 mov     [esp+1Ch+var_1C], esi
 * 0006FDD7: 33 C0                    xor     eax, eax
 * 0006FDD9: 8A 47 05                 mov     al, [edi+5]
 * 0006FDDC: 8B 04 C5 B8 24 00 00     mov     eax, dword ptr ds:loc_24B7+1[eax*8]
 * 0006FDE3: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 0006FDE7: E8 70 E7 05 00           call    strcpy
 * 0006FDEC: E9 47 0B 00 00           jmp     def_70809; jumptable 00070809 default case
 * 0006FDF1: 90 90 90                 align 4
 * 0006FDF4: 89 1C 24                 mov     [esp+1Ch+var_1C], ebx
 * 0006FDF7: 33 C0                    xor     eax, eax
 * 0006FDF9: 8A 47 05                 mov     al, [edi+5]
 * 0006FDFC: 8B 04 C5 C4 24 00 00     mov     eax, dword ptr ds:loc_24C2+2[eax*8]
 * 0006FE03: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 0006FE07: E8 50 E7 05 00           call    strcpy
 * 0006FE0C: 89 34 24                 mov     [esp+1Ch+var_1C], esi
 * 0006FE0F: 33 C0                    xor     eax, eax
 * 0006FE11: 8A 47 05                 mov     al, [edi+5]
 * 0006FE14: 8B 04 C5 C8 24 00 00     mov     eax, dword ptr ds:loc_24C7+1[eax*8]
 * 0006FE1B: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 0006FE1F: E8 38 E7 05 00           call    strcpy
 * 0006FE24: E9 0F 0B 00 00           jmp     def_70809; jumptable 00070809 default case
 * 0006FE29: 90 90 90                 align 4
 * 0006FE2C: 89 1C 24                 mov     [esp+1Ch+var_1C], ebx
 * 0006FE2F: 33 C0                    xor     eax, eax
 * 0006FE31: 8A 47 05                 mov     al, [edi+5]
 * 0006FE34: 8B 04 C5 D4 24 00 00     mov     eax, dword ptr ds:loc_24D4[eax*8]
 * 0006FE3B: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 0006FE3F: E8 18 E7 05 00           call    strcpy
 * 0006FE44: 89 34 24                 mov     [esp+1Ch+var_1C], esi
 * 0006FE47: 33 C0                    xor     eax, eax
 * 0006FE49: 8A 47 05                 mov     al, [edi+5]
 * 0006FE4C: 8B 04 C5 D8 24 00 00     mov     eax, dword ptr ds:loc_24D8[eax*8]
 * 0006FE53: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 0006FE57: E8 00 E7 05 00           call    strcpy
 * 0006FE5C: E9 D7 0A 00 00           jmp     def_70809; jumptable 00070809 default case
 * 0006FE61: 90 90 90                 align 4
 * 0006FE64: 89 1C 24                 mov     [esp+1Ch+var_1C], ebx
 * 0006FE67: 33 C0                    xor     eax, eax
 * 0006FE69: 8A 47 05                 mov     al, [edi+5]
 * 0006FE6C: 8B 04 C5 E4 24 00 00     mov     eax, dword ptr ds:loc_24E3+1[eax*8]
 * 0006FE73: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 0006FE77: E8 E0 E6 05 00           call    strcpy
 * 0006FE7C: 89 34 24                 mov     [esp+1Ch+var_1C], esi
 * 0006FE7F: 33 C0                    xor     eax, eax
 * 0006FE81: 8A 47 05                 mov     al, [edi+5]
 * 0006FE84: 8B 04 C5 E8 24 00 00     mov     eax, dword ptr ds:loc_24E7+1[eax*8]
 * 0006FE8B: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 0006FE8F: E8 C8 E6 05 00           call    strcpy
 * 0006FE94: E9 9F 0A 00 00           jmp     def_70809; jumptable 00070809 default case
 * 0006FE99: 90 90 90                 align 4
 * 0006FE9C: 89 1C 24                 mov     [esp+1Ch+var_1C], ebx
 * 0006FE9F: 33 C0                    xor     eax, eax
 * 0006FEA1: 8A 47 05                 mov     al, [edi+5]
 * 0006FEA4: 8B 04 C5 F4 24 00 00     mov     eax, dword ptr ds:loc_24F4[eax*8]
 * 0006FEAB: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 0006FEAF: E8 A8 E6 05 00           call    strcpy
 * 0006FEB4: 89 34 24                 mov     [esp+1Ch+var_1C], esi
 * 0006FEB7: 33 C0                    xor     eax, eax
 * 0006FEB9: 8A 47 05                 mov     al, [edi+5]
 * 0006FEBC: 8B 04 C5 F8 24 00 00     mov     eax, dword ptr ds:loc_24F5+3[eax*8]
 * 0006FEC3: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 0006FEC7: E8 90 E6 05 00           call    strcpy
 * 0006FECC: E9 67 0A 00 00           jmp     def_70809; jumptable 00070809 default case
 * 0006FED1: 90 90 90                 align 4
 * 0006FED4: 89 1C 24                 mov     [esp+1Ch+var_1C], ebx
 * 0006FED7: 33 C0                    xor     eax, eax
 * 0006FED9: 8A 47 05                 mov     al, [edi+5]
 * 0006FEDC: 8B 04 85 A4 26 00 00     mov     eax, ds:dword_25C4+0E0h[eax*4]
 * 0006FEE3: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 0006FEE7: E8 70 E6 05 00           call    strcpy
 * 0006FEEC: 89 34 24                 mov     [esp+1Ch+var_1C], esi
 * 0006FEEF: 33 C0                    xor     eax, eax
 * 0006FEF1: 8A 47 05                 mov     al, [edi+5]
 * 0006FEF4: 8B 04 85 C4 26 00 00     mov     eax, ds:dword_25C4+100h[eax*4]
 * 0006FEFB: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 0006FEFF: E8 58 E6 05 00           call    strcpy
 * 0006FF04: E9 2F 0A 00 00           jmp     def_70809; jumptable 00070809 default case
 * 0006FF09: 90 90 90                 align 4
 * 0006FF0C: 89 1C 24                 mov     [esp+1Ch+var_1C], ebx
 * 0006FF0F: 33 C0                    xor     eax, eax
 * 0006FF11: 8A 47 05                 mov     al, [edi+5]
 * 0006FF14: 8B 04 85 AC 26 00 00     mov     eax, ds:dword_25C4+0E8h[eax*4]
 * 0006FF1B: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 0006FF1F: E8 38 E6 05 00           call    strcpy
 * 0006FF24: 89 34 24                 mov     [esp+1Ch+var_1C], esi
 * 0006FF27: 33 C0                    xor     eax, eax
 * 0006FF29: 8A 47 05                 mov     al, [edi+5]
 * 0006FF2C: 8B 04 85 C4 26 00 00     mov     eax, ds:dword_25C4+100h[eax*4]
 * 0006FF33: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 0006FF37: E8 20 E6 05 00           call    strcpy
 * 0006FF3C: E9 F7 09 00 00           jmp     def_70809; jumptable 00070809 default case
 * 0006FF41: 90 90 90                 align 4
 * 0006FF44: 89 1C 24                 mov     [esp+1Ch+var_1C], ebx
 * 0006FF47: 33 C0                    xor     eax, eax
 * 0006FF49: 8A 47 05                 mov     al, [edi+5]
 * 0006FF4C: 8B 04 85 B4 26 00 00     mov     eax, ds:dword_25C4+0F0h[eax*4]
 * 0006FF53: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 0006FF57: E8 00 E6 05 00           call    strcpy
 * 0006FF5C: 89 34 24                 mov     [esp+1Ch+var_1C], esi
 * 0006FF5F: 33 C0                    xor     eax, eax
 * 0006FF61: 8A 47 05                 mov     al, [edi+5]
 * 0006FF64: 8B 04 85 C4 26 00 00     mov     eax, ds:dword_25C4+100h[eax*4]
 * 0006FF6B: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 0006FF6F: E8 E8 E5 05 00           call    strcpy
 * 0006FF74: E9 BF 09 00 00           jmp     def_70809; jumptable 00070809 default case
 * 0006FF79: 90 90 90                 align 4
 * 0006FF7C: 89 1C 24                 mov     [esp+1Ch+var_1C], ebx
 * 0006FF7F: 33 C0                    xor     eax, eax
 * 0006FF81: 8A 47 05                 mov     al, [edi+5]
 * 0006FF84: 8B 04 85 BC 26 00 00     mov     eax, ds:dword_25C4+0F8h[eax*4]
 * 0006FF8B: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 0006FF8F: E8 C8 E5 05 00           call    strcpy
 * 0006FF94: 89 34 24                 mov     [esp+1Ch+var_1C], esi
 * 0006FF97: 33 C0                    xor     eax, eax
 * 0006FF99: 8A 47 05                 mov     al, [edi+5]
 * 0006FF9C: 8B 04 85 C4 26 00 00     mov     eax, ds:dword_25C4+100h[eax*4]
 * 0006FFA3: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 0006FFA7: E8 B0 E5 05 00           call    strcpy
 * 0006FFAC: E9 87 09 00 00           jmp     def_70809; jumptable 00070809 default case
 * 0006FFB1: 90 90 90                 align 4
 * 0006FFB4: 89 1C 24                 mov     [esp+1Ch+var_1C], ebx
 * 0006FFB7: 33 C0                    xor     eax, eax
 * 0006FFB9: 8A 47 05                 mov     al, [edi+5]
 * 0006FFBC: 8B 04 85 A4 26 00 00     mov     eax, ds:dword_25C4+0E0h[eax*4]
 * 0006FFC3: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 0006FFC7: E8 90 E5 05 00           call    strcpy
 * 0006FFCC: 89 34 24                 mov     [esp+1Ch+var_1C], esi
 * 0006FFCF: 33 C0                    xor     eax, eax
 * 0006FFD1: 8A 47 05                 mov     al, [edi+5]
 * 0006FFD4: 8B 04 85 CC 26 00 00     mov     eax, ds:dword_25C4+108h[eax*4]
 * 0006FFDB: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 0006FFDF: E8 78 E5 05 00           call    strcpy
 * 0006FFE4: E9 4F 09 00 00           jmp     def_70809; jumptable 00070809 default case
 * 0006FFE9: 90 90 90                 align 4
 * 0006FFEC: 89 1C 24                 mov     [esp+1Ch+var_1C], ebx
 * 0006FFEF: 33 C0                    xor     eax, eax
 * 0006FFF1: 8A 47 05                 mov     al, [edi+5]
 * 0006FFF4: 8B 04 85 AC 26 00 00     mov     eax, ds:dword_25C4+0E8h[eax*4]
 * 0006FFFB: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 0006FFFF: E8 58 E5 05 00           call    strcpy
 * 00070004: 89 34 24                 mov     [esp+1Ch+var_1C], esi
 * 00070007: 33 C0                    xor     eax, eax
 * 00070009: 8A 47 05                 mov     al, [edi+5]
 * 0007000C: 8B 04 85 CC 26 00 00     mov     eax, ds:dword_25C4+108h[eax*4]
 * 00070013: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 00070017: E8 40 E5 05 00           call    strcpy
 * 0007001C: E9 17 09 00 00           jmp     def_70809; jumptable 00070809 default case
 * 00070021: 90 90 90                 align 4
 * 00070024: 89 1C 24                 mov     [esp+1Ch+var_1C], ebx
 * 00070027: 33 C0                    xor     eax, eax
 * 00070029: 8A 47 05                 mov     al, [edi+5]
 * 0007002C: 8B 04 85 B4 26 00 00     mov     eax, ds:dword_25C4+0F0h[eax*4]
 * 00070033: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 00070037: E8 20 E5 05 00           call    strcpy
 * 0007003C: 89 34 24                 mov     [esp+1Ch+var_1C], esi
 * 0007003F: 33 C0                    xor     eax, eax
 * 00070041: 8A 47 05                 mov     al, [edi+5]
 * 00070044: 8B 04 85 CC 26 00 00     mov     eax, ds:dword_25C4+108h[eax*4]
 * 0007004B: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 0007004F: E8 08 E5 05 00           call    strcpy
 * 00070054: E9 DF 08 00 00           jmp     def_70809; jumptable 00070809 default case
 * 00070059: 90 90 90                 align 4
 * 0007005C: 89 1C 24                 mov     [esp+1Ch+var_1C], ebx
 * 0007005F: 33 C0                    xor     eax, eax
 * 00070061: 8A 47 05                 mov     al, [edi+5]
 * 00070064: 8B 04 85 BC 26 00 00     mov     eax, ds:dword_25C4+0F8h[eax*4]
 * 0007006B: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 0007006F: E8 E8 E4 05 00           call    strcpy
 * 00070074: 89 34 24                 mov     [esp+1Ch+var_1C], esi
 * 00070077: 33 C0                    xor     eax, eax
 * 00070079: 8A 47 05                 mov     al, [edi+5]
 * 0007007C: 8B 04 85 CC 26 00 00     mov     eax, ds:dword_25C4+108h[eax*4]
 * 00070083: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 00070087: E8 D0 E4 05 00           call    strcpy
 * 0007008C: E9 A7 08 00 00           jmp     def_70809; jumptable 00070809 default case
 * 00070091: 90 90 90                 align 4
 * 00070094: 89 1C 24                 mov     [esp+1Ch+var_1C], ebx
 * 00070097: 33 C0                    xor     eax, eax
 * 00070099: 8A 47 05                 mov     al, [edi+5]
 * 0007009C: 8B 04 85 A4 26 00 00     mov     eax, ds:dword_25C4+0E0h[eax*4]
 * 000700A3: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 000700A7: E8 B0 E4 05 00           call    strcpy
 * 000700AC: 89 34 24                 mov     [esp+1Ch+var_1C], esi
 * 000700AF: 33 C0                    xor     eax, eax
 * 000700B1: 8A 47 05                 mov     al, [edi+5]
 * 000700B4: 8B 04 85 D4 26 00 00     mov     eax, ds:dword_25C4+110h[eax*4]
 * 000700BB: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 000700BF: E8 98 E4 05 00           call    strcpy
 * 000700C4: E9 6F 08 00 00           jmp     def_70809; jumptable 00070809 default case
 * 000700C9: 90 90 90                 align 4
 * 000700CC: 89 1C 24                 mov     [esp+1Ch+var_1C], ebx
 * 000700CF: 33 C0                    xor     eax, eax
 * 000700D1: 8A 47 05                 mov     al, [edi+5]
 * 000700D4: 8B 04 85 AC 26 00 00     mov     eax, ds:dword_25C4+0E8h[eax*4]
 * 000700DB: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 000700DF: E8 78 E4 05 00           call    strcpy
 * 000700E4: 89 34 24                 mov     [esp+1Ch+var_1C], esi
 * 000700E7: 33 C0                    xor     eax, eax
 * 000700E9: 8A 47 05                 mov     al, [edi+5]
 * 000700EC: 8B 04 85 D4 26 00 00     mov     eax, ds:dword_25C4+110h[eax*4]
 * 000700F3: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 000700F7: E8 60 E4 05 00           call    strcpy
 * 000700FC: E9 37 08 00 00           jmp     def_70809; jumptable 00070809 default case
 * 00070101: 90 90 90                 align 4
 * 00070104: 89 1C 24                 mov     [esp+1Ch+var_1C], ebx
 * 00070107: 33 C0                    xor     eax, eax
 * 00070109: 8A 47 05                 mov     al, [edi+5]
 * 0007010C: 8B 04 85 B4 26 00 00     mov     eax, ds:dword_25C4+0F0h[eax*4]
 * 00070113: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 00070117: E8 40 E4 05 00           call    strcpy
 * 0007011C: 89 34 24                 mov     [esp+1Ch+var_1C], esi
 * 0007011F: 33 C0                    xor     eax, eax
 * 00070121: 8A 47 05                 mov     al, [edi+5]
 * 00070124: 8B 04 85 D4 26 00 00     mov     eax, ds:dword_25C4+110h[eax*4]
 * 0007012B: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 0007012F: E8 28 E4 05 00           call    strcpy
 * 00070134: E9 FF 07 00 00           jmp     def_70809; jumptable 00070809 default case
 * 00070139: 90 90 90                 align 4
 * 0007013C: 89 1C 24                 mov     [esp+1Ch+var_1C], ebx
 * 0007013F: 33 C0                    xor     eax, eax
 * 00070141: 8A 47 05                 mov     al, [edi+5]
 * 00070144: 8B 04 85 BC 26 00 00     mov     eax, ds:dword_25C4+0F8h[eax*4]
 * 0007014B: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 0007014F: E8 08 E4 05 00           call    strcpy
 * 00070154: 89 34 24                 mov     [esp+1Ch+var_1C], esi
 * 00070157: 33 C0                    xor     eax, eax
 * 00070159: 8A 47 05                 mov     al, [edi+5]
 * 0007015C: 8B 04 85 D4 26 00 00     mov     eax, ds:dword_25C4+110h[eax*4]
 * 00070163: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 00070167: E8 F0 E3 05 00           call    strcpy
 * 0007016C: E9 C7 07 00 00           jmp     def_70809; jumptable 00070809 default case
 * 00070171: 90 90 90                 align 4
 * 00070174: 89 1C 24                 mov     [esp+1Ch+var_1C], ebx
 * 00070177: 33 C0                    xor     eax, eax
 * 00070179: 8A 47 05                 mov     al, [edi+5]
 * 0007017C: 8B 04 C5 04 25 00 00     mov     eax, dword ptr ds:loc_2501+3[eax*8]
 * 00070183: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 00070187: E8 D0 E3 05 00           call    strcpy
 * 0007018C: 89 34 24                 mov     [esp+1Ch+var_1C], esi
 * 0007018F: 33 C0                    xor     eax, eax
 * 00070191: 8A 47 05                 mov     al, [edi+5]
 * 00070194: 8B 04 C5 08 25 00 00     mov     eax, dword ptr ds:loc_2505+3[eax*8]
 * 0007019B: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 0007019F: E8 B8 E3 05 00           call    strcpy
 * 000701A4: E9 8F 07 00 00           jmp     def_70809; jumptable 00070809 default case
 * 000701A9: 90 90 90                 align 4
 * 000701AC: 89 1C 24                 mov     [esp+1Ch+var_1C], ebx
 * 000701AF: 33 C0                    xor     eax, eax
 * 000701B1: 8A 47 05                 mov     al, [edi+5]
 * 000701B4: 8B 04 C5 14 25 00 00     mov     eax, dword ptr ds:loc_2512+2[eax*8]
 * 000701BB: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 000701BF: E8 98 E3 05 00           call    strcpy
 * 000701C4: 89 34 24                 mov     [esp+1Ch+var_1C], esi
 * 000701C7: 33 C0                    xor     eax, eax
 * 000701C9: 8A 47 05                 mov     al, [edi+5]
 * 000701CC: 8B 04 C5 18 25 00 00     mov     eax, dword ptr ds:loc_2518[eax*8]
 * 000701D3: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 000701D7: E8 80 E3 05 00           call    strcpy
 * 000701DC: E9 57 07 00 00           jmp     def_70809; jumptable 00070809 default case
 * 000701E1: 90 90 90                 align 4
 * 000701E4: 89 1C 24                 mov     [esp+1Ch+var_1C], ebx
 * 000701E7: 33 C0                    xor     eax, eax
 * 000701E9: 8A 47 05                 mov     al, [edi+5]
 * 000701EC: 8B 04 C5 24 25 00 00     mov     eax, dword ptr ds:loc_2524[eax*8]
 * 000701F3: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 000701F7: E8 60 E3 05 00           call    strcpy
 * 000701FC: 89 34 24                 mov     [esp+1Ch+var_1C], esi
 * 000701FF: 33 C0                    xor     eax, eax
 * 00070201: 8A 47 05                 mov     al, [edi+5]
 * 00070204: 8B 04 C5 28 25 00 00     mov     eax, dword ptr ds:loc_2528[eax*8]
 * 0007020B: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 0007020F: E8 48 E3 05 00           call    strcpy
 * 00070214: E9 1F 07 00 00           jmp     def_70809; jumptable 00070809 default case
 * 00070219: 90 90 90                 align 4
 * 0007021C: 89 1C 24                 mov     [esp+1Ch+var_1C], ebx
 * 0007021F: 33 C0                    xor     eax, eax
 * 00070221: 8A 47 05                 mov     al, [edi+5]
 * 00070224: 8B 04 C5 34 25 00 00     mov     eax, dword ptr ds:loc_2534[eax*8]
 * 0007022B: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 0007022F: E8 28 E3 05 00           call    strcpy
 * 00070234: 89 34 24                 mov     [esp+1Ch+var_1C], esi
 * 00070237: 33 C0                    xor     eax, eax
 * 00070239: 8A 47 05                 mov     al, [edi+5]
 * 0007023C: 8B 04 C5 38 25 00 00     mov     eax, dword ptr ds:loc_2535+3[eax*8]
 * 00070243: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 00070247: E8 10 E3 05 00           call    strcpy
 * 0007024C: E9 E7 06 00 00           jmp     def_70809; jumptable 00070809 default case
 * 00070251: 90 90 90                 align 4
 * 00070254: 89 1C 24                 mov     [esp+1Ch+var_1C], ebx
 * 00070257: 33 C0                    xor     eax, eax
 * 00070259: 8A 47 05                 mov     al, [edi+5]
 * 0007025C: 8B 04 C5 44 25 00 00     mov     eax, dword ptr ds:loc_2544[eax*8]
 * 00070263: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 00070267: E8 F0 E2 05 00           call    strcpy
 * 0007026C: 89 34 24                 mov     [esp+1Ch+var_1C], esi
 * 0007026F: 33 C0                    xor     eax, eax
 * 00070271: 8A 47 05                 mov     al, [edi+5]
 * 00070274: 8B 04 C5 48 25 00 00     mov     eax, dword ptr ds:loc_2544+4[eax*8]
 * 0007027B: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 0007027F: E8 D8 E2 05 00           call    strcpy
 * 00070284: E9 AF 06 00 00           jmp     def_70809; jumptable 00070809 default case
 * 00070289: 90 90 90                 align 4
 * 0007028C: 89 1C 24                 mov     [esp+1Ch+var_1C], ebx
 * 0007028F: 33 C0                    xor     eax, eax
 * 00070291: 8A 47 05                 mov     al, [edi+5]
 * 00070294: 8B 04 C5 54 25 00 00     mov     eax, dword ptr ds:loc_2554[eax*8]
 * 0007029B: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 0007029F: E8 B8 E2 05 00           call    strcpy
 * 000702A4: 89 34 24                 mov     [esp+1Ch+var_1C], esi
 * 000702A7: 33 C0                    xor     eax, eax
 * 000702A9: 8A 47 05                 mov     al, [edi+5]
 * 000702AC: 8B 04 C5 58 25 00 00     mov     eax, dword ptr ds:loc_2558[eax*8]
 * 000702B3: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 000702B7: E8 A0 E2 05 00           call    strcpy
 * 000702BC: E9 77 06 00 00           jmp     def_70809; jumptable 00070809 default case
 * 000702C1: 90 90 90                 align 4
 * 000702C4: 89 1C 24                 mov     [esp+1Ch+var_1C], ebx
 * 000702C7: 33 C0                    xor     eax, eax
 * 000702C9: 8A 47 05                 mov     al, [edi+5]
 * 000702CC: 8B 04 C5 64 25 00 00     mov     eax, dword ptr ds:locret_2564[eax*8]
 * 000702D3: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 000702D7: E8 80 E2 05 00           call    strcpy
 * 000702DC: 89 34 24                 mov     [esp+1Ch+var_1C], esi
 * 000702DF: 33 C0                    xor     eax, eax
 * 000702E1: 8A 47 05                 mov     al, [edi+5]
 * 000702E4: 8B 04 C5 68 25 00 00     mov     eax, dword ptr ds:loc_2565+3[eax*8]
 * 000702EB: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 000702EF: E8 68 E2 05 00           call    strcpy
 * 000702F4: E9 3F 06 00 00           jmp     def_70809; jumptable 00070809 default case
 * 000702F9: 90 90 90                 align 4
 * 000702FC: 89 1C 24                 mov     [esp+1Ch+var_1C], ebx
 * 000702FF: 33 C0                    xor     eax, eax
 * 00070301: 8A 47 05                 mov     al, [edi+5]
 * 00070304: 8B 04 C5 74 25 00 00     mov     eax, dword ptr ds:loc_2573+1[eax*8]
 * 0007030B: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 0007030F: E8 48 E2 05 00           call    strcpy
 * 00070314: 89 34 24                 mov     [esp+1Ch+var_1C], esi
 * 00070317: 33 C0                    xor     eax, eax
 * 00070319: 8A 47 05                 mov     al, [edi+5]
 * 0007031C: 8B 04 C5 78 25 00 00     mov     eax, dword ptr ds:loc_2577+1[eax*8]
 * 00070323: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 00070327: E8 30 E2 05 00           call    strcpy
 * 0007032C: E9 07 06 00 00           jmp     def_70809; jumptable 00070809 default case
 * 00070331: 90 90 90                 align 4
 * 00070334: 89 1C 24                 mov     [esp+1Ch+var_1C], ebx
 * 00070337: 33 C0                    xor     eax, eax
 * 00070339: 8A 47 05                 mov     al, [edi+5]
 * 0007033C: 8B 04 C5 84 25 00 00     mov     eax, dword ptr ds:loc_2583+1[eax*8]
 * 00070343: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 00070347: E8 10 E2 05 00           call    strcpy
 * 0007034C: 89 34 24                 mov     [esp+1Ch+var_1C], esi
 * 0007034F: 33 C0                    xor     eax, eax
 * 00070351: 8A 47 05                 mov     al, [edi+5]
 * 00070354: 8B 04 C5 88 25 00 00     mov     eax, dword ptr ds:loc_2587+1[eax*8]
 * 0007035B: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 0007035F: E8 F8 E1 05 00           call    strcpy
 * 00070364: E9 CF 05 00 00           jmp     def_70809; jumptable 00070809 default case
 * 00070369: 90 90 90                 align 4
 * 0007036C: 89 1C 24                 mov     [esp+1Ch+var_1C], ebx
 * 0007036F: 33 C0                    xor     eax, eax
 * 00070371: 8A 47 05                 mov     al, [edi+5]
 * 00070374: 8B 04 C5 1C 1F 00 00     mov     eax, ds:dword_1F00+1Ch[eax*8]
 * 0007037B: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 0007037F: E8 D8 E1 05 00           call    strcpy
 * 00070384: 89 34 24                 mov     [esp+1Ch+var_1C], esi
 * 00070387: 33 C0                    xor     eax, eax
 * 00070389: 8A 47 05                 mov     al, [edi+5]
 * 0007038C: 8B 04 C5 20 1F 00 00     mov     eax, ds:dword_1F00+20h[eax*8]
 * 00070393: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 00070397: E8 C0 E1 05 00           call    strcpy
 * 0007039C: E9 97 05 00 00           jmp     def_70809; jumptable 00070809 default case
 * 000703A1: 90 90 90                 align 4
 * 000703A4: 89 1C 24                 mov     [esp+1Ch+var_1C], ebx
 * 000703A7: 33 C0                    xor     eax, eax
 * 000703A9: 8A 47 05                 mov     al, [edi+5]
 * 000703AC: 8B 04 C5 FC 1E 00 00     mov     eax, dword ptr ds:unk_1EFC[eax*8]
 * 000703B3: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 000703B7: E8 A0 E1 05 00           call    strcpy
 * 000703BC: 89 34 24                 mov     [esp+1Ch+var_1C], esi
 * 000703BF: 33 C0                    xor     eax, eax
 * 000703C1: 8A 47 05                 mov     al, [edi+5]
 * 000703C4: 8B 04 C5 00 1F 00 00     mov     eax, ds:dword_1F00[eax*8]
 * 000703CB: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 000703CF: E8 88 E1 05 00           call    strcpy
 * 000703D4: E9 5F 05 00 00           jmp     def_70809; jumptable 00070809 default case
 * 000703D9: 90 90 90                 align 4
 * 000703DC: 89 1C 24                 mov     [esp+1Ch+var_1C], ebx
 * 000703DF: 33 C0                    xor     eax, eax
 * 000703E1: 8A 47 05                 mov     al, [edi+5]
 * 000703E4: 8B 04 C5 0C 1F 00 00     mov     eax, ds:dword_1F00+0Ch[eax*8]
 * 000703EB: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 000703EF: E8 68 E1 05 00           call    strcpy
 * 000703F4: 89 34 24                 mov     [esp+1Ch+var_1C], esi
 * 000703F7: 33 C0                    xor     eax, eax
 * 000703F9: 8A 47 05                 mov     al, [edi+5]
 * 000703FC: 8B 04 C5 10 1F 00 00     mov     eax, ds:dword_1F00+10h[eax*8]
 * 00070403: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 00070407: E8 50 E1 05 00           call    strcpy
 * 0007040C: E9 27 05 00 00           jmp     def_70809; jumptable 00070809 default case
 * 00070411: 90 90 90                 align 4
 * 00070414: 89 1C 24                 mov     [esp+1Ch+var_1C], ebx
 * 00070417: 33 C0                    xor     eax, eax
 * 00070419: 8A 47 05                 mov     al, [edi+5]
 * 0007041C: 8B 04 C5 94 25 00 00     mov     eax, dword ptr ds:loc_2594[eax*8]
 * 00070423: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 00070427: E8 30 E1 05 00           call    strcpy
 * 0007042C: 89 34 24                 mov     [esp+1Ch+var_1C], esi
 * 0007042F: 33 C0                    xor     eax, eax
 * 00070431: 8A 47 05                 mov     al, [edi+5]
 * 00070434: 8B 04 C5 98 25 00 00     mov     eax, dword ptr ds:unk_2598[eax*8]
 * 0007043B: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 0007043F: E8 18 E1 05 00           call    strcpy
 * 00070444: E9 EF 04 00 00           jmp     def_70809; jumptable 00070809 default case
 * 00070449: 90 90 90                 align 4
 * 0007044C: 89 1C 24                 mov     [esp+1Ch+var_1C], ebx
 * 0007044F: 33 C0                    xor     eax, eax
 * 00070451: 8A 47 05                 mov     al, [edi+5]
 * 00070454: 8B 04 C5 A4 25 00 00     mov     eax, ds:dword_25A4[eax*8]
 * 0007045B: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 0007045F: E8 F8 E0 05 00           call    strcpy
 * 00070464: 89 34 24                 mov     [esp+1Ch+var_1C], esi
 * 00070467: 33 C0                    xor     eax, eax
 * 00070469: 8A 47 05                 mov     al, [edi+5]
 * 0007046C: 8B 04 C5 A8 25 00 00     mov     eax, ds:dword_25A8[eax*8]
 * 00070473: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 00070477: E8 E0 E0 05 00           call    strcpy
 * 0007047C: E9 B7 04 00 00           jmp     def_70809; jumptable 00070809 default case
 * 00070481: 90 90 90                 align 4
 * 00070484: 89 1C 24                 mov     [esp+1Ch+var_1C], ebx
 * 00070487: 33 C0                    xor     eax, eax
 * 00070489: 8A 47 05                 mov     al, [edi+5]
 * 0007048C: 8B 04 C5 B4 25 00 00     mov     eax, ds:dword_25B4[eax*8]
 * 00070493: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 00070497: E8 C0 E0 05 00           call    strcpy
 * 0007049C: 89 34 24                 mov     [esp+1Ch+var_1C], esi
 * 0007049F: 33 C0                    xor     eax, eax
 * 000704A1: 8A 47 05                 mov     al, [edi+5]
 * 000704A4: 8B 04 C5 B8 25 00 00     mov     eax, ds:dword_25B8[eax*8]
 * 000704AB: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 000704AF: E8 A8 E0 05 00           call    strcpy
 * 000704B4: E9 7F 04 00 00           jmp     def_70809; jumptable 00070809 default case
 * 000704B9: 90 90 90                 align 4
 * 000704BC: 89 1C 24                 mov     [esp+1Ch+var_1C], ebx
 * 000704BF: 33 C0                    xor     eax, eax
 * 000704C1: 8A 47 05                 mov     al, [edi+5]
 * 000704C4: 8B 04 C5 C4 25 00 00     mov     eax, ds:dword_25C4[eax*8]
 * 000704CB: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 000704CF: E8 88 E0 05 00           call    strcpy
 * 000704D4: 89 34 24                 mov     [esp+1Ch+var_1C], esi
 * 000704D7: 33 C0                    xor     eax, eax
 * 000704D9: 8A 47 05                 mov     al, [edi+5]
 * 000704DC: 8B 04 C5 C8 25 00 00     mov     eax, ds:dword_25C4+4[eax*8]
 * 000704E3: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 000704E7: E8 70 E0 05 00           call    strcpy
 * 000704EC: E9 47 04 00 00           jmp     def_70809; jumptable 00070809 default case
 * 000704F1: 90 90 90                 align 4
 * 000704F4: 89 1C 24                 mov     [esp+1Ch+var_1C], ebx
 * 000704F7: 33 C0                    xor     eax, eax
 * 000704F9: 8A 47 05                 mov     al, [edi+5]
 * 000704FC: 8B 04 C5 D4 25 00 00     mov     eax, ds:dword_25C4+10h[eax*8]
 * 00070503: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 00070507: E8 50 E0 05 00           call    strcpy
 * 0007050C: 89 34 24                 mov     [esp+1Ch+var_1C], esi
 * 0007050F: 33 C0                    xor     eax, eax
 * 00070511: 8A 47 05                 mov     al, [edi+5]
 * 00070514: 8B 04 C5 D8 25 00 00     mov     eax, ds:dword_25C4+14h[eax*8]
 * 0007051B: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 0007051F: E8 38 E0 05 00           call    strcpy
 * 00070524: E9 0F 04 00 00           jmp     def_70809; jumptable 00070809 default case
 * 00070529: 90 90 90                 align 4
 * 0007052C: 89 1C 24                 mov     [esp+1Ch+var_1C], ebx
 * 0007052F: 33 C0                    xor     eax, eax
 * 00070531: 8A 47 05                 mov     al, [edi+5]
 * 00070534: 8B 04 C5 84 23 00 00     mov     eax, ds:dword_2384[eax*8]
 * 0007053B: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 0007053F: E8 18 E0 05 00           call    strcpy
 * 00070544: 89 34 24                 mov     [esp+1Ch+var_1C], esi
 * 00070547: 33 C0                    xor     eax, eax
 * 00070549: 8A 47 05                 mov     al, [edi+5]
 * 0007054C: 8B 04 C5 88 23 00 00     mov     eax, ds:dword_2388[eax*8]
 * 00070553: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 00070557: E8 00 E0 05 00           call    strcpy
 * 0007055C: E9 D7 03 00 00           jmp     def_70809; jumptable 00070809 default case
 * 00070561: 90 90 90                 align 4
 * 00070564: 89 1C 24                 mov     [esp+1Ch+var_1C], ebx
 * 00070567: 33 C0                    xor     eax, eax
 * 00070569: 8A 47 05                 mov     al, [edi+5]
 * 0007056C: 8B 04 C5 E4 25 00 00     mov     eax, ds:dword_25C4+20h[eax*8]
 * 00070573: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 00070577: E8 E0 DF 05 00           call    strcpy
 * 0007057C: 89 34 24                 mov     [esp+1Ch+var_1C], esi
 * 0007057F: 33 C0                    xor     eax, eax
 * 00070581: 8A 47 05                 mov     al, [edi+5]
 * 00070584: 8B 04 C5 E8 25 00 00     mov     eax, ds:dword_25C4+24h[eax*8]
 * 0007058B: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 0007058F: E8 C8 DF 05 00           call    strcpy
 * 00070594: E9 9F 03 00 00           jmp     def_70809; jumptable 00070809 default case
 * 00070599: 90 90 90                 align 4
 * 0007059C: 89 1C 24                 mov     [esp+1Ch+var_1C], ebx
 * 0007059F: 33 C0                    xor     eax, eax
 * 000705A1: 8A 47 05                 mov     al, [edi+5]
 * 000705A4: 8B 04 C5 F4 25 00 00     mov     eax, ds:dword_25C4+30h[eax*8]
 * 000705AB: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 000705AF: E8 A8 DF 05 00           call    strcpy
 * 000705B4: 89 34 24                 mov     [esp+1Ch+var_1C], esi
 * 000705B7: 33 C0                    xor     eax, eax
 * 000705B9: 8A 47 05                 mov     al, [edi+5]
 * 000705BC: 8B 04 C5 F8 25 00 00     mov     eax, ds:dword_25C4+34h[eax*8]
 * 000705C3: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 000705C7: E8 90 DF 05 00           call    strcpy
 * 000705CC: E9 67 03 00 00           jmp     def_70809; jumptable 00070809 default case
 * 000705D1: 90 90 90                 align 4
 * 000705D4: 89 1C 24                 mov     [esp+1Ch+var_1C], ebx
 * 000705D7: 33 C0                    xor     eax, eax
 * 000705D9: 8A 47 05                 mov     al, [edi+5]
 * 000705DC: 8B 04 C5 04 26 00 00     mov     eax, ds:dword_25C4+40h[eax*8]
 * 000705E3: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 000705E7: E8 70 DF 05 00           call    strcpy
 * 000705EC: 89 34 24                 mov     [esp+1Ch+var_1C], esi
 * 000705EF: 33 C0                    xor     eax, eax
 * 000705F1: 8A 47 05                 mov     al, [edi+5]
 * 000705F4: 8B 04 C5 08 26 00 00     mov     eax, ds:dword_25C4+44h[eax*8]
 * 000705FB: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 000705FF: E8 58 DF 05 00           call    strcpy
 * 00070604: E9 2F 03 00 00           jmp     def_70809; jumptable 00070809 default case
 * 00070609: 90 90 90                 align 4
 * 0007060C: 89 1C 24                 mov     [esp+1Ch+var_1C], ebx
 * 0007060F: 33 C0                    xor     eax, eax
 * 00070611: 8A 47 05                 mov     al, [edi+5]
 * 00070614: 8B 04 C5 14 26 00 00     mov     eax, ds:dword_25C4+50h[eax*8]
 * 0007061B: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 0007061F: E8 38 DF 05 00           call    strcpy
 * 00070624: 89 34 24                 mov     [esp+1Ch+var_1C], esi
 * 00070627: 33 C0                    xor     eax, eax
 * 00070629: 8A 47 05                 mov     al, [edi+5]
 * 0007062C: 8B 04 C5 18 26 00 00     mov     eax, ds:dword_25C4+54h[eax*8]
 * 00070633: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 00070637: E8 20 DF 05 00           call    strcpy
 * 0007063C: E9 F7 02 00 00           jmp     def_70809; jumptable 00070809 default case
 * 00070641: 90 90 90                 align 4
 * 00070644: 89 1C 24                 mov     [esp+1Ch+var_1C], ebx
 * 00070647: 33 C0                    xor     eax, eax
 * 00070649: 8A 47 05                 mov     al, [edi+5]
 * 0007064C: 8B 04 C5 24 26 00 00     mov     eax, ds:dword_25C4+60h[eax*8]
 * 00070653: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 00070657: E8 00 DF 05 00           call    strcpy
 * 0007065C: 89 34 24                 mov     [esp+1Ch+var_1C], esi
 * 0007065F: 33 C0                    xor     eax, eax
 * 00070661: 8A 47 05                 mov     al, [edi+5]
 * 00070664: 8B 04 C5 28 26 00 00     mov     eax, ds:dword_25C4+64h[eax*8]
 * 0007066B: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 0007066F: E8 E8 DE 05 00           call    strcpy
 * 00070674: E9 BF 02 00 00           jmp     def_70809; jumptable 00070809 default case
 * 00070679: 90 90 90                 align 4
 * 0007067C: 89 1C 24                 mov     [esp+1Ch+var_1C], ebx
 * 0007067F: 33 C0                    xor     eax, eax
 * 00070681: 8A 47 05                 mov     al, [edi+5]
 * 00070684: 8B 04 C5 34 26 00 00     mov     eax, ds:dword_25C4+70h[eax*8]
 * 0007068B: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 0007068F: E8 C8 DE 05 00           call    strcpy
 * 00070694: 89 34 24                 mov     [esp+1Ch+var_1C], esi
 * 00070697: 33 C0                    xor     eax, eax
 * 00070699: 8A 47 05                 mov     al, [edi+5]
 * 0007069C: 8B 04 C5 38 26 00 00     mov     eax, ds:dword_25C4+74h[eax*8]
 * 000706A3: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 000706A7: E8 B0 DE 05 00           call    strcpy
 * 000706AC: E9 87 02 00 00           jmp     def_70809; jumptable 00070809 default case
 * 000706B1: 90 90 90                 align 4
 * 000706B4: 89 1C 24                 mov     [esp+1Ch+var_1C], ebx
 * 000706B7: 33 C0                    xor     eax, eax
 * 000706B9: 8A 47 05                 mov     al, [edi+5]
 * 000706BC: 8B 04 C5 44 26 00 00     mov     eax, ds:dword_25C4+80h[eax*8]
 * 000706C3: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 000706C7: E8 90 DE 05 00           call    strcpy
 * 000706CC: 89 34 24                 mov     [esp+1Ch+var_1C], esi
 * 000706CF: 33 C0                    xor     eax, eax
 * 000706D1: 8A 47 05                 mov     al, [edi+5]
 * 000706D4: 8B 04 C5 48 26 00 00     mov     eax, ds:dword_25C4+84h[eax*8]
 * 000706DB: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 000706DF: E8 78 DE 05 00           call    strcpy
 * 000706E4: E9 4F 02 00 00           jmp     def_70809; jumptable 00070809 default case
 * 000706E9: 90 90 90                 align 4
 * 000706EC: 89 1C 24                 mov     [esp+1Ch+var_1C], ebx
 * 000706EF: 33 C0                    xor     eax, eax
 * 000706F1: 8A 47 05                 mov     al, [edi+5]
 * 000706F4: 8B 04 C5 54 26 00 00     mov     eax, ds:dword_25C4+90h[eax*8]
 * 000706FB: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 000706FF: E8 58 DE 05 00           call    strcpy
 * 00070704: 89 34 24                 mov     [esp+1Ch+var_1C], esi
 * 00070707: 33 C0                    xor     eax, eax
 * 00070709: 8A 47 05                 mov     al, [edi+5]
 * 0007070C: 8B 04 C5 58 26 00 00     mov     eax, ds:dword_25C4+94h[eax*8]
 * 00070713: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 00070717: E8 40 DE 05 00           call    strcpy
 * 0007071C: E9 17 02 00 00           jmp     def_70809; jumptable 00070809 default case
 * 00070721: 90 90 90                 align 4
 * 00070724: 89 1C 24                 mov     [esp+1Ch+var_1C], ebx
 * 00070727: 33 C0                    xor     eax, eax
 * 00070729: 8A 47 05                 mov     al, [edi+5]
 * 0007072C: 8B 04 C5 64 26 00 00     mov     eax, ds:dword_25C4+0A0h[eax*8]
 * 00070733: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 00070737: E8 20 DE 05 00           call    strcpy
 * 0007073C: 89 34 24                 mov     [esp+1Ch+var_1C], esi
 * 0007073F: 33 C0                    xor     eax, eax
 * 00070741: 8A 47 05                 mov     al, [edi+5]
 * 00070744: 8B 04 C5 68 26 00 00     mov     eax, ds:dword_25C4+0A4h[eax*8]
 * 0007074B: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 0007074F: E8 08 DE 05 00           call    strcpy
 * 00070754: E9 DF 01 00 00           jmp     def_70809; jumptable 00070809 default case
 * 00070759: 90 90 90                 align 4
 * 0007075C: 89 1C 24                 mov     [esp+1Ch+var_1C], ebx
 * 0007075F: 33 C0                    xor     eax, eax
 * 00070761: 8A 47 05                 mov     al, [edi+5]
 * 00070764: 8B 04 C5 74 26 00 00     mov     eax, ds:dword_25C4+0B0h[eax*8]
 * 0007076B: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 0007076F: E8 E8 DD 05 00           call    strcpy
 * 00070774: 89 34 24                 mov     [esp+1Ch+var_1C], esi
 * 00070777: 33 C0                    xor     eax, eax
 * 00070779: 8A 47 05                 mov     al, [edi+5]
 * 0007077C: 8B 04 C5 78 26 00 00     mov     eax, ds:dword_25C4+0B4h[eax*8]
 * 00070783: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 00070787: E8 D0 DD 05 00           call    strcpy
 * 0007078C: E9 A7 01 00 00           jmp     def_70809; jumptable 00070809 default case
 * 00070791: 90 90 90                 align 4
 * 00070794: 89 1C 24                 mov     [esp+1Ch+var_1C], ebx
 * 00070797: 33 C0                    xor     eax, eax
 * 00070799: 8A 47 05                 mov     al, [edi+5]
 * 0007079C: 8B 04 C5 84 26 00 00     mov     eax, ds:dword_25C4+0C0h[eax*8]
 * 000707A3: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 000707A7: E8 B0 DD 05 00           call    strcpy
 * 000707AC: 89 34 24                 mov     [esp+1Ch+var_1C], esi
 * 000707AF: 33 C0                    xor     eax, eax
 * 000707B1: 8A 47 05                 mov     al, [edi+5]
 * 000707B4: 8B 04 C5 88 26 00 00     mov     eax, ds:dword_25C4+0C4h[eax*8]
 * 000707BB: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 000707BF: E8 98 DD 05 00           call    strcpy
 * 000707C4: E9 6F 01 00 00           jmp     def_70809; jumptable 00070809 default case
 * 000707C9: 90 90 90                 align 4
 * 000707CC: 89 1C 24                 mov     [esp+1Ch+var_1C], ebx
 * 000707CF: 33 C0                    xor     eax, eax
 * 000707D1: 8A 47 05                 mov     al, [edi+5]
 * 000707D4: 8B 04 C5 94 26 00 00     mov     eax, ds:dword_25C4+0D0h[eax*8]
 * 000707DB: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 000707DF: E8 78 DD 05 00           call    strcpy
 * 000707E4: 89 34 24                 mov     [esp+1Ch+var_1C], esi
 * 000707E7: 33 C0                    xor     eax, eax
 * 000707E9: 8A 47 05                 mov     al, [edi+5]
 * 000707EC: 8B 04 C5 98 26 00 00     mov     eax, ds:dword_25C4+0D4h[eax*8]
 * 000707F3: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 000707F7: E8 60 DD 05 00           call    strcpy
 * 000707FC: E9 37 01 00 00           jmp     def_70809; jumptable 00070809 default case
 * 00070801: 90 90 90                 align 4
 * 00070804: 25 FF FF 00 00           and     eax, 0FFFFh
 * 00070809: 2E FF 24 85 14 08 E7 FF  jmp     dword ptr cs:[eax*4-18F7ECh]; switch jump
 * 00070811: 90 90 90                 align 4
 * 00070814: 44 F8 E6 FF 7C F8 E6 FF B4 F8 E6 FF EC F8 E6 FF 24 F9 E6 FF 5C F9 E6 FF 94 F9 E6 FF CC F9 E6 FF 04 FA E6 FF 3C FA E6 FF 74 FA E6 FF AC FA E6 FF E4 FA E6 FF 1C FB E6 FF 54 FB E6 FF 8C FB E6 FF C4 FB E6 FF FC FB E6 FF 34 FC E6 FF 6C FC E6 FF A4 FC E6 FF DC FC E6 FF 14 FD E6 FF 4C FD E6 FF 38 09 E7 FF 84 FD E6 FF BC FD E6 FF F4 FD E6 FF 64 FE E6 FF 9C FE E6 FF 74 01 E7 FF D4 FE E6 FF 0C FF E6 FF 44 FF E6 FF 7C FF E6 FF B4 FF E6 FF EC FF E6 FF 24 00 E7 FF 5C 00 E7 FF 94 00 E7 FF CC 00 E7 FF 04 01 E7 FF 3C 01 E7 FF AC 01 E7 FF E4 01 E7 FF 1C 02 E7 FF 54 02 E7 FF 8C 02 E7 FF C4 02 E7 FF FC 02 E7 FF 34 03 E7 FF 6C 03 E7 FF A4 03 E7 FF DC 03 E7 FF 14 04 E7 FF 4C 04 E7 FF 84 04 E7 FF BC 04 E7 FF F4 04 E7 FF 2C 05 E7 FF 64 05 E7 FF 9C 05 E7 FF D4 05 E7 FF 0C 06 E7 FF 44 06 E7 FF 7C 06 E7 FF B4 06 E7 FF EC 06 E7 FF 24 07 E7 FF 5C 07 E7 FF 94 07 E7 FF 2C FE E6 FF CC 07 E7 FF dd 0FFE6F844h, 0FFE6F87Ch, 0FFE6F8B4h, 0FFE6F8ECh, 0FFE6F924h
 * 00070938: 2B C0                    sub     eax, eax; jumptable 00070809 default case
 * 0007093A: 8B 5D EC                 mov     ebx, [ebp+var_14]
 * 0007093D: 8B 75 F0                 mov     esi, [ebp+var_10]
 * 00070940: 8B 7D F4                 mov     edi, [ebp+var_C]
 * 00070943: 89 EC                    mov     esp, ebp
 * 00070945: 5D                       pop     ebp
 * 00070946: C3                       retn
 * ========================================================================== */
/* Hex-Rays unavailable for 0x6F7DC (point_var_dispatch); see assembly above. */
void point_var_dispatch(void) { /* jump-table handler */ }


