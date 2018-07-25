global _ft_isalnum
extern _ft_isdigit
extern _ft_isalpha

_ft_isalnum:
	call _ft_isdigit
	mov ebx, eax
	call _ft_isalpha
	or eax, ebx
	ret
