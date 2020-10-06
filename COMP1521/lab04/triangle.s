#print a triangle
#int i = t0
#int j = t1
# 10 = t2

main:
    li $t0, 1

loop1:
    bgt $t0, 10, end1  # if (i > 10) goto end1

    li $t1, 0          #j = 0;

loop2:
    bge $t1, $t0, addtoI # if (j >= i) goto addtoI

    li $v0, 11          #printf("*")
    li $a0, '*'
    syscall

    addi $t1, $t1, 1    #j +=1
    b loop2

addtoI:

    li $v0, 11          #printf("\n")
    li $a0, '\n'
    syscall

    addi $t0, $t0, 1    # i +=1
    b loop1

end1:
    li $v0, 10
    syscall
