.intel_syntax noprefix
.global ft_strlen

ft_strlen:
    mov rcx, 0

    loop:
        cmp byte ptr [rcx + rdi], 0
        je end
        inc rcx
        jmp loop

end:
    mov rax, rcx
    ret
