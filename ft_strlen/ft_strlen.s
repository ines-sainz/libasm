# Entrada: rdi contiene el puntero a la cadena (const char *s)
# Salida:  rax contiene la longitud de la cadena (size_t)

.intel_syntax noprefix
.global ft_strlen

ft_strlen:
    mov rax, rdi

.loop:
    cmp byte ptr [rax], 0
    je .return
    inc rax
    jmp .loop

.return:
    sub rax, rdi
    ret

.section .note.GNU-stack,"",@progbits
