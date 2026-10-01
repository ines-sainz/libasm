# Entrada: rdi contiene el puntero a la cadena (const char *s)
# Salida:  rax contiene el puntero origina de la cadena (char*)

.intel_syntax noprefix
.global ft_strcpy

ft_strcpy:
	mov rax, rdi

.loop:
	mov dl, byte ptr [rsi]
	mov byte ptr [rdi], dl

	inc rsi
	inc rdi

	cmp dl, 0
	jne .loop

	ret

.section .note.GNU-stack,"",@progbits
