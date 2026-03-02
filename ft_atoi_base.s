.intel_syntax noprefix
.global ft_atoi_base
.extern ft_strlen

ft_atoi_base:
    jmp check_base

check_base:
    call ft_strlen
    cmp rax, 2
    jl error
    xor dl, dl
    xor al, al
    loop:

        loop1:

        jmp loop1
    jmp loop