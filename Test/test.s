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
  addi $sp, $sp, -100
  li $t1, 0
  sw $t1, -20($fp)
  li $t3, -16
  add $t2, $fp, $t3
  lw $t3, -20($fp)
  add $t1, $t2, $t3
  sw $t1, -24($fp)
  li $t1, 0
  sw $t1, -28($fp)
  lw $t2, -24($fp)
  lw $t3, -28($fp)
  add $t1, $t2, $t3
  sw $t1, -32($fp)
  lw $t1, -32($fp)
  li $t2, 1
  sw $t2, 0($t1)
  li $t1, 0
  sw $t1, -36($fp)
  li $t3, -16
  add $t2, $fp, $t3
  lw $t3, -36($fp)
  add $t1, $t2, $t3
  sw $t1, -40($fp)
  li $t1, 4
  sw $t1, -44($fp)
  lw $t2, -40($fp)
  lw $t3, -44($fp)
  add $t1, $t2, $t3
  sw $t1, -48($fp)
  lw $t1, -48($fp)
  li $t2, 2
  sw $t2, 0($t1)
  li $t1, 8
  sw $t1, -52($fp)
  li $t3, -16
  add $t2, $fp, $t3
  lw $t3, -52($fp)
  add $t1, $t2, $t3
  sw $t1, -56($fp)
  li $t1, 4
  sw $t1, -60($fp)
  lw $t2, -56($fp)
  lw $t3, -60($fp)
  add $t1, $t2, $t3
  sw $t1, -64($fp)
  lw $t1, -64($fp)
  li $t2, 4
  sw $t2, 0($t1)
  li $t1, 8
  sw $t1, -68($fp)
  li $t3, -16
  add $t2, $fp, $t3
  lw $t3, -68($fp)
  add $t1, $t2, $t3
  sw $t1, -72($fp)
  li $t1, 0
  sw $t1, -76($fp)
  lw $t2, -72($fp)
  lw $t3, -76($fp)
  add $t1, $t2, $t3
  sw $t1, -80($fp)
  lw $t1, -80($fp)
  li $t2, 3
  sw $t2, 0($t1)
  li $t1, 8
  sw $t1, -84($fp)
  li $t3, -16
  add $t2, $fp, $t3
  lw $t3, -84($fp)
  add $t1, $t2, $t3
  sw $t1, -88($fp)
  li $t1, 4
  sw $t1, -92($fp)
  lw $t2, -88($fp)
  lw $t3, -92($fp)
  add $t1, $t2, $t3
  sw $t1, -96($fp)
  lw $t2, -96($fp)
  lw $t1, 0($t2)
  sw $t1, -100($fp)
  lw $t2, -100($fp)
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

