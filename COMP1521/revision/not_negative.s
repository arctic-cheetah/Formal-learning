#  read numbers until a non-negative number entered
# x in $t0

main:


loop1:

    la $a0, prompt0                #printf("Enter a number: ");
    li $v0, 4
    syscall

    li $v0, 5                      #scanf("%d", &x);
    syscall
    move $t0, $v0

    bge $t0, 0, end1               #if (x >= 0) goto end1

    la $a0, prompt1                #printf("Enter a positive number\n");
    li $v0, 4
    syscall

    j loop1
end1:

    la $a0, entry
    li $v0, 4
    syscall

    move $a0, $t0
    li $v0, 1
    syscall

    li $a0, 10
    li $v0, 11
    syscall

    li $v0, 10
    syscall


.data
    prompt0: .asciiz "Enter a number: "
    prompt1: .asciiz "Enter a positive number\n"
    entry: .asciiz "You entered: "
