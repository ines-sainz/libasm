.intel_syntax noprefix
.global ft_strcmp

ft_strcmp:
    xor eax, eax
    xor edx, edx

.loop:
    mov al, byte ptr [rdi]
    mov dl, byte ptr [rsi]

    cmp al, dl
    jne .return

    cmp al, 0
    je .return

    inc rdi
    inc rsi
    jmp .loop

.return:
    sub rax, rdx
    ret

.section .note.GNU-stack,"",@progbits
