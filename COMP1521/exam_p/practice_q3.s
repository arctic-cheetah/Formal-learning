# this code reads 1 integer and prints it
# add code so that prints 1 iff
# the least significant (bottom) byte of the number read
# is equal to the 2nd least significant byte
# and it prints 0 otherwise'

#t0 = least_byte
#t1 = value
#t2 = lower_byte
#t3 = high_byte
#t4 = temp

main:
    li $t0, 255             #least_byte = 255 = 0xff

    li   $v0, 5
    syscall
    move $t1, $v0           #value

    # PUT YOUR CODE HERE

    and $t2, $t1, $t0       #lower_byte = value & least_byte
    sll $t4, $t0, 8         #(least_byte << 8);
    and $t3, $t4, $t1       #high_byte = value & (least_byte << 8);
    srl $t3, $t3, 8         #high_byte = high_byte >> 8;

    bne $t3, $t2, else
    li $a0, 1
    j end
else:
    li $a0, 0
    
end:
    li   $v0, 1
    syscall

    li   $a0, 10
    li   $v0, 11
    syscall

    li   $v0, 0
    jr   $ra
