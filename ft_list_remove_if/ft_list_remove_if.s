.intel_syntax noprefix
.global ft_list_remove_if

ft_list_remove_if:
	push rbx
	push r12
	push r13
	push r14
	push r15

	cmp rdi, 0
	je return

	mov r13, rsi
	mov r14, rdx
	mov r15, rcx

	mov r12, rdi

	loop:
		cmp qword ptr [r12], 0
		je return

		mov r9, qword ptr [r12]
		mov rdi, qword ptr [r9 + 0]
		mov rsi, r13
		call R14
		cmp rax, 0
		je move_and_free_node

		lea r12, [r9 + 8]
		jmp loop

move_and_free_node:
	mov rbx, [r12]

	mov r9, qword ptr [rbx + 8]
	mov qword ptr [r12], r9

	mov rdi, qword ptr [rbx + 0]
	call r15

	mov rdi, rbx
	call free

	jmp loop

return:
	pop r15
	pop r14
	pop r13
	pop r12
	pop rbx
	ret

.section .note.GNU-stack,"",@progbits
