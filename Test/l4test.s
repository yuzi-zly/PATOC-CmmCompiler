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
  addi $fp, $sp, 8
  li $t1, 0
  addi $sp, $sp, -4
  sw $t1, 0($sp)
  li $t1, 1
  addi $sp, $sp, -4
  sw $t1, 0($sp)
  li $t1, 0
  addi $sp, $sp, -4
  sw $t1, 0($sp)
  lw $t2, 0($fp)
  addi $t1, $t2, -1
  addi $sp, $sp, -4
  sw $t1, 0($sp)
  lw $t2, -24($fp)
  move $t1, $t2
  addi $sp, $sp, -4
  sw $t1, 0($sp)
  lw $t2, -28($fp)
  addi $t1, $t2, -1
  addi $sp, $sp, -4
  sw $t1, 0($sp)
  lw $t2, -32($fp)
  move $t1, $t2
  sw $t1, -28($fp)
  move $v0, $0
  jr $ra

