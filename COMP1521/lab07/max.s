max:
  # prologue
  addi $sp, $sp, -8
  sw $ra, 0($sp)
  sw $s0, 4($sp)

  #int first_element = a[0];
  lw $s0, ($a0)
  # if (length == 1) {
  #      return first_element;
  #  }
  bne $a1, 1, end1
  move $v0, $s0
  j max_return
end1:
  #calculate &a[1]
  # &a -> a0, &a[1]
  addi $a0, $a0, 4

  # length -1
  addi $a1, $a1, -1
  #int max_so_far = max(&a[1], length - 1);
  jal max
  # v0 is holding max so far
  move $t0, $v0

  #if (first_element > max_so_far) {
  #   max_so_far = first_element;
  # }

  ble $s0, $t0, end2
  move $t0, $s0
end2:
  #return max_so_far;
  move $v0, $t0
  j max_return
//.....


max_return:
  # epilogue
  lw $s0, 4($sp)
  lw $ra, 0($sp)
  addi $sp, $sp, 8
  jr $ra

 > ORIGINAL POSITION
