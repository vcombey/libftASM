global _ft_isdigit

_ft_isdigit:
	cmp edi, 48
	jge greater
	mov rax, 0
	ret
greater:
	cmp rdi, 57
	jle lower
	mov rax, 0
	ret
lower:
	mov rax, 1
	ret
