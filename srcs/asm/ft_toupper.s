global _ft_toupper

_ft_toupper:
	xor rax, rax
	cmp edi, 97
	jge .greater
	jmp .is_not_lowercase

	.greater:
	cmp edi, 122
	jle .is_lowercase
	jmp .is_not_lowercase

	.is_lowercase:
	mov eax, edi
	sub eax, 32
	ret

	.is_not_lowercase:
	mov eax, edi
	ret
