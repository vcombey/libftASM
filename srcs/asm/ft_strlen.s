global _ft_strlen
section .text
_ft_strlen:
	xor rax, rax
	xor rcx, rcx
	not rcx
	mov r8, rdi ; save pointer
	;mov rsi, rdi ; save pointer
	cld
	repnz scasb
	sub rdi, r8 ; substract from saved pointer
	mov rax, rdi
	;mov rax, rdi
	;sub rax, r8
	dec rax
	ret
