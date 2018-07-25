global _ft_bzero
extern _ft_memset

_ft_bzero:
	.loop:	
	mov rdx, rsi
	mov esi, 0
	call _ft_memset
	ret
