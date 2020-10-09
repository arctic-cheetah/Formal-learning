# A factorial calculator
# n = t0
# i = t1;
# fact = t2

.text
main:

    la $a0, prompt  #printf("Enter a number")
    li $v0, 4
    syscall

    li $v0, 5       #scanf("%d", i)
    syscall
    move $t0, $v0

    li $t1, 1       #i = 1
    li $t2, 1       #fact = 1

loop:
    bgt $t1, $t0, endloop
    mul $t2, $t2, $t1
    addi $t1, $t1, 1
    j loop

endloop:

    la $a0, result  #printf("n! = ")
    li $v0, 4
    syscall

    move $a0, $t2      #printf("%d", fact)
    li $v0, 1
    syscall

    li $a0, '\n'    #printf(""\n")
    li $v0, 11
    syscall

    li $v0, 10
    syscall

.data
    prompt: .asciiz "Enter a number (n): "
    result: .asciiz "n! = "
