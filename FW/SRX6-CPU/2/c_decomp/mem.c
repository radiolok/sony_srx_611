/*
 * Sony SRX-611 firmware - C equivalents (Hex-Rays) - prefix 'mem'
 * Source image: ROM1-C.bin (80486 real mode, OS+/386 V2.0)
 * Generated from IDA database ROM1-C.bin.i64
 * Functions in this file: 1
 */

/* ============================================================================
 * mem_alloc  @ 0x8B74   size=0x5E   pop_rank=8/1298
 * calls=82 callers=81
 * note: Memory allocation/request via os_syscall_91h_05h; size computed relative to sub_4A24 | [SRX-611] pop_rank=8/1298, sites=82, callers=81, callees=1, size=0x5E
 * --- original assembly (address: bytes  mnemonic) ---------------------------
 * 00008B74: 55                       push    ebp
 * 00008B75: 89 E5                    mov     ebp, esp
 * 00008B77: 8D 45 08                 lea     eax, [ebp+arg_0]
 * 00008B7A: 89 45 F0                 mov     [ebp+var_10], eax
 * 00008B7D: 8D 45 E8                 lea     eax, [ebp+var_18]
 * 00008B80: 83 EC 24                 sub     esp, 24h
 * 00008B83: 89 45 F4                 mov     [ebp+var_C], eax
 * 00008B86: 8B 45 0C                 mov     eax, [ebp+arg_4]
 * 00008B89: 89 45 F8                 mov     [ebp+var_8], eax
 * 00008B8C: 8D 0D 24 4A 00 00        lea     ecx, os_4A24
 * 00008B92: 2B C1                    sub     eax, ecx
 * 00008B94: 89 45 E8                 mov     [ebp+var_18], eax
 * 00008B97: C7 04 24 00 00 05 00     mov     [esp+24h+var_24], offset loc_50000
 * 00008B9E: 8D 45 F0                 lea     eax, [ebp+var_10]
 * 00008BA1: 89 44 24 04              mov     [esp+24h+var_20], eax
 * 00008BA5: 8D 45 EC                 lea     eax, [ebp+var_14]
 * 00008BA8: 89 44 24 08              mov     [esp+24h+var_1C], eax
 * 00008BAC: E8 6F 59 0C 00           call    os_syscall_91h_05h
 * 00008BB1: 23 C0                    and     eax, eax
 * 00008BB3: 74 07                    jz      short loc_8BBC
 * 00008BB5: 66 B8 F8 2A              mov     ax, 2AF8h
 * 00008BB9: EB 13                    jmp     short loc_8BCE
 * 00008BBB: 90                       align 4
 * 00008BBC: 83 7D EC 00              cmp     [ebp+var_14], 0
 * 00008BC0: 74 0A                    jz      short loc_8BCC
 * 00008BC2: 66 B8 03 2B              mov     ax, 2B03h
 * 00008BC6: EB 06                    jmp     short loc_8BCE
 * 00008BC8: 90 90 90 90              db 4 dup(90h)
 * 00008BCC: 2B C0                    sub     eax, eax
 * 00008BCE: 89 EC                    mov     esp, ebp
 * 00008BD0: 5D                       pop     ebp
 * 00008BD1: C3                       retn
 * ========================================================================== */
// Memory allocation/request via os_syscall_91h_05h; size computed relative to sub_4A24 | [SRX-611] pop_rank=8/1298, sites=82, callers=81, callees=1, size=0x5E
__int16 __cdecl mem_alloc(char a1, int a2)
{
  int v3; // [esp+Ch] [ebp-18h] BYREF
  int v4; // [esp+10h] [ebp-14h] BYREF
  _DWORD v5[4]; // [esp+14h] [ebp-10h] BYREF

  v5[0] = &a1;
  v5[1] = &v3;
  v5[2] = a2;
  v3 = a2 - (_DWORD)os_4A24;
  if ( os_syscall_91h_05h(&loc_50000, v5, &v4) )
    return 11000;
  if ( v4 )
    return 11011;
  return 0;
}


