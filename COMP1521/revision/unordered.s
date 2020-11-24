# Read 10 numbers into an array
# print 0 if they are in non-decreasing order
# print 1 otherwise

#t0 = i
#t1 = array
#temporary = t2
#t3 = swapped
#t4 = x
#t5 = y

main:

loop1:
    bge $t0, 10, end1               #if (i >= 10) goto end1

    la $t1, numbers
    mul $t2, $t0, 4
    add $t1, $t2, $t1               #calculate index

    li $v0, 5
    syscall
    sw $v0, 0($t1)                   #scanf("%d", &numbers[i])

    addi $t0, $t0, 1                #i+=1
    j loop1
end1:

    li $t0, 1                       #i = 1

loop2:
    bge $t0, 10, end2               #if (i >= 10) goto end1

    la $t4, numbers
    mul $t2, $t0, 4
    add $t4, $t2, $t4               #int x = numbers[i];

    lw $t5, -4($t4)                 #int y = numbers[i - 1];
    lw $t4, 0($t4)

    bge $t4, $t5, skip
    li $t3, 1                       #swapped = 1;
skip:


    addi $t0, $t0, 1                #i+=1
    j loop2
end2:

    li $v0, 1
    move $a0, $t3
    syscall                         #printf("%d\n", swapped);

    li $a0, 10
    li $v0, 11
    syscall

    li $v0, 10
    syscall


    .data

numbers: .word 0:10                 #int numbers[10] = { 0 };
