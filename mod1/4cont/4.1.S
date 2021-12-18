    .text
    .global    main

main:
    
    
    sub    sp, sp, #32
    str    x19, [sp, #16]
    str    x20, [sp, #24]
    str    x30, [sp]
    ldr    x0, =scanf_string
    add    x1, sp, #8
    add    x2, sp, #12
    bl     scanf
    ldr    x19, [sp, #8]
    ldr    x20, [sp, #12]
    add    x1, x19, x20
    ldr    x0, =printf_string
    bl     printf
    ldr    x30, [sp]
    ldr    x20, [sp, #24]
    ldr    x19, [sp, #16]
    add    sp, sp, #48
    mov x0, 0
    ret
    
    




    .section    .rodata 
scanf_string:
    .string "%d %d"
printf_string:
    .string "%d\n"
