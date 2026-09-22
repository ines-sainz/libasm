# FT_STRLEN
## C CODE VS ANSIBLE CODE
```
size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}
```

```
ft_strlen:
    mov rcx, 0

    loop:
        cmp byte ptr [rcx + rdi], 0
        je end
        inc rcx
        jmp loop

end:
    mov rax, rcx
    ret
```

```
size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (*s)
    {
        (*s)++
		i++;
    }
    return (i);
}
´´´

```
ft_strlen:
    mov rax, rdi

    loop:
        cmp byte ptr [rdi], 0
        je salir
        inc rdi
        jmp loop

salir:
    sub rdi, rax
    mov rax, rdi
    ret
```

´´´
size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (*s)
    {
        (*s)++;
		i++;
    }
	return (i);
}

```

```
ft_strlen:
    mov rcx, 0

    loop:
        cmp byte ptr [rdi], 0
        je salir
        inc rdi
        inc rcx
        jmp loop

salir:
    mov rax, rcx
    ret
```