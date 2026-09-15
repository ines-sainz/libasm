.intel_syntax noprefix
.global ft_list_push_front
.extern malloc
.extern __errno_location

ft_list_push_front:
	push rdi
	mov rdi, rsi
	call ft_lstnew

ft_lstnew:


error:
	mov rdi, 12
	call __errno_location
	mov [rax], rdi # mov dword ptr [rax], edi (12 es un int, mueves solo 4 bytes en vez de 8)
	xor rax, rax # xor eax, eax --> (eax = últimos 32 bits de rax) los pone a 0 y la CPU pone el resto (más rápido y habitual en compiladores)

	pop rbx
	ret

