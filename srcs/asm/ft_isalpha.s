global _ft_isalpha

_ft_isalpha:
;mov rax, rdi
	cmp rdi, 97
	jge greater
	mov rax, 0
	ret
greater:
	cmp rdi, 122
	jle lower
	mov rax, 0
	ret
lower:
	mov rax, 1
	ret
		
;	push	rbp
;   mov     rbp, rsp
;sub		rsp, 16
;leave
;ret 
