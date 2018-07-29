%include "syscall.s"

%define SYS_CALL 0x2000000
%define SYS_WRITE  (0x4 | SYS_CALL)
%define STDOUT_FILENO 0x1

global _ft_puts
extern _ft_strlen

section .data
newline: db 0xa

section .text
_ft_puts:
		push rdi
		call _ft_strlen
		mov rdi, STDOUT_FILENO
		pop rsi
		mov rdx, rax
		mov rax, SYS_WRITE
		syscall
		mov rdi, STDOUT_FILENO
		lea rsi, [rel newline]
		mov rdx, 1
		mov rax, SYS_WRITE
		syscall
		ret
