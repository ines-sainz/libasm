.intel_syntax noprefix
.global ft_strlen

ft_strlen:
    mov rcx, 0

    loop:
        cmp byte ptr [rdi], 0
        je salir
        inc rdi
        inc rcx
        jmp loop

salir:
    mov rax, rcx
    ret
