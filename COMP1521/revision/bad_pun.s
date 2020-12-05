
    main:
    la $a0, intro
    li $v0, 4;
    syscall

    li $v0, 10
    syscall



    .data
intro:
    .asciiz "I MIPS you!"
