# read a mark and print the corresponding UNSW grade

main:
    la $a0, prompt      # printf("Enter a mark: ");
    li $v0, 4
    syscall

    li $v0, 5           # scanf("%d", mark);
    syscall
    move $t0, $v0       # store in mark == t0

    blt $t0, 50, fail       # if (mark < 50)
    blt $t0, 65, pass
    blt $t0, 75, credit
    blt $t0, 85, distinct
    b hdistinct


########################load address to print
fail:
    la $a0, fl
    b end

pass:
    la $a0, ps
    b end

credit:
    la $a0, cr
    b end

distinct:
    la $a0, dn
    b end

hdistinct:
    la $a0, hd
    b end

#end program
end:
    li $v0, 4
    syscall

    li $v0, 10
    syscall


    .data
prompt:
    .asciiz "Enter a mark: "
fl:
    .asciiz "FL\n"
ps:
    .asciiz "PS\n"
cr:
    .asciiz "CR\n"
dn:
    .asciiz "DN\n"
hd:
    .asciiz "HD\n"
