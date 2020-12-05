

main:
    addi $sp, $sp, -4
    sw $ra, 0($sp)

    la $a0, list
    jal max

    move $a0, $v0
    li $v0, 1
    syscall

    addi $sp, $sp, 4

    li $a0, '\n'
    li $v0, 11
    syscall

    li $v0, 10
    syscall



max:
   # prologue
   addi $sp, $sp, -4
   sw   $fp, ($sp)
   la   $fp, ($sp)
   addi $sp, $sp, -4
   sw   $ra, ($sp)

   la $a0, 4($a0)
   # body
   #  if (list == NULL) return -1;
   #  int max = list->value;
   #  Node *curr = list;
   #  while (curr != NULL) {
   #     if (curr->value > max) max = curr->value;
   #     curr = curr->next;
   #  }
   #  return max;
   bne  $a0, $0, max1
   li   $v0, -1
   j    end_max
max1:
   move $s0, $a0       # use $s0 for curr
   lw   $v0, 0($s0)    # use $v0 for max
loop:
   beq  $s0, $0, end_max
   lw   $t0, 0($s0)    # $t0 = curr->value
   ble  $t0, $v0, max2
   move $v0, $t0       # max = curr->value
max2:
   lw   $s0, 4($s0)    # curr = curr->next
   j    loop
end_max:
   # epilogue
   lw   $ra, ($sp)
   addi $sp, $sp, 4
   lw   $fp, ($sp)
   addi $sp, $sp, 4
   jr   $ra

   .data
list:   .word node1
node1:  .word 1,  node2
node2:  .word 33, node3
node3:  .word 5,  node4
node4:  .word 22, node5
node5:  .word 65, node6
node6:  .word 42, node7
node7:  .word 59, node8
node8:  .word 2, 0
