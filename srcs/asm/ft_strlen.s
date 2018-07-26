global _ft_strlen

_ft_strlen:
	xor al, al
	mov r8, rdi ; save pointer
	repne scasb
	sub rdi, r8 ; substract from saved pointer
	sub rdi, 1
	mov rax, rdi
	ret
