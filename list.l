  1                   # TEST_RETURN_CODE=PAS
  2                   
  3                   # allons au mandela
  4                   # allons au ru
  5                   .set noreorder
  6                   .text
  7 00000000 3C010000     LW $t0, boucle
  7 00000004 8C280000 
  8 00000008 8CE6FE00     LW $6, -0x200($7)
  9 0000000C 8D280AA0     LW $8, 0xaa0($9)
 10 00000010 20090008     ADDI $t1,$zero,8
 11                   boucle:
 12 00000014 11090000     BEQ $t0 , $t1 , byebye
 13 00000018 00000000     NOP
 14 0000001C 00801840     MOVE $3,$4
 15 00000020 00041822     NEG $3,$4
 16 00000024 20030064     LI $3,100
 17 00000028 0064082A     BLT $3,$4,boucle
 17 0000002C 14200000 
 18 00000030 21290001     ADDI $t1 , $t1 , 1
 19 00000034 08000000     J boucle
 20 00000038 00000000     NOP
 21 0000003C 0C000000     byebye: JAL viteviteauru
 22                   .data
 23 00000000 000003E7     lunchtime : .word 12
 24 00000004 000003E7     .word byebye
 25 00000008 000003E7     .byte  2, 0x4
 26 0000000A 000003E7     .space 12
 27                       .asciiz "blabla","gabuzomeu shadoks"
 28                   .bss
 29 00000000 000003E7 .space 12
 30 0000000C 000003E7 .space 12
 31                   .data
 32                   .text
 33 00000040 8D280AA0     LW $8, 0xaa0($9)
 34 00000044 20090008     ADDI $t1,$zero,8

.symtab
 11	.text:00000014	boucle
 21	.text:0000003C	byebye
 23	.data:00000000	lunchtime

rel.text
00000000    R_MIPS_HI16   .text:000004d2  boucle
00000014    R_MIPS_HI16   .text:000004d2  byebye
0000002c    R_MIPS_HI16   .text:000004d2  boucle
00000034    R_MIPS_26    .text:000004d2  boucle
0000003c    R_MIPS_26    unknown:000004d2  viteviteauru

rel.data
00000004    R_MIPS_32    .text:000004d2  byebye
