global _ft_strcpy

_ft_strcpy:
		push rdi
		push rsi
		call _ft_strlen
		inc rax
		pop rsi
		pop rdi
		mov rcx, rax
		call _ft_memcpy
