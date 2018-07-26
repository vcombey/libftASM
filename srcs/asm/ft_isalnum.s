global _ft_isalnum
extern _ft_isdigit
extern _ft_isalpha

_ft_isalnum:
	call _ft_isdigit
	mov ecx, eax
	call _ft_isalpha
	or eax, ecx
	ret
