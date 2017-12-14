  1                   # TEST_RETURN_CODE=PASS
  2                   # allons au ru
  3                   
  4                   
  5                   .set noreorder
  6                   .text
  7 00000000 000001C8     LW $t0 , lunchtime
  7 00000004 000001C8 
  8 00000008 000001C8     LW $6, -0x200($7)
  9 0000000C 000001C8     ADDI $t1,$zero,8
 10                   
 11                   boucle:
 12 00000010 000001C8     BEQ $t0 , $t1 , byebye
 13 00000014 000001C8     NOP
 14 00000018 000001C8     ADDI $t1 , $t1 , 1
 15 0000001C 000001C8     J boucle
 16 00000020 000001C8     NOP
 16 00000024 000001C8 
 17                   byebye:
 18 00000024 000001C8     JAL viteviteauru
