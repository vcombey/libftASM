%include "syscall.s"

%define SYS_CALL 0x2000000
%define SYS_WRITE  (0x4 | SYS_CALL)
%define STDOUT_FILENO 0x1

global _ft_puts
extern _ft_strlen

_ft_puts:
	push rdi
	call _ft_strlen
	pop rdi
	mov rdx, rax
	mov rax, SYS_WRITE
	mov rsi, rdi
	mov rdi, STDOUT_FILENO
	syscall
	ret
