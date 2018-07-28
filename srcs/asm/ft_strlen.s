global _ft_strlen
section .data
bitwise:
.low	dq 0x0101010101010101 
.high	dq 0x8080808080808080

section .text
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
	jz .found		; jump if found during alignement
		
;#define haszero(v) (((v) - 0x01010101UL) & ~(v) & 0x80808080UL)
.loop:
	mov r9, qword [rdi]
	mov r10, r9
	sub r9, qword [rel bitwise.low]
	not r10
	and r10, qword [rel  bitwise.high]
	and r9, r10
	cmp r9, 0x0
	jg .find_zero_among_8
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
