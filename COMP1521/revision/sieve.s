# Sieve of Eratosthenes
# https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes
# t0 = i
# t1 = j
# t2 = temp
# t3 = prime[]

main:

    li $t1, 1

loop0:
    bge $t0, 1000, end0         #if (i >= 1000) goto end0

    la $t2, prime               #prime[i] = 1;
    add $t2, $t2, $t0
    sb $t1, 0($t2)

    addi $t0, $t0, 1
    j loop0
end0:

    li $t1, 0
    li $t0, 2                   #i = 2

loop1:
    bge $t0, 1000, end1         #if (i >= 1000) goto end1

    la $t2, prime
    add $t2, $t2, $t0
    lb $a0, 0($t2)
    beq $a0, 0, skip            #if (!prime[i]) goto skip

    move $a0, $t0
    li $v0, 1
    syscall

    li $a0, 10                  #printf("%d\n", i);
    li $v0, 11
    syscall

    mul $t1, $t0, 2
loop2:
    bge $t1, 1000, end2         #if (i >= 1000) goto end1

    la $t2, prime               #prime[j] = 0;
    add $t2, $t2, $t1
    li $t3, 0
    sb $t3, 0($t2)

    add $t1, $t1, $t0          #j = j + i
    j loop2
end2:
skip:

    addi $t0, $t0, 1
    j loop1
end1:



    li $v0, 10           # return 0
    syscall

.data
prime:
    .space 1000
