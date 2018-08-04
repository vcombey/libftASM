%include "syscall.s"

%define SYS_CALL 0x2000000
%define SYS_WRITE  (0x4 | SYS_CALL)
%define SYS_READ  (0x3 | SYS_CALL)
%define STDOUT_FILENO 0x1
%define BUFFSIZE 0x2

global _ft_cat

section .data
buff:	times BUFFSIZE db 0

section .text
_ft_cat:
		lea rsi, [rel buff]
		mov rdx, BUFFSIZE
.loop:
		mov rax, SYS_READ
		syscall

		mov rax, SYS_WRITE
		syscall
		jmp .loop
		ret
