; ---- boot page 0: 192 words loaded at PM $0000 ----
  ; -- vector slot RESET --
  0000: 340004  M0 = $0000                                  
  0001: 340008  L0 = $0000                                  
  0002: 340015  M1 = $0001                                  
  0003: 340009  L1 = $0000                                  
  ; -- vector slot IRQ2 --
  0004: 37FFF6  M2 = $3FFF                                  
  0005: 34000A  L2 = $0000                                  
  0006: 340007  M3 = $0000                                  
  0007: 34000B  L3 = $0000                                  
  ; -- vector slot SPORT0_TX --
  0008: 380004  M4 = $0000                                  
  0009: 380008  L4 = $0000                                  
  000A: 380015  M5 = $0001                                  
  000B: 380009  L5 = $0000                                  
  ; -- vector slot SPORT0_RX --
  000C: 3BFFF6  M6 = $3FFF                                  
  000D: 38000A  L6 = $0000                                  
  000E: 380007  M7 = $0000                                  
  000F: 38000B  L7 = $0000                                  
  ; -- vector slot IRQ1_SPORT1_TX --
  0010: 37FF41  I1 = $3FF4                                  ; SP0_RFSDIV
  0011: A000F5  DM(I1,M1) = $000F                           ; I1=$3FF4 SP0_RFSDIV
  0012: A001B5  DM(I1,M1) = $001B                           ; I1=$3FF5 SP0_SCLKDIV
  0013: A410F5  DM(I1,M1) = $410F                           ; I1=$3FF6 SP0_CTRL
  ; -- vector slot IRQ0_SPORT1_RX --
  0014: 37FFE1  I1 = $3FFE                                  ; DM_WAIT
  0015: A253F5  DM(I1,M1) = $253F                           ; I1=$3FFE DM_WAIT
  0016: 3C0064  ICNTL = $0006                               
  0017: 0CBC88  DIS BIT_REV ENA AR_SAT ENA M_MODE DIS TIMER DIS G_MODE
  ; -- vector slot TIMER --
  0018: 370210  I0 = $3021                                  
  0019: A00600  DM(I0,M0) = $0060                           ; I0=$3021 ext_DWAIT3
  001A: A00830  DM(I0,M0) = $0083                           ; I0=$3021 ext_DWAIT3
  001B: 400000  AX0 = $0000                                 
  001C: 930220  DM($3022) = AX0                             ; ext_DWAIT3
  001D: 400061  AX1 = $0006                                 
  001E: 930231  DM($3023) = AX1                             ; ext_DWAIT3
  001F: 400071  AX1 = $0007                                 
  0020: 930241  DM($3024) = AX1                             ; ext_DWAIT3
  0021: 930251  DM($3025) = AX1                             ; ext_DWAIT3
  0022: 40808A  AR = $0808                                  
  0023: 9302FA  DM($302F) = AR                              ; ext_DWAIT3
  0024: 930320  DM($3032) = AX0                             ; ext_DWAIT3
  0025: 83400A  AR = DM($3400)                              ; ext_DWAIT4
  0026: 378001  I1 = $3800                                  
  0027: 3C2005  CNTR = $0200                                
  0028: 14029E  DO $0029 UNTIL CE                           
  0029: A00005  DM(I1,M1) = $0000                           ; I1=$3800..$39FF x512 int_ram
  002A: 370001  I1 = $3000                                  
  002B: 3C0205  CNTR = $0020                                
  002C: 1402DE  DO $002D UNTIL CE                           
  002D: A00005  DM(I1,M1) = $0000                           ; I1=$3000..$301F x32 ext_DWAIT3
  002E: A00800  DM(I0,M0) = $0080                           ; I0=$3021 ext_DWAIT3
  002F: 3FFFF5  CNTR = $3FFF                                
  0030: 14046E  DO $0046 UNTIL CE                           
  0031: 40080A  AR = $0080                                  
  0032: 93025A  DM($3025) = AR                              ; ext_DWAIT3
  0033: 4FFFFA  AR = $FFFF                                  
  0034: 93200A  DM($3200) = AR                              ; ext_DWAIT3
  0035: 429AA6  MY0 = $29AA                                 

loc_0036:
  0036: 83023A  AR = DM($3023)                              ; ext_DWAIT3
  0037: 830234  AY0 = DM($3023)                             ; ext_DWAIT3
  0038: 22E20F  AR = AR - AY0                               
  0039: 180361  IF NE JUMP loc_0036                         
  003A: 0D0084  SI = AY0                                    
  003B: 400890  AX0 = $0089                                 
  003C: 400074  AY0 = $0007                                 
  003D: 0F00FD  SR = LSHIFT SI BY -3 (HI)                   
  003E: 27870F  AF = SR1 AND AY0                            
  003F: 22700F  AR = AX0 + AF                               
  0040: 0D080A  I4 = AR                                     
  0041: 0F00FA  SR = LSHIFT SI BY -6 (HI)                   
  0042: 578720  AF = SR1 AND AY0, MX0 = PM(I4,M4)           
  0043: 2A7002  AR = AX0 + AF, AX0 = MX0                    
  0044: 0D080A  I4 = AR                                     
  0045: 502030  MR = MX0 * MY0 (RND), MX1 = PM(I4,M4)       
  0046: 000000  NOP                                         
  0047: 93029C  DM($3029) = MR1                             ; ext_DWAIT3
  0048: 282113  MR = MX1 * MY0 (RND), AX1 = MX1             
  0049: 9302DC  DM($302D) = MR1                             ; ext_DWAIT3
  004A: 40400A  AR = $0400                                  
  004B: 26780F  AF = AX0                                    
  004C: 221801  IF NE AR = 0                                
  004D: 408004  AY0 = $0800                                 
  004E: 26790F  AF = AX1                                    
  004F: 23A200  IF EQ AR = AR OR AY0                        
  0050: 93834A  DM($3834) = AR                              ; int_ram
  0051: 380920  I4 = $0092                                  
  0052: 3781A0  I0 = $381A                                  
  0053: 3C0185  CNTR = $0018                                
  0054: 14056E  DO $0056 UNTIL CE                           
  0055: 5000A1  AR = PM(I4,M5)                              
  0056: 6800A1  DM(I0,M1) = AR                              ; I0=$381A int_ram
  0057: 380AA0  I4 = $00AA                                  
  0058: 378380  I0 = $3838                                  
  0059: 3C0055  CNTR = $0005                                
  005A: 1405CE  DO $005C UNTIL CE                           
  005B: 5000A1  AR = PM(I4,M5)                              
  005C: 6800A1  DM(I0,M1) = AR                              ; I0=$3838 int_ram
  005D: 380AF0  I4 = $00AF                                  
  005E: 378580  I0 = $3858                                  
  005F: 3C00C5  CNTR = $000C                                
  0060: 14062E  DO $0062 UNTIL CE                           
  0061: 5000A1  AR = PM(I4,M5)                              
  0062: 6800A1  DM(I0,M1) = AR                              ; I0=$3858 int_ram
  0063: 378021  I1 = $3802                                  
  0064: A00005  DM(I1,M1) = $0000                           ; I1=$3802 int_ram
  0065: A00005  DM(I1,M1) = $0000                           
  0066: 3784E1  I1 = $384E                                  
  0067: A7DF35  DM(I1,M1) = $7DF3                           ; I1=$384E int_ram
  0068: A20005  DM(I1,M1) = $2000                           
  0069: 378531  I1 = $3853                                  
  006A: A7DF35  DM(I1,M1) = $7DF3                           ; I1=$3853 int_ram
  006B: A20005  DM(I1,M1) = $2000                           
  006C: 406000  AX0 = $0600                                 
  006D: 938040  DM($3804) = AX0                             ; int_ram
  006E: 406000  AX0 = $0600                                 
  006F: 938350  DM($3835) = AX0                             ; int_ram
  0070: 378A81  I1 = $38A8                                  
  0071: A38485  DM(I1,M1) = $3848                           ; I1=$38A8 int_ram
  0072: A38655  DM(I1,M1) = $3865                           
  0073: A384D5  DM(I1,M1) = $384D                           
  0074: A38755  DM(I1,M1) = $3875                           
  0075: A00805  DM(I1,M1) = $0080                           
  0076: A00805  DM(I1,M1) = $0080                           
  0077: 0C2000  DIS M_MODE                                  
  0078: 83021A  AR = DM($3021)                              ; ext_DWAIT3
  0079: 4E0004  AY0 = $E000                                 
  007A: 23820F  AR = AR AND AY0                             
  007B: 180821  IF NE JUMP loc_0082                         
  007C: 3C1F45  CNTR = $01F4                                
  007D: 14081E  DO $0081 UNTIL CE                           
  007E: 3C6405  CNTR = $0640                                
  007F: 14080E  DO $0080 UNTIL CE                           
  0080: 000000  NOP                                         
  0081: 000000  NOP                                         

loc_0082:
  0082: 37FFF1  I1 = $3FFF                                  ; SYSCNTL
  0083: A02585  DM(I1,M1) = $0258                           ; I1=$3FFF SYSCNTL
  0084: 000800  ??? (000800)                                
  0085: 002000  ??? (002000)                                
  0086: 008000  ??? (008000)                                
  0087: 020000  IF EQ                                       
  0088: 080000  ??? (080000)                                
  0089: 000000  NOP                                         
  008A: 040000  NOP                                         
  008B: 080000  ??? (080000)                                
  008C: 060000  DIVS AY0,AX0                                
  008D: 0C0000                                              
  008E: 020000  IF EQ                                       
  008F: 0A0000  IF EQ RTS                                   
  0090: 000000  NOP                                         
  0091: 20C400  IF EQ MR = MR1 * MY0 (US)                   
  0092: 000100  ??? (000100)                                
  0093: 000200  ??? (000200)                                
  0094: 000400  ??? (000400)                                
  0095: 000800  ??? (000800)                                
  0096: 001000  ??? (001000)                                
  0097: 000500  ??? (000500)                                
  0098: 000A00  ??? (000A00)                                
  0099: 001400  ??? (001400)                                
  009A: 000D00  ??? (000D00)                                
  009B: 001A00  ??? (001A00)                                
  009C: 001100  ??? (001100)                                
  009D: 000700  ??? (000700)                                
  009E: 000E00  ??? (000E00)                                
  009F: 001C00  ??? (001C00)                                
  00A0: 001D00  ??? (001D00)                                
  00A1: 001F00  ??? (001F00)                                
  00A2: 001B00  ??? (001B00)                                
  00A3: 001300  ??? (001300)                                
  00A4: 000300  ??? (000300)                                
  00A5: 000600  ??? (000600)                                
  00A6: 000C00  ??? (000C00)                                
  00A7: 001800  ??? (001800)                                
  00A8: 001500  ??? (001500)                                
  00A9: 000000  NOP                                         
  00AA: 324000  AX0 = $2400                                 
  00AB: 005300  ??? (005300)                                
  00AC: AACC00  DM(I0,M0) = $ACC0                           
  00AD: 08B700  ??? (08B700)                                
  00AE: 1CCE00  IF EQ CALL sub_0CE0                         
  00AF: 002900  ??? (002900)                                
  00B0: 103900  SR = SR OR ASHIFT ?? (LO), AX0 = AX0        
  00B1: 207300  IF EQ MR = MR - MR0 * MF (RND)              
  00B2: 003500  ??? (003500)                                
  00B3: 137000  SE = EXP SI (LO), AX0 = DM(I4,M4)           
  00B4: 26E000  IF EQ AF = AX0 - AY0                        
  00B5: 002300  ??? (002300)                                
  00B6: 0CF500  ENA M_MODE ENA TIMER                        
  00B7: 19EA00  IF EQ JUMP loc_1EA0                         
  00B8: 008300  ??? (008300)                                
  00B9: 09D300  ??? (09D300)                                
  00BA: 13A700  SR = ASHIFT SR1 (HI), DM(I4,M4) = AX0       
  00BB: FFFFFF  AR = ABS SR1, MX1 = DM(I3,M3), MY1 = PM(I7,M7)
  00BC: FFFFFF  AR = ABS SR1, MX1 = DM(I3,M3), MY1 = PM(I7,M7)
  00BD: FFFFFF  AR = ABS SR1, MX1 = DM(I3,M3), MY1 = PM(I7,M7)
  00BE: FFFFFF  AR = ABS SR1, MX1 = DM(I3,M3), MY1 = PM(I7,M7)
  00BF: FFFFFF  AR = ABS SR1, MX1 = DM(I3,M3), MY1 = PM(I7,M7)

