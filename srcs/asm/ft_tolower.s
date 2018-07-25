global _ft_tolower

%define ASCII_A 65
%define ASCII_Z 90

_ft_tolower:
	xor rax, rax
	cmp edi, ASCII_A
	jge .greater
	jmp .is_not_uppercase

	.greater:
	cmp edi, ASCII_Z
	jle .is_uppercase
	jmp .is_not_uppercase

	.is_uppercase:
	mov eax, edi
	add eax, 32
	ret

	.is_not_uppercase:
	mov eax, edi
	ret
