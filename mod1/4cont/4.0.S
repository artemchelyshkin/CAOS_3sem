    .data
    .global R
R:  .space 8

    .text
    .global    calculate
    
calculate:
    adr x0, .Lexterns
    ldr x1, [x0]
    ldr x2, [x0, 8]
    ldr x3, [x0, 16]
    ldr x4, [x0, 24]
    ldr x5, [x0, 32]
    ldr x1, [x1]
    ldr x2, [x2]
    ldr x3, [x3]
    ldr x4, [x4]
    mul x1, x1, x2
    mul x3, x3, x4
    add x6, x1, x3
    str x6, [x5]
    ret

.Lexterns:
    .quad A
    .quad B
    .quad C
    .quad D
    .quad R
