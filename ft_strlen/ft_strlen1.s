.intel_syntax noprefix
.global ft_strlen

ft_strlen:
    mov rax, rdi

    loop:
        cmp byte ptr [rdi], 0
        je salir
        inc rdi
        jmp loop

salir:
    sub rdi, rax
    mov rax, rdi
    ret
