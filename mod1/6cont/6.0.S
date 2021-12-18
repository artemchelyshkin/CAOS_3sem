.intel_syntax noprefix
.globl very_important_function
.text


very_important_function:
    push     rbp
    mov      rbp,  rsp
    mov      r8,   0
    mov      r9,   0
    cvtsi2ss xmm3, r9
calc:
    cmp      r9,   rdi
    jz       end
    vmovaps  ymm1, YMMWORD PTR[rsi + r8]
    vaddps   ymm1, ymm1, YMMWORD PTR[rdx + r8]
    vmovaps  YMMWORD PTR[rcx + r8], ymm1
    mov      r10, r8
    add      r8, 32

loop:
    cmp      r10, r8
    jz       endloop
    movss    xmm2, [rcx + r10]
    addss    xmm3, xmm2
    add      r10,  4
    jmp      loop

endloop:
    add      r9, 8
    jmp      calc

end:
    cvtsi2sd xmm2, rdi
    cvtss2sd xmm0, xmm3
    divsd    xmm0, xmm2
    pop      rbp
    ret
