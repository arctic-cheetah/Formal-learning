# $t0 = mark

main:

    la $a0, prompt  #printf("Enter a mark: ");
    li $v0, 4
    syscall

    li $v0, 5       #scanf("%d", &mark);
    syscall
    move $t0, $v0

    blt $t0, 50, FAIL
    blt $t0, 65, PASS
    blt $t0, 75, CRED
    blt $t0, 85, DIST
    j HDIST


FAIL:
    la $a0, FL
    j end
PASS:
    la $a0, PS
    j end
CRED:
    la $a0, CR
    j end
DIST:
    la $a0, DN
    j end
HDIST:
    la $a0, HD
    j end


end:
    li $v0, 4
    syscall

    li $v0, 10
    syscall

.data
    prompt: .asciiz "Enter a mark: "
    FL: .asciiz "FL\n"
    PS: .asciiz "PS\n"
    CR: .asciiz "CR\n"
    DN: .asciiz "DN\n"
    HD: .asciiz "HD\n"
