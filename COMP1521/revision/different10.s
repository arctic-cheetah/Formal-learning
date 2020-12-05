# x in register $t0
# i in register $t1
# n_seen in register $t2
# registers $t3 and $t4 used to hold temporary results
main:

    li   $t2, 0          # n_seen = 0;
start:
    bge  $t2, 10, end    # while (n_seen < 10) {
    la   $a0, string0    # printf("Enter a number: ");
    li   $v0, 4
    syscall
    li   $v0, 5          # scanf("%d", &x);
    syscall

    move $t0, $v0

    li $t1, 0
loop0:
    bge $t1, $t2, end0

    mul $t3, $t1, 4      # calculate &numbers[n_seen]
    la  $t4, numbers
    add $t4, $t4, $t3
    lw $t4, 0($t4)

    beq $t0, $t4, end0   #if (x == numbers[i]) goto end0

    addi $t1, $t1, 1
    j loop0
end0:


    bne $t1, $t2, start # if (i != n_seen) goto start
    mul  $t3, $t2, 4    # calculate &numbers[n_seen]
    la   $t4, numbers   #
    add  $t4, $t3, $t4  #
    sw   $t0, ($t4)     # numbers[n_seen] = x

    addi $t2, $t2, 1    # n_seen++;
    j    start



end:
    la   $a0, string1   # printf("10th different number was: ");
    li   $v0, 4
    syscall

    move $a0, $t0       # printf("%d", x)
    li   $v0, 1
    syscall

    li   $a0, 10      # printf("%c", '\n');
    li   $v0, 11
    syscall

    li   $v0, 0         # return 0
    jr   $ra

    .data

numbers:
    .space 40           # int numbers[10];

string0:
    .asciiz "Enter a number: "
string1:
    .asciiz "10th different number was: "
