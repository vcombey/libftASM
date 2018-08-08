global _ft_strchr

section .text

_ft_strchr:
.loop:
		cmp byte [rdi], sil
		je .found
		cmp byte [rdi], 0
		je .notfound
		inc rdi
		dec rcx
		jmp .loop
		ret
.found:
		mov rax, rdi
		ret
.notfound:
		xor rax, rax
		ret
