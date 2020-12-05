#t0 = size
#t1 = array
#t2 = index

main:
    addi $sp, $sp, -4
    sw $ra, 0($sp)

    la $a0, prompt
    li $v0, 4
    syscall

    jal array

    la $a0, success
    li $v0, 4
    syscall

    li $v0, 10
    syscall


array:
    li $v0, 5
    syscall

    addi $fp, $sp, 0
    li $a0, 1
                                #Initialise an array of ints to 1
loop1:
    bge $t2, $v0, end1

    addi $sp, $sp, 4
    sw $a0, 0($sp)

    addi $t2, $t2, 1
    j loop1
end1:

    addi $v0, $sp, 0
    move $sp, $fp               #Correctly return the stack pointer
    jr $ra

    .data
prompt: .asciiz "Enter the size of the array: "
success: .asciiz "Success\n"
