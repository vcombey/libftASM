global _ft_memcpy

_ft_memcpy:
		push rdi		; save pointer
		cld
		mov rcx, rdx	; already align
		repnz movsb
		pop rax
		ret
