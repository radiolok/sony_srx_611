/*
 * Sony SRX-611 firmware - C equivalents (Hex-Rays) - prefix 'os'
 * Source image: ROM1-C.bin (80486 real mode, OS+/386 V2.0)
 * Generated from IDA database ROM1-C.bin.i64
 * Functions in this file: 7
 */

/* ============================================================================
 * os_syscall_90h_12h  @ 0xCDFE8   size=0x18   pop_rank=10/1298
 * calls=61 callers=14
 * note: OS+/386 system call wrapper: function 0x12 via int 0x90h | [SRX-611] pop_rank=10/1298, sites=61, callers=14, callees=0, size=0x18, leaf
 * --- original assembly (address: bytes  mnemonic) ---------------------------
 * 000CDFE8: 55                       push    ebp
 * 000CDFE9: 8B EC                    mov     ebp, esp
 * 000CDFEB: 53                       push    ebx
 * 000CDFEC: 8B D6                    mov     edx, esi
 * 000CDFEE: 8B 5D 08                 mov     ebx, [ebp+arg_0]
 * 000CDFF1: 8B 75 0C                 mov     esi, [ebp+arg_4]
 * 000CDFF4: B8 12 00 00 00           mov     eax, 12h
 * 000CDFF9: CD 90                    int     90h; used by BASIC while in interpreter
 * 000CDFFB: 8B F2                    mov     esi, edx
 * 000CDFFD: 5B                       pop     ebx
 * 000CDFFE: C9                       leave
 * 000CDFFF: C3                       retn
 * ========================================================================== */
// OS+/386 system call wrapper: function 0x12 via int 0x90h | [SRX-611] pop_rank=10/1298, sites=61, callers=14, callees=0, size=0x18, leaf
int os_syscall_90h_12h()
{
  int result; // eax

  result = 18;
  __asm { int     90h; used by BASIC while in interpreter }
  return result;
}


/* ============================================================================
 * os_syscall_90h_2Ch  @ 0xCE2A3   size=0x18   pop_rank=16/1298
 * calls=36 callers=30
 * note: OS+/386 system call wrapper: function 0x2C via int 0x90h | [SRX-611] pop_rank=16/1298, sites=36, callers=30, callees=0, size=0x18, leaf
 * --- original assembly (address: bytes  mnemonic) ---------------------------
 * 000CE2A3: 55                       push    ebp
 * 000CE2A4: 8B EC                    mov     ebp, esp
 * 000CE2A6: 53                       push    ebx
 * 000CE2A7: 8B CE                    mov     ecx, esi
 * 000CE2A9: 8B 5D 08                 mov     ebx, [ebp+arg_0]
 * 000CE2AC: 8B 75 0C                 mov     esi, [ebp+arg_4]
 * 000CE2AF: B8 2C 00 00 00           mov     eax, 2Ch ; ','
 * 000CE2B4: CD 90                    int     90h; used by BASIC while in interpreter
 * 000CE2B6: 8B F1                    mov     esi, ecx
 * 000CE2B8: 5B                       pop     ebx
 * 000CE2B9: C9                       leave
 * 000CE2BA: C3                       retn
 * ========================================================================== */
// OS+/386 system call wrapper: function 0x2C via int 0x90h | [SRX-611] pop_rank=16/1298, sites=36, callers=30, callees=0, size=0x18, leaf
int os_syscall_90h_2Ch()
{
  int result; // eax

  result = 44;
  __asm { int     90h; used by BASIC while in interpreter }
  return result;
}


