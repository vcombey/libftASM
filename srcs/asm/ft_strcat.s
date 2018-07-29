%include "syscall.s"

global _ft_strcat
extern _ft_strlen
extern _ft_memcpy

_ft_strcat:
		push rsi
		push rdi
		call _ft_strlen
		pop rsi
		add rsi, rax
		pop rdi
		push rsi
		push rdi
		call _ft_strlen
		inc rax
		mov rcx, rax
		pop rsi
		pop rdi
		call _ft_memcpy	
		ret
