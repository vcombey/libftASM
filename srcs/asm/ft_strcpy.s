extern _ft_strlen
extern _ft_memcpy
global _ft_strcpy

_ft_strcpy:
		push rdi
		push rsi
		mov rdi, rsi
		call _ft_strlen
		inc rax
		pop rsi
		pop rdi
		mov rdx, rax
		call _ft_memcpy
