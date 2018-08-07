global _ft_memchr

section .text

_ft_memchr:
		mov rcx, rdx
.loop:
		cmp rcx, 0
		je .notfound
		cmp byte [rdi], sil
		je .found
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
