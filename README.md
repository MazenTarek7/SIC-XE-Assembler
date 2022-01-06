								**SIC/XE Assembler**

The Simplified Instructional Computer is a hypothetical computer system introduced in System Software: An Introduction to Systems Programming, by Leland Beck.

Functions:
* Addressing Mode (Flag bit)
* Direct Addressing Mode
* Indirect Addressing Mode
* Simple Addressing Mode
* Immediate Addressing Mode
  * Relative Addressing Mode
  * Program Counter (PC Register)
* Base (Base Register)
* Extended Instruction (4bit Instruction)

Operation Table For SIC-XE:

|Mnemonic     |Format  |Opcode  |Effect                           |Notes
|-------------|:------:|:------:|---------------------------------|:-----:
|ADD m        |  3/4   |  18    |A ← (A) + (m..m+2)               |
|ADDF m       |  3/4   |  58    |F ← (F) + (m..m+5)               |F
|ADDR r1,r2   |   2    |  90    |r2 ← (r2) + (r1)                 
|AND m        |  3/4   |  40    |A ← (A) & (m..m+2)               
|CLEAR r1     |   2    |  B4    |r1 ← 0                           
|COMP m       |  3/4   |  28    |A : (m..m+2)                     |C
|COMPF m      |  3/4   |  88    |F : (m..m+5)                     |CF
|COMPR r1,r2  |   2    |  A0    |(r1) : (r2)                      |C
|DIV m        |  3/4   |  24    |A : (A) / (m..m+2)
|DIVF m       |  3/4   |  64    |F : (F) / (m..m+5)               |F
|DIVR r1,r2   |   2    |  9C    |(r2) ← (r2) / (r1)
|FIX          |   1    |  C4    |A ← (F) [convert to integer]
|FLOAT        |   1    |  C0    |F ← (A) [convert to floating]    |F
|HIO          |   1    |  F4    |Halt I/O channel number (A)      |P
|J m          |  3/4   |  3C    |PC ← m
|JEQ m        |  3/4   |  30    |PC ← m if CC set to =
|JGT m        |  3/4   |  34    |PC ← m if CC set to >
|JLT m        |  3/4   |  38    |PC ← m if CC set to <
|JSUB m       |  3/4   |  48    |L ← (PC); PC ← m<
|LDA m        |  3/4   |  00    |A ← (m..m+2)
|LDB m        |  3/4   |  68    |B ← (m..m+2)
|LDCH m       |  3/4   |  50    |A [rightmost byte] ← (m)
|LDF m        |  3/4   |  70    |F ← (m..m+5)                      |F
|LDL m        |  3/4   |  08    |L ← (m..m+2)
|LDS m        |  3/4   |  6C    |S ← (m..m+2)
|LDT m        |  3/4   |  74    |T ← (m..m+2)
|LDX m        |  3/4   |  04    |X ← (m..m+2)
|LPS m        |  3/4   |  D0    |Load processor status             |P
|MUL m        |  3/4   |  20    |A ← (A) * (m..m+2)
|MULF m       |  3/4   |  60    |F ← (F) * (m..m+5)
|MULR r1,r2   |   2    |  98    |r2 ← (r2) * (r1)
|NORM         |   1    |  C8    |F ← (F) [normalized]              |F
|OR m         |  3/4   |  44    |A ← (A)  (m..m+2)
|RD m         |  3/4   |  D8    |A [rightmost byte] ← data         |P
|RMO r1,r2    |   2    |  AC    |r2 ← (r1)
|RSUB         |  3/4   |  4C    |PC ← (L)
|SHIFTL r1,n  |   2    |  A4    |r1 ← (r1); left circular shift
|SHIFTR r1,n  |   2    |  A8    |r1 ← (r1); right shift n bits
|SIO          |   1    |  F0    |Start I/O channel number (A)      |P
|SSK m        |  3/4   |  EC    |Protection key for address m      |P
|STA m        |  3/4   |  0C    |m..m+2 ← (A)
|STB m        |  3/4   |  78    |m..m+2 ← (B)
|STCH m       |  3/4   |  54    |m ← (A) [rightmost byte]
|STF m        |  3/4   |  80    |m..m+5 ← (F)                       |F
|STI m        |  3/4   |  D4    |Interval timer value ← (m..m+2)    |P
|STL m        |  3/4   |  14    |m..m+2 ← (L)
|STS m        |  3/4   |  7C    |m..m+2 ← (S)
|STSW m       |  3/4   |  E8    |m..m+2 ← (SW)                      |P
|STT m        |  3/4   |  84    |m..m+2 ← (T)
|STX m        |  3/4   |  10    |m..m+2 ← (X)
|SUB m        |  3/4   |  1C    |A ← (A) - (m..m+2)
|SUBF m       |  3/4   |  5C    |F ← (F) - (m..m+5)                 |F
|SUBR r1,r2   |   2    |  94    |r2 ← (r2) - (r1)
|SVC n        |   2    |  B0    |Generate SVC interrupt
|TD m         |  3/4   |  E0    |Test device specified by (m)       |PC
|TIO          |   1    |  F8    |Test I/O channel number (A)        |PC
|TIX m        |  3/4   |  2C    |X ← (X) + 1; (X) : (m..m+2)        |C
|TIXR r1      |   2    |  B8    |X ← (X) + 1; (X) : (r1)            |C
|WD m         |  3/4   |  DC    |Device specified by (m) ← (A)      |P