; ---- boot page 1: 1024 words loaded at PM $0000 ----
; assumed at entry (left by page 0): M0=0, M1=1, M2=-1, M3=0, M4=0, M5=1, M6=-1, M7=0
  ; -- vector slot RESET --
  0000: 37FFF1  I1 = $3FFF                                  ; SYSCNTL
  0001: A101A5  DM(I1,M1) = $101A                           ; I1=$3FFF SYSCNTL
  0002: 3C0065  CNTR = $0006                                
  0003: 18014F  JUMP loc_0014                               
  ; -- vector slot IRQ2 --
  0004: 0C0830  ENA SEC_REG DIS AR_SAT                      
  0005: 9B8AE3  DM($38AE) = I7                              ; int_ram
  0006: 400030  AX0 = $0003                                 
  0007: 930210  DM($3021) = AX0                             ; ext_DWAIT3
  ; -- vector slot SPORT0_TX --
  0008: 3B8BE0  I4 = $38BE                                  
  0009: 700041  AY0 = DM(I4,M5)                             ; I4=$38BE int_ram
  000A: 700002  AX0 = DM(I4,M6)                             ; I4=$38BF int_ram
  000B: 1815FF  JUMP loc_015F                               
  ; -- vector slot SPORT0_RX --
  000C: 0C0030  ENA SEC_REG                                 
  000D: 0D0348  AY0 = RX0                                   
  000E: 8B8D20  I4 = DM($38D2)                              ; int_ram
  000F: 0B000F  JUMP (I4)                                   
  ; -- vector slot IRQ1_SPORT1_TX --
  0010: 0C0C30  ENA SEC_REG ENA AR_SAT                      
  0011: 374001  I1 = $3400                                  
  0012: 378442  I2 = $3844                                  
  0013: 18128F  JUMP loc_0128                               
  ; -- vector slot IRQ0_SPORT1_RX --

loc_0014:
  0014: 3703C1  I1 = $303C                                  
  0015: 14016E  DO $0016 UNTIL CE                           
  0016: A01F46  DM(I1,M2) = $01F4                           ; I1=$303C ext_DWAIT3
  0017: A00006  DM(I1,M2) = $0000                           ; I1=$303B ext_DWAIT3
  ; -- vector slot TIMER --
  0018: A0FFF6  DM(I1,M2) = $0FFF                           ; I1=$303A ext_DWAIT3
  0019: A000F6  DM(I1,M2) = $000F                           ; I1=$3039 ext_DWAIT3
  001A: A03E86  DM(I1,M2) = $03E8                           ; I1=$3038 ext_DWAIT3
  001B: 370161  I1 = $3016                                  
  001C: 340027  M3 = $0002                                  
  001D: 3C0025  CNTR = $0002                                
  001E: 14022E  DO $0022 UNTIL CE                           
  001F: A00005  DM(I1,M1) = $0000                           ; I1=$3016 ext_DWAIT3
  0020: A80005  DM(I1,M1) = $8000                           ; I1=$3017 ext_DWAIT3
  0021: A00005  DM(I1,M1) = $0000                           ; I1=$3018 ext_DWAIT3
  0022: A80007  DM(I1,M3) = $8000                           ; I1=$3019 ext_DWAIT3
  0023: 4000F4  AY0 = $000F                                 
  0024: 83030E  SR0 = DM($3030)                             ; ext_DWAIT3
  0025: 23860F  AR = SR0 AND AY0                            
  0026: 93884A  DM($3884) = AR                              ; int_ram
  0027: 0F16F8  SR = LSHIFT SR0 BY -8 (LO)                  
  0028: 2B860A  AR = SR0 AND AY0, AX0 = AR                  
  0029: 93885A  DM($3885) = AR                              ; int_ram
  002A: 1C07AF  CALL sub_007A                               
  002B: 378980  I0 = $3898                                  
  002C: 1C0A3F  CALL sub_00A3                               
  002D: 83884A  AR = DM($3884)                              ; int_ram
  002E: 3701A1  I1 = $301A                                  
  002F: 1C068F  CALL sub_0068                               
  0030: 83885A  AR = DM($3885)                              ; int_ram
  0031: 3701F1  I1 = $301F                                  
  0032: 1C068F  CALL sub_0068                               
  0033: 370210  I0 = $3021                                  
  0034: 83834A  AR = DM($3834)                              ; int_ram
  0035: 93002A  DM($3002) = AR                              ; ext_DWAIT3
  0036: 1C372F  CALL sub_0372                               
  0037: 3C03FC  IFC = $003F                                 
  0038: 3C02C3  IMASK = $002C                               
  0039: 83400A  AR = DM($3400)                              ; ext_DWAIT4
  003A: 4FFFFA  AR = $FFFF                                  
  003B: 93003A  DM($3003) = AR                              ; ext_DWAIT3
  003C: A00610  DM(I0,M0) = $0061                           ; I0=$3021 ext_DWAIT3
  003D: 4FFFCA  AR = $FFFC                                  
  003E: 938BDA  DM($38BD) = AR                              ; int_ram
  003F: 93200A  DM($3200) = AR                              ; ext_DWAIT3
  0040: 9303FA  DM($303F) = AR                              ; ext_DWAIT3

loc_0041:
  0041: 0C2800  DIS AR_SAT DIS M_MODE                       
  0042: 3B0003  I7 = $3000                                  
  0043: 378880  I0 = $3888                                  
  0044: 3C0205  CNTR = $0020                                
  0045: 14047E  DO $0047 UNTIL CE                           
  0046: 7000AD  AR = DM(I7,M5)                              ; I7=$3000 ext_DWAIT3
  0047: 6800A1  DM(I0,M1) = AR                              ; I0=$3888 int_ram
  0048: 3B8883  I7 = $3888                                  
  0049: 70000D  AX0 = DM(I7,M5)                             ; I7=$3888 int_ram
  004A: 4C0004  AY0 = $C000                                 
  004B: 23800F  AR = AX0 AND AY0                            
  004C: 180DC0  IF EQ JUMP loc_00DC                         
  004D: 22E20F  AR = AR - AY0                               
  004E: 180A90  IF EQ JUMP loc_00A9                         
  004F: 480014  AY0 = $8001                                 
  0050: 22E00F  AR = AX0 - AY0                              
  0051: 180C60  IF EQ JUMP loc_00C6                         
  0052: 480004  AY0 = $8000                                 
  0053: 22E00F  AR = AX0 - AY0                              
  0054: 180610  IF EQ JUMP loc_0061                         
  0055: 410024  AY0 = $1002                                 
  0056: 26E20F  AF = AR - AY0                               
  0057: 180610  IF EQ JUMP loc_0061                         
  0058: 400024  AY0 = $0002                                 
  0059: 26E20F  AF = AR - AY0                               
  005A: 180610  IF EQ JUMP loc_0061                         
  005B: 400044  AY0 = $0004                                 
  005C: 26E20F  AF = AR - AY0                               
  005D: 180610  IF EQ JUMP loc_0061                         
  005E: 400065  AY1 = $0006                                 
  005F: 26EA0F  AF = AR - AY1                               
  0060: 180DC1  IF NE JUMP loc_00DC                         

loc_0061:
  0061: 93800A  DM($3800) = AR                              ; int_ram
  0062: 838B14  AY0 = DM($38B1)                             ; int_ram
  0063: 23C20F  AR = AR XOR AY0                             
  0064: 400064  AY0 = $0006                                 
  0065: 23820F  AR = AR AND AY0                             
  0066: 180DA0  IF EQ JUMP loc_00DA                         
  0067: 180DCF  JUMP loc_00DC                               

sub_0068:
  0068: 4000C4  AY0 = $000C                                 
  0069: 432150  AX0 = $3215                                 
  006A: 26E20F  AF = AR - AY0                               
  006B: 180780  IF EQ JUMP loc_0078                         
  006C: 4000A4  AY0 = $000A                                 
  006D: 400000  AX0 = $0000                                 
  006E: 26E20F  AF = AR - AY0                               
  006F: 180780  IF EQ JUMP loc_0078                         
  0070: 400094  AY0 = $0009                                 
  0071: 421150  AX0 = $2115                                 
  0072: 26E20F  AF = AR - AY0                               
  0073: 180780  IF EQ JUMP loc_0078                         
  0074: 400084  AY0 = $0008                                 
  0075: 432150  AX0 = $3215                                 
  0076: 26E20F  AF = AR - AY0                               
  0077: 0A0001  IF NE RTS                                   

loc_0078:
  0078: 680004  DM(I1,M0) = AX0                             
  0079: 0A000F  RTS                                         

sub_007A:
  007A: 383FD0  I4 = $03FD                                  
  007B: 3C0025  CNTR = $0002                                
  007C: 1408DE  DO $008D UNTIL CE                           
  007D: 4000C4  AY0 = $000C                                 
  007E: 56E210  AF = AR - AY0, AX1 = PM(I4,M4)              
  007F: 180811  IF NE JUMP loc_0081                         
  0080: 44F201  AX1 = $4F20                                 

loc_0081:
  0081: 4000A4  AY0 = $000A                                 
  0082: 26E20F  AF = AR - AY0                               
  0083: 180851  IF NE JUMP loc_0085                         
  0084: 434E01  AX1 = $34E0                                 

loc_0085:
  0085: 400094  AY0 = $0009                                 
  0086: 26E20F  AF = AR - AY0                               
  0087: 180891  IF NE JUMP loc_0089                         
  0088: 46D601  AX1 = $6D60                                 

