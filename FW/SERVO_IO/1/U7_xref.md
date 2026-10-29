## Boot page 0 (192 words)

### Direct DM accesses `DM($addr)`

| addr | region / name | reads | writes | at PM |
|---|---|---|---|---|
| `$3021` | ext_DWAIT3 | 1 | 0 | 0078 |
| `$3022` | ext_DWAIT3 | 0 | 1 | 001C |
| `$3023` | ext_DWAIT3 | 2 | 1 | 001E 0036 0037 |
| `$3024` | ext_DWAIT3 | 0 | 1 | 0020 |
| `$3025` | ext_DWAIT3 | 0 | 2 | 0021 0032 |
| `$3029` | ext_DWAIT3 | 0 | 1 | 0047 |
| `$302D` | ext_DWAIT3 | 0 | 1 | 0049 |
| `$302F` | ext_DWAIT3 | 0 | 1 | 0023 |
| `$3032` | ext_DWAIT3 | 0 | 1 | 0024 |
| `$3200` | ext_DWAIT3 | 0 | 1 | 0034 |
| `$3400` | ext_DWAIT4 | 1 | 0 | 0025 |
| `$3804` | int_ram | 0 | 1 | 006D |
| `$3834` | int_ram | 0 | 1 | 0050 |
| `$3835` | int_ram | 0 | 1 | 006F |

### Indirect DM accesses with a known I-register value

| addr | region / name | reads | writes | at PM |
|---|---|---|---|---|
| `$3000` | ext_DWAIT3 | 0 | 1 | 002D |
| `$3021` | ext_DWAIT3 | 0 | 3 | 0019 001A 002E |
| `$3800` | int_ram | 0 | 1 | 0029 |
| `$3802` | int_ram | 0 | 1 | 0064 |
| `$381A` | int_ram | 0 | 1 | 0056 |
| `$3838` | int_ram | 0 | 1 | 005C |
| `$384E` | int_ram | 0 | 1 | 0067 |
| `$3853` | int_ram | 0 | 1 | 006A |
| `$3858` | int_ram | 0 | 1 | 0062 |
| `$38A8` | int_ram | 0 | 1 | 0071 |
| `$3FF4` | SP0_RFSDIV | 0 | 1 | 0011 |
| `$3FF5` | SP0_SCLKDIV | 0 | 1 | 0012 |
| `$3FF6` | SP0_CTRL | 0 | 1 | 0013 |
| `$3FFE` | DM_WAIT | 0 | 1 | 0015 |
| `$3FFF` | SYSCNTL | 0 | 1 | 0083 |

### Flag-pin changes


### Most-called subroutines

- `0CE0` ×1

## Boot page 1 (1024 words)

### Direct DM accesses `DM($addr)`

