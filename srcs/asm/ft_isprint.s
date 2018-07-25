global _ft_isprint

_ft_isprint:
	cmp edi, 32
	jge .greater
	mov rax, 0
	ret

	.greater:
	cmp edi, 126
	jle .lower
	mov rax, 0
	ret

	.lower:
	mov rax, 1
	ret
