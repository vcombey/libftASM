%define SYS_CALL 0x2000000
%define SYS_MALLOC  | SYS_CALL)

extern _ft_strlen
extern _malloc
extern _ft_memcpy
global _ft_strdup

_ft_strdup:
		push rdi
		call _ft_strlen
		inc rax
		push rax
		mov rdi, rax
		call _malloc
		mov rdi, rax
		pop rdx
		pop rsi
		call _ft_memcpy
		ret
