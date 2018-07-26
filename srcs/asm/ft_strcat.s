%include "syscall.s"

global _ft_strcat
extern _ft_strlen

_ft_strcat:
	push rsi
	push rdi
	call _ft_strlen
	mov r8, rax
	pop rdi
	mov rsi, rdi
	call _ft_strlen
	mov r9, rax
	ret
