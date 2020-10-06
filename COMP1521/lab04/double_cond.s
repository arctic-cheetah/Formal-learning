#int x = t0
# 100 = t1
# 1000 = t2


main:
    ori $t1, 100
    ori $t2, 1000

    li $v0, 4           #printf("Enter a number: ")
    la $a0, prompt
    syscall

    li $v0, 5
    syscall
    move $t0, $v0       #scanf("%d", &x)

    ble $t0, $t1, else  #if (x <= 100 && x >= 100)
    bge $t0, $t2, else

    la $a0, medium      #word = "medium"

    b exit

else:
    la $a0, bors        #word = "bors"
    b exit

exit:
    li $v0, 4
    syscall

    li $v0, 10
    syscall



.data
    prompt: .asciiz "Enter a number: "
    medium: .asciiz "medium\n"
    bors: .asciiz "small/big\n"
