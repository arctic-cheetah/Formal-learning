#
#int x = t0
#int y = t1
#int max = t2 46340

main:

    ori $t2, 46340

    li $v0, 4
    la $a0, prompt
    syscall

    li $v0, 5           #scan in a number
    syscall
    move $t0, $v0

    bgt $t0, $t2, else #if (x > 46340)

    mul $t1, $t0, $t0 #y = x * x

    li $v0, 1           #print ("%d", y)
    move $a0, $t1
    syscall

    li $v0, 11          #print ("\n")
    li $a0, '\n'
    syscall

    b exit


else:
    li $v0, 4       # print ("square too big")
    la $a0, tooBig
    syscall

exit:
    li $v0, 10
    syscall


.data
    prompt: .asciiz "Enter a number: "
    tooBig: .asciiz "square too big for 32 bits\n"