loc_0089:
  0089: 400084  AY0 = $0008                                 
  008A: 26E20F  AF = AR - AY0                               
  008B: 1808D1  IF NE JUMP loc_008D                         
  008C: 44D801  AX1 = $4D80                                 

loc_008D:
  008D: 5A7812  AR = AX0, PM(I4,M6) = AX1                   
  008E: 370100  I0 = $3010                                  
  008F: 1C091F  CALL sub_0091                               
  0090: 83885A  AR = DM($3885)                              ; int_ram

sub_0091:
  0091: 4000C5  AY1 = $000C                                 
  0092: 3B8613  I7 = $3861                                  
  0093: 26EA0F  AF = AR - AY1                               
  0094: 1809E0  IF EQ JUMP loc_009E                         
  0095: 4000A5  AY1 = $000A                                 
  0096: 3B85E3  I7 = $385E                                  
  0097: 26EA0F  AF = AR - AY1                               
  0098: 1809E0  IF EQ JUMP loc_009E                         
  0099: 400095  AY1 = $0009                                 
  009A: 3B85B3  I7 = $385B                                  
  009B: 26EA0F  AF = AR - AY1                               
  009C: 1809E0  IF EQ JUMP loc_009E                         
  009D: 3B8583  I7 = $3858                                  

loc_009E:
  009E: 3C0035  CNTR = $0003                                
  009F: 140A1E  DO $00A1 UNTIL CE                           
  00A0: 70000D  AX0 = DM(I7,M5)                             
  00A1: 680001  DM(I0,M1) = AX0                             
  00A2: 0A000F  RTS                                         

sub_00A3:
  00A3: 383513  I7 = $0351                                  
  00A4: 3C0065  CNTR = $0006                                
  00A5: 140A7E  DO $00A7 UNTIL CE                           
  00A6: 600001  AX0 = DM(I0,M1)                             
  00A7: 58000D  PM(I7,M5) = AX0                             
  00A8: 0A000F  RTS                                         

loc_00A9:
  00A9: 0D0080  SI = AX0                                    
  00AA: 0F2004  SR = ASHIFT SI BY 4 (HI)                    
  00AB: 0F27FE  SR = ASHIFT SR1 BY -2 (HI)                  
  00AC: 0F07FE  SR = LSHIFT SR1 BY -2 (HI)                  
  00AD: 4F0005  AY1 = $F000                                 
  00AE: 4C0004  AY0 = $C000                                 
  00AF: 73881D  AR = AX0 AND AY1, AX1 = DM(I7,M5)           
  00B0: 26E20F  AF = AR - AY0                               
  00B1: 0D083F  I7 = SR1                                    
  00B2: 180BF0  IF EQ JUMP loc_00BF                         
  00B3: 4D0004  AY0 = $D000                                 
  00B4: 26E20F  AF = AR - AY0                               
  00B5: 180DC1  IF NE JUMP loc_00DC                         
  00B6: 830014  AY0 = DM($3001)                             ; ext_DWAIT3
  00B7: 23C10F  AR = AX1 XOR AY0                            
  00B8: 180DC1  IF NE JUMP loc_00DC                         
  00B9: 238F0F  AR = SR1 AND AY1                            
  00BA: 180BD0  IF EQ JUMP loc_00BD                         
  00BB: 78001C  DM(I7,M4) = AX1                             
  00BC: 180DAF  JUMP loc_00DA                               

loc_00BD:
  00BD: 58001C  PM(I7,M4) = AX1                             
  00BE: 180DAF  JUMP loc_00DA                               

loc_00BF:
  00BF: 238F0F  AR = SR1 AND AY1                            
  00C0: 180C30  IF EQ JUMP loc_00C3                         
  00C1: 7000AD  AR = DM(I7,M5)                              
  00C2: 180C4F  JUMP loc_00C4                               

loc_00C3:
  00C3: 5000AD  AR = PM(I7,M5)                              

loc_00C4:
  00C4: 93001A  DM($3001) = AR                              ; ext_DWAIT3
  00C5: 180DAF  JUMP loc_00DA                               

loc_00C6:
  00C6: 40000A  AR = $0000                                  
  00C7: 93022A  DM($3022) = AR                              ; ext_DWAIT3
  00C8: 938D1A  DM($38D1) = AR                              ; int_ram
  00C9: 030D12  IF FLAG_IN JUMP loc_00D1                    
  00CA: 400070  AX0 = $0007                                 
  00CB: 930230  DM($3023) = AX0                             ; ext_DWAIT3
  00CC: 83030A  AR = DM($3030)                              ; ext_DWAIT3
  00CD: 23620F  AR = NOT AR                                 
  00CE: 410104  AY0 = $1010                                 
  00CF: 23820F  AR = AR AND AY0                             
  00D0: 180DC1  IF NE JUMP loc_00DC                         

loc_00D1:
  00D1: 400060  AX0 = $0006                                 
  00D2: 930230  DM($3023) = AX0                             ; ext_DWAIT3
  00D3: 83021A  AR = DM($3021)                              ; ext_DWAIT3
  00D4: 403804  AY0 = $0380                                 
  00D5: 23820F  AR = AR AND AY0                             
  00D6: 180DC1  IF NE JUMP loc_00DC                         
  00D7: 83022A  AR = DM($3022)                              ; ext_DWAIT3
  00D8: 227A0F  AR = AR                                     
  00D9: 180DC1  IF NE JUMP loc_00DC                         

loc_00DA:
  00DA: 40000A  AR = $0000                                  
  00DB: 93000A  DM($3000) = AR                              ; ext_DWAIT3

loc_00DC:
  00DC: 438004  AY0 = $3800                                 
  00DD: 378A80  I0 = $38A8                                  
  00DE: 1C120F  CALL sub_0120                               
  00DF: 93004A  DM($3004) = AR                              ; ext_DWAIT3
  00E0: 1C120F  CALL sub_0120                               
  00E1: 93005A  DM($3005) = AR                              ; ext_DWAIT3
  00E2: 1C120F  CALL sub_0120                               
  00E3: 93006A  DM($3006) = AR                              ; ext_DWAIT3
  00E4: 1C120F  CALL sub_0120                               
  00E5: 93007A  DM($3007) = AR                              ; ext_DWAIT3
  00E6: 378980  I0 = $3898                                  
  00E7: 1C0A3F  CALL sub_00A3                               
  00E8: 030F70  IF NOT FLAG_IN JUMP loc_00F7                
  00E9: 3789E0  I0 = $389E                                  
  00EA: 3832F3  I7 = $032F                                  
  00EB: 3C0025  CNTR = $0002                                
  00EC: 140F6E  DO $00F6 UNTIL CE                           
  00ED: 600001  AX0 = DM(I0,M1)                             ; I0=$389E int_ram
  00EE: 600011  AX1 = DM(I0,M1)                             ; I0=$389F int_ram
  00EF: 600041  AY0 = DM(I0,M1)                             ; I0=$38A0 int_ram
  00F0: 600051  AY1 = DM(I0,M1)                             ; I0=$38A1 int_ram
  00F1: 6000A1  AR = DM(I0,M1)                              ; I0=$38A2 int_ram
  00F2: 58000D  PM(I7,M5) = AX0                             
  00F3: 58004D  PM(I7,M5) = AY0                             
  00F4: 58001D  PM(I7,M5) = AX1                             
  00F5: 58005D  PM(I7,M5) = AY1                             
  00F6: 3833F3  I7 = $033F                                  

loc_00F7:
  00F7: 378A20  I0 = $38A2                                  
  00F8: 3B8B93  I7 = $38B9                                  
  00F9: 1C10EF  CALL sub_010E                               
  00FA: 378A70  I0 = $38A7                                  
  00FB: 1C10EF  CALL sub_010E                               
  00FC: 378940  I0 = $3894                                  
  00FD: 3B8023  I7 = $3802                                  
  00FE: 838B10  AX0 = DM($38B1)                             ; int_ram
  00FF: 401004  AY0 = $0100                                 
  0100: 678011  AF = AX0 AND AY0, AX1 = DM(I0,M1)           ; I0=$3894 int_ram
  0101: 181050  IF EQ JUMP loc_0105                         
  0102: 031050  IF NOT FLAG_IN JUMP loc_0105                
  0103: 400001  AX1 = $0000                                 
  0104: 9300C1  DM($300C) = AX1                             ; ext_DWAIT3

loc_0105:
  0105: 78001D  DM(I7,M5) = AX1                             
  0106: 402004  AY0 = $0200                                 
  0107: 678011  AF = AX0 AND AY0, AX1 = DM(I0,M1)           
  0108: 1810C0  IF EQ JUMP loc_010C                         
  0109: 0310C0  IF NOT FLAG_IN JUMP loc_010C                
  010A: 400001  AX1 = $0000                                 
  010B: 9300D1  DM($300D) = AX1                             ; ext_DWAIT3

loc_010C:
  010C: 78001D  DM(I7,M5) = AX1                             
  010D: 183EBF  JUMP loc_03EB                               

sub_010E:
  010E: 621801  AR = 0, AX0 = DM(I0,M1)                     
  010F: 4FF005  AY1 = $FF00                                 
  0110: 2B884A  AR = AX0 AND AY1, AY0 = AR                  
  0111: 400FF5  AY1 = $00FF                                 
  0112: 7B88AD  AR = AX0 AND AY1, DM(I7,M5) = AR            
  0113: 0D005A  AY1 = AR                                    
  0114: 410AA0  AX0 = $10AA                                 
  0115: 1C321F  CALL sub_0321                               
  0116: 78004D  DM(I7,M5) = AY0                             
  0117: 0A000F  RTS                                         

sub_0118:
  0118: 600005  AX0 = DM(I1,M1)                             
  0119: 633065  AR = AF - AX0, MY0 = DM(I1,M1)              
  011A: 221803  IF LE AR = 0                                
  011B: 0A0003  IF LE RTS                                   
  011C: 1C31EF  CALL sub_031E                               
  011D: 20820F  MR = AR * MY0 (SS)                          
  011E: 0D00AC  AR = MR1                                    
  011F: 0A000F  RTS                                         

sub_0120:
  0120: 6000A1  AR = DM(I0,M1)                              
  0121: 0D083A  I7 = AR                                     
  0122: 23820F  AR = AR AND AY0                             
  0123: 181260  IF EQ JUMP loc_0126                         
  0124: 7000AC  AR = DM(I7,M4)                              
  0125: 0A000F  RTS                                         

loc_0126:
  0126: 5000AC  AR = PM(I7,M4)                              
  0127: 0A000F  RTS                                         

