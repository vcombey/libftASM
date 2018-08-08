section .text
global _ft_memcmp

_ft_memcmp:
		mov rcx, rdx
		rep cmpsb
		dec rsi
		dec rdi
		xor rax, rax
		mov al, byte [rdi]	
		xor rcx, rcx
		mov cl, byte [rsi]
		sub eax, ecx
		ret
