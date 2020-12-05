# this code reads a line of input and prints 42
# change it to evaluate the arithmetic expression
# *s = t0
# left = s0,
# right = s1,
# n = s2
# temp = t2

main:
    addi $sp, $sp, -4
    sw $ra, 0($sp)       # store the return address

    la   $a0, line
    li   $a1, 10000
    li   $v0, 8          # fgets(buffer, 256, stdin)
    syscall              #

    la $t0, line

    jal expression

    lw   $ra, 0($sp)
    addi $sp, $sp, 4     # fetch the return address

    move $a0, $v0         # printf("%d", 42);
    li   $v0, 1
    syscall

    li   $a0, '\n'       # printf("%c", '\n');
    li   $v0, 11
    syscall

    li   $v0, 0          # return 0
    jr   $31

#------------------------------------------------------
expression:
    #prologue
    addi $sp, $sp, -12
    sw $s1, 8($sp)
    sw $s0, 4($sp)
    sw $ra, 0($sp)

    jal term
    move $s0, $v0           #left = term()

    lb $t1, 0($t0)
    beq $t1, '+', else      #if (*s == '*') goto else
    move $v0, $s0

    lw $s1, 8($sp)
    lw $s0, 4($sp)
    lw $ra, 0($sp)
    addi $sp, $sp, 12     # fetch the return address
    jr $ra
else:

    addi $t0, $t0, 1      #s +=1

    jal expression
    move $s1, $v0       #right = expression()

    add $v0, $s0, $s1   # return left + right

    li $s0, 0
    li $s1, 0           # preserve the originality of the function reg

    # preserve the originality of the function reg
    lw $s1, 8($sp)
    lw $s0, 4($sp)
    lw $ra, 0($sp)
    addi $sp, $sp, 12     # fetch the return address

    jr $ra
#------------------------------------------------------

term:
    #prologue
    addi $sp, $sp, -12
    sw $s1, 8($sp)
    sw $s0, 4($sp)
    sw $ra, 0($sp)

    jal number
    move $s0, $v0           #left = term()

    lb $t1, 0($t0)
    beq $t1, '*', else2      #if (*s == '*') goto else
    move $v0, $s0

    lw $s1, 8($sp)
    lw $s0, 4($sp)
    lw $ra, 0($sp)
    addi $sp, $sp, 12     # fetch the return address
    jr $ra
else2:

    addi $t0, $t0, 1      #s +=1

    jal term
    move $s1, $v0       #right = expression()

    mul $v0, $s0, $s1   # return left * right

    # preserve the originality of the function reg
    lw $s1, 8($sp)
    lw $s0, 4($sp)
    lw $ra, 0($sp)
    addi $sp, $sp, 12     # fetch the return address
    jr $ra

#------------------------------------------------------
number:
    addi $sp, $sp, -4
    sw $ra, 0($sp)

    li $s2, 0           #n = 0
loop1:
    lb $t1, 0($t0)
    blt $t1, '0', end1 #if (*s < '0') goto else2
    bgt $t1, '9', end1 #if (*s > '9') goto else2

    addi $t2, $t1, -48  #*s - '0';
    mul $s2, $s2, 10    #10 * n
    add $s2, $s2, $t2   #n = 10 * n + *s - '0';

    addi $t0, $t0, 1    #s++;
    j loop1
end1:
    move $v0, $s2
    li $s2, 0

    lw $ra, 0($sp)
    addi $sp, $sp, 4     # fetch the return address
    jr $ra

.data
line:
    .space 10000            # char line[10000];
