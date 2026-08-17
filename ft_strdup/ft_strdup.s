.intel_syntax noprefix
.global ft_strdup
.extern ft_strlen
.extern ft_strcpy
.extern malloc
.extern __errno_location

ft_strdup:

	push rbx
	mov rbx, rdi

	call ft_strlen
	inc rax

	mov rdi, rax
	call malloc

	cmp rax, 0 # test rax, rax
	je error

	mov rdi, rax
	mov rsi, rbx
	call ft_strcpy

	pop rbx
	ret

error:
	mov rdi, 12
	call __errno_location
	mov [rax], rdi # mov dword ptr [rax], edi (12 es un int, mueves solo 4 bytes en vez de 8)
	xor rax, rax # xor eax, eax --> (eax = últimos 32 bits de rax) los pone a 0 y la CPU pone el resto (más rápido y habitual en compiladores)

	pop rbx
	ret
