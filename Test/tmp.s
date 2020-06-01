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

myfunc_binary_search:
  addi $sp, $sp, -88
  lw $t1, 8($fp)
  sw $t1, -4($fp)
  lw $t1, 12($fp)
  sw $t1, -8($fp)
  lw $t1, 16($fp)
  sw $t1, -12($fp)
  li $t1, 0
  sw $t1, -16($fp)
  lw $t2, -12($fp)
  li $t3, 1
  sub $t1, $t2, $t3
  sw $t1, -20($fp)
  lw $t2, -20($fp)
  move $t1, $t2
  sw $t1, -24($fp)
  li $t1, 0
  sw $t1, -28($fp)
  li $t1, 0
  sw $t1, -32($fp)
label1:
  lw $t1, -16($fp)
  lw $t2, -24($fp)
  ble $t1, $t2, label4
  j label3
label4:
  lw $t1, -32($fp)
  li $t2, 0
  beq $t1, $t2, label2
  j label3
label2:
  lw $t2, -28($fp)
  li $t3, 1
  add $t1, $t2, $t3
  sw $t1, -36($fp)
  lw $t2, -36($fp)
  move $t1, $t2
  sw $t1, -28($fp)
  lw $t2, -16($fp)
  lw $t3, -24($fp)
  add $t1, $t2, $t3
  sw $t1, -40($fp)
  li $t3, 2
  lw $t2, -40($fp)
  div $t2, $t3
  mflo $t1
  sw $t1, -44($fp)
  lw $t2, -44($fp)
  move $t1, $t2
  sw $t1, -48($fp)
  li $t2, 4
  lw $t3, -48($fp)
  mul $t1, $t2, $t3
  sw $t1, -52($fp)
  lw $t2, -8($fp)
  lw $t3, -52($fp)
  add $t1, $t2, $t3
  sw $t1, -56($fp)
  lw $t1, -4($fp)
  lw $t3, -56($fp)
  lw $t2, 0($t3)
  blt $t1, $t2, label5
  j label6
label5:
  lw $t2, -48($fp)
  li $t3, 1
  sub $t1, $t2, $t3
  sw $t1, -60($fp)
  lw $t2, -60($fp)
  move $t1, $t2
  sw $t1, -24($fp)
  j label7
label6:
  li $t2, 4
  lw $t3, -48($fp)
  mul $t1, $t2, $t3
  sw $t1, -64($fp)
  lw $t2, -8($fp)
  lw $t3, -64($fp)
  add $t1, $t2, $t3
  sw $t1, -68($fp)
  lw $t1, -4($fp)
  lw $t3, -68($fp)
  lw $t2, 0($t3)
  bgt $t1, $t2, label8
  j label9
label8:
  lw $t2, -48($fp)
  li $t3, 1
  add $t1, $t2, $t3
  sw $t1, -72($fp)
  lw $t2, -72($fp)
  move $t1, $t2
  sw $t1, -16($fp)
  j label10
label9:
  li $t2, 4
  lw $t3, -48($fp)
  mul $t1, $t2, $t3
  sw $t1, -76($fp)
  lw $t2, -8($fp)
  lw $t3, -76($fp)
  add $t1, $t2, $t3
  sw $t1, -80($fp)
  lw $t1, -4($fp)
  lw $t3, -80($fp)
  lw $t2, 0($t3)
  beq $t1, $t2, label11
  j label12
label11:
  lw $t2, -48($fp)
  li $t3, 1
  add $t1, $t2, $t3
  sw $t1, -84($fp)
  lw $t2, -84($fp)
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
  lw $t2, -28($fp)
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
  li $t1, 1
  sw $t1, -32($fp)
label12:
label10:
label7:
  j label1
label3:
  lw $t1, -32($fp)
  li $t2, 0
  beq $t1, $t2, label13
  j label14
label13:
  li $t1, -1
  sw $t1, -88($fp)
  lw $t2, -88($fp)
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
label14:
  move $v0, $0
  jr $ra

main:
  move $fp, $sp
  addi $sp, $sp, -64
  li $t1, 0
  sw $t1, -4($fp)
  li $t1, 7
  sw $t1, -36($fp)
label15:
  lw $t1, -4($fp)
  lw $t2, -36($fp)
  blt $t1, $t2, label16
  j label17
label16:
  li $t2, 4
  lw $t3, -4($fp)
  mul $t1, $t2, $t3
  sw $t1, -40($fp)
  li $t3, -32
  add $t2, $fp, $t3
  lw $t3, -40($fp)
  add $t1, $t2, $t3
  sw $t1, -44($fp)
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
  sw $t1, -48($fp)
  lw $t1, -44($fp)
  lw $t2, -48($fp)
  sw $t2, 0($t1)
  lw $t2, -4($fp)
  li $t3, 1
  add $t1, $t2, $t3
  sw $t1, -52($fp)
  lw $t2, -52($fp)
  move $t1, $t2
  sw $t1, -4($fp)
  j label15
label17:
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
  sw $t1, -56($fp)
  lw $t2, -56($fp)
  move $t1, $t2
  sw $t1, -60($fp)
  addi $sp, $sp, -4
  lw $t1, -36($fp)
  sw $t1, 0($sp)
  addi $sp, $sp, -4
  li $t2, -32
  add $t1, $fp, $t2
  sw $t1, 0($sp)
  addi $sp, $sp, -4
  lw $t1, -60($fp)
  sw $t1, 0($sp)
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  addi $sp, $sp, -4
  sw $fp, 0($sp)
  move $fp, $sp
  jal myfunc_binary_search
  move $sp, $fp
  lw $fp, 0($sp)
  addi $sp, $sp, 4
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  addi $sp, $sp, 12
  move $t1, $v0
  sw $t1, -64($fp)
  move $v0, $0
  jr $ra

