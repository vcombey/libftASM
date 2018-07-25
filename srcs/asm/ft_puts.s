%include "syscall.s"

%define SYS_CALL 0x2000000
%define SYS_WRITE  (0x4 | SYS_CALL)
%define STDOUT_FILENO 0x1

global _ft_puts

_ft_puts:
	mov rax, SYS_WRITE
	mov rsi, rdi
	mov rdi, STDOUT_FILENO
	mov rdx, 5
	syscall
	ret
