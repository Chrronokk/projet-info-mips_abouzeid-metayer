# TEST_RETURN_CODE=PAS

.text
.set noreorder



  ADDI  $t9,$zero,EXIT
  ADDI  $t2,$zero,-	43     	# $t2 <- -43
  ADDI  $t3,	$0,0xffff      	# $t3 <- 0xff

#fait la division
  DIV  $t2,$t3
  MFLO $t0
  MFHI $t1
  BEQ $t1,$zero, mult
  ADD $t2,$zero,$zero
  J EXIT


mult:
  NOP
  NOP
  MULT $t0,$t3
  MFLO $t0
  MFHI $t1
  ADD $t5,$zero,$zero
  BNE $t1,$t5,EXIT
  BEQ $t0,$t2,reussi
  ADD $t2,$zero,$zero
  J EXIT
reussi:
  ADDI $t2,$zero,0x1
  J EXIT


EXIT    :

## The End

.data
.byte 12,0xAA,0xBB,0xCC,0xdd
.byte 0xFF
.word 0xAABBCCDD
