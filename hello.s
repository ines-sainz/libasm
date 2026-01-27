.intel_syntax noprefix
.global _start

.section .text

_start:
    mov rax, 60      # syscall: exit
    mov rdi, 42      # código de salida
    syscall
