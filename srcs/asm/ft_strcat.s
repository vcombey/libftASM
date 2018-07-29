%include "syscall.s"

global _ft_strcat
extern _ft_strlen
extern _ft_strcpy

_ft_strcat:
		push rdi
		push rdi
		push rsi
		call _ft_strlen
		pop rsi
		pop rdi
		add rdi, rax
		call _ft_strcpy
		pop rdi
		mov rax, rdi
		ret
