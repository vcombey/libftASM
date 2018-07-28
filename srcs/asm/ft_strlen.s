global _ft_strlen

_ft_strlen:
		xor rax, rax
		mov r8, rdi		; save pointer
		push rdi		; save pointer
		mov rcx, 0x8
		and rdi, 0x7
		sub rcx, rdi
		and rcx, 0x7 	; rcx contains the number of bits to align
		pop rdi
		cld
		repnz scasb
		jz .found					;jump if found during alignement

		
		xor rcx, rcx
		not rcx
		;mov rsi, rdi ; save pointer
		repnz scasb

		;found among 8 bytes
		mov rcx, 0x8
		repnz scasb

.found:
		sub rdi, r8 ; substract from saved pointer
		mov rax, rdi
		;mov rax, rdi
		;sub rax, r8
		dec rax
		ret
