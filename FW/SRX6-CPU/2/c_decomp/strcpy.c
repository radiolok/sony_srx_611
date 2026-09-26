/*
 * Sony SRX-611 firmware - C equivalents (Hex-Rays) - prefix 'strcpy'
 * Source image: ROM1-C.bin (80486 real mode, OS+/386 V2.0)
 * Generated from IDA database ROM1-C.bin.i64
 * Functions in this file: 1
 */

/* ============================================================================
 * strcpy  @ 0xCE55C   size=0x30   pop_rank=3/1298
 * calls=235 callers=44
 * note: String copy: strlen (repne scasb) + dword/byte copy (rep movs) | [SRX-611] pop_rank=3/1298, sites=235, callers=44, callees=0, size=0x30, leaf
 * --- original assembly (address: bytes  mnemonic) ---------------------------
 * 000CE55C: 8B D6                    mov     edx, esi
 * 000CE55E: 57                       push    edi
 * 000CE55F: 2B C0                    sub     eax, eax
 * 000CE561: B9 FF FF FF FF           mov     ecx, 0FFFFFFFFh
 * 000CE566: 8B 7C 24 0C              mov     edi, [esp+4+arg_4]
 * 000CE56A: F2 AE                    repne scasb
 * 000CE56C: F7 D1                    not     ecx
 * 000CE56E: 8B 74 24 0C              mov     esi, [esp+4+arg_4]
 * 000CE572: 8B 7C 24 08              mov     edi, [esp+4+arg_0]
 * 000CE576: 8B C1                    mov     eax, ecx
 * 000CE578: C1 E9 02                 shr     ecx, 2
 * 000CE57B: F3 A5                    rep movsd
 * 000CE57D: 8B C8                    mov     ecx, eax
 * 000CE57F: 83 E1 03                 and     ecx, 3
 * 000CE582: F3 A4                    rep movsb
 * 000CE584: 8B 44 24 08              mov     eax, [esp+4+arg_0]
 * 000CE588: 8B F2                    mov     esi, edx
 * 000CE58A: 5F                       pop     edi
 * 000CE58B: C3                       retn
 * ========================================================================== */
// String copy: strlen (repne scasb) + dword/byte copy (rep movs) | [SRX-611] pop_rank=3/1298, sites=235, callers=44, callees=0, size=0x30, leaf
char *__cdecl strcpy(char *a1, const char *a2)
{
  strcpy(a1, a2);
  return a1;
}


