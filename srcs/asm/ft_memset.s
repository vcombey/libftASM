global _ft_memset

_ft_memset:
	.loop:	
	mov byte [rdi], sil
	add rdi, 1
	sub rdx, 1
	cmp rdx, 0
	jg .loop
	ret
