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

fact:
  addi $sp, $sp, -16
  lw $t1, 8($fp)
  sw $t1, -4($fp)
  lw $t1, -4($fp)
  li $t2, 1
  beq $t1, $t2, label1
  j label2
label1:
  lw $t2, -4($fp)
  move $v0, $t2
  jr $ra
  j label3
label2:
  lw $t2, -4($fp)
  addi $t1, $t2, -1
  sw $t1, -8($fp)
  addi $sp, $sp, -4
  lw $t1, -8($fp)
  sw $t1, 0($sp)
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  addi $sp, $sp, -4
  sw $fp, 0($sp)
  move $fp, $sp
  jal fact
  move $sp, $fp
  lw $fp, 0($sp)
  addi $sp, $sp, 4
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  addi $sp, $sp, 4
  move $t1, $v0
  sw $t1, -12($fp)
  lw $t2, -4($fp)
  lw $t3, -12($fp)
  mul $t1, $t2, $t3
  sw $t1, -16($fp)
  lw $t2, -16($fp)
  move $v0, $t2
  jr $ra
label3:

main:
  move $fp, $sp
  addi $sp, $sp, -16
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
  sw $t1, -4($fp)
  lw $t2, -4($fp)
  move $t1, $t2
  sw $t1, -8($fp)
  lw $t1, -8($fp)
  li $t2, 1
  bgt $t1, $t2, label4
  j label5
label4:
  addi $sp, $sp, -4
  lw $t1, -8($fp)
  sw $t1, 0($sp)
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  addi $sp, $sp, -4
  sw $fp, 0($sp)
  move $fp, $sp
  jal fact
  move $sp, $fp
  lw $fp, 0($sp)
  addi $sp, $sp, 4
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  addi $sp, $sp, 4
  move $t1, $v0
  sw $t1, -12($fp)
  lw $t2, -12($fp)
  move $t1, $t2
  sw $t1, -16($fp)
  j label6
label5:
  li $t1, 1
  sw $t1, -16($fp)
label6:
  lw $t2, -16($fp)
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
  move $v0, $0
  jr $ra

