# Entrada: rdi contiene el file descriptor en el que se va a escribir (int)
# Entrada: rsi contiene la cadena que se va a escribir (const void*)
# Entrada: rdx contiene la cantidad de bytes que se van a escribir (size_t)
# Salida:  rax contiene el número de bytes escritos o un número negativo si falla (int)

.intel_syntax noprefix
.global ft_write
.extern __errno_location

ft_write:
	mov rax, 1
	syscall

	cmp rax, 0
	jl .error
	ret

.error:
	neg rax
	push rax

	call __errno_location

	pop rdi
	mov [rax], rdi

	mov rax, -1
	ret

.section .note.GNU-stack,"",@progbits
