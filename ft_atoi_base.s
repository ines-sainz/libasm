.intel_syntax noprefix
.global ft_atoi_base
.extern ft_strlen

check_base:
    push rdi
    mov rsi, rdi
    call ft_strlen
    pop rdi
    cmp rax, 2
    jl error
    xor dl, dl
    xor al, al
    loop:

        loop1:

        jmp loop1
    jmp loop

ft_atoi_base:
    jmp check_base