/* ============================================================================
 * os_syscall_90h_11h  @ 0xCDFC5   size=0x23   pop_rank=21/1298
 * calls=31 callers=21
 * note: OS+/386 system call wrapper: function 0x11 via int 0x90h | [SRX-611] pop_rank=21/1298, sites=31, callers=21, callees=0, size=0x23, leaf
 * --- original assembly (address: bytes  mnemonic) ---------------------------
 * 000CDFC5: 55                       push    ebp
 * 000CDFC6: 8B EC                    mov     ebp, esp
 * 000CDFC8: 53                       push    ebx
 * 000CDFC9: 56                       push    esi
 * 000CDFCA: 57                       push    edi
 * 000CDFCB: 8B 5D 08                 mov     ebx, [ebp+arg_0]
 * 000CDFCE: 8B 4D 0C                 mov     ecx, [ebp+arg_4]
 * 000CDFD1: 8B 7D 10                 mov     edi, [ebp+arg_8]
 * 000CDFD4: 8B 55 14                 mov     edx, [ebp+arg_C]
 * 000CDFD7: B8 11 00 00 00           mov     eax, 11h
 * 000CDFDC: CD 90                    int     90h; used by BASIC while in interpreter
 * 000CDFDE: 8B 4D 18                 mov     ecx, [ebp+arg_10]
 * 000CDFE1: 89 31                    mov     [ecx], esi
 * 000CDFE3: 5F                       pop     edi
 * 000CDFE4: 5E                       pop     esi
 * 000CDFE5: 5B                       pop     ebx
 * 000CDFE6: C9                       leave
 * 000CDFE7: C3                       retn
 * ========================================================================== */
// OS+/386 system call wrapper: function 0x11 via int 0x90h | [SRX-611] pop_rank=21/1298, sites=31, callers=21, callees=0, size=0x23, leaf
int __usercall os_syscall_90h_11h@<eax>(int a1@<esi>, int a2, int a3, int a4, int a5, _DWORD *a6)
{
  int result; // eax

  result = 17;
  __asm { int     90h; used by BASIC while in interpreter }
  *a6 = a1;
  return result;
}


/* ============================================================================
 * os_syscall_90h_08h  @ 0xCDEDD   size=0x19   pop_rank=23/1298
 * calls=28 callers=8
 * note: OS+/386 system call wrapper: function 0x08 via int 0x90h | [SRX-611] pop_rank=23/1298, sites=28, callers=8, callees=0, size=0x19, leaf
 * --- original assembly (address: bytes  mnemonic) ---------------------------
 * 000CDEDD: 55                       push    ebp
 * 000CDEDE: 8B EC                    mov     ebp, esp
 * 000CDEE0: 53                       push    ebx
 * 000CDEE1: 8B 5D 08                 mov     ebx, [ebp+arg_0]
 * 000CDEE4: 8B 4D 0C                 mov     ecx, [ebp+arg_4]
 * 000CDEE7: B8 08 00 00 00           mov     eax, 8
 * 000CDEEC: CD 90                    int     90h; used by BASIC while in interpreter
 * 000CDEEE: 8B 5D 10                 mov     ebx, [ebp+arg_8]
 * 000CDEF1: 89 0B                    mov     [ebx], ecx
 * 000CDEF3: 5B                       pop     ebx
 * 000CDEF4: C9                       leave
 * 000CDEF5: C3                       retn
 * ========================================================================== */
// OS+/386 system call wrapper: function 0x08 via int 0x90h | [SRX-611] pop_rank=23/1298, sites=28, callers=8, callees=0, size=0x19, leaf
int __cdecl os_syscall_90h_08h(int a1, int a2, _DWORD *a3)
{
  int result; // eax

  result = 8;
  __asm { int     90h; used by BASIC while in interpreter }
  *a3 = a2;
  return result;
}


/* ============================================================================
 * os_syscall_90h_36h  @ 0xCE35C   size=0x1B   pop_rank=31/1298
 * calls=25 callers=11
 * note: OS+/386 system call wrapper: function 0x36 via int 0x90h | [SRX-611] pop_rank=31/1298, sites=25, callers=11, callees=0, size=0x1B, leaf
 * --- original assembly (address: bytes  mnemonic) ---------------------------
 * 000CE35C: 55                       push    ebp
 * 000CE35D: 8B EC                    mov     ebp, esp
 * 000CE35F: 53                       push    ebx
 * 000CE360: 8B CF                    mov     ecx, edi
 * 000CE362: 8B 5D 08                 mov     ebx, [ebp+arg_0]
 * 000CE365: 8B 7D 0C                 mov     edi, [ebp+arg_4]
 * 000CE368: 8B 55 10                 mov     edx, [ebp+arg_8]
 * 000CE36B: B8 36 00 00 00           mov     eax, 36h ; '6'
 * 000CE370: CD 90                    int     90h; used by BASIC while in interpreter
 * 000CE372: 8B F9                    mov     edi, ecx
 * 000CE374: 5B                       pop     ebx
 * 000CE375: C9                       leave
 * 000CE376: C3                       retn
 * ========================================================================== */
