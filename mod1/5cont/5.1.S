.intel_syntax noprefix
.text
.globl sum

sum:
    push rbp
    mov  rbp, rsp

.loop:
    cmp    rdi, 0
    jle    .ret
    dec    rdi
    mov    eax, DWORD PTR[rsi]
    add    eax, DWORD PTR[rdx]
    mov    DWORD PTR[rcx], eax
    add    rcx, 4
    add    rsi, 4
    add    rdx, 4
    jmp    .loop

.ret:    
    pop  rbp
    ret
    
