# Read a number and print positive multiples of 7 or 11 < n
#$t0 = number
#$t1 = i
#$t2 = remainder
#$t3 = 7
#$t4 = 11

main:                  # int main(void) {

    la $a0, prompt     # printf("Enter a number: ");
    li $v0, 4
    syscall

    li $v0, 5           # scanf("%d", number);
    syscall
    move $t0, $v0

    or $t1, 1           # i = 1;
    or $t3, 7           # declare 7
    or $t4, 11          # declare 11

loop:
    beq $t0, $t1, end
    div $t1, $t3
    mfhi $t2
    beq $t2, 0, print   # i % 7 == 0

    div $t1, $t4
    mfhi $t2
    beq $t2, 0, print   # i % 11 == 0

    goto:
    addi $t1, $t1, 1
    b loop

end:
    jr   $ra           # return

print:
    li $v0, 1;
    move $a0, $t1       # printf(i);
    syscall

    li   $a0, '\n'      # printf("%c", '\n');
    li   $v0, 11
    syscall

    b goto


    .data
prompt:
    .asciiz "Enter a number: "
