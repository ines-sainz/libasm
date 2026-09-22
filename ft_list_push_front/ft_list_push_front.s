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
	cmp qword ptr [rdi], 0
	je no_prev_nodes
	mov rdx, qword ptr [rdi]
    mov qword ptr [rax + 8], rdx
	mov qword ptr [rdi], rax
	ret

ft_lstnew:
	push rdi
	mov rdi, 16
	call malloc
	pop rdi
	cmp rax, 0
	je malloc_error
	mov qword ptr [rax], rdi
	mov qword ptr [rax + 8], 0
	ret

no_prev_nodes:
	mov qword ptr [rdi], rax
	ret

malloc_error:
	ret

error:
	mov rdi, 12
	call __errno_location
	mov dword ptr [rax], 12 # mov dword ptr [rax], edi (12 es un int, mueves solo 4 bytes en vez de 8)
	xor eax, eax # --> (eax = últimos 32 bits de rax) los pone a 0 y la CPU pone el resto (más rápido y habitual en compiladores)
	ret

