  1                   # allons au mandela
  2                   # allons au ru
  3                   .set noreorder
  4                   .text
  5 00000000 000001C8     LW $t0, boucle
  5 00000004 000001C8 
  6 00000008 000001C8     LW $6, -0x200($7)
  7 0000000C 000001C8     LW $8, 0xaa0($9)
  8 00000010 000001C8     ADDI $t1,$zero,8
  9                   boucle:
 10 00000014 000001C8     BEQ $t0 , $t1 , byebye
 11 00000018 000001C8     NOP
 12 0000001C 000001C8     MOVE $3,$4
 13 00000020 000001C8     NEG $3,$4
 14 00000024 000001C8     LI $3,100
 15 00000028 000001C8     BLT $3,$4,boucle
 15 0000002C 000001C8 
 16 00000030 000001C8     ADDI $t1 , $t1 , 1
 17 00000034 000001C8     J boucle
 18 00000038 000001C8     NOP
 19 0000003C 000001C8     byebye: JAL viteviteauru
 20                   .data
 21 00000000 000003E7     lunchtime : .word 12
 22 00000004 000003E7     .word byebye
 23 00000008 000003E7     .byte  2, 0x4
 24 0000000A 000003E7     .space 12
 25                       .asciiz "blabla","gabuzomeu shadoks"
 26                   .bss
 27 00000000 000003E7 .space 12
 28 0000000C 000003E7 .space 12
 29                   .data
 30                   .text
 31 00000040 000001C8     LW $8, 0xaa0($9)
 32 00000044 000001C8     ADDI $t1,$zero,8

.symtab
  9	.text:00000014	boucle
 19	.text:0000003C	byebye
 21	.data:00000000	lunchtime
