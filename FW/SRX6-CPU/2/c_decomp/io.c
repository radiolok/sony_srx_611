/*
 * Sony SRX-611 firmware - C equivalents (Hex-Rays) - prefix 'io'
 * Source image: ROM1-C.bin (80486 real mode, OS+/386 V2.0)
 * Generated from IDA database ROM1-C.bin.i64
 * Functions in this file: 1
 */

/* ============================================================================
 * io_req_27h  @ 0x44F60   size=0x86   pop_rank=38/1298
 * calls=22 callers=22
 * note: Validate index against table and call os_syscall_90h_27h | [SRX-611] pop_rank=38/1298, sites=22, callers=22, callees=2, size=0x86
 * --- original assembly (address: bytes  mnemonic) ---------------------------
 * 00044F60: 55                       push    ebp
 * 00044F61: 89 E5                    mov     ebp, esp
 * 00044F63: 83 EC 24                 sub     esp, 24h
 * 00044F66: 8D 45 FF                 lea     eax, [ebp+var_1]
 * 00044F69: 89 04 24                 mov     [esp+24h+var_24], eax
 * 00044F6C: E8 93 5D FC FF           call    plc_AD04
 * 00044F71: 66 23 C0                 and     ax, ax
 * 00044F74: 74 0A                    jz      short loc_44F80
 * 00044F76: 66 B8 8B 3E              mov     ax, 3E8Bh
 * 00044F7A: EB 66                    jmp     short loc_44FE2
 * 00044F7C: 90 90 90 90              align 10h
 * 00044F80: 8A 45 08                 mov     al, [ebp+arg_0]
 * 00044F83: 3C 01                    cmp     al, 1
 * 00044F85: 72 05                    jb      short loc_44F8C
 * 00044F87: 3A 45 FF                 cmp     al, [ebp+var_1]
 * 00044F8A: 76 0C                    jbe     short loc_44F98
 * 00044F8C: 66 B8 8C 3E              mov     ax, 3E8Ch
 * 00044F90: EB 50                    jmp     short loc_44FE2
 * 00044F92: 90 90 90 90 90 90        align 8
 * 00044F98: 25 FF 00 00 00           and     eax, 0FFh
 * 00044F9D: 80 B8 F3 74 00 00 01     cmp     byte ptr [eax+74F3h], 1
 * 00044FA4: 74 0A                    jz      short loc_44FB0
 * 00044FA6: 66 B8 8C 3E              mov     ax, 3E8Ch
 * 00044FAA: EB 36                    jmp     short loc_44FE2
 * 00044FAC: 90 90 90 90              align 10h
 * 00044FB0: 8B 04 85 D0 74 00 00     mov     eax, dword ptr ds:loc_74CE+2[eax*4]
 * 00044FB7: C7 45 EC 01 00 00 00     mov     [ebp+var_14], 1
 * 00044FBE: C7 45 F0 14 00 00 00     mov     [ebp+var_10], 14h
 * 00044FC5: 8B 00                    mov     eax, [eax]
 * 00044FC7: 89 04 24                 mov     [esp+24h+var_24], eax
 * 00044FCA: 8D 45 E8                 lea     eax, [ebp+var_18]
 * 00044FCD: 89 44 24 04              mov     [esp+24h+var_20], eax
 * 00044FD1: E8 47 91 08 00           call    os_syscall_90h_27h
 * 00044FD6: 23 C0                    and     eax, eax
 * 00044FD8: 74 06                    jz      short loc_44FE0
 * 00044FDA: 66 B8 80 3E              mov     ax, 3E80h
 * 00044FDE: EB 02                    jmp     short loc_44FE2
 * 00044FE0: 2B C0                    sub     eax, eax
 * 00044FE2: 89 EC                    mov     esp, ebp
 * 00044FE4: 5D                       pop     ebp
 * 00044FE5: C3                       retn
 * ========================================================================== */
// Validate index against table and call os_syscall_90h_27h | [SRX-611] pop_rank=38/1298, sites=22, callers=22, callees=2, size=0x86
__int16 __cdecl io_req_27h(unsigned __int8 a1)
{
  _DWORD *v2; // eax
  _BYTE v3[4]; // [esp+Ch] [ebp-18h] BYREF
  int v4; // [esp+10h] [ebp-14h]
  int v5; // [esp+14h] [ebp-10h]
  unsigned __int8 v6; // [esp+23h] [ebp-1h] BYREF

  if ( (unsigned __int16)plc_AD04(&v6) )
    return 16011;
  if ( !a1 || a1 > v6 )
    return 16012;
  if ( *((_BYTE *)&loc_74EE + a1 + 5) != 1 )
    return 16012;
  v2 = *(_DWORD **)((char *)&loc_74CE + 4 * a1 + 2);
  v4 = 1;
  v5 = 20;
  if ( os_syscall_90h_27h(*v2, v3) )
    return 16000;
  else
    return 0;
}