| addr | region / name | reads | writes | at PM |
|---|---|---|---|---|
| `$0000` | ext_DWAIT0 | 4 | 0 | 0331 0332 0341 0342 |
| `$1000` | ext_DWAIT2 | 0 | 1 | 0146 |
| `$1001` | ext_DWAIT2 | 0 | 1 | 014C |
| `$3000` | ext_DWAIT3 | 1 | 2 | 00DB 01D0 03E8 |
| `$3001` | ext_DWAIT3 | 1 | 1 | 00B6 00C4 |
| `$3002` | ext_DWAIT3 | 0 | 2 | 0035 017A |
| `$3003` | ext_DWAIT3 | 1 | 2 | 003B 03D9 03DC |
| `$3004` | ext_DWAIT3 | 0 | 1 | 00DF |
| `$3005` | ext_DWAIT3 | 0 | 1 | 00E1 |
| `$3006` | ext_DWAIT3 | 0 | 1 | 00E3 |
| `$3007` | ext_DWAIT3 | 0 | 1 | 00E5 |
| `$300C` | ext_DWAIT3 | 0 | 1 | 0104 |
| `$300D` | ext_DWAIT3 | 0 | 1 | 010B |
| `$3021` | ext_DWAIT3 | 2 | 3 | 0007 00D3 0150 0159 0167 |
| `$3022` | ext_DWAIT3 | 2 | 2 | 00C7 00D7 0168 0173 |
| `$3023` | ext_DWAIT3 | 1 | 4 | 00CB 00D2 015D 0175 0180 |
| `$3025` | ext_DWAIT3 | 0 | 2 | 0223 03F4 |
| `$3029` | ext_DWAIT3 | 2 | 0 | 0198 0199 |
| `$3030` | ext_DWAIT3 | 3 | 0 | 0024 00CC 015F |
| `$3031` | ext_DWAIT3 | 1 | 0 | 023E |
| `$3033` | ext_DWAIT3 | 0 | 1 | 03F6 |
| `$303F` | ext_DWAIT3 | 1 | 1 | 0040 01E2 |
| `$3200` | ext_DWAIT3 | 0 | 2 | 003F 01FA |
| `$3400` | ext_DWAIT4 | 1 | 0 | 0039 |
| `$3800` | int_ram | 1 | 2 | 0061 0152 0181 |
| `$3808` | int_ram | 1 | 0 | 0245 |
| `$380C` | int_ram | 1 | 0 | 0249 |
| `$380E` | int_ram | 0 | 1 | 036E |
| `$3813` | int_ram | 0 | 1 | 036C |
| `$3816` | int_ram | 1 | 1 | 0385 039C |
| `$3832` | int_ram | 1 | 0 | 03EB |
| `$3833` | int_ram | 1 | 0 | 03EF |
| `$3834` | int_ram | 2 | 0 | 0034 0185 |
| `$3835` | int_ram | 1 | 0 | 013F |
| `$3852` | int_ram | 1 | 0 | 01BC |
| `$3857` | int_ram | 1 | 0 | 01C5 |
| `$3868` | int_ram | 0 | 1 | 018C |
| `$3869` | int_ram | 0 | 1 | 018D |
| `$386F` | int_ram | 0 | 1 | 018E |
| `$3870` | int_ram | 0 | 1 | 018F |
| `$3878` | int_ram | 0 | 1 | 0193 |
| `$3879` | int_ram | 0 | 1 | 0194 |
| `$387F` | int_ram | 0 | 1 | 0195 |
| `$3880` | int_ram | 0 | 1 | 0196 |
| `$3884` | int_ram | 1 | 1 | 0026 002D |
| `$3885` | int_ram | 2 | 1 | 0029 0030 0090 |
| `$3896` | int_ram | 1 | 0 | 0202 |
| `$3897` | int_ram | 1 | 0 | 0207 |
| `$38A8` | int_ram | 1 | 0 | 0142 |
| `$38A9` | int_ram | 1 | 0 | 0148 |
| `$38AC` | int_ram | 1 | 0 | 0141 |
| `$38AD` | int_ram | 1 | 0 | 0147 |
| `$38AE` | int_ram | 1 | 1 | 0005 0224 |
| `$38AF` | int_ram | 1 | 1 | 019E 0203 |
| `$38B0` | int_ram | 1 | 1 | 01A3 0208 |
| `$38B1` | int_ram | 6 | 4 | 0062 00FE 0154 0179 0188 0219 0221 024D … |
| `$38B7` | int_ram | 1 | 1 | 01C0 0204 |
| `$38B8` | int_ram | 1 | 1 | 01C9 0209 |
| `$38BD` | int_ram | 1 | 2 | 003E 01CB 01F9 |
| `$38C4` | int_ram | 1 | 1 | 01D1 01D7 |
| `$38CF` | int_ram | 3 | 2 | 01EF 01F3 0373 03CE 03E4 |
| `$38D0` | int_ram | 1 | 1 | 01F2 03E5 |
| `$38D1` | int_ram | 1 | 2 | 00C8 0170 0172 |
| `$38D2` | int_ram | 1 | 2 | 000E 0370 0387 |

### Indirect DM accesses with a known I-register value

