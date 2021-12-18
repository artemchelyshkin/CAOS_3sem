.text
.global main

// while (elem != EOF){
//  if (size == capacity) {
//   realloc
//  }
//  add_letter
// }
// for (int i = size; i >= 0; i--) {
//  putchar(str[i])
// }
// free
//
// ---------------------------------------
//
// x19 ---> pointer dynamic array
// x20 ---> size
// x21 ---> capacity
// 

main:
    sub    sp, sp, #48
    str    x30, [sp, #8]
    str    x19, [sp, #40]
    str    x20, [sp, #32]
    str    x21, [sp, #24]
    str    x22, [sp, #16]
    mov    x19, #0
    mov    x20, #0
    mov    x21, #4
    mov    x0, #0
    mov    x1, #4
    mov    x22, #2
    bl     realloc
    mov    x19, x0
    b      read_string 

end:
    mov    x0, x19
    bl     free   
    ldr    x22, [sp, #16]
    ldr    x21, [sp, #24]
    ldr    x20, [sp, #32]
    ldr    x19, [sp, #40] 
    ldr    x30, [sp, #8]
    add    sp, sp, #48
    mov    x0, #0
    ret


read_string:
    mov    x0, #0
    bl     getchar_unlocked
    cmp    x0, #0
    blt    reverse_print
    mov    x23, x0
    cmp    x20, x21
    beq    increase_capacity
push_back:
    str    x23, [x19, x20]
    add    x20, x20, #1
    b read_string


increase_capacity:
    mov    x0, x19
    mul    x21, x21, x22
    mov    x1, x21
    bl     realloc
    mov    x19, x0
    b      push_back

reverse_print:
    sub    x20, x20, #1
    cmp    x20, #0
    blt    end
    ldr    x0, [x19, x20]
    bl     putchar_unlocked
    b      reverse_print
