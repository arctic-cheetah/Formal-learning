# read 10 numbers into an array
# bubblesort them
# then print the 10 numbers

#t0 = i
#t1 = swapped
#t2 = x
#t3 = y
#t4 = temp
#t5 = numbers[]


main:

loop1:
    bge $t0, 10, end1               #if (i >= 10) goto

    la $t2, numbers
    mul $t4, $t0, 4
    add $t2, $t2, $t4

    li $v0, 5
    syscall
    sw $v0, 0($t2)                  #scanf("%d", &numbers[i]);

    addi $t0, $t0, 1                #i++;
    j loop1
end1:

    li $t1, 1                       #swapped = 1

loop2:
    bne $t1, 1, end2                #if (!swapped) goto end2
    li $t1, 0                       #swapped = 0
    li $t0, 1                       #i = 1

loop3:
    bge $t0, 10, end3               #if (i >= 10) goto end3

    la $t5, numbers
    mul $t4, $t0, 4
    add $t5, $t5, $t4

    lw $t2, 0($t5)                  #int x = numbers[i];
    lw $t3, -4($t5)                 #int y = numbers[i - 1];

    bge $t2, $t3, skip              #if (x >= y) goto skip
    sw $t3, 0($t5)                  #numbers[i] = y;
    sw $t2, -4($t5)                 #numbers[i - 1] = x;
    li $t1, 1                       #swapped = 1
skip:
    addi $t0, $t0, 1                #i+=1
    j loop3
end3:

    j loop2
end2:

    li $t0, 0
loop4:
    bge $t0, 10, end4               #if (i >= 10) goto end4

    la $a0, numbers
    mul $t4, $t0, 4
    add $a0, $a0, $t4
    lw $a0, 0($a0)
    li $v0, 1
    syscall                         #printf("%d\n", numbers[i]);
    li $a0, 10
    li $v0, 11
    syscall

    addi $t0, $t0, 1                #i +=1
    j loop4
end4:

    li $v0, 10
    syscall


    .data
numbers: .word 0:10                 #int numbers[10] = { 0 };
