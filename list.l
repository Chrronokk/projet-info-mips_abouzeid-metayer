  1                   # TEST_RETURN_CODE=PASS
  2                   # allons au ru blblblblblblblblblbbbl
  3                   
  4                   
  5                   .set noreorder
  6                   .text
  7 00000000 3C010000     LW $t0 , lunchtime
  7 00000004 8C280000 
  8 00000008 8CE6FE00     LW $6, -0x200($7)
  9 0000000C 20090008     ADDI $t1,$zero,8
 10                   
 11                   boucle:
 12 00000010 11090009     BEQ $t0 , $t1 , byebye
 13 00000014 00000000     NOP
 14 00000018 21290001     ADDI $t1 , $t1 , 1
 15 0000001C 08000004     J boucle
 16 00000020 00000000     NOP
 17                   byebye:
 18 00000024 0C000000     JAL viteviteauru
 19                   
 20                   .data
 21 00000000 000003E7 lunchtime: .word 12
 22 00000004 000003E7 .word menu
 23 00000008 000003E7 .word 12
 24                   
 25                   .bss
 26 00000000 000003E7 menu:.space 24

.symtab
 11	.text:00000010	boucle
 17	.text:00000024	byebye
 21	.data:00000000	lunchtime
 26	.bss :00000000	menu

rel.text
00000000    R_MIPS_HI16   .text:000004d2  lunchtime
00000010    R_MIPS_HI16   .text:000004d2  byebye
0000001c    R_MIPS_26    .text:000004d2  boucle

rel.data
00000004    R_MIPS_32    .data:000004d2  menu
