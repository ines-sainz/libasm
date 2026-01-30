.intel_syntax noprefix
.global ft_strcpy

ft_strcpy:
	xor rcx, rcx
	loop:
		cmp byte ptr rsi, 0
		je salir

		mov byte ptr rdi, rsi
		inc rcx

salir:
	mov rax, rdi
