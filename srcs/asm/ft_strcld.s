section .text
global _ft_strcld

_ft_strcld:
		cmp byte [rdi], 0
		je .quit
		mov byte [rdi], 0
		inc rdi
		jmp _ft_strcld	
.quit:
		ret
