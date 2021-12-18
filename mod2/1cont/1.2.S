#include <sys/syscall.h>

.intel_syntax noprefix
.text

my_exit:
   mov rax, SYS_exit_group
   syscall


while3:
   cmp r15, 0
   jle end_while3
   mov r8, r13
   add r8, r15
   mov al, BYTE PTR[r8]
   cmp al, 10
   jz end_while3
   add r14, 1
   sub r15, 1
   jmp while3

if2:
   //syscall(SYS_write, 1, p, lenght + 1);
   mov rax, SYS_write
   mov rdi, 1
   mov rsi, r13
   mov rdx, r14
   add rdx, 1
   syscall

   //syscall(SYS_write, 1, eol, 1);
   mov rax, SYS_write
   mov rdi, 1
   mov rsi, rbx
   mov rdx, 1
   syscall

   jmp end_while2


while2:
   cmp r15, 0
   jle end_while2
   mov r14, 0
   jmp while3
end_while3:
   cmp r15, 0
   jz if2

   //syscall(SYS_write, 1, p + new_adr + 1, lenght);
   mov rax, SYS_write
   mov rdi, 1
   mov rsi, r13
   add rsi, r15
   add rsi, 1
   mov rdx, r14
   syscall

   //syscall(SYS_write, 1, eol, 1);
   mov rax, SYS_write
   mov rdi, 1
   mov rsi, rbx
   mov rdx, 1
   syscall

   sub r15, 1
   jmp while2


end2:
   //syscall(SYS_write, 1, eol, 1);
   mov rax, SYS_write
   mov rdi, 1
   mov rsi, rbx
   mov rdx, 1
   syscall
   jmp end


if0:
   add rbx, 1024
   mov rax, SYS_brk
   mov rdi, r12
   add rdi, r13
   add rdi, rbx
   syscall
   jmp end_if0

while_1:
   cmp r14, 0
   jle end_while1

   mov rax, r12
   add rax, rbx
   sub rax, r15
   cmp rax, 0
   jz  if0
end_if0:

   //lenght = syscall(SYS_read, 0, p + new_adr, buf - new_adr);
   mov rax, SYS_read
   mov rdi, 0
   mov rsi, r13
   add rsi, r15
   mov rdx, r12
   add rdx, rbx
   sub rdx, r15
   syscall
   mov r14, rax
 
   //if (lenght < 0) break;
   cmp r14, 0
   jl end_while1
   
   //new_adr += lenght;
   add r15, r14
   
   jmp while_1




if1:
    add r15, 1
    jmp end_if1



prog:
   mov r12, 1024
   mov rbx, 0
   //char* p = (char*)syscall(SYS_brk, 0);
   mov rax, SYS_brk
   mov rdi, 0
   syscall
   mov r13, rax
   //syscall(SYS_brk, p + buf);
   mov rax, SYS_brk
   mov rdi, r13 
   add rdi, r12
   syscall
   //long lenght = syscall(SYS_read, 0, p, buf);
   mov rax, SYS_read
   mov rdi, 0
   mov rsi, r13
   mov rdx, r12
   syscall
   mov r14, rax
   //long new_adr = lenght;
   mov r15, r14
   jmp while_1
end_while1:
   //char eol[1] = { '\n' };
   mov al, 10
   mov BYTE PTR[rsp], al
   //mov rbx, .eol[rip]
   //mov BYTE[rsp], rbx
   mov rbx, rsp
   //jmp end
   cmp r15, 0
   jl  end
   cmp r15, 0
   jz  end2
   //if (p[new_adr - 1] != '\n')   
   mov rax, r13
   add rax, r15
   sub rax, 1
   mov al, BYTE PTR[rax]
   cmp al, 10
   jnz if1  
end_if1:
   //new_adr -= 2;
   sub r15, 2
   //jmp end

   jmp while2
end_while2:
   jmp end

.globl _start
_start:
   push rbp
   mov  rbp, rsp
   push r12 // 32mb
   push r13 // p
   push r14 // lenght
   push r15 // new_adr
   push rbx // eol
   sub  rsp, 8
   jmp  prog

end:
   mov  rax, SYS_brk
   mov  rdi, r13
   syscall
   add  rsp, 8
   pop  rbx
   pop  r15
   pop  r14
   pop  r13
   pop  r12
   pop  rbp
   mov  rdi, 0
   call my_exit


