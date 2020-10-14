#A program which prints out a 2d array
#i = t0
#j = t1
#numbers = t2

.text
main:

loop1:
    bge $t0, 3, end1    # if (i >= 3) goto end1
    li $t1, 0           # j = 0

    la $t2, numbers     #set the next row, ie: *number[i]
    mul $t3, $t0, 20
    add $t2, $t2, $t3

loop2:
    bge $t1, 5, end2    # if (j >= 5) goto end2;

    lw $a0, ($t2)       #printf("%d", numbers[i][j]);
    li $v0, 1
    syscall

    li $a0, ' '         #print(" ");
    li $v0, 11
    syscall

    addi $t2, $t2, 4    #increment to the next index

    addi $t1, $t1, 1    # j+=1;
    j loop2
end2:

    li $a0, '\n'         #print("\n");
    li $v0, 11
    syscall

    addi $t0, $t0, 1    # i +=1
    j loop1
end1:

    li $v0, 10
    syscall


.data
# int numbers[3][5] = {{3,9,27,81,243},{4,16,64,256,1024},{5,25,125,625,3125}};
numbers:
     .word  3, 9, 27, 81, 243, 4, 16, 64, 256, 1024, 5, 25, 125, 625, 3125
