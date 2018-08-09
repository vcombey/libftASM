%include "syscall.s"

%define SYS_CALL 0x2000000
%define SYS_WRITE  (0x4 | SYS_CALL)
%define SYS_READ  (0x3 | SYS_CALL)
%define STDOUT_FILENO 0x1
%define BUFFSIZE 0x100

global _ft_cat

section .data
buff:	times BUFFSIZE db 0

section .text
_ft_cat:
	push rdi
	push rdi

.loop:
	mov rax, SYS_READ
	pop rdi
	push rdi
	lea rsi, [rel buff]
	mov rdx, BUFFSIZE
	syscall	
	jc .err
	cmp rax, 0
	je .quit

	mov rdx, rax
	mov rdi, STDOUT_FILENO
	mov rax, SYS_WRITE
	lea rsi, [rel buff]
	syscall	
	jc .err
	jmp .loop

.quit:
	xor rax, rax
	pop rdi
	pop rdi
	ret

.err:
	mov rax, 1
	pop rdi
	pop rdi
	ret
	
	;		lea rsi, [rel buff]
	;		mov rdx, BUFFSIZE
	;.loop:
	;		mov rax, SYS_READ
	;		syscall
	;
	;		mov rax, SYS_WRITE
	;		syscall
	;		jmp .loop
	;		ret
