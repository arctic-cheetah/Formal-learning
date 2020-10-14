
# i in register $t0,
# x = t3
# y = t4
# swap = t5
# j = t6
# numbers[i] = t2
# numbers[j] = t7

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


    # PUT YOUR CODE HERE


    li $t0, 1           # i = 1
    li $t6, 0           # j = 0
loop1:
    bge $t0, 10, end1   # while (i < 10) {

    mul $t1, $t0, 4     #   calculate &numbers[i]
    la $t2, numbers     #
    add $t2, $t1, $t2   #
    lw $t3, ($t2)       #   x = numbers[i]

    mul $t1, $t6, 4
    la $t7, numbers
    add $t7, $t7, $t1   # calculate numbers[j]
    lw $t4, ($t7)       # y = numbers[j]

    bge $t3, $t4, skip  # if (x >= y) goto skip
    sw $t4, ($t2)       # numbers[i] = y;
    sw $t3, ($t7)       # numbers[i - 1] = x;
skip:

    lw $a0, ($t7)
    li $v0, 1           #   printf("%d", numbers[i])
    syscall

    li   $a0, '\n'      #   printf("%c", '\n');
    li   $v0, 11
    syscall


    add $t6, $t6, 1     # j+=1;
    add $t0, $t0, 1     #   i++
    b loop1             # }
end1:
    
    mul $t1, $t0, 4     #   calculate &numbers[i]
    la $t2, numbers     #
    add $t2, $t1, $t2   #
    lw $t3, ($t2)       #   x = numbers[i]

    lw $a0, ($t2)
    li $v0, 1           #   printf("%d", numbers[i])
    syscall

    li   $a0, '\n'      #   printf("%c", '\n');
    li   $v0, 11
    syscall

    li $v0, 10
    syscall             # return

.data

numbers:
    .word 0:10 # int numbers[10] = {0};
