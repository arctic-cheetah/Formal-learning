# Sieve of Eratosthenes
# https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes
# $t0 = i
# $t1 = j
# $t2 = prime[]


main:

    la $t2, prime
    li $t3, 1               # i = 0

loop1:
    bge $t0, 1000, end1     # if (i >= 1000) goto end1
    sw $t3, ($t2)           # prime[i] = 1
    addi $t2, $t2, 4
    addi $t0, $t0, 1        # i+=1
    j loop1
end1:

    li $t0, 2               # i = 2
loop2:
    bge $t0, 1000, end2     # if (i > = 1000) goto end2

    la $t2, prime
    mul $t3, $t0, 4
    add $t2, $t2, $t3
    lw $t3, ($t2)           # Get the array index prime[i]

    beq $t3, 0, skipNum     # if (!prime[i]) goto skipNum

    move $a0, $t0           # printf("%d", i);
    li $v0, 1
    syscall

    li $a0, '\n'            # printf("\n");
    li $v0, 11
    syscall

    mul $t1, $t0, 2        # j = 2 * i
    li $t4, 0
loop3:
    bge $t1, 1000, end3     # if (j >= 1000) goto end3

    la $t2, prime
    mul $t3, $t1, 4
    add $t2, $t2, $t3
    sw $t4, ($t2)           # prime[j] = 0

    add $t1, $t1, $t0       # j += i
    j loop3
end3:

skipNum:

    addi $t0, $t0, 1        # i +=1
    j loop2
end2:


    li $v0, 0           # return 0
    jr $31

.data
prime:
    .word 0:1000       # initialise an array of 1000 elements to zero
