#number = t0
#i = t1
#remainder = t2
#t3 = 7
#t4 = 11

main:

    la $a0, prompt  #printf("Enter number: ");
    li $v0, 4
    syscall

    li $v0, 5       #scanf("%d", &number);
    syscall
    move $t0, $v0

    li $t1, 1       #i = 1
    li $t3, 7
    li $t4, 11


loop:
    bge $t1, $t0, end

    div $t1, $t3      #if (i % 7 == 0 || i % 11 == 0)
    mfhi $t2
    beq $t2, 0, print
    div $t1, $t4
    mfhi $t2
    beq $t2, 0, print
    j skipPrint
print:              #printf("%d\n", i);
    li $v0, 1
    move $a0, $t1
    syscall

    li $a0, '\n'
    li $v0, 11
    syscall

skipPrint:


    addi $t1, $t1, 1
    j loop

end:
    li $v0, 10
    syscall

.data
    prompt: .asciiz "Enter a number: "
