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

myfunc_Swap:
  addi $sp, $sp, -48
  lw $t1, 8($fp)
  sw $t1, -4($fp)
  lw $t1, 12($fp)
  sw $t1, -8($fp)
  lw $t1, 16($fp)
  sw $t1, -12($fp)
  li $t2, 4
  lw $t3, -8($fp)
  mul $t1, $t2, $t3
  sw $t1, -16($fp)
  lw $t2, -4($fp)
  lw $t3, -16($fp)
  add $t1, $t2, $t3
  sw $t1, -20($fp)
  lw $t2, -20($fp)
  lw $t1, 0($t2)
  sw $t1, -24($fp)
  li $t2, 4
  lw $t3, -8($fp)
  mul $t1, $t2, $t3
  sw $t1, -28($fp)
  lw $t2, -4($fp)
  lw $t3, -28($fp)
  add $t1, $t2, $t3
  sw $t1, -32($fp)
  li $t2, 4
  lw $t3, -12($fp)
  mul $t1, $t2, $t3
  sw $t1, -36($fp)
  lw $t2, -4($fp)
  lw $t3, -36($fp)
  add $t1, $t2, $t3
  sw $t1, -40($fp)
  lw $t1, -32($fp)
  lw $t2, -40($fp)
  lw $t3, 0($t2)
  sw $t3, 0($t1)
  li $t2, 4
  lw $t3, -12($fp)
  mul $t1, $t2, $t3
  sw $t1, -44($fp)
  lw $t2, -4($fp)
  lw $t3, -44($fp)
  add $t1, $t2, $t3
  sw $t1, -48($fp)
  lw $t1, -48($fp)
  lw $t2, -24($fp)
  sw $t2, 0($t1)
  move $v0, $0
  jr $ra

myfunc_Partition:
  addi $sp, $sp, -56
  lw $t1, 8($fp)
  sw $t1, -4($fp)
  lw $t1, 12($fp)
  sw $t1, -8($fp)
  lw $t1, 16($fp)
  sw $t1, -12($fp)
  li $t2, 4
  lw $t3, -8($fp)
  mul $t1, $t2, $t3
  sw $t1, -16($fp)
  lw $t2, -4($fp)
  lw $t3, -16($fp)
  add $t1, $t2, $t3
  sw $t1, -20($fp)
  lw $t2, -20($fp)
  lw $t1, 0($t2)
  sw $t1, -24($fp)
label1:
  lw $t1, -8($fp)
  lw $t2, -12($fp)
  blt $t1, $t2, label2
  j label3
label2:
label4:
  lw $t1, -8($fp)
  lw $t2, -12($fp)
  blt $t1, $t2, label7
  j label6
label7:
  li $t2, 4
  lw $t3, -12($fp)
  mul $t1, $t2, $t3
  sw $t1, -28($fp)
  lw $t2, -4($fp)
  lw $t3, -28($fp)
  add $t1, $t2, $t3
  sw $t1, -32($fp)
  lw $t2, -32($fp)
  lw $t1, 0($t2)
  lw $t2, -24($fp)
  bge $t1, $t2, label5
  j label6
label5:
  lw $t2, -12($fp)
  li $t3, 1
  sub $t1, $t2, $t3
  sw $t1, -36($fp)
  lw $t2, -36($fp)
  move $t1, $t2
  sw $t1, -12($fp)
  j label4
label6:
  addi $sp, $sp, -4
  lw $t1, -12($fp)
  sw $t1, 0($sp)
  addi $sp, $sp, -4
  lw $t1, -8($fp)
  sw $t1, 0($sp)
  addi $sp, $sp, -4
  lw $t1, -4($fp)
  sw $t1, 0($sp)
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  addi $sp, $sp, -4
  sw $fp, 0($sp)
  move $fp, $sp
  jal myfunc_Swap
  move $sp, $fp
  lw $fp, 0($sp)
  addi $sp, $sp, 4
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  addi $sp, $sp, 12
  move $t1, $v0
  sw $t1, -40($fp)
label8:
  lw $t1, -8($fp)
  lw $t2, -12($fp)
  blt $t1, $t2, label11
  j label10
label11:
  li $t2, 4
  lw $t3, -8($fp)
  mul $t1, $t2, $t3
  sw $t1, -44($fp)
  lw $t2, -4($fp)
  lw $t3, -44($fp)
  add $t1, $t2, $t3
  sw $t1, -48($fp)
  lw $t2, -48($fp)
  lw $t1, 0($t2)
  lw $t2, -24($fp)
  ble $t1, $t2, label9
  j label10
label9:
  lw $t2, -8($fp)
  li $t3, 1
  add $t1, $t2, $t3
  sw $t1, -52($fp)
  lw $t2, -52($fp)
  move $t1, $t2
  sw $t1, -8($fp)
  j label8
label10:
  addi $sp, $sp, -4
  lw $t1, -12($fp)
  sw $t1, 0($sp)
  addi $sp, $sp, -4
  lw $t1, -8($fp)
  sw $t1, 0($sp)
  addi $sp, $sp, -4
  lw $t1, -4($fp)
  sw $t1, 0($sp)
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  addi $sp, $sp, -4
  sw $fp, 0($sp)
  move $fp, $sp
  jal myfunc_Swap
  move $sp, $fp
  lw $fp, 0($sp)
  addi $sp, $sp, 4
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  addi $sp, $sp, 12
  move $t1, $v0
  sw $t1, -56($fp)
  j label1
