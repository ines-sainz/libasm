.intel_syntax noprefix
.global ft_strcpy

ft_strcpy:
	mov rax, rdi

	loop:
		cmp byte ptr [rsi], 0
		je salir

		mov dl, [rsi]
		mov [rdi], dl
		inc rdi
		inc rsi
		jmp loop

salir:
	mov byte ptr [rdi], 0
	ret

.section .note.GNU-stack,"",@progbits