loc_0128:
  0128: 378643  I3 = $3864                                  
  0129: 37FFB7  M3 = $3FFB                                  
  012A: 383510  I4 = $0351                                  
  012B: 3832F1  I5 = $032F                                  
  012C: 3B83E2  I6 = $383E                                  
  012D: 1C2A0F  CALL sub_02A0                               
  012E: 383540  I4 = $0354                                  
  012F: 1C2A0F  CALL sub_02A0                               
  0130: 37FFC7  M3 = $3FFC                                  
  0131: 378731  I1 = $3873                                  
  0132: 1C2F5F  CALL sub_02F5                               
  0133: 378831  I1 = $3883                                  
  0134: 1C2F5F  CALL sub_02F5                               
  0135: 3783E1  I1 = $383E                                  
  0136: 370372  I2 = $3037                                  
  0137: 378443  I3 = $3844                                  
  0138: 3832E0  I4 = $032E                                  
  0139: 3B8041  I5 = $3804                                  
  013A: 340037  M3 = $0003                                  
  013B: 4FFC0A  AR = $FFC0                                  
  013C: 767A45  AF = AR, AY0 = DM(I5,M5)                    ; I5=$3804 int_ram
  013D: 1C2FFF  CALL sub_02FF                               
  013E: 3B8091  I5 = $3809                                  
  013F: 838354  AY0 = DM($3835)                             ; int_ram
  0140: 1C2FFF  CALL sub_02FF                               
  0141: 838AC6  MY0 = DM($38AC)                             ; int_ram
  0142: 878A81  I1 = DM($38A8)                              ; int_ram
  0143: 609824  MR = 0, MX0 = DM(I1,M0)                     
  0144: 40080C  MR1 = $0080                                 
  0145: 21000F  MR = MR + MX0 * MY0 (SS)                    
  0146: 91000C  DM($1000) = MR1                             ; ext_DWAIT2
  0147: 838AD6  MY0 = DM($38AD)                             ; int_ram
  0148: 878A91  I1 = DM($38A9)                              ; int_ram
  0149: 609824  MR = 0, MX0 = DM(I1,M0)                     
  014A: 40080C  MR1 = $0080                                 
  014B: 21000F  MR = MR + MX0 * MY0 (SS)                    
  014C: 91001C  DM($1001) = MR1                             ; ext_DWAIT2
  014D: 0A001F  RTI                                         

loc_014E:
  014E: 031580  IF NOT FLAG_IN JUMP loc_0158                
  014F: 40081A  AR = $0081                                  
  0150: 93021A  DM($3021) = AR                              ; ext_DWAIT3

loc_0151:
  0151: 40000A  AR = $0000                                  
  0152: 93800A  DM($3800) = AR                              ; int_ram

loc_0153:
  0153: 02002F  RESET FLAG_OUT                              
  0154: 838B10  AX0 = DM($38B1)                             ; int_ram
  0155: 4FCF94  AY0 = $FCF9                                 
  0156: 23800F  AR = AX0 AND AY0                            
  0157: 1817AF  JUMP loc_017A                               

loc_0158:
  0158: 40080A  AR = $0080                                  
  0159: 830214  AY0 = DM($3021)                             ; ext_DWAIT3
  015A: 23820F  AR = AR AND AY0                             
  015B: 181511  IF NE JUMP loc_0151                         
  015C: 40007A  AR = $0007                                  
  015D: 93023A  DM($3023) = AR                              ; ext_DWAIT3
  015E: 18151F  JUMP loc_0151                               

loc_015F:
  015F: 83030A  AR = DM($3030)                              ; ext_DWAIT3
  0160: 7EE2A1  AF = AR - AY0, DM(I4,M5) = AR               
  0161: 227801  IF NE AR = AX0                              
  0162: 7B62A1  AR = NOT AR, DM(I4,M5) = AR                 
  0163: 410104  AY0 = $1010                                 
  0164: 23820F  AR = AR AND AY0                             
  0165: 1814E1  IF NE JUMP loc_014E                         
  0166: 40080A  AR = $0080                                  
  0167: 93021A  DM($3021) = AR                              ; ext_DWAIT3
  0168: 830220  AX0 = DM($3022)                             ; ext_DWAIT3
  0169: 400024  AY0 = $0002                                 
  016A: 23800F  AR = AX0 AND AY0                            
  016B: 181511  IF NE JUMP loc_0151                         
  016C: 400014  AY0 = $0001                                 
  016D: 23800F  AR = AX0 AND AY0                            
  016E: 181750  IF EQ JUMP loc_0175                         
  016F: 031720  IF NOT FLAG_IN JUMP loc_0172                
  0170: 938D1A  DM($38D1) = AR                              ; int_ram
  0171: 18151F  JUMP loc_0151                               

loc_0172:
  0172: 838D1A  AR = DM($38D1)                              ; int_ram
  0173: 93022A  DM($3022) = AR                              ; ext_DWAIT3
  0174: 18151F  JUMP loc_0151                               

loc_0175:
  0175: 830230  AX0 = DM($3023)                             ; ext_DWAIT3
  0176: 22780F  AR = AX0                                    
  0177: 181512  IF GT JUMP loc_0151                         
  0178: 031530  IF NOT FLAG_IN JUMP loc_0153                
  0179: 838B1A  AR = DM($38B1)                              ; int_ram

loc_017A:
  017A: 93002A  DM($3002) = AR                              ; ext_DWAIT3
  017B: 403004  AY0 = $0300                                 
  017C: 27820F  AF = AR AND AY0                             
  017D: 400064  AY0 = $0006                                 
  017E: 23820F  AR = AR AND AY0                             
  017F: 23C20F  AR = AR XOR AY0                             
  0180: 93023A  DM($3023) = AR                              ; ext_DWAIT3
  0181: 838000  AX0 = DM($3800)                             ; int_ram
  0182: 23800F  AR = AX0 AND AY0                            
  0183: 020020  IF EQ RESET FLAG_OUT                        
  0184: 020031  IF NE SET FLAG_OUT                          
  0185: 838344  AY0 = DM($3834)                             ; int_ram
  0186: 23A20F  AR = AR OR AY0                              
  0187: 23B20F  AR = AR OR AF                               
  0188: 938B1A  DM($38B1) = AR                              ; int_ram
  0189: 400024  AY0 = $0002                                 
  018A: 23800F  AR = AX0 AND AY0                            
  018B: 181901  IF NE JUMP loc_0190                         
  018C: 93868A  DM($3868) = AR                              ; int_ram
  018D: 93869A  DM($3869) = AR                              ; int_ram
  018E: 9386FA  DM($386F) = AR                              ; int_ram
  018F: 93870A  DM($3870) = AR                              ; int_ram

loc_0190:
  0190: 400044  AY0 = $0004                                 
  0191: 23800F  AR = AX0 AND AY0                            
  0192: 181971  IF NE JUMP loc_0197                         
  0193: 93878A  DM($3878) = AR                              ; int_ram
  0194: 93879A  DM($3879) = AR                              ; int_ram
  0195: 9387FA  DM($387F) = AR                              ; int_ram
  0196: 93880A  DM($3880) = AR                              ; int_ram

loc_0197:
  0197: 3702D2  I2 = $302D                                  
  0198: 830290  AX0 = DM($3029)                             ; ext_DWAIT3
  0199: 830294  AY0 = DM($3029)                             ; ext_DWAIT3
  019A: 62E018  AR = AX0 - AY0, AX1 = DM(I2,M0)             ; I2=$302D ext_DWAIT3
  019B: 67E258  AF = ABS AR, AY1 = DM(I2,M0)                ; I2=$302D ext_DWAIT3
  019C: 271001  IF NE AF = AF - 1                           
  019D: 1819F1  IF NE JUMP loc_019F                         
  019E: 938AF4  DM($38AF) = AY0                             ; int_ram

loc_019F:
  019F: 22E90F  AR = AX1 - AY1                              
  01A0: 27E20F  AF = ABS AR                                 
  01A1: 271001  IF NE AF = AF - 1                           
  01A2: 181A41  IF NE JUMP loc_01A4                         
  01A3: 938B05  DM($38B0) = AY1                             ; int_ram

loc_01A4:
  01A4: 3780D1  I1 = $380D                                  
  01A5: 378B12  I2 = $38B1                                  
  01A6: 6000A8  AR = DM(I2,M0)                              ; I2=$38B1 int_ram
  01A7: 4FF065  AY1 = $FF06                                 
  01A8: 638A44  AR = AR AND AY1, AY0 = DM(I1,M0)            ; I1=$380D int_ram
  01A9: 6B00A8  AR = AY0 - 1, DM(I2,M0) = AR                ; I2=$38B1 int_ram
  01AA: 181AC1  IF NE JUMP loc_01AC                         
  01AB: 40640A  AR = $0640                                  

loc_01AC:
  01AC: 6E7AA4  AF = AR, DM(I1,M0) = AR                     
  01AD: 6710A8  AF = AF - 1, AR = DM(I2,M0)                 
  01AE: 182270  IF EQ JUMP loc_0227                         
  01AF: 27100F  AF = AF - 1                                 
  01B0: 1822A0  IF EQ JUMP loc_022A                         
  01B1: 27100F  AF = AF - 1                                 
  01B2: 182340  IF EQ JUMP loc_0234                         
  01B3: 27100F  AF = AF - 1                                 
  01B4: 182370  IF EQ JUMP loc_0237                         
  01B5: 27100F  AF = AF - 1                                 
  01B6: 182440  IF EQ JUMP loc_0244                         

loc_01B7:
  01B7: 340027  M3 = $0002                                  
  01B8: 3832F0  I4 = $032F                                  
  01B9: 378C03  I3 = $38C0                                  
  01BA: 370162  I2 = $3016                                  
  01BB: 378441  I1 = $3844                                  
  01BC: 83852A  AR = DM($3852)                              ; int_ram
  01BD: 1C25BF  CALL sub_025B                               
  01BE: 378B91  I1 = $38B9                                  
  01BF: 1C118F  CALL sub_0118                               
  01C0: 938B7A  DM($38B7) = AR                              ; int_ram
  01C1: 3833F0  I4 = $033F                                  
  01C2: 378C23  I3 = $38C2                                  
  01C3: 3701B2  I2 = $301B                                  
  01C4: 378491  I1 = $3849                                  
  01C5: 83857A  AR = DM($3857)                              ; int_ram
  01C6: 1C25BF  CALL sub_025B                               
  01C7: 378BB1  I1 = $38BB                                  
  01C8: 1C118F  CALL sub_0118                               
  01C9: 938B8A  DM($38B8) = AR                              ; int_ram
  01CA: 400400  AX0 = $0040                                 
  01CB: 838BD5  AY1 = DM($38BD)                             ; int_ram
  01CC: 4FF83A  AR = $FF83                                  
  01CD: 278A0F  AF = AR AND AY1                             
  01CE: 031D02  IF FLAG_IN JUMP loc_01D0                    
  01CF: 27B00F  AF = AX0 OR AF                              

loc_01D0:
  01D0: 830000  AX0 = DM($3000)                             ; ext_DWAIT3
  01D1: 838C44  AY0 = DM($38C4)                             ; int_ram
  01D2: 2B00E0  AR = AY0 - 1, SR0 = AX0                     
  01D3: 181D72  IF GT JUMP loc_01D7                         
  01D4: 400801  AX1 = $0080                                 
  01D5: 27D10F  AF = AX1 XOR AF                             
  01D6: 42000A  AR = $2000                                  

