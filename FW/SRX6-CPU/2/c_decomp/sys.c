/*
 * Sony SRX-611 firmware - C equivalents (Hex-Rays) - prefix 'sys'
 * Source image: ROM1-C.bin (80486 real mode, OS+/386 V2.0)
 * Generated from IDA database ROM1-C.bin.i64
 * Functions in this file: 1
 */

/* ============================================================================
 * sys_req_27h  @ 0xBE214   size=0x5E   pop_rank=15/1298
 * calls=39 callers=10
 * note: Build request block and call os_syscall_90h_27h | [SRX-611] pop_rank=15/1298, sites=39, callers=10, callees=1, size=0x5E
 * --- original assembly (address: bytes  mnemonic) ---------------------------
 * 000BE214: 55                       push    ebp
 * 000BE215: 89 E5                    mov     ebp, esp
 * 000BE217: 83 EC 1C                 sub     esp, 1Ch
 * 000BE21A: 66 8B 4D 10              mov     cx, [ebp+arg_8]
 * 000BE21E: 66 83 F9 64              cmp     cx, 64h ; 'd'
 * 000BE222: 73 07                    jnb     short loc_BE22B
 * 000BE224: C6 05 D8 75 00 00 01     mov     byte ptr ds:loc_75D6+2, 1
 * 000BE22B: 33 C0                    xor     eax, eax
 * 000BE22D: 8A 45 08                 mov     al, [ebp+arg_0]
 * 000BE230: 89 45 F0                 mov     [ebp+var_10], eax
 * 000BE233: 33 C0                    xor     eax, eax
 * 000BE235: 66 8B 45 0C              mov     ax, [ebp+arg_4]
 * 000BE239: 89 45 F4                 mov     [ebp+var_C], eax
 * 000BE23C: 33 C0                    xor     eax, eax
 * 000BE23E: 66 89 C8                 mov     ax, cx
 * 000BE241: 89 45 F8                 mov     [ebp+var_8], eax
 * 000BE244: A1 CC 75 00 00           mov     eax, dword ptr ds:loc_75CC
 * 000BE249: C7 45 FC 00 00 00 00     mov     [ebp+var_4], 0
 * 000BE250: 89 04 24                 mov     [esp+1Ch+var_1C], eax
 * 000BE253: 8D 45 F0                 lea     eax, [ebp+var_10]
 * 000BE256: 89 44 24 04              mov     [esp+1Ch+var_18], eax
 * 000BE25A: E8 BE FE 00 00           call    os_syscall_90h_27h
 * 000BE25F: 23 C0                    and     eax, eax
 * 000BE261: 74 09                    jz      short loc_BE26C
 * 000BE263: 66 B8 1E 00              mov     ax, 1Eh
 * 000BE267: EB 05                    jmp     short loc_BE26E
 * 000BE269: 90 90 90                 align 4
 * 000BE26C: 2B C0                    sub     eax, eax
 * 000BE26E: 89 EC                    mov     esp, ebp
 * 000BE270: 5D                       pop     ebp
 * 000BE271: C3                       retn
 * ========================================================================== */
// Build request block and call os_syscall_90h_27h | [SRX-611] pop_rank=15/1298, sites=39, callers=10, callees=1, size=0x5E
// write access to const memory has been detected, the output may be wrong!
__int16 __cdecl sys_req_27h(char a1, __int16 a2, unsigned __int16 a3)
{
  if ( a3 < 0x64u )
    *(&loc_75D6 + 2) = 1;
  if ( os_syscall_90h_27h() )
    return 30;
  else
    return 0;
}


