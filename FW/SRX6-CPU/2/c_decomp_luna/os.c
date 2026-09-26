/*
 * Sony SRX-611 firmware - LUNA object-code interpreter/decoder - prefix 'os'
 * Source: ROM1-C.bin (80486 real mode, OS+/386 V2.0)
 * Functions: 2. The LUNA language compiles robot programs to object code;
 * this cluster decodes opcodes/tokens and formats operands.
 */

/* ============================================================================
 * os_C8FC4  @ 0xC8FC4   size=0x60B   callers=2
 * note: [SRX-611] pop_rank=787/1298, sites=0, callers=0, callees=5, size=0x60B
 * --- original assembly (address: bytes  mnemonic) ---------------------------
 * 000C8FC4: 55                       push    ebp
 * 000C8FC5: 89 E5                    mov     ebp, esp
 * 000C8FC7: 83 EC 4C                 sub     esp, 4Ch
 * 000C8FCA: 8D 45 F7                 lea     eax, [ebp+var_9]
 * 000C8FCD: 57                       push    edi
 * 000C8FCE: 56                       push    esi
 * 000C8FCF: 53                       push    ebx
 * 000C8FD0: 83 EC 14                 sub     esp, 14h
 * 000C8FD3: 89 04 24                 mov     [esp+6Ch+var_6C], eax
 * 000C8FD6: 8D 45 F4                 lea     eax, [ebp+var_C]
 * 000C8FD9: 89 44 24 04              mov     [esp+6Ch+var_68], eax
 * 000C8FDD: E8 FA 46 00 00           call    os_read_var
 * 000C8FE2: 66 89 45 BE              mov     [ebp+var_42], ax
 * 000C8FE6: 66 23 C0                 and     ax, ax
 * 000C8FE9: 74 09                    jz      short loc_C8FF4
 * 000C8FEB: E9 D2 05 00 00           jmp     loc_C95C2
 * 000C8FF0: 90 90 90 90              db 4 dup(90h)
 * 000C8FF4: 80 7D F7 06              cmp     [ebp+var_9], 6
 * 000C8FF8: 74 0A                    jz      short loc_C9004
 * 000C8FFA: 66 B8 78 50              mov     ax, 5078h
 * 000C8FFE: E9 BF 05 00 00           jmp     loc_C95C2
 * 000C9003: 90                       align 4
 * 000C9004: 66 81 7D F4 00 08        cmp     [ebp+var_C], 800h
 * 000C900A: 76 10                    jbe     short loc_C901C
 * 000C900C: 66 B8 78 50              mov     ax, 5078h
 * 000C9010: E9 AD 05 00 00           jmp     loc_C95C2
 * 000C9015: 90 90 90 90 90 90 90     db 7 dup(90h)
 * 000C901C: C7 04 24 00 00 00 00     mov     [esp+6Ch+var_6C], 0
 * 000C9023: C7 44 24 04 00 02 00 00  mov     [esp+6Ch+var_68], 200h
 * 000C902B: C7 44 24 08 01 00 00 00  mov     [esp+6Ch+var_64], 1
 * 000C9033: 2B FF                    sub     edi, edi
 * 000C9035: C7 44 24 0C 00 00 00 00  mov     [esp+6Ch+var_60], 0
 * 000C903D: 8D 45 F0                 lea     eax, [ebp+var_10]
 * 000C9040: 89 44 24 10              mov     [esp+6Ch+var_5C], eax
 * 000C9044: E8 7C 4F 00 00           call    os_syscall_90h_11h
 * 000C9049: 89 45 B8                 mov     [ebp+var_48], eax
 * 000C904C: 23 C0                    and     eax, eax
 * 000C904E: 74 24                    jz      short loc_C9074
 * 000C9050: 83 F8 22                 cmp     eax, 22h ; '"'
 * 000C9053: 75 0F                    jnz     short loc_C9064
 * 000C9055: 66 B8 DD 50              mov     ax, 50DDh
 * 000C9059: E9 64 05 00 00           jmp     loc_C95C2
 * 000C905E: 90 90 90 90 90 90        db 6 dup(90h)
 * 000C9064: 66 B8 DC 50              mov     ax, 50DCh
 * 000C9068: E9 55 05 00 00           jmp     loc_C95C2
 * 000C906D: 90 90 90 90 90 90 90     db 7 dup(90h)
 * 000C9074: 8B 75 F0                 mov     esi, [ebp+var_10]
 * 000C9077: 89 75 EC                 mov     [ebp+var_14], esi
 * 000C907A: C6 06 EB                 mov     byte ptr [esi], 0EBh
 * 000C907D: B9 70 00 00 00           mov     ecx, 70h ; 'p'
 * 000C9082: C6 46 01 3C              mov     byte ptr [esi+1], 3Ch ; '<'
 * 000C9086: C6 46 02 90              mov     byte ptr [esi+2], 90h
 * 000C908A: 8B 15 C0 F1 00 00        mov     edx, dword ptr ds:loc_F1C0
 * 000C9090: 57                       push    edi
 * 000C9091: 89 56 03                 mov     [esi+3], edx
 * 000C9094: 8B 15 C4 F1 00 00        mov     edx, dword ptr ds:loc_F1C4
 * 000C909A: 89 56 07                 mov     [esi+7], edx
 * 000C909D: 66 C7 46 0B 00 02        mov     word ptr [esi+0Bh], 200h
 * 000C90A3: C6 46 0D 01              mov     byte ptr [esi+0Dh], 1
 * 000C90A7: 66 C7 46 0E 01 00        mov     word ptr [esi+0Eh], 1
 * 000C90AD: C6 46 10 01              mov     byte ptr [esi+10h], 1
 * 000C90B1: 66 C7 46 11 F0 00        mov     word ptr [esi+11h], 0F0h
 * 000C90B7: 66 8B 45 F4              mov     ax, [ebp+var_C]
 * 000C90BB: D1 E0                    shl     eax, 1
 * 000C90BD: 89 7E 1C                 mov     [esi+1Ch], edi
 * 000C90C0: 89 7E 20                 mov     [esi+20h], edi
 * 000C90C3: 66 89 46 13              mov     [esi+13h], ax
 * 000C90C7: B8 90 90 90 90           mov     eax, 90909090h
 * 000C90CC: C6 46 15 F8              mov     byte ptr [esi+15h], 0F8h
 * 000C90D0: 66 C7 46 16 06 00        mov     word ptr [esi+16h], 6
 * 000C90D6: 66 C7 46 18 08 00        mov     word ptr [esi+18h], 8
 * 000C90DC: 66 C7 46 1A 02 00        mov     word ptr [esi+1Ah], 2
 * 000C90E2: C6 46 24 00              mov     byte ptr [esi+24h], 0
 * 000C90E6: C6 46 25 00              mov     byte ptr [esi+25h], 0
 * 000C90EA: C6 46 26 29              mov     byte ptr [esi+26h], 29h ; ')'
 * 000C90EE: C7 46 27 FC 1A 37 1F     mov     dword ptr [esi+27h], 1F371AFCh
 * 000C90F5: 8B 15 CC F1 00 00        mov     edx, dword ptr ds:loc_F1CC
 * 000C90FB: 89 56 2B                 mov     [esi+2Bh], edx
 * 000C90FE: 8B 15 D0 F1 00 00        mov     edx, dword ptr ds:loc_F1CC+4
 * 000C9104: 89 56 2F                 mov     [esi+2Fh], edx
 * 000C9107: 66 8B 15 D4 F1 00 00     mov     dx, word ptr ds:loc_F1D3+1
 * 000C910E: 66 89 56 33              mov     [esi+33h], dx
 * 000C9112: 8A 15 D6 F1 00 00        mov     dl, byte ptr ds:loc_F1D5+1
 * 000C9118: 88 56 35                 mov     [esi+35h], dl
 * 000C911B: 8B 15 D8 F1 00 00        mov     edx, dword ptr ds:loc_F1D7+1
 * 000C9121: 89 56 36                 mov     [esi+36h], edx
 * 000C9124: 8B 15 DC F1 00 00        mov     edx, dword ptr ds:loc_F1DC
 * 000C912A: 89 56 3A                 mov     [esi+3Ah], edx
 * 000C912D: 8D 7E 3E                 lea     edi, [esi+3Eh]
 * 000C9130: F3 AB                    rep stosd
 * 000C9132: 8B 45 F0                 mov     eax, [ebp+var_10]
 * 000C9135: 66 C7 80 FE 01 00 00 55 AA mov     word ptr [eax+1FEh], 0AA55h
 * 000C913E: 5F                       pop     edi
 * 000C913F: 66 89 7D E0              mov     [ebp+var_20], di
 * 000C9143: 66 C7 45 E2 02 00        mov     [ebp+var_1E], 2
 * 000C9149: C7 45 E4 FF FF FF FF     mov     [ebp+var_1C], 0FFFFFFFFh
 * 000C9150: C7 04 24 18 00 00 00     mov     [esp+6Ch+var_6C], 18h
 * 000C9157: 8D 5D E8                 lea     ebx, [ebp+var_18]
 * 000C915A: 89 5C 24 04              mov     [esp+6Ch+var_68], ebx
 * 000C915E: 89 7C 24 08              mov     [esp+6Ch+var_64], edi
 * 000C9162: C7 44 24 0C 08 00 00 00  mov     [esp+6Ch+var_60], 8
 * 000C916A: 8D 45 E0                 lea     eax, [ebp+var_20]
 * 000C916D: 89 44 24 10              mov     [esp+6Ch+var_5C], eax
 * 000C9171: E8 DE F6 FF FF           call    format_dispatch
 * 000C9176: 89 C6                    mov     esi, eax
 * 000C9178: 66 89 75 BE              mov     [ebp+var_42], si
 * 000C917C: 8B 45 F0                 mov     eax, [ebp+var_10]
 * 000C917F: 66 23 F6                 and     si, si
 * 000C9182: 74 18                    jz      short loc_C919C
 * 000C9184: 89 3C 24                 mov     [esp+6Ch+var_6C], edi
 * 000C9187: 89 44 24 04              mov     [esp+6Ch+var_68], eax
 * 000C918B: E8 58 4E 00 00           call    os_syscall_90h_12h
 * 000C9190: 89 F0                    mov     eax, esi
 * 000C9192: E9 2B 04 00 00           jmp     loc_C95C2
 * 000C9197: 90 90 90 90 90           db 5 dup(90h)
 * 000C919C: 89 7D D0                 mov     [ebp+var_30], edi
 * 000C919F: C7 45 D4 00 02 00 00     mov     [ebp+var_2C], 200h
 * 000C91A6: 66 C7 45 D8 08 00        mov     [ebp+var_28], 8
 * 000C91AC: C7 04 24 24 00 00 00     mov     [esp+6Ch+var_6C], 24h ; '$'
 * 000C91B3: 89 5C 24 04              mov     [esp+6Ch+var_68], ebx
 * 000C91B7: 89 44 24 08              mov     [esp+6Ch+var_64], eax
 * 000C91BB: C7 44 24 0C 0A 00 00 00  mov     [esp+6Ch+var_60], 0Ah
 * 000C91C3: 8D 45 D0                 lea     eax, [ebp+var_30]
 * 000C91C6: 89 44 24 10              mov     [esp+6Ch+var_5C], eax
 * 000C91CA: E8 85 F6 FF FF           call    format_dispatch
 * 000C91CF: 89 C6                    mov     esi, eax
 * 000C91D1: 66 89 75 BE              mov     [ebp+var_42], si
 * 000C91D5: 66 23 F6                 and     si, si
 * 000C91D8: 74 32                    jz      short loc_C920C
 * 000C91DA: 89 3C 24                 mov     [esp+6Ch+var_6C], edi
 * 000C91DD: 89 5C 24 04              mov     [esp+6Ch+var_68], ebx
 * 000C91E1: 89 7C 24 08              mov     [esp+6Ch+var_64], edi
 * 000C91E5: 89 7C 24 0C              mov     [esp+6Ch+var_60], edi
 * 000C91E9: 89 7C 24 10              mov     [esp+6Ch+var_5C], edi
 * 000C91ED: E8 62 F6 FF FF           call    format_dispatch
 * 000C91F2: 89 3C 24                 mov     [esp+6Ch+var_6C], edi
 * 000C91F5: 8B 45 F0                 mov     eax, [ebp+var_10]
 * 000C91F8: 89 44 24 04              mov     [esp+6Ch+var_68], eax
 * 000C91FC: E8 E7 4D 00 00           call    os_syscall_90h_12h
 * 000C9201: 89 F0                    mov     eax, esi
 * 000C9203: E9 BA 03 00 00           jmp     loc_C95C2
 * 000C9208: 90 90 90 90              db 4 dup(90h)
 * 000C920C: 8B 45 F0                 mov     eax, [ebp+var_10]
 * 000C920F: B9 03 00 00 00           mov     ecx, 3
 * 000C9214: C6 00 F8                 mov     byte ptr [eax], 0F8h
 * 000C9217: 8B 45 F0                 mov     eax, [ebp+var_10]
 * 000C921A: C6 40 01 FF              mov     byte ptr [eax+1], 0FFh
 * 000C921E: 8B 45 F0                 mov     eax, [ebp+var_10]
 * 000C9221: C6 40 02 FF              mov     byte ptr [eax+2], 0FFh
 * 000C9225: C7 45 CC 03 00 00 00     mov     [ebp+var_34], 3
 * 000C922C: 8B 45 F0                 mov     eax, [ebp+var_10]
 * 000C922F: 81 F9 00 02 00 00        cmp     ecx, 200h
 * 000C9235: 7D 0D                    jge     short loc_C9244
 * 000C9237: C6 04 08 00              mov     byte ptr [eax+ecx], 0
 * 000C923B: 41                       inc     ecx
 * 000C923C: EB EE                    jmp     short loc_C922C
 * 000C923E: 90 90 90 90 90 90        db 6 dup(90h)
 * 000C9244: C7 45 D0 00 02 00 00     mov     [ebp+var_30], 200h
 * 000C924B: 89 4D CC                 mov     [ebp+var_34], ecx
 * 000C924E: C7 45 D4 00 02 00 00     mov     [ebp+var_2C], 200h
 * 000C9255: 66 C7 45 D8 08 00        mov     [ebp+var_28], 8
 * 000C925B: C7 04 24 24 00 00 00     mov     [esp+6Ch+var_6C], 24h ; '$'
 * 000C9262: 89 5C 24 04              mov     [esp+6Ch+var_68], ebx
 * 000C9266: 89 44 24 08              mov     [esp+6Ch+var_64], eax
 * 000C926A: C7 44 24 0C 0A 00 00 00  mov     [esp+6Ch+var_60], 0Ah
 * 000C9272: 8D 45 D0                 lea     eax, [ebp+var_30]
 * 000C9275: 89 44 24 10              mov     [esp+6Ch+var_5C], eax
 * 000C9279: E8 D6 F5 FF FF           call    format_dispatch
 * 000C927E: 89 45 FC                 mov     [ebp+var_4], eax
 * 000C9281: 66 89 45 BE              mov     [ebp+var_42], ax
 * 000C9285: 66 23 C0                 and     ax, ax
 * 000C9288: 74 32                    jz      short loc_C92BC
 * 000C928A: 89 3C 24                 mov     [esp+6Ch+var_6C], edi
 * 000C928D: 89 5C 24 04              mov     [esp+6Ch+var_68], ebx
 * 000C9291: 89 7C 24 08              mov     [esp+6Ch+var_64], edi
 * 000C9295: 89 7C 24 0C              mov     [esp+6Ch+var_60], edi
 * 000C9299: 89 7C 24 10              mov     [esp+6Ch+var_5C], edi
 * 000C929D: E8 B2 F5 FF FF           call    format_dispatch
 * 000C92A2: 89 3C 24                 mov     [esp+6Ch+var_6C], edi
 * 000C92A5: 8B 45 F0                 mov     eax, [ebp+var_10]
 * 000C92A8: 89 44 24 04              mov     [esp+6Ch+var_68], eax
 * 000C92AC: E8 37 4D 00 00           call    os_syscall_90h_12h
 * 000C92B1: 8B 45 FC                 mov     eax, [ebp+var_4]
 * 000C92B4: E9 09 03 00 00           jmp     loc_C95C2
 * 000C92B9: 90 90 90                 align 4
 * 000C92BC: 8B 45 F0                 mov     eax, [ebp+var_10]
 * 000C92BF: BE 01 00 00 00           mov     esi, 1
 * 000C92C4: C6 00 00                 mov     byte ptr [eax], 0
 * 000C92C7: 8B 45 F0                 mov     eax, [ebp+var_10]
 * 000C92CA: C6 40 01 00              mov     byte ptr [eax+1], 0
 * 000C92CE: 8B 45 F0                 mov     eax, [ebp+var_10]
 * 000C92D1: C6 40 02 00              mov     byte ptr [eax+2], 0
 * 000C92D5: C7 45 CC 01 00 00 00     mov     [ebp+var_34], 1
 * 000C92DC: 8B 4D FC                 mov     ecx, [ebp+var_4]
 * 000C92DF: 8B 45 F0                 mov     eax, [ebp+var_10]
 * 000C92E2: 83 FE 06                 cmp     esi, 6
 * 000C92E5: 0F 8D 81 00 00 00        jge     loc_C936C
 * 000C92EB: 81 45 D0 00 02 00 00     add     [ebp+var_30], 200h
 * 000C92F2: C7 45 D4 00 02 00 00     mov     [ebp+var_2C], 200h
 * 000C92F9: 66 C7 45 D8 08 00        mov     [ebp+var_28], 8
 * 000C92FF: C7 04 24 24 00 00 00     mov     [esp+6Ch+var_6C], 24h ; '$'
 * 000C9306: 89 5C 24 04              mov     [esp+6Ch+var_68], ebx
 * 000C930A: 89 44 24 08              mov     [esp+6Ch+var_64], eax
 * 000C930E: C7 44 24 0C 0A 00 00 00  mov     [esp+6Ch+var_60], 0Ah
 * 000C9316: 8D 45 D0                 lea     eax, [ebp+var_30]
 * 000C9319: 89 44 24 10              mov     [esp+6Ch+var_5C], eax
 * 000C931D: E8 32 F5 FF FF           call    format_dispatch
 * 000C9322: 66 23 C0                 and     ax, ax
 * 000C9325: 74 3D                    jz      short loc_C9364
 * 000C9327: 89 45 FC                 mov     [ebp+var_4], eax
 * 000C932A: 66 89 45 BE              mov     [ebp+var_42], ax
 * 000C932E: 89 75 CC                 mov     [ebp+var_34], esi
 * 000C9331: 89 3C 24                 mov     [esp+6Ch+var_6C], edi
 * 000C9334: 89 5C 24 04              mov     [esp+6Ch+var_68], ebx
 * 000C9338: 89 7C 24 08              mov     [esp+6Ch+var_64], edi
 * 000C933C: 89 7C 24 0C              mov     [esp+6Ch+var_60], edi
 * 000C9340: 89 7C 24 10              mov     [esp+6Ch+var_5C], edi
 * 000C9344: E8 0B F5 FF FF           call    format_dispatch
 * 000C9349: 89 3C 24                 mov     [esp+6Ch+var_6C], edi
 * 000C934C: 8B 45 F0                 mov     eax, [ebp+var_10]
 * 000C934F: 89 44 24 04              mov     [esp+6Ch+var_68], eax
 * 000C9353: E8 90 4C 00 00           call    os_syscall_90h_12h
 * 000C9358: 8B 45 FC                 mov     eax, [ebp+var_4]
 * 000C935B: E9 62 02 00 00           jmp     loc_C95C2
 * 000C9360: 90 90 90 90              db 4 dup(90h)
 * 000C9364: 46                       inc     esi
 * 000C9365: 89 C1                    mov     ecx, eax
 * 000C9367: E9 73 FF FF FF           jmp     loc_C92DF
 * 000C936C: 8B 15 CC F1 00 00        mov     edx, dword ptr ds:loc_F1CC
 * 000C9372: 66 89 4D BE              mov     [ebp+var_42], cx
 * 000C9376: 89 75 CC                 mov     [ebp+var_34], esi
 * 000C9379: B9 0C 00 00 00           mov     ecx, 0Ch
 * 000C937E: 89 10                    mov     [eax], edx
 * 000C9380: 8B 15 D0 F1 00 00        mov     edx, dword ptr ds:loc_F1CC+4
 * 000C9386: 89 50 04                 mov     [eax+4], edx
 * 000C9389: 66 8B 15 D4 F1 00 00     mov     dx, word ptr ds:loc_F1D3+1
 * 000C9390: 66 89 50 08              mov     [eax+8], dx
 * 000C9394: 8A 15 D6 F1 00 00        mov     dl, byte ptr ds:loc_F1D5+1
 * 000C939A: 88 50 0A                 mov     [eax+0Ah], dl
 * 000C939D: 8B 45 F0                 mov     eax, [ebp+var_10]
 * 000C93A0: C6 40 0B 28              mov     byte ptr [eax+0Bh], 28h ; '('
 * 000C93A4: C7 45 CC 0C 00 00 00     mov     [ebp+var_34], 0Ch
 * 000C93AB: 83 F9 16                 cmp     ecx, 16h
 * 000C93AE: 7D 0C                    jge     short loc_C93BC
 * 000C93B0: 8B 45 F0                 mov     eax, [ebp+var_10]
 * 000C93B3: C6 04 08 00              mov     byte ptr [eax+ecx], 0
 * 000C93B7: 41                       inc     ecx
 * 000C93B8: EB F1                    jmp     short loc_C93AB
 * 000C93BA: 90 90                    align 4
 * 000C93BC: 89 4D CC                 mov     [ebp+var_34], ecx
 * 000C93BF: 8D 45 C0                 lea     eax, [ebp+var_40]
 * 000C93C2: 89 04 24                 mov     [esp+6Ch+var_6C], eax
 * 000C93C5: E8 2E 6C F6 FF           call    pccard_2FFF8
 * 000C93CA: 33 C9                    xor     ecx, ecx
 * 000C93CC: 8A 4D C4                 mov     cl, [ebp+var_3C]
 * 000C93CF: C1 E1 0B                 shl     ecx, 0Bh
 * 000C93D2: 8B 55 F0                 mov     edx, [ebp+var_10]
 * 000C93D5: 33 C0                    xor     eax, eax
 * 000C93D7: 66 89 4A 16              mov     [edx+16h], cx
 * 000C93DB: 8A 45 C5                 mov     al, [ebp+var_3B]
 * 000C93DE: C1 E0 05                 shl     eax, 5
 * 000C93E1: 66 0B C1                 or      ax, cx
 * 000C93E4: 66 89 42 16              mov     [edx+16h], ax
 * 000C93E8: 8A 4D C6                 mov     cl, [ebp+var_3A]
 * 000C93EB: D0 E9                    shr     cl, 1
 * 000C93ED: 66 81 E1 FF 00           and     cx, 0FFh
 * 000C93F2: 66 0B C8                 or      cx, ax
 * 000C93F5: 66 89 4A 16              mov     [edx+16h], cx
 * 000C93F9: 66 8B 4D C0              mov     cx, [ebp+var_40]
 * 000C93FD: 66 81 C1 44 F8           add     cx, 0F844h
 * 000C9402: C1 E1 09                 shl     ecx, 9
 * 000C9405: 33 C0                    xor     eax, eax
 * 000C9407: 66 89 4A 18              mov     [edx+18h], cx
 * 000C940B: 8A 45 C2                 mov     al, [ebp+var_3E]
 * 000C940E: C1 E0 05                 shl     eax, 5
 * 000C9411: 66 0B C1                 or      ax, cx
 * 000C9414: 66 89 42 18              mov     [edx+18h], ax
 * 000C9418: 33 C9                    xor     ecx, ecx
 * 000C941A: 8A 4D C3                 mov     cl, [ebp+var_3D]
 * 000C941D: 66 0B C8                 or      cx, ax
 * 000C9420: 66 89 4A 18              mov     [edx+18h], cx
 * 000C9424: C7 45 CC 1A 00 00 00     mov     [ebp+var_34], 1Ah
 * 000C942B: B8 1A 00 00 00           mov     eax, 1Ah
 * 000C9430: 83 F8 20                 cmp     eax, 20h ; ' '
 * 000C9433: 7D 0F                    jge     short loc_C9444
 * 000C9435: C6 04 02 00              mov     byte ptr [edx+eax], 0
 * 000C9439: 40                       inc     eax
 * 000C943A: 8B 55 F0                 mov     edx, [ebp+var_10]
 * 000C943D: EB F1                    jmp     short loc_C9430
 * 000C943F: 90 90 90 90 90           db 5 dup(90h)
 * 000C9444: 81 45 D0 00 02 00 00     add     [ebp+var_30], 200h
 * 000C944B: 89 45 CC                 mov     [ebp+var_34], eax
 * 000C944E: C7 45 D4 00 02 00 00     mov     [ebp+var_2C], 200h
 * 000C9455: 66 C7 45 D8 08 00        mov     [ebp+var_28], 8
 * 000C945B: C7 04 24 24 00 00 00     mov     [esp+6Ch+var_6C], 24h ; '$'
 * 000C9462: 89 5C 24 04              mov     [esp+6Ch+var_68], ebx
 * 000C9466: 89 54 24 08              mov     [esp+6Ch+var_64], edx
 * 000C946A: C7 44 24 0C 0A 00 00 00  mov     [esp+6Ch+var_60], 0Ah
 * 000C9472: 8D 45 D0                 lea     eax, [ebp+var_30]
 * 000C9475: 89 44 24 10              mov     [esp+6Ch+var_5C], eax
 * 000C9479: E8 D6 F3 FF FF           call    format_dispatch
 * 000C947E: 89 C6                    mov     esi, eax
 * 000C9480: 66 89 75 BE              mov     [ebp+var_42], si
 * 000C9484: 66 23 F6                 and     si, si
 * 000C9487: 74 33                    jz      short loc_C94BC
 * 000C9489: 89 3C 24                 mov     [esp+6Ch+var_6C], edi
 * 000C948C: 89 5C 24 04              mov     [esp+6Ch+var_68], ebx
 * 000C9490: 89 7C 24 08              mov     [esp+6Ch+var_64], edi
 * 000C9494: 89 7C 24 0C              mov     [esp+6Ch+var_60], edi
 * 000C9498: 89 7C 24 10              mov     [esp+6Ch+var_5C], edi
 * 000C949C: E8 B3 F3 FF FF           call    format_dispatch
 * 000C94A1: 89 3C 24                 mov     [esp+6Ch+var_6C], edi
 * 000C94A4: 8B 45 F0                 mov     eax, [ebp+var_10]
 * 000C94A7: 89 44 24 04              mov     [esp+6Ch+var_68], eax
 * 000C94AB: E8 38 4B 00 00           call    os_syscall_90h_12h
 * 000C94B0: 89 F0                    mov     eax, esi
 * 000C94B2: E9 0B 01 00 00           jmp     loc_C95C2
 * 000C94B7: 90 90 90 90 90           db 5 dup(90h)
 * 000C94BC: 89 7D CC                 mov     [ebp+var_34], edi
 * 000C94BF: 89 F9                    mov     ecx, edi
 * 000C94C1: 83 F9 20                 cmp     ecx, 20h ; ' '
 * 000C94C4: 7D 0E                    jge     short loc_C94D4
 * 000C94C6: 8B 45 F0                 mov     eax, [ebp+var_10]
 * 000C94C9: C6 04 08 00              mov     byte ptr [eax+ecx], 0
 * 000C94CD: 41                       inc     ecx
 * 000C94CE: EB F1                    jmp     short loc_C94C1
 * 000C94D0: 90 90 90 90              db 4 dup(90h)
 * 000C94D4: 89 4D CC                 mov     [ebp+var_34], ecx
 * 000C94D7: C7 45 CC 01 00 00 00     mov     [ebp+var_34], 1
 * 000C94DE: BE 01 00 00 00           mov     esi, 1
 * 000C94E3: 66 8B 45 BE              mov     ax, [ebp+var_42]
 * 000C94E7: 83 FE 0F                 cmp     esi, 0Fh
 * 000C94EA: 0F 8D 84 00 00 00        jge     loc_C9574
 * 000C94F0: 81 45 D0 00 02 00 00     add     [ebp+var_30], 200h
 * 000C94F7: C7 45 D4 00 02 00 00     mov     [ebp+var_2C], 200h
 * 000C94FE: 66 C7 45 D8 08 00        mov     [ebp+var_28], 8
 * 000C9504: C7 04 24 24 00 00 00     mov     [esp+6Ch+var_6C], 24h ; '$'
 * 000C950B: 89 5C 24 04              mov     [esp+6Ch+var_68], ebx
 * 000C950F: 8B 45 F0                 mov     eax, [ebp+var_10]
 * 000C9512: 89 44 24 08              mov     [esp+6Ch+var_64], eax
 * 000C9516: C7 44 24 0C 0A 00 00 00  mov     [esp+6Ch+var_60], 0Ah
 * 000C951E: 8D 45 D0                 lea     eax, [ebp+var_30]
 * 000C9521: 89 44 24 10              mov     [esp+6Ch+var_5C], eax
 * 000C9525: E8 2A F3 FF FF           call    format_dispatch
 * 000C952A: 66 23 C0                 and     ax, ax
 * 000C952D: 74 3D                    jz      short loc_C956C
 * 000C952F: 89 45 F8                 mov     [ebp+var_8], eax
 * 000C9532: 66 89 45 BE              mov     [ebp+var_42], ax
 * 000C9536: 89 75 CC                 mov     [ebp+var_34], esi
 * 000C9539: 89 3C 24                 mov     [esp+6Ch+var_6C], edi
 * 000C953C: 89 5C 24 04              mov     [esp+6Ch+var_68], ebx
 * 000C9540: 89 7C 24 08              mov     [esp+6Ch+var_64], edi
 * 000C9544: 89 7C 24 0C              mov     [esp+6Ch+var_60], edi
 * 000C9548: 89 7C 24 10              mov     [esp+6Ch+var_5C], edi
 * 000C954C: E8 03 F3 FF FF           call    format_dispatch
 * 000C9551: 89 3C 24                 mov     [esp+6Ch+var_6C], edi
 * 000C9554: 8B 45 F0                 mov     eax, [ebp+var_10]
 * 000C9557: 89 44 24 04              mov     [esp+6Ch+var_68], eax
 * 000C955B: E8 88 4A 00 00           call    os_syscall_90h_12h
 * 000C9560: 8B 45 F8                 mov     eax, [ebp+var_8]
 * 000C9563: EB 5D                    jmp     short loc_C95C2
 * 000C9565: 90 90 90 90 90 90 90     db 7 dup(90h)
 * 000C956C: 46                       inc     esi
 * 000C956D: E9 75 FF FF FF           jmp     loc_C94E7
 * 000C9572: 90 90                    align 4
 * 000C9574: 66 89 45 BE              mov     [ebp+var_42], ax
 * 000C9578: 89 75 CC                 mov     [ebp+var_34], esi
 * 000C957B: 89 3C 24                 mov     [esp+6Ch+var_6C], edi
 * 000C957E: 89 5C 24 04              mov     [esp+6Ch+var_68], ebx
 * 000C9582: 89 7C 24 08              mov     [esp+6Ch+var_64], edi
 * 000C9586: 89 7C 24 0C              mov     [esp+6Ch+var_60], edi
 * 000C958A: 89 7C 24 10              mov     [esp+6Ch+var_5C], edi
 * 000C958E: E8 C1 F2 FF FF           call    format_dispatch
 * 000C9593: 89 C6                    mov     esi, eax
 * 000C9595: 66 89 75 BE              mov     [ebp+var_42], si
 * 000C9599: 8B 45 F0                 mov     eax, [ebp+var_10]
 * 000C959C: 66 23 F6                 and     si, si
 * 000C959F: 74 13                    jz      short loc_C95B4
 * 000C95A1: 89 3C 24                 mov     [esp+6Ch+var_6C], edi
 * 000C95A4: 89 44 24 04              mov     [esp+6Ch+var_68], eax
 * 000C95A8: E8 3B 4A 00 00           call    os_syscall_90h_12h
 * 000C95AD: 89 F0                    mov     eax, esi
 * 000C95AF: EB 11                    jmp     short loc_C95C2
 * 000C95B1: 90 90 90                 align 4
 * 000C95B4: 89 3C 24                 mov     [esp+6Ch+var_6C], edi
 * 000C95B7: 89 44 24 04              mov     [esp+6Ch+var_68], eax
 * 000C95BB: E8 28 4A 00 00           call    os_syscall_90h_12h
 * 000C95C0: 2B C0                    sub     eax, eax
 * 000C95C2: 8B 5D A8                 mov     ebx, [ebp+var_58]
 * 000C95C5: 8B 75 AC                 mov     esi, [ebp+var_54]
 * 000C95C8: 8B 7D B0                 mov     edi, [ebp+var_50]
 * 000C95CB: 89 EC                    mov     esp, ebp
 * 000C95CD: 5D                       pop     ebp
 * 000C95CE: C3                       retn
 * ========================================================================== */