| addr | region / name | reads | writes | at PM |
|---|---|---|---|---|
| `$3000` | ext_DWAIT3 | 1 | 0 | 0046 |
| `$3016` | ext_DWAIT3 | 0 | 1 | 001F |
| `$3017` | ext_DWAIT3 | 0 | 1 | 0020 |
| `$3018` | ext_DWAIT3 | 0 | 1 | 0021 |
| `$3019` | ext_DWAIT3 | 0 | 1 | 0022 |
| `$3021` | ext_DWAIT3 | 0 | 1 | 003C |
| `$302D` | ext_DWAIT3 | 2 | 0 | 019A 019B |
| `$3038` | ext_DWAIT3 | 0 | 1 | 001A |
| `$3039` | ext_DWAIT3 | 0 | 1 | 0019 |
| `$303A` | ext_DWAIT3 | 0 | 1 | 0018 |
| `$303B` | ext_DWAIT3 | 0 | 1 | 0017 |
| `$303C` | ext_DWAIT3 | 0 | 1 | 0016 |
| `$3804` | int_ram | 1 | 0 | 013C |
| `$380D` | int_ram | 1 | 0 | 01A8 |
| `$380E` | int_ram | 1 | 1 | 038B 0390 |
| `$380F` | int_ram | 1 | 1 | 039E 03A3 |
| `$3810` | int_ram | 1 | 1 | 03A0 03A4 |
| `$3811` | int_ram | 1 | 1 | 03A6 03AB |
| `$3812` | int_ram | 2 | 1 | 03A8 03AD 03B0 |
| `$3813` | int_ram | 0 | 1 | 03B3 |
| `$3814` | int_ram | 0 | 1 | 03B4 |
| `$3815` | int_ram | 0 | 1 | 03B5 |
| `$3888` | int_ram | 1 | 1 | 0047 0049 |
| `$3894` | int_ram | 1 | 0 | 0100 |
| `$389E` | int_ram | 1 | 0 | 00ED |
| `$389F` | int_ram | 1 | 0 | 00EE |
| `$38A0` | int_ram | 1 | 0 | 00EF |
| `$38A1` | int_ram | 1 | 0 | 00F0 |
| `$38A2` | int_ram | 1 | 0 | 00F1 |
| `$38B1` | int_ram | 1 | 1 | 01A6 01A9 |
| `$38BE` | int_ram | 1 | 0 | 0009 |
| `$38BF` | int_ram | 1 | 0 | 000A |
| `$38C9` | int_ram | 1 | 1 | 03BF 03C0 |
| `$38CA` | int_ram | 1 | 1 | 03C1 03C2 |
| `$38CB` | int_ram | 0 | 1 | 03C3 |
| `$38CC` | int_ram | 1 | 1 | 03C5 03C6 |
| `$38CD` | int_ram | 1 | 1 | 03C7 03C8 |
| `$3FFF` | SYSCNTL | 0 | 2 | 0001 03FA |

### Flag-pin changes

- `0153` RESET FLAG_OUT 
- `0183` IF EQ RESET FLAG_OUT 
- `0184` IF NE SET FLAG_OUT 

### Most-called subroutines

- `0120` ×4
- `024F` ×4
- `036B` ×3
- `031D` ×3
- `00A3` ×2
- `0068` ×2
- `0372` ×2
- `010E` ×2
- `031E` ×2
- `02A0` ×2
- `02F5` ×2
- `02FF` ×2
- `025B` ×2
- `0118` ×2
- `026D` ×2

## Boot page 2 (72 words)

### Direct DM accesses `DM($addr)`

| addr | region / name | reads | writes | at PM |
|---|---|---|---|---|
| `$3025` | ext_DWAIT3 | 0 | 1 | 001E |
| `$3200` | ext_DWAIT3 | 0 | 2 | 001C 0031 |

### Indirect DM accesses with a known I-register value

| addr | region / name | reads | writes | at PM |
|---|---|---|---|---|
| `$3000` | ext_DWAIT3 | 1 | 1 | 001A 0030 |
| `$3001` | ext_DWAIT3 | 0 | 1 | 001B |
| `$3033` | ext_DWAIT3 | 0 | 1 | 002B |
| `$3034` | ext_DWAIT3 | 0 | 1 | 002A |
| `$3035` | ext_DWAIT3 | 0 | 1 | 0029 |
| `$3036` | ext_DWAIT3 | 0 | 1 | 0028 |
| `$303C` | ext_DWAIT3 | 0 | 1 | 0027 |
| `$3400` | ext_DWAIT4 | 1 | 0 | 0035 |
| `$3FFF` | SYSCNTL | 0 | 1 | 0001 |

### Flag-pin changes


### Most-called subroutines

- `0038` ×4

