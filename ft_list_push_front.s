.intel_syntax noprefix
.global ft_list_push_front
.extern malloc
.extern __errno_location

ft_list_push_front:
	push rdi
	mov rdi, rsi
	call ft_lstnew
	pop rdi
	cmp rax, 0
	je error
	cmp [rdi], 0
	je no_prev_nodes
	mov [rax + 8], [rdi]
	mov [rdi], rax
	ret

ft_lstnew:
	mov rax, 16
	call malloc
	cmp rax, 0
	je malloc_error
	mov rax, rdi
	mov [rax + 8], 0
	ret

no_prev_nodes:
	mov [rdi], rax
	ret

malloc_error:
	ret

error:
	mov rdi, 12
	call __errno_location
	mov [rax], rdi # mov dword ptr [rax], edi (12 es un int, mueves solo 4 bytes en vez de 8)
	xor rax, rax # xor eax, eax --> (eax = últimos 32 bits de rax) los pone a 0 y la CPU pone el resto (más rápido y habitual en compiladores)

	pop rbx
	ret

