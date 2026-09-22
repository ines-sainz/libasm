.intel_syntax noprefix
.global ft_list_size

ft_list_size:

    xor rax, rax

    loop:
        cmp rdi, 0
        je return

        mov rdi, [rdi + 8]
        inc rax

        jmp loop

return:
    ret

.section .note.GNU-stack,"",@progbits
