.intel_syntax noprefix
.global ft_strcmp

ft_strcmp:

loop:

	mov al, [rdi]
	mov dl, [rsi]

	cmp al, dl
	jne salir

	cmp al, 0
	je salir

	inc rdi
	inc rsi
	jmp loop

salir:
	movzx rax, al
	movzx rdx, dl
	sub rax, rdx
	ret
