.intel_syntax noprefix
.global ft_list_sort

ft_list_sort:
    push rbx
    push r12
    push r13

    cmp rdi, 0
    je return
    
    cmp qword ptr [rdi], 0
    je return

    cmp rsi, 0
    je return

    mov r13, rsi
    mov rbx, qword ptr [rdi]
    loop_node:
        cmp rbx, 0
        je return

        mov r12, qword ptr [rbx + 8]

    loop_next_node:
        cmp r12, 0
        je exit_loop_next_node

        mov rdi, qword ptr [rbx]
        mov rsi, qword ptr [r12]
        call r13
        
        cmp eax, 0
        jg swap_datas 

        mov r12, qword ptr [r12 + 8]
        jmp loop_next_node

swap_datas:
    mov r10, qword ptr [rbx]

    mov r11, qword ptr [r12]
    mov qword ptr [rbx], r11

    mov qword ptr [r12], r10
    
    mov r12, qword ptr [r12 + 8]
    jmp loop_next_node


exit_loop_next_node:
    mov rbx, qword ptr [rbx + 8]
    jmp loop_node

return:
    pop r13
    pop r12
    pop rbx
    ret

.section .note.GNU-stack,"",@progbits
