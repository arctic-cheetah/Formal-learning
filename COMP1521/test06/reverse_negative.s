# Read numbers into an array until a negative number is entered
# then print the numbers in reverse order

# i in register $t0
# registers $t1, $t2 & $t3 used to hold temporary results

main:
    li   $t0, 0          # i = 0
loop0:
    bge  $t0, 1000, end0 # while (i < 1000) {

    li   $v0, 5          #   scanf("%d", &numbers[i]);
    syscall              #

    bge $v0, 0, skipCheck# if (x >= 0) skipCheck
    j end0
skipCheck:
    mul  $t1, $t0, 4     #   calculate &numbers[i]
    la   $t2, numbers    #
    add  $t3, $t1, $t2   #
    sw   $v0, ($t3)      #   store entered number in array

    addi $t0, $t0, 1     #   i++;
    j    loop0           # }
end0:

loop1:
    ble $t0, 0, end1     # if ($t0 <= 0) goto end1
    addi $t0, $t0, -1    # i -=1

    la $t2, numbers
    mul $t3, $t0, 4      # calculate &numbers[i]
    add $t2, $t2, $t3
    lw $a0, ($t2)

    li $v0, 1            # printf("%d", numbers[i])
    syscall

    li $a0, '\n'         # printf("\n")
    li $v0, 11
    syscall

    j loop1
end1:

    li   $v0, 0          # return 0
    jr   $ra              #

.data
numbers:
    .space 4000
