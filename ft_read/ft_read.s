.intel_syntax noprefix
.global ft_read

ft_read:

	mov rax, 0
	syscall

	cmp rax, 0
	jl error
	
	ret

error:
	neg rax
	mov rdi, rax
	call __errno_location
	mov [rax], rdi
	mov rax, -1
	ret
