#include <sys/syscall.h>

.intel_syntax noprefix
.text


//r13 - buf
//r14 - flag

while1:
    cmp r14, 0
    jle end_while1
    mov rax, SYS_write
    mov rdi, 1
    mov rsi, r13
    mov rdx, r14
    syscall

    mov rax, SYS_read
    mov rdi, 0
    mov rsi, r13
    mov rdx, 4000
    syscall
    mov r14, rax
    jmp while1

my_exit:
    mov rax, SYS_exit_group
    syscall

.globl _start
_start:
    push rbp
    mov  rbp, rsp
    push r13
    push r14
    mov rax, SYS_brk
    mov rdi, 0
    syscall
    mov r13, rax
    mov rax, SYS_brk
    mov rdi, r13
    add rdi, 4000
    syscall

    mov rax, SYS_read
    mov rdi, 0
    mov rsi, r13
    mov rdx, 4000
    syscall
    mov r14, rax
    
    jmp while1
end_while1:
    

    mov  rax, SYS_brk
    mov  rdi, r13
    syscall
    pop r14
    pop r13
    pop rbp
    mov  rdi, 0
    call my_exit