**#Sample Input:**
```
COPY	START	0
FIRST	STL	RETADR
	LDB	#LENGTH
	BASE	LENGTH
CLOOP	+JSUB	RDREC
	LDA	LENGTH
	COMP	#0
	JEQ	ENDFIL
	+JSUB	WRREC
	J	CLOOP
ENDFIL	LDA	EOF
	STA	BUFFER
	LDA	#3
	STA	LENGTH
	+JSUB	WRREC
	J	@RETADR
EOF	BYTE	C'EOF'
RETADR	RESW	1
LENGTH	RESW	1
BUFFER	RESB	4096
RDREC	CLEAR	X
	CLEAR	A
	CLEAR	S
	+LDT	#4096
RLOOP	TD	INPUT
	JEQ	RLOOP
	RD	INPUT
	COMPR	A,S	
	JEQ	EXIT
	STCH	BUFFER,X
	TIXR	T
	JLT	RLOOP
EXIT	STX	LENGTH
	RSUB	
INPUT	BYTE	X'F1'
WRREC	CLEAR	X
	LDT	LENGTH
WLOOP	TD	OUTPUT
	JEQ	WLOOP
	LDCH	BUFFER,X
	WD	OUTPUT
	TIXR	T
	JLT	WLOOP
	RSUB	
OUTPUT	BYTE	X'05'	
	END	FIRST	
```
**Symbol Table output:**
```
0000	COPY	START	0
0000	FIRST	STL	RETADR
0003		LDB	#LENGTH
		BASE	LENGTH
0006	CLOOP	+JSUB	RDREC
000A		LDA	LENGTH
000D		COMP	#0
0010		JEQ	ENDFIL
0013		+JSUB	WRREC
0017		J	CLOOP
001A	ENDFIL	LDA	EOF
001D		STA	BUFFER
0020		LDA	#3
0023		STA	LENGTH
0026		+JSUB	WRREC
002A		J	@RETADR
002D	EOF	BYTE	C'EOF'
0030	RETADR	RESW	1
0033	LENGTH	RESW	1
0036	BUFFER	RESB	4096
1036	RDREC	CLEAR	X
1038		CLEAR	A
103A		CLEAR	S
103C		+LDT	#4096
1040	RLOOP	TD	INPUT
1043		JEQ	RLOOP
1046		RD	INPUT
1049		COMPR	A,S
104B		JEQ	EXIT
104E		STCH	BUFFER,X
1051		TIXR	T
1053		JLT	RLOOP
1056	EXIT	STX	LENGTH
1059		RSUB	
105C	INPUT	BYTE	X'F1'
105D	WRREC	CLEAR	X
105F		LDT	LENGTH
1062	WLOOP	TD	OUTPUT
1065		JEQ	WLOOP
1068		LDCH	BUFFER,X
106B		WD	OUTPUT
106E		TIXR	T
1070		JLT	WLOOP
1073		RSUB	
1076	OUTPUT	BYTE	X'05'
1077		END	FIRST
```
**Object Table Output**:
```
0000	COPY	START	0	
0000	FIRST	STL	RETADR	17202D
0003		LDB	#LENGTH	69202D
		BASE	LENGTH	
0006	CLOOP	+JSUB	RDREC	4B101036
000A		LDA	LENGTH	032026
000D		COMP	#0	290000
0010		JEQ	ENDFIL	332007
0013		+JSUB	WRREC	4B10105D
0017		J	CLOOP	3F2FEC
001A	ENDFIL	LDA	EOF	032010
001D		STA	BUFFER	0F2016
0020		LDA	#3	010003
0023		STA	LENGTH	0F200D
0026		+JSUB	WRREC	4B10105D
002A		J	@RETADR	3E2003
002D	EOF	BYTE	C'EOF'	454F46
0030	RETADR	RESW	1	
0033	LENGTH	RESW	1	
0036	BUFFER	RESB	4096	
1036	RDREC	CLEAR	X	B410
1038		CLEAR	A	B400
103A		CLEAR	S	B440
103C		+LDT	#4096	75101000
1040	RLOOP	TD	INPUT	E32019
1043		JEQ	RLOOP	332FFA
1046		RD	INPUT	DB2013
1049		COMPR	A,S	A004
104B		JEQ	EXIT	332008
104E		STCH	BUFFER,X	57C003
1051		TIXR	T	B850
1053		JLT	RLOOP	3B2FEA
1056	EXIT	STX	LENGTH	134000
1059		RSUB		4F0000
105C	INPUT	BYTE	X'F1'	F1
105D	WRREC	CLEAR	X	B410
105F		LDT	LENGTH	774000
1062	WLOOP	TD	OUTPUT	E32011
1065		JEQ	WLOOP	332FFA
1068		LDCH	BUFFER,X	53C003
106B		WD	OUTPUT	DF2008
106E		TIXR	T	B850
1070		JLT	WLOOP	3B2FEF
1073		RSUB		4F0000
1076	OUTPUT	BYTE	X'05'	05
1077		END	FIRST	
```
**HTE Output:**
```
H^COPY__^000000^001077
T^000000^1D^17202D69202D4B1010360320262900003320074B10105D3F2FEC032010
T^00001D^13^0F20160100030F200D4B10105D3E2003454F46
T^001036^1D^B410B400B44075101000E32019332FFADB2013A00433200857C003B850
T^001053^1D^3B2FEA1340004F0000F1B410774000E32011332FFA53C003DF2008B850
T^001070^07^3B2FEF4F000005
M^000007^05
M^000014^05
M^000027^05
E^000000
```
