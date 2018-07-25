global _ft_isascii

_ft_isascii:
	cmp edi, 0
	jge .greater
	mov rax, 0
	ret

	.greater:
	cmp edi, 127
	jle .lower
	mov rax, 0
	ret

	.lower:
	mov rax, 1
	ret