label3:
  lw $t2, -8($fp)
  move $v0, $t2
  jr $ra

myfunc_QuickSort:
  addi $sp, $sp, -36
  lw $t1, 8($fp)
  sw $t1, -4($fp)
  lw $t1, 12($fp)
  sw $t1, -8($fp)
  lw $t1, 16($fp)
  sw $t1, -12($fp)
  lw $t1, -8($fp)
  lw $t2, -12($fp)
  blt $t1, $t2, label12
  j label13
label12:
  addi $sp, $sp, -4
  lw $t1, -12($fp)
  sw $t1, 0($sp)
  addi $sp, $sp, -4
  lw $t1, -8($fp)
  sw $t1, 0($sp)
  addi $sp, $sp, -4
  lw $t1, -4($fp)
  sw $t1, 0($sp)
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  addi $sp, $sp, -4
  sw $fp, 0($sp)
  move $fp, $sp
  jal myfunc_Partition
  move $sp, $fp
  lw $fp, 0($sp)
  addi $sp, $sp, 4
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  addi $sp, $sp, 12
  move $t1, $v0
  sw $t1, -16($fp)
  lw $t2, -16($fp)
  move $t1, $t2
  sw $t1, -20($fp)
  lw $t2, -20($fp)
  li $t3, 1
  sub $t1, $t2, $t3
  sw $t1, -24($fp)
  addi $sp, $sp, -4
  lw $t1, -24($fp)
  sw $t1, 0($sp)
  addi $sp, $sp, -4
  lw $t1, -8($fp)
  sw $t1, 0($sp)
  addi $sp, $sp, -4
  lw $t1, -4($fp)
  sw $t1, 0($sp)
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  addi $sp, $sp, -4
  sw $fp, 0($sp)
  move $fp, $sp
  jal myfunc_QuickSort
  move $sp, $fp
  lw $fp, 0($sp)
  addi $sp, $sp, 4
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  addi $sp, $sp, 12
  move $t1, $v0
  sw $t1, -28($fp)
  lw $t2, -20($fp)
  li $t3, 1
  add $t1, $t2, $t3
  sw $t1, -32($fp)
  addi $sp, $sp, -4
  lw $t1, -12($fp)
  sw $t1, 0($sp)
  addi $sp, $sp, -4
  lw $t1, -32($fp)
  sw $t1, 0($sp)
  addi $sp, $sp, -4
  lw $t1, -4($fp)
  sw $t1, 0($sp)
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  addi $sp, $sp, -4
  sw $fp, 0($sp)
  move $fp, $sp
  jal myfunc_QuickSort
  move $sp, $fp
  lw $fp, 0($sp)
  addi $sp, $sp, 4
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  addi $sp, $sp, 12
  move $t1, $v0
  sw $t1, -36($fp)
label13:
  move $v0, $0
  jr $ra

main:
  move $fp, $sp
  addi $sp, $sp, -80
  li $t1, 8
  sw $t1, -4($fp)
  li $t1, 0
  sw $t1, -40($fp)
label14:
  lw $t1, -40($fp)
  lw $t2, -4($fp)
  blt $t1, $t2, label15
  j label16
label15:
  li $t2, 4
  lw $t3, -40($fp)
  mul $t1, $t2, $t3
  sw $t1, -44($fp)
  li $t3, -36
  add $t2, $fp, $t3
  lw $t3, -44($fp)
  add $t1, $t2, $t3
  sw $t1, -48($fp)
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
  sw $t1, -52($fp)
  lw $t1, -48($fp)
  lw $t2, -52($fp)
  sw $t2, 0($t1)
  lw $t2, -40($fp)
  li $t3, 1
  add $t1, $t2, $t3
  sw $t1, -56($fp)
  lw $t2, -56($fp)
  move $t1, $t2
  sw $t1, -40($fp)
  j label14
label16:
  lw $t2, -4($fp)
  li $t3, 1
  sub $t1, $t2, $t3
  sw $t1, -60($fp)
  addi $sp, $sp, -4
  lw $t1, -60($fp)
  sw $t1, 0($sp)
  addi $sp, $sp, -4
  li $t1, 0
  sw $t1, 0($sp)
  addi $sp, $sp, -4
  li $t2, -36
  add $t1, $fp, $t2
  sw $t1, 0($sp)
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  addi $sp, $sp, -4
  sw $fp, 0($sp)
  move $fp, $sp
  jal myfunc_QuickSort
  move $sp, $fp
  lw $fp, 0($sp)
  addi $sp, $sp, 4
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  addi $sp, $sp, 12
  move $t1, $v0
  sw $t1, -64($fp)
  li $t1, 0
  sw $t1, -40($fp)
label17:
  lw $t1, -40($fp)
  lw $t2, -4($fp)
  blt $t1, $t2, label18
  j label19
label18:
  li $t2, 4
  lw $t3, -40($fp)
  mul $t1, $t2, $t3
  sw $t1, -68($fp)
  li $t3, -36
  add $t2, $fp, $t3
  lw $t3, -68($fp)
  add $t1, $t2, $t3
  sw $t1, -72($fp)
  lw $t2, -72($fp)
  lw $t1, 0($t2)
  sw $t1, -76($fp)
  lw $t2, -76($fp)
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
  lw $t2, -40($fp)
  li $t3, 1
  add $t1, $t2, $t3
  sw $t1, -80($fp)
  lw $t2, -80($fp)
  move $t1, $t2
  sw $t1, -40($fp)
  j label17
label19:
  move $v0, $0
  jr $ra

