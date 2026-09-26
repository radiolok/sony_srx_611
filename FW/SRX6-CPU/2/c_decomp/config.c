/*
 * Sony SRX-611 firmware - C equivalents (Hex-Rays) - prefix 'config'
 * Source image: ROM1-C.bin (80486 real mode, OS+/386 V2.0)
 * Generated from IDA database ROM1-C.bin.i64
 * Functions in this file: 1
 */

/* ============================================================================
 * config_get_record  @ 0xAD9C   size=0xB0   pop_rank=25/1298
 * calls=26 callers=25
 * note: Fetch/validate a config record by index (1012-byte records @0x4660) | [SRX-611] pop_rank=25/1298, sites=26, callers=25, callees=0, size=0xB0, leaf
 * --- original assembly (address: bytes  mnemonic) ---------------------------
 * 0000AD9C: 55                       push    ebp
 * 0000AD9D: 89 E5                    mov     ebp, esp
 * 0000AD9F: 83 EC 08                 sub     esp, 8
 * 0000ADA2: 8A 45 08                 mov     al, [ebp+arg_0]
 * 0000ADA5: 66 C7 45 FE 00 00        mov     [ebp+var_2], 0
 * 0000ADAB: 57                       push    edi
 * 0000ADAC: 56                       push    esi
 * 0000ADAD: 53                       push    ebx
 * 0000ADAE: 2B FF                    sub     edi, edi
 * 0000ADB0: 3C 01                    cmp     al, 1
 * 0000ADB2: 72 08                    jb      short loc_ADBC
 * 0000ADB4: 3A 05 50 4A 00 00        cmp     al, byte ptr ds:loc_4A4E+2
 * 0000ADBA: 76 10                    jbe     short loc_ADCC
 * 0000ADBC: 66 B8 0C 2B              mov     ax, 2B0Ch
 * 0000ADC0: E9 80 00 00 00           jmp     loc_AE45
 * 0000ADC5: 90 90 90 90 90 90 90     db 7 dup(90h)
 * 0000ADCC: 25 FF 00 00 00           and     eax, 0FFh
 * 0000ADD1: 89 C6                    mov     esi, eax
 * 0000ADD3: C1 E6 06                 shl     esi, 6
 * 0000ADD6: 2B F0                    sub     esi, eax
 * 0000ADD8: 8D 34 B0                 lea     esi, [eax+esi*4]
 * 0000ADDB: C1 E6 02                 shl     esi, 2
 * 0000ADDE: 8D 86 60 46 00 00        lea     eax, [esi+4660h]
 * 0000ADE4: 89 45 F8                 mov     [ebp+var_8], eax
 * 0000ADE7: 8B 45 0C                 mov     eax, [ebp+arg_4]
 * 0000ADEA: 8A 8E 60 46 00 00        mov     cl, [esi+4660h]
 * 0000ADF0: 88 08                    mov     [eax], cl
 * 0000ADF2: 8A 96 61 46 00 00        mov     dl, [esi+4661h]
 * 0000ADF8: 80 F9 01                 cmp     cl, 1
 * 0000ADFB: 88 50 01                 mov     [eax+1], dl
 * 0000ADFE: 8A 9E 62 46 00 00        mov     bl, [esi+4662h]
 * 0000AE04: 88 58 02                 mov     [eax+2], bl
 * 0000AE07: 8A 96 63 46 00 00        mov     dl, [esi+4663h]
 * 0000AE0D: 88 50 03                 mov     [eax+3], dl
 * 0000AE10: 8A 96 64 46 00 00        mov     dl, [esi+4664h]
 * 0000AE16: 88 50 04                 mov     [eax+4], dl
 * 0000AE19: 74 11                    jz      short loc_AE2C
 * 0000AE1B: 80 F9 02                 cmp     cl, 2
 * 0000AE1E: 74 14                    jz      short loc_AE34
 * 0000AE20: 66 C7 45 FE 0D 2B        mov     [ebp+var_2], 2B0Dh
 * 0000AE26: 66 B8 0D 2B              mov     ax, 2B0Dh
 * 0000AE2A: EB 0A                    jmp     short loc_AE36
 * 0000AE2C: 89 F8                    mov     eax, edi
 * 0000AE2E: EB 06                    jmp     short loc_AE36
 * 0000AE30: 90 90 90 90              db 4 dup(90h)
 * 0000AE34: 89 F8                    mov     eax, edi
 * 0000AE36: 80 FB 04                 cmp     bl, 4
 * 0000AE39: 76 0A                    jbe     short loc_AE45
 * 0000AE3B: 66 C7 45 FE 0F 2B        mov     [ebp+var_2], 2B0Fh
 * 0000AE41: 66 B8 0F 2B              mov     ax, 2B0Fh
 * 0000AE45: 5B                       pop     ebx
 * 0000AE46: 5E                       pop     esi
 * 0000AE47: 5F                       pop     edi
 * 0000AE48: 89 EC                    mov     esp, ebp
 * 0000AE4A: 5D                       pop     ebp
 * 0000AE4B: C3                       retn
 * ========================================================================== */
// Fetch/validate a config record by index (1012-byte records @0x4660) | [SRX-611] pop_rank=25/1298, sites=26, callers=25, callees=0, size=0xB0, leaf
__int16 __cdecl config_get_record(unsigned __int8 a1, _BYTE *a2)
{
  __int16 result; // ax
  char v3; // cl
  unsigned __int8 v4; // bl

  if ( !a1 || a1 > *(&loc_4A4E + 2) )
    return 11020;
  v3 = *((_BYTE *)&loc_4660 + 1012 * a1);
  *a2 = v3;
  a2[1] = *((_BYTE *)&loc_4660 + 1012 * a1 + 1);
  v4 = *((_BYTE *)&loc_4660 + 1012 * a1 + 2);
  a2[2] = v4;
  a2[3] = *((_BYTE *)&loc_4660 + 1012 * a1 + 3);
  a2[4] = *((_BYTE *)&loc_4660 + 1012 * a1 + 4);
  if ( v3 == 1 )
  {
    result = 0;
  }
  else if ( v3 == 2 )
  {
    result = 0;
  }
  else
  {
    result = 11021;
  }
  if ( v4 > 4u )
    return 11023;
  return result;
}


