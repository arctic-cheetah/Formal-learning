# Read a number n and print the first n tetrahedral numbers
# https://en.wikipedia.org/wiki/Tetrahedral_number

# i = t0
# j = t1
# n = t2
# total = t3
# how_many = t4
.text
main:                  # int main(void) {

    la $a0, prompt     # printf("Enter how many: ");
    li $v0, 4
    syscall

    li $v0, 5           # scanf("%d", how_many);
    syscall
    move $t4, $v0

    li $t2, 1           #n = 1

loop1:
    bgt $t2, $t4, end   #if (n > how_many) goto end

    li $t3, 0           #total = 0
    li $t1, 1           #j = 1

loop2:
    bgt $t1, $t2, continue1 #if (j > n) goto continue1
    li $t0, 1;          #i = 1

loop3:
    bgt $t0, $t1, continue2 #if (i > j) goto continue2
    add $t3, $t3, $t0       #total += i
    addi $t0, $t0, 1        # i+=1
    j loop3
continue2:
    addi $t1, $t1, 1    #j +=1
    j loop2
continue1:
    move $a0, $t3        #   printf("%d", total);
    li   $v0, 1
    syscall

    li   $a0, '\n'      # printf("%c", '\n');
    li   $v0, 11
    syscall

    addi $t2, $t2, 1    #n +=1;
    j loop1

end:

    jr   $ra           # return

    .data
prompt:
    .asciiz "Enter how many: "
