.intel_syntax noprefix
.global ft_atoi_base
.extern ft_strlen

check_base:
    push rdi
    mov rdi, rsi
    call ft_strlen
    pop rdi
    cmp rax, 2
    jl global_error

    xor rcx, rcx
    loop1_i:
        cmp byte ptr [rdi + rcx], 0
        je loop2_i

        cmp byte ptr [rdi + rcx], '+'
        je global_error
        cmp byte ptr [rdi + rcx], '-'
        je global_error
        cmp byte ptr [rdi + rcx], ' '
        je global_error
    
        xor rdx, rdx
        loop1_j:
            cmp byte ptr [rdi + rdx], 0
            je end_loop1_j

            cmp byte ptr [rdi + rcx], byte ptr [rdi + rdx]
            jne return_loop1_j
            cmp rcx, rdx
            jne global_error

            inc rdx
            jmp loop1_j

        inc rcx
        jmp loop1_i

    loop2:
        xor rcx, rcx
        loop2_i:
            cmp byte ptr [rdi + rcx], 0
            je ret
            
            xor rdx, rdx
            xor r8d, r8d

            loop2_j:
                cmp byte ptr [rsi + rdx], 0
                jmp end_loop2_j

                cmp byte ptr [rdi + rcx], byte ptr [rsi + rdx]
                je update_eq
                inc rdx
                jmp loop2_j
            
            cmp eq, 0
            je global_error

            inc rcx
            jmp loop2_i

jmp end_loop1_j:
    inc rcx
    jmp loop1_i

jmp return_loop1_j:
    inc rdx
    jmp loop1_j

update_eq:
    mov r8d, 1

jmp end_loop2_j:
    inc rcx
    jmp loop2_i

get_pos:
    xor r8d, r8d
    loop:
        cmp byte ptr [rsi + r8d], 0
        je return_loop_pos1

        cmp byte ptr [rsi + r8d], [rdi + rcx]
        je return_loop_pos2
        inc r8d
        jmp loop


return_loop_pos1:
    mov eax, 0
    ret

return_loop_pos2:
    mov eax, r8d
    ret

ft_atoi_base:
    jmp check_base

    xor r9d, r9d
    xor rcx, rcx

    push rdi
    mov rdi, rsi
    call ft_strlen
    pop rdi
    mov r10d, rax 

    loop:
        cmp byte ptr [rdi + rcx], 0
        je return_number

        imul r9d , r10d
        jmp get_pos
        add r9d, eax
        inc rcx
    ret

global_error:
    mov rax, 0
    ret

return_number:
    mov rax, r9d
    ret