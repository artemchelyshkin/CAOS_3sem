.text
.global main

main:
    sub sp, sp, #16
    str x30, [sp, #8]

loop:
    //while (x0 >= 0)
    bl getchar_unlocked
    cmp x0, 0
    blt end
    cmp x0, 48
    bge digit
    b loop
    
digit:
    cmp x0, 57
    bgt loop
    bl putchar_unlocked
    b loop

end:
    ldr x30, [sp, #8]
    add sp, sp, #16
    mov x0, 0
    ret