loc_01D7:
  01D7: 938C4A  DM($38C4) = AR                              ; int_ram
  01D8: 407FF4  AY0 = $07FF                                 
  01D9: 23820F  AR = AR AND AY0                             
  01DA: 181E00  IF EQ JUMP loc_01E0                         
  01DB: 404004  AY0 = $0400                                 
  01DC: 22E20F  AR = AR - AY0                               
  01DD: 181E21  IF NE JUMP loc_01E2                         
  01DE: 480940  AX0 = $8094                                 
  01DF: 181E1F  JUMP loc_01E1                               

loc_01E0:
  01E0: 480920  AX0 = $8092                                 

loc_01E1:
  01E1: 0D00EA  SR0 = AR                                    

loc_01E2:
  01E2: 8303F4  AY0 = DM($303F)                             ; ext_DWAIT3
  01E3: 4003C1  AX1 = $003C                                 
  01E4: 23810F  AR = AX1 AND AY0                            
  01E5: 27B20F  AF = AR OR AF                               
  01E6: 4FFEF4  AY0 = $FFEF                                 
  01E7: 23800F  AR = AX0 AND AY0                            
  01E8: 480824  AY0 = $8082                                 
  01E9: 2AE21A  AR = AR - AY0, AX1 = AR                     
  01EA: 181EF0  IF EQ JUMP loc_01EF                         
  01EB: 480844  AY0 = $8084                                 
  01EC: 22E10F  AR = AX1 - AY0                              
  01ED: 181F81  IF NE JUMP loc_01F8                         
  01EE: 40001A  AR = $0001                                  

loc_01EF:
  01EF: 838CF4  AY0 = DM($38CF)                             ; int_ram
  01F0: 2AE01A  AR = AX0 - AY0, AX1 = AR                    
  01F1: 181F80  IF EQ JUMP loc_01F8                         
  01F2: 938D0E  DM($38D0) = SR0                             ; int_ram
  01F3: 938CF0  DM($38CF) = AX0                             ; int_ram
  01F4: 4FFFE0  AX0 = $FFFE                                 
  01F5: 27900F  AF = AX0 AND AF                             
  01F6: 27B10F  AF = AX1 OR AF                              
  01F7: 1C36BF  CALL sub_036B                               

loc_01F8:
  01F8: 22100F  AR = AF                                     
  01F9: 938BDA  DM($38BD) = AR                              ; int_ram
  01FA: 93200A  DM($3200) = AR                              ; ext_DWAIT3
  01FB: 3B8383  I7 = $3838                                  
  01FC: 38005B  L7 = $0005                                  
  01FD: 3834F2  I6 = $034F                                  
  01FE: 383331  I5 = $0333                                  
  01FF: 3832D0  I4 = $032D                                  
  0200: 378362  I2 = $3836                                  
  0201: 3784E1  I1 = $384E                                  
  0202: 838965  AY1 = DM($3896)                             ; int_ram
  0203: 838AF0  AX0 = DM($38AF)                             ; int_ram
  0204: 838B74  AY0 = DM($38B7)                             ; int_ram
  0205: 1C26DF  CALL sub_026D                               
  0206: 383431  I5 = $0343                                  
  0207: 838975  AY1 = DM($3897)                             ; int_ram
  0208: 838B00  AX0 = DM($38B0)                             ; int_ram
  0209: 838B84  AY0 = DM($38B8)                             ; int_ram
  020A: 1C26DF  CALL sub_026D                               
  020B: 370081  I1 = $3008                                  
  020C: 378452  I2 = $3845                                  
  020D: 340037  M3 = $0003                                  
  020E: 378023  I3 = $3802                                  
  020F: 400085  AY1 = $0008                                 
  0210: 1C24FF  CALL sub_024F                               
  0211: 1C24FF  CALL sub_024F                               
  0212: 3784A2  I2 = $384A                                  
  0213: 378033  I3 = $3803                                  
  0214: 400105  AY1 = $0010                                 
  0215: 1C24FF  CALL sub_024F                               
  0216: 1C24FF  CALL sub_024F                               
  0217: 383330  I4 = $0333                                  
  0218: 383431  I5 = $0343                                  
  0219: 838B1A  AR = DM($38B1)                              ; int_ram
  021A: 400204  AY0 = $0020                                 
  021B: 500050  AY1 = PM(I4,M4)                             
  021C: 562854  AF = AY1 + 1, AY1 = PM(I5,M4)               
  021D: 23A207  IF NOT AV AR = AR OR AY0                    
  021E: 400404  AY0 = $0040                                 
  021F: 26280F  AF = AY1 + 1                                
  0220: 23A207  IF NOT AV AR = AR OR AY0                    
  0221: 938B1A  DM($38B1) = AR                              ; int_ram
  0222: 40080A  AR = $0080                                  
  0223: 93025A  DM($3025) = AR                              ; ext_DWAIT3
  0224: 8B8AE3  I7 = DM($38AE)                              ; int_ram
  0225: 38000B  L7 = $0000                                  
  0226: 0A001F  RTI                                         

loc_0227:
  0227: 378051  I1 = $3805                                  
  0228: 383FC0  I4 = $03FC                                  
  0229: 1822CF  JUMP loc_022C                               

loc_022A:
  022A: 378091  I1 = $3809                                  
  022B: 383FD0  I4 = $03FD                                  

loc_022C:
  022C: 6000B5  MR0 = DM(I1,M1)                             
  022D: 6210C6  AR = AF, MR1 = DM(I1,M2)                    
  022E: 505860  MR = MR + MX0 * 0 (RND), MY0 = PM(I4,M4)    
  022F: 6824A5  MR = MR1 * MY0 (RND), DM(I1,M1) = AR        
  0230: 050000  IF MV SAT MR                                
  0231: 6800A5  DM(I1,M1) = AR                              
  0232: 6800C5  DM(I1,M1) = MR1                             
  0233: 181B7F  JUMP loc_01B7                               

loc_0234:
  0234: 378081  I1 = $3808                                  
  0235: 383FE0  I4 = $03FE                                  
  0236: 18239F  JUMP loc_0239                               

loc_0237:
  0237: 3780C1  I1 = $380C                                  
  0238: 383FF0  I4 = $03FF                                  

loc_0239:
  0239: E00006  AX0 = DM(I1,M2), MY0 = PM(I4,M4)            
  023A: 600045  AY0 = DM(I1,M1)                             
  023B: 22600F  AR = AX0 + AY0                              
  023C: 22620F  AR = AR + AY0                               
  023D: 20820F  MR = AR * MY0 (SS)                          
  023E: 830310  AX0 = DM($3031)                             ; ext_DWAIT3
  023F: 480004  AY0 = $8000                                 
  0240: 27C00F  AF = AX0 XOR AY0                            
  0241: 209800  IF EQ MR = 0                                
  0242: 6800C5  DM(I1,M1) = MR1                             
  0243: 181B7F  JUMP loc_01B7                               

loc_0244:
  0244: 464004  AY0 = $6400                                 
  0245: 838080  AX0 = DM($3808)                             ; int_ram
  0246: 401005  AY1 = $0100                                 
  0247: 27200F  AF = AY0 - AX0                              
  0248: 23AA04  IF LT AR = AR OR AY1                        
  0249: 8380C0  AX0 = DM($380C)                             ; int_ram
  024A: 402005  AY1 = $0200                                 
  024B: 27200F  AF = AY0 - AX0                              
  024C: 23AA04  IF LT AR = AR OR AY1                        
  024D: 938B1A  DM($38B1) = AR                              ; int_ram
  024E: 181B7F  JUMP loc_01B7                               

sub_024F:
  024F: 6000A5  AR = DM(I1,M1)                              
  0250: 63E24C  AR = ABS AR, AY0 = DM(I3,M0)                
  0251: 236206  IF AV AR = NOT AR                           
  0252: 26E20F  AF = AR - AY0                               
  0253: 220002  IF GT AR = AY0                              
  0254: 1C31EF  CALL sub_031E                               
  0255: 6E10AB  AF = AF, DM(I2,M3) = AR                     
  0256: 0A0003  IF LE RTS                                   
  0257: 838B1A  AR = DM($38B1)                              ; int_ram
  0258: 23AA0F  AR = AR OR AY1                              
  0259: 938B1A  DM($38B1) = AR                              ; int_ram
  025A: 0A000F  RTS                                         

sub_025B:
  025B: 27E20F  AF = ABS AR                                 
  025C: 40040A  AR = $0040                                  
  025D: 633217  AR = AF - AR, AX1 = DM(I1,M3)               
  025E: 0A0002  IF GT RTS                                   
  025F: 0326C2  IF FLAG_IN JUMP loc_026C                    
  0260: 404006  MY0 = $0400                                 
  0261: 408004  AY0 = $0800                                 
  0262: 1C263F  CALL sub_0263                               

sub_0263:
  0263: 23E10F  AR = ABS AX1                                
  0264: 2EE2A1  AF = AR - AY0, AR = AX1                     
  0265: 6000BC  MR0 = DM(I3,M0)                             
  0266: 5000C0  MR1 = PM(I4,M4)                             
  0267: 612217  MR = MR + AR * MY0 (SU), AX1 = DM(I1,M3)    
  0268: 209802  IF GT MR = 0                                
  0269: 6800BD  DM(I3,M1) = MR0                             
  026A: 5800C1  PM(I4,M5) = MR1                             
  026B: 6800CB  DM(I2,M3) = MR1                             

loc_026C:
  026C: 0A000F  RTS                                         

