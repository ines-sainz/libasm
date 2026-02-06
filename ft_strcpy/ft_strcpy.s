.intel_syntax noprefix
.global ft_strcpy

ft_strcpy:
	xor rcx, rcx
	loop:
		cmp byte ptr [rcx + rsi], 0
		je salir

		mov al, [rcx + rsi]
		mov [rcx + rdi], al
		inc rcx
		jmp loop

salir:
	mov byte ptr [rcx + rdi], 0
	mov rax, rdi
	ret

.section .note.GNU-stack,"",@progbits
