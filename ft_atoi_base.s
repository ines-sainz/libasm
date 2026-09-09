.intel_syntax noprefix
.global ft_atoi_base
.extern ft_strlen

check_base:
    push rdi
    mov rsi, rdi
    call ft_strlen
    pop rdi
    cmp rax, 2
    jl global_error

    xor rcx, rcx
    loop1_i:
        cmp byte ptr [rdi + rcx], 0
        xor rcx, rcx
        je loop2_i

        cmp byte ptr [rdi + rcx], '+'
        je global_error
        cmp byte ptr [rdi + rcx], '-'
        je global_error
        cmp byte ptr [rdi + rcx], ' '
        je global_error
    
        xor rdx, rdx
        loop1_j:
            cmp byte ptr [rdi + rcx], byte ptr [rdi + rdx]
             global_error
            cmp rcx
            inc
            inc
        cmp
        ret

        inc rcx
        jmp loop

    loop2_i:
        cmp byte ptr [rdi + rcx], 0
        je leave_check_base
        xor rdx, rdx
        xor r8d, r8d
        loop2_j:



get_pos:
    xor
    loop:
        cmp 
        ret
        inc
    ret

ft_atoi_base:
    jmp check_base

    xor 
    xor
    push rdi
    mov rsi, rdi
    call ft_strlen
    pop rdi
    mov rax 

    loop:
        inc
    ret

global_error:
    mov rax, 0
    ret