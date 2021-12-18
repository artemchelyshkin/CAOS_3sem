.intel_syntax noprefix
.global avx_sin

//  xmm0 -> res
//  xmm1 -> x
//  xmm2 -> prev precision
//  xmm3 -> last_member

avx_sin:
    push      rbp
    mov       rbp,  rsp
    vmovsd    xmm2, xmm0, xmm0
    vmovsd    xmm1, xmm0, xmm0
    vmovsd    xmm3, xmm0, xmm0
    vmulsd    xmm3, xmm3, xmm0
    vmulsd    xmm3, xmm3, xmm0
    mov       rax,   -1
    vcvtsi2sd xmm4, xmm4, rax
    vmulsd    xmm3, xmm3, xmm4
    mov       rax,  6
    mov       r8,   6
    mov       r9,   3
    vcvtsi2sd xmm4, xmm4, rax
    vdivsd    xmm3, xmm3, xmm4
    vaddsd    xmm0, xmm0, xmm3
    jmp    loop

loop:
    vcomisd   xmm2, xmm0
    jz        end
    vmovsd    xmm2, xmm0, xmm0
    vmulsd    xmm3, xmm3, xmm1
    vmulsd    xmm3, xmm3, xmm1
    add       r9,   1
    vcvtsi2sd xmm4, xmm4, r9
    vdivsd    xmm3, xmm3, xmm4
    add       r9,   1
    vcvtsi2sd xmm4, xmm4, r9
    vdivsd    xmm3, xmm3, xmm4
    mov       rax, -1
    vcvtsi2sd xmm4, xmm4, rax
    vmulsd    xmm3, xmm3, xmm4
    vaddsd    xmm0, xmm0, xmm3
    jmp       loop
    

end:
    pop   rbp
    ret
