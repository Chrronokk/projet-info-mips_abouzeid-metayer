# allons au mandela
# allons au ru
.set noreorder
.text
	LW $t0 , lunchtime
	LW $6, -0x200($7)
	LW $8, 0xaa0($9)
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
	lunchtime : 
	.byte  2, 0x4
	.space 12
	.asciiz "blabla","gabuzomeu"
.bss
.space 12