sub_026D:
  026D: 526070  AR = AX0 + AY0, MY1 = PM(I4,M4)             
  026E: 0F1204  SR = LSHIFT AR BY 4 (LO)                    
  026F: 0F36FE  SR = ASHIFT SR0 BY -2 (LO)                  
  0270: 400079  SE = $0007                                  
  0271: 60AE65  MR = SR0 * MY1 (SU), MY0 = DM(I1,M1)        
  0272: 120475  SR = LSHIFT MR1 (HI), MY1 = DM(I1,M1)       
  0273: 121B44  SR = SR OR LSHIFT MR0 (LO), AY0 = DM(I1,M0) 
  0274: 6800F5  DM(I1,M1) = SR1                             
  0275: 62E735  AR = SR1 - AY0, MX1 = DM(I1,M1)             
  0276: 221806  IF AV AR = 0                                
  0277: 20C10F  MR = MX1 * MY0 (US)                         
  0278: 28984C  MR = 0, AY0 = MR1                           
  0279: 0D00B4  MR0 = AY0                                   
  027A: 610A36  MR = MR + AR * MY1 (SS), MX1 = DM(I1,M2)    
  027B: 29011F  MR = MR + MX1 * MY0 (SS), AX1 = SR1         
  027C: 050000  IF MV SAT MR                                
  027D: 440004  AY0 = $4000                                 
  027E: 6800B5  DM(I1,M1) = MR0                             
  027F: 6A67C5  AR = SR1 + AY0, DM(I1,M1) = MR1             
  0280: 2BE40A  AR = ABS MR1, AX0 = AR                      
  0281: 509869  MR = 0, MY0 = PM(I6,M5)                     
  0282: 532AC4  AR = AY1 - AR, MR1 = PM(I5,M4)              
  0283: FC00A8  MX1 = DM(I2,M0), MY1 = PM(I6,M6)            
  0284: 6902A9  MR = MR + AR * MY0 (SS), DM(I2,M1) = AR     
  0285: 20490F  MR = MR + MX1 * MY1 (RND)                   
  0286: 050000  IF MV SAT MR                                
  0287: 227C0F  AR = MR1                                    
  0288: 221804  IF LT AR = 0                                
  0289: 5800A5  PM(I5,M5) = AR                              
  028A: 0329F0  IF NOT FLAG_IN JUMP loc_029F                
  028B: 0D005A  AY1 = AR                                    
  028C: 1C357F  CALL sub_0357                               
  028D: 5800A5  PM(I5,M5) = AR                              
  028E: 0D0001  AX0 = AX1                                   
  028F: 0D008A  SI = AR                                     
  0290: 1C357F  CALL sub_0357                               
  0291: 449E76  MY0 = $49E7                                 
  0292: 282228  MR = AR * MY0 (RND), MX0 = SI               
  0293: 5820C5  MR = MX0 * MY0 (RND), PM(I5,M5) = MR1       
  0294: 5E7E55  AF = SR0, PM(I5,M5) = AY1                   
  0295: 5800A5  PM(I5,M5) = AR                              
  0296: 5800C5  PM(I5,M5) = MR1                             
  0297: 46EDA6  MY0 = $6EDA                                 
  0298: 4FFFF9  SE = $FFFF                                  
  0299: 11A025  SR = ASHIFT SI (HI), PM(I5,M5) = MX0        
  029A: 5822A5  MR = AR * MY0 (RND), PM(I5,M5) = AR         
  029B: 5800C5  PM(I5,M5) = MR1                             
  029C: 5820F5  MR = MX0 * MY0 (RND), PM(I5,M5) = SR1       
  029D: 11A2C5  SR = ASHIFT AR (HI), PM(I5,M5) = MR1        
  029E: 5800F5  PM(I5,M5) = SR1                             

loc_029F:
  029F: 0A000F  RTS                                         

sub_02A0:
  02A0: 4FFF05  AY1 = $FFF0                                 
  02A1: C00054  AX0 = DM(I1,M0), AY0 = PM(I5,M5)            
  02A2: 22780F  AR = AX0                                    
  02A3: 238A05  IF GE AR = AR AND AY1                       
  02A4: C2E254  AR = AR - AY0, AX0 = DM(I1,M0), AY0 = PM(I5,M5)
  02A5: 500065  MY0 = PM(I5,M5)                             
  02A6: 50A265  MR = AR * MY0 (SU), MY0 = PM(I5,M5)         
  02A7: 050000  IF MV SAT MR                                
  02A8: 22780F  AR = AX0                                    
  02A9: 238A05  IF GE AR = AR AND AY1                       
  02AA: 2AE22C  AR = AR - AY0, MX0 = MR1                    
  02AB: 6F3C29  AF = -MR1, DM(I2,M1) = MX0                  
  02AC: ECA259  MR = AR * MY0 (SU), MX1 = DM(I2,M1), MY0 = PM(I5,M5)
  02AD: 050000  IF MV SAT MR                                
  02AE: 6821C8  MR = MX1 * MY0 (RND), DM(I2,M0) = MR1       
  02AF: E40059  AX1 = DM(I2,M1), MY0 = PM(I5,M5)            
  02B0: 2B3131  AR = AF - AX1, MX1 = AX1                    
  02B1: 6E7CA9  AF = MR1, DM(I2,M1) = AR                    
  02B2: 508075  MR = MX0 * MY0 (SS), MY1 = PM(I5,M5)        
  02B3: 6188E9  MR = MR - MX0 * MY1 (SS), SR0 = DM(I2,M1)   
  02B4: 518965  MR = MR - MX1 * MY1 (SS), MY0 = PM(I5,M5)   
  02B5: 506975  MR = MR - MX1 * MY1 (RND), MY1 = PM(I5,M5)  
  02B6: 050000  IF MV SAT MR                                
  02B7: 6B34CD  AR = AF - MR1, DM(I3,M1) = MR1              
  02B8: 502665  MR = SR0 * MY0 (RND), MY0 = PM(I5,M5)       
  02B9: 28884C  MR = MX0 * MY1 (SS), AY0 = MR1              
  02BA: 2900EA  MR = MR + MX0 * MY0 (SS), SR0 = AR          
  02BB: 21010F  MR = MR + MX1 * MY0 (SS)                    
  02BC: 20410F  MR = MR + MX1 * MY0 (RND)                   
  02BD: 050000  IF MV SAT MR                                
  02BE: 6F24CD  AF = AY0 - MR1, DM(I3,M1) = MR1             
  02BF: 227E0F  AR = SR0                                    
  02C0: 400004  AY0 = $0000                                 
  02C1: 1C2DBF  CALL sub_02DB                               
  02C2: 68004D  DM(I3,M1) = AY0                             
  02C3: 267C0F  AF = MR1                                    
  02C4: 1C2DBF  CALL sub_02DB                               
  02C5: 0D003C  MX1 = MR1                                   
  02C6: 500065  MY0 = PM(I5,M5)                             
  02C7: 508265  MR = AR * MY0 (SS), MY0 = PM(I5,M5)         
  02C8: 504165  MR = MR + MX1 * MY0 (RND), MY0 = PM(I5,M5)  
  02C9: 050000  IF MV SAT MR                                
  02CA: 182CCD  IF NOT MV JUMP loc_02CC                     
  02CB: 4FFFF4  AY0 = $FFFF                                 

loc_02CC:
  02CC: 7F3CC9  AF = -MR1, DM(I6,M5) = MR1                  
  02CD: 269006  IF AV AF = NOT AF                           
  02CE: 508265  MR = AR * MY0 (SS), MY0 = PM(I5,M5)         
  02CF: 518265  MR = MR - AR * MY0 (SS), MY0 = PM(I5,M5)    
  02D0: 518165  MR = MR - MX1 * MY0 (SS), MY0 = PM(I5,M5)   
  02D1: 20610F  MR = MR - MX1 * MY0 (RND)                   
  02D2: 050000  IF MV SAT MR                                
  02D3: 182D5D  IF NOT MV JUMP loc_02D5                     
  02D4: 4FFFF4  AY0 = $FFFF                                 

loc_02D5:
  02D5: 7B34C9  AR = AF - MR1, DM(I6,M5) = MR1              
  02D6: 7800A9  DM(I6,M5) = AR                              
  02D7: 182D97  IF NOT AV JUMP loc_02D9                     
  02D8: 4FFFF4  AY0 = $FFFF                                 

loc_02D9:
  02D9: 68004D  DM(I3,M1) = AY0                             
  02DA: 0A000F  RTS                                         

sub_02DB:
  02DB: E8001D  MX0 = DM(I3,M1), MY0 = PM(I4,M5)            
  02DC: FC001D  MX1 = DM(I3,M1), MY1 = PM(I4,M5)            
  02DD: 6000BD  MR0 = DM(I3,M1)                             
  02DE: 6000CD  MR1 = DM(I3,M1)                             
  02DF: 6800BD  DM(I3,M1) = MR0                             
  02E0: 6800CF  DM(I3,M3) = MR1                             
  02E1: 6922AD  MR = MR + AR * MY0 (SU), DM(I3,M1) = AR     
  02E2: 69202D  MR = MR + MX0 * MY0 (SU), DM(I3,M1) = MX0   
  02E3: 050000  IF MV SAT MR                                
  02E4: 6800BD  DM(I3,M1) = MR0                             
  02E5: 692ACD  MR = MR + AR * MY1 (SU), DM(I3,M1) = MR1    
  02E6: 61293D  MR = MR + MX1 * MY1 (SU), MX1 = DM(I3,M1)   
  02E7: 61A83D  MR = MR - MX0 * MY1 (SS), MX1 = DM(I3,M1)   
  02E8: 51A872  MR = MR - MX0 * MY1 (SS), MY1 = PM(I4,M6)   
  02E9: 512A72  MR = MR + AR * MY1 (SU), MY1 = PM(I4,M6)    
  02EA: 050000  IF MV SAT MR                                
  02EB: 0F24F4  SR = ASHIFT MR1 BY -12 (HI)                 
  02EC: 0F1BF4  SR = SR OR LSHIFT MR0 BY -12 (LO)           
  02ED: 0D00CE  MR1 = SR0                                   
  02EE: 2A10DF  AR = AF, MR2 = SR1                          
  02EF: 21180F  MR = MR + MX0 * 0 (SS)                      
  02F0: 0A000D  IF NOT MV RTS                               
  02F1: 050000  IF MV SAT MR                                
  02F2: 23000F  AR = AY0 - 1                                
  02F3: 2A104A  AR = AF, AY0 = AR                           
  02F4: 0A000F  RTS                                         

sub_02F5:
  02F5: 600046  AY0 = DM(I1,M2)                             
  02F6: 22000F  AR = AY0                                    
  02F7: 0A0000  IF EQ RTS                                   
  02F8: 3C0025  CNTR = $0002                                
  02F9: 142FDE  DO $02FD UNTIL CE                           
  02FA: 600006  AX0 = DM(I1,M2)                             
  02FB: 600016  AX1 = DM(I1,M2)                             
  02FC: 680006  DM(I1,M2) = AX0                             
  02FD: 680017  DM(I1,M3) = AX1                             
  02FE: 0A000F  RTS                                         

sub_02FF:
  02FF: 401EFC  MR1 = $01EF                                 
  0300: 25180F  MF = MR + MX0 * 0 (SS)                      
  0301: E4980F  MR = 0, AX1 = DM(I3,M3), MY0 = PM(I4,M4)    
  0302: 63E155  AR = ABS AX1, AY1 = DM(I1,M1)               
  0303: 2B92C6  AR = AR AND AF, MR1 = MY0                   
  0304: 1C31DF  CALL sub_031D                               
  0305: 2A6A21  AR = AR + AY1, MX0 = AX1                    
  0306: 60521E  MR = MR + AR * MF (RND), AX1 = DM(I3,M2)    
  0307: 6898C9  MR = 0, DM(I2,M1) = MR1                     
  0308: 63E155  AR = ABS AX1, AY1 = DM(I1,M1)               
  0309: 2B9272  AR = AR AND AF, MY1 = MX0                   
  030A: 0D00C6  MR1 = MY0                                   
  030B: 1C31DF  CALL sub_031D                               
  030C: 2A6A31  AR = AR + AY1, MX1 = AX1                    
  030D: 60521F  MR = MR + AR * MF (RND), AX1 = DM(I3,M3)    
  030E: 6898C9  MR = 0, DM(I2,M1) = MR1                     
  030F: 63E155  AR = ABS AX1, AY1 = DM(I1,M1)               
  0310: 2B92C6  AR = AR AND AF, MR1 = MY0                   
  0311: 1C31DF  CALL sub_031D                               
  0312: 2A6AE1  AR = AR + AY1, SR0 = AX1                    
  0313: 285263  MR = MR + AR * MF (RND), MY0 = MX1          
  0314: 6888C9  MR = MX0 * MY1 (SS), DM(I2,M1) = MR1        
  0315: 290171  MR = MR + MX1 * MY0 (SS), MY1 = AX1         
  0316: 704E45  MR = MR + SR0 * MY1 (RND), AY0 = DM(I5,M5)  
  0317: 0C0800  DIS AR_SAT                                  
  0318: 726456  AR = MR1 + AY0, AY1 = DM(I5,M6)             
  0319: 0C0C00  ENA AR_SAT                                  
  031A: 7A4DA5  AR = MR2 + AY1 + C, DM(I5,M5) = AR          
  031B: 7800A5  DM(I5,M5) = AR                              
  031C: 0A000F  RTS                                         

