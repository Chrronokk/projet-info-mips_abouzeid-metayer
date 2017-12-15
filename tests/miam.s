# TEST_RETURN_CODE=PASS
# allons au ru blblblblblblblblblbbbl


.set noreorder
.text
    LW $t0 , lunchtime
    LW $6, -0x200($7)
    ADDI $t1,$zero,8

boucle:
    BEQ $t0 , $t1 , byebye
    NOP
    ADDI $t1 , $t1 , 1
    J boucle
    NOP
byebye:
    JAL viteviteauru

.data
lunchtime: .word 12
.word menu
.word 12

.bss
menu:.space 24
