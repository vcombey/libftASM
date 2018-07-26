global _ft_memset

;_ft_memset:
;	.loop:	
;	mov byte [rdi], sil
;	add rdi, 1
;	sub rdx, 1
;	cmp rdx, 0
;	jg .loop
;	ret
;
;	rep STOS

_ft_memset:
	push rdi
	mov al, sil
	rep stosb
	pop rdi
	mov rax, rdi
	ret

;_ft_memset:
;	mov al, sil
;	;mov rsx in [edx] for rcx
;	rep stosb
;	ret