// OS+/386 system call wrapper: function 0x36 via int 0x90h | [SRX-611] pop_rank=31/1298, sites=25, callers=11, callees=0, size=0x1B, leaf
int os_syscall_90h_36h()
{
  int result; // eax

  result = 54;
  __asm { int     90h; used by BASIC while in interpreter }
  return result;
}


/* ============================================================================
 * os_syscall_90h_37h  @ 0xCE34B   size=0x11   pop_rank=32/1298
 * calls=24 callers=15
 * note: OS+/386 system call wrapper: function 0x37 via int 0x90h | [SRX-611] pop_rank=32/1298, sites=24, callers=15, callees=0, size=0x11, leaf
 * --- original assembly (address: bytes  mnemonic) ---------------------------
 * 000CE34B: 55                       push    ebp
 * 000CE34C: 8B EC                    mov     ebp, esp
 * 000CE34E: 53                       push    ebx
 * 000CE34F: 8B 5D 08                 mov     ebx, [ebp+arg_0]
 * 000CE352: B8 37 00 00 00           mov     eax, 37h ; '7'
 * 000CE357: CD 90                    int     90h; used by BASIC while in interpreter
 * 000CE359: 5B                       pop     ebx
 * 000CE35A: C9                       leave
 * 000CE35B: C3                       retn
 * ========================================================================== */
// OS+/386 system call wrapper: function 0x37 via int 0x90h | [SRX-611] pop_rank=32/1298, sites=24, callers=15, callees=0, size=0x11, leaf
int os_syscall_90h_37h()
{
  int result; // eax

  result = 55;
  __asm { int     90h; used by BASIC while in interpreter }
  return result;
}


/* ============================================================================
 * os_syscall_90h_27h  @ 0xCE11D   size=0x23   pop_rank=46/1298
 * calls=20 callers=15
 * note: OS+/386 system call wrapper: function 0x27 via int 0x90h | [SRX-611] pop_rank=46/1298, sites=20, callers=15, callees=0, size=0x23, leaf
 * --- original assembly (address: bytes  mnemonic) ---------------------------
 * 000CE11D: 55                       push    ebp
 * 000CE11E: 8B EC                    mov     ebp, esp
 * 000CE120: 53                       push    ebx
 * 000CE121: 56                       push    esi
 * 000CE122: 57                       push    edi
 * 000CE123: 8B 5D 08                 mov     ebx, [ebp+arg_0]
 * 000CE126: 8B 7D 0C                 mov     edi, [ebp+arg_4]
 * 000CE129: 8B 0F                    mov     ecx, [edi]
 * 000CE12B: 8B 57 04                 mov     edx, [edi+4]
 * 000CE12E: 8B 77 08                 mov     esi, [edi+8]
 * 000CE131: 8B 7F 0C                 mov     edi, [edi+0Ch]
 * 000CE134: B8 27 00 00 00           mov     eax, 27h ; '''
 * 000CE139: CD 90                    int     90h; used by BASIC while in interpreter
 * 000CE13B: 5F                       pop     edi
 * 000CE13C: 5E                       pop     esi
 * 000CE13D: 5B                       pop     ebx
 * 000CE13E: C9                       leave
 * 000CE13F: C3                       retn
 * ========================================================================== */
// OS+/386 system call wrapper: function 0x27 via int 0x90h | [SRX-611] pop_rank=46/1298, sites=20, callers=15, callees=0, size=0x23, leaf
int os_syscall_90h_27h()
{
  int result; // eax

  result = 39;
  __asm { int     90h; used by BASIC while in interpreter }
  return result;
}