// [SRX-611] pop_rank=787/1298, sites=0, callers=0, callees=5, size=0x60B
__int16 __usercall os_C8FC4@<ax>(int a1@<esi>)
{
  __int16 result; // ax
  int v2; // eax
  int v3; // esi
  __int16 v4; // ax
  __int16 v5; // si
  __int16 v6; // si
  int v7; // ecx
  int v8; // eax
  int v9; // esi
  int v10; // eax
  int v11; // eax
  int v12; // ecx
  __int16 v13; // cx
  int v14; // edx
  __int16 v15; // ax
  __int16 v16; // cx
  __int16 v17; // ax
  int i; // eax
  __int16 v19; // si
  int j; // ecx
  int k; // esi
  int v22; // eax
  __int16 v23; // si
  __int16 v24; // [esp+2Ch] [ebp-40h] BYREF
  unsigned __int8 v25; // [esp+2Eh] [ebp-3Eh]
  unsigned __int8 v26; // [esp+2Fh] [ebp-3Dh]
  unsigned __int8 v27; // [esp+30h] [ebp-3Ch]
  unsigned __int8 v28; // [esp+31h] [ebp-3Bh]
  unsigned __int8 v29; // [esp+32h] [ebp-3Ah]
  int v30; // [esp+38h] [ebp-34h]
  int v31; // [esp+3Ch] [ebp-30h] BYREF
  int v32; // [esp+40h] [ebp-2Ch]
  __int16 v33; // [esp+44h] [ebp-28h]
  _WORD v34[2]; // [esp+4Ch] [ebp-20h] BYREF
  int v35; // [esp+50h] [ebp-1Ch]
  _BYTE v36[4]; // [esp+54h] [ebp-18h] BYREF
  int v37; // [esp+58h] [ebp-14h]
  int v38; // [esp+5Ch] [ebp-10h] BYREF
  unsigned __int16 v39; // [esp+60h] [ebp-Ch] BYREF
  char v40; // [esp+63h] [ebp-9h] BYREF
  int v41; // [esp+64h] [ebp-8h]
  int v42; // [esp+68h] [ebp-4h]

  result = os_read_var(&v40, &v39);
  if ( !result )
  {
    if ( v40 == 6 )
    {
      if ( v39 <= 0x800u )
      {
        v2 = os_syscall_90h_11h(a1, 0, 512, 1, 0, &v38);
        if ( v2 )
        {
          if ( v2 == 34 )
            return 20701;
          else
            return 20700;
        }
        else
        {
          v3 = v38;
          v37 = v38;
          *(_BYTE *)v38 = -21;
          *(_BYTE *)(v3 + 1) = 60;
          *(_BYTE *)(v3 + 2) = -112;
          *(_DWORD *)(v3 + 3) = loc_F1C0;
          *(_DWORD *)(v3 + 7) = loc_F1C4;
          *(_WORD *)(v3 + 11) = 512;
          *(_BYTE *)(v3 + 13) = 1;
          *(_WORD *)(v3 + 14) = 1;
          *(_BYTE *)(v3 + 16) = 1;
          *(_WORD *)(v3 + 17) = 240;
          v4 = 2 * v39;
          *(_DWORD *)(v3 + 28) = 0;
          *(_DWORD *)(v3 + 32) = 0;
          *(_WORD *)(v3 + 19) = v4;
          *(_BYTE *)(v3 + 21) = -8;
          *(_WORD *)(v3 + 22) = 6;
          *(_WORD *)(v3 + 24) = 8;
          *(_WORD *)(v3 + 26) = 2;
          *(_BYTE *)(v3 + 36) = 0;
          *(_BYTE *)(v3 + 37) = 0;
          *(_BYTE *)(v3 + 38) = 41;
          *(_DWORD *)(v3 + 39) = 523705084;
          *(_DWORD *)(v3 + 43) = loc_F1CC;
          *(_DWORD *)(v3 + 47) = *(&loc_F1CC + 1);
          *(_WORD *)(v3 + 51) = *(_WORD *)((char *)&loc_F1D3 + 1);
          *(_BYTE *)(v3 + 53) = *(&loc_F1D5 + 1);
          *(_DWORD *)(v3 + 54) = *(_DWORD *)((char *)&loc_F1D7 + 1);
          *(_DWORD *)(v3 + 58) = loc_F1DC;
          memset((void *)(v3 + 62), 0x90u, 0x1C0u);
          *(_WORD *)(v38 + 510) = -21931;
          v34[0] = 0;
          v34[1] = 2;
          v35 = -1;
          v5 = format_dispatch(24, (int)v36, 0, 8, (int)v34);
          if ( v5 )
          {
            os_syscall_90h_12h();
            return v5;
          }
          else
          {
            v31 = 0;
            v32 = 512;
            v33 = 8;
            v6 = format_dispatch(36, (int)v36, v38, 10, (int)&v31);
            if ( v6 )
            {
              format_dispatch(0, (int)v36, 0, 0, 0);
              os_syscall_90h_12h();
              return v6;
            }
            else
            {
              v7 = 3;
              *(_BYTE *)v38 = -8;
              *(_BYTE *)(v38 + 1) = -1;
              *(_BYTE *)(v38 + 2) = -1;
              v30 = 3;
              while ( v7 < 512 )
                *(_BYTE *)(v38 + v7++) = 0;
              v31 = 512;
              v30 = v7;
              v32 = 512;
              v33 = 8;
              LOWORD(v8) = format_dispatch(36, (int)v36, v38, 10, (int)&v31);
              v42 = v8;
              if ( (_WORD)v8 )
              {
                format_dispatch(0, (int)v36, 0, 0, 0);
                os_syscall_90h_12h();
                return v42;
              }
              else
              {
                v9 = 1;
                *(_BYTE *)v38 = 0;
                *(_BYTE *)(v38 + 1) = 0;
                *(_BYTE *)(v38 + 2) = 0;
                v30 = 1;
                while ( 1 )
                {
                  v10 = v38;
                  if ( v9 >= 6 )
                    break;
                  v31 += 512;
                  v32 = 512;
                  v33 = 8;
                  LOWORD(v11) = format_dispatch(36, (int)v36, v38, 10, (int)&v31);
                  if ( (_WORD)v11 )
                  {
                    v42 = v11;
                    v30 = v9;
                    format_dispatch(0, (int)v36, 0, 0, 0);
                    os_syscall_90h_12h();
                    return v42;
                  }
                  ++v9;
                }
                v12 = 12;
                *(_DWORD *)v38 = loc_F1CC;
                *(_DWORD *)(v10 + 4) = *(&loc_F1CC + 1);
                *(_WORD *)(v10 + 8) = *(_WORD *)((char *)&loc_F1D3 + 1);
                *(_BYTE *)(v10 + 10) = *(&loc_F1D5 + 1);
                *(_BYTE *)(v38 + 11) = 40;
                v30 = 12;
                while ( v12 < 22 )
                  *(_BYTE *)(v38 + v12++) = 0;
                v30 = v12;
                pccard_2FFF8(&v24);
                v13 = v27 << 11;
                v14 = v38;
                *(_WORD *)(v38 + 22) = v13;
                v15 = v13 | (32 * v28);
                *(_WORD *)(v14 + 22) = v15;
                *(_WORD *)(v14 + 22) = v15 | (v29 >> 1);
                v16 = (v24 - 1980) << 9;
                *(_WORD *)(v14 + 24) = v16;
                v17 = v16 | (32 * v25);
                *(_WORD *)(v14 + 24) = v17;
                *(_WORD *)(v14 + 24) = v17 | v26;
                v30 = 26;
                for ( i = 26; i < 32; ++i )
                {
                  *(_BYTE *)(v14 + i) = 0;
                  v14 = v38;
                }
                v31 += 512;
                v30 = i;
                v32 = 512;
                v33 = 8;
                v19 = format_dispatch(36, (int)v36, v14, 10, (int)&v31);
                if ( v19 )
                {
                  format_dispatch(0, (int)v36, 0, 0, 0);
                  os_syscall_90h_12h();
                  return v19;
                }
                else
                {
                  v30 = 0;
                  for ( j = 0; j < 32; ++j )
                    *(_BYTE *)(v38 + j) = 0;
                  v30 = 1;
                  for ( k = 1; k < 15; ++k )
                  {
                    v31 += 512;
                    v32 = 512;
                    v33 = 8;
                    LOWORD(v22) = format_dispatch(36, (int)v36, v38, 10, (int)&v31);
                    if ( (_WORD)v22 )
                    {
                      v41 = v22;
                      v30 = k;
                      format_dispatch(0, (int)v36, 0, 0, 0);
                      os_syscall_90h_12h();
                      return v41;
                    }
                  }
                  v30 = k;
                  v23 = format_dispatch(0, (int)v36, 0, 0, 0);
                  os_syscall_90h_12h();
                  if ( v23 )
                    return v23;
                  else
                    return 0;
                }
              }
            }
          }
        }
      }
      else
      {
        return 20600;
      }
    }
    else
    {
      return 20600;
    }
  }
  return result;
}


