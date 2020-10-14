# Read 10 numbers into an array
# then print the numbers which are
# larger than the last number read.

# i in register $t0
# registers $t1, $t2 used to hold temporary results
# last_number = t4
.data

numbers:
    .word 0:10  # int numbers[10] = {0};

.text
main:

    li $t0, 0           # i = 0
loop0:
    bge $t0, 10, end0   # while (i < 10) {

    li $v0, 5           #   scanf("%d", &numbers[i]);
    syscall             #

    mul $t1, $t0, 4     #   calculate &numbers[i]
    la $t2, numbers     #
    add $t2, $t1, $t2   #
    sw $v0, ($t2)       #   store entered number in array


    add $t0, $t0, 1     #   i++;
    b loop0             # }
end0:
    lw $t4, ($t2)       # last_numer = numbers[i]
    li $t0, 0           # i = 0
loop1:
    bge $t0, 10, end1   # while (i < 10) {

    mul $t1, $t0, 4     #   calculate &numbers[i]
    la $t2, numbers     #
    add $t3, $t1, $t2   #
    lw $a0, ($t3)       #   load numbers[i] into $a0

    blt $a0, $t4 skip #  if (numbers[i] < last_number) goto skip
    li $v0, 1           #   printf("%d", numbers[i])
    syscall

    li   $a0, '\n'      #   printf("%c", '\n');
    li   $v0, 11
    syscall
skip:

    add $t0, $t0, 1     #   i++
    b loop1             # }
end1:

    li $v0, 10
    syscall # return