sub_031D:
  031D: 220001  IF NE AR = AY0                              

sub_031E:
  031E: 233A0A  IF NEG AR = -AR                             
  031F: 236206  IF AV AR = NOT AR                           
  0320: 0A000F  RTS                                         

sub_0321:
  0321: 26080F  AF = AY1                                    
  0322: 23280F  AR = AY1 - AX0                              
  0323: 183284  IF LT JUMP loc_0328                         
  0324: 183261  IF NE JUMP loc_0326                         
  0325: 47FFF4  AY0 = $7FFF                                 

loc_0326:
  0326: 3C0040  ASTAT = $0004                               
  0327: 0A000F  RTS                                         

loc_0328:
  0328: 3C0000  ASTAT = $0000                               
  0329: 3C0105  CNTR = $0010                                
  032A: 1432BE  DO $032B UNTIL CE                           
  032B: 071000  DIVQ AX0                                    
  032C: 0A000F  RTS                                         
  032D: 20C400  IF EQ MR = MR1 * MY0 (US)                   
  032E: 01F400  IO($740) = AX0  ; 218x only                 
  032F: 000000  NOP                                         
  0330: 000000  NOP                                         
  0331: 800000  AX0 = DM($0000)                             ; ext_DWAIT0
  0332: 800000  AX0 = DM($0000)                             ; ext_DWAIT0
  0333: 7FFF00  AF = ABS SR1, DM(I4,M4) = AX0               
  0334: 000000  NOP                                         
  0335: 000000  NOP                                         
  0336: 7FFF00  AF = ABS SR1, DM(I4,M4) = AX0               
  0337: 000000  NOP                                         
  0338: 000000  NOP                                         
  0339: 000000  NOP                                         
  033A: 000000  NOP                                         
  033B: 000000  NOP                                         
  033C: 000000  NOP                                         
  033D: 000000  NOP                                         
  033E: 000000  NOP                                         
  033F: 000000  NOP                                         
  0340: 000000  NOP                                         
  0341: 800000  AX0 = DM($0000)                             ; ext_DWAIT0
  0342: 800000  AX0 = DM($0000)                             ; ext_DWAIT0
  0343: 7FFF00  AF = ABS SR1, DM(I4,M4) = AX0               
  0344: 000000  NOP                                         
  0345: 000000  NOP                                         
  0346: 7FFF00  AF = ABS SR1, DM(I4,M4) = AX0               
  0347: 000000  NOP                                         
  0348: 000000  NOP                                         
  0349: 000000  NOP                                         
  034A: 000000  NOP                                         
  034B: 000000  NOP                                         
  034C: 000000  NOP                                         
  034D: 000000  NOP                                         
  034E: 000000  NOP                                         
  034F: 7FFF00  AF = ABS SR1, DM(I4,M4) = AX0               
  0350: C00000  AX0 = DM(I0,M0), AY0 = PM(I4,M4)            
  0351: FFFFFF  AR = ABS SR1, MX1 = DM(I3,M3), MY1 = PM(I7,M7)
  0352: FFFFFF  AR = ABS SR1, MX1 = DM(I3,M3), MY1 = PM(I7,M7)
  0353: FFFFFF  AR = ABS SR1, MX1 = DM(I3,M3), MY1 = PM(I7,M7)
  0354: FFFFFF  AR = ABS SR1, MX1 = DM(I3,M3), MY1 = PM(I7,M7)
  0355: FFFFFF  AR = ABS SR1, MX1 = DM(I3,M3), MY1 = PM(I7,M7)
  0356: FFFFFF  AR = ABS SR1, MX1 = DM(I3,M3), MY1 = PM(I7,M7)

sub_0357:
  0357: 440004  AY0 = $4000                                 
  0358: 2F80A0  AF = AX0 AND AY0, AR = AX0                  
  0359: 233801  IF NE AR = -AX0                             
  035A: 47FFF4  AY0 = $7FFF                                 
  035B: 23820F  AR = AR AND AY0                             
  035C: 0D007A  MY1 = AR                                    
  035D: 742A3D  MF = AR * MY1 (RND), MX1 = DM(I7,M5)        
  035E: 70893D  MR = MX1 * MY1 (SS), MX1 = DM(I7,M5)        
  035F: 3C0035  CNTR = $0003                                
  0360: 14362E  DO $0362 UNTIL CE                           
  0361: 21110F  MR = MR + MX1 * MF (SS)                     
  0362: 74323D  MF = AR * MF (RND), MX1 = DM(I7,M5)         
  0363: 21110F  MR = MR + MX1 * MF (SS)                     
  0364: 0F2403  SR = ASHIFT MR1 BY 3 (HI)                   
  0365: 0F1B03  SR = SR OR LSHIFT MR0 BY 3 (LO)             
  0366: 227F0F  AR = SR1                                    
  0367: 220004  IF LT AR = AY0                              
  0368: 26780F  AF = AX0                                    
  0369: 233A04  IF LT AR = -AR                              
  036A: 0A000F  RTS                                         

sub_036B:
  036B: 4FFFFA  AR = $FFFF                                  
  036C: 93813A  DM($3813) = AR                              ; int_ram

sub_036D:
  036D: 48030A  AR = $8030                                  
  036E: 9380EA  DM($380E) = AR                              ; int_ram
  036F: 40389A  AR = $0389                                  

loc_0370:
  0370: 938D2A  DM($38D2) = AR                              ; int_ram
  0371: 0A000F  RTS                                         

sub_0372:
  0372: 22180F  AR = 0                                      
  0373: 938CFA  DM($38CF) = AR                              ; int_ram
  0374: 403EAA  AR = $03EA                                  
  0375: 18370F  JUMP loc_0370                               

loc_0376:
  0376: 600005  AX0 = DM(I1,M1)                             
  0377: 400059  SE = $0005                                  
  0378: 48000F  SR1 = $8000                                 
  0379: 2E800F  AF = NOT AY0, AX0 = SR1                     
  037A: 1837D3  IF LE JUMP loc_037D                         
  037B: 4FFFD9  SE = $FFFD                                  
  037C: 26000F  AF = AY0                                    

loc_037D:
  037D: 1437F1  DO $037F UNTIL EQ                           
  037E: 0F07FF  SR = LSHIFT SR1 BY -1 (HI)                  
  037F: 23970F  AR = SR1 AND AF                             
  0380: 1287A5  SR = LSHIFT SR1 (HI), DM(I1,M1) = AR        
  0381: 6800A5  DM(I1,M1) = AR                              
  0382: A00185  DM(I1,M1) = $0018                           
  0383: 6A7FA5  AR = SR1, DM(I1,M1) = AR                    
  0384: 227800  IF EQ AR = AX0                              
  0385: 93816A  DM($3816) = AR                              ; int_ram
  0386: 4039AA  AR = $039A                                  
  0387: 938D2A  DM($38D2) = AR                              ; int_ram
  0388: 0A001F  RTI                                         
  0389: 3780E1  I1 = $380E                                  
  038A: 4FFF00  AX0 = $FFF0                                 
  038B: 678054  AF = AX0 AND AY0, AY1 = DM(I1,M0)           ; I1=$380E int_ram
  038C: 23D00F  AR = AX0 XOR AF                             
  038D: 183940  IF EQ JUMP loc_0394                         
  038E: 23080F  AR = AY1 - 1                                
  038F: 183760  IF EQ JUMP loc_0376                         
  0390: 6800A4  DM(I1,M0) = AR                              ; I1=$380E int_ram
  0391: 183E96  IF AV JUMP loc_03E9                         
  0392: 1C36B5  IF GE CALL sub_036B                         
  0393: 0A001F  RTI                                         

loc_0394:
  0394: 23080F  AR = AY1 - 1                                
  0395: 183984  IF LT JUMP loc_0398                         
  0396: A00014  DM(I1,M0) = $0001                           
  0397: 0A001F  RTI                                         

loc_0398:
  0398: A00025  DM(I1,M1) = $0002                           
  0399: 0A001F  RTI                                         
  039A: 3780F1  I1 = $380F                                  
  039B: 400019  SE = $0001                                  
  039C: 838160  AX0 = DM($3816)                             ; int_ram
  039D: 400015  AY1 = $0001                                 
  039E: 638085  AR = AX0 AND AY0, SI = DM(I1,M1)            ; I1=$380F int_ram
  039F: 220801  IF NE AR = AY1                              
  03A0: 120086  SR = LSHIFT SI (HI), SI = DM(I1,M2)         ; I1=$3810 int_ram
  03A1: 0D00EA  SR0 = AR                                    
  03A2: 0E180F  SR = SR OR LSHIFT SI (LO)                   
  03A3: 6800F5  DM(I1,M1) = SR1                             ; I1=$380F int_ram
  03A4: 6A7AE5  AR = AR, DM(I1,M1) = SR0                    ; I1=$3810 int_ram
  03A5: 233A01  IF NE AR = -AR                              
  03A6: 667A45  AF = AR, AY0 = DM(I1,M1)                    ; I1=$3811 int_ram
  03A7: 438190  AX0 = $3819                                 
  03A8: 626016  AR = AX0 + AY0, AX1 = DM(I1,M2)             ; I1=$3812 int_ram
  03A9: 0D043A  I3 = AR                                     
  03AA: 63000C  AR = AY0 - 1, AX0 = DM(I3,M0)               
  03AB: 6F90A5  AF = AX0 AND AF, DM(I1,M1) = AR             ; I1=$3811 int_ram
  03AC: 2BD10A  AR = AX1 XOR AF, AX0 = AR                   
  03AD: 6A78A4  AR = AX0, DM(I1,M0) = AR                    ; I1=$3812 int_ram
  03AE: 0A0011  IF NE RTI                                   
  03AF: 400204  AY0 = $0020                                 
  03B0: 638745  AR = SR1 AND AY0, AY0 = DM(I1,M1)           ; I1=$3812 int_ram
  03B1: 183B71  IF NE JUMP loc_03B7                         
  03B2: 1C36DF  CALL sub_036D                               
  03B3: 680045  DM(I1,M1) = AY0                             ; I1=$3813 int_ram
  03B4: 6A7EF5  AR = SR0, DM(I1,M1) = SR1                   ; I1=$3814 int_ram
  03B5: 6800A5  DM(I1,M1) = AR                              ; I1=$3815 int_ram
  03B6: 0A001F  RTI                                         

