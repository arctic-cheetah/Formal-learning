# read 10 numbers into an array
# bubblesort them
# then print the 10 numbers

# i in register $t0
# j = t3
# registers $t1, $t2, t7 used to hold temporary results
# swapped = t4
# x = t5
# y = t6

main:

    li $t0, 0           # i = 0
loop0:
    bge $t0, 10, end0   # while (i < 10) {

    li $v0, 5           #   scanf("%d", &numbers[i]);
    syscall             #

    mul $t1, $t0, 4     #   calculate &numbers[i]
    la $t2, numbers     #
    add $t2, $t1, $t2   #
    sw $v0, ($t2)       #   store entered number in array

    add $t0, $t0, 1     #   i++;
    b loop0             # }
end0:

    li $t4, 1           # swapped = 1;
loopSort:
    beq $t4, 0, endSort # if (!swapped) goto endSort
    li $t4, 0           # swapped = 0
    li $t0, 1           # i = 1
    li $t3, 0           # j = 0

loop1:
    bge $t0, 10, end1   # if (i >= 10) goto end1

    la $t2, numbers
    mul $t1, $t0, 4
    add $t2, $t2, $t1
    lw $t5, ($t2)       # x = numbers[i]

    la $t7, numbers
    mul $t1, $t3, 4
    add $t7, $t7, $t1
    lw $t6, ($t7)       # y = numbers[j]

    bge $t5, $t6, skipSwap # if (x >= y) goto skipSwap

    sw $t6, ($t2)       # numbers[i] = y
    sw $t5, ($t7)       # numbers[j] = x
    li $t4, 1           # swapped = 1
skipSwap:

    addi $t3, $t3, 1    #j+=1
    addi $t0, $t0, 1    #i+=1
    j loop1
end1:

    j loopSort
endSort:


    li $t0, 0           # i = 0
loop2:
    bge $t0, 10, end2   # while (i < 10) {

    mul $t1, $t0, 4     #   calculate &numbers[i]
    la $t2, numbers     #
    add $t2, $t1, $t2   #
    lw $a0, ($t2)       #   load numbers[i] into $a0
    li $v0, 1           #   printf("%d", numbers[i])
    syscall

    li   $a0, '\n'      #   printf("%c", '\n');
    li   $v0, 11
    syscall

    add $t0, $t0, 1     #   i++
    b loop2             # }
end2:

    li $v0, 10
    syscall

.data

numbers:
    .word 0 0 0 0 0 0 0 0 0 0  # int numbers[10] = {0};
