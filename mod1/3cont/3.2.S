.text
.global solve

solve:
    mov x4, 0

LoopBegin: 
    mov    w5, w0
    mul    w5, w5, w4
    add    w5, w5, w1
    mul    w5, w5, w4
    add    w5, w5, w2
    mul    w5, w5, w4
    add    w5, w5, w3
    cmp    w5, 0
    beq    EndLoop
    mov    w5, 0
    add    w4, w4, 1
    b      LoopBegin

EndLoop:
    mov    w0, w4
    ret

    
