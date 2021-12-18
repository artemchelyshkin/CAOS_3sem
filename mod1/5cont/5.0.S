	    .intel_syntax noprefix
    .text
    .globl very_important_function

very_important_function:
    push rbp
    mov  rbp, rsp
    push r15
    push r14
    sub  rsp, 16
    mov  r14, rdi
    lea  rsi, A[rip]
    mov  r15, QWORD PTR[rsi]

.start_loop:
    cmp  r14, 0
    jle  .return
    mov  rsi, rsp
    add  rsi, 12
    lea  rdi, .format_scanf[rip]
    call scanf
    movslq  rax, DWORD PTR[r15]
    movslq  rcx, DWORD PTR[rsp + 12]
    imul  rcx
    mov  rsi, rax
    lea  rdi, .format_printf[rip]
    call printf
    add  r15, 4
    dec  r14
    jmp  .start_loop

.return:
    add  rsp, 16
    pop  r14
    pop  r15
    pop  rbp
    ret

.section   .rodata
.format_scanf:
   .string "%d"
.format_printf:
   .string "%ld\n"

