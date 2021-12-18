    .text
    .global sum
sum:
    mov    x4, 0
LoopBegin:
    cmp    x4, x1
    beq    LoopEnd
    ldr    w5, [x2]
    add    x2, x2, #4
    add    x4, x4, 1
    add    w0, w0, w5
    b      LoopBegin
LoopEnd:
    ret
