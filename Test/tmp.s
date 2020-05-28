.data 
_prompt: .asciiz "Enter an integer:" 
_ret: .asciiz "\n" 
.globl main 
.text 
read: 
  li $v0, 4 
  la $a0, _prompt 
  syscall 
  li $v0, 5
  syscall
  jr $ra

write:
  li $v0, 1
  syscall
  li $v0, 4
  la $a0, _ret
  syscall
  move $v0, $0
  jr $ra

main:
  move $fp, $sp
  addi $sp, $sp, -1052
  li $t1, 0
  sw $t1, -4($fp)
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  addi $sp, $sp, -4
  sw $fp, 0($sp)
  move $fp, $sp
  jal read
  move $sp, $fp
  lw $fp, 0($sp)
  addi $sp, $sp, 4
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  move $t1, $v0
  sw $t1, -908($fp)
  lw $t2, -908($fp)
  move $t1, $t2
  sw $t1, -912($fp)
label1:
  lw $t1, -4($fp)
  lw $t2, -912($fp)
  blt $t1, $t2, label2
  j label3
label2:
  li $t2, 60
  lw $t3, -4($fp)
  mul $t1, $t2, $t3
  sw $t1, -916($fp)
  li $t3, -904
  add $t2, $fp, $t3
  lw $t3, -916($fp)
  add $t1, $t2, $t3
  sw $t1, -920($fp)
  li $t1, 0
  sw $t1, -924($fp)
  lw $t2, -920($fp)
  lw $t3, -924($fp)
  add $t1, $t2, $t3
  sw $t1, -928($fp)
  lw $t1, -928($fp)
  li $t2, 1
  sw $t2, 0($t1)
  li $t1, 1
  sw $t1, -932($fp)
label4:
  lw $t1, -932($fp)
  lw $t2, -4($fp)
  blt $t1, $t2, label5
  j label6
label5:
  li $t2, 60
  lw $t3, -4($fp)
  mul $t1, $t2, $t3
  sw $t1, -936($fp)
  li $t3, -904
  add $t2, $fp, $t3
  lw $t3, -936($fp)
  add $t1, $t2, $t3
  sw $t1, -940($fp)
  li $t2, 4
  lw $t3, -932($fp)
  mul $t1, $t2, $t3
  sw $t1, -944($fp)
  lw $t2, -940($fp)
  lw $t3, -944($fp)
  add $t1, $t2, $t3
  sw $t1, -948($fp)
  lw $t2, -4($fp)
  li $t3, 1
  sub $t1, $t2, $t3
  sw $t1, -952($fp)
  li $t2, 60
  lw $t3, -952($fp)
  mul $t1, $t2, $t3
  sw $t1, -956($fp)
  li $t3, -904
  add $t2, $fp, $t3
  lw $t3, -956($fp)
  add $t1, $t2, $t3
  sw $t1, -960($fp)
  lw $t2, -932($fp)
  li $t3, 1
  sub $t1, $t2, $t3
  sw $t1, -964($fp)
  li $t2, 4
  lw $t3, -964($fp)
  mul $t1, $t2, $t3
  sw $t1, -968($fp)
  lw $t2, -960($fp)
  lw $t3, -968($fp)
  add $t1, $t2, $t3
  sw $t1, -972($fp)
  lw $t2, -4($fp)
  li $t3, 1
  sub $t1, $t2, $t3
  sw $t1, -976($fp)
  li $t2, 60
  lw $t3, -976($fp)
  mul $t1, $t2, $t3
  sw $t1, -980($fp)
  li $t3, -904
  add $t2, $fp, $t3
  lw $t3, -980($fp)
  add $t1, $t2, $t3
  sw $t1, -984($fp)
  li $t2, 4
  lw $t3, -932($fp)
  mul $t1, $t2, $t3
  sw $t1, -988($fp)
  lw $t2, -984($fp)
  lw $t3, -988($fp)
  add $t1, $t2, $t3
  sw $t1, -992($fp)
  lw $t3, -972($fp)
  lw $t2, 0($t3)
  lw $t4, -992($fp)
  lw $t3, 0($t4)
  add $t1, $t2, $t3
  sw $t1, -996($fp)
  lw $t1, -948($fp)
  lw $t2, -996($fp)
  sw $t2, 0($t1)
  lw $t2, -932($fp)
  li $t3, 1
  add $t1, $t2, $t3
  sw $t1, -1000($fp)
  lw $t2, -1000($fp)
  move $t1, $t2
  sw $t1, -932($fp)
  j label4
label6:
  li $t2, 60
  lw $t3, -4($fp)
  mul $t1, $t2, $t3
  sw $t1, -1004($fp)
  li $t3, -904
  add $t2, $fp, $t3
  lw $t3, -1004($fp)
  add $t1, $t2, $t3
  sw $t1, -1008($fp)
  li $t2, 4
  lw $t3, -932($fp)
  mul $t1, $t2, $t3
  sw $t1, -1012($fp)
  lw $t2, -1008($fp)
  lw $t3, -1012($fp)
  add $t1, $t2, $t3
  sw $t1, -1016($fp)
  lw $t1, -1016($fp)
  li $t2, 1
  sw $t2, 0($t1)
  lw $t2, -4($fp)
  li $t3, 1
  add $t1, $t2, $t3
  sw $t1, -1020($fp)
  lw $t2, -1020($fp)
  move $t1, $t2
  sw $t1, -4($fp)
  j label1
label3:
  li $t1, 0
  sw $t1, -932($fp)
label7:
  lw $t2, -912($fp)
  li $t3, 1
  sub $t1, $t2, $t3
  sw $t1, -1024($fp)
  lw $t1, -932($fp)
  lw $t2, -1024($fp)
  ble $t1, $t2, label8
  j label9
label8:
  lw $t2, -912($fp)
  li $t3, 1
  sub $t1, $t2, $t3
  sw $t1, -1028($fp)
  li $t2, 60
  lw $t3, -1028($fp)
  mul $t1, $t2, $t3
  sw $t1, -1032($fp)
  li $t3, -904
  add $t2, $fp, $t3
  lw $t3, -1032($fp)
  add $t1, $t2, $t3
  sw $t1, -1036($fp)
  li $t2, 4
  lw $t3, -932($fp)
  mul $t1, $t2, $t3
  sw $t1, -1040($fp)
  lw $t2, -1036($fp)
  lw $t3, -1040($fp)
  add $t1, $t2, $t3
  sw $t1, -1044($fp)
  lw $t2, -1044($fp)
  lw $t1, 0($t2)
  sw $t1, -1048($fp)
  lw $t2, -1048($fp)
  move $a0, $t2
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  addi $sp, $sp, -4
  sw $fp, 0($sp)
  move $fp, $sp
  jal write
  move $sp, $fp
  lw $fp, 0($sp)
  addi $sp, $sp, 4
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  lw $t2, -932($fp)
  li $t3, 1
  add $t1, $t2, $t3
  sw $t1, -1052($fp)
  lw $t2, -1052($fp)
  move $t1, $t2
  sw $t1, -932($fp)
  j label7
label9:
  move $v0, $0
  jr $ra

