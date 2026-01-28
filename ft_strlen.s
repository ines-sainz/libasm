.intel_syntax noprefix
.global ft_strlen

ft_strlen:
    mov 0, rcx

    cmp rdi, 0
    je equal
    loop:
        cmp [rcx + rdi], 0
        je equal
        inc rdi
        jmp loop


# size_t	ft_strlen(const char *s)
# {
#	size_t	i;
#
#	i = 0;
#	if (!s)
#		return (0);
#	while (s[i])
#		i++;
#	return (i);
#}
