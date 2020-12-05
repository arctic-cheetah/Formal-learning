#i = t0
#number = t1

main:
    la $a0, prompt
    li $v0, 4
    syscall         #printf("Enter number: ");

    li $v0, 5
    syscall
    move $t1, $v0   #scanf("%d", &number);

    li $t0, 1       #i = 1
loop:
    bgt $t0, $t1, end

    move $a0, $t0
    li $v0, 1
    syscall         #printf("%d", i);

    li $a0, '\n'  #printf("\n");
    li $v0, 11
    syscall

    addi $t0, $t0, 1    #i +=1
    j loop
end:
    li $v0, 10
    syscall

.data
    prompt: .asciiz "Enter a number: "