loc_03B7:
  03B7: 600005  AX0 = DM(I1,M1)                             
  03B8: 2BA08E  AR = AX0 OR AY0, SI = SR0                   
  03B9: 183CA1  IF NE JUMP loc_03CA                         
  03BA: 378C93  I3 = $38C9                                  
  03BB: 4FFFB9  SE = $FFFB                                  
  03BC: 1207A5  SR = LSHIFT SR1 (HI), AR = DM(I1,M1)        
  03BD: 121885  SR = SR OR LSHIFT SI (LO), SI = DM(I1,M1)   
  03BE: 1002CE  SR = LSHIFT AR (HI), MR1 = SR0              
  03BF: 12184C  SR = SR OR LSHIFT SI (LO), AY0 = DM(I3,M0)  ; I3=$38C9 int_ram
  03C0: 6FC4CD  AF = MR1 XOR AY0, DM(I3,M1) = MR1           ; I3=$38C9 int_ram
  03C1: 60005C  AY1 = DM(I3,M0)                             ; I3=$38CA int_ram
  03C2: 6BCC4D  AR = MR1 XOR AY1, DM(I3,M1) = AY0           ; I3=$38CA int_ram
  03C3: 6BB25D  AR = AR OR AF, DM(I3,M1) = AY1              ; I3=$38CB int_ram
  03C4: 4FC004  AY0 = $FC00                                 
  03C5: 63824C  AR = AR AND AY0, AY0 = DM(I3,M0)            ; I3=$38CC int_ram
  03C6: 6FC6ED  AF = SR0 XOR AY0, DM(I3,M1) = SR0           ; I3=$38CC int_ram
  03C7: 63B25C  AR = AR OR AF, AY1 = DM(I3,M0)              ; I3=$38CD int_ram
  03C8: 6FCE4D  AF = SR0 XOR AY1, DM(I3,M1) = AY0           ; I3=$38CD int_ram
  03C9: 23B20F  AR = AR OR AF                               

loc_03CA:
  03CA: 1C36B1  IF NE CALL sub_036B                         
  03CB: 0A0011  IF NE RTI                                   
  03CC: 4FF004  AY0 = $FF00                                 
  03CD: 2B860E  AR = SR0 AND AY0, AX0 = SR0                 
  03CE: 838CF1  AX1 = DM($38CF)                             ; int_ram
  03CF: 400025  AY1 = $0002                                 
  03D0: 2F89EA  AF = AX1 AND AY1, SR0 = AR                  
  03D1: 183D61  IF NE JUMP loc_03D6                         
  03D2: 378C81  I1 = $38C8                                  
  03D3: 3702A3  I3 = $302A                                  
  03D4: 400FF4  AY0 = $00FF                                 
  03D5: 183D9F  JUMP loc_03D9                               

loc_03D6:
  03D6: 0F16F8  SR = LSHIFT SR0 BY -8 (LO)                  
  03D7: 378C61  I1 = $38C6                                  
  03D8: 370263  I3 = $3026                                  

loc_03D9:
  03D9: 83003A  AR = DM($3003)                              ; ext_DWAIT3
  03DA: 6F8206  AF = AR AND AY0, DM(I1,M2) = AX0            
  03DB: 6BB6C4  AR = SR0 OR AF, DM(I1,M0) = MR1             
  03DC: 93003A  DM($3003) = AR                              ; ext_DWAIT3
  03DD: 4FFF04  AY0 = $FFF0                                 
  03DE: 23810F  AR = AX1 AND AY0                            
  03DF: 480904  AY0 = $8090                                 
  03E0: 22E20F  AR = AR - AY0                               
  03E1: 183E40  IF EQ JUMP loc_03E4                         
  03E2: 6800CD  DM(I3,M1) = MR1                             
  03E3: 68000C  DM(I3,M0) = AX0                             

loc_03E4:
  03E4: 838CF0  AX0 = DM($38CF)                             ; int_ram
  03E5: 838D04  AY0 = DM($38D0)                             ; int_ram
  03E6: 22E00F  AR = AX0 - AY0                              
  03E7: 183E91  IF NE JUMP loc_03E9                         
  03E8: 93000A  DM($3000) = AR                              ; ext_DWAIT3

loc_03E9:
  03E9: 1C372F  CALL sub_0372                               
  03EA: 0A001F  RTI                                         

loc_03EB:
  03EB: 838320  AX0 = DM($3832)                             ; int_ram
  03EC: 441234  AY0 = $4123                                 
  03ED: 22E00F  AR = AX0 - AY0                              
  03EE: 180411  IF NE JUMP loc_0041                         
  03EF: 838331  AX1 = DM($3833)                             ; int_ram
  03F0: 410025  AY1 = $1002                                 
  03F1: 22E90F  AR = AX1 - AY1                              
  03F2: 180411  IF NE JUMP loc_0041                         
  03F3: 4000FA  AR = $000F                                  
  03F4: 93025A  DM($3025) = AR                              ; ext_DWAIT3
  03F5: 40FFFA  AR = $0FFF                                  
  03F6: 93033A  DM($3033) = AR                              ; ext_DWAIT3
  03F7: 40000A  AR = $0000                                  
  03F8: 0D0C3A  IMASK = AR                                  
  03F9: 37FFF1  I1 = $3FFF                                  ; SYSCNTL
  03FA: A02985  DM(I1,M1) = $0298                           ; I1=$3FFF SYSCNTL
  03FB: FFFFFF  AR = ABS SR1, MX1 = DM(I3,M3), MY1 = PM(I7,M7)
  03FC: 7FFF00  AF = ABS SR1, DM(I4,M4) = AX0               
  03FD: 7FFF00  AF = ABS SR1, DM(I4,M4) = AX0               
  03FE: 7F1C00  AF = -1, DM(I4,M4) = AX0                    
  03FF: 7F1C00  AF = -1, DM(I4,M4) = AX0                    

; ---- boot page 2: 72 words loaded at PM $0000 ----
; assumed at entry (left by page 0): M0=0, M1=1, M2=-1, M3=0, M4=0, M5=1, M6=-1, M7=0
  ; -- vector slot RESET --
  0000: 37FFF1  I1 = $3FFF                                  ; SYSCNTL
  0001: A101A5  DM(I1,M1) = $101A                           ; I1=$3FFF SYSCNTL
  0002: 18020F  JUMP loc_0020                               
  0003: 000000  NOP                                         
  ; -- vector slot IRQ2 --
  0004: 0A001F  RTI                                         
  0005: 000000  NOP                                         
  0006: 000000  NOP                                         
  0007: 000000  NOP                                         
  ; -- vector slot SPORT0_TX --
  0008: 000000  NOP                                         
  0009: 000000  NOP                                         
  000A: 000000  NOP                                         
  000B: 000000  NOP                                         
  ; -- vector slot SPORT0_RX --
  000C: 0D03A8  AR = RX0                                    
  000D: 267A0F  AF = AR                                     
  000E: 0A001F  RTI                                         
  000F: 000000  NOP                                         
  ; -- vector slot IRQ1_SPORT1_TX --
  0010: 370000  I0 = $3000                                  
  0011: 374001  I1 = $3400                                  
  0012: 378002  I2 = $3800                                  
  0013: 1C038F  CALL sub_0038                               
  ; -- vector slot IRQ0_SPORT1_RX --
  0014: 378202  I2 = $3820                                  
  0015: 1C038F  CALL sub_0038                               
  0016: 378402  I2 = $3840                                  
  0017: 1C038F  CALL sub_0038                               
  ; -- vector slot TIMER --
  0018: 378602  I2 = $3860                                  
  0019: 1C038F  CALL sub_0038                               
  001A: 621001  AR = AF, AX0 = DM(I0,M1)                    ; I0=$3000 ext_DWAIT3
  001B: 6800A1  DM(I0,M1) = AR                              ; I0=$3001 ext_DWAIT3
  001C: 932000  DM($3200) = AX0                             ; ext_DWAIT3
  001D: 40080A  AR = $0080                                  
  001E: 93025A  DM($3025) = AR                              ; ext_DWAIT3
  001F: 0A001F  RTI                                         

loc_0020:
  0020: 0C3008  ENA M_MODE DIS G_MODE                       
  0021: 340004  M0 = $0000                                  
  0022: 340015  M1 = $0001                                  
  0023: 37FFF6  M2 = $3FFF                                  
  0024: 3C0065  CNTR = $0006                                
  0025: 3703C1  I1 = $303C                                  
  0026: 14027E  DO $0027 UNTIL CE                           
  0027: A01F46  DM(I1,M2) = $01F4                           ; I1=$303C..$3037 x6 ext_DWAIT3
  0028: A00006  DM(I1,M2) = $0000                           ; I1=$3036 ext_DWAIT3
  0029: A0FFF6  DM(I1,M2) = $0FFF                           ; I1=$3035 ext_DWAIT3
  002A: A000F6  DM(I1,M2) = $000F                           ; I1=$3034 ext_DWAIT3
  002B: A03E86  DM(I1,M2) = $03E8                           ; I1=$3033 ext_DWAIT3
  002C: 370000  I0 = $3000                                  
  002D: 3C0205  CNTR = $0020                                
  002E: 22180F  AR = 0                                      
  002F: 14030E  DO $0030 UNTIL CE                           
  0030: 6800A1  DM(I0,M1) = AR                              ; I0=$3000..$301F x32 ext_DWAIT3
  0031: 93200A  DM($3200) = AR                              ; ext_DWAIT3
  0032: 3C03FC  IFC = $003F                                 
  0033: 3C02C3  IMASK = $002C                               
  0034: 374001  I1 = $3400                                  
  0035: 6000A4  AR = DM(I1,M0)                              ; I1=$3400 ext_DWAIT4

loc_0036:
  0036: 028000  IDLE                                        
  0037: 18036F  JUMP loc_0036                               

sub_0038:
  0038: 6000E4  SR0 = DM(I1,M0)                             
  0039: 6800E1  DM(I0,M1) = SR0                             
  003A: 408006  MY0 = $0800                                 
  003B: 20980F  MR = 0                                      
  003C: 3C0205  CNTR = $0020                                
  003D: 1403FE  DO $003F UNTIL CE                           
  003E: 627EE8  AR = SR0, SR0 = DM(I2,M0)                   
  003F: 6922A9  MR = MR + AR * MY0 (SU), DM(I2,M1) = AR     
  0040: 050000  IF MV SAT MR                                
  0041: 6800C1  DM(I0,M1) = MR1                             
  0042: 0A000F  RTS                                         
  0043: FFFFFF  AR = ABS SR1, MX1 = DM(I3,M3), MY1 = PM(I7,M7)
  0044: FFFFFF  AR = ABS SR1, MX1 = DM(I3,M3), MY1 = PM(I7,M7)
  0045: FFFFFF  AR = ABS SR1, MX1 = DM(I3,M3), MY1 = PM(I7,M7)
  0046: FFFFFF  AR = ABS SR1, MX1 = DM(I3,M3), MY1 = PM(I7,M7)
  0047: FFFFFF  AR = ABS SR1, MX1 = DM(I3,M3), MY1 = PM(I7,M7)

