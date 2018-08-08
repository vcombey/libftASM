
section .text

global _ft_strcmp
_ft_strcmp:
.loop:
		cmp byte [rdi], 0
		je .endloop
		cmp byte [rsi], 0
		je .endloop
		mov r8b, byte [rsi]
		cmp byte [rdi], r8b
		jne .endloop
		inc rdi
		inc rsi
		jmp .loop
.endloop:
		xor rax, rax
		mov al, byte [rdi]	
		xor rcx, rcx
		mov cl, byte [rsi]
		sub eax, ecx
		ret
