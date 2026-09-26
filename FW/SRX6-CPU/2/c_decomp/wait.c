/*
 * Sony SRX-611 firmware - C equivalents (Hex-Rays) - prefix 'wait'
 * Source image: ROM1-C.bin (80486 real mode, OS+/386 V2.0)
 * Generated from IDA database ROM1-C.bin.i64
 * Functions in this file: 1
 */

/* ============================================================================
 * wait_real_var  @ 0x66D24   size=0xC2   pop_rank=11/1298
 * calls=53 callers=1
 * note: Poll a REAL variable via db_get_real in a timed loop until it changes/target | [SRX-611] pop_rank=11/1298, sites=53, callers=1, callees=4, size=0xC2
 * --- original assembly (address: bytes  mnemonic) ---------------------------
 * 00066D24: 55                       push    ebp
 * 00066D25: 89 E5                    mov     ebp, esp
 * 00066D27: 83 EC 10                 sub     esp, 10h
 * 00066D2A: 57                       push    edi
 * 00066D2B: 56                       push    esi
 * 00066D2C: 53                       push    ebx
 * 00066D2D: 83 EC 10                 sub     esp, 10h
 * 00066D30: 8D 7D FF                 lea     edi, [ebp+var_1]
 * 00066D33: 8D 75 FE                 lea     esi, [ebp+var_2]
 * 00066D36: 8A 5D 08                 mov     bl, [ebp+arg_0]
 * 00066D39: 89 3C 24                 mov     [esp+2Ch+var_2C], edi
 * 00066D3C: 89 74 24 04              mov     [esp+2Ch+var_28], esi
 * 00066D40: 8D 45 FD                 lea     eax, [ebp+var_3]
 * 00066D43: 89 44 24 08              mov     [esp+2Ch+var_24], eax
 * 00066D47: 8D 45 F0                 lea     eax, [ebp+var_10]
 * 00066D4A: 89 44 24 0C              mov     [esp+2Ch+var_20], eax
 * 00066D4E: E8 11 37 05 00           call    db_get_real
 * 00066D53: 38 5D F0                 cmp     [ebp+var_10], bl
 * 00066D56: 75 0C                    jnz     short loc_66D64
 * 00066D58: 8D 45 FD                 lea     eax, [ebp+var_3]
 * 00066D5B: 89 C3                    mov     ebx, eax
 * 00066D5D: EB 3D                    jmp     short loc_66D9C
 * 00066D5F: 90 90 90 90 90           db 5 dup(90h)
 * 00066D64: 80 7D FF 00              cmp     [ebp+var_1], 0
 * 00066D68: 74 14                    jz      short loc_66D7E
 * 00066D6A: C7 04 24 FE 00 00 00     mov     [esp+2Ch+var_2C], 0FEh
 * 00066D71: C7 44 24 04 05 00 00 00  mov     [esp+2Ch+var_28], 5
 * 00066D79: E8 46 46 05 00           call    db_get_field92
 * 00066D7E: C7 04 24 0A 00 00 00     mov     [esp+2Ch+var_2C], 0Ah
 * 00066D85: E8 53 76 06 00           call    os_syscall_90h_3Ch
 * 00066D8A: E8 CD 1A FA FF           call    motion_885C
 * 00066D8F: 22 C0                    and     al, al
 * 00066D91: 75 A6                    jnz     short loc_66D39
 * 00066D93: EB 44                    jmp     short loc_66DD9
 * 00066D95: 90 90 90 90 90 90 90     db 7 dup(90h)
 * 00066D9C: 89 3C 24                 mov     [esp+2Ch+var_2C], edi
 * 00066D9F: 89 74 24 04              mov     [esp+2Ch+var_28], esi
 * 00066DA3: 89 5C 24 08              mov     [esp+2Ch+var_24], ebx
 * 00066DA7: 8D 45 F0                 lea     eax, [ebp+var_10]
 * 00066DAA: 89 44 24 0C              mov     [esp+2Ch+var_20], eax
 * 00066DAE: E8 B1 36 05 00           call    db_get_real
 * 00066DB3: 80 7D F0 00              cmp     [ebp+var_10], 0
 * 00066DB7: 74 06                    jz      short loc_66DBF
 * 00066DB9: 80 7D FF 00              cmp     [ebp+var_1], 0
 * 00066DBD: 75 05                    jnz     short loc_66DC4
 * 00066DBF: EB 18                    jmp     short loc_66DD9
 * 00066DC1: 90 90 90                 align 4
 * 00066DC4: C7 04 24 0A 00 00 00     mov     [esp+2Ch+var_2C], 0Ah
 * 00066DCB: E8 0D 76 06 00           call    os_syscall_90h_3Ch
 * 00066DD0: E8 87 1A FA FF           call    motion_885C
 * 00066DD5: 22 C0                    and     al, al
 * 00066DD7: 75 C3                    jnz     short loc_66D9C
 * 00066DD9: 8B 5D E4                 mov     ebx, [ebp+var_1C]
 * 00066DDC: 8B 75 E8                 mov     esi, [ebp+var_18]
 * 00066DDF: 8B 7D EC                 mov     edi, [ebp+var_14]
 * 00066DE2: 89 EC                    mov     esp, ebp
 * 00066DE4: 5D                       pop     ebp
 * 00066DE5: C3                       retn
 * ========================================================================== */
// Poll a REAL variable via db_get_real in a timed loop until it changes/target | [SRX-611] pop_rank=11/1298, sites=53, callers=1, callees=4, size=0xC2
char __cdecl wait_real_var(char a1)
{
  char result; // al
  _BYTE v2[13]; // [esp+1Ch] [ebp-10h] BYREF
  char v3; // [esp+29h] [ebp-3h] BYREF
  char v4; // [esp+2Ah] [ebp-2h] BYREF
  char v5; // [esp+2Bh] [ebp-1h] BYREF

  while ( 1 )
  {
    db_get_real(&v5, &v4, &v3, v2);
    if ( v2[0] == a1 )
      break;
    if ( v5 )
      db_get_field92(0xFEu, 5);
    os_syscall_90h_3Ch(10);
    result = motion_885C();
    if ( !result )
      return result;
  }
  do
  {
    result = db_get_real(&v5, &v4, &v3, v2);
    if ( !v2[0] )
      break;
    if ( !v5 )
      break;
    os_syscall_90h_3Ch(10);
    result = motion_885C();
  }
  while ( result );
  return result;
}


