.intel_syntax noprefix
.global ft_list_sort

ft_list_sort:
    # Guardamos los registros "callee-saved" que vamos a usar
    # Al hacer 3 pushes, la pila queda alineada a 16 bytes (obligatorio antes de hacer call)
    push rbx
    push r12
    push r13

    # Comprobaciones iniciales (!begin_list || !*begin_list || !cmp)
    cmp rdi, 0
    je end
    cmp qword ptr [rdi], 0
    je end
    cmp rsi, 0
    je end

    mov r13, rsi              # r13 = puntero a la funcion de comparacion (cmp)
    mov rbx, qword ptr [rdi]  # rbx = node (*begin_list)

loop_node:
    cmp rbx, 0                # while (node != NULL)
    je end

    mov r12, qword ptr [rbx + 8]  # r12 = next_node (node->next)

loop_next_node:
    cmp r12, 0                # while (next_node != NULL)
    je exit_loop_next_node

    # Preparamos los argumentos para cmp(node->data, next_node->data)
    mov rdi, qword ptr [rbx]  # primer argumento = node->data
    mov rsi, qword ptr [r12]  # segundo argumento = next_node->data
    
    call r13                  # llamamos a cmp

    cmp eax, 0
    jg swap_datas             # si cmp > 0, hacemos swap

advance_next_node:
    mov r12, qword ptr [r12 + 8]  # next_node = next_node->next
    jmp loop_next_node

swap_datas:
    # Hacemos el intercambio de los punteros 'data' (offset 0)
    mov r10, qword ptr [rbx]      # r10 = node->data
    mov r11, qword ptr [r12]      # r11 = next_node->data
    
    mov qword ptr [rbx], r11      # node->data = r11
    mov qword ptr [r12], r10      # next_node->data = r10

    # Tras hacer el swap, continuamos avanzando en el bucle interior
    jmp advance_next_node

exit_loop_next_node:
    mov rbx, qword ptr [rbx + 8]  # node = node->next
    jmp loop_node

end:
    # Restauramos los registros en orden inverso
    pop r13
    pop r12
    pop rbx
    ret

.section .note.GNU-stack,"",@progbits