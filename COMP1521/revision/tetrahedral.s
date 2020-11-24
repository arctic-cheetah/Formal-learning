#t0 = i
#t1 = j
#t2 = n
#t3 = total
#t4 = how_many

main:

    li $v0, 4
    la $a0, prompt      #printf("Enter how many: ");
    syscall

    li $v0, 5           #scanf("%d", &how_many);
    syscall
    move $t4, $v0

    li $t2, 1           #n = 1

loop1:
    bgt $t2, $t4, end1   #if(n > how_many) goto end
    li $t3, 0           #total = 0
    li $t1, 1           #j = 1

loop2:
    bgt $t1, $t2, end2  #if (j > n) goto end2
    li $t0, 1           #i = 1
loop3:
    bgt $t0, $t1, end3  #if (i > j) goto end3
    add $t3, $t3, $t0   #total += i;
    addi $t0, $t0, 1    #i +=1
    j loop3
end3:
    addi $t1, $t1, 1    #j +=1
    j loop2
end2:

    li $v0, 1           #printf("%d\n", total);
    move $a0, $t3
    syscall

    li $a0, '\n'
    li $v0, 11
    syscall

    addi $t2, $t2, 1    #n +=1
    j loop1
end1:
    li $v0, 10
    syscall


    .data
prompt: .asciiz "Enter how many: "
