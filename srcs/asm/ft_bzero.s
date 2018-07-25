global _ft_bzero

_ft_bzero:
	.loop:	
	mov byte [rdi], 0
	sub rsi, 1
	cmp rsi, 0
	jg .loop
	ret