/* ============================================================================
 * os_C87FC  @ 0xC87FC   size=0x52   callers=1
 * note: [SRX-611] pop_rank=1218/1298, sites=0, callers=0, callees=1, size=0x52
 * --- original assembly (address: bytes  mnemonic) ---------------------------
 * 000C87FC: 55                       push    ebp
 * 000C87FD: 8B 15 B8 F1 00 00        mov     edx, dword ptr ds:loc_F1B8
 * 000C8803: 89 E5                    mov     ebp, esp
 * 000C8805: 83 EC 1C                 sub     esp, 1Ch
 * 000C8808: 89 55 F8                 mov     [ebp+var_8], edx
 * 000C880B: 8A 15 BC F1 00 00        mov     dl, byte ptr ds:loc_F1BA+2
 * 000C8811: 88 55 FC                 mov     [ebp+var_4], dl
 * 000C8814: 8D 45 F8                 lea     eax, [ebp+var_8]
 * 000C8817: 89 04 24                 mov     [esp+1Ch+var_1C], eax
 * 000C881A: C7 44 24 04 01 00 00 00  mov     [esp+1Ch+var_18], 1
 * 000C8822: C7 44 24 08 00 00 00 00  mov     [esp+1Ch+var_14], 0
 * 000C882A: C7 44 24 0C F4 75 00 00  mov     [esp+1Ch+var_10], 75F4h
 * 000C8832: E8 A4 5A 00 00           call    os_syscall_90h_33h
 * 000C8837: 23 C0                    and     eax, eax
 * 000C8839: 74 09                    jz      short loc_C8844
 * 000C883B: 66 B8 DC 50              mov     ax, 50DCh
 * 000C883F: EB 09                    jmp     short loc_C884A
 * 000C8841: 90 90 90                 align 4
 * 000C8844: B0 01                    mov     al, 1
 * 000C8846: E6 4C                    out     4Ch, al
 * 000C8848: 2B C0                    sub     eax, eax
 * 000C884A: 89 EC                    mov     esp, ebp
 * 000C884C: 5D                       pop     ebp
 * 000C884D: C3                       retn
 * ========================================================================== */
// [SRX-611] pop_rank=1218/1298, sites=0, callers=0, callees=1, size=0x52
__int16 os_C87FC()
{
  int v1; // [esp+14h] [ebp-8h] BYREF
  char v2; // [esp+18h] [ebp-4h]

  v1 = loc_F1B8;
  v2 = *(&loc_F1BA + 2);
  if ( os_syscall_90h_33h(&v1, 1, 0, 30196) )
    return 20700;
  __outbyte(0x4Cu, 1u);
  return 0;
}


