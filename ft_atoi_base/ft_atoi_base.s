.intel_syntax noprefix
.global ft_atoi_base
.extern ft_strlen

check_base:
    push rdi
    mov rdi, rsi
    call ft_strlen
    pop rdi
    cmp rax, 2
    jl error

    xor rcx, rcx
    loop1_i:
        cmp byte ptr [rsi + rcx], 0
        je loop2

        cmp byte ptr [rsi + rcx], '+'
        je error
        cmp byte ptr [rsi + rcx], '-'
        je error
        cmp byte ptr [rsi + rcx], ' '
        je error
    
        xor rdx, rdx
        loop1_j:
            cmp byte ptr [rsi + rdx], 0
            je end_loop1_j

            mov al, byte ptr [rsi + rcx]
            cmp al, byte ptr [rsi + rdx]
            jne return_loop1_j
            cmp rcx, rdx
            jne error

            inc rdx
            jmp loop1_j

    loop2:
        xor rcx, rcx
        loop2_i:
            cmp byte ptr [rdi + rcx], 0
            je global_error
            
            xor rdx, rdx
            xor r8, r8

            loop2_j:
                cmp byte ptr [rsi + rdx], 0
                je end_loop2_j
                call check_eq
                inc rdx
                jmp loop2_j

end_loop1_j:
    inc rcx
    jmp loop1_i

return_loop1_j:
    inc rdx
    jmp loop1_j

check_eq:
    mov al, byte ptr [rdi + rcx]
    cmp al, byte ptr [rsi + rdx]
    je update_eq
    ret

update_eq:
    mov r8, 1
    ret

end_loop2_j:
    cmp r8, 0
    je error
    inc rcx
    jmp loop2_i

get_pos:
    xor r8, r8
    loop_pos:
        cmp byte ptr [rsi + r8], 0
        je return_loop_pos1

        mov al, byte ptr [rsi + r8]
        cmp al, byte ptr [rdi + rcx]
        je return_loop_pos2
        inc r8
        jmp loop_pos


return_loop_pos1:
    mov rax, 0
    ret

return_loop_pos2:
    mov rax, r8
    ret

ft_atoi_base:
    call check_base
    cmp eax, 1
    je global_error

    push rdi
    mov rdi, rsi
    call ft_strlen
    pop rdi
    mov r10, rax 

    xor r9, r9
    xor rcx, rcx

    loop:
        cmp byte ptr [rdi + rcx], 0
        je return_number

        imul r9, r10
        call get_pos
        add r9, rax
        inc rcx
        jmp loop

error:
    mov rax, 1
    ret

global_error:
    mov rax, 0
    ret

return_number:
    mov rax, r9
    ret

.section .note.GNU-stack,"",@progbits
