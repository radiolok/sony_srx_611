/*
 * Sony SRX-611 firmware - C equivalents (Hex-Rays) - prefix 'str'
 * Source image: ROM1-C.bin (80486 real mode, OS+/386 V2.0)
 * Generated from IDA database ROM1-C.bin.i64
 * Functions in this file: 1
 */

/* ============================================================================
 * str_store  @ 0xCD9D4   size=0x4C   pop_rank=1/1298
 * calls=699 callers=121
 * note: String store/copy helper (most-used function, 699 call sites): copies string arg4 into buffer obtained from field_CE60C(arg0) | [SRX-611] pop_rank=1/1298, sites=699, callers=121, callees=1, size=0x4C
 * --- original assembly (address: bytes  mnemonic) ---------------------------
 * 000CD9D4: 55                       push    ebp
 * 000CD9D5: 89 E5                    mov     ebp, esp
 * 000CD9D7: 57                       push    edi
 * 000CD9D8: 56                       push    esi
 * 000CD9D9: 53                       push    ebx
 * 000CD9DA: 8B 5D 0C                 mov     ebx, [ebp+arg_4]
 * 000CD9DD: 68 FF FF FF 7F           push    7FFFFFFFh
 * 000CD9E2: 6A 00                    push    0
 * 000CD9E4: 8B 7D 08                 mov     edi, [ebp+arg_0]
 * 000CD9E7: 57                       push    edi
 * 000CD9E8: E8 1F 0C 00 00           call    field_CE60C
 * 000CD9ED: 89 C6                    mov     esi, eax
 * 000CD9EF: 2B C0                    sub     eax, eax
 * 000CD9F1: B9 FF FF FF FF           mov     ecx, 0FFFFFFFFh
 * 000CD9F6: 57                       push    edi
 * 000CD9F7: 89 DF                    mov     edi, ebx
 * 000CD9F9: F2 AE                    repne scasb
 * 000CD9FB: F7 D9                    neg     ecx
 * 000CD9FD: 83 E9 02                 sub     ecx, 2
 * 000CDA00: 41                       inc     ecx
 * 000CDA01: 89 F7                    mov     edi, esi
 * 000CDA03: 89 DE                    mov     esi, ebx
 * 000CDA05: FC                       cld
 * 000CDA06: 0F AC CA 02              shrd    edx, ecx, 2
 * 000CDA0A: C1 E9 02                 shr     ecx, 2
 * 000CDA0D: F3 A5                    rep movsd
 * 000CDA0F: 0F A4 D1 02              shld    ecx, edx, 2
 * 000CDA13: F3 A4                    rep movsb
 * 000CDA15: 5F                       pop     edi
 * 000CDA16: 89 F8                    mov     eax, edi
 * 000CDA18: 83 C4 0C                 add     esp, 0Ch
 * 000CDA1B: 5B                       pop     ebx
 * 000CDA1C: 5E                       pop     esi
 * 000CDA1D: 5F                       pop     edi
 * 000CDA1E: C9                       leave
 * 000CDA1F: C3                       retn
 * ========================================================================== */
// String store/copy helper (most-used function, 699 call sites): copies string arg4 into buffer obtained from field_CE60C(arg0) | [SRX-611] pop_rank=1/1298, sites=699, callers=121, callees=1, size=0x4C
int __cdecl str_store(int a1, const char *a2)
{
  char *v2; // esi
  unsigned int v3; // kr04_4
  unsigned int v4; // edx

  v2 = (char *)field_CE60C(a1, 0, 0x7FFFFFFF);
  v3 = strlen(a2) + 1;
  qmemcpy(v2, a2, 4 * (v3 >> 2));
  qmemcpy(&v2[4 * (v3 >> 2)], &a2[4 * (v3 >> 2)], (unsigned __int64)(unsigned int)(__PAIR64__(v3, v4) >> 2) >> 30);
  return a1;
}


