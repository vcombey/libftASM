global _ft_strlen

section .text

_ft_strlen:
		mov r8, rdi		; save pointer
		mov r9, rdi		; save pointer
		mov rcx, 0x8
		and r9, 0x7
		sub rcx, r9
		cld

		cmp rcx, 0x8 	; already align
		je .loop

		xor rax, rax	; want to find a \0
		repnz scasb
		jz .found		; jump if found during alignement
		
		;#define haszero(v) (((v) - 0x01010101UL) & ~(v) & 0x80808080UL)
.loop:
		mov r9, qword [rdi]
		mov r10, r9
		mov r11, 0x0101010101010101
		sub r9, r11
		not r10
		mov r11, 0x8080808080808080
		and r10, r11
		and r9, r10
		cmp r9, 0x0
		ja .find_zero_among_8 		;jump if above 0
		add rdi, 0x8
		jmp .loop

.find_zero_among_8:
		xor rax, rax
		cld
		mov rcx, 0x8	; a zero byte was found among 8 bytes
		repnz scasb

.found:
		sub rdi, r8		; substract from saved pointer
		mov rax, rdi
		dec rax
		ret

;; Trivial implementation
;;_ft_strlen:
;;		xor rcx, rcx
;;		not rcx
;;		;mov rsi, rdi ; save pointer
;;		repnz scasb
;;		sub rdi, r8 ; substract from saved pointer
;;		mov rax, rdi
;;		;mov rax, rdi
;;		;sub rax, r8
;;		dec rax
;;		ret
