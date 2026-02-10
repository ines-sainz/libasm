.intel_syntax noprefix
.global ft_read

ft_read:

	mov rax, 0
	syscall

	ret