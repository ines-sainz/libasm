.intel_syntax noprefix
.global ft_strdup
.extern ft_strlen
.extern ft_strcpy
.extern malloc

ft_strdup:

	xor rcx, rcx

	mov rbx, rdi
	call ft_strlen
	inc rax
	mov rdi, rax
	call malloc
	cmp rax, 0
	je error

	mov rdi, rax
	mov rsi, rbx

	call ft_strcpy
	ret

error:
	mov rax, 1
	ret
