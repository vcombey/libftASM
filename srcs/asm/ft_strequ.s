
section .text

global _ft_strequ
extern _ft_strcmp

_ft_strequ:
		call _ft_strcmp
		cmp rax, 0
		je .equal
		mov rax, 0
		ret
.equal:
		mov rax, 1
		ret

