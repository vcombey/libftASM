section .text
global _ft_memcmp

_ft_memcmp:
		mov rcx, rdx
		rep cmpsb
		dec rsi
		dec rdi
		mov al, byte [rdi]	
		mov cl, byte [rsi]
		sub eax, ecx
		ret
