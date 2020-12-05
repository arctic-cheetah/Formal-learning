# read 10 numbers into an array
# swap any pairs of of number which are out of order
# then print the 10 numbers

#t0 = i
#t1 = x
#t2 = y
#t3 = temporary
#t4 = numbers[]


main:

loop1:
    bge $t0, 10, end1               #if (i >= 10) goto end1

    la $t1, numbers
    mul $t3, $t0, 4
    add $t1, $t3, $t1

    li $v0, 5                       #scanf("%d", &numbers[i]);
    syscall
    sw $v0, 0($t1)

    addi $t0, $t0, 1                #i+=1
    j loop1
end1:

    li $t0, 1                       #i = 1
loop2:
    bge $t0, 10, end2               #if (i >= 10) goto end1

    la $t4, numbers
    mul $t3, $t0, 4
    add $t4, $t4, $t3

    lw $t1, 0($t4)                  #int x = numbers[i];
    lw $t2, -4($t4)                 #int y = numbers[i - 1];

    bge $t1, $t2, skip
    sw $t2, 0($t4)                  #numbers[i] = y;
    sw $t1, -4($t4)                 #numbers[i - 1] = x;
skip:

    addi $t0, $t0, 1                #i+=1
    j loop2
end2:

    li $t0, 0                       #i = 0

loop3:
    bge $t0, 10, end3

    la $a0, numbers
    mul $t3, $t0, 4
    add $a0, $a0, $t3
    lw $a0, 0($a0)
    li $v0, 1
    syscall                         #printf("%d\n", numbers[i]);

    li $a0, 10
    li $v0, 11
    syscall


    addi $t0, $t0, 1
    j loop3
end3:

    li $v0, 10
    syscall



.data
numbers: .word 0:10                 #int numbers[10] = { 0 };
