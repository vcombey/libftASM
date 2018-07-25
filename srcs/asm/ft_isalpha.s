global _ft_isalpha

_ft_isalpha:
	cmp edi, 97
	jge greater
	cmp edi, 65
	jge upper
	mov rax, 0
	ret
greater:
	cmp edi, 122
	jle lower
upper:	
	cmp edi, 90
	jle lower
	mov rax, 0
	ret
lower:
	mov rax, 1
	ret
