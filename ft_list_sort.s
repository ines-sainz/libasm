.intel_syntax noprefix
.global ft_list_sort

ft_list_sort:
    cmp rdi, 0
    je return
    
    cmp qword ptr [rdi], 0
    je return

    cmp rsi, 0
    je return

    mov r8, qword ptr [rdi]
    loop_node:
        cmp r8, 0
        je return

        mov r9, qword ptr [r8 + 8]
        jmp loop_next_node

    loop_next_node:
        cmp r9, 0
        je exit_loop_next_node

        push rsi
        mov rdi, qword ptr [r8]
        mov rsi, qword ptr [r9]
        call [rsp]
        pop rsi
        
        cmp eax, 0
        jg swap_datas 

        mov r11, qword ptr [r9 + r8]
        mov [r9], r11
        jmp loop_next_node

swap_datas:
    mov r11, qword ptr [r8]
    mov r10, r11

    mov r11, qword ptr [r9]
    mov [r8], r11

    mov r11, qword ptr [r10]
    mov [r9 + 8], r11

return:
    ret

exit_loop_next_node:
    mov r11, qword ptr [r8 + 8]
    mov [r8], r11
    jmp loop_node

.section .note.GNU-stack,"",@progbits
