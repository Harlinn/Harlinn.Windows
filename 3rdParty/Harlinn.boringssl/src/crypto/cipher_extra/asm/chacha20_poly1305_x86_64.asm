; This file is generated from a similarly-named Perl script in the BoringSSL
; source tree. Do not edit by hand.

OPTION	DOTNAME
.text$	SEGMENT ALIGN(256) 'CODE'
EXTERN	OPENSSL_ia32cap_P:NEAR

chacha20_poly1305_constants::

ALIGN	64
$L$chacha20_consts::
DB	'e','x','p','a','n','d',' ','3','2','-','b','y','t','e',' ','k'
DB	'e','x','p','a','n','d',' ','3','2','-','b','y','t','e',' ','k'
$L$rol8::
DB	3,0,1,2,7,4,5,6,11,8,9,10,15,12,13,14
DB	3,0,1,2,7,4,5,6,11,8,9,10,15,12,13,14
$L$rol16::
DB	2,3,0,1,6,7,4,5,10,11,8,9,14,15,12,13
DB	2,3,0,1,6,7,4,5,10,11,8,9,14,15,12,13
$L$avx2_init::
	DD	0,0,0,0
$L$sse_inc::
	DD	1,0,0,0
$L$avx2_inc::
	DD	2,0,0,0,2,0,0,0
$L$clamp::
	DQ	00FFFFFFC0FFFFFFFh,00FFFFFFC0FFFFFFCh
	DQ	0FFFFFFFFFFFFFFFFh,0FFFFFFFFFFFFFFFFh
ALIGN	16
$L$and_masks::
DB	0ffh,000h,000h,000h,000h,000h,000h,000h,000h,000h,000h,000h,000h,000h,000h,000h
DB	0ffh,0ffh,000h,000h,000h,000h,000h,000h,000h,000h,000h,000h,000h,000h,000h,000h
DB	0ffh,0ffh,0ffh,000h,000h,000h,000h,000h,000h,000h,000h,000h,000h,000h,000h,000h
DB	0ffh,0ffh,0ffh,0ffh,000h,000h,000h,000h,000h,000h,000h,000h,000h,000h,000h,000h
DB	0ffh,0ffh,0ffh,0ffh,0ffh,000h,000h,000h,000h,000h,000h,000h,000h,000h,000h,000h
DB	0ffh,0ffh,0ffh,0ffh,0ffh,0ffh,000h,000h,000h,000h,000h,000h,000h,000h,000h,000h
DB	0ffh,0ffh,0ffh,0ffh,0ffh,0ffh,0ffh,000h,000h,000h,000h,000h,000h,000h,000h,000h
DB	0ffh,0ffh,0ffh,0ffh,0ffh,0ffh,0ffh,0ffh,000h,000h,000h,000h,000h,000h,000h,000h
DB	0ffh,0ffh,0ffh,0ffh,0ffh,0ffh,0ffh,0ffh,0ffh,000h,000h,000h,000h,000h,000h,000h
DB	0ffh,0ffh,0ffh,0ffh,0ffh,0ffh,0ffh,0ffh,0ffh,0ffh,000h,000h,000h,000h,000h,000h
DB	0ffh,0ffh,0ffh,0ffh,0ffh,0ffh,0ffh,0ffh,0ffh,0ffh,0ffh,000h,000h,000h,000h,000h
DB	0ffh,0ffh,0ffh,0ffh,0ffh,0ffh,0ffh,0ffh,0ffh,0ffh,0ffh,0ffh,000h,000h,000h,000h
DB	0ffh,0ffh,0ffh,0ffh,0ffh,0ffh,0ffh,0ffh,0ffh,0ffh,0ffh,0ffh,0ffh,000h,000h,000h
DB	0ffh,0ffh,0ffh,0ffh,0ffh,0ffh,0ffh,0ffh,0ffh,0ffh,0ffh,0ffh,0ffh,0ffh,000h,000h
DB	0ffh,0ffh,0ffh,0ffh,0ffh,0ffh,0ffh,0ffh,0ffh,0ffh,0ffh,0ffh,0ffh,0ffh,0ffh,000h
DB	0ffh,0ffh,0ffh,0ffh,0ffh,0ffh,0ffh,0ffh,0ffh,0ffh,0ffh,0ffh,0ffh,0ffh,0ffh,0ffh


ALIGN	64
poly_hash_ad_internal	PROC PRIVATE


	xor	r10,r10
	xor	r11,r11
	xor	r12,r12
	cmp	r8,13
	jne	$L$hash_ad_loop
$L$poly_fast_tls_ad::

	mov	r10,QWORD PTR[rcx]
	mov	r11,QWORD PTR[5+rcx]
	shr	r11,24
	mov	r12,1
	mov	rax,QWORD PTR[((0+160+0))+rbp]
	mov	r15,rax
	mul	r10
	mov	r13,rax
	mov	r14,rdx
	mov	rax,QWORD PTR[((0+160+0))+rbp]
	mul	r11
	imul	r15,r12
	add	r14,rax
	adc	r15,rdx
	mov	rax,QWORD PTR[((8+160+0))+rbp]
	mov	r9,rax
	mul	r10
	add	r14,rax
	adc	rdx,0
	mov	r10,rdx
	mov	rax,QWORD PTR[((8+160+0))+rbp]
	mul	r11
	add	r15,rax
	adc	rdx,0
	imul	r9,r12
	add	r15,r10
	adc	r9,rdx
	mov	r10,r13
	mov	r11,r14
	mov	r12,r15
	and	r12,3
	mov	r13,r15
	and	r13,-4
	mov	r14,r9
	shrd	r15,r9,2
	shr	r9,2
	add	r15,r13
	adc	r9,r14
	add	r10,r15
	adc	r11,r9
	adc	r12,0

	DB	0F3h,0C3h		;repret
$L$hash_ad_loop::

	cmp	r8,16
	jb	$L$hash_ad_tail
	add	r10,QWORD PTR[((0+0))+rcx]
	adc	r11,QWORD PTR[((8+0))+rcx]
	adc	r12,1
	mov	rax,QWORD PTR[((0+160+0))+rbp]
	mov	r15,rax
	mul	r10
	mov	r13,rax
	mov	r14,rdx
	mov	rax,QWORD PTR[((0+160+0))+rbp]
	mul	r11
	imul	r15,r12
	add	r14,rax
	adc	r15,rdx
	mov	rax,QWORD PTR[((8+160+0))+rbp]
	mov	r9,rax
	mul	r10
	add	r14,rax
	adc	rdx,0
	mov	r10,rdx
	mov	rax,QWORD PTR[((8+160+0))+rbp]
	mul	r11
	add	r15,rax
	adc	rdx,0
	imul	r9,r12
	add	r15,r10
	adc	r9,rdx
	mov	r10,r13
	mov	r11,r14
	mov	r12,r15
	and	r12,3
	mov	r13,r15
	and	r13,-4
	mov	r14,r9
	shrd	r15,r9,2
	shr	r9,2
	add	r15,r13
	adc	r9,r14
	add	r10,r15
	adc	r11,r9
	adc	r12,0

	lea	rcx,QWORD PTR[16+rcx]
	sub	r8,16
	jmp	$L$hash_ad_loop
$L$hash_ad_tail::
	cmp	r8,0
	je	$L$hash_ad_done

	xor	r13,r13
	xor	r14,r14
	xor	r15,r15
	add	rcx,r8
$L$hash_ad_tail_loop::
	shld	r14,r13,8
	shl	r13,8
	movzx	r15,BYTE PTR[((-1))+rcx]
	xor	r13,r15
	dec	rcx
	dec	r8
	jne	$L$hash_ad_tail_loop

	add	r10,r13
	adc	r11,r14
	adc	r12,1
	mov	rax,QWORD PTR[((0+160+0))+rbp]
	mov	r15,rax
	mul	r10
	mov	r13,rax
	mov	r14,rdx
	mov	rax,QWORD PTR[((0+160+0))+rbp]
	mul	r11
	imul	r15,r12
	add	r14,rax
	adc	r15,rdx
	mov	rax,QWORD PTR[((8+160+0))+rbp]
	mov	r9,rax
	mul	r10
	add	r14,rax
	adc	rdx,0
	mov	r10,rdx
	mov	rax,QWORD PTR[((8+160+0))+rbp]
	mul	r11
	add	r15,rax
	adc	rdx,0
	imul	r9,r12
	add	r15,r10
	adc	r9,rdx
	mov	r10,r13
	mov	r11,r14
	mov	r12,r15
	and	r12,3
	mov	r13,r15
	and	r13,-4
	mov	r14,r9
	shrd	r15,r9,2
	shr	r9,2
	add	r15,r13
	adc	r9,r14
	add	r10,r15
	adc	r11,r9
	adc	r12,0


$L$hash_ad_done::
	DB	0F3h,0C3h		;repret

poly_hash_ad_internal	ENDP

PUBLIC	chacha20_poly1305_open

ALIGN	64
chacha20_poly1305_open	PROC PUBLIC
	mov	QWORD PTR[8+rsp],rdi	;WIN64 prologue
	mov	QWORD PTR[16+rsp],rsi
	mov	rax,rsp
$L$SEH_begin_chacha20_poly1305_open::
	mov	rdi,rcx
	mov	rsi,rdx
	mov	rdx,r8
	mov	rcx,r9
	mov	r8,QWORD PTR[40+rsp]
	mov	r9,QWORD PTR[48+rsp]



	push	rbp

	push	rbx

	push	r12

	push	r13

	push	r14

	push	r15



	push	r9

	sub	rsp,288 + 160 + 32


	lea	rbp,QWORD PTR[32+rsp]
	and	rbp,-32

	movaps	XMMWORD PTR[(0+0)+rbp],xmm6
	movaps	XMMWORD PTR[(16+0)+rbp],xmm7
	movaps	XMMWORD PTR[(32+0)+rbp],xmm8
	movaps	XMMWORD PTR[(48+0)+rbp],xmm9
	movaps	XMMWORD PTR[(64+0)+rbp],xmm10
	movaps	XMMWORD PTR[(80+0)+rbp],xmm11
	movaps	XMMWORD PTR[(96+0)+rbp],xmm12
	movaps	XMMWORD PTR[(112+0)+rbp],xmm13
	movaps	XMMWORD PTR[(128+0)+rbp],xmm14
	movaps	XMMWORD PTR[(144+0)+rbp],xmm15

	mov	rbx,rdx
	mov	QWORD PTR[((0+160+32))+rbp],r8
	mov	QWORD PTR[((8+160+32))+rbp],rbx

	mov	eax,DWORD PTR[((OPENSSL_ia32cap_P+8))]
	and	eax,288
	xor	eax,288
	jz	chacha20_poly1305_open_avx2

	cmp	rbx,128
	jbe	$L$open_sse_128

	movdqa	xmm0,XMMWORD PTR[$L$chacha20_consts]
	movdqu	xmm4,XMMWORD PTR[r9]
	movdqu	xmm8,XMMWORD PTR[16+r9]
	movdqu	xmm12,XMMWORD PTR[32+r9]

	movdqa	xmm7,xmm12

	movdqa	XMMWORD PTR[(160+48)+rbp],xmm4
	movdqa	XMMWORD PTR[(160+64)+rbp],xmm8
	movdqa	XMMWORD PTR[(160+96)+rbp],xmm12
	mov	r10,10
$L$open_sse_init_rounds::
	paddd	xmm0,xmm4
	pxor	xmm12,xmm0
	pshufb	xmm12,XMMWORD PTR[$L$rol16]
	paddd	xmm8,xmm12
	pxor	xmm4,xmm8
	movdqa	xmm3,xmm4
	pslld	xmm3,12
	psrld	xmm4,20
	pxor	xmm4,xmm3
	paddd	xmm0,xmm4
	pxor	xmm12,xmm0
	pshufb	xmm12,XMMWORD PTR[$L$rol8]
	paddd	xmm8,xmm12
	pxor	xmm4,xmm8
	movdqa	xmm3,xmm4
	pslld	xmm3,7
	psrld	xmm4,25
	pxor	xmm4,xmm3
DB	102,15,58,15,228,4
DB	102,69,15,58,15,192,8
DB	102,69,15,58,15,228,12
	paddd	xmm0,xmm4
	pxor	xmm12,xmm0
	pshufb	xmm12,XMMWORD PTR[$L$rol16]
	paddd	xmm8,xmm12
	pxor	xmm4,xmm8
	movdqa	xmm3,xmm4
	pslld	xmm3,12
	psrld	xmm4,20
	pxor	xmm4,xmm3
	paddd	xmm0,xmm4
	pxor	xmm12,xmm0
	pshufb	xmm12,XMMWORD PTR[$L$rol8]
	paddd	xmm8,xmm12
	pxor	xmm4,xmm8
	movdqa	xmm3,xmm4
	pslld	xmm3,7
	psrld	xmm4,25
	pxor	xmm4,xmm3
DB	102,15,58,15,228,12
DB	102,69,15,58,15,192,8
DB	102,69,15,58,15,228,4

	dec	r10
	jne	$L$open_sse_init_rounds

	paddd	xmm0,XMMWORD PTR[$L$chacha20_consts]
	paddd	xmm4,XMMWORD PTR[((160+48))+rbp]

	pand	xmm0,XMMWORD PTR[$L$clamp]
	movdqa	XMMWORD PTR[(160+0)+rbp],xmm0
	movdqa	XMMWORD PTR[(160+16)+rbp],xmm4

	mov	r8,r8
	call	poly_hash_ad_internal
$L$open_sse_main_loop::
	cmp	rbx,16*16
	jb	$L$open_sse_tail

	movdqa	xmm0,XMMWORD PTR[$L$chacha20_consts]
	movdqa	xmm4,XMMWORD PTR[((160+48))+rbp]
	movdqa	xmm8,XMMWORD PTR[((160+64))+rbp]
	movdqa	xmm1,xmm0
	movdqa	xmm5,xmm4
	movdqa	xmm9,xmm8
	movdqa	xmm2,xmm0
	movdqa	xmm6,xmm4
	movdqa	xmm10,xmm8
	movdqa	xmm3,xmm0
	movdqa	xmm7,xmm4
	movdqa	xmm11,xmm8
	movdqa	xmm15,XMMWORD PTR[((160+96))+rbp]
	paddd	xmm15,XMMWORD PTR[$L$sse_inc]
	movdqa	xmm14,xmm15
	paddd	xmm14,XMMWORD PTR[$L$sse_inc]
	movdqa	xmm13,xmm14
	paddd	xmm13,XMMWORD PTR[$L$sse_inc]
	movdqa	xmm12,xmm13
	paddd	xmm12,XMMWORD PTR[$L$sse_inc]
	movdqa	XMMWORD PTR[(160+96)+rbp],xmm12
	movdqa	XMMWORD PTR[(160+112)+rbp],xmm13
	movdqa	XMMWORD PTR[(160+128)+rbp],xmm14
	movdqa	XMMWORD PTR[(160+144)+rbp],xmm15



	mov	rcx,4
	mov	r8,rsi
$L$open_sse_main_loop_rounds::
	movdqa	XMMWORD PTR[(160+80)+rbp],xmm8
	movdqa	xmm8,XMMWORD PTR[$L$rol16]
	paddd	xmm3,xmm7
	paddd	xmm2,xmm6
	paddd	xmm1,xmm5
	paddd	xmm0,xmm4
	pxor	xmm15,xmm3
	pxor	xmm14,xmm2
	pxor	xmm13,xmm1
	pxor	xmm12,xmm0
DB	102,69,15,56,0,248
DB	102,69,15,56,0,240
DB	102,69,15,56,0,232
DB	102,69,15,56,0,224
	movdqa	xmm8,XMMWORD PTR[((160+80))+rbp]
	paddd	xmm11,xmm15
	paddd	xmm10,xmm14
	paddd	xmm9,xmm13
	paddd	xmm8,xmm12
	pxor	xmm7,xmm11
	add	r10,QWORD PTR[((0+0))+r8]
	adc	r11,QWORD PTR[((8+0))+r8]
	adc	r12,1

	lea	r8,QWORD PTR[16+r8]
	pxor	xmm6,xmm10
	pxor	xmm5,xmm9
	pxor	xmm4,xmm8
	movdqa	XMMWORD PTR[(160+80)+rbp],xmm8
	movdqa	xmm8,xmm7
	psrld	xmm8,20
	pslld	xmm7,32-20
	pxor	xmm7,xmm8
	movdqa	xmm8,xmm6
	psrld	xmm8,20
	pslld	xmm6,32-20
	pxor	xmm6,xmm8
	movdqa	xmm8,xmm5
	psrld	xmm8,20
	pslld	xmm5,32-20
	pxor	xmm5,xmm8
	movdqa	xmm8,xmm4
	psrld	xmm8,20
	pslld	xmm4,32-20
	pxor	xmm4,xmm8
	mov	rax,QWORD PTR[((0+160+0))+rbp]
	mov	r15,rax
	mul	r10
	mov	r13,rax
	mov	r14,rdx
	mov	rax,QWORD PTR[((0+160+0))+rbp]
	mul	r11
	imul	r15,r12
	add	r14,rax
	adc	r15,rdx
	movdqa	xmm8,XMMWORD PTR[$L$rol8]
	paddd	xmm3,xmm7
	paddd	xmm2,xmm6
	paddd	xmm1,xmm5
	paddd	xmm0,xmm4
	pxor	xmm15,xmm3
	pxor	xmm14,xmm2
	pxor	xmm13,xmm1
	pxor	xmm12,xmm0
DB	102,69,15,56,0,248
DB	102,69,15,56,0,240
DB	102,69,15,56,0,232
DB	102,69,15,56,0,224
	movdqa	xmm8,XMMWORD PTR[((160+80))+rbp]
	paddd	xmm11,xmm15
	paddd	xmm10,xmm14
	paddd	xmm9,xmm13
	paddd	xmm8,xmm12
	pxor	xmm7,xmm11
	pxor	xmm6,xmm10
	mov	rax,QWORD PTR[((8+160+0))+rbp]
	mov	r9,rax
	mul	r10
	add	r14,rax
	adc	rdx,0
	mov	r10,rdx
	mov	rax,QWORD PTR[((8+160+0))+rbp]
	mul	r11
	add	r15,rax
	adc	rdx,0
	pxor	xmm5,xmm9
	pxor	xmm4,xmm8
	movdqa	XMMWORD PTR[(160+80)+rbp],xmm8
	movdqa	xmm8,xmm7
	psrld	xmm8,25
	pslld	xmm7,32-25
	pxor	xmm7,xmm8
	movdqa	xmm8,xmm6
	psrld	xmm8,25
	pslld	xmm6,32-25
	pxor	xmm6,xmm8
	movdqa	xmm8,xmm5
	psrld	xmm8,25
	pslld	xmm5,32-25
	pxor	xmm5,xmm8
	movdqa	xmm8,xmm4
	psrld	xmm8,25
	pslld	xmm4,32-25
	pxor	xmm4,xmm8
	movdqa	xmm8,XMMWORD PTR[((160+80))+rbp]
	imul	r9,r12
	add	r15,r10
	adc	r9,rdx
DB	102,15,58,15,255,4
DB	102,69,15,58,15,219,8
DB	102,69,15,58,15,255,12
DB	102,15,58,15,246,4
DB	102,69,15,58,15,210,8
DB	102,69,15,58,15,246,12
DB	102,15,58,15,237,4
DB	102,69,15,58,15,201,8
DB	102,69,15,58,15,237,12
DB	102,15,58,15,228,4
DB	102,69,15,58,15,192,8
DB	102,69,15,58,15,228,12
	movdqa	XMMWORD PTR[(160+80)+rbp],xmm8
	movdqa	xmm8,XMMWORD PTR[$L$rol16]
	paddd	xmm3,xmm7
	paddd	xmm2,xmm6
	paddd	xmm1,xmm5
	paddd	xmm0,xmm4
	pxor	xmm15,xmm3
	pxor	xmm14,xmm2
	mov	r10,r13
	mov	r11,r14
	mov	r12,r15
	and	r12,3
	mov	r13,r15
	and	r13,-4
	mov	r14,r9
	shrd	r15,r9,2
	shr	r9,2
	add	r15,r13
	adc	r9,r14
	add	r10,r15
	adc	r11,r9
	adc	r12,0
	pxor	xmm13,xmm1
	pxor	xmm12,xmm0
DB	102,69,15,56,0,248
DB	102,69,15,56,0,240
DB	102,69,15,56,0,232
DB	102,69,15,56,0,224
	movdqa	xmm8,XMMWORD PTR[((160+80))+rbp]
	paddd	xmm11,xmm15
	paddd	xmm10,xmm14
	paddd	xmm9,xmm13
	paddd	xmm8,xmm12
	pxor	xmm7,xmm11
	pxor	xmm6,xmm10
	pxor	xmm5,xmm9
	pxor	xmm4,xmm8
	movdqa	XMMWORD PTR[(160+80)+rbp],xmm8
	movdqa	xmm8,xmm7
	psrld	xmm8,20
	pslld	xmm7,32-20
	pxor	xmm7,xmm8
	movdqa	xmm8,xmm6
	psrld	xmm8,20
	pslld	xmm6,32-20
	pxor	xmm6,xmm8
	movdqa	xmm8,xmm5
	psrld	xmm8,20
	pslld	xmm5,32-20
	pxor	xmm5,xmm8
	movdqa	xmm8,xmm4
	psrld	xmm8,20
	pslld	xmm4,32-20
	pxor	xmm4,xmm8
	movdqa	xmm8,XMMWORD PTR[$L$rol8]
	paddd	xmm3,xmm7
	paddd	xmm2,xmm6
	paddd	xmm1,xmm5
	paddd	xmm0,xmm4
	pxor	xmm15,xmm3
	pxor	xmm14,xmm2
	pxor	xmm13,xmm1
	pxor	xmm12,xmm0
DB	102,69,15,56,0,248
DB	102,69,15,56,0,240
DB	102,69,15,56,0,232
DB	102,69,15,56,0,224
	movdqa	xmm8,XMMWORD PTR[((160+80))+rbp]
	paddd	xmm11,xmm15
	paddd	xmm10,xmm14
	paddd	xmm9,xmm13
	paddd	xmm8,xmm12
	pxor	xmm7,xmm11
	pxor	xmm6,xmm10
	pxor	xmm5,xmm9
	pxor	xmm4,xmm8
	movdqa	XMMWORD PTR[(160+80)+rbp],xmm8
	movdqa	xmm8,xmm7
	psrld	xmm8,25
	pslld	xmm7,32-25
	pxor	xmm7,xmm8
	movdqa	xmm8,xmm6
	psrld	xmm8,25
	pslld	xmm6,32-25
	pxor	xmm6,xmm8
	movdqa	xmm8,xmm5
	psrld	xmm8,25
	pslld	xmm5,32-25
	pxor	xmm5,xmm8
	movdqa	xmm8,xmm4
	psrld	xmm8,25
	pslld	xmm4,32-25
	pxor	xmm4,xmm8
	movdqa	xmm8,XMMWORD PTR[((160+80))+rbp]
DB	102,15,58,15,255,12
DB	102,69,15,58,15,219,8
DB	102,69,15,58,15,255,4
DB	102,15,58,15,246,12
DB	102,69,15,58,15,210,8
DB	102,69,15,58,15,246,4
DB	102,15,58,15,237,12
DB	102,69,15,58,15,201,8
DB	102,69,15,58,15,237,4
DB	102,15,58,15,228,12
DB	102,69,15,58,15,192,8
DB	102,69,15,58,15,228,4

	dec	rcx
	jge	$L$open_sse_main_loop_rounds
	add	r10,QWORD PTR[((0+0))+r8]
	adc	r11,QWORD PTR[((8+0))+r8]
	adc	r12,1
	mov	rax,QWORD PTR[((0+160+0))+rbp]
	mov	r15,rax
	mul	r10
	mov	r13,rax
	mov	r14,rdx
	mov	rax,QWORD PTR[((0+160+0))+rbp]
	mul	r11
	imul	r15,r12
	add	r14,rax
	adc	r15,rdx
	mov	rax,QWORD PTR[((8+160+0))+rbp]
	mov	r9,rax
	mul	r10
	add	r14,rax
	adc	rdx,0
	mov	r10,rdx
	mov	rax,QWORD PTR[((8+160+0))+rbp]
	mul	r11
	add	r15,rax
	adc	rdx,0
	imul	r9,r12
	add	r15,r10
	adc	r9,rdx
	mov	r10,r13
	mov	r11,r14
	mov	r12,r15
	and	r12,3
	mov	r13,r15
	and	r13,-4
	mov	r14,r9
	shrd	r15,r9,2
	shr	r9,2
	add	r15,r13
	adc	r9,r14
	add	r10,r15
	adc	r11,r9
	adc	r12,0

	lea	r8,QWORD PTR[16+r8]
	cmp	rcx,-6
	jg	$L$open_sse_main_loop_rounds
	paddd	xmm3,XMMWORD PTR[$L$chacha20_consts]
	paddd	xmm7,XMMWORD PTR[((160+48))+rbp]
	paddd	xmm11,XMMWORD PTR[((160+64))+rbp]
	paddd	xmm15,XMMWORD PTR[((160+144))+rbp]
	paddd	xmm2,XMMWORD PTR[$L$chacha20_consts]
	paddd	xmm6,XMMWORD PTR[((160+48))+rbp]
	paddd	xmm10,XMMWORD PTR[((160+64))+rbp]
	paddd	xmm14,XMMWORD PTR[((160+128))+rbp]
	paddd	xmm1,XMMWORD PTR[$L$chacha20_consts]
	paddd	xmm5,XMMWORD PTR[((160+48))+rbp]
	paddd	xmm9,XMMWORD PTR[((160+64))+rbp]
	paddd	xmm13,XMMWORD PTR[((160+112))+rbp]
	paddd	xmm0,XMMWORD PTR[$L$chacha20_consts]
	paddd	xmm4,XMMWORD PTR[((160+48))+rbp]
	paddd	xmm8,XMMWORD PTR[((160+64))+rbp]
	paddd	xmm12,XMMWORD PTR[((160+96))+rbp]
	movdqa	XMMWORD PTR[(160+80)+rbp],xmm12
	movdqu	xmm12,XMMWORD PTR[((0 + 0))+rsi]
	pxor	xmm12,xmm3
	movdqu	XMMWORD PTR[(0 + 0)+rdi],xmm12
	movdqu	xmm12,XMMWORD PTR[((16 + 0))+rsi]
	pxor	xmm12,xmm7
	movdqu	XMMWORD PTR[(16 + 0)+rdi],xmm12
	movdqu	xmm12,XMMWORD PTR[((32 + 0))+rsi]
	pxor	xmm12,xmm11
	movdqu	XMMWORD PTR[(32 + 0)+rdi],xmm12
	movdqu	xmm12,XMMWORD PTR[((48 + 0))+rsi]
	pxor	xmm12,xmm15
	movdqu	XMMWORD PTR[(48 + 0)+rdi],xmm12
	movdqu	xmm3,XMMWORD PTR[((0 + 64))+rsi]
	movdqu	xmm7,XMMWORD PTR[((16 + 64))+rsi]
	movdqu	xmm11,XMMWORD PTR[((32 + 64))+rsi]
	movdqu	xmm15,XMMWORD PTR[((48 + 64))+rsi]
	pxor	xmm2,xmm3
	pxor	xmm6,xmm7
	pxor	xmm10,xmm11
	pxor	xmm15,xmm14
	movdqu	XMMWORD PTR[(0 + 64)+rdi],xmm2
	movdqu	XMMWORD PTR[(16 + 64)+rdi],xmm6
	movdqu	XMMWORD PTR[(32 + 64)+rdi],xmm10
	movdqu	XMMWORD PTR[(48 + 64)+rdi],xmm15
	movdqu	xmm3,XMMWORD PTR[((0 + 128))+rsi]
	movdqu	xmm7,XMMWORD PTR[((16 + 128))+rsi]
	movdqu	xmm11,XMMWORD PTR[((32 + 128))+rsi]
	movdqu	xmm15,XMMWORD PTR[((48 + 128))+rsi]
	pxor	xmm1,xmm3
	pxor	xmm5,xmm7
	pxor	xmm9,xmm11
	pxor	xmm15,xmm13
	movdqu	XMMWORD PTR[(0 + 128)+rdi],xmm1
	movdqu	XMMWORD PTR[(16 + 128)+rdi],xmm5
	movdqu	XMMWORD PTR[(32 + 128)+rdi],xmm9
	movdqu	XMMWORD PTR[(48 + 128)+rdi],xmm15
	movdqu	xmm3,XMMWORD PTR[((0 + 192))+rsi]
	movdqu	xmm7,XMMWORD PTR[((16 + 192))+rsi]
	movdqu	xmm11,XMMWORD PTR[((32 + 192))+rsi]
	movdqu	xmm15,XMMWORD PTR[((48 + 192))+rsi]
	pxor	xmm0,xmm3
	pxor	xmm4,xmm7
	pxor	xmm8,xmm11
	pxor	xmm15,XMMWORD PTR[((160+80))+rbp]
	movdqu	XMMWORD PTR[(0 + 192)+rdi],xmm0
	movdqu	XMMWORD PTR[(16 + 192)+rdi],xmm4
	movdqu	XMMWORD PTR[(32 + 192)+rdi],xmm8
	movdqu	XMMWORD PTR[(48 + 192)+rdi],xmm15

	lea	rsi,QWORD PTR[256+rsi]
	lea	rdi,QWORD PTR[256+rdi]
	sub	rbx,16*16
	jmp	$L$open_sse_main_loop
$L$open_sse_tail::

	test	rbx,rbx
	jz	$L$open_sse_finalize
	cmp	rbx,12*16
	ja	$L$open_sse_tail_256
	cmp	rbx,8*16
	ja	$L$open_sse_tail_192
	cmp	rbx,4*16
	ja	$L$open_sse_tail_128
	movdqa	xmm0,XMMWORD PTR[$L$chacha20_consts]
	movdqa	xmm4,XMMWORD PTR[((160+48))+rbp]
	movdqa	xmm8,XMMWORD PTR[((160+64))+rbp]
	movdqa	xmm12,XMMWORD PTR[((160+96))+rbp]
	paddd	xmm12,XMMWORD PTR[$L$sse_inc]
	movdqa	XMMWORD PTR[(160+96)+rbp],xmm12

	xor	r8,r8
	mov	rcx,rbx
	cmp	rcx,16
	jb	$L$open_sse_tail_64_rounds
$L$open_sse_tail_64_rounds_and_x1hash::
	add	r10,QWORD PTR[((0+0))+r8*1+rsi]
	adc	r11,QWORD PTR[((8+0))+r8*1+rsi]
	adc	r12,1
	mov	rax,QWORD PTR[((0+160+0))+rbp]
	mov	r15,rax
	mul	r10
	mov	r13,rax
	mov	r14,rdx
	mov	rax,QWORD PTR[((0+160+0))+rbp]
	mul	r11
	imul	r15,r12
	add	r14,rax
	adc	r15,rdx
	mov	rax,QWORD PTR[((8+160+0))+rbp]
	mov	r9,rax
	mul	r10
	add	r14,rax
	adc	rdx,0
	mov	r10,rdx
	mov	rax,QWORD PTR[((8+160+0))+rbp]
	mul	r11
	add	r15,rax
	adc	rdx,0
	imul	r9,r12
	add	r15,r10
	adc	r9,rdx
	mov	r10,r13
	mov	r11,r14
	mov	r12,r15
	and	r12,3
	mov	r13,r15
	and	r13,-4
	mov	r14,r9
	shrd	r15,r9,2
	shr	r9,2
	add	r15,r13
	adc	r9,r14
	add	r10,r15
	adc	r11,r9
	adc	r12,0

	sub	rcx,16
$L$open_sse_tail_64_rounds::
	add	r8,16
	paddd	xmm0,xmm4
	pxor	xmm12,xmm0
	pshufb	xmm12,XMMWORD PTR[$L$rol16]
	paddd	xmm8,xmm12
	pxor	xmm4,xmm8
	movdqa	xmm3,xmm4
	pslld	xmm3,12
	psrld	xmm4,20
	pxor	xmm4,xmm3
	paddd	xmm0,xmm4
	pxor	xmm12,xmm0
	pshufb	xmm12,XMMWORD PTR[$L$rol8]
	paddd	xmm8,xmm12
	pxor	xmm4,xmm8
	movdqa	xmm3,xmm4
	pslld	xmm3,7
	psrld	xmm4,25
	pxor	xmm4,xmm3
DB	102,15,58,15,228,4
DB	102,69,15,58,15,192,8
DB	102,69,15,58,15,228,12
	paddd	xmm0,xmm4
	pxor	xmm12,xmm0
	pshufb	xmm12,XMMWORD PTR[$L$rol16]
	paddd	xmm8,xmm12
	pxor	xmm4,xmm8
	movdqa	xmm3,xmm4
	pslld	xmm3,12
	psrld	xmm4,20
	pxor	xmm4,xmm3
	paddd	xmm0,xmm4
	pxor	xmm12,xmm0
	pshufb	xmm12,XMMWORD PTR[$L$rol8]
	paddd	xmm8,xmm12
	pxor	xmm4,xmm8
	movdqa	xmm3,xmm4
	pslld	xmm3,7
	psrld	xmm4,25
	pxor	xmm4,xmm3
DB	102,15,58,15,228,12
DB	102,69,15,58,15,192,8
DB	102,69,15,58,15,228,4

	cmp	rcx,16
	jae	$L$open_sse_tail_64_rounds_and_x1hash
	cmp	r8,10*16
	jne	$L$open_sse_tail_64_rounds
	paddd	xmm0,XMMWORD PTR[$L$chacha20_consts]
	paddd	xmm4,XMMWORD PTR[((160+48))+rbp]
	paddd	xmm8,XMMWORD PTR[((160+64))+rbp]
	paddd	xmm12,XMMWORD PTR[((160+96))+rbp]

	jmp	$L$open_sse_tail_64_dec_loop

$L$open_sse_tail_128::
	movdqa	xmm0,XMMWORD PTR[$L$chacha20_consts]
	movdqa	xmm4,XMMWORD PTR[((160+48))+rbp]
	movdqa	xmm8,XMMWORD PTR[((160+64))+rbp]
	movdqa	xmm1,xmm0
	movdqa	xmm5,xmm4
	movdqa	xmm9,xmm8
	movdqa	xmm13,XMMWORD PTR[((160+96))+rbp]
	paddd	xmm13,XMMWORD PTR[$L$sse_inc]
	movdqa	xmm12,xmm13
	paddd	xmm12,XMMWORD PTR[$L$sse_inc]
	movdqa	XMMWORD PTR[(160+96)+rbp],xmm12
	movdqa	XMMWORD PTR[(160+112)+rbp],xmm13

	mov	rcx,rbx
	and	rcx,-16
	xor	r8,r8
$L$open_sse_tail_128_rounds_and_x1hash::
	add	r10,QWORD PTR[((0+0))+r8*1+rsi]
	adc	r11,QWORD PTR[((8+0))+r8*1+rsi]
	adc	r12,1
	mov	rax,QWORD PTR[((0+160+0))+rbp]
	mov	r15,rax
	mul	r10
	mov	r13,rax
	mov	r14,rdx
	mov	rax,QWORD PTR[((0+160+0))+rbp]
	mul	r11
	imul	r15,r12
	add	r14,rax
	adc	r15,rdx
	mov	rax,QWORD PTR[((8+160+0))+rbp]
	mov	r9,rax
	mul	r10
	add	r14,rax
	adc	rdx,0
	mov	r10,rdx
	mov	rax,QWORD PTR[((8+160+0))+rbp]
	mul	r11
	add	r15,rax
	adc	rdx,0
	imul	r9,r12
	add	r15,r10
	adc	r9,rdx
	mov	r10,r13
	mov	r11,r14
	mov	r12,r15
	and	r12,3
	mov	r13,r15
	and	r13,-4
	mov	r14,r9
	shrd	r15,r9,2
	shr	r9,2
	add	r15,r13
	adc	r9,r14
	add	r10,r15
	adc	r11,r9
	adc	r12,0

$L$open_sse_tail_128_rounds::
	add	r8,16
	paddd	xmm0,xmm4
	pxor	xmm12,xmm0
	pshufb	xmm12,XMMWORD PTR[$L$rol16]
	paddd	xmm8,xmm12
	pxor	xmm4,xmm8
	movdqa	xmm3,xmm4
	pslld	xmm3,12
	psrld	xmm4,20
	pxor	xmm4,xmm3
	paddd	xmm0,xmm4
	pxor	xmm12,xmm0
	pshufb	xmm12,XMMWORD PTR[$L$rol8]
	paddd	xmm8,xmm12
	pxor	xmm4,xmm8
	movdqa	xmm3,xmm4
	pslld	xmm3,7
	psrld	xmm4,25
	pxor	xmm4,xmm3
DB	102,15,58,15,228,4
DB	102,69,15,58,15,192,8
DB	102,69,15,58,15,228,12
	paddd	xmm1,xmm5
	pxor	xmm13,xmm1
	pshufb	xmm13,XMMWORD PTR[$L$rol16]
	paddd	xmm9,xmm13
	pxor	xmm5,xmm9
	movdqa	xmm3,xmm5
	pslld	xmm3,12
	psrld	xmm5,20
	pxor	xmm5,xmm3
	paddd	xmm1,xmm5
	pxor	xmm13,xmm1
	pshufb	xmm13,XMMWORD PTR[$L$rol8]
	paddd	xmm9,xmm13
	pxor	xmm5,xmm9
	movdqa	xmm3,xmm5
	pslld	xmm3,7
	psrld	xmm5,25
	pxor	xmm5,xmm3
DB	102,15,58,15,237,4
DB	102,69,15,58,15,201,8
DB	102,69,15,58,15,237,12
	paddd	xmm0,xmm4
	pxor	xmm12,xmm0
	pshufb	xmm12,XMMWORD PTR[$L$rol16]
	paddd	xmm8,xmm12
	pxor	xmm4,xmm8
	movdqa	xmm3,xmm4
	pslld	xmm3,12
	psrld	xmm4,20
	pxor	xmm4,xmm3
	paddd	xmm0,xmm4
	pxor	xmm12,xmm0
	pshufb	xmm12,XMMWORD PTR[$L$rol8]
	paddd	xmm8,xmm12
	pxor	xmm4,xmm8
	movdqa	xmm3,xmm4
	pslld	xmm3,7
	psrld	xmm4,25
	pxor	xmm4,xmm3
DB	102,15,58,15,228,12
DB	102,69,15,58,15,192,8
DB	102,69,15,58,15,228,4
	paddd	xmm1,xmm5
	pxor	xmm13,xmm1
	pshufb	xmm13,XMMWORD PTR[$L$rol16]
	paddd	xmm9,xmm13
	pxor	xmm5,xmm9
	movdqa	xmm3,xmm5
	pslld	xmm3,12
	psrld	xmm5,20
	pxor	xmm5,xmm3
	paddd	xmm1,xmm5
	pxor	xmm13,xmm1
	pshufb	xmm13,XMMWORD PTR[$L$rol8]
	paddd	xmm9,xmm13
	pxor	xmm5,xmm9
	movdqa	xmm3,xmm5
	pslld	xmm3,7
	psrld	xmm5,25
	pxor	xmm5,xmm3
DB	102,15,58,15,237,12
DB	102,69,15,58,15,201,8
DB	102,69,15,58,15,237,4

	cmp	r8,rcx
	jb	$L$open_sse_tail_128_rounds_and_x1hash
	cmp	r8,10*16
	jne	$L$open_sse_tail_128_rounds
	paddd	xmm1,XMMWORD PTR[$L$chacha20_consts]
	paddd	xmm5,XMMWORD PTR[((160+48))+rbp]
	paddd	xmm9,XMMWORD PTR[((160+64))+rbp]
	paddd	xmm13,XMMWORD PTR[((160+112))+rbp]
	paddd	xmm0,XMMWORD PTR[$L$chacha20_consts]
	paddd	xmm4,XMMWORD PTR[((160+48))+rbp]
	paddd	xmm8,XMMWORD PTR[((160+64))+rbp]
	paddd	xmm12,XMMWORD PTR[((160+96))+rbp]
	movdqu	xmm3,XMMWORD PTR[((0 + 0))+rsi]
	movdqu	xmm7,XMMWORD PTR[((16 + 0))+rsi]
	movdqu	xmm11,XMMWORD PTR[((32 + 0))+rsi]
	movdqu	xmm15,XMMWORD PTR[((48 + 0))+rsi]
	pxor	xmm1,xmm3
	pxor	xmm5,xmm7
	pxor	xmm9,xmm11
	pxor	xmm15,xmm13
	movdqu	XMMWORD PTR[(0 + 0)+rdi],xmm1
	movdqu	XMMWORD PTR[(16 + 0)+rdi],xmm5
	movdqu	XMMWORD PTR[(32 + 0)+rdi],xmm9
	movdqu	XMMWORD PTR[(48 + 0)+rdi],xmm15

	sub	rbx,4*16
	lea	rsi,QWORD PTR[64+rsi]
	lea	rdi,QWORD PTR[64+rdi]
	jmp	$L$open_sse_tail_64_dec_loop

$L$open_sse_tail_192::
	movdqa	xmm0,XMMWORD PTR[$L$chacha20_consts]
	movdqa	xmm4,XMMWORD PTR[((160+48))+rbp]
	movdqa	xmm8,XMMWORD PTR[((160+64))+rbp]
	movdqa	xmm1,xmm0
	movdqa	xmm5,xmm4
	movdqa	xmm9,xmm8
	movdqa	xmm2,xmm0
	movdqa	xmm6,xmm4
	movdqa	xmm10,xmm8
	movdqa	xmm14,XMMWORD PTR[((160+96))+rbp]
	paddd	xmm14,XMMWORD PTR[$L$sse_inc]
	movdqa	xmm13,xmm14
	paddd	xmm13,XMMWORD PTR[$L$sse_inc]
	movdqa	xmm12,xmm13
	paddd	xmm12,XMMWORD PTR[$L$sse_inc]
	movdqa	XMMWORD PTR[(160+96)+rbp],xmm12
	movdqa	XMMWORD PTR[(160+112)+rbp],xmm13
	movdqa	XMMWORD PTR[(160+128)+rbp],xmm14

	mov	rcx,rbx
	mov	r8,10*16
	cmp	rcx,10*16
	cmovg	rcx,r8
	and	rcx,-16
	xor	r8,r8
$L$open_sse_tail_192_rounds_and_x1hash::
	add	r10,QWORD PTR[((0+0))+r8*1+rsi]
	adc	r11,QWORD PTR[((8+0))+r8*1+rsi]
	adc	r12,1
	mov	rax,QWORD PTR[((0+160+0))+rbp]
	mov	r15,rax
	mul	r10
	mov	r13,rax
	mov	r14,rdx
	mov	rax,QWORD PTR[((0+160+0))+rbp]
	mul	r11
	imul	r15,r12
	add	r14,rax
	adc	r15,rdx
	mov	rax,QWORD PTR[((8+160+0))+rbp]
	mov	r9,rax
	mul	r10
	add	r14,rax
	adc	rdx,0
	mov	r10,rdx
	mov	rax,QWORD PTR[((8+160+0))+rbp]
	mul	r11
	add	r15,rax
	adc	rdx,0
	imul	r9,r12
	add	r15,r10
	adc	r9,rdx
	mov	r10,r13
	mov	r11,r14
	mov	r12,r15
	and	r12,3
	mov	r13,r15
	and	r13,-4
	mov	r14,r9
	shrd	r15,r9,2
	shr	r9,2
	add	r15,r13
	adc	r9,r14
	add	r10,r15
	adc	r11,r9
	adc	r12,0

$L$open_sse_tail_192_rounds::
	add	r8,16
	paddd	xmm0,xmm4
	pxor	xmm12,xmm0
	pshufb	xmm12,XMMWORD PTR[$L$rol16]
	paddd	xmm8,xmm12
	pxor	xmm4,xmm8
	movdqa	xmm3,xmm4
	pslld	xmm3,12
	psrld	xmm4,20
	pxor	xmm4,xmm3
	paddd	xmm0,xmm4
	pxor	xmm12,xmm0
	pshufb	xmm12,XMMWORD PTR[$L$rol8]
	paddd	xmm8,xmm12
	pxor	xmm4,xmm8
	movdqa	xmm3,xmm4
	pslld	xmm3,7
	psrld	xmm4,25
	pxor	xmm4,xmm3
DB	102,15,58,15,228,4
DB	102,69,15,58,15,192,8
DB	102,69,15,58,15,228,12
	paddd	xmm1,xmm5
	pxor	xmm13,xmm1
	pshufb	xmm13,XMMWORD PTR[$L$rol16]
	paddd	xmm9,xmm13
	pxor	xmm5,xmm9
	movdqa	xmm3,xmm5
	pslld	xmm3,12
	psrld	xmm5,20
	pxor	xmm5,xmm3
	paddd	xmm1,xmm5
	pxor	xmm13,xmm1
	pshufb	xmm13,XMMWORD PTR[$L$rol8]
	paddd	xmm9,xmm13
	pxor	xmm5,xmm9
	movdqa	xmm3,xmm5
	pslld	xmm3,7
	psrld	xmm5,25
	pxor	xmm5,xmm3
DB	102,15,58,15,237,4
DB	102,69,15,58,15,201,8
DB	102,69,15,58,15,237,12
	paddd	xmm2,xmm6
	pxor	xmm14,xmm2
	pshufb	xmm14,XMMWORD PTR[$L$rol16]
	paddd	xmm10,xmm14
	pxor	xmm6,xmm10
	movdqa	xmm3,xmm6
	pslld	xmm3,12
	psrld	xmm6,20
	pxor	xmm6,xmm3
	paddd	xmm2,xmm6
	pxor	xmm14,xmm2
	pshufb	xmm14,XMMWORD PTR[$L$rol8]
	paddd	xmm10,xmm14
	pxor	xmm6,xmm10
	movdqa	xmm3,xmm6
	pslld	xmm3,7
	psrld	xmm6,25
	pxor	xmm6,xmm3
DB	102,15,58,15,246,4
DB	102,69,15,58,15,210,8
DB	102,69,15,58,15,246,12
	paddd	xmm0,xmm4
	pxor	xmm12,xmm0
	pshufb	xmm12,XMMWORD PTR[$L$rol16]
	paddd	xmm8,xmm12
	pxor	xmm4,xmm8
	movdqa	xmm3,xmm4
	pslld	xmm3,12
	psrld	xmm4,20
	pxor	xmm4,xmm3
	paddd	xmm0,xmm4
	pxor	xmm12,xmm0
	pshufb	xmm12,XMMWORD PTR[$L$rol8]
	paddd	xmm8,xmm12
	pxor	xmm4,xmm8
	movdqa	xmm3,xmm4
	pslld	xmm3,7
	psrld	xmm4,25
	pxor	xmm4,xmm3
DB	102,15,58,15,228,12
DB	102,69,15,58,15,192,8
DB	102,69,15,58,15,228,4
	paddd	xmm1,xmm5
	pxor	xmm13,xmm1
	pshufb	xmm13,XMMWORD PTR[$L$rol16]
	paddd	xmm9,xmm13
	pxor	xmm5,xmm9
	movdqa	xmm3,xmm5
	pslld	xmm3,12
	psrld	xmm5,20
	pxor	xmm5,xmm3
	paddd	xmm1,xmm5
	pxor	xmm13,xmm1
	pshufb	xmm13,XMMWORD PTR[$L$rol8]
	paddd	xmm9,xmm13
	pxor	xmm5,xmm9
	movdqa	xmm3,xmm5
	pslld	xmm3,7
	psrld	xmm5,25
	pxor	xmm5,xmm3
DB	102,15,58,15,237,12
DB	102,69,15,58,15,201,8
DB	102,69,15,58,15,237,4
	paddd	xmm2,xmm6
	pxor	xmm14,xmm2
	pshufb	xmm14,XMMWORD PTR[$L$rol16]
	paddd	xmm10,xmm14
	pxor	xmm6,xmm10
	movdqa	xmm3,xmm6
	pslld	xmm3,12
	psrld	xmm6,20
	pxor	xmm6,xmm3
	paddd	xmm2,xmm6
	pxor	xmm14,xmm2
	pshufb	xmm14,XMMWORD PTR[$L$rol8]
	paddd	xmm10,xmm14
	pxor	xmm6,xmm10
	movdqa	xmm3,xmm6
	pslld	xmm3,7
	psrld	xmm6,25
	pxor	xmm6,xmm3
DB	102,15,58,15,246,12
DB	102,69,15,58,15,210,8
DB	102,69,15,58,15,246,4

	cmp	r8,rcx
	jb	$L$open_sse_tail_192_rounds_and_x1hash
	cmp	r8,10*16
	jne	$L$open_sse_tail_192_rounds
	cmp	rbx,11*16
	jb	$L$open_sse_tail_192_finish
	add	r10,QWORD PTR[((0+160))+rsi]
	adc	r11,QWORD PTR[((8+160))+rsi]
	adc	r12,1
	mov	rax,QWORD PTR[((0+160+0))+rbp]
	mov	r15,rax
	mul	r10
	mov	r13,rax
	mov	r14,rdx
	mov	rax,QWORD PTR[((0+160+0))+rbp]
	mul	r11
	imul	r15,r12
	add	r14,rax
	adc	r15,rdx
	mov	rax,QWORD PTR[((8+160+0))+rbp]
	mov	r9,rax
	mul	r10
	add	r14,rax
	adc	rdx,0
	mov	r10,rdx
	mov	rax,QWORD PTR[((8+160+0))+rbp]
	mul	r11
	add	r15,rax
	adc	rdx,0
	imul	r9,r12
	add	r15,r10
	adc	r9,rdx
	mov	r10,r13
	mov	r11,r14
	mov	r12,r15
	and	r12,3
	mov	r13,r15
	and	r13,-4
	mov	r14,r9
	shrd	r15,r9,2
	shr	r9,2
	add	r15,r13
	adc	r9,r14
	add	r10,r15
	adc	r11,r9
	adc	r12,0

	cmp	rbx,12*16
	jb	$L$open_sse_tail_192_finish
	add	r10,QWORD PTR[((0+176))+rsi]
	adc	r11,QWORD PTR[((8+176))+rsi]
	adc	r12,1
	mov	rax,QWORD PTR[((0+160+0))+rbp]
	mov	r15,rax
	mul	r10
	mov	r13,rax
	mov	r14,rdx
	mov	rax,QWORD PTR[((0+160+0))+rbp]
	mul	r11
	imul	r15,r12
	add	r14,rax
	adc	r15,rdx
	mov	rax,QWORD PTR[((8+160+0))+rbp]
	mov	r9,rax
	mul	r10
	add	r14,rax
	adc	rdx,0
	mov	r10,rdx
	mov	rax,QWORD PTR[((8+160+0))+rbp]
	mul	r11
	add	r15,rax
	adc	rdx,0
	imul	r9,r12
	add	r15,r10
	adc	r9,rdx
	mov	r10,r13
	mov	r11,r14
	mov	r12,r15
	and	r12,3
	mov	r13,r15
	and	r13,-4
	mov	r14,r9
	shrd	r15,r9,2
	shr	r9,2
	add	r15,r13
	adc	r9,r14
	add	r10,r15
	adc	r11,r9
	adc	r12,0

$L$open_sse_tail_192_finish::
	paddd	xmm2,XMMWORD PTR[$L$chacha20_consts]
	paddd	xmm6,XMMWORD PTR[((160+48))+rbp]
	paddd	xmm10,XMMWORD PTR[((160+64))+rbp]
	paddd	xmm14,XMMWORD PTR[((160+128))+rbp]
	paddd	xmm1,XMMWORD PTR[$L$chacha20_consts]
	paddd	xmm5,XMMWORD PTR[((160+48))+rbp]
	paddd	xmm9,XMMWORD PTR[((160+64))+rbp]
	paddd	xmm13,XMMWORD PTR[((160+112))+rbp]
	paddd	xmm0,XMMWORD PTR[$L$chacha20_consts]
	paddd	xmm4,XMMWORD PTR[((160+48))+rbp]
	paddd	xmm8,XMMWORD PTR[((160+64))+rbp]
	paddd	xmm12,XMMWORD PTR[((160+96))+rbp]
	movdqu	xmm3,XMMWORD PTR[((0 + 0))+rsi]
	movdqu	xmm7,XMMWORD PTR[((16 + 0))+rsi]
	movdqu	xmm11,XMMWORD PTR[((32 + 0))+rsi]
	movdqu	xmm15,XMMWORD PTR[((48 + 0))+rsi]
	pxor	xmm2,xmm3
	pxor	xmm6,xmm7
	pxor	xmm10,xmm11
	pxor	xmm15,xmm14
	movdqu	XMMWORD PTR[(0 + 0)+rdi],xmm2
	movdqu	XMMWORD PTR[(16 + 0)+rdi],xmm6
	movdqu	XMMWORD PTR[(32 + 0)+rdi],xmm10
	movdqu	XMMWORD PTR[(48 + 0)+rdi],xmm15
	movdqu	xmm3,XMMWORD PTR[((0 + 64))+rsi]
	movdqu	xmm7,XMMWORD PTR[((16 + 64))+rsi]
	movdqu	xmm11,XMMWORD PTR[((32 + 64))+rsi]
	movdqu	xmm15,XMMWORD PTR[((48 + 64))+rsi]
	pxor	xmm1,xmm3
	pxor	xmm5,xmm7
	pxor	xmm9,xmm11
	pxor	xmm15,xmm13
	movdqu	XMMWORD PTR[(0 + 64)+rdi],xmm1
	movdqu	XMMWORD PTR[(16 + 64)+rdi],xmm5
	movdqu	XMMWORD PTR[(32 + 64)+rdi],xmm9
	movdqu	XMMWORD PTR[(48 + 64)+rdi],xmm15

	sub	rbx,8*16
	lea	rsi,QWORD PTR[128+rsi]
	lea	rdi,QWORD PTR[128+rdi]
	jmp	$L$open_sse_tail_64_dec_loop

$L$open_sse_tail_256::
	movdqa	xmm0,XMMWORD PTR[$L$chacha20_consts]
	movdqa	xmm4,XMMWORD PTR[((160+48))+rbp]
	movdqa	xmm8,XMMWORD PTR[((160+64))+rbp]
	movdqa	xmm1,xmm0
	movdqa	xmm5,xmm4
	movdqa	xmm9,xmm8
	movdqa	xmm2,xmm0
	movdqa	xmm6,xmm4
	movdqa	xmm10,xmm8
	movdqa	xmm3,xmm0
	movdqa	xmm7,xmm4
	movdqa	xmm11,xmm8
	movdqa	xmm15,XMMWORD PTR[((160+96))+rbp]
	paddd	xmm15,XMMWORD PTR[$L$sse_inc]
	movdqa	xmm14,xmm15
	paddd	xmm14,XMMWORD PTR[$L$sse_inc]
	movdqa	xmm13,xmm14
	paddd	xmm13,XMMWORD PTR[$L$sse_inc]
	movdqa	xmm12,xmm13
	paddd	xmm12,XMMWORD PTR[$L$sse_inc]
	movdqa	XMMWORD PTR[(160+96)+rbp],xmm12
	movdqa	XMMWORD PTR[(160+112)+rbp],xmm13
	movdqa	XMMWORD PTR[(160+128)+rbp],xmm14
	movdqa	XMMWORD PTR[(160+144)+rbp],xmm15

	xor	r8,r8
$L$open_sse_tail_256_rounds_and_x1hash::
	add	r10,QWORD PTR[((0+0))+r8*1+rsi]
	adc	r11,QWORD PTR[((8+0))+r8*1+rsi]
	adc	r12,1
	movdqa	XMMWORD PTR[(160+80)+rbp],xmm11
	paddd	xmm0,xmm4
	pxor	xmm12,xmm0
	pshufb	xmm12,XMMWORD PTR[$L$rol16]
	paddd	xmm8,xmm12
	pxor	xmm4,xmm8
	movdqa	xmm11,xmm4
	pslld	xmm11,12
	psrld	xmm4,20
	pxor	xmm4,xmm11
	paddd	xmm0,xmm4
	pxor	xmm12,xmm0
	pshufb	xmm12,XMMWORD PTR[$L$rol8]
	paddd	xmm8,xmm12
	pxor	xmm4,xmm8
	movdqa	xmm11,xmm4
	pslld	xmm11,7
	psrld	xmm4,25
	pxor	xmm4,xmm11
DB	102,15,58,15,228,4
DB	102,69,15,58,15,192,8
DB	102,69,15,58,15,228,12
	paddd	xmm1,xmm5
	pxor	xmm13,xmm1
	pshufb	xmm13,XMMWORD PTR[$L$rol16]
	paddd	xmm9,xmm13
	pxor	xmm5,xmm9
	movdqa	xmm11,xmm5
	pslld	xmm11,12
	psrld	xmm5,20
	pxor	xmm5,xmm11
	paddd	xmm1,xmm5
	pxor	xmm13,xmm1
	pshufb	xmm13,XMMWORD PTR[$L$rol8]
	paddd	xmm9,xmm13
	pxor	xmm5,xmm9
	movdqa	xmm11,xmm5
	pslld	xmm11,7
	psrld	xmm5,25
	pxor	xmm5,xmm11
DB	102,15,58,15,237,4
DB	102,69,15,58,15,201,8
DB	102,69,15,58,15,237,12
	paddd	xmm2,xmm6
	pxor	xmm14,xmm2
	pshufb	xmm14,XMMWORD PTR[$L$rol16]
	paddd	xmm10,xmm14
	pxor	xmm6,xmm10
	movdqa	xmm11,xmm6
	pslld	xmm11,12
	psrld	xmm6,20
	pxor	xmm6,xmm11
	paddd	xmm2,xmm6
	pxor	xmm14,xmm2
	pshufb	xmm14,XMMWORD PTR[$L$rol8]
	paddd	xmm10,xmm14
	pxor	xmm6,xmm10
	movdqa	xmm11,xmm6
	pslld	xmm11,7
	psrld	xmm6,25
	pxor	xmm6,xmm11
DB	102,15,58,15,246,4
DB	102,69,15,58,15,210,8
DB	102,69,15,58,15,246,12
	movdqa	xmm11,XMMWORD PTR[((160+80))+rbp]
	mov	rax,QWORD PTR[((0+160+0))+rbp]
	mov	r15,rax
	mul	r10
	mov	r13,rax
	mov	r14,rdx
	mov	rax,QWORD PTR[((0+160+0))+rbp]
	mul	r11
	imul	r15,r12
	add	r14,rax
	adc	r15,rdx
	movdqa	XMMWORD PTR[(160+80)+rbp],xmm9
	paddd	xmm3,xmm7
	pxor	xmm15,xmm3
	pshufb	xmm15,XMMWORD PTR[$L$rol16]
	paddd	xmm11,xmm15
	pxor	xmm7,xmm11
	movdqa	xmm9,xmm7
	pslld	xmm9,12
	psrld	xmm7,20
	pxor	xmm7,xmm9
	paddd	xmm3,xmm7
	pxor	xmm15,xmm3
	pshufb	xmm15,XMMWORD PTR[$L$rol8]
	paddd	xmm11,xmm15
	pxor	xmm7,xmm11
	movdqa	xmm9,xmm7
	pslld	xmm9,7
	psrld	xmm7,25
	pxor	xmm7,xmm9
DB	102,15,58,15,255,4
DB	102,69,15,58,15,219,8
DB	102,69,15,58,15,255,12
	movdqa	xmm9,XMMWORD PTR[((160+80))+rbp]
	mov	rax,QWORD PTR[((8+160+0))+rbp]
	mov	r9,rax
	mul	r10
	add	r14,rax
	adc	rdx,0
	mov	r10,rdx
	mov	rax,QWORD PTR[((8+160+0))+rbp]
	mul	r11
	add	r15,rax
	adc	rdx,0
	movdqa	XMMWORD PTR[(160+80)+rbp],xmm11
	paddd	xmm0,xmm4
	pxor	xmm12,xmm0
	pshufb	xmm12,XMMWORD PTR[$L$rol16]
	paddd	xmm8,xmm12
	pxor	xmm4,xmm8
	movdqa	xmm11,xmm4
	pslld	xmm11,12
	psrld	xmm4,20
	pxor	xmm4,xmm11
	paddd	xmm0,xmm4
	pxor	xmm12,xmm0
	pshufb	xmm12,XMMWORD PTR[$L$rol8]
	paddd	xmm8,xmm12
	pxor	xmm4,xmm8
	movdqa	xmm11,xmm4
	pslld	xmm11,7
	psrld	xmm4,25
	pxor	xmm4,xmm11
DB	102,15,58,15,228,12
DB	102,69,15,58,15,192,8
DB	102,69,15,58,15,228,4
	paddd	xmm1,xmm5
	pxor	xmm13,xmm1
	pshufb	xmm13,XMMWORD PTR[$L$rol16]
	paddd	xmm9,xmm13
	pxor	xmm5,xmm9
	movdqa	xmm11,xmm5
	pslld	xmm11,12
	psrld	xmm5,20
	pxor	xmm5,xmm11
	paddd	xmm1,xmm5
	pxor	xmm13,xmm1
	pshufb	xmm13,XMMWORD PTR[$L$rol8]
	paddd	xmm9,xmm13
	pxor	xmm5,xmm9
	movdqa	xmm11,xmm5
	pslld	xmm11,7
	psrld	xmm5,25
	pxor	xmm5,xmm11
DB	102,15,58,15,237,12
DB	102,69,15,58,15,201,8
DB	102,69,15,58,15,237,4
	imul	r9,r12
	add	r15,r10
	adc	r9,rdx
	paddd	xmm2,xmm6
	pxor	xmm14,xmm2
	pshufb	xmm14,XMMWORD PTR[$L$rol16]
	paddd	xmm10,xmm14
	pxor	xmm6,xmm10
	movdqa	xmm11,xmm6
	pslld	xmm11,12
	psrld	xmm6,20
	pxor	xmm6,xmm11
	paddd	xmm2,xmm6
	pxor	xmm14,xmm2
	pshufb	xmm14,XMMWORD PTR[$L$rol8]
	paddd	xmm10,xmm14
	pxor	xmm6,xmm10
	movdqa	xmm11,xmm6
	pslld	xmm11,7
	psrld	xmm6,25
	pxor	xmm6,xmm11
DB	102,15,58,15,246,12
DB	102,69,15,58,15,210,8
DB	102,69,15,58,15,246,4
	movdqa	xmm11,XMMWORD PTR[((160+80))+rbp]
	mov	r10,r13
	mov	r11,r14
	mov	r12,r15
	and	r12,3
	mov	r13,r15
	and	r13,-4
	mov	r14,r9
	shrd	r15,r9,2
	shr	r9,2
	add	r15,r13
	adc	r9,r14
	add	r10,r15
	adc	r11,r9
	adc	r12,0
	movdqa	XMMWORD PTR[(160+80)+rbp],xmm9
	paddd	xmm3,xmm7
	pxor	xmm15,xmm3
	pshufb	xmm15,XMMWORD PTR[$L$rol16]
	paddd	xmm11,xmm15
	pxor	xmm7,xmm11
	movdqa	xmm9,xmm7
	pslld	xmm9,12
	psrld	xmm7,20
	pxor	xmm7,xmm9
	paddd	xmm3,xmm7
	pxor	xmm15,xmm3
	pshufb	xmm15,XMMWORD PTR[$L$rol8]
	paddd	xmm11,xmm15
	pxor	xmm7,xmm11
	movdqa	xmm9,xmm7
	pslld	xmm9,7
	psrld	xmm7,25
	pxor	xmm7,xmm9
DB	102,15,58,15,255,12
DB	102,69,15,58,15,219,8
DB	102,69,15,58,15,255,4
	movdqa	xmm9,XMMWORD PTR[((160+80))+rbp]

	add	r8,16
	cmp	r8,10*16
	jb	$L$open_sse_tail_256_rounds_and_x1hash

	mov	rcx,rbx
	and	rcx,-16
$L$open_sse_tail_256_hash::
	add	r10,QWORD PTR[((0+0))+r8*1+rsi]
	adc	r11,QWORD PTR[((8+0))+r8*1+rsi]
	adc	r12,1
	mov	rax,QWORD PTR[((0+160+0))+rbp]
	mov	r15,rax
	mul	r10
	mov	r13,rax
	mov	r14,rdx
	mov	rax,QWORD PTR[((0+160+0))+rbp]
	mul	r11
	imul	r15,r12
	add	r14,rax
	adc	r15,rdx
	mov	rax,QWORD PTR[((8+160+0))+rbp]
	mov	r9,rax
	mul	r10
	add	r14,rax
	adc	rdx,0
	mov	r10,rdx
	mov	rax,QWORD PTR[((8+160+0))+rbp]
	mul	r11
	add	r15,rax
	adc	rdx,0
	imul	r9,r12
	add	r15,r10
	adc	r9,rdx
	mov	r10,r13
	mov	r11,r14
	mov	r12,r15
	and	r12,3
	mov	r13,r15
	and	r13,-4
	mov	r14,r9
	shrd	r15,r9,2
	shr	r9,2
	add	r15,r13
	adc	r9,r14
	add	r10,r15
	adc	r11,r9
	adc	r12,0

	add	r8,16
	cmp	r8,rcx
	jb	$L$open_sse_tail_256_hash
	paddd	xmm3,XMMWORD PTR[$L$chacha20_consts]
	paddd	xmm7,XMMWORD PTR[((160+48))+rbp]
	paddd	xmm11,XMMWORD PTR[((160+64))+rbp]
	paddd	xmm15,XMMWORD PTR[((160+144))+rbp]
	paddd	xmm2,XMMWORD PTR[$L$chacha20_consts]
	paddd	xmm6,XMMWORD PTR[((160+48))+rbp]
	paddd	xmm10,XMMWORD PTR[((160+64))+rbp]
	paddd	xmm14,XMMWORD PTR[((160+128))+rbp]
	paddd	xmm1,XMMWORD PTR[$L$chacha20_consts]
	paddd	xmm5,XMMWORD PTR[((160+48))+rbp]
	paddd	xmm9,XMMWORD PTR[((160+64))+rbp]
	paddd	xmm13,XMMWORD PTR[((160+112))+rbp]
	paddd	xmm0,XMMWORD PTR[$L$chacha20_consts]
	paddd	xmm4,XMMWORD PTR[((160+48))+rbp]
	paddd	xmm8,XMMWORD PTR[((160+64))+rbp]
	paddd	xmm12,XMMWORD PTR[((160+96))+rbp]
	movdqa	XMMWORD PTR[(160+80)+rbp],xmm12
	movdqu	xmm12,XMMWORD PTR[((0 + 0))+rsi]
	pxor	xmm12,xmm3
	movdqu	XMMWORD PTR[(0 + 0)+rdi],xmm12
	movdqu	xmm12,XMMWORD PTR[((16 + 0))+rsi]
	pxor	xmm12,xmm7
	movdqu	XMMWORD PTR[(16 + 0)+rdi],xmm12
	movdqu	xmm12,XMMWORD PTR[((32 + 0))+rsi]
	pxor	xmm12,xmm11
	movdqu	XMMWORD PTR[(32 + 0)+rdi],xmm12
	movdqu	xmm12,XMMWORD PTR[((48 + 0))+rsi]
	pxor	xmm12,xmm15
	movdqu	XMMWORD PTR[(48 + 0)+rdi],xmm12
	movdqu	xmm3,XMMWORD PTR[((0 + 64))+rsi]
	movdqu	xmm7,XMMWORD PTR[((16 + 64))+rsi]
	movdqu	xmm11,XMMWORD PTR[((32 + 64))+rsi]
	movdqu	xmm15,XMMWORD PTR[((48 + 64))+rsi]
	pxor	xmm2,xmm3
	pxor	xmm6,xmm7
	pxor	xmm10,xmm11
	pxor	xmm15,xmm14
	movdqu	XMMWORD PTR[(0 + 64)+rdi],xmm2
	movdqu	XMMWORD PTR[(16 + 64)+rdi],xmm6
	movdqu	XMMWORD PTR[(32 + 64)+rdi],xmm10
	movdqu	XMMWORD PTR[(48 + 64)+rdi],xmm15
	movdqu	xmm3,XMMWORD PTR[((0 + 128))+rsi]
	movdqu	xmm7,XMMWORD PTR[((16 + 128))+rsi]
	movdqu	xmm11,XMMWORD PTR[((32 + 128))+rsi]
	movdqu	xmm15,XMMWORD PTR[((48 + 128))+rsi]
	pxor	xmm1,xmm3
	pxor	xmm5,xmm7
	pxor	xmm9,xmm11
	pxor	xmm15,xmm13
	movdqu	XMMWORD PTR[(0 + 128)+rdi],xmm1
	movdqu	XMMWORD PTR[(16 + 128)+rdi],xmm5
	movdqu	XMMWORD PTR[(32 + 128)+rdi],xmm9
	movdqu	XMMWORD PTR[(48 + 128)+rdi],xmm15

	movdqa	xmm12,XMMWORD PTR[((160+80))+rbp]
	sub	rbx,12*16
	lea	rsi,QWORD PTR[192+rsi]
	lea	rdi,QWORD PTR[192+rdi]


$L$open_sse_tail_64_dec_loop::
	cmp	rbx,16
	jb	$L$open_sse_tail_16_init
	sub	rbx,16
	movdqu	xmm3,XMMWORD PTR[rsi]
	pxor	xmm0,xmm3
	movdqu	XMMWORD PTR[rdi],xmm0
	lea	rsi,QWORD PTR[16+rsi]
	lea	rdi,QWORD PTR[16+rdi]
	movdqa	xmm0,xmm4
	movdqa	xmm4,xmm8
	movdqa	xmm8,xmm12
	jmp	$L$open_sse_tail_64_dec_loop
$L$open_sse_tail_16_init::
	movdqa	xmm1,xmm0


$L$open_sse_tail_16::
	test	rbx,rbx
	jz	$L$open_sse_finalize



	pxor	xmm3,xmm3
	lea	rsi,QWORD PTR[((-1))+rbx*1+rsi]
	mov	r8,rbx
$L$open_sse_tail_16_compose::
	pslldq	xmm3,1
	pinsrb	xmm3,BYTE PTR[rsi],0
	sub	rsi,1
	sub	r8,1
	jnz	$L$open_sse_tail_16_compose

DB	102,73,15,126,221
	pextrq	r14,xmm3,1

	pxor	xmm3,xmm1


$L$open_sse_tail_16_extract::
	pextrb	XMMWORD PTR[rdi],xmm3,0
	psrldq	xmm3,1
	add	rdi,1
	sub	rbx,1
	jne	$L$open_sse_tail_16_extract

	add	r10,r13
	adc	r11,r14
	adc	r12,1
	mov	rax,QWORD PTR[((0+160+0))+rbp]
	mov	r15,rax
	mul	r10
	mov	r13,rax
	mov	r14,rdx
	mov	rax,QWORD PTR[((0+160+0))+rbp]
	mul	r11
	imul	r15,r12
	add	r14,rax
	adc	r15,rdx
	mov	rax,QWORD PTR[((8+160+0))+rbp]
	mov	r9,rax
	mul	r10
	add	r14,rax
	adc	rdx,0
	mov	r10,rdx
	mov	rax,QWORD PTR[((8+160+0))+rbp]
	mul	r11
	add	r15,rax
	adc	rdx,0
	imul	r9,r12
	add	r15,r10
	adc	r9,rdx
	mov	r10,r13
	mov	r11,r14
	mov	r12,r15
	and	r12,3
	mov	r13,r15
	and	r13,-4
	mov	r14,r9
	shrd	r15,r9,2
	shr	r9,2
	add	r15,r13
	adc	r9,r14
	add	r10,r15
	adc	r11,r9
	adc	r12,0


$L$open_sse_finalize::
	add	r10,QWORD PTR[((0+160+32))+rbp]
	adc	r11,QWORD PTR[((8+160+32))+rbp]
	adc	r12,1
	mov	rax,QWORD PTR[((0+160+0))+rbp]
	mov	r15,rax
	mul	r10
	mov	r13,rax
	mov	r14,rdx
	mov	rax,QWORD PTR[((0+160+0))+rbp]
	mul	r11
	imul	r15,r12
	add	r14,rax
	adc	r15,rdx
	mov	rax,QWORD PTR[((8+160+0))+rbp]
	mov	r9,rax
	mul	r10
	add	r14,rax
	adc	rdx,0
	mov	r10,rdx
	mov	rax,QWORD PTR[((8+160+0))+rbp]
	mul	r11
	add	r15,rax
	adc	rdx,0
	imul	r9,r12
	add	r15,r10
	adc	r9,rdx
	mov	r10,r13
	mov	r11,r14
	mov	r12,r15
	and	r12,3
	mov	r13,r15
	and	r13,-4
	mov	r14,r9
	shrd	r15,r9,2
	shr	r9,2
	add	r15,r13
	adc	r9,r14
	add	r10,r15
	adc	r11,r9
	adc	r12,0


	mov	r13,r10
	mov	r14,r11
	mov	r15,r12
	sub	r10,-5
	sbb	r11,-1
	sbb	r12,3
	cmovc	r10,r13
	cmovc	r11,r14
	cmovc	r12,r15

	add	r10,QWORD PTR[((0+160+16))+rbp]
	adc	r11,QWORD PTR[((8+160+16))+rbp]

	movaps	xmm6,XMMWORD PTR[((0+0))+rbp]
	movaps	xmm7,XMMWORD PTR[((16+0))+rbp]
	movaps	xmm8,XMMWORD PTR[((32+0))+rbp]
	movaps	xmm9,XMMWORD PTR[((48+0))+rbp]
	movaps	xmm10,XMMWORD PTR[((64+0))+rbp]
	movaps	xmm11,XMMWORD PTR[((80+0))+rbp]
	movaps	xmm12,XMMWORD PTR[((96+0))+rbp]
	movaps	xmm13,XMMWORD PTR[((112+0))+rbp]
	movaps	xmm14,XMMWORD PTR[((128+0))+rbp]
	movaps	xmm15,XMMWORD PTR[((144+0))+rbp]


	add	rsp,288 + 160 + 32


	pop	r9

	mov	QWORD PTR[r9],r10
	mov	QWORD PTR[8+r9],r11
	pop	r15

	pop	r14

	pop	r13

	pop	r12

	pop	rbx

	pop	rbp

	mov	rdi,QWORD PTR[8+rsp]	;WIN64 epilogue
	mov	rsi,QWORD PTR[16+rsp]
	DB	0F3h,0C3h		;repret

$L$open_sse_128::

	movdqu	xmm0,XMMWORD PTR[$L$chacha20_consts]
	movdqa	xmm1,xmm0
	movdqa	xmm2,xmm0
	movdqu	xmm4,XMMWORD PTR[r9]
	movdqa	xmm5,xmm4
	movdqa	xmm6,xmm4
	movdqu	xmm8,XMMWORD PTR[16+r9]
	movdqa	xmm9,xmm8
	movdqa	xmm10,xmm8
	movdqu	xmm12,XMMWORD PTR[32+r9]
	movdqa	xmm13,xmm12
	paddd	xmm13,XMMWORD PTR[$L$sse_inc]
	movdqa	xmm14,xmm13
	paddd	xmm14,XMMWORD PTR[$L$sse_inc]
	movdqa	xmm7,xmm4
	movdqa	xmm11,xmm8
	movdqa	xmm15,xmm13
	mov	r10,10

$L$open_sse_128_rounds::
	paddd	xmm0,xmm4
	pxor	xmm12,xmm0
	pshufb	xmm12,XMMWORD PTR[$L$rol16]
	paddd	xmm8,xmm12
	pxor	xmm4,xmm8
	movdqa	xmm3,xmm4
	pslld	xmm3,12
	psrld	xmm4,20
	pxor	xmm4,xmm3
	paddd	xmm0,xmm4
	pxor	xmm12,xmm0
	pshufb	xmm12,XMMWORD PTR[$L$rol8]
	paddd	xmm8,xmm12
	pxor	xmm4,xmm8
	movdqa	xmm3,xmm4
	pslld	xmm3,7
	psrld	xmm4,25
	pxor	xmm4,xmm3
DB	102,15,58,15,228,4
DB	102,69,15,58,15,192,8
DB	102,69,15,58,15,228,12
	paddd	xmm1,xmm5
	pxor	xmm13,xmm1
	pshufb	xmm13,XMMWORD PTR[$L$rol16]
	paddd	xmm9,xmm13
	pxor	xmm5,xmm9
	movdqa	xmm3,xmm5
	pslld	xmm3,12
	psrld	xmm5,20
	pxor	xmm5,xmm3
	paddd	xmm1,xmm5
	pxor	xmm13,xmm1
	pshufb	xmm13,XMMWORD PTR[$L$rol8]
	paddd	xmm9,xmm13
	pxor	xmm5,xmm9
	movdqa	xmm3,xmm5
	pslld	xmm3,7
	psrld	xmm5,25
	pxor	xmm5,xmm3
DB	102,15,58,15,237,4
DB	102,69,15,58,15,201,8
DB	102,69,15,58,15,237,12
	paddd	xmm2,xmm6
	pxor	xmm14,xmm2
	pshufb	xmm14,XMMWORD PTR[$L$rol16]
	paddd	xmm10,xmm14
	pxor	xmm6,xmm10
	movdqa	xmm3,xmm6
	pslld	xmm3,12
	psrld	xmm6,20
	pxor	xmm6,xmm3
	paddd	xmm2,xmm6
	pxor	xmm14,xmm2
	pshufb	xmm14,XMMWORD PTR[$L$rol8]
	paddd	xmm10,xmm14
	pxor	xmm6,xmm10
	movdqa	xmm3,xmm6
	pslld	xmm3,7
	psrld	xmm6,25
	pxor	xmm6,xmm3
DB	102,15,58,15,246,4
DB	102,69,15,58,15,210,8
DB	102,69,15,58,15,246,12
	paddd	xmm0,xmm4
	pxor	xmm12,xmm0
	pshufb	xmm12,XMMWORD PTR[$L$rol16]
	paddd	xmm8,xmm12
	pxor	xmm4,xmm8
	movdqa	xmm3,xmm4
	pslld	xmm3,12
	psrld	xmm4,20
	pxor	xmm4,xmm3
	paddd	xmm0,xmm4
	pxor	xmm12,xmm0
	pshufb	xmm12,XMMWORD PTR[$L$rol8]
	paddd	xmm8,xmm12
	pxor	xmm4,xmm8
	movdqa	xmm3,xmm4
	pslld	xmm3,7
	psrld	xmm4,25
	pxor	xmm4,xmm3
DB	102,15,58,15,228,12
DB	102,69,15,58,15,192,8
DB	102,69,15,58,15,228,4
	paddd	xmm1,xmm5
	pxor	xmm13,xmm1
	pshufb	xmm13,XMMWORD PTR[$L$rol16]
	paddd	xmm9,xmm13
	pxor	xmm5,xmm9
	movdqa	xmm3,xmm5
	pslld	xmm3,12
	psrld	xmm5,20
	pxor	xmm5,xmm3
	paddd	xmm1,xmm5
	pxor	xmm13,xmm1
	pshufb	xmm13,XMMWORD PTR[$L$rol8]
	paddd	xmm9,xmm13
	pxor	xmm5,xmm9
	movdqa	xmm3,xmm5
	pslld	xmm3,7
	psrld	xmm5,25
	pxor	xmm5,xmm3
DB	102,15,58,15,237,12
DB	102,69,15,58,15,201,8
DB	102,69,15,58,15,237,4
	paddd	xmm2,xmm6
	pxor	xmm14,xmm2
	pshufb	xmm14,XMMWORD PTR[$L$rol16]
	paddd	xmm10,xmm14
	pxor	xmm6,xmm10
	movdqa	xmm3,xmm6
	pslld	xmm3,12
	psrld	xmm6,20
	pxor	xmm6,xmm3
	paddd	xmm2,xmm6
	pxor	xmm14,xmm2
	pshufb	xmm14,XMMWORD PTR[$L$rol8]
	paddd	xmm10,xmm14
	pxor	xmm6,xmm10
	movdqa	xmm3,xmm6
	pslld	xmm3,7
	psrld	xmm6,25
	pxor	xmm6,xmm3
DB	102,15,58,15,246,12
DB	102,69,15,58,15,210,8
DB	102,69,15,58,15,246,4

	dec	r10
	jnz	$L$open_sse_128_rounds
	paddd	xmm0,XMMWORD PTR[$L$chacha20_consts]
	paddd	xmm1,XMMWORD PTR[$L$chacha20_consts]
	paddd	xmm2,XMMWORD PTR[$L$chacha20_consts]
	paddd	xmm4,xmm7
	paddd	xmm5,xmm7
	paddd	xmm6,xmm7
	paddd	xmm9,xmm11
	paddd	xmm10,xmm11
	paddd	xmm13,xmm15
	paddd	xmm15,XMMWORD PTR[$L$sse_inc]
	paddd	xmm14,xmm15

	pand	xmm0,XMMWORD PTR[$L$clamp]
	movdqa	XMMWORD PTR[(160+0)+rbp],xmm0
	movdqa	XMMWORD PTR[(160+16)+rbp],xmm4

	mov	r8,r8
	call	poly_hash_ad_internal
$L$open_sse_128_xor_hash::
	cmp	rbx,16
	jb	$L$open_sse_tail_16
	sub	rbx,16
	add	r10,QWORD PTR[((0+0))+rsi]
	adc	r11,QWORD PTR[((8+0))+rsi]
	adc	r12,1


	movdqu	xmm3,XMMWORD PTR[rsi]
	pxor	xmm1,xmm3
	movdqu	XMMWORD PTR[rdi],xmm1
	lea	rsi,QWORD PTR[16+rsi]
	lea	rdi,QWORD PTR[16+rdi]
	mov	rax,QWORD PTR[((0+160+0))+rbp]
	mov	r15,rax
	mul	r10
	mov	r13,rax
	mov	r14,rdx
	mov	rax,QWORD PTR[((0+160+0))+rbp]
	mul	r11
	imul	r15,r12
	add	r14,rax
	adc	r15,rdx
	mov	rax,QWORD PTR[((8+160+0))+rbp]
	mov	r9,rax
	mul	r10
	add	r14,rax
	adc	rdx,0
	mov	r10,rdx
	mov	rax,QWORD PTR[((8+160+0))+rbp]
	mul	r11
	add	r15,rax
	adc	rdx,0
	imul	r9,r12
	add	r15,r10
	adc	r9,rdx
	mov	r10,r13
	mov	r11,r14
	mov	r12,r15
	and	r12,3
	mov	r13,r15
	and	r13,-4
	mov	r14,r9
	shrd	r15,r9,2
	shr	r9,2
	add	r15,r13
	adc	r9,r14
	add	r10,r15
	adc	r11,r9
	adc	r12,0


	movdqa	xmm1,xmm5
	movdqa	xmm5,xmm9
	movdqa	xmm9,xmm13
	movdqa	xmm13,xmm2
	movdqa	xmm2,xmm6
	movdqa	xmm6,xmm10
	movdqa	xmm10,xmm14
	jmp	$L$open_sse_128_xor_hash
$L$SEH_end_chacha20_poly1305_open::
chacha20_poly1305_open	ENDP








PUBLIC	chacha20_poly1305_seal

ALIGN	64
chacha20_poly1305_seal	PROC PUBLIC
	mov	QWORD PTR[8+rsp],rdi	;WIN64 prologue
	mov	QWORD PTR[16+rsp],rsi
	mov	rax,rsp
$L$SEH_begin_chacha20_poly1305_seal::
	mov	rdi,rcx
	mov	rsi,rdx
	mov	rdx,r8
	mov	rcx,r9
	mov	r8,QWORD PTR[40+rsp]
	mov	r9,QWORD PTR[48+rsp]



	push	rbp

	push	rbx

	push	r12

	push	r13

	push	r14

	push	r15



	push	r9

	sub	rsp,288 + 160 + 32

	lea	rbp,QWORD PTR[32+rsp]
	and	rbp,-32

	movaps	XMMWORD PTR[(0+0)+rbp],xmm6
	movaps	XMMWORD PTR[(16+0)+rbp],xmm7
	movaps	XMMWORD PTR[(32+0)+rbp],xmm8
	movaps	XMMWORD PTR[(48+0)+rbp],xmm9
	movaps	XMMWORD PTR[(64+0)+rbp],xmm10
	movaps	XMMWORD PTR[(80+0)+rbp],xmm11
	movaps	XMMWORD PTR[(96+0)+rbp],xmm12
	movaps	XMMWORD PTR[(112+0)+rbp],xmm13
	movaps	XMMWORD PTR[(128+0)+rbp],xmm14
	movaps	XMMWORD PTR[(144+0)+rbp],xmm15

	mov	rbx,QWORD PTR[56+r9]
	add	rbx,rdx
	mov	QWORD PTR[((0+160+32))+rbp],r8
	mov	QWORD PTR[((8+160+32))+rbp],rbx
	mov	rbx,rdx

	mov	eax,DWORD PTR[((OPENSSL_ia32cap_P+8))]
	and	eax,288
	xor	eax,288
	jz	chacha20_poly1305_seal_avx2

	cmp	rbx,128
	jbe	$L$seal_sse_128

	movdqa	xmm0,XMMWORD PTR[$L$chacha20_consts]
	movdqu	xmm4,XMMWORD PTR[r9]
	movdqu	xmm8,XMMWORD PTR[16+r9]
	movdqu	xmm12,XMMWORD PTR[32+r9]

	movdqa	xmm1,xmm0
	movdqa	xmm2,xmm0
	movdqa	xmm3,xmm0
	movdqa	xmm5,xmm4
	movdqa	xmm6,xmm4
	movdqa	xmm7,xmm4
	movdqa	xmm9,xmm8
	movdqa	xmm10,xmm8
	movdqa	xmm11,xmm8
	movdqa	xmm15,xmm12
	paddd	xmm12,XMMWORD PTR[$L$sse_inc]
	movdqa	xmm14,xmm12
	paddd	xmm12,XMMWORD PTR[$L$sse_inc]
	movdqa	xmm13,xmm12
	paddd	xmm12,XMMWORD PTR[$L$sse_inc]

	movdqa	XMMWORD PTR[(160+48)+rbp],xmm4
	movdqa	XMMWORD PTR[(160+64)+rbp],xmm8
	movdqa	XMMWORD PTR[(160+96)+rbp],xmm12
	movdqa	XMMWORD PTR[(160+112)+rbp],xmm13
	movdqa	XMMWORD PTR[(160+128)+rbp],xmm14
	movdqa	XMMWORD PTR[(160+144)+rbp],xmm15
	mov	r10,10
$L$seal_sse_init_rounds::
	movdqa	XMMWORD PTR[(160+80)+rbp],xmm8
	movdqa	xmm8,XMMWORD PTR[$L$rol16]
	paddd	xmm3,xmm7
	paddd	xmm2,xmm6
	paddd	xmm1,xmm5
	paddd	xmm0,xmm4
	pxor	xmm15,xmm3
	pxor	xmm14,xmm2
	pxor	xmm13,xmm1
	pxor	xmm12,xmm0
DB	102,69,15,56,0,248
DB	102,69,15,56,0,240
DB	102,69,15,56,0,232
DB	102,69,15,56,0,224
	movdqa	xmm8,XMMWORD PTR[((160+80))+rbp]
	paddd	xmm11,xmm15
	paddd	xmm10,xmm14
	paddd	xmm9,xmm13
	paddd	xmm8,xmm12
	pxor	xmm7,xmm11
	pxor	xmm6,xmm10
	pxor	xmm5,xmm9
	pxor	xmm4,xmm8
	movdqa	XMMWORD PTR[(160+80)+rbp],xmm8
	movdqa	xmm8,xmm7
	psrld	xmm8,20
	pslld	xmm7,32-20
	pxor	xmm7,xmm8
	movdqa	xmm8,xmm6
	psrld	xmm8,20
	pslld	xmm6,32-20
	pxor	xmm6,xmm8
	movdqa	xmm8,xmm5
	psrld	xmm8,20
	pslld	xmm5,32-20
	pxor	xmm5,xmm8
	movdqa	xmm8,xmm4
	psrld	xmm8,20
	pslld	xmm4,32-20
	pxor	xmm4,xmm8
	movdqa	xmm8,XMMWORD PTR[$L$rol8]
	paddd	xmm3,xmm7
	paddd	xmm2,xmm6
	paddd	xmm1,xmm5
	paddd	xmm0,xmm4
	pxor	xmm15,xmm3
	pxor	xmm14,xmm2
	pxor	xmm13,xmm1
	pxor	xmm12,xmm0
DB	102,69,15,56,0,248
DB	102,69,15,56,0,240
DB	102,69,15,56,0,232
DB	102,69,15,56,0,224
	movdqa	xmm8,XMMWORD PTR[((160+80))+rbp]
	paddd	xmm11,xmm15
	paddd	xmm10,xmm14
	paddd	xmm9,xmm13
	paddd	xmm8,xmm12
	pxor	xmm7,xmm11
	pxor	xmm6,xmm10
	pxor	xmm5,xmm9
	pxor	xmm4,xmm8
	movdqa	XMMWORD PTR[(160+80)+rbp],xmm8
	movdqa	xmm8,xmm7
	psrld	xmm8,25
	pslld	xmm7,32-25
	pxor	xmm7,xmm8
	movdqa	xmm8,xmm6
	psrld	xmm8,25
	pslld	xmm6,32-25
	pxor	xmm6,xmm8
	movdqa	xmm8,xmm5
	psrld	xmm8,25
	pslld	xmm5,32-25
	pxor	xmm5,xmm8
	movdqa	xmm8,xmm4
	psrld	xmm8,25
	pslld	xmm4,32-25
	pxor	xmm4,xmm8
	movdqa	xmm8,XMMWORD PTR[((160+80))+rbp]
DB	102,15,58,15,255,4
DB	102,69,15,58,15,219,8
DB	102,69,15,58,15,255,12
DB	102,15,58,15,246,4
DB	102,69,15,58,15,210,8
DB	102,69,15,58,15,246,12
DB	102,15,58,15,237,4
DB	102,69,15,58,15,201,8
DB	102,69,15,58,15,237,12
DB	102,15,58,15,228,4
DB	102,69,15,58,15,192,8
DB	102,69,15,58,15,228,12
	movdqa	XMMWORD PTR[(160+80)+rbp],xmm8
	movdqa	xmm8,XMMWORD PTR[$L$rol16]
	paddd	xmm3,xmm7
	paddd	xmm2,xmm6
	paddd	xmm1,xmm5
	paddd	xmm0,xmm4
	pxor	xmm15,xmm3
	pxor	xmm14,xmm2
	pxor	xmm13,xmm1
	pxor	xmm12,xmm0
DB	102,69,15,56,0,248
DB	102,69,15,56,0,240
DB	102,69,15,56,0,232
DB	102,69,15,56,0,224
	movdqa	xmm8,XMMWORD PTR[((160+80))+rbp]
	paddd	xmm11,xmm15
	paddd	xmm10,xmm14
	paddd	xmm9,xmm13
	paddd	xmm8,xmm12
	pxor	xmm7,xmm11
	pxor	xmm6,xmm10
	pxor	xmm5,xmm9
	pxor	xmm4,xmm8
	movdqa	XMMWORD PTR[(160+80)+rbp],xmm8
	movdqa	xmm8,xmm7
	psrld	xmm8,20
	pslld	xmm7,32-20
	pxor	xmm7,xmm8
	movdqa	xmm8,xmm6
	psrld	xmm8,20
	pslld	xmm6,32-20
	pxor	xmm6,xmm8
	movdqa	xmm8,xmm5
	psrld	xmm8,20
	pslld	xmm5,32-20
	pxor	xmm5,xmm8
	movdqa	xmm8,xmm4
	psrld	xmm8,20
	pslld	xmm4,32-20
	pxor	xmm4,xmm8
	movdqa	xmm8,XMMWORD PTR[$L$rol8]
	paddd	xmm3,xmm7
	paddd	xmm2,xmm6
	paddd	xmm1,xmm5
	paddd	xmm0,xmm4
	pxor	xmm15,xmm3
	pxor	xmm14,xmm2
	pxor	xmm13,xmm1
	pxor	xmm12,xmm0
DB	102,69,15,56,0,248
DB	102,69,15,56,0,240
DB	102,69,15,56,0,232
DB	102,69,15,56,0,224
	movdqa	xmm8,XMMWORD PTR[((160+80))+rbp]
	paddd	xmm11,xmm15
	paddd	xmm10,xmm14
	paddd	xmm9,xmm13
	paddd	xmm8,xmm12
	pxor	xmm7,xmm11
	pxor	xmm6,xmm10
	pxor	xmm5,xmm9
	pxor	xmm4,xmm8
	movdqa	XMMWORD PTR[(160+80)+rbp],xmm8
	movdqa	xmm8,xmm7
	psrld	xmm8,25
	pslld	xmm7,32-25
	pxor	xmm7,xmm8
	movdqa	xmm8,xmm6
	psrld	xmm8,25
	pslld	xmm6,32-25
	pxor	xmm6,xmm8
	movdqa	xmm8,xmm5
	psrld	xmm8,25
	pslld	xmm5,32-25
	pxor	xmm5,xmm8
	movdqa	xmm8,xmm4
	psrld	xmm8,25
	pslld	xmm4,32-25
	pxor	xmm4,xmm8
	movdqa	xmm8,XMMWORD PTR[((160+80))+rbp]
DB	102,15,58,15,255,12
DB	102,69,15,58,15,219,8
DB	102,69,15,58,15,255,4
DB	102,15,58,15,246,12
DB	102,69,15,58,15,210,8
DB	102,69,15,58,15,246,4
DB	102,15,58,15,237,12
DB	102,69,15,58,15,201,8
DB	102,69,15,58,15,237,4
DB	102,15,58,15,228,12
DB	102,69,15,58,15,192,8
DB	102,69,15,58,15,228,4

	dec	r10
	jnz	$L$seal_sse_init_rounds
	paddd	xmm3,XMMWORD PTR[$L$chacha20_consts]
	paddd	xmm7,XMMWORD PTR[((160+48))+rbp]
	paddd	xmm11,XMMWORD PTR[((160+64))+rbp]
	paddd	xmm15,XMMWORD PTR[((160+144))+rbp]
	paddd	xmm2,XMMWORD PTR[$L$chacha20_consts]
	paddd	xmm6,XMMWORD PTR[((160+48))+rbp]
	paddd	xmm10,XMMWORD PTR[((160+64))+rbp]
	paddd	xmm14,XMMWORD PTR[((160+128))+rbp]
	paddd	xmm1,XMMWORD PTR[$L$chacha20_consts]
	paddd	xmm5,XMMWORD PTR[((160+48))+rbp]
	paddd	xmm9,XMMWORD PTR[((160+64))+rbp]
	paddd	xmm13,XMMWORD PTR[((160+112))+rbp]
	paddd	xmm0,XMMWORD PTR[$L$chacha20_consts]
	paddd	xmm4,XMMWORD PTR[((160+48))+rbp]
	paddd	xmm8,XMMWORD PTR[((160+64))+rbp]
	paddd	xmm12,XMMWORD PTR[((160+96))+rbp]


	pand	xmm3,XMMWORD PTR[$L$clamp]
	movdqa	XMMWORD PTR[(160+0)+rbp],xmm3
	movdqa	XMMWORD PTR[(160+16)+rbp],xmm7

	mov	r8,r8
	call	poly_hash_ad_internal
	movdqu	xmm3,XMMWORD PTR[((0 + 0))+rsi]
	movdqu	xmm7,XMMWORD PTR[((16 + 0))+rsi]
	movdqu	xmm11,XMMWORD PTR[((32 + 0))+rsi]
	movdqu	xmm15,XMMWORD PTR[((48 + 0))+rsi]
	pxor	xmm2,xmm3
	pxor	xmm6,xmm7
	pxor	xmm10,xmm11
	pxor	xmm15,xmm14
	movdqu	XMMWORD PTR[(0 + 0)+rdi],xmm2
	movdqu	XMMWORD PTR[(16 + 0)+rdi],xmm6
	movdqu	XMMWORD PTR[(32 + 0)+rdi],xmm10
	movdqu	XMMWORD PTR[(48 + 0)+rdi],xmm15
	movdqu	xmm3,XMMWORD PTR[((0 + 64))+rsi]
	movdqu	xmm7,XMMWORD PTR[((16 + 64))+rsi]
	movdqu	xmm11,XMMWORD PTR[((32 + 64))+rsi]
	movdqu	xmm15,XMMWORD PTR[((48 + 64))+rsi]
	pxor	xmm1,xmm3
	pxor	xmm5,xmm7
	pxor	xmm9,xmm11
	pxor	xmm15,xmm13
	movdqu	XMMWORD PTR[(0 + 64)+rdi],xmm1
	movdqu	XMMWORD PTR[(16 + 64)+rdi],xmm5
	movdqu	XMMWORD PTR[(32 + 64)+rdi],xmm9
	movdqu	XMMWORD PTR[(48 + 64)+rdi],xmm15

	cmp	rbx,12*16
	ja	$L$seal_sse_main_init
	mov	rcx,8*16
	sub	rbx,8*16
	lea	rsi,QWORD PTR[128+rsi]
	jmp	$L$seal_sse_128_tail_hash
$L$seal_sse_main_init::
	movdqu	xmm3,XMMWORD PTR[((0 + 128))+rsi]
	movdqu	xmm7,XMMWORD PTR[((16 + 128))+rsi]
	movdqu	xmm11,XMMWORD PTR[((32 + 128))+rsi]
	movdqu	xmm15,XMMWORD PTR[((48 + 128))+rsi]
	pxor	xmm0,xmm3
	pxor	xmm4,xmm7
	pxor	xmm8,xmm11
	pxor	xmm15,xmm12
	movdqu	XMMWORD PTR[(0 + 128)+rdi],xmm0
	movdqu	XMMWORD PTR[(16 + 128)+rdi],xmm4
	movdqu	XMMWORD PTR[(32 + 128)+rdi],xmm8
	movdqu	XMMWORD PTR[(48 + 128)+rdi],xmm15

	mov	rcx,12*16
	sub	rbx,12*16
	lea	rsi,QWORD PTR[192+rsi]
	mov	rcx,2
	mov	r8,8
	cmp	rbx,4*16
	jbe	$L$seal_sse_tail_64
	cmp	rbx,8*16
	jbe	$L$seal_sse_tail_128
	cmp	rbx,12*16
	jbe	$L$seal_sse_tail_192

$L$seal_sse_main_loop::
	movdqa	xmm0,XMMWORD PTR[$L$chacha20_consts]
	movdqa	xmm4,XMMWORD PTR[((160+48))+rbp]
	movdqa	xmm8,XMMWORD PTR[((160+64))+rbp]
	movdqa	xmm1,xmm0
	movdqa	xmm5,xmm4
	movdqa	xmm9,xmm8
	movdqa	xmm2,xmm0
	movdqa	xmm6,xmm4
	movdqa	xmm10,xmm8
	movdqa	xmm3,xmm0
	movdqa	xmm7,xmm4
	movdqa	xmm11,xmm8
	movdqa	xmm15,XMMWORD PTR[((160+96))+rbp]
	paddd	xmm15,XMMWORD PTR[$L$sse_inc]
	movdqa	xmm14,xmm15
	paddd	xmm14,XMMWORD PTR[$L$sse_inc]
	movdqa	xmm13,xmm14
	paddd	xmm13,XMMWORD PTR[$L$sse_inc]
	movdqa	xmm12,xmm13
	paddd	xmm12,XMMWORD PTR[$L$sse_inc]
	movdqa	XMMWORD PTR[(160+96)+rbp],xmm12
	movdqa	XMMWORD PTR[(160+112)+rbp],xmm13
	movdqa	XMMWORD PTR[(160+128)+rbp],xmm14
	movdqa	XMMWORD PTR[(160+144)+rbp],xmm15

ALIGN	32
$L$seal_sse_main_rounds::
	movdqa	XMMWORD PTR[(160+80)+rbp],xmm8
	movdqa	xmm8,XMMWORD PTR[$L$rol16]
	paddd	xmm3,xmm7
	paddd	xmm2,xmm6
	paddd	xmm1,xmm5
	paddd	xmm0,xmm4
	pxor	xmm15,xmm3
	pxor	xmm14,xmm2
	pxor	xmm13,xmm1
	pxor	xmm12,xmm0
DB	102,69,15,56,0,248
DB	102,69,15,56,0,240
DB	102,69,15,56,0,232
DB	102,69,15,56,0,224
	movdqa	xmm8,XMMWORD PTR[((160+80))+rbp]
	paddd	xmm11,xmm15
	paddd	xmm10,xmm14
	paddd	xmm9,xmm13
	paddd	xmm8,xmm12
	pxor	xmm7,xmm11
	add	r10,QWORD PTR[((0+0))+rdi]
	adc	r11,QWORD PTR[((8+0))+rdi]
	adc	r12,1
	pxor	xmm6,xmm10
	pxor	xmm5,xmm9
	pxor	xmm4,xmm8
	movdqa	XMMWORD PTR[(160+80)+rbp],xmm8
	movdqa	xmm8,xmm7
	psrld	xmm8,20
	pslld	xmm7,32-20
	pxor	xmm7,xmm8
	movdqa	xmm8,xmm6
	psrld	xmm8,20
	pslld	xmm6,32-20
	pxor	xmm6,xmm8
	movdqa	xmm8,xmm5
	psrld	xmm8,20
	pslld	xmm5,32-20
	pxor	xmm5,xmm8
	movdqa	xmm8,xmm4
	psrld	xmm8,20
	pslld	xmm4,32-20
	pxor	xmm4,xmm8
	mov	rax,QWORD PTR[((0+160+0))+rbp]
	mov	r15,rax
	mul	r10
	mov	r13,rax
	mov	r14,rdx
	mov	rax,QWORD PTR[((0+160+0))+rbp]
	mul	r11
	imul	r15,r12
	add	r14,rax
	adc	r15,rdx
	movdqa	xmm8,XMMWORD PTR[$L$rol8]
	paddd	xmm3,xmm7
	paddd	xmm2,xmm6
	paddd	xmm1,xmm5
	paddd	xmm0,xmm4
	pxor	xmm15,xmm3
	pxor	xmm14,xmm2
	pxor	xmm13,xmm1
	pxor	xmm12,xmm0
DB	102,69,15,56,0,248
DB	102,69,15,56,0,240
DB	102,69,15,56,0,232
DB	102,69,15,56,0,224
	movdqa	xmm8,XMMWORD PTR[((160+80))+rbp]
	paddd	xmm11,xmm15
	paddd	xmm10,xmm14
	paddd	xmm9,xmm13
	paddd	xmm8,xmm12
	pxor	xmm7,xmm11
	pxor	xmm6,xmm10
	mov	rax,QWORD PTR[((8+160+0))+rbp]
	mov	r9,rax
	mul	r10
	add	r14,rax
	adc	rdx,0
	mov	r10,rdx
	mov	rax,QWORD PTR[((8+160+0))+rbp]
	mul	r11
	add	r15,rax
	adc	rdx,0
	pxor	xmm5,xmm9
	pxor	xmm4,xmm8
	movdqa	XMMWORD PTR[(160+80)+rbp],xmm8
	movdqa	xmm8,xmm7
	psrld	xmm8,25
	pslld	xmm7,32-25
	pxor	xmm7,xmm8
	movdqa	xmm8,xmm6
	psrld	xmm8,25
	pslld	xmm6,32-25
	pxor	xmm6,xmm8
	movdqa	xmm8,xmm5
	psrld	xmm8,25
	pslld	xmm5,32-25
	pxor	xmm5,xmm8
	movdqa	xmm8,xmm4
	psrld	xmm8,25
	pslld	xmm4,32-25
	pxor	xmm4,xmm8
	movdqa	xmm8,XMMWORD PTR[((160+80))+rbp]
	imul	r9,r12
	add	r15,r10
	adc	r9,rdx
DB	102,15,58,15,255,4
DB	102,69,15,58,15,219,8
DB	102,69,15,58,15,255,12
DB	102,15,58,15,246,4
DB	102,69,15,58,15,210,8
DB	102,69,15,58,15,246,12
DB	102,15,58,15,237,4
DB	102,69,15,58,15,201,8
DB	102,69,15,58,15,237,12
DB	102,15,58,15,228,4
DB	102,69,15,58,15,192,8
DB	102,69,15,58,15,228,12
	movdqa	XMMWORD PTR[(160+80)+rbp],xmm8
	movdqa	xmm8,XMMWORD PTR[$L$rol16]
	paddd	xmm3,xmm7
	paddd	xmm2,xmm6
	paddd	xmm1,xmm5
	paddd	xmm0,xmm4
	pxor	xmm15,xmm3
	pxor	xmm14,xmm2
	mov	r10,r13
	mov	r11,r14
	mov	r12,r15
	and	r12,3
	mov	r13,r15
	and	r13,-4
	mov	r14,r9
	shrd	r15,r9,2
	shr	r9,2
	add	r15,r13
	adc	r9,r14
	add	r10,r15
	adc	r11,r9
	adc	r12,0
	pxor	xmm13,xmm1
	pxor	xmm12,xmm0
DB	102,69,15,56,0,248
DB	102,69,15,56,0,240
DB	102,69,15,56,0,232
DB	102,69,15,56,0,224
	movdqa	xmm8,XMMWORD PTR[((160+80))+rbp]
	paddd	xmm11,xmm15
	paddd	xmm10,xmm14
	paddd	xmm9,xmm13
	paddd	xmm8,xmm12
	pxor	xmm7,xmm11
	pxor	xmm6,xmm10
	pxor	xmm5,xmm9
	pxor	xmm4,xmm8
	movdqa	XMMWORD PTR[(160+80)+rbp],xmm8
	movdqa	xmm8,xmm7
	psrld	xmm8,20
	pslld	xmm7,32-20
	pxor	xmm7,xmm8
	movdqa	xmm8,xmm6
	psrld	xmm8,20
	pslld	xmm6,32-20
	pxor	xmm6,xmm8
	movdqa	xmm8,xmm5
	psrld	xmm8,20
	pslld	xmm5,32-20
	pxor	xmm5,xmm8
	movdqa	xmm8,xmm4
	psrld	xmm8,20
	pslld	xmm4,32-20
	pxor	xmm4,xmm8
	movdqa	xmm8,XMMWORD PTR[$L$rol8]
	paddd	xmm3,xmm7
	paddd	xmm2,xmm6
	paddd	xmm1,xmm5
	paddd	xmm0,xmm4
	pxor	xmm15,xmm3
	pxor	xmm14,xmm2
	pxor	xmm13,xmm1
	pxor	xmm12,xmm0
DB	102,69,15,56,0,248
DB	102,69,15,56,0,240
DB	102,69,15,56,0,232
DB	102,69,15,56,0,224
	movdqa	xmm8,XMMWORD PTR[((160+80))+rbp]
	paddd	xmm11,xmm15
	paddd	xmm10,xmm14
	paddd	xmm9,xmm13
	paddd	xmm8,xmm12
	pxor	xmm7,xmm11
	pxor	xmm6,xmm10
	pxor	xmm5,xmm9
	pxor	xmm4,xmm8
	movdqa	XMMWORD PTR[(160+80)+rbp],xmm8
	movdqa	xmm8,xmm7
	psrld	xmm8,25
	pslld	xmm7,32-25
	pxor	xmm7,xmm8
	movdqa	xmm8,xmm6
	psrld	xmm8,25
	pslld	xmm6,32-25
	pxor	xmm6,xmm8
	movdqa	xmm8,xmm5
	psrld	xmm8,25
	pslld	xmm5,32-25
	pxor	xmm5,xmm8
	movdqa	xmm8,xmm4
	psrld	xmm8,25
	pslld	xmm4,32-25
	pxor	xmm4,xmm8
	movdqa	xmm8,XMMWORD PTR[((160+80))+rbp]
DB	102,15,58,15,255,12
DB	102,69,15,58,15,219,8
DB	102,69,15,58,15,255,4
DB	102,15,58,15,246,12
DB	102,69,15,58,15,210,8
DB	102,69,15,58,15,246,4
DB	102,15,58,15,237,12
DB	102,69,15,58,15,201,8
DB	102,69,15,58,15,237,4
DB	102,15,58,15,228,12
DB	102,69,15,58,15,192,8
DB	102,69,15,58,15,228,4

	lea	rdi,QWORD PTR[16+rdi]
	dec	r8
	jge	$L$seal_sse_main_rounds
	add	r10,QWORD PTR[((0+0))+rdi]
	adc	r11,QWORD PTR[((8+0))+rdi]
	adc	r12,1
	mov	rax,QWORD PTR[((0+160+0))+rbp]
	mov	r15,rax
	mul	r10
	mov	r13,rax
	mov	r14,rdx
	mov	rax,QWORD PTR[((0+160+0))+rbp]
	mul	r11
	imul	r15,r12
	add	r14,rax
	adc	r15,rdx
	mov	rax,QWORD PTR[((8+160+0))+rbp]
	mov	r9,rax
	mul	r10
	add	r14,rax
	adc	rdx,0
	mov	r10,rdx
	mov	rax,QWORD PTR[((8+160+0))+rbp]
	mul	r11
	add	r15,rax
	adc	rdx,0
	imul	r9,r12
	add	r15,r10
	adc	r9,rdx
	mov	r10,r13
	mov	r11,r14
	mov	r12,r15
	and	r12,3
	mov	r13,r15
	and	r13,-4
	mov	r14,r9
	shrd	r15,r9,2
	shr	r9,2
	add	r15,r13
	adc	r9,r14
	add	r10,r15
	adc	r11,r9
	adc	r12,0

	lea	rdi,QWORD PTR[16+rdi]
	dec	rcx
	jg	$L$seal_sse_main_rounds
	paddd	xmm3,XMMWORD PTR[$L$chacha20_consts]
	paddd	xmm7,XMMWORD PTR[((160+48))+rbp]
	paddd	xmm11,XMMWORD PTR[((160+64))+rbp]
	paddd	xmm15,XMMWORD PTR[((160+144))+rbp]
	paddd	xmm2,XMMWORD PTR[$L$chacha20_consts]
	paddd	xmm6,XMMWORD PTR[((160+48))+rbp]
	paddd	xmm10,XMMWORD PTR[((160+64))+rbp]
	paddd	xmm14,XMMWORD PTR[((160+128))+rbp]
	paddd	xmm1,XMMWORD PTR[$L$chacha20_consts]
	paddd	xmm5,XMMWORD PTR[((160+48))+rbp]
	paddd	xmm9,XMMWORD PTR[((160+64))+rbp]
	paddd	xmm13,XMMWORD PTR[((160+112))+rbp]
	paddd	xmm0,XMMWORD PTR[$L$chacha20_consts]
	paddd	xmm4,XMMWORD PTR[((160+48))+rbp]
	paddd	xmm8,XMMWORD PTR[((160+64))+rbp]
	paddd	xmm12,XMMWORD PTR[((160+96))+rbp]

	movdqa	XMMWORD PTR[(160+80)+rbp],xmm14
	movdqa	XMMWORD PTR[(160+80)+rbp],xmm14
	movdqu	xmm14,XMMWORD PTR[((0 + 0))+rsi]
	pxor	xmm14,xmm3
	movdqu	XMMWORD PTR[(0 + 0)+rdi],xmm14
	movdqu	xmm14,XMMWORD PTR[((16 + 0))+rsi]
	pxor	xmm14,xmm7
	movdqu	XMMWORD PTR[(16 + 0)+rdi],xmm14
	movdqu	xmm14,XMMWORD PTR[((32 + 0))+rsi]
	pxor	xmm14,xmm11
	movdqu	XMMWORD PTR[(32 + 0)+rdi],xmm14
	movdqu	xmm14,XMMWORD PTR[((48 + 0))+rsi]
	pxor	xmm14,xmm15
	movdqu	XMMWORD PTR[(48 + 0)+rdi],xmm14

	movdqa	xmm14,XMMWORD PTR[((160+80))+rbp]
	movdqu	xmm3,XMMWORD PTR[((0 + 64))+rsi]
	movdqu	xmm7,XMMWORD PTR[((16 + 64))+rsi]
	movdqu	xmm11,XMMWORD PTR[((32 + 64))+rsi]
	movdqu	xmm15,XMMWORD PTR[((48 + 64))+rsi]
	pxor	xmm2,xmm3
	pxor	xmm6,xmm7
	pxor	xmm10,xmm11
	pxor	xmm15,xmm14
	movdqu	XMMWORD PTR[(0 + 64)+rdi],xmm2
	movdqu	XMMWORD PTR[(16 + 64)+rdi],xmm6
	movdqu	XMMWORD PTR[(32 + 64)+rdi],xmm10
	movdqu	XMMWORD PTR[(48 + 64)+rdi],xmm15
	movdqu	xmm3,XMMWORD PTR[((0 + 128))+rsi]
	movdqu	xmm7,XMMWORD PTR[((16 + 128))+rsi]
	movdqu	xmm11,XMMWORD PTR[((32 + 128))+rsi]
	movdqu	xmm15,XMMWORD PTR[((48 + 128))+rsi]
	pxor	xmm1,xmm3
	pxor	xmm5,xmm7
	pxor	xmm9,xmm11
	pxor	xmm15,xmm13
	movdqu	XMMWORD PTR[(0 + 128)+rdi],xmm1
	movdqu	XMMWORD PTR[(16 + 128)+rdi],xmm5
	movdqu	XMMWORD PTR[(32 + 128)+rdi],xmm9
	movdqu	XMMWORD PTR[(48 + 128)+rdi],xmm15

	cmp	rbx,16*16
	ja	$L$seal_sse_main_loop_xor

	mov	rcx,12*16
	sub	rbx,12*16
	lea	rsi,QWORD PTR[192+rsi]
	jmp	$L$seal_sse_128_tail_hash
$L$seal_sse_main_loop_xor::
	movdqu	xmm3,XMMWORD PTR[((0 + 192))+rsi]
	movdqu	xmm7,XMMWORD PTR[((16 + 192))+rsi]
	movdqu	xmm11,XMMWORD PTR[((32 + 192))+rsi]
	movdqu	xmm15,XMMWORD PTR[((48 + 192))+rsi]
	pxor	xmm0,xmm3
	pxor	xmm4,xmm7
	pxor	xmm8,xmm11
	pxor	xmm15,xmm12
	movdqu	XMMWORD PTR[(0 + 192)+rdi],xmm0
	movdqu	XMMWORD PTR[(16 + 192)+rdi],xmm4
	movdqu	XMMWORD PTR[(32 + 192)+rdi],xmm8
	movdqu	XMMWORD PTR[(48 + 192)+rdi],xmm15

	lea	rsi,QWORD PTR[256+rsi]
	sub	rbx,16*16
	mov	rcx,6
	mov	r8,4
	cmp	rbx,12*16
	jg	$L$seal_sse_main_loop
	mov	rcx,rbx
	test	rbx,rbx
	je	$L$seal_sse_128_tail_hash
	mov	rcx,6
	cmp	rbx,8*16
	ja	$L$seal_sse_tail_192
	cmp	rbx,4*16
	ja	$L$seal_sse_tail_128

$L$seal_sse_tail_64::
	movdqa	xmm0,XMMWORD PTR[$L$chacha20_consts]
	movdqa	xmm4,XMMWORD PTR[((160+48))+rbp]
	movdqa	xmm8,XMMWORD PTR[((160+64))+rbp]
	movdqa	xmm12,XMMWORD PTR[((160+96))+rbp]
	paddd	xmm12,XMMWORD PTR[$L$sse_inc]
	movdqa	XMMWORD PTR[(160+96)+rbp],xmm12

$L$seal_sse_tail_64_rounds_and_x2hash::
	add	r10,QWORD PTR[((0+0))+rdi]
	adc	r11,QWORD PTR[((8+0))+rdi]
	adc	r12,1
	mov	rax,QWORD PTR[((0+160+0))+rbp]
	mov	r15,rax
	mul	r10
	mov	r13,rax
	mov	r14,rdx
	mov	rax,QWORD PTR[((0+160+0))+rbp]
	mul	r11
	imul	r15,r12
	add	r14,rax
	adc	r15,rdx
	mov	rax,QWORD PTR[((8+160+0))+rbp]
	mov	r9,rax
	mul	r10
	add	r14,rax
	adc	rdx,0
	mov	r10,rdx
	mov	rax,QWORD PTR[((8+160+0))+rbp]
	mul	r11
	add	r15,rax
	adc	rdx,0
	imul	r9,r12
	add	r15,r10
	adc	r9,rdx
	mov	r10,r13
	mov	r11,r14
	mov	r12,r15
	and	r12,3
	mov	r13,r15
	and	r13,-4
	mov	r14,r9
	shrd	r15,r9,2
	shr	r9,2
	add	r15,r13
	adc	r9,r14
	add	r10,r15
	adc	r11,r9
	adc	r12,0

	lea	rdi,QWORD PTR[16+rdi]
$L$seal_sse_tail_64_rounds_and_x1hash::
	paddd	xmm0,xmm4
	pxor	xmm12,xmm0
	pshufb	xmm12,XMMWORD PTR[$L$rol16]
	paddd	xmm8,xmm12
	pxor	xmm4,xmm8
	movdqa	xmm3,xmm4
	pslld	xmm3,12
	psrld	xmm4,20
	pxor	xmm4,xmm3
	paddd	xmm0,xmm4
	pxor	xmm12,xmm0
	pshufb	xmm12,XMMWORD PTR[$L$rol8]
	paddd	xmm8,xmm12
	pxor	xmm4,xmm8
	movdqa	xmm3,xmm4
	pslld	xmm3,7
	psrld	xmm4,25
	pxor	xmm4,xmm3
DB	102,15,58,15,228,4
DB	102,69,15,58,15,192,8
DB	102,69,15,58,15,228,12
	paddd	xmm0,xmm4
	pxor	xmm12,xmm0
	pshufb	xmm12,XMMWORD PTR[$L$rol16]
	paddd	xmm8,xmm12
	pxor	xmm4,xmm8
	movdqa	xmm3,xmm4
	pslld	xmm3,12
	psrld	xmm4,20
	pxor	xmm4,xmm3
	paddd	xmm0,xmm4
	pxor	xmm12,xmm0
	pshufb	xmm12,XMMWORD PTR[$L$rol8]
	paddd	xmm8,xmm12
	pxor	xmm4,xmm8
	movdqa	xmm3,xmm4
	pslld	xmm3,7
	psrld	xmm4,25
	pxor	xmm4,xmm3
DB	102,15,58,15,228,12
DB	102,69,15,58,15,192,8
DB	102,69,15,58,15,228,4
	add	r10,QWORD PTR[((0+0))+rdi]
	adc	r11,QWORD PTR[((8+0))+rdi]
	adc	r12,1
	mov	rax,QWORD PTR[((0+160+0))+rbp]
	mov	r15,rax
	mul	r10
	mov	r13,rax
	mov	r14,rdx
	mov	rax,QWORD PTR[((0+160+0))+rbp]
	mul	r11
	imul	r15,r12
	add	r14,rax
	adc	r15,rdx
	mov	rax,QWORD PTR[((8+160+0))+rbp]
	mov	r9,rax
	mul	r10
	add	r14,rax
	adc	rdx,0
	mov	r10,rdx
	mov	rax,QWORD PTR[((8+160+0))+rbp]
	mul	r11
	add	r15,rax
	adc	rdx,0
	imul	r9,r12
	add	r15,r10
	adc	r9,rdx
	mov	r10,r13
	mov	r11,r14
	mov	r12,r15
	and	r12,3
	mov	r13,r15
	and	r13,-4
	mov	r14,r9
	shrd	r15,r9,2
	shr	r9,2
	add	r15,r13
	adc	r9,r14
	add	r10,r15
	adc	r11,r9
	adc	r12,0

	lea	rdi,QWORD PTR[16+rdi]
	dec	rcx
	jg	$L$seal_sse_tail_64_rounds_and_x2hash
	dec	r8
	jge	$L$seal_sse_tail_64_rounds_and_x1hash
	paddd	xmm0,XMMWORD PTR[$L$chacha20_consts]
	paddd	xmm4,XMMWORD PTR[((160+48))+rbp]
	paddd	xmm8,XMMWORD PTR[((160+64))+rbp]
	paddd	xmm12,XMMWORD PTR[((160+96))+rbp]

	jmp	$L$seal_sse_128_tail_xor

$L$seal_sse_tail_128::
	movdqa	xmm0,XMMWORD PTR[$L$chacha20_consts]
	movdqa	xmm4,XMMWORD PTR[((160+48))+rbp]
	movdqa	xmm8,XMMWORD PTR[((160+64))+rbp]
	movdqa	xmm1,xmm0
	movdqa	xmm5,xmm4
	movdqa	xmm9,xmm8
	movdqa	xmm13,XMMWORD PTR[((160+96))+rbp]
	paddd	xmm13,XMMWORD PTR[$L$sse_inc]
	movdqa	xmm12,xmm13
	paddd	xmm12,XMMWORD PTR[$L$sse_inc]
	movdqa	XMMWORD PTR[(160+96)+rbp],xmm12
	movdqa	XMMWORD PTR[(160+112)+rbp],xmm13

$L$seal_sse_tail_128_rounds_and_x2hash::
	add	r10,QWORD PTR[((0+0))+rdi]
	adc	r11,QWORD PTR[((8+0))+rdi]
	adc	r12,1
	mov	rax,QWORD PTR[((0+160+0))+rbp]
	mov	r15,rax
	mul	r10
	mov	r13,rax
	mov	r14,rdx
	mov	rax,QWORD PTR[((0+160+0))+rbp]
	mul	r11
	imul	r15,r12
	add	r14,rax
	adc	r15,rdx
	mov	rax,QWORD PTR[((8+160+0))+rbp]
	mov	r9,rax
	mul	r10
	add	r14,rax
	adc	rdx,0
	mov	r10,rdx
	mov	rax,QWORD PTR[((8+160+0))+rbp]
	mul	r11
	add	r15,rax
	adc	rdx,0
	imul	r9,r12
	add	r15,r10
	adc	r9,rdx
	mov	r10,r13
	mov	r11,r14
	mov	r12,r15
	and	r12,3
	mov	r13,r15
	and	r13,-4
	mov	r14,r9
	shrd	r15,r9,2
	shr	r9,2
	add	r15,r13
	adc	r9,r14
	add	r10,r15
	adc	r11,r9
	adc	r12,0

	lea	rdi,QWORD PTR[16+rdi]
$L$seal_sse_tail_128_rounds_and_x1hash::
	paddd	xmm0,xmm4
	pxor	xmm12,xmm0
	pshufb	xmm12,XMMWORD PTR[$L$rol16]
	paddd	xmm8,xmm12
	pxor	xmm4,xmm8
	movdqa	xmm3,xmm4
	pslld	xmm3,12
	psrld	xmm4,20
	pxor	xmm4,xmm3
	paddd	xmm0,xmm4
	pxor	xmm12,xmm0
	pshufb	xmm12,XMMWORD PTR[$L$rol8]
	paddd	xmm8,xmm12
	pxor	xmm4,xmm8
	movdqa	xmm3,xmm4
	pslld	xmm3,7
	psrld	xmm4,25
	pxor	xmm4,xmm3
DB	102,15,58,15,228,4
DB	102,69,15,58,15,192,8
DB	102,69,15,58,15,228,12
	paddd	xmm1,xmm5
	pxor	xmm13,xmm1
	pshufb	xmm13,XMMWORD PTR[$L$rol16]
	paddd	xmm9,xmm13
	pxor	xmm5,xmm9
	movdqa	xmm3,xmm5
	pslld	xmm3,12
	psrld	xmm5,20
	pxor	xmm5,xmm3
	paddd	xmm1,xmm5
	pxor	xmm13,xmm1
	pshufb	xmm13,XMMWORD PTR[$L$rol8]
	paddd	xmm9,xmm13
	pxor	xmm5,xmm9
	movdqa	xmm3,xmm5
	pslld	xmm3,7
	psrld	xmm5,25
	pxor	xmm5,xmm3
DB	102,15,58,15,237,4
DB	102,69,15,58,15,201,8
DB	102,69,15,58,15,237,12
	add	r10,QWORD PTR[((0+0))+rdi]
	adc	r11,QWORD PTR[((8+0))+rdi]
	adc	r12,1
	mov	rax,QWORD PTR[((0+160+0))+rbp]
	mov	r15,rax
	mul	r10
	mov	r13,rax
	mov	r14,rdx
	mov	rax,QWORD PTR[((0+160+0))+rbp]
	mul	r11
	imul	r15,r12
	add	r14,rax
	adc	r15,rdx
	mov	rax,QWORD PTR[((8+160+0))+rbp]
	mov	r9,rax
	mul	r10
	add	r14,rax
	adc	rdx,0
	mov	r10,rdx
	mov	rax,QWORD PTR[((8+160+0))+rbp]
	mul	r11
	add	r15,rax
	adc	rdx,0
	imul	r9,r12
	add	r15,r10
	adc	r9,rdx
	mov	r10,r13
	mov	r11,r14
	mov	r12,r15
	and	r12,3
	mov	r13,r15
	and	r13,-4
	mov	r14,r9
	shrd	r15,r9,2
	shr	r9,2
	add	r15,r13
	adc	r9,r14
	add	r10,r15
	adc	r11,r9
	adc	r12,0
	paddd	xmm0,xmm4
	pxor	xmm12,xmm0
	pshufb	xmm12,XMMWORD PTR[$L$rol16]
	paddd	xmm8,xmm12
	pxor	xmm4,xmm8
	movdqa	xmm3,xmm4
	pslld	xmm3,12
	psrld	xmm4,20
	pxor	xmm4,xmm3
	paddd	xmm0,xmm4
	pxor	xmm12,xmm0
	pshufb	xmm12,XMMWORD PTR[$L$rol8]
	paddd	xmm8,xmm12
	pxor	xmm4,xmm8
	movdqa	xmm3,xmm4
	pslld	xmm3,7
	psrld	xmm4,25
	pxor	xmm4,xmm3
DB	102,15,58,15,228,12
DB	102,69,15,58,15,192,8
DB	102,69,15,58,15,228,4
	paddd	xmm1,xmm5
	pxor	xmm13,xmm1
	pshufb	xmm13,XMMWORD PTR[$L$rol16]
	paddd	xmm9,xmm13
	pxor	xmm5,xmm9
	movdqa	xmm3,xmm5
	pslld	xmm3,12
	psrld	xmm5,20
	pxor	xmm5,xmm3
	paddd	xmm1,xmm5
	pxor	xmm13,xmm1
	pshufb	xmm13,XMMWORD PTR[$L$rol8]
	paddd	xmm9,xmm13
	pxor	xmm5,xmm9
	movdqa	xmm3,xmm5
	pslld	xmm3,7
	psrld	xmm5,25
	pxor	xmm5,xmm3
DB	102,15,58,15,237,12
DB	102,69,15,58,15,201,8
DB	102,69,15,58,15,237,4

	lea	rdi,QWORD PTR[16+rdi]
	dec	rcx
	jg	$L$seal_sse_tail_128_rounds_and_x2hash
	dec	r8
	jge	$L$seal_sse_tail_128_rounds_and_x1hash
	paddd	xmm1,XMMWORD PTR[$L$chacha20_consts]
	paddd	xmm5,XMMWORD PTR[((160+48))+rbp]
	paddd	xmm9,XMMWORD PTR[((160+64))+rbp]
	paddd	xmm13,XMMWORD PTR[((160+112))+rbp]
	paddd	xmm0,XMMWORD PTR[$L$chacha20_consts]
	paddd	xmm4,XMMWORD PTR[((160+48))+rbp]
	paddd	xmm8,XMMWORD PTR[((160+64))+rbp]
	paddd	xmm12,XMMWORD PTR[((160+96))+rbp]
	movdqu	xmm3,XMMWORD PTR[((0 + 0))+rsi]
	movdqu	xmm7,XMMWORD PTR[((16 + 0))+rsi]
	movdqu	xmm11,XMMWORD PTR[((32 + 0))+rsi]
	movdqu	xmm15,XMMWORD PTR[((48 + 0))+rsi]
	pxor	xmm1,xmm3
	pxor	xmm5,xmm7
	pxor	xmm9,xmm11
	pxor	xmm15,xmm13
	movdqu	XMMWORD PTR[(0 + 0)+rdi],xmm1
	movdqu	XMMWORD PTR[(16 + 0)+rdi],xmm5
	movdqu	XMMWORD PTR[(32 + 0)+rdi],xmm9
	movdqu	XMMWORD PTR[(48 + 0)+rdi],xmm15

	mov	rcx,4*16
	sub	rbx,4*16
	lea	rsi,QWORD PTR[64+rsi]
	jmp	$L$seal_sse_128_tail_hash

$L$seal_sse_tail_192::
	movdqa	xmm0,XMMWORD PTR[$L$chacha20_consts]
	movdqa	xmm4,XMMWORD PTR[((160+48))+rbp]
	movdqa	xmm8,XMMWORD PTR[((160+64))+rbp]
	movdqa	xmm1,xmm0
	movdqa	xmm5,xmm4
	movdqa	xmm9,xmm8
	movdqa	xmm2,xmm0
	movdqa	xmm6,xmm4
	movdqa	xmm10,xmm8
	movdqa	xmm14,XMMWORD PTR[((160+96))+rbp]
	paddd	xmm14,XMMWORD PTR[$L$sse_inc]
	movdqa	xmm13,xmm14
	paddd	xmm13,XMMWORD PTR[$L$sse_inc]
	movdqa	xmm12,xmm13
	paddd	xmm12,XMMWORD PTR[$L$sse_inc]
	movdqa	XMMWORD PTR[(160+96)+rbp],xmm12
	movdqa	XMMWORD PTR[(160+112)+rbp],xmm13
	movdqa	XMMWORD PTR[(160+128)+rbp],xmm14

$L$seal_sse_tail_192_rounds_and_x2hash::
	add	r10,QWORD PTR[((0+0))+rdi]
	adc	r11,QWORD PTR[((8+0))+rdi]
	adc	r12,1
	mov	rax,QWORD PTR[((0+160+0))+rbp]
	mov	r15,rax
	mul	r10
	mov	r13,rax
	mov	r14,rdx
	mov	rax,QWORD PTR[((0+160+0))+rbp]
	mul	r11
	imul	r15,r12
	add	r14,rax
	adc	r15,rdx
	mov	rax,QWORD PTR[((8+160+0))+rbp]
	mov	r9,rax
	mul	r10
	add	r14,rax
	adc	rdx,0
	mov	r10,rdx
	mov	rax,QWORD PTR[((8+160+0))+rbp]
	mul	r11
	add	r15,rax
	adc	rdx,0
	imul	r9,r12
	add	r15,r10
	adc	r9,rdx
	mov	r10,r13
	mov	r11,r14
	mov	r12,r15
	and	r12,3
	mov	r13,r15
	and	r13,-4
	mov	r14,r9
	shrd	r15,r9,2
	shr	r9,2
	add	r15,r13
	adc	r9,r14
	add	r10,r15
	adc	r11,r9
	adc	r12,0

	lea	rdi,QWORD PTR[16+rdi]
$L$seal_sse_tail_192_rounds_and_x1hash::
	paddd	xmm0,xmm4
	pxor	xmm12,xmm0
	pshufb	xmm12,XMMWORD PTR[$L$rol16]
	paddd	xmm8,xmm12
	pxor	xmm4,xmm8
	movdqa	xmm3,xmm4
	pslld	xmm3,12
	psrld	xmm4,20
	pxor	xmm4,xmm3
	paddd	xmm0,xmm4
	pxor	xmm12,xmm0
	pshufb	xmm12,XMMWORD PTR[$L$rol8]
	paddd	xmm8,xmm12
	pxor	xmm4,xmm8
	movdqa	xmm3,xmm4
	pslld	xmm3,7
	psrld	xmm4,25
	pxor	xmm4,xmm3
DB	102,15,58,15,228,4
DB	102,69,15,58,15,192,8
DB	102,69,15,58,15,228,12
	paddd	xmm1,xmm5
	pxor	xmm13,xmm1
	pshufb	xmm13,XMMWORD PTR[$L$rol16]
	paddd	xmm9,xmm13
	pxor	xmm5,xmm9
	movdqa	xmm3,xmm5
	pslld	xmm3,12
	psrld	xmm5,20
	pxor	xmm5,xmm3
	paddd	xmm1,xmm5
	pxor	xmm13,xmm1
	pshufb	xmm13,XMMWORD PTR[$L$rol8]
	paddd	xmm9,xmm13
	pxor	xmm5,xmm9
	movdqa	xmm3,xmm5
	pslld	xmm3,7
	psrld	xmm5,25
	pxor	xmm5,xmm3
DB	102,15,58,15,237,4
DB	102,69,15,58,15,201,8
DB	102,69,15,58,15,237,12
	paddd	xmm2,xmm6
	pxor	xmm14,xmm2
	pshufb	xmm14,XMMWORD PTR[$L$rol16]
	paddd	xmm10,xmm14
	pxor	xmm6,xmm10
	movdqa	xmm3,xmm6
	pslld	xmm3,12
	psrld	xmm6,20
	pxor	xmm6,xmm3
	paddd	xmm2,xmm6
	pxor	xmm14,xmm2
	pshufb	xmm14,XMMWORD PTR[$L$rol8]
	paddd	xmm10,xmm14
	pxor	xmm6,xmm10
	movdqa	xmm3,xmm6
	pslld	xmm3,7
	psrld	xmm6,25
	pxor	xmm6,xmm3
DB	102,15,58,15,246,4
DB	102,69,15,58,15,210,8
DB	102,69,15,58,15,246,12
	add	r10,QWORD PTR[((0+0))+rdi]
	adc	r11,QWORD PTR[((8+0))+rdi]
	adc	r12,1
	mov	rax,QWORD PTR[((0+160+0))+rbp]
	mov	r15,rax
	mul	r10
	mov	r13,rax
	mov	r14,rdx
	mov	rax,QWORD PTR[((0+160+0))+rbp]
	mul	r11
	imul	r15,r12
	add	r14,rax
	adc	r15,rdx
	mov	rax,QWORD PTR[((8+160+0))+rbp]
	mov	r9,rax
	mul	r10
	add	r14,rax
	adc	rdx,0
	mov	r10,rdx
	mov	rax,QWORD PTR[((8+160+0))+rbp]
	mul	r11
	add	r15,rax
	adc	rdx,0
	imul	r9,r12
	add	r15,r10
	adc	r9,rdx
	mov	r10,r13
	mov	r11,r14
	mov	r12,r15
	and	r12,3
	mov	r13,r15
	and	r13,-4
	mov	r14,r9
	shrd	r15,r9,2
	shr	r9,2
	add	r15,r13
	adc	r9,r14
	add	r10,r15
	adc	r11,r9
	adc	r12,0
	paddd	xmm0,xmm4
	pxor	xmm12,xmm0
	pshufb	xmm12,XMMWORD PTR[$L$rol16]
	paddd	xmm8,xmm12
	pxor	xmm4,xmm8
	movdqa	xmm3,xmm4
	pslld	xmm3,12
	psrld	xmm4,20
	pxor	xmm4,xmm3
	paddd	xmm0,xmm4
	pxor	xmm12,xmm0
	pshufb	xmm12,XMMWORD PTR[$L$rol8]
	paddd	xmm8,xmm12
	pxor	xmm4,xmm8
	movdqa	xmm3,xmm4
	pslld	xmm3,7
	psrld	xmm4,25
	pxor	xmm4,xmm3
DB	102,15,58,15,228,12
DB	102,69,15,58,15,192,8
DB	102,69,15,58,15,228,4
	paddd	xmm1,xmm5
	pxor	xmm13,xmm1
	pshufb	xmm13,XMMWORD PTR[$L$rol16]
	paddd	xmm9,xmm13
	pxor	xmm5,xmm9
	movdqa	xmm3,xmm5
	pslld	xmm3,12
	psrld	xmm5,20
	pxor	xmm5,xmm3
	paddd	xmm1,xmm5
	pxor	xmm13,xmm1
	pshufb	xmm13,XMMWORD PTR[$L$rol8]
	paddd	xmm9,xmm13
	pxor	xmm5,xmm9
	movdqa	xmm3,xmm5
	pslld	xmm3,7
	psrld	xmm5,25
	pxor	xmm5,xmm3
DB	102,15,58,15,237,12
DB	102,69,15,58,15,201,8
DB	102,69,15,58,15,237,4
	paddd	xmm2,xmm6
	pxor	xmm14,xmm2
	pshufb	xmm14,XMMWORD PTR[$L$rol16]
	paddd	xmm10,xmm14
	pxor	xmm6,xmm10
	movdqa	xmm3,xmm6
	pslld	xmm3,12
	psrld	xmm6,20
	pxor	xmm6,xmm3
	paddd	xmm2,xmm6
	pxor	xmm14,xmm2
	pshufb	xmm14,XMMWORD PTR[$L$rol8]
	paddd	xmm10,xmm14
	pxor	xmm6,xmm10
	movdqa	xmm3,xmm6
	pslld	xmm3,7
	psrld	xmm6,25
	pxor	xmm6,xmm3
DB	102,15,58,15,246,12
DB	102,69,15,58,15,210,8
DB	102,69,15,58,15,246,4

	lea	rdi,QWORD PTR[16+rdi]
	dec	rcx
	jg	$L$seal_sse_tail_192_rounds_and_x2hash
	dec	r8
	jge	$L$seal_sse_tail_192_rounds_and_x1hash
	paddd	xmm2,XMMWORD PTR[$L$chacha20_consts]
	paddd	xmm6,XMMWORD PTR[((160+48))+rbp]
	paddd	xmm10,XMMWORD PTR[((160+64))+rbp]
	paddd	xmm14,XMMWORD PTR[((160+128))+rbp]
	paddd	xmm1,XMMWORD PTR[$L$chacha20_consts]
	paddd	xmm5,XMMWORD PTR[((160+48))+rbp]
	paddd	xmm9,XMMWORD PTR[((160+64))+rbp]
	paddd	xmm13,XMMWORD PTR[((160+112))+rbp]
	paddd	xmm0,XMMWORD PTR[$L$chacha20_consts]
	paddd	xmm4,XMMWORD PTR[((160+48))+rbp]
	paddd	xmm8,XMMWORD PTR[((160+64))+rbp]
	paddd	xmm12,XMMWORD PTR[((160+96))+rbp]
	movdqu	xmm3,XMMWORD PTR[((0 + 0))+rsi]
	movdqu	xmm7,XMMWORD PTR[((16 + 0))+rsi]
	movdqu	xmm11,XMMWORD PTR[((32 + 0))+rsi]
	movdqu	xmm15,XMMWORD PTR[((48 + 0))+rsi]
	pxor	xmm2,xmm3
	pxor	xmm6,xmm7
	pxor	xmm10,xmm11
	pxor	xmm15,xmm14
	movdqu	XMMWORD PTR[(0 + 0)+rdi],xmm2
	movdqu	XMMWORD PTR[(16 + 0)+rdi],xmm6
	movdqu	XMMWORD PTR[(32 + 0)+rdi],xmm10
	movdqu	XMMWORD PTR[(48 + 0)+rdi],xmm15
	movdqu	xmm3,XMMWORD PTR[((0 + 64))+rsi]
	movdqu	xmm7,XMMWORD PTR[((16 + 64))+rsi]
	movdqu	xmm11,XMMWORD PTR[((32 + 64))+rsi]
	movdqu	xmm15,XMMWORD PTR[((48 + 64))+rsi]
	pxor	xmm1,xmm3
	pxor	xmm5,xmm7
	pxor	xmm9,xmm11
	pxor	xmm15,xmm13
	movdqu	XMMWORD PTR[(0 + 64)+rdi],xmm1
	movdqu	XMMWORD PTR[(16 + 64)+rdi],xmm5
	movdqu	XMMWORD PTR[(32 + 64)+rdi],xmm9
	movdqu	XMMWORD PTR[(48 + 64)+rdi],xmm15

	mov	rcx,8*16
	sub	rbx,8*16
	lea	rsi,QWORD PTR[128+rsi]

$L$seal_sse_128_tail_hash::
	cmp	rcx,16
	jb	$L$seal_sse_128_tail_xor
	add	r10,QWORD PTR[((0+0))+rdi]
	adc	r11,QWORD PTR[((8+0))+rdi]
	adc	r12,1
	mov	rax,QWORD PTR[((0+160+0))+rbp]
	mov	r15,rax
	mul	r10
	mov	r13,rax
	mov	r14,rdx
	mov	rax,QWORD PTR[((0+160+0))+rbp]
	mul	r11
	imul	r15,r12
	add	r14,rax
	adc	r15,rdx
	mov	rax,QWORD PTR[((8+160+0))+rbp]
	mov	r9,rax
	mul	r10
	add	r14,rax
	adc	rdx,0
	mov	r10,rdx
	mov	rax,QWORD PTR[((8+160+0))+rbp]
	mul	r11
	add	r15,rax
	adc	rdx,0
	imul	r9,r12
	add	r15,r10
	adc	r9,rdx
	mov	r10,r13
	mov	r11,r14
	mov	r12,r15
	and	r12,3
	mov	r13,r15
	and	r13,-4
	mov	r14,r9
	shrd	r15,r9,2
	shr	r9,2
	add	r15,r13
	adc	r9,r14
	add	r10,r15
	adc	r11,r9
	adc	r12,0

	sub	rcx,16
	lea	rdi,QWORD PTR[16+rdi]
	jmp	$L$seal_sse_128_tail_hash

$L$seal_sse_128_tail_xor::
	cmp	rbx,16
	jb	$L$seal_sse_tail_16
	sub	rbx,16

	movdqu	xmm3,XMMWORD PTR[rsi]
	pxor	xmm0,xmm3
	movdqu	XMMWORD PTR[rdi],xmm0

	add	r10,QWORD PTR[rdi]
	adc	r11,QWORD PTR[8+rdi]
	adc	r12,1
	lea	rsi,QWORD PTR[16+rsi]
	lea	rdi,QWORD PTR[16+rdi]
	mov	rax,QWORD PTR[((0+160+0))+rbp]
	mov	r15,rax
	mul	r10
	mov	r13,rax
	mov	r14,rdx
	mov	rax,QWORD PTR[((0+160+0))+rbp]
	mul	r11
	imul	r15,r12
	add	r14,rax
	adc	r15,rdx
	mov	rax,QWORD PTR[((8+160+0))+rbp]
	mov	r9,rax
	mul	r10
	add	r14,rax
	adc	rdx,0
	mov	r10,rdx
	mov	rax,QWORD PTR[((8+160+0))+rbp]
	mul	r11
	add	r15,rax
	adc	rdx,0
	imul	r9,r12
	add	r15,r10
	adc	r9,rdx
	mov	r10,r13
	mov	r11,r14
	mov	r12,r15
	and	r12,3
	mov	r13,r15
	and	r13,-4
	mov	r14,r9
	shrd	r15,r9,2
	shr	r9,2
	add	r15,r13
	adc	r9,r14
	add	r10,r15
	adc	r11,r9
	adc	r12,0


	movdqa	xmm0,xmm4
	movdqa	xmm4,xmm8
	movdqa	xmm8,xmm12
	movdqa	xmm12,xmm1
	movdqa	xmm1,xmm5
	movdqa	xmm5,xmm9
	movdqa	xmm9,xmm13
	jmp	$L$seal_sse_128_tail_xor

$L$seal_sse_tail_16::
	test	rbx,rbx
	jz	$L$process_blocks_of_extra_in

	mov	r8,rbx
	mov	rcx,rbx
	lea	rsi,QWORD PTR[((-1))+rbx*1+rsi]
	pxor	xmm15,xmm15
$L$seal_sse_tail_16_compose::
	pslldq	xmm15,1
	pinsrb	xmm15,BYTE PTR[rsi],0
	lea	rsi,QWORD PTR[((-1))+rsi]
	dec	rcx
	jne	$L$seal_sse_tail_16_compose


	pxor	xmm15,xmm0


	mov	rcx,rbx
	movdqu	xmm0,xmm15
$L$seal_sse_tail_16_extract::
	pextrb	XMMWORD PTR[rdi],xmm0,0
	psrldq	xmm0,1
	add	rdi,1
	sub	rcx,1
	jnz	$L$seal_sse_tail_16_extract








	mov	r9,QWORD PTR[((288 + 160 + 32))+rsp]
	mov	r14,QWORD PTR[56+r9]
	mov	r13,QWORD PTR[48+r9]
	test	r14,r14
	jz	$L$process_partial_block

	mov	r15,16
	sub	r15,rbx
	cmp	r14,r15

	jge	$L$load_extra_in
	mov	r15,r14

$L$load_extra_in::


	lea	rsi,QWORD PTR[((-1))+r15*1+r13]


	add	r13,r15
	sub	r14,r15
	mov	QWORD PTR[48+r9],r13
	mov	QWORD PTR[56+r9],r14



	add	r8,r15


	pxor	xmm11,xmm11
$L$load_extra_load_loop::
	pslldq	xmm11,1
	pinsrb	xmm11,BYTE PTR[rsi],0
	lea	rsi,QWORD PTR[((-1))+rsi]
	sub	r15,1
	jnz	$L$load_extra_load_loop




	mov	r15,rbx

$L$load_extra_shift_loop::
	pslldq	xmm11,1
	sub	r15,1
	jnz	$L$load_extra_shift_loop




	lea	r15,QWORD PTR[$L$and_masks]
	shl	rbx,4
	pand	xmm15,XMMWORD PTR[((-16))+rbx*1+r15]


	por	xmm15,xmm11



DB	102,77,15,126,253
	pextrq	r14,xmm15,1
	add	r10,r13
	adc	r11,r14
	adc	r12,1
	mov	rax,QWORD PTR[((0+160+0))+rbp]
	mov	r15,rax
	mul	r10
	mov	r13,rax
	mov	r14,rdx
	mov	rax,QWORD PTR[((0+160+0))+rbp]
	mul	r11
	imul	r15,r12
	add	r14,rax
	adc	r15,rdx
	mov	rax,QWORD PTR[((8+160+0))+rbp]
	mov	r9,rax
	mul	r10
	add	r14,rax
	adc	rdx,0
	mov	r10,rdx
	mov	rax,QWORD PTR[((8+160+0))+rbp]
	mul	r11
	add	r15,rax
	adc	rdx,0
	imul	r9,r12
	add	r15,r10
	adc	r9,rdx
	mov	r10,r13
	mov	r11,r14
	mov	r12,r15
	and	r12,3
	mov	r13,r15
	and	r13,-4
	mov	r14,r9
	shrd	r15,r9,2
	shr	r9,2
	add	r15,r13
	adc	r9,r14
	add	r10,r15
	adc	r11,r9
	adc	r12,0


$L$process_blocks_of_extra_in::

	mov	r9,QWORD PTR[((288+32+160 ))+rsp]
	mov	rsi,QWORD PTR[48+r9]
	mov	r8,QWORD PTR[56+r9]
	mov	rcx,r8
	shr	r8,4

$L$process_extra_hash_loop::
	jz	process_extra_in_trailer
	add	r10,QWORD PTR[((0+0))+rsi]
	adc	r11,QWORD PTR[((8+0))+rsi]
	adc	r12,1
	mov	rax,QWORD PTR[((0+160+0))+rbp]
	mov	r15,rax
	mul	r10
	mov	r13,rax
	mov	r14,rdx
	mov	rax,QWORD PTR[((0+160+0))+rbp]
	mul	r11
	imul	r15,r12
	add	r14,rax
	adc	r15,rdx
	mov	rax,QWORD PTR[((8+160+0))+rbp]
	mov	r9,rax
	mul	r10
	add	r14,rax
	adc	rdx,0
	mov	r10,rdx
	mov	rax,QWORD PTR[((8+160+0))+rbp]
	mul	r11
	add	r15,rax
	adc	rdx,0
	imul	r9,r12
	add	r15,r10
	adc	r9,rdx
	mov	r10,r13
	mov	r11,r14
	mov	r12,r15
	and	r12,3
	mov	r13,r15
	and	r13,-4
	mov	r14,r9
	shrd	r15,r9,2
	shr	r9,2
	add	r15,r13
	adc	r9,r14
	add	r10,r15
	adc	r11,r9
	adc	r12,0

	lea	rsi,QWORD PTR[16+rsi]
	sub	r8,1
	jmp	$L$process_extra_hash_loop
process_extra_in_trailer::
	and	rcx,15
	mov	rbx,rcx
	jz	$L$do_length_block
	lea	rsi,QWORD PTR[((-1))+rcx*1+rsi]

$L$process_extra_in_trailer_load::
	pslldq	xmm15,1
	pinsrb	xmm15,BYTE PTR[rsi],0
	lea	rsi,QWORD PTR[((-1))+rsi]
	sub	rcx,1
	jnz	$L$process_extra_in_trailer_load

$L$process_partial_block::

	lea	r15,QWORD PTR[$L$and_masks]
	shl	rbx,4
	pand	xmm15,XMMWORD PTR[((-16))+rbx*1+r15]
DB	102,77,15,126,253
	pextrq	r14,xmm15,1
	add	r10,r13
	adc	r11,r14
	adc	r12,1
	mov	rax,QWORD PTR[((0+160+0))+rbp]
	mov	r15,rax
	mul	r10
	mov	r13,rax
	mov	r14,rdx
	mov	rax,QWORD PTR[((0+160+0))+rbp]
	mul	r11
	imul	r15,r12
	add	r14,rax
	adc	r15,rdx
	mov	rax,QWORD PTR[((8+160+0))+rbp]
	mov	r9,rax
	mul	r10
	add	r14,rax
	adc	rdx,0
	mov	r10,rdx
	mov	rax,QWORD PTR[((8+160+0))+rbp]
	mul	r11
	add	r15,rax
	adc	rdx,0
	imul	r9,r12
	add	r15,r10
	adc	r9,rdx
	mov	r10,r13
	mov	r11,r14
	mov	r12,r15
	and	r12,3
	mov	r13,r15
	and	r13,-4
	mov	r14,r9
	shrd	r15,r9,2
	shr	r9,2
	add	r15,r13
	adc	r9,r14
	add	r10,r15
	adc	r11,r9
	adc	r12,0


$L$do_length_block::
	add	r10,QWORD PTR[((0+160+32))+rbp]
	adc	r11,QWORD PTR[((8+160+32))+rbp]
	adc	r12,1
	mov	rax,QWORD PTR[((0+160+0))+rbp]
	mov	r15,rax
	mul	r10
	mov	r13,rax
	mov	r14,rdx
	mov	rax,QWORD PTR[((0+160+0))+rbp]
	mul	r11
	imul	r15,r12
	add	r14,rax
	adc	r15,rdx
	mov	rax,QWORD PTR[((8+160+0))+rbp]
	mov	r9,rax
	mul	r10
	add	r14,rax
	adc	rdx,0
	mov	r10,rdx
	mov	rax,QWORD PTR[((8+160+0))+rbp]
	mul	r11
	add	r15,rax
	adc	rdx,0
	imul	r9,r12
	add	r15,r10
	adc	r9,rdx
	mov	r10,r13
	mov	r11,r14
	mov	r12,r15
	and	r12,3
	mov	r13,r15
	and	r13,-4
	mov	r14,r9
	shrd	r15,r9,2
	shr	r9,2
	add	r15,r13
	adc	r9,r14
	add	r10,r15
	adc	r11,r9
	adc	r12,0


	mov	r13,r10
	mov	r14,r11
	mov	r15,r12
	sub	r10,-5
	sbb	r11,-1
	sbb	r12,3
	cmovc	r10,r13
	cmovc	r11,r14
	cmovc	r12,r15

	add	r10,QWORD PTR[((0+160+16))+rbp]
	adc	r11,QWORD PTR[((8+160+16))+rbp]

	movaps	xmm6,XMMWORD PTR[((0+0))+rbp]
	movaps	xmm7,XMMWORD PTR[((16+0))+rbp]
	movaps	xmm8,XMMWORD PTR[((32+0))+rbp]
	movaps	xmm9,XMMWORD PTR[((48+0))+rbp]
	movaps	xmm10,XMMWORD PTR[((64+0))+rbp]
	movaps	xmm11,XMMWORD PTR[((80+0))+rbp]
	movaps	xmm12,XMMWORD PTR[((96+0))+rbp]
	movaps	xmm13,XMMWORD PTR[((112+0))+rbp]
	movaps	xmm14,XMMWORD PTR[((128+0))+rbp]
	movaps	xmm15,XMMWORD PTR[((144+0))+rbp]


	add	rsp,288 + 160 + 32


	pop	r9

	mov	QWORD PTR[r9],r10
	mov	QWORD PTR[8+r9],r11
	pop	r15

	pop	r14

	pop	r13

	pop	r12

	pop	rbx

	pop	rbp

	mov	rdi,QWORD PTR[8+rsp]	;WIN64 epilogue
	mov	rsi,QWORD PTR[16+rsp]
	DB	0F3h,0C3h		;repret

$L$seal_sse_128::

	movdqu	xmm0,XMMWORD PTR[$L$chacha20_consts]
	movdqa	xmm1,xmm0
	movdqa	xmm2,xmm0
	movdqu	xmm4,XMMWORD PTR[r9]
	movdqa	xmm5,xmm4
	movdqa	xmm6,xmm4
	movdqu	xmm8,XMMWORD PTR[16+r9]
	movdqa	xmm9,xmm8
	movdqa	xmm10,xmm8
	movdqu	xmm14,XMMWORD PTR[32+r9]
	movdqa	xmm12,xmm14
	paddd	xmm12,XMMWORD PTR[$L$sse_inc]
	movdqa	xmm13,xmm12
	paddd	xmm13,XMMWORD PTR[$L$sse_inc]
	movdqa	xmm7,xmm4
	movdqa	xmm11,xmm8
	movdqa	xmm15,xmm12
	mov	r10,10

$L$seal_sse_128_rounds::
	paddd	xmm0,xmm4
	pxor	xmm12,xmm0
	pshufb	xmm12,XMMWORD PTR[$L$rol16]
	paddd	xmm8,xmm12
	pxor	xmm4,xmm8
	movdqa	xmm3,xmm4
	pslld	xmm3,12
	psrld	xmm4,20
	pxor	xmm4,xmm3
	paddd	xmm0,xmm4
	pxor	xmm12,xmm0
	pshufb	xmm12,XMMWORD PTR[$L$rol8]
	paddd	xmm8,xmm12
	pxor	xmm4,xmm8
	movdqa	xmm3,xmm4
	pslld	xmm3,7
	psrld	xmm4,25
	pxor	xmm4,xmm3
DB	102,15,58,15,228,4
DB	102,69,15,58,15,192,8
DB	102,69,15,58,15,228,12
	paddd	xmm1,xmm5
	pxor	xmm13,xmm1
	pshufb	xmm13,XMMWORD PTR[$L$rol16]
	paddd	xmm9,xmm13
	pxor	xmm5,xmm9
	movdqa	xmm3,xmm5
	pslld	xmm3,12
	psrld	xmm5,20
	pxor	xmm5,xmm3
	paddd	xmm1,xmm5
	pxor	xmm13,xmm1
	pshufb	xmm13,XMMWORD PTR[$L$rol8]
	paddd	xmm9,xmm13
	pxor	xmm5,xmm9
	movdqa	xmm3,xmm5
	pslld	xmm3,7
	psrld	xmm5,25
	pxor	xmm5,xmm3
DB	102,15,58,15,237,4
DB	102,69,15,58,15,201,8
DB	102,69,15,58,15,237,12
	paddd	xmm2,xmm6
	pxor	xmm14,xmm2
	pshufb	xmm14,XMMWORD PTR[$L$rol16]
	paddd	xmm10,xmm14
	pxor	xmm6,xmm10
	movdqa	xmm3,xmm6
	pslld	xmm3,12
	psrld	xmm6,20
	pxor	xmm6,xmm3
	paddd	xmm2,xmm6
	pxor	xmm14,xmm2
	pshufb	xmm14,XMMWORD PTR[$L$rol8]
	paddd	xmm10,xmm14
	pxor	xmm6,xmm10
	movdqa	xmm3,xmm6
	pslld	xmm3,7
	psrld	xmm6,25
	pxor	xmm6,xmm3
DB	102,15,58,15,246,4
DB	102,69,15,58,15,210,8
DB	102,69,15,58,15,246,12
	paddd	xmm0,xmm4
	pxor	xmm12,xmm0
	pshufb	xmm12,XMMWORD PTR[$L$rol16]
	paddd	xmm8,xmm12
	pxor	xmm4,xmm8
	movdqa	xmm3,xmm4
	pslld	xmm3,12
	psrld	xmm4,20
	pxor	xmm4,xmm3
	paddd	xmm0,xmm4
	pxor	xmm12,xmm0
	pshufb	xmm12,XMMWORD PTR[$L$rol8]
	paddd	xmm8,xmm12
	pxor	xmm4,xmm8
	movdqa	xmm3,xmm4
	pslld	xmm3,7
	psrld	xmm4,25
	pxor	xmm4,xmm3
DB	102,15,58,15,228,12
DB	102,69,15,58,15,192,8
DB	102,69,15,58,15,228,4
	paddd	xmm1,xmm5
	pxor	xmm13,xmm1
	pshufb	xmm13,XMMWORD PTR[$L$rol16]
	paddd	xmm9,xmm13
	pxor	xmm5,xmm9
	movdqa	xmm3,xmm5
	pslld	xmm3,12
	psrld	xmm5,20
	pxor	xmm5,xmm3
	paddd	xmm1,xmm5
	pxor	xmm13,xmm1
	pshufb	xmm13,XMMWORD PTR[$L$rol8]
	paddd	xmm9,xmm13
	pxor	xmm5,xmm9
	movdqa	xmm3,xmm5
	pslld	xmm3,7
	psrld	xmm5,25
	pxor	xmm5,xmm3
DB	102,15,58,15,237,12
DB	102,69,15,58,15,201,8
DB	102,69,15,58,15,237,4
	paddd	xmm2,xmm6
	pxor	xmm14,xmm2
	pshufb	xmm14,XMMWORD PTR[$L$rol16]
	paddd	xmm10,xmm14
	pxor	xmm6,xmm10
	movdqa	xmm3,xmm6
	pslld	xmm3,12
	psrld	xmm6,20
	pxor	xmm6,xmm3
	paddd	xmm2,xmm6
	pxor	xmm14,xmm2
	pshufb	xmm14,XMMWORD PTR[$L$rol8]
	paddd	xmm10,xmm14
	pxor	xmm6,xmm10
	movdqa	xmm3,xmm6
	pslld	xmm3,7
	psrld	xmm6,25
	pxor	xmm6,xmm3
DB	102,15,58,15,246,12
DB	102,69,15,58,15,210,8
DB	102,69,15,58,15,246,4

	dec	r10
	jnz	$L$seal_sse_128_rounds
	paddd	xmm0,XMMWORD PTR[$L$chacha20_consts]
	paddd	xmm1,XMMWORD PTR[$L$chacha20_consts]
	paddd	xmm2,XMMWORD PTR[$L$chacha20_consts]
	paddd	xmm4,xmm7
	paddd	xmm5,xmm7
	paddd	xmm6,xmm7
	paddd	xmm8,xmm11
	paddd	xmm9,xmm11
	paddd	xmm12,xmm15
	paddd	xmm15,XMMWORD PTR[$L$sse_inc]
	paddd	xmm13,xmm15

	pand	xmm2,XMMWORD PTR[$L$clamp]
	movdqa	XMMWORD PTR[(160+0)+rbp],xmm2
	movdqa	XMMWORD PTR[(160+16)+rbp],xmm6

	mov	r8,r8
	call	poly_hash_ad_internal
	jmp	$L$seal_sse_128_tail_xor
$L$SEH_end_chacha20_poly1305_seal::
chacha20_poly1305_seal	ENDP




ALIGN	64
chacha20_poly1305_open_avx2	PROC PRIVATE












	vzeroupper
	vmovdqa	ymm0,YMMWORD PTR[$L$chacha20_consts]
	vbroadcasti128	ymm4,XMMWORD PTR[r9]
	vbroadcasti128	ymm8,XMMWORD PTR[16+r9]
	vbroadcasti128	ymm12,XMMWORD PTR[32+r9]
	vpaddd	ymm12,ymm12,YMMWORD PTR[$L$avx2_init]
	cmp	rbx,6*32
	jbe	$L$open_avx2_192
	cmp	rbx,10*32
	jbe	$L$open_avx2_320

	vmovdqa	YMMWORD PTR[(160+64)+rbp],ymm4
	vmovdqa	YMMWORD PTR[(160+96)+rbp],ymm8
	vmovdqa	YMMWORD PTR[(160+160)+rbp],ymm12
	mov	r10,10
$L$open_avx2_init_rounds::
	vpaddd	ymm0,ymm0,ymm4
	vpxor	ymm12,ymm12,ymm0
	vpshufb	ymm12,ymm12,YMMWORD PTR[$L$rol16]
	vpaddd	ymm8,ymm8,ymm12
	vpxor	ymm4,ymm4,ymm8
	vpsrld	ymm3,ymm4,20
	vpslld	ymm4,ymm4,12
	vpxor	ymm4,ymm4,ymm3
	vpaddd	ymm0,ymm0,ymm4
	vpxor	ymm12,ymm12,ymm0
	vpshufb	ymm12,ymm12,YMMWORD PTR[$L$rol8]
	vpaddd	ymm8,ymm8,ymm12
	vpxor	ymm4,ymm4,ymm8
	vpslld	ymm3,ymm4,7
	vpsrld	ymm4,ymm4,25
	vpxor	ymm4,ymm4,ymm3
	vpalignr	ymm12,ymm12,ymm12,12
	vpalignr	ymm8,ymm8,ymm8,8
	vpalignr	ymm4,ymm4,ymm4,4
	vpaddd	ymm0,ymm0,ymm4
	vpxor	ymm12,ymm12,ymm0
	vpshufb	ymm12,ymm12,YMMWORD PTR[$L$rol16]
	vpaddd	ymm8,ymm8,ymm12
	vpxor	ymm4,ymm4,ymm8
	vpsrld	ymm3,ymm4,20
	vpslld	ymm4,ymm4,12
	vpxor	ymm4,ymm4,ymm3
	vpaddd	ymm0,ymm0,ymm4
	vpxor	ymm12,ymm12,ymm0
	vpshufb	ymm12,ymm12,YMMWORD PTR[$L$rol8]
	vpaddd	ymm8,ymm8,ymm12
	vpxor	ymm4,ymm4,ymm8
	vpslld	ymm3,ymm4,7
	vpsrld	ymm4,ymm4,25
	vpxor	ymm4,ymm4,ymm3
	vpalignr	ymm12,ymm12,ymm12,4
	vpalignr	ymm8,ymm8,ymm8,8
	vpalignr	ymm4,ymm4,ymm4,12

	dec	r10
	jne	$L$open_avx2_init_rounds
	vpaddd	ymm0,ymm0,YMMWORD PTR[$L$chacha20_consts]
	vpaddd	ymm4,ymm4,YMMWORD PTR[((160+64))+rbp]
	vpaddd	ymm8,ymm8,YMMWORD PTR[((160+96))+rbp]
	vpaddd	ymm12,ymm12,YMMWORD PTR[((160+160))+rbp]

	vperm2i128	ymm3,ymm4,ymm0,002h

	vpand	ymm3,ymm3,YMMWORD PTR[$L$clamp]
	vmovdqa	YMMWORD PTR[(160+0)+rbp],ymm3

	vperm2i128	ymm0,ymm4,ymm0,013h
	vperm2i128	ymm4,ymm12,ymm8,013h

	mov	r8,r8
	call	poly_hash_ad_internal

	xor	rcx,rcx
$L$open_avx2_init_hash::
	add	r10,QWORD PTR[((0+0))+rcx*1+rsi]
	adc	r11,QWORD PTR[((8+0))+rcx*1+rsi]
	adc	r12,1
	mov	rax,QWORD PTR[((0+160+0))+rbp]
	mov	r15,rax
	mul	r10
	mov	r13,rax
	mov	r14,rdx
	mov	rax,QWORD PTR[((0+160+0))+rbp]
	mul	r11
	imul	r15,r12
	add	r14,rax
	adc	r15,rdx
	mov	rax,QWORD PTR[((8+160+0))+rbp]
	mov	r9,rax
	mul	r10
	add	r14,rax
	adc	rdx,0
	mov	r10,rdx
	mov	rax,QWORD PTR[((8+160+0))+rbp]
	mul	r11
	add	r15,rax
	adc	rdx,0
	imul	r9,r12
	add	r15,r10
	adc	r9,rdx
	mov	r10,r13
	mov	r11,r14
	mov	r12,r15
	and	r12,3
	mov	r13,r15
	and	r13,-4
	mov	r14,r9
	shrd	r15,r9,2
	shr	r9,2
	add	r15,r13
	adc	r9,r14
	add	r10,r15
	adc	r11,r9
	adc	r12,0

	add	rcx,16
	cmp	rcx,2*32
	jne	$L$open_avx2_init_hash

	vpxor	ymm0,ymm0,YMMWORD PTR[rsi]
	vpxor	ymm4,ymm4,YMMWORD PTR[32+rsi]

	vmovdqu	YMMWORD PTR[rdi],ymm0
	vmovdqu	YMMWORD PTR[32+rdi],ymm4
	lea	rsi,QWORD PTR[64+rsi]
	lea	rdi,QWORD PTR[64+rdi]
	sub	rbx,2*32
$L$open_avx2_main_loop::

	cmp	rbx,16*32
	jb	$L$open_avx2_main_loop_done
	vmovdqa	ymm0,YMMWORD PTR[$L$chacha20_consts]
	vmovdqa	ymm4,YMMWORD PTR[((160+64))+rbp]
	vmovdqa	ymm8,YMMWORD PTR[((160+96))+rbp]
	vmovdqa	ymm1,ymm0
	vmovdqa	ymm5,ymm4
	vmovdqa	ymm9,ymm8
	vmovdqa	ymm2,ymm0
	vmovdqa	ymm6,ymm4
	vmovdqa	ymm10,ymm8
	vmovdqa	ymm3,ymm0
	vmovdqa	ymm7,ymm4
	vmovdqa	ymm11,ymm8
	vmovdqa	ymm12,YMMWORD PTR[$L$avx2_inc]
	vpaddd	ymm15,ymm12,YMMWORD PTR[((160+160))+rbp]
	vpaddd	ymm14,ymm12,ymm15
	vpaddd	ymm13,ymm12,ymm14
	vpaddd	ymm12,ymm12,ymm13
	vmovdqa	YMMWORD PTR[(160+256)+rbp],ymm15
	vmovdqa	YMMWORD PTR[(160+224)+rbp],ymm14
	vmovdqa	YMMWORD PTR[(160+192)+rbp],ymm13
	vmovdqa	YMMWORD PTR[(160+160)+rbp],ymm12

	xor	rcx,rcx
$L$open_avx2_main_loop_rounds::
	add	r10,QWORD PTR[((0+0))+rcx*1+rsi]
	adc	r11,QWORD PTR[((8+0))+rcx*1+rsi]
	adc	r12,1
	vmovdqa	YMMWORD PTR[(160+128)+rbp],ymm8
	vmovdqa	ymm8,YMMWORD PTR[$L$rol16]
	vpaddd	ymm3,ymm3,ymm7
	vpaddd	ymm2,ymm2,ymm6
	vpaddd	ymm1,ymm1,ymm5
	vpaddd	ymm0,ymm0,ymm4
	vpxor	ymm15,ymm15,ymm3
	vpxor	ymm14,ymm14,ymm2
	vpxor	ymm13,ymm13,ymm1
	vpxor	ymm12,ymm12,ymm0
	mov	rdx,QWORD PTR[((0+160+0))+rbp]
	mov	r15,rdx
	mulx	r14,r13,r10
	mulx	rdx,rax,r11
	imul	r15,r12
	add	r14,rax
	adc	r15,rdx
	vpshufb	ymm15,ymm15,ymm8
	vpshufb	ymm14,ymm14,ymm8
	vpshufb	ymm13,ymm13,ymm8
	vpshufb	ymm12,ymm12,ymm8
	vpaddd	ymm11,ymm11,ymm15
	vpaddd	ymm10,ymm10,ymm14
	vpaddd	ymm9,ymm9,ymm13
	vpaddd	ymm8,ymm12,YMMWORD PTR[((160+128))+rbp]
	vpxor	ymm7,ymm7,ymm11
	mov	rdx,QWORD PTR[((8+160+0))+rbp]
	mulx	rax,r10,r10
	add	r14,r10
	mulx	r9,r11,r11
	adc	r15,r11
	adc	r9,0
	imul	rdx,r12
	vpxor	ymm6,ymm6,ymm10
	vpxor	ymm5,ymm5,ymm9
	vpxor	ymm4,ymm4,ymm8
	vmovdqa	YMMWORD PTR[(160+128)+rbp],ymm8
	vpsrld	ymm8,ymm7,20
	vpslld	ymm7,ymm7,32-20
	vpxor	ymm7,ymm7,ymm8
	vpsrld	ymm8,ymm6,20
	vpslld	ymm6,ymm6,32-20
	vpxor	ymm6,ymm6,ymm8
	vpsrld	ymm8,ymm5,20
	vpslld	ymm5,ymm5,32-20
	add	r15,rax
	adc	r9,rdx
	vpxor	ymm5,ymm5,ymm8
	vpsrld	ymm8,ymm4,20
	vpslld	ymm4,ymm4,32-20
	vpxor	ymm4,ymm4,ymm8
	vmovdqa	ymm8,YMMWORD PTR[$L$rol8]
	vpaddd	ymm3,ymm3,ymm7
	vpaddd	ymm2,ymm2,ymm6
	vpaddd	ymm1,ymm1,ymm5
	vpaddd	ymm0,ymm0,ymm4
	vpxor	ymm15,ymm15,ymm3
	mov	r10,r13
	mov	r11,r14
	mov	r12,r15
	and	r12,3
	mov	r13,r15
	and	r13,-4
	mov	r14,r9
	shrd	r15,r9,2
	shr	r9,2
	add	r15,r13
	adc	r9,r14
	add	r10,r15
	adc	r11,r9
	adc	r12,0
	vpxor	ymm14,ymm14,ymm2
	vpxor	ymm13,ymm13,ymm1
	vpxor	ymm12,ymm12,ymm0
	vpshufb	ymm15,ymm15,ymm8
	vpshufb	ymm14,ymm14,ymm8
	vpshufb	ymm13,ymm13,ymm8
	vpshufb	ymm12,ymm12,ymm8
	vpaddd	ymm11,ymm11,ymm15
	vpaddd	ymm10,ymm10,ymm14
	add	r10,QWORD PTR[((0+16))+rcx*1+rsi]
	adc	r11,QWORD PTR[((8+16))+rcx*1+rsi]
	adc	r12,1
	vpaddd	ymm9,ymm9,ymm13
	vpaddd	ymm8,ymm12,YMMWORD PTR[((160+128))+rbp]
	vpxor	ymm7,ymm7,ymm11
	vpxor	ymm6,ymm6,ymm10
	vpxor	ymm5,ymm5,ymm9
	vpxor	ymm4,ymm4,ymm8
	vmovdqa	YMMWORD PTR[(160+128)+rbp],ymm8
	vpsrld	ymm8,ymm7,25
	mov	rdx,QWORD PTR[((0+160+0))+rbp]
	mov	r15,rdx
	mulx	r14,r13,r10
	mulx	rdx,rax,r11
	imul	r15,r12
	add	r14,rax
	adc	r15,rdx
	vpslld	ymm7,ymm7,32-25
	vpxor	ymm7,ymm7,ymm8
	vpsrld	ymm8,ymm6,25
	vpslld	ymm6,ymm6,32-25
	vpxor	ymm6,ymm6,ymm8
	vpsrld	ymm8,ymm5,25
	vpslld	ymm5,ymm5,32-25
	vpxor	ymm5,ymm5,ymm8
	vpsrld	ymm8,ymm4,25
	vpslld	ymm4,ymm4,32-25
	vpxor	ymm4,ymm4,ymm8
	vmovdqa	ymm8,YMMWORD PTR[((160+128))+rbp]
	vpalignr	ymm7,ymm7,ymm7,4
	vpalignr	ymm11,ymm11,ymm11,8
	vpalignr	ymm15,ymm15,ymm15,12
	vpalignr	ymm6,ymm6,ymm6,4
	vpalignr	ymm10,ymm10,ymm10,8
	vpalignr	ymm14,ymm14,ymm14,12
	mov	rdx,QWORD PTR[((8+160+0))+rbp]
	mulx	rax,r10,r10
	add	r14,r10
	mulx	r9,r11,r11
	adc	r15,r11
	adc	r9,0
	imul	rdx,r12
	vpalignr	ymm5,ymm5,ymm5,4
	vpalignr	ymm9,ymm9,ymm9,8
	vpalignr	ymm13,ymm13,ymm13,12
	vpalignr	ymm4,ymm4,ymm4,4
	vpalignr	ymm8,ymm8,ymm8,8
	vpalignr	ymm12,ymm12,ymm12,12
	vmovdqa	YMMWORD PTR[(160+128)+rbp],ymm8
	vmovdqa	ymm8,YMMWORD PTR[$L$rol16]
	vpaddd	ymm3,ymm3,ymm7
	vpaddd	ymm2,ymm2,ymm6
	vpaddd	ymm1,ymm1,ymm5
	vpaddd	ymm0,ymm0,ymm4
	vpxor	ymm15,ymm15,ymm3
	vpxor	ymm14,ymm14,ymm2
	vpxor	ymm13,ymm13,ymm1
	vpxor	ymm12,ymm12,ymm0
	vpshufb	ymm15,ymm15,ymm8
	vpshufb	ymm14,ymm14,ymm8
	add	r15,rax
	adc	r9,rdx
	vpshufb	ymm13,ymm13,ymm8
	vpshufb	ymm12,ymm12,ymm8
	vpaddd	ymm11,ymm11,ymm15
	vpaddd	ymm10,ymm10,ymm14
	vpaddd	ymm9,ymm9,ymm13
	vpaddd	ymm8,ymm12,YMMWORD PTR[((160+128))+rbp]
	vpxor	ymm7,ymm7,ymm11
	vpxor	ymm6,ymm6,ymm10
	vpxor	ymm5,ymm5,ymm9
	mov	r10,r13
	mov	r11,r14
	mov	r12,r15
	and	r12,3
	mov	r13,r15
	and	r13,-4
	mov	r14,r9
	shrd	r15,r9,2
	shr	r9,2
	add	r15,r13
	adc	r9,r14
	add	r10,r15
	adc	r11,r9
	adc	r12,0
	vpxor	ymm4,ymm4,ymm8
	vmovdqa	YMMWORD PTR[(160+128)+rbp],ymm8
	vpsrld	ymm8,ymm7,20
	vpslld	ymm7,ymm7,32-20
	vpxor	ymm7,ymm7,ymm8
	vpsrld	ymm8,ymm6,20
	vpslld	ymm6,ymm6,32-20
	vpxor	ymm6,ymm6,ymm8
	add	r10,QWORD PTR[((0+32))+rcx*1+rsi]
	adc	r11,QWORD PTR[((8+32))+rcx*1+rsi]
	adc	r12,1

	lea	rcx,QWORD PTR[48+rcx]
	vpsrld	ymm8,ymm5,20
	vpslld	ymm5,ymm5,32-20
	vpxor	ymm5,ymm5,ymm8
	vpsrld	ymm8,ymm4,20
	vpslld	ymm4,ymm4,32-20
	vpxor	ymm4,ymm4,ymm8
	vmovdqa	ymm8,YMMWORD PTR[$L$rol8]
	vpaddd	ymm3,ymm3,ymm7
	vpaddd	ymm2,ymm2,ymm6
	vpaddd	ymm1,ymm1,ymm5
	vpaddd	ymm0,ymm0,ymm4
	vpxor	ymm15,ymm15,ymm3
	vpxor	ymm14,ymm14,ymm2
	vpxor	ymm13,ymm13,ymm1
	vpxor	ymm12,ymm12,ymm0
	vpshufb	ymm15,ymm15,ymm8
	vpshufb	ymm14,ymm14,ymm8
	vpshufb	ymm13,ymm13,ymm8
	mov	rdx,QWORD PTR[((0+160+0))+rbp]
	mov	r15,rdx
	mulx	r14,r13,r10
	mulx	rdx,rax,r11
	imul	r15,r12
	add	r14,rax
	adc	r15,rdx
	vpshufb	ymm12,ymm12,ymm8
	vpaddd	ymm11,ymm11,ymm15
	vpaddd	ymm10,ymm10,ymm14
	vpaddd	ymm9,ymm9,ymm13
	vpaddd	ymm8,ymm12,YMMWORD PTR[((160+128))+rbp]
	vpxor	ymm7,ymm7,ymm11
	vpxor	ymm6,ymm6,ymm10
	vpxor	ymm5,ymm5,ymm9
	mov	rdx,QWORD PTR[((8+160+0))+rbp]
	mulx	rax,r10,r10
	add	r14,r10
	mulx	r9,r11,r11
	adc	r15,r11
	adc	r9,0
	imul	rdx,r12
	vpxor	ymm4,ymm4,ymm8
	vmovdqa	YMMWORD PTR[(160+128)+rbp],ymm8
	vpsrld	ymm8,ymm7,25
	vpslld	ymm7,ymm7,32-25
	vpxor	ymm7,ymm7,ymm8
	vpsrld	ymm8,ymm6,25
	vpslld	ymm6,ymm6,32-25
	vpxor	ymm6,ymm6,ymm8
	add	r15,rax
	adc	r9,rdx
	vpsrld	ymm8,ymm5,25
	vpslld	ymm5,ymm5,32-25
	vpxor	ymm5,ymm5,ymm8
	vpsrld	ymm8,ymm4,25
	vpslld	ymm4,ymm4,32-25
	vpxor	ymm4,ymm4,ymm8
	vmovdqa	ymm8,YMMWORD PTR[((160+128))+rbp]
	vpalignr	ymm7,ymm7,ymm7,12
	vpalignr	ymm11,ymm11,ymm11,8
	vpalignr	ymm15,ymm15,ymm15,4
	vpalignr	ymm6,ymm6,ymm6,12
	vpalignr	ymm10,ymm10,ymm10,8
	vpalignr	ymm14,ymm14,ymm14,4
	vpalignr	ymm5,ymm5,ymm5,12
	vpalignr	ymm9,ymm9,ymm9,8
	vpalignr	ymm13,ymm13,ymm13,4
	vpalignr	ymm4,ymm4,ymm4,12
	vpalignr	ymm8,ymm8,ymm8,8
	mov	r10,r13
	mov	r11,r14
	mov	r12,r15
	and	r12,3
	mov	r13,r15
	and	r13,-4
	mov	r14,r9
	shrd	r15,r9,2
	shr	r9,2
	add	r15,r13
	adc	r9,r14
	add	r10,r15
	adc	r11,r9
	adc	r12,0
	vpalignr	ymm12,ymm12,ymm12,4

	cmp	rcx,10*6*8
	jne	$L$open_avx2_main_loop_rounds
	vpaddd	ymm3,ymm3,YMMWORD PTR[$L$chacha20_consts]
	vpaddd	ymm7,ymm7,YMMWORD PTR[((160+64))+rbp]
	vpaddd	ymm11,ymm11,YMMWORD PTR[((160+96))+rbp]
	vpaddd	ymm15,ymm15,YMMWORD PTR[((160+256))+rbp]
	vpaddd	ymm2,ymm2,YMMWORD PTR[$L$chacha20_consts]
	vpaddd	ymm6,ymm6,YMMWORD PTR[((160+64))+rbp]
	vpaddd	ymm10,ymm10,YMMWORD PTR[((160+96))+rbp]
	vpaddd	ymm14,ymm14,YMMWORD PTR[((160+224))+rbp]
	vpaddd	ymm1,ymm1,YMMWORD PTR[$L$chacha20_consts]
	vpaddd	ymm5,ymm5,YMMWORD PTR[((160+64))+rbp]
	vpaddd	ymm9,ymm9,YMMWORD PTR[((160+96))+rbp]
	vpaddd	ymm13,ymm13,YMMWORD PTR[((160+192))+rbp]
	vpaddd	ymm0,ymm0,YMMWORD PTR[$L$chacha20_consts]
	vpaddd	ymm4,ymm4,YMMWORD PTR[((160+64))+rbp]
	vpaddd	ymm8,ymm8,YMMWORD PTR[((160+96))+rbp]
	vpaddd	ymm12,ymm12,YMMWORD PTR[((160+160))+rbp]

	vmovdqa	YMMWORD PTR[(160+128)+rbp],ymm0
	add	r10,QWORD PTR[((0+480))+rsi]
	adc	r11,QWORD PTR[((8+480))+rsi]
	adc	r12,1
	vperm2i128	ymm0,ymm7,ymm3,002h
	vperm2i128	ymm7,ymm7,ymm3,013h
	vperm2i128	ymm3,ymm15,ymm11,002h
	vperm2i128	ymm11,ymm15,ymm11,013h
	vpxor	ymm0,ymm0,YMMWORD PTR[((0+0))+rsi]
	vpxor	ymm3,ymm3,YMMWORD PTR[((32+0))+rsi]
	vpxor	ymm7,ymm7,YMMWORD PTR[((64+0))+rsi]
	vpxor	ymm11,ymm11,YMMWORD PTR[((96+0))+rsi]
	vmovdqu	YMMWORD PTR[(0+0)+rdi],ymm0
	vmovdqu	YMMWORD PTR[(32+0)+rdi],ymm3
	vmovdqu	YMMWORD PTR[(64+0)+rdi],ymm7
	vmovdqu	YMMWORD PTR[(96+0)+rdi],ymm11

	vmovdqa	ymm0,YMMWORD PTR[((160+128))+rbp]
	mov	rax,QWORD PTR[((0+160+0))+rbp]
	mov	r15,rax
	mul	r10
	mov	r13,rax
	mov	r14,rdx
	mov	rax,QWORD PTR[((0+160+0))+rbp]
	mul	r11
	imul	r15,r12
	add	r14,rax
	adc	r15,rdx
	mov	rax,QWORD PTR[((8+160+0))+rbp]
	mov	r9,rax
	mul	r10
	add	r14,rax
	adc	rdx,0
	mov	r10,rdx
	mov	rax,QWORD PTR[((8+160+0))+rbp]
	mul	r11
	add	r15,rax
	adc	rdx,0
	imul	r9,r12
	add	r15,r10
	adc	r9,rdx
	mov	r10,r13
	mov	r11,r14
	mov	r12,r15
	and	r12,3
	mov	r13,r15
	and	r13,-4
	mov	r14,r9
	shrd	r15,r9,2
	shr	r9,2
	add	r15,r13
	adc	r9,r14
	add	r10,r15
	adc	r11,r9
	adc	r12,0
	vperm2i128	ymm3,ymm6,ymm2,002h
	vperm2i128	ymm6,ymm6,ymm2,013h
	vperm2i128	ymm2,ymm14,ymm10,002h
	vperm2i128	ymm10,ymm14,ymm10,013h
	vpxor	ymm3,ymm3,YMMWORD PTR[((0+128))+rsi]
	vpxor	ymm2,ymm2,YMMWORD PTR[((32+128))+rsi]
	vpxor	ymm6,ymm6,YMMWORD PTR[((64+128))+rsi]
	vpxor	ymm10,ymm10,YMMWORD PTR[((96+128))+rsi]
	vmovdqu	YMMWORD PTR[(0+128)+rdi],ymm3
	vmovdqu	YMMWORD PTR[(32+128)+rdi],ymm2
	vmovdqu	YMMWORD PTR[(64+128)+rdi],ymm6
	vmovdqu	YMMWORD PTR[(96+128)+rdi],ymm10
	add	r10,QWORD PTR[((0+480+16))+rsi]
	adc	r11,QWORD PTR[((8+480+16))+rsi]
	adc	r12,1
	vperm2i128	ymm3,ymm5,ymm1,002h
	vperm2i128	ymm5,ymm5,ymm1,013h
	vperm2i128	ymm1,ymm13,ymm9,002h
	vperm2i128	ymm9,ymm13,ymm9,013h
	vpxor	ymm3,ymm3,YMMWORD PTR[((0+256))+rsi]
	vpxor	ymm1,ymm1,YMMWORD PTR[((32+256))+rsi]
	vpxor	ymm5,ymm5,YMMWORD PTR[((64+256))+rsi]
	vpxor	ymm9,ymm9,YMMWORD PTR[((96+256))+rsi]
	vmovdqu	YMMWORD PTR[(0+256)+rdi],ymm3
	vmovdqu	YMMWORD PTR[(32+256)+rdi],ymm1
	vmovdqu	YMMWORD PTR[(64+256)+rdi],ymm5
	vmovdqu	YMMWORD PTR[(96+256)+rdi],ymm9
	mov	rax,QWORD PTR[((0+160+0))+rbp]
	mov	r15,rax
	mul	r10
	mov	r13,rax
	mov	r14,rdx
	mov	rax,QWORD PTR[((0+160+0))+rbp]
	mul	r11
	imul	r15,r12
	add	r14,rax
	adc	r15,rdx
	mov	rax,QWORD PTR[((8+160+0))+rbp]
	mov	r9,rax
	mul	r10
	add	r14,rax
	adc	rdx,0
	mov	r10,rdx
	mov	rax,QWORD PTR[((8+160+0))+rbp]
	mul	r11
	add	r15,rax
	adc	rdx,0
	imul	r9,r12
	add	r15,r10
	adc	r9,rdx
	mov	r10,r13
	mov	r11,r14
	mov	r12,r15
	and	r12,3
	mov	r13,r15
	and	r13,-4
	mov	r14,r9
	shrd	r15,r9,2
	shr	r9,2
	add	r15,r13
	adc	r9,r14
	add	r10,r15
	adc	r11,r9
	adc	r12,0
	vperm2i128	ymm3,ymm4,ymm0,002h
	vperm2i128	ymm4,ymm4,ymm0,013h
	vperm2i128	ymm0,ymm12,ymm8,002h
	vperm2i128	ymm8,ymm12,ymm8,013h
	vpxor	ymm3,ymm3,YMMWORD PTR[((0+384))+rsi]
	vpxor	ymm0,ymm0,YMMWORD PTR[((32+384))+rsi]
	vpxor	ymm4,ymm4,YMMWORD PTR[((64+384))+rsi]
	vpxor	ymm8,ymm8,YMMWORD PTR[((96+384))+rsi]
	vmovdqu	YMMWORD PTR[(0+384)+rdi],ymm3
	vmovdqu	YMMWORD PTR[(32+384)+rdi],ymm0
	vmovdqu	YMMWORD PTR[(64+384)+rdi],ymm4
	vmovdqu	YMMWORD PTR[(96+384)+rdi],ymm8

	lea	rsi,QWORD PTR[512+rsi]
	lea	rdi,QWORD PTR[512+rdi]
	sub	rbx,16*32
	jmp	$L$open_avx2_main_loop
$L$open_avx2_main_loop_done::
	test	rbx,rbx
	vzeroupper
	je	$L$open_sse_finalize

	cmp	rbx,12*32
	ja	$L$open_avx2_tail_512
	cmp	rbx,8*32
	ja	$L$open_avx2_tail_384
	cmp	rbx,4*32
	ja	$L$open_avx2_tail_256
	vmovdqa	ymm0,YMMWORD PTR[$L$chacha20_consts]
	vmovdqa	ymm4,YMMWORD PTR[((160+64))+rbp]
	vmovdqa	ymm8,YMMWORD PTR[((160+96))+rbp]
	vmovdqa	ymm12,YMMWORD PTR[$L$avx2_inc]
	vpaddd	ymm12,ymm12,YMMWORD PTR[((160+160))+rbp]
	vmovdqa	YMMWORD PTR[(160+160)+rbp],ymm12

	xor	r8,r8
	mov	rcx,rbx
	and	rcx,-16
	test	rcx,rcx
	je	$L$open_avx2_tail_128_rounds
$L$open_avx2_tail_128_rounds_and_x1hash::
	add	r10,QWORD PTR[((0+0))+r8*1+rsi]
	adc	r11,QWORD PTR[((8+0))+r8*1+rsi]
	adc	r12,1
	mov	rax,QWORD PTR[((0+160+0))+rbp]
	mov	r15,rax
	mul	r10
	mov	r13,rax
	mov	r14,rdx
	mov	rax,QWORD PTR[((0+160+0))+rbp]
	mul	r11
	imul	r15,r12
	add	r14,rax
	adc	r15,rdx
	mov	rax,QWORD PTR[((8+160+0))+rbp]
	mov	r9,rax
	mul	r10
	add	r14,rax
	adc	rdx,0
	mov	r10,rdx
	mov	rax,QWORD PTR[((8+160+0))+rbp]
	mul	r11
	add	r15,rax
	adc	rdx,0
	imul	r9,r12
	add	r15,r10
	adc	r9,rdx
	mov	r10,r13
	mov	r11,r14
	mov	r12,r15
	and	r12,3
	mov	r13,r15
	and	r13,-4
	mov	r14,r9
	shrd	r15,r9,2
	shr	r9,2
	add	r15,r13
	adc	r9,r14
	add	r10,r15
	adc	r11,r9
	adc	r12,0

$L$open_avx2_tail_128_rounds::
	add	r8,16
	vpaddd	ymm0,ymm0,ymm4
	vpxor	ymm12,ymm12,ymm0
	vpshufb	ymm12,ymm12,YMMWORD PTR[$L$rol16]
	vpaddd	ymm8,ymm8,ymm12
	vpxor	ymm4,ymm4,ymm8
	vpsrld	ymm3,ymm4,20
	vpslld	ymm4,ymm4,12
	vpxor	ymm4,ymm4,ymm3
	vpaddd	ymm0,ymm0,ymm4
	vpxor	ymm12,ymm12,ymm0
	vpshufb	ymm12,ymm12,YMMWORD PTR[$L$rol8]
	vpaddd	ymm8,ymm8,ymm12
	vpxor	ymm4,ymm4,ymm8
	vpslld	ymm3,ymm4,7
	vpsrld	ymm4,ymm4,25
	vpxor	ymm4,ymm4,ymm3
	vpalignr	ymm12,ymm12,ymm12,12
	vpalignr	ymm8,ymm8,ymm8,8
	vpalignr	ymm4,ymm4,ymm4,4
	vpaddd	ymm0,ymm0,ymm4
	vpxor	ymm12,ymm12,ymm0
	vpshufb	ymm12,ymm12,YMMWORD PTR[$L$rol16]
	vpaddd	ymm8,ymm8,ymm12
	vpxor	ymm4,ymm4,ymm8
	vpsrld	ymm3,ymm4,20
	vpslld	ymm4,ymm4,12
	vpxor	ymm4,ymm4,ymm3
	vpaddd	ymm0,ymm0,ymm4
	vpxor	ymm12,ymm12,ymm0
	vpshufb	ymm12,ymm12,YMMWORD PTR[$L$rol8]
	vpaddd	ymm8,ymm8,ymm12
	vpxor	ymm4,ymm4,ymm8
	vpslld	ymm3,ymm4,7
	vpsrld	ymm4,ymm4,25
	vpxor	ymm4,ymm4,ymm3
	vpalignr	ymm12,ymm12,ymm12,4
	vpalignr	ymm8,ymm8,ymm8,8
	vpalignr	ymm4,ymm4,ymm4,12

	cmp	r8,rcx
	jb	$L$open_avx2_tail_128_rounds_and_x1hash
	cmp	r8,160
	jne	$L$open_avx2_tail_128_rounds
	vpaddd	ymm0,ymm0,YMMWORD PTR[$L$chacha20_consts]
	vpaddd	ymm4,ymm4,YMMWORD PTR[((160+64))+rbp]
	vpaddd	ymm8,ymm8,YMMWORD PTR[((160+96))+rbp]
	vpaddd	ymm12,ymm12,YMMWORD PTR[((160+160))+rbp]
	vperm2i128	ymm3,ymm4,ymm0,013h
	vperm2i128	ymm0,ymm4,ymm0,002h
	vperm2i128	ymm4,ymm12,ymm8,002h
	vperm2i128	ymm12,ymm12,ymm8,013h
	vmovdqa	ymm8,ymm3

	jmp	$L$open_avx2_tail_128_xor

$L$open_avx2_tail_256::
	vmovdqa	ymm0,YMMWORD PTR[$L$chacha20_consts]
	vmovdqa	ymm4,YMMWORD PTR[((160+64))+rbp]
	vmovdqa	ymm8,YMMWORD PTR[((160+96))+rbp]
	vmovdqa	ymm1,ymm0
	vmovdqa	ymm5,ymm4
	vmovdqa	ymm9,ymm8
	vmovdqa	ymm12,YMMWORD PTR[$L$avx2_inc]
	vpaddd	ymm13,ymm12,YMMWORD PTR[((160+160))+rbp]
	vpaddd	ymm12,ymm12,ymm13
	vmovdqa	YMMWORD PTR[(160+160)+rbp],ymm12
	vmovdqa	YMMWORD PTR[(160+192)+rbp],ymm13

	mov	QWORD PTR[((160+128))+rbp],rbx
	mov	rcx,rbx
	sub	rcx,4*32
	shr	rcx,4
	mov	r8,10
	cmp	rcx,10
	cmovg	rcx,r8
	mov	rbx,rsi
	xor	r8,r8
$L$open_avx2_tail_256_rounds_and_x1hash::
	add	r10,QWORD PTR[((0+0))+rbx]
	adc	r11,QWORD PTR[((8+0))+rbx]
	adc	r12,1
	mov	rdx,QWORD PTR[((0+160+0))+rbp]
	mov	r15,rdx
	mulx	r14,r13,r10
	mulx	rdx,rax,r11
	imul	r15,r12
	add	r14,rax
	adc	r15,rdx
	mov	rdx,QWORD PTR[((8+160+0))+rbp]
	mulx	rax,r10,r10
	add	r14,r10
	mulx	r9,r11,r11
	adc	r15,r11
	adc	r9,0
	imul	rdx,r12
	add	r15,rax
	adc	r9,rdx
	mov	r10,r13
	mov	r11,r14
	mov	r12,r15
	and	r12,3
	mov	r13,r15
	and	r13,-4
	mov	r14,r9
	shrd	r15,r9,2
	shr	r9,2
	add	r15,r13
	adc	r9,r14
	add	r10,r15
	adc	r11,r9
	adc	r12,0

	lea	rbx,QWORD PTR[16+rbx]
$L$open_avx2_tail_256_rounds::
	vpaddd	ymm0,ymm0,ymm4
	vpxor	ymm12,ymm12,ymm0
	vpshufb	ymm12,ymm12,YMMWORD PTR[$L$rol16]
	vpaddd	ymm8,ymm8,ymm12
	vpxor	ymm4,ymm4,ymm8
	vpsrld	ymm3,ymm4,20
	vpslld	ymm4,ymm4,12
	vpxor	ymm4,ymm4,ymm3
	vpaddd	ymm0,ymm0,ymm4
	vpxor	ymm12,ymm12,ymm0
	vpshufb	ymm12,ymm12,YMMWORD PTR[$L$rol8]
	vpaddd	ymm8,ymm8,ymm12
	vpxor	ymm4,ymm4,ymm8
	vpslld	ymm3,ymm4,7
	vpsrld	ymm4,ymm4,25
	vpxor	ymm4,ymm4,ymm3
	vpalignr	ymm12,ymm12,ymm12,12
	vpalignr	ymm8,ymm8,ymm8,8
	vpalignr	ymm4,ymm4,ymm4,4
	vpaddd	ymm1,ymm1,ymm5
	vpxor	ymm13,ymm13,ymm1
	vpshufb	ymm13,ymm13,YMMWORD PTR[$L$rol16]
	vpaddd	ymm9,ymm9,ymm13
	vpxor	ymm5,ymm5,ymm9
	vpsrld	ymm3,ymm5,20
	vpslld	ymm5,ymm5,12
	vpxor	ymm5,ymm5,ymm3
	vpaddd	ymm1,ymm1,ymm5
	vpxor	ymm13,ymm13,ymm1
	vpshufb	ymm13,ymm13,YMMWORD PTR[$L$rol8]
	vpaddd	ymm9,ymm9,ymm13
	vpxor	ymm5,ymm5,ymm9
	vpslld	ymm3,ymm5,7
	vpsrld	ymm5,ymm5,25
	vpxor	ymm5,ymm5,ymm3
	vpalignr	ymm13,ymm13,ymm13,12
	vpalignr	ymm9,ymm9,ymm9,8
	vpalignr	ymm5,ymm5,ymm5,4

	inc	r8
	vpaddd	ymm0,ymm0,ymm4
	vpxor	ymm12,ymm12,ymm0
	vpshufb	ymm12,ymm12,YMMWORD PTR[$L$rol16]
	vpaddd	ymm8,ymm8,ymm12
	vpxor	ymm4,ymm4,ymm8
	vpsrld	ymm3,ymm4,20
	vpslld	ymm4,ymm4,12
	vpxor	ymm4,ymm4,ymm3
	vpaddd	ymm0,ymm0,ymm4
	vpxor	ymm12,ymm12,ymm0
	vpshufb	ymm12,ymm12,YMMWORD PTR[$L$rol8]
	vpaddd	ymm8,ymm8,ymm12
	vpxor	ymm4,ymm4,ymm8
	vpslld	ymm3,ymm4,7
	vpsrld	ymm4,ymm4,25
	vpxor	ymm4,ymm4,ymm3
	vpalignr	ymm12,ymm12,ymm12,4
	vpalignr	ymm8,ymm8,ymm8,8
	vpalignr	ymm4,ymm4,ymm4,12
	vpaddd	ymm1,ymm1,ymm5
	vpxor	ymm13,ymm13,ymm1
	vpshufb	ymm13,ymm13,YMMWORD PTR[$L$rol16]
	vpaddd	ymm9,ymm9,ymm13
	vpxor	ymm5,ymm5,ymm9
	vpsrld	ymm3,ymm5,20
	vpslld	ymm5,ymm5,12
	vpxor	ymm5,ymm5,ymm3
	vpaddd	ymm1,ymm1,ymm5
	vpxor	ymm13,ymm13,ymm1
	vpshufb	ymm13,ymm13,YMMWORD PTR[$L$rol8]
	vpaddd	ymm9,ymm9,ymm13
	vpxor	ymm5,ymm5,ymm9
	vpslld	ymm3,ymm5,7
	vpsrld	ymm5,ymm5,25
	vpxor	ymm5,ymm5,ymm3
	vpalignr	ymm13,ymm13,ymm13,4
	vpalignr	ymm9,ymm9,ymm9,8
	vpalignr	ymm5,ymm5,ymm5,12
	vpaddd	ymm2,ymm2,ymm6
	vpxor	ymm14,ymm14,ymm2
	vpshufb	ymm14,ymm14,YMMWORD PTR[$L$rol16]
	vpaddd	ymm10,ymm10,ymm14
	vpxor	ymm6,ymm6,ymm10
	vpsrld	ymm3,ymm6,20
	vpslld	ymm6,ymm6,12
	vpxor	ymm6,ymm6,ymm3
	vpaddd	ymm2,ymm2,ymm6
	vpxor	ymm14,ymm14,ymm2
	vpshufb	ymm14,ymm14,YMMWORD PTR[$L$rol8]
	vpaddd	ymm10,ymm10,ymm14
	vpxor	ymm6,ymm6,ymm10
	vpslld	ymm3,ymm6,7
	vpsrld	ymm6,ymm6,25
	vpxor	ymm6,ymm6,ymm3
	vpalignr	ymm14,ymm14,ymm14,4
	vpalignr	ymm10,ymm10,ymm10,8
	vpalignr	ymm6,ymm6,ymm6,12

	cmp	r8,rcx
	jb	$L$open_avx2_tail_256_rounds_and_x1hash
	cmp	r8,10
	jne	$L$open_avx2_tail_256_rounds
	mov	r8,rbx
	sub	rbx,rsi
	mov	rcx,rbx
	mov	rbx,QWORD PTR[((160+128))+rbp]
$L$open_avx2_tail_256_hash::
	add	rcx,16
	cmp	rcx,rbx
	jg	$L$open_avx2_tail_256_done
	add	r10,QWORD PTR[((0+0))+r8]
	adc	r11,QWORD PTR[((8+0))+r8]
	adc	r12,1
	mov	rdx,QWORD PTR[((0+160+0))+rbp]
	mov	r15,rdx
	mulx	r14,r13,r10
	mulx	rdx,rax,r11
	imul	r15,r12
	add	r14,rax
	adc	r15,rdx
	mov	rdx,QWORD PTR[((8+160+0))+rbp]
	mulx	rax,r10,r10
	add	r14,r10
	mulx	r9,r11,r11
	adc	r15,r11
	adc	r9,0
	imul	rdx,r12
	add	r15,rax
	adc	r9,rdx
	mov	r10,r13
	mov	r11,r14
	mov	r12,r15
	and	r12,3
	mov	r13,r15
	and	r13,-4
	mov	r14,r9
	shrd	r15,r9,2
	shr	r9,2
	add	r15,r13
	adc	r9,r14
	add	r10,r15
	adc	r11,r9
	adc	r12,0

	lea	r8,QWORD PTR[16+r8]
	jmp	$L$open_avx2_tail_256_hash
$L$open_avx2_tail_256_done::
	vpaddd	ymm1,ymm1,YMMWORD PTR[$L$chacha20_consts]
	vpaddd	ymm5,ymm5,YMMWORD PTR[((160+64))+rbp]
	vpaddd	ymm9,ymm9,YMMWORD PTR[((160+96))+rbp]
	vpaddd	ymm13,ymm13,YMMWORD PTR[((160+192))+rbp]
	vpaddd	ymm0,ymm0,YMMWORD PTR[$L$chacha20_consts]
	vpaddd	ymm4,ymm4,YMMWORD PTR[((160+64))+rbp]
	vpaddd	ymm8,ymm8,YMMWORD PTR[((160+96))+rbp]
	vpaddd	ymm12,ymm12,YMMWORD PTR[((160+160))+rbp]
	vperm2i128	ymm3,ymm5,ymm1,002h
	vperm2i128	ymm5,ymm5,ymm1,013h
	vperm2i128	ymm1,ymm13,ymm9,002h
	vperm2i128	ymm9,ymm13,ymm9,013h
	vpxor	ymm3,ymm3,YMMWORD PTR[((0+0))+rsi]
	vpxor	ymm1,ymm1,YMMWORD PTR[((32+0))+rsi]
	vpxor	ymm5,ymm5,YMMWORD PTR[((64+0))+rsi]
	vpxor	ymm9,ymm9,YMMWORD PTR[((96+0))+rsi]
	vmovdqu	YMMWORD PTR[(0+0)+rdi],ymm3
	vmovdqu	YMMWORD PTR[(32+0)+rdi],ymm1
	vmovdqu	YMMWORD PTR[(64+0)+rdi],ymm5
	vmovdqu	YMMWORD PTR[(96+0)+rdi],ymm9
	vperm2i128	ymm3,ymm4,ymm0,013h
	vperm2i128	ymm0,ymm4,ymm0,002h
	vperm2i128	ymm4,ymm12,ymm8,002h
	vperm2i128	ymm12,ymm12,ymm8,013h
	vmovdqa	ymm8,ymm3

	lea	rsi,QWORD PTR[128+rsi]
	lea	rdi,QWORD PTR[128+rdi]
	sub	rbx,4*32
	jmp	$L$open_avx2_tail_128_xor

$L$open_avx2_tail_384::
	vmovdqa	ymm0,YMMWORD PTR[$L$chacha20_consts]
	vmovdqa	ymm4,YMMWORD PTR[((160+64))+rbp]
	vmovdqa	ymm8,YMMWORD PTR[((160+96))+rbp]
	vmovdqa	ymm1,ymm0
	vmovdqa	ymm5,ymm4
	vmovdqa	ymm9,ymm8
	vmovdqa	ymm2,ymm0
	vmovdqa	ymm6,ymm4
	vmovdqa	ymm10,ymm8
	vmovdqa	ymm12,YMMWORD PTR[$L$avx2_inc]
	vpaddd	ymm14,ymm12,YMMWORD PTR[((160+160))+rbp]
	vpaddd	ymm13,ymm12,ymm14
	vpaddd	ymm12,ymm12,ymm13
	vmovdqa	YMMWORD PTR[(160+160)+rbp],ymm12
	vmovdqa	YMMWORD PTR[(160+192)+rbp],ymm13
	vmovdqa	YMMWORD PTR[(160+224)+rbp],ymm14

	mov	QWORD PTR[((160+128))+rbp],rbx
	mov	rcx,rbx
	sub	rcx,8*32
	shr	rcx,4
	add	rcx,6
	mov	r8,10
	cmp	rcx,10
	cmovg	rcx,r8
	mov	rbx,rsi
	xor	r8,r8
$L$open_avx2_tail_384_rounds_and_x2hash::
	add	r10,QWORD PTR[((0+0))+rbx]
	adc	r11,QWORD PTR[((8+0))+rbx]
	adc	r12,1
	mov	rdx,QWORD PTR[((0+160+0))+rbp]
	mov	r15,rdx
	mulx	r14,r13,r10
	mulx	rdx,rax,r11
	imul	r15,r12
	add	r14,rax
	adc	r15,rdx
	mov	rdx,QWORD PTR[((8+160+0))+rbp]
	mulx	rax,r10,r10
	add	r14,r10
	mulx	r9,r11,r11
	adc	r15,r11
	adc	r9,0
	imul	rdx,r12
	add	r15,rax
	adc	r9,rdx
	mov	r10,r13
	mov	r11,r14
	mov	r12,r15
	and	r12,3
	mov	r13,r15
	and	r13,-4
	mov	r14,r9
	shrd	r15,r9,2
	shr	r9,2
	add	r15,r13
	adc	r9,r14
	add	r10,r15
	adc	r11,r9
	adc	r12,0

	lea	rbx,QWORD PTR[16+rbx]
$L$open_avx2_tail_384_rounds_and_x1hash::
	vpaddd	ymm2,ymm2,ymm6
	vpxor	ymm14,ymm14,ymm2
	vpshufb	ymm14,ymm14,YMMWORD PTR[$L$rol16]
	vpaddd	ymm10,ymm10,ymm14
	vpxor	ymm6,ymm6,ymm10
	vpsrld	ymm3,ymm6,20
	vpslld	ymm6,ymm6,12
	vpxor	ymm6,ymm6,ymm3
	vpaddd	ymm2,ymm2,ymm6
	vpxor	ymm14,ymm14,ymm2
	vpshufb	ymm14,ymm14,YMMWORD PTR[$L$rol8]
	vpaddd	ymm10,ymm10,ymm14
	vpxor	ymm6,ymm6,ymm10
	vpslld	ymm3,ymm6,7
	vpsrld	ymm6,ymm6,25
	vpxor	ymm6,ymm6,ymm3
	vpalignr	ymm14,ymm14,ymm14,12
	vpalignr	ymm10,ymm10,ymm10,8
	vpalignr	ymm6,ymm6,ymm6,4
	vpaddd	ymm1,ymm1,ymm5
	vpxor	ymm13,ymm13,ymm1
	vpshufb	ymm13,ymm13,YMMWORD PTR[$L$rol16]
	vpaddd	ymm9,ymm9,ymm13
	vpxor	ymm5,ymm5,ymm9
	vpsrld	ymm3,ymm5,20
	vpslld	ymm5,ymm5,12
	vpxor	ymm5,ymm5,ymm3
	vpaddd	ymm1,ymm1,ymm5
	vpxor	ymm13,ymm13,ymm1
	vpshufb	ymm13,ymm13,YMMWORD PTR[$L$rol8]
	vpaddd	ymm9,ymm9,ymm13
	vpxor	ymm5,ymm5,ymm9
	vpslld	ymm3,ymm5,7
	vpsrld	ymm5,ymm5,25
	vpxor	ymm5,ymm5,ymm3
	vpalignr	ymm13,ymm13,ymm13,12
	vpalignr	ymm9,ymm9,ymm9,8
	vpalignr	ymm5,ymm5,ymm5,4
	vpaddd	ymm0,ymm0,ymm4
	vpxor	ymm12,ymm12,ymm0
	vpshufb	ymm12,ymm12,YMMWORD PTR[$L$rol16]
	vpaddd	ymm8,ymm8,ymm12
	vpxor	ymm4,ymm4,ymm8
	vpsrld	ymm3,ymm4,20
	vpslld	ymm4,ymm4,12
	vpxor	ymm4,ymm4,ymm3
	vpaddd	ymm0,ymm0,ymm4
	vpxor	ymm12,ymm12,ymm0
	vpshufb	ymm12,ymm12,YMMWORD PTR[$L$rol8]
	vpaddd	ymm8,ymm8,ymm12
	vpxor	ymm4,ymm4,ymm8
	vpslld	ymm3,ymm4,7
	vpsrld	ymm4,ymm4,25
	vpxor	ymm4,ymm4,ymm3
	vpalignr	ymm12,ymm12,ymm12,12
	vpalignr	ymm8,ymm8,ymm8,8
	vpalignr	ymm4,ymm4,ymm4,4
	add	r10,QWORD PTR[((0+0))+rbx]
	adc	r11,QWORD PTR[((8+0))+rbx]
	adc	r12,1
	mov	rax,QWORD PTR[((0+160+0))+rbp]
	mov	r15,rax
	mul	r10
	mov	r13,rax
	mov	r14,rdx
	mov	rax,QWORD PTR[((0+160+0))+rbp]
	mul	r11
	imul	r15,r12
	add	r14,rax
	adc	r15,rdx
	mov	rax,QWORD PTR[((8+160+0))+rbp]
	mov	r9,rax
	mul	r10
	add	r14,rax
	adc	rdx,0
	mov	r10,rdx
	mov	rax,QWORD PTR[((8+160+0))+rbp]
	mul	r11
	add	r15,rax
	adc	rdx,0
	imul	r9,r12
	add	r15,r10
	adc	r9,rdx
	mov	r10,r13
	mov	r11,r14
	mov	r12,r15
	and	r12,3
	mov	r13,r15
	and	r13,-4
	mov	r14,r9
	shrd	r15,r9,2
	shr	r9,2
	add	r15,r13
	adc	r9,r14
	add	r10,r15
	adc	r11,r9
	adc	r12,0

	lea	rbx,QWORD PTR[16+rbx]
	inc	r8
	vpaddd	ymm2,ymm2,ymm6
	vpxor	ymm14,ymm14,ymm2
	vpshufb	ymm14,ymm14,YMMWORD PTR[$L$rol16]
	vpaddd	ymm10,ymm10,ymm14
	vpxor	ymm6,ymm6,ymm10
	vpsrld	ymm3,ymm6,20
	vpslld	ymm6,ymm6,12
	vpxor	ymm6,ymm6,ymm3
	vpaddd	ymm2,ymm2,ymm6
	vpxor	ymm14,ymm14,ymm2
	vpshufb	ymm14,ymm14,YMMWORD PTR[$L$rol8]
	vpaddd	ymm10,ymm10,ymm14
	vpxor	ymm6,ymm6,ymm10
	vpslld	ymm3,ymm6,7
	vpsrld	ymm6,ymm6,25
	vpxor	ymm6,ymm6,ymm3
	vpalignr	ymm14,ymm14,ymm14,4
	vpalignr	ymm10,ymm10,ymm10,8
	vpalignr	ymm6,ymm6,ymm6,12
	vpaddd	ymm1,ymm1,ymm5
	vpxor	ymm13,ymm13,ymm1
	vpshufb	ymm13,ymm13,YMMWORD PTR[$L$rol16]
	vpaddd	ymm9,ymm9,ymm13
	vpxor	ymm5,ymm5,ymm9
	vpsrld	ymm3,ymm5,20
	vpslld	ymm5,ymm5,12
	vpxor	ymm5,ymm5,ymm3
	vpaddd	ymm1,ymm1,ymm5
	vpxor	ymm13,ymm13,ymm1
	vpshufb	ymm13,ymm13,YMMWORD PTR[$L$rol8]
	vpaddd	ymm9,ymm9,ymm13
	vpxor	ymm5,ymm5,ymm9
	vpslld	ymm3,ymm5,7
	vpsrld	ymm5,ymm5,25
	vpxor	ymm5,ymm5,ymm3
	vpalignr	ymm13,ymm13,ymm13,4
	vpalignr	ymm9,ymm9,ymm9,8
	vpalignr	ymm5,ymm5,ymm5,12
	vpaddd	ymm0,ymm0,ymm4
	vpxor	ymm12,ymm12,ymm0
	vpshufb	ymm12,ymm12,YMMWORD PTR[$L$rol16]
	vpaddd	ymm8,ymm8,ymm12
	vpxor	ymm4,ymm4,ymm8
	vpsrld	ymm3,ymm4,20
	vpslld	ymm4,ymm4,12
	vpxor	ymm4,ymm4,ymm3
	vpaddd	ymm0,ymm0,ymm4
	vpxor	ymm12,ymm12,ymm0
	vpshufb	ymm12,ymm12,YMMWORD PTR[$L$rol8]
	vpaddd	ymm8,ymm8,ymm12
	vpxor	ymm4,ymm4,ymm8
	vpslld	ymm3,ymm4,7
	vpsrld	ymm4,ymm4,25
	vpxor	ymm4,ymm4,ymm3
	vpalignr	ymm12,ymm12,ymm12,4
	vpalignr	ymm8,ymm8,ymm8,8
	vpalignr	ymm4,ymm4,ymm4,12

	cmp	r8,rcx
	jb	$L$open_avx2_tail_384_rounds_and_x2hash
	cmp	r8,10
	jne	$L$open_avx2_tail_384_rounds_and_x1hash
	mov	r8,rbx
	sub	rbx,rsi
	mov	rcx,rbx
	mov	rbx,QWORD PTR[((160+128))+rbp]
$L$open_avx2_384_tail_hash::
	add	rcx,16
	cmp	rcx,rbx
	jg	$L$open_avx2_384_tail_done
	add	r10,QWORD PTR[((0+0))+r8]
	adc	r11,QWORD PTR[((8+0))+r8]
	adc	r12,1
	mov	rdx,QWORD PTR[((0+160+0))+rbp]
	mov	r15,rdx
	mulx	r14,r13,r10
	mulx	rdx,rax,r11
	imul	r15,r12
	add	r14,rax
	adc	r15,rdx
	mov	rdx,QWORD PTR[((8+160+0))+rbp]
	mulx	rax,r10,r10
	add	r14,r10
	mulx	r9,r11,r11
	adc	r15,r11
	adc	r9,0
	imul	rdx,r12
	add	r15,rax
	adc	r9,rdx
	mov	r10,r13
	mov	r11,r14
	mov	r12,r15
	and	r12,3
	mov	r13,r15
	and	r13,-4
	mov	r14,r9
	shrd	r15,r9,2
	shr	r9,2
	add	r15,r13
	adc	r9,r14
	add	r10,r15
	adc	r11,r9
	adc	r12,0

	lea	r8,QWORD PTR[16+r8]
	jmp	$L$open_avx2_384_tail_hash
$L$open_avx2_384_tail_done::
	vpaddd	ymm2,ymm2,YMMWORD PTR[$L$chacha20_consts]
	vpaddd	ymm6,ymm6,YMMWORD PTR[((160+64))+rbp]
	vpaddd	ymm10,ymm10,YMMWORD PTR[((160+96))+rbp]
	vpaddd	ymm14,ymm14,YMMWORD PTR[((160+224))+rbp]
	vpaddd	ymm1,ymm1,YMMWORD PTR[$L$chacha20_consts]
	vpaddd	ymm5,ymm5,YMMWORD PTR[((160+64))+rbp]
	vpaddd	ymm9,ymm9,YMMWORD PTR[((160+96))+rbp]
	vpaddd	ymm13,ymm13,YMMWORD PTR[((160+192))+rbp]
	vpaddd	ymm0,ymm0,YMMWORD PTR[$L$chacha20_consts]
	vpaddd	ymm4,ymm4,YMMWORD PTR[((160+64))+rbp]
	vpaddd	ymm8,ymm8,YMMWORD PTR[((160+96))+rbp]
	vpaddd	ymm12,ymm12,YMMWORD PTR[((160+160))+rbp]
	vperm2i128	ymm3,ymm6,ymm2,002h
	vperm2i128	ymm6,ymm6,ymm2,013h
	vperm2i128	ymm2,ymm14,ymm10,002h
	vperm2i128	ymm10,ymm14,ymm10,013h
	vpxor	ymm3,ymm3,YMMWORD PTR[((0+0))+rsi]
	vpxor	ymm2,ymm2,YMMWORD PTR[((32+0))+rsi]
	vpxor	ymm6,ymm6,YMMWORD PTR[((64+0))+rsi]
	vpxor	ymm10,ymm10,YMMWORD PTR[((96+0))+rsi]
	vmovdqu	YMMWORD PTR[(0+0)+rdi],ymm3
	vmovdqu	YMMWORD PTR[(32+0)+rdi],ymm2
	vmovdqu	YMMWORD PTR[(64+0)+rdi],ymm6
	vmovdqu	YMMWORD PTR[(96+0)+rdi],ymm10
	vperm2i128	ymm3,ymm5,ymm1,002h
	vperm2i128	ymm5,ymm5,ymm1,013h
	vperm2i128	ymm1,ymm13,ymm9,002h
	vperm2i128	ymm9,ymm13,ymm9,013h
	vpxor	ymm3,ymm3,YMMWORD PTR[((0+128))+rsi]
	vpxor	ymm1,ymm1,YMMWORD PTR[((32+128))+rsi]
	vpxor	ymm5,ymm5,YMMWORD PTR[((64+128))+rsi]
	vpxor	ymm9,ymm9,YMMWORD PTR[((96+128))+rsi]
	vmovdqu	YMMWORD PTR[(0+128)+rdi],ymm3
	vmovdqu	YMMWORD PTR[(32+128)+rdi],ymm1
	vmovdqu	YMMWORD PTR[(64+128)+rdi],ymm5
	vmovdqu	YMMWORD PTR[(96+128)+rdi],ymm9
	vperm2i128	ymm3,ymm4,ymm0,013h
	vperm2i128	ymm0,ymm4,ymm0,002h
	vperm2i128	ymm4,ymm12,ymm8,002h
	vperm2i128	ymm12,ymm12,ymm8,013h
	vmovdqa	ymm8,ymm3

	lea	rsi,QWORD PTR[256+rsi]
	lea	rdi,QWORD PTR[256+rdi]
	sub	rbx,8*32
	jmp	$L$open_avx2_tail_128_xor

$L$open_avx2_tail_512::
	vmovdqa	ymm0,YMMWORD PTR[$L$chacha20_consts]
	vmovdqa	ymm4,YMMWORD PTR[((160+64))+rbp]
	vmovdqa	ymm8,YMMWORD PTR[((160+96))+rbp]
	vmovdqa	ymm1,ymm0
	vmovdqa	ymm5,ymm4
	vmovdqa	ymm9,ymm8
	vmovdqa	ymm2,ymm0
	vmovdqa	ymm6,ymm4
	vmovdqa	ymm10,ymm8
	vmovdqa	ymm3,ymm0
	vmovdqa	ymm7,ymm4
	vmovdqa	ymm11,ymm8
	vmovdqa	ymm12,YMMWORD PTR[$L$avx2_inc]
	vpaddd	ymm15,ymm12,YMMWORD PTR[((160+160))+rbp]
	vpaddd	ymm14,ymm12,ymm15
	vpaddd	ymm13,ymm12,ymm14
	vpaddd	ymm12,ymm12,ymm13
	vmovdqa	YMMWORD PTR[(160+256)+rbp],ymm15
	vmovdqa	YMMWORD PTR[(160+224)+rbp],ymm14
	vmovdqa	YMMWORD PTR[(160+192)+rbp],ymm13
	vmovdqa	YMMWORD PTR[(160+160)+rbp],ymm12

	xor	rcx,rcx
	mov	r8,rsi
$L$open_avx2_tail_512_rounds_and_x2hash::
	add	r10,QWORD PTR[((0+0))+r8]
	adc	r11,QWORD PTR[((8+0))+r8]
	adc	r12,1
	mov	rax,QWORD PTR[((0+160+0))+rbp]
	mov	r15,rax
	mul	r10
	mov	r13,rax
	mov	r14,rdx
	mov	rax,QWORD PTR[((0+160+0))+rbp]
	mul	r11
	imul	r15,r12
	add	r14,rax
	adc	r15,rdx
	mov	rax,QWORD PTR[((8+160+0))+rbp]
	mov	r9,rax
	mul	r10
	add	r14,rax
	adc	rdx,0
	mov	r10,rdx
	mov	rax,QWORD PTR[((8+160+0))+rbp]
	mul	r11
	add	r15,rax
	adc	rdx,0
	imul	r9,r12
	add	r15,r10
	adc	r9,rdx
	mov	r10,r13
	mov	r11,r14
	mov	r12,r15
	and	r12,3
	mov	r13,r15
	and	r13,-4
	mov	r14,r9
	shrd	r15,r9,2
	shr	r9,2
	add	r15,r13
	adc	r9,r14
	add	r10,r15
	adc	r11,r9
	adc	r12,0

	lea	r8,QWORD PTR[16+r8]
$L$open_avx2_tail_512_rounds_and_x1hash::
	vmovdqa	YMMWORD PTR[(160+128)+rbp],ymm8
	vmovdqa	ymm8,YMMWORD PTR[$L$rol16]
	vpaddd	ymm3,ymm3,ymm7
	vpaddd	ymm2,ymm2,ymm6
	vpaddd	ymm1,ymm1,ymm5
	vpaddd	ymm0,ymm0,ymm4
	vpxor	ymm15,ymm15,ymm3
	vpxor	ymm14,ymm14,ymm2
	vpxor	ymm13,ymm13,ymm1
	vpxor	ymm12,ymm12,ymm0
	vpshufb	ymm15,ymm15,ymm8
	vpshufb	ymm14,ymm14,ymm8
	vpshufb	ymm13,ymm13,ymm8
	vpshufb	ymm12,ymm12,ymm8
	vpaddd	ymm11,ymm11,ymm15
	vpaddd	ymm10,ymm10,ymm14
	vpaddd	ymm9,ymm9,ymm13
	vpaddd	ymm8,ymm12,YMMWORD PTR[((160+128))+rbp]
	vpxor	ymm7,ymm7,ymm11
	vpxor	ymm6,ymm6,ymm10
	vpxor	ymm5,ymm5,ymm9
	vpxor	ymm4,ymm4,ymm8
	vmovdqa	YMMWORD PTR[(160+128)+rbp],ymm8
	vpsrld	ymm8,ymm7,20
	vpslld	ymm7,ymm7,32-20
	vpxor	ymm7,ymm7,ymm8
	vpsrld	ymm8,ymm6,20
	vpslld	ymm6,ymm6,32-20
	vpxor	ymm6,ymm6,ymm8
	vpsrld	ymm8,ymm5,20
	vpslld	ymm5,ymm5,32-20
	vpxor	ymm5,ymm5,ymm8
	vpsrld	ymm8,ymm4,20
	vpslld	ymm4,ymm4,32-20
	vpxor	ymm4,ymm4,ymm8
	vmovdqa	ymm8,YMMWORD PTR[$L$rol8]
	vpaddd	ymm3,ymm3,ymm7
	add	r10,QWORD PTR[((0+0))+r8]
	adc	r11,QWORD PTR[((8+0))+r8]
	adc	r12,1
	mov	rdx,QWORD PTR[((0+160+0))+rbp]
	mov	r15,rdx
	mulx	r14,r13,r10
	mulx	rdx,rax,r11
	imul	r15,r12
	add	r14,rax
	adc	r15,rdx
	mov	rdx,QWORD PTR[((8+160+0))+rbp]
	mulx	rax,r10,r10
	add	r14,r10
	mulx	r9,r11,r11
	adc	r15,r11
	adc	r9,0
	imul	rdx,r12
	add	r15,rax
	adc	r9,rdx
	mov	r10,r13
	mov	r11,r14
	mov	r12,r15
	and	r12,3
	mov	r13,r15
	and	r13,-4
	mov	r14,r9
	shrd	r15,r9,2
	shr	r9,2
	add	r15,r13
	adc	r9,r14
	add	r10,r15
	adc	r11,r9
	adc	r12,0
	vpaddd	ymm2,ymm2,ymm6
	vpaddd	ymm1,ymm1,ymm5
	vpaddd	ymm0,ymm0,ymm4
	vpxor	ymm15,ymm15,ymm3
	vpxor	ymm14,ymm14,ymm2
	vpxor	ymm13,ymm13,ymm1
	vpxor	ymm12,ymm12,ymm0
	vpshufb	ymm15,ymm15,ymm8
	vpshufb	ymm14,ymm14,ymm8
	vpshufb	ymm13,ymm13,ymm8
	vpshufb	ymm12,ymm12,ymm8
	vpaddd	ymm11,ymm11,ymm15
	vpaddd	ymm10,ymm10,ymm14
	vpaddd	ymm9,ymm9,ymm13
	vpaddd	ymm8,ymm12,YMMWORD PTR[((160+128))+rbp]
	vpxor	ymm7,ymm7,ymm11
	vpxor	ymm6,ymm6,ymm10
	vpxor	ymm5,ymm5,ymm9
	vpxor	ymm4,ymm4,ymm8
	vmovdqa	YMMWORD PTR[(160+128)+rbp],ymm8
	vpsrld	ymm8,ymm7,25
	vpslld	ymm7,ymm7,32-25
	vpxor	ymm7,ymm7,ymm8
	vpsrld	ymm8,ymm6,25
	vpslld	ymm6,ymm6,32-25
	vpxor	ymm6,ymm6,ymm8
	vpsrld	ymm8,ymm5,25
	vpslld	ymm5,ymm5,32-25
	vpxor	ymm5,ymm5,ymm8
	vpsrld	ymm8,ymm4,25
	vpslld	ymm4,ymm4,32-25
	vpxor	ymm4,ymm4,ymm8
	vmovdqa	ymm8,YMMWORD PTR[((160+128))+rbp]
	vpalignr	ymm7,ymm7,ymm7,4
	vpalignr	ymm11,ymm11,ymm11,8
	vpalignr	ymm15,ymm15,ymm15,12
	vpalignr	ymm6,ymm6,ymm6,4
	vpalignr	ymm10,ymm10,ymm10,8
	vpalignr	ymm14,ymm14,ymm14,12
	vpalignr	ymm5,ymm5,ymm5,4
	vpalignr	ymm9,ymm9,ymm9,8
	vpalignr	ymm13,ymm13,ymm13,12
	vpalignr	ymm4,ymm4,ymm4,4
	vpalignr	ymm8,ymm8,ymm8,8
	vpalignr	ymm12,ymm12,ymm12,12
	vmovdqa	YMMWORD PTR[(160+128)+rbp],ymm8
	vmovdqa	ymm8,YMMWORD PTR[$L$rol16]
	vpaddd	ymm3,ymm3,ymm7
	add	r10,QWORD PTR[((0+16))+r8]
	adc	r11,QWORD PTR[((8+16))+r8]
	adc	r12,1
	mov	rdx,QWORD PTR[((0+160+0))+rbp]
	mov	r15,rdx
	mulx	r14,r13,r10
	mulx	rdx,rax,r11
	imul	r15,r12
	add	r14,rax
	adc	r15,rdx
	mov	rdx,QWORD PTR[((8+160+0))+rbp]
	mulx	rax,r10,r10
	add	r14,r10
	mulx	r9,r11,r11
	adc	r15,r11
	adc	r9,0
	imul	rdx,r12
	add	r15,rax
	adc	r9,rdx
	mov	r10,r13
	mov	r11,r14
	mov	r12,r15
	and	r12,3
	mov	r13,r15
	and	r13,-4
	mov	r14,r9
	shrd	r15,r9,2
	shr	r9,2
	add	r15,r13
	adc	r9,r14
	add	r10,r15
	adc	r11,r9
	adc	r12,0

	lea	r8,QWORD PTR[32+r8]
	vpaddd	ymm2,ymm2,ymm6
	vpaddd	ymm1,ymm1,ymm5
	vpaddd	ymm0,ymm0,ymm4
	vpxor	ymm15,ymm15,ymm3
	vpxor	ymm14,ymm14,ymm2
	vpxor	ymm13,ymm13,ymm1
	vpxor	ymm12,ymm12,ymm0
	vpshufb	ymm15,ymm15,ymm8
	vpshufb	ymm14,ymm14,ymm8
	vpshufb	ymm13,ymm13,ymm8
	vpshufb	ymm12,ymm12,ymm8
	vpaddd	ymm11,ymm11,ymm15
	vpaddd	ymm10,ymm10,ymm14
	vpaddd	ymm9,ymm9,ymm13
	vpaddd	ymm8,ymm12,YMMWORD PTR[((160+128))+rbp]
	vpxor	ymm7,ymm7,ymm11
	vpxor	ymm6,ymm6,ymm10
	vpxor	ymm5,ymm5,ymm9
	vpxor	ymm4,ymm4,ymm8
	vmovdqa	YMMWORD PTR[(160+128)+rbp],ymm8
	vpsrld	ymm8,ymm7,20
	vpslld	ymm7,ymm7,32-20
	vpxor	ymm7,ymm7,ymm8
	vpsrld	ymm8,ymm6,20
	vpslld	ymm6,ymm6,32-20
	vpxor	ymm6,ymm6,ymm8
	vpsrld	ymm8,ymm5,20
	vpslld	ymm5,ymm5,32-20
	vpxor	ymm5,ymm5,ymm8
	vpsrld	ymm8,ymm4,20
	vpslld	ymm4,ymm4,32-20
	vpxor	ymm4,ymm4,ymm8
	vmovdqa	ymm8,YMMWORD PTR[$L$rol8]
	vpaddd	ymm3,ymm3,ymm7
	vpaddd	ymm2,ymm2,ymm6
	vpaddd	ymm1,ymm1,ymm5
	vpaddd	ymm0,ymm0,ymm4
	vpxor	ymm15,ymm15,ymm3
	vpxor	ymm14,ymm14,ymm2
	vpxor	ymm13,ymm13,ymm1
	vpxor	ymm12,ymm12,ymm0
	vpshufb	ymm15,ymm15,ymm8
	vpshufb	ymm14,ymm14,ymm8
	vpshufb	ymm13,ymm13,ymm8
	vpshufb	ymm12,ymm12,ymm8
	vpaddd	ymm11,ymm11,ymm15
	vpaddd	ymm10,ymm10,ymm14
	vpaddd	ymm9,ymm9,ymm13
	vpaddd	ymm8,ymm12,YMMWORD PTR[((160+128))+rbp]
	vpxor	ymm7,ymm7,ymm11
	vpxor	ymm6,ymm6,ymm10
	vpxor	ymm5,ymm5,ymm9
	vpxor	ymm4,ymm4,ymm8
	vmovdqa	YMMWORD PTR[(160+128)+rbp],ymm8
	vpsrld	ymm8,ymm7,25
	vpslld	ymm7,ymm7,32-25
	vpxor	ymm7,ymm7,ymm8
	vpsrld	ymm8,ymm6,25
	vpslld	ymm6,ymm6,32-25
	vpxor	ymm6,ymm6,ymm8
	vpsrld	ymm8,ymm5,25
	vpslld	ymm5,ymm5,32-25
	vpxor	ymm5,ymm5,ymm8
	vpsrld	ymm8,ymm4,25
	vpslld	ymm4,ymm4,32-25
	vpxor	ymm4,ymm4,ymm8
	vmovdqa	ymm8,YMMWORD PTR[((160+128))+rbp]
	vpalignr	ymm7,ymm7,ymm7,12
	vpalignr	ymm11,ymm11,ymm11,8
	vpalignr	ymm15,ymm15,ymm15,4
	vpalignr	ymm6,ymm6,ymm6,12
	vpalignr	ymm10,ymm10,ymm10,8
	vpalignr	ymm14,ymm14,ymm14,4
	vpalignr	ymm5,ymm5,ymm5,12
	vpalignr	ymm9,ymm9,ymm9,8
	vpalignr	ymm13,ymm13,ymm13,4
	vpalignr	ymm4,ymm4,ymm4,12
	vpalignr	ymm8,ymm8,ymm8,8
	vpalignr	ymm12,ymm12,ymm12,4

	inc	rcx
	cmp	rcx,4
	jl	$L$open_avx2_tail_512_rounds_and_x2hash
	cmp	rcx,10
	jne	$L$open_avx2_tail_512_rounds_and_x1hash
	mov	rcx,rbx
	sub	rcx,12*32
	and	rcx,-16
$L$open_avx2_tail_512_hash::
	test	rcx,rcx
	je	$L$open_avx2_tail_512_done
	add	r10,QWORD PTR[((0+0))+r8]
	adc	r11,QWORD PTR[((8+0))+r8]
	adc	r12,1
	mov	rdx,QWORD PTR[((0+160+0))+rbp]
	mov	r15,rdx
	mulx	r14,r13,r10
	mulx	rdx,rax,r11
	imul	r15,r12
	add	r14,rax
	adc	r15,rdx
	mov	rdx,QWORD PTR[((8+160+0))+rbp]
	mulx	rax,r10,r10
	add	r14,r10
	mulx	r9,r11,r11
	adc	r15,r11
	adc	r9,0
	imul	rdx,r12
	add	r15,rax
	adc	r9,rdx
	mov	r10,r13
	mov	r11,r14
	mov	r12,r15
	and	r12,3
	mov	r13,r15
	and	r13,-4
	mov	r14,r9
	shrd	r15,r9,2
	shr	r9,2
	add	r15,r13
	adc	r9,r14
	add	r10,r15
	adc	r11,r9
	adc	r12,0

	lea	r8,QWORD PTR[16+r8]
	sub	rcx,2*8
	jmp	$L$open_avx2_tail_512_hash
$L$open_avx2_tail_512_done::
	vpaddd	ymm3,ymm3,YMMWORD PTR[$L$chacha20_consts]
	vpaddd	ymm7,ymm7,YMMWORD PTR[((160+64))+rbp]
	vpaddd	ymm11,ymm11,YMMWORD PTR[((160+96))+rbp]
	vpaddd	ymm15,ymm15,YMMWORD PTR[((160+256))+rbp]
	vpaddd	ymm2,ymm2,YMMWORD PTR[$L$chacha20_consts]
	vpaddd	ymm6,ymm6,YMMWORD PTR[((160+64))+rbp]
	vpaddd	ymm10,ymm10,YMMWORD PTR[((160+96))+rbp]
	vpaddd	ymm14,ymm14,YMMWORD PTR[((160+224))+rbp]
	vpaddd	ymm1,ymm1,YMMWORD PTR[$L$chacha20_consts]
	vpaddd	ymm5,ymm5,YMMWORD PTR[((160+64))+rbp]
	vpaddd	ymm9,ymm9,YMMWORD PTR[((160+96))+rbp]
	vpaddd	ymm13,ymm13,YMMWORD PTR[((160+192))+rbp]
	vpaddd	ymm0,ymm0,YMMWORD PTR[$L$chacha20_consts]
	vpaddd	ymm4,ymm4,YMMWORD PTR[((160+64))+rbp]
	vpaddd	ymm8,ymm8,YMMWORD PTR[((160+96))+rbp]
	vpaddd	ymm12,ymm12,YMMWORD PTR[((160+160))+rbp]

	vmovdqa	YMMWORD PTR[(160+128)+rbp],ymm0
	vperm2i128	ymm0,ymm7,ymm3,002h
	vperm2i128	ymm7,ymm7,ymm3,013h
	vperm2i128	ymm3,ymm15,ymm11,002h
	vperm2i128	ymm11,ymm15,ymm11,013h
	vpxor	ymm0,ymm0,YMMWORD PTR[((0+0))+rsi]
	vpxor	ymm3,ymm3,YMMWORD PTR[((32+0))+rsi]
	vpxor	ymm7,ymm7,YMMWORD PTR[((64+0))+rsi]
	vpxor	ymm11,ymm11,YMMWORD PTR[((96+0))+rsi]
	vmovdqu	YMMWORD PTR[(0+0)+rdi],ymm0
	vmovdqu	YMMWORD PTR[(32+0)+rdi],ymm3
	vmovdqu	YMMWORD PTR[(64+0)+rdi],ymm7
	vmovdqu	YMMWORD PTR[(96+0)+rdi],ymm11

	vmovdqa	ymm0,YMMWORD PTR[((160+128))+rbp]
	vperm2i128	ymm3,ymm6,ymm2,002h
	vperm2i128	ymm6,ymm6,ymm2,013h
	vperm2i128	ymm2,ymm14,ymm10,002h
	vperm2i128	ymm10,ymm14,ymm10,013h
	vpxor	ymm3,ymm3,YMMWORD PTR[((0+128))+rsi]
	vpxor	ymm2,ymm2,YMMWORD PTR[((32+128))+rsi]
	vpxor	ymm6,ymm6,YMMWORD PTR[((64+128))+rsi]
	vpxor	ymm10,ymm10,YMMWORD PTR[((96+128))+rsi]
	vmovdqu	YMMWORD PTR[(0+128)+rdi],ymm3
	vmovdqu	YMMWORD PTR[(32+128)+rdi],ymm2
	vmovdqu	YMMWORD PTR[(64+128)+rdi],ymm6
	vmovdqu	YMMWORD PTR[(96+128)+rdi],ymm10
	vperm2i128	ymm3,ymm5,ymm1,002h
	vperm2i128	ymm5,ymm5,ymm1,013h
	vperm2i128	ymm1,ymm13,ymm9,002h
	vperm2i128	ymm9,ymm13,ymm9,013h
	vpxor	ymm3,ymm3,YMMWORD PTR[((0+256))+rsi]
	vpxor	ymm1,ymm1,YMMWORD PTR[((32+256))+rsi]
	vpxor	ymm5,ymm5,YMMWORD PTR[((64+256))+rsi]
	vpxor	ymm9,ymm9,YMMWORD PTR[((96+256))+rsi]
	vmovdqu	YMMWORD PTR[(0+256)+rdi],ymm3
	vmovdqu	YMMWORD PTR[(32+256)+rdi],ymm1
	vmovdqu	YMMWORD PTR[(64+256)+rdi],ymm5
	vmovdqu	YMMWORD PTR[(96+256)+rdi],ymm9
	vperm2i128	ymm3,ymm4,ymm0,013h
	vperm2i128	ymm0,ymm4,ymm0,002h
	vperm2i128	ymm4,ymm12,ymm8,002h
	vperm2i128	ymm12,ymm12,ymm8,013h
	vmovdqa	ymm8,ymm3

	lea	rsi,QWORD PTR[384+rsi]
	lea	rdi,QWORD PTR[384+rdi]
	sub	rbx,12*32
$L$open_avx2_tail_128_xor::
	cmp	rbx,32
	jb	$L$open_avx2_tail_32_xor
	sub	rbx,32
	vpxor	ymm0,ymm0,YMMWORD PTR[rsi]
	vmovdqu	YMMWORD PTR[rdi],ymm0
	lea	rsi,QWORD PTR[32+rsi]
	lea	rdi,QWORD PTR[32+rdi]
	vmovdqa	ymm0,ymm4
	vmovdqa	ymm4,ymm8
	vmovdqa	ymm8,ymm12
	jmp	$L$open_avx2_tail_128_xor
$L$open_avx2_tail_32_xor::
	cmp	rbx,16
	vmovdqa	xmm1,xmm0
	jb	$L$open_avx2_exit
	sub	rbx,16

	vpxor	xmm1,xmm0,XMMWORD PTR[rsi]
	vmovdqu	XMMWORD PTR[rdi],xmm1
	lea	rsi,QWORD PTR[16+rsi]
	lea	rdi,QWORD PTR[16+rdi]
	vperm2i128	ymm0,ymm0,ymm0,011h
	vmovdqa	xmm1,xmm0
$L$open_avx2_exit::
	vzeroupper
	jmp	$L$open_sse_tail_16

$L$open_avx2_192::
	vmovdqa	ymm1,ymm0
	vmovdqa	ymm2,ymm0
	vmovdqa	ymm5,ymm4
	vmovdqa	ymm6,ymm4
	vmovdqa	ymm9,ymm8
	vmovdqa	ymm10,ymm8
	vpaddd	ymm13,ymm12,YMMWORD PTR[$L$avx2_inc]
	vmovdqa	ymm11,ymm12
	vmovdqa	ymm15,ymm13
	mov	r10,10
$L$open_avx2_192_rounds::
	vpaddd	ymm0,ymm0,ymm4
	vpxor	ymm12,ymm12,ymm0
	vpshufb	ymm12,ymm12,YMMWORD PTR[$L$rol16]
	vpaddd	ymm8,ymm8,ymm12
	vpxor	ymm4,ymm4,ymm8
	vpsrld	ymm3,ymm4,20
	vpslld	ymm4,ymm4,12
	vpxor	ymm4,ymm4,ymm3
	vpaddd	ymm0,ymm0,ymm4
	vpxor	ymm12,ymm12,ymm0
	vpshufb	ymm12,ymm12,YMMWORD PTR[$L$rol8]
	vpaddd	ymm8,ymm8,ymm12
	vpxor	ymm4,ymm4,ymm8
	vpslld	ymm3,ymm4,7
	vpsrld	ymm4,ymm4,25
	vpxor	ymm4,ymm4,ymm3
	vpalignr	ymm12,ymm12,ymm12,12
	vpalignr	ymm8,ymm8,ymm8,8
	vpalignr	ymm4,ymm4,ymm4,4
	vpaddd	ymm1,ymm1,ymm5
	vpxor	ymm13,ymm13,ymm1
	vpshufb	ymm13,ymm13,YMMWORD PTR[$L$rol16]
	vpaddd	ymm9,ymm9,ymm13
	vpxor	ymm5,ymm5,ymm9
	vpsrld	ymm3,ymm5,20
	vpslld	ymm5,ymm5,12
	vpxor	ymm5,ymm5,ymm3
	vpaddd	ymm1,ymm1,ymm5
	vpxor	ymm13,ymm13,ymm1
	vpshufb	ymm13,ymm13,YMMWORD PTR[$L$rol8]
	vpaddd	ymm9,ymm9,ymm13
	vpxor	ymm5,ymm5,ymm9
	vpslld	ymm3,ymm5,7
	vpsrld	ymm5,ymm5,25
	vpxor	ymm5,ymm5,ymm3
	vpalignr	ymm13,ymm13,ymm13,12
	vpalignr	ymm9,ymm9,ymm9,8
	vpalignr	ymm5,ymm5,ymm5,4
	vpaddd	ymm0,ymm0,ymm4
	vpxor	ymm12,ymm12,ymm0
	vpshufb	ymm12,ymm12,YMMWORD PTR[$L$rol16]
	vpaddd	ymm8,ymm8,ymm12
	vpxor	ymm4,ymm4,ymm8
	vpsrld	ymm3,ymm4,20
	vpslld	ymm4,ymm4,12
	vpxor	ymm4,ymm4,ymm3
	vpaddd	ymm0,ymm0,ymm4
	vpxor	ymm12,ymm12,ymm0
	vpshufb	ymm12,ymm12,YMMWORD PTR[$L$rol8]
	vpaddd	ymm8,ymm8,ymm12
	vpxor	ymm4,ymm4,ymm8
	vpslld	ymm3,ymm4,7
	vpsrld	ymm4,ymm4,25
	vpxor	ymm4,ymm4,ymm3
	vpalignr	ymm12,ymm12,ymm12,4
	vpalignr	ymm8,ymm8,ymm8,8
	vpalignr	ymm4,ymm4,ymm4,12
	vpaddd	ymm1,ymm1,ymm5
	vpxor	ymm13,ymm13,ymm1
	vpshufb	ymm13,ymm13,YMMWORD PTR[$L$rol16]
	vpaddd	ymm9,ymm9,ymm13
	vpxor	ymm5,ymm5,ymm9
	vpsrld	ymm3,ymm5,20
	vpslld	ymm5,ymm5,12
	vpxor	ymm5,ymm5,ymm3
	vpaddd	ymm1,ymm1,ymm5
	vpxor	ymm13,ymm13,ymm1
	vpshufb	ymm13,ymm13,YMMWORD PTR[$L$rol8]
	vpaddd	ymm9,ymm9,ymm13
	vpxor	ymm5,ymm5,ymm9
	vpslld	ymm3,ymm5,7
	vpsrld	ymm5,ymm5,25
	vpxor	ymm5,ymm5,ymm3
	vpalignr	ymm13,ymm13,ymm13,4
	vpalignr	ymm9,ymm9,ymm9,8
	vpalignr	ymm5,ymm5,ymm5,12

	dec	r10
	jne	$L$open_avx2_192_rounds
	vpaddd	ymm0,ymm0,ymm2
	vpaddd	ymm1,ymm1,ymm2
	vpaddd	ymm4,ymm4,ymm6
	vpaddd	ymm5,ymm5,ymm6
	vpaddd	ymm8,ymm8,ymm10
	vpaddd	ymm9,ymm9,ymm10
	vpaddd	ymm12,ymm12,ymm11
	vpaddd	ymm13,ymm13,ymm15
	vperm2i128	ymm3,ymm4,ymm0,002h

	vpand	ymm3,ymm3,YMMWORD PTR[$L$clamp]
	vmovdqa	YMMWORD PTR[(160+0)+rbp],ymm3

	vperm2i128	ymm0,ymm4,ymm0,013h
	vperm2i128	ymm4,ymm12,ymm8,013h
	vperm2i128	ymm8,ymm5,ymm1,002h
	vperm2i128	ymm12,ymm13,ymm9,002h
	vperm2i128	ymm1,ymm5,ymm1,013h
	vperm2i128	ymm5,ymm13,ymm9,013h
$L$open_avx2_short::
	mov	r8,r8
	call	poly_hash_ad_internal
$L$open_avx2_short_hash_and_xor_loop::
	cmp	rbx,32
	jb	$L$open_avx2_short_tail_32
	sub	rbx,32
	add	r10,QWORD PTR[((0+0))+rsi]
	adc	r11,QWORD PTR[((8+0))+rsi]
	adc	r12,1
	mov	rax,QWORD PTR[((0+160+0))+rbp]
	mov	r15,rax
	mul	r10
	mov	r13,rax
	mov	r14,rdx
	mov	rax,QWORD PTR[((0+160+0))+rbp]
	mul	r11
	imul	r15,r12
	add	r14,rax
	adc	r15,rdx
	mov	rax,QWORD PTR[((8+160+0))+rbp]
	mov	r9,rax
	mul	r10
	add	r14,rax
	adc	rdx,0
	mov	r10,rdx
	mov	rax,QWORD PTR[((8+160+0))+rbp]
	mul	r11
	add	r15,rax
	adc	rdx,0
	imul	r9,r12
	add	r15,r10
	adc	r9,rdx
	mov	r10,r13
	mov	r11,r14
	mov	r12,r15
	and	r12,3
	mov	r13,r15
	and	r13,-4
	mov	r14,r9
	shrd	r15,r9,2
	shr	r9,2
	add	r15,r13
	adc	r9,r14
	add	r10,r15
	adc	r11,r9
	adc	r12,0
	add	r10,QWORD PTR[((0+16))+rsi]
	adc	r11,QWORD PTR[((8+16))+rsi]
	adc	r12,1
	mov	rax,QWORD PTR[((0+160+0))+rbp]
	mov	r15,rax
	mul	r10
	mov	r13,rax
	mov	r14,rdx
	mov	rax,QWORD PTR[((0+160+0))+rbp]
	mul	r11
	imul	r15,r12
	add	r14,rax
	adc	r15,rdx
	mov	rax,QWORD PTR[((8+160+0))+rbp]
	mov	r9,rax
	mul	r10
	add	r14,rax
	adc	rdx,0
	mov	r10,rdx
	mov	rax,QWORD PTR[((8+160+0))+rbp]
	mul	r11
	add	r15,rax
	adc	rdx,0
	imul	r9,r12
	add	r15,r10
	adc	r9,rdx
	mov	r10,r13
	mov	r11,r14
	mov	r12,r15
	and	r12,3
	mov	r13,r15
	and	r13,-4
	mov	r14,r9
	shrd	r15,r9,2
	shr	r9,2
	add	r15,r13
	adc	r9,r14
	add	r10,r15
	adc	r11,r9
	adc	r12,0


	vpxor	ymm0,ymm0,YMMWORD PTR[rsi]
	vmovdqu	YMMWORD PTR[rdi],ymm0
	lea	rsi,QWORD PTR[32+rsi]
	lea	rdi,QWORD PTR[32+rdi]

	vmovdqa	ymm0,ymm4
	vmovdqa	ymm4,ymm8
	vmovdqa	ymm8,ymm12
	vmovdqa	ymm12,ymm1
	vmovdqa	ymm1,ymm5
	vmovdqa	ymm5,ymm9
	vmovdqa	ymm9,ymm13
	vmovdqa	ymm13,ymm2
	vmovdqa	ymm2,ymm6
	jmp	$L$open_avx2_short_hash_and_xor_loop
$L$open_avx2_short_tail_32::
	cmp	rbx,16
	vmovdqa	xmm1,xmm0
	jb	$L$open_avx2_short_tail_32_exit
	sub	rbx,16
	add	r10,QWORD PTR[((0+0))+rsi]
	adc	r11,QWORD PTR[((8+0))+rsi]
	adc	r12,1
	mov	rax,QWORD PTR[((0+160+0))+rbp]
	mov	r15,rax
	mul	r10
	mov	r13,rax
	mov	r14,rdx
	mov	rax,QWORD PTR[((0+160+0))+rbp]
	mul	r11
	imul	r15,r12
	add	r14,rax
	adc	r15,rdx
	mov	rax,QWORD PTR[((8+160+0))+rbp]
	mov	r9,rax
	mul	r10
	add	r14,rax
	adc	rdx,0
	mov	r10,rdx
	mov	rax,QWORD PTR[((8+160+0))+rbp]
	mul	r11
	add	r15,rax
	adc	rdx,0
	imul	r9,r12
	add	r15,r10
	adc	r9,rdx
	mov	r10,r13
	mov	r11,r14
	mov	r12,r15
	and	r12,3
	mov	r13,r15
	and	r13,-4
	mov	r14,r9
	shrd	r15,r9,2
	shr	r9,2
	add	r15,r13
	adc	r9,r14
	add	r10,r15
	adc	r11,r9
	adc	r12,0

	vpxor	xmm3,xmm0,XMMWORD PTR[rsi]
	vmovdqu	XMMWORD PTR[rdi],xmm3
	lea	rsi,QWORD PTR[16+rsi]
	lea	rdi,QWORD PTR[16+rdi]
	vextracti128	xmm1,ymm0,1
$L$open_avx2_short_tail_32_exit::
	vzeroupper
	jmp	$L$open_sse_tail_16

$L$open_avx2_320::
	vmovdqa	ymm1,ymm0
	vmovdqa	ymm2,ymm0
	vmovdqa	ymm5,ymm4
	vmovdqa	ymm6,ymm4
	vmovdqa	ymm9,ymm8
	vmovdqa	ymm10,ymm8
	vpaddd	ymm13,ymm12,YMMWORD PTR[$L$avx2_inc]
	vpaddd	ymm14,ymm13,YMMWORD PTR[$L$avx2_inc]
	vmovdqa	ymm7,ymm4
	vmovdqa	ymm11,ymm8
	vmovdqa	YMMWORD PTR[(160+160)+rbp],ymm12
	vmovdqa	YMMWORD PTR[(160+192)+rbp],ymm13
	vmovdqa	YMMWORD PTR[(160+224)+rbp],ymm14
	mov	r10,10
$L$open_avx2_320_rounds::
	vpaddd	ymm0,ymm0,ymm4
	vpxor	ymm12,ymm12,ymm0
	vpshufb	ymm12,ymm12,YMMWORD PTR[$L$rol16]
	vpaddd	ymm8,ymm8,ymm12
	vpxor	ymm4,ymm4,ymm8
	vpsrld	ymm3,ymm4,20
	vpslld	ymm4,ymm4,12
	vpxor	ymm4,ymm4,ymm3
	vpaddd	ymm0,ymm0,ymm4
	vpxor	ymm12,ymm12,ymm0
	vpshufb	ymm12,ymm12,YMMWORD PTR[$L$rol8]
	vpaddd	ymm8,ymm8,ymm12
	vpxor	ymm4,ymm4,ymm8
	vpslld	ymm3,ymm4,7
	vpsrld	ymm4,ymm4,25
	vpxor	ymm4,ymm4,ymm3
	vpalignr	ymm12,ymm12,ymm12,12
	vpalignr	ymm8,ymm8,ymm8,8
	vpalignr	ymm4,ymm4,ymm4,4
	vpaddd	ymm1,ymm1,ymm5
	vpxor	ymm13,ymm13,ymm1
	vpshufb	ymm13,ymm13,YMMWORD PTR[$L$rol16]
	vpaddd	ymm9,ymm9,ymm13
	vpxor	ymm5,ymm5,ymm9
	vpsrld	ymm3,ymm5,20
	vpslld	ymm5,ymm5,12
	vpxor	ymm5,ymm5,ymm3
	vpaddd	ymm1,ymm1,ymm5
	vpxor	ymm13,ymm13,ymm1
	vpshufb	ymm13,ymm13,YMMWORD PTR[$L$rol8]
	vpaddd	ymm9,ymm9,ymm13
	vpxor	ymm5,ymm5,ymm9
	vpslld	ymm3,ymm5,7
	vpsrld	ymm5,ymm5,25
	vpxor	ymm5,ymm5,ymm3
	vpalignr	ymm13,ymm13,ymm13,12
	vpalignr	ymm9,ymm9,ymm9,8
	vpalignr	ymm5,ymm5,ymm5,4
	vpaddd	ymm2,ymm2,ymm6
	vpxor	ymm14,ymm14,ymm2
	vpshufb	ymm14,ymm14,YMMWORD PTR[$L$rol16]
	vpaddd	ymm10,ymm10,ymm14
	vpxor	ymm6,ymm6,ymm10
	vpsrld	ymm3,ymm6,20
	vpslld	ymm6,ymm6,12
	vpxor	ymm6,ymm6,ymm3
	vpaddd	ymm2,ymm2,ymm6
	vpxor	ymm14,ymm14,ymm2
	vpshufb	ymm14,ymm14,YMMWORD PTR[$L$rol8]
	vpaddd	ymm10,ymm10,ymm14
	vpxor	ymm6,ymm6,ymm10
	vpslld	ymm3,ymm6,7
	vpsrld	ymm6,ymm6,25
	vpxor	ymm6,ymm6,ymm3
	vpalignr	ymm14,ymm14,ymm14,12
	vpalignr	ymm10,ymm10,ymm10,8
	vpalignr	ymm6,ymm6,ymm6,4
	vpaddd	ymm0,ymm0,ymm4
	vpxor	ymm12,ymm12,ymm0
	vpshufb	ymm12,ymm12,YMMWORD PTR[$L$rol16]
	vpaddd	ymm8,ymm8,ymm12
	vpxor	ymm4,ymm4,ymm8
	vpsrld	ymm3,ymm4,20
	vpslld	ymm4,ymm4,12
	vpxor	ymm4,ymm4,ymm3
	vpaddd	ymm0,ymm0,ymm4
	vpxor	ymm12,ymm12,ymm0
	vpshufb	ymm12,ymm12,YMMWORD PTR[$L$rol8]
	vpaddd	ymm8,ymm8,ymm12
	vpxor	ymm4,ymm4,ymm8
	vpslld	ymm3,ymm4,7
	vpsrld	ymm4,ymm4,25
	vpxor	ymm4,ymm4,ymm3
	vpalignr	ymm12,ymm12,ymm12,4
	vpalignr	ymm8,ymm8,ymm8,8
	vpalignr	ymm4,ymm4,ymm4,12
	vpaddd	ymm1,ymm1,ymm5
	vpxor	ymm13,ymm13,ymm1
	vpshufb	ymm13,ymm13,YMMWORD PTR[$L$rol16]
	vpaddd	ymm9,ymm9,ymm13
	vpxor	ymm5,ymm5,ymm9
	vpsrld	ymm3,ymm5,20
	vpslld	ymm5,ymm5,12
	vpxor	ymm5,ymm5,ymm3
	vpaddd	ymm1,ymm1,ymm5
	vpxor	ymm13,ymm13,ymm1
	vpshufb	ymm13,ymm13,YMMWORD PTR[$L$rol8]
	vpaddd	ymm9,ymm9,ymm13
	vpxor	ymm5,ymm5,ymm9
	vpslld	ymm3,ymm5,7
	vpsrld	ymm5,ymm5,25
	vpxor	ymm5,ymm5,ymm3
	vpalignr	ymm13,ymm13,ymm13,4
	vpalignr	ymm9,ymm9,ymm9,8
	vpalignr	ymm5,ymm5,ymm5,12
	vpaddd	ymm2,ymm2,ymm6
	vpxor	ymm14,ymm14,ymm2
	vpshufb	ymm14,ymm14,YMMWORD PTR[$L$rol16]
	vpaddd	ymm10,ymm10,ymm14
	vpxor	ymm6,ymm6,ymm10
	vpsrld	ymm3,ymm6,20
	vpslld	ymm6,ymm6,12
	vpxor	ymm6,ymm6,ymm3
	vpaddd	ymm2,ymm2,ymm6
	vpxor	ymm14,ymm14,ymm2
	vpshufb	ymm14,ymm14,YMMWORD PTR[$L$rol8]
	vpaddd	ymm10,ymm10,ymm14
	vpxor	ymm6,ymm6,ymm10
	vpslld	ymm3,ymm6,7
	vpsrld	ymm6,ymm6,25
	vpxor	ymm6,ymm6,ymm3
	vpalignr	ymm14,ymm14,ymm14,4
	vpalignr	ymm10,ymm10,ymm10,8
	vpalignr	ymm6,ymm6,ymm6,12

	dec	r10
	jne	$L$open_avx2_320_rounds
	vpaddd	ymm0,ymm0,YMMWORD PTR[$L$chacha20_consts]
	vpaddd	ymm1,ymm1,YMMWORD PTR[$L$chacha20_consts]
	vpaddd	ymm2,ymm2,YMMWORD PTR[$L$chacha20_consts]
	vpaddd	ymm4,ymm4,ymm7
	vpaddd	ymm5,ymm5,ymm7
	vpaddd	ymm6,ymm6,ymm7
	vpaddd	ymm8,ymm8,ymm11
	vpaddd	ymm9,ymm9,ymm11
	vpaddd	ymm10,ymm10,ymm11
	vpaddd	ymm12,ymm12,YMMWORD PTR[((160+160))+rbp]
	vpaddd	ymm13,ymm13,YMMWORD PTR[((160+192))+rbp]
	vpaddd	ymm14,ymm14,YMMWORD PTR[((160+224))+rbp]
	vperm2i128	ymm3,ymm4,ymm0,002h

	vpand	ymm3,ymm3,YMMWORD PTR[$L$clamp]
	vmovdqa	YMMWORD PTR[(160+0)+rbp],ymm3

	vperm2i128	ymm0,ymm4,ymm0,013h
	vperm2i128	ymm4,ymm12,ymm8,013h
	vperm2i128	ymm8,ymm5,ymm1,002h
	vperm2i128	ymm12,ymm13,ymm9,002h
	vperm2i128	ymm1,ymm5,ymm1,013h
	vperm2i128	ymm5,ymm13,ymm9,013h
	vperm2i128	ymm9,ymm6,ymm2,002h
	vperm2i128	ymm13,ymm14,ymm10,002h
	vperm2i128	ymm2,ymm6,ymm2,013h
	vperm2i128	ymm6,ymm14,ymm10,013h
	jmp	$L$open_avx2_short
chacha20_poly1305_open_avx2	ENDP




ALIGN	64
chacha20_poly1305_seal_avx2	PROC PRIVATE












	vzeroupper
	vmovdqa	ymm0,YMMWORD PTR[$L$chacha20_consts]
	vbroadcasti128	ymm4,XMMWORD PTR[r9]
	vbroadcasti128	ymm8,XMMWORD PTR[16+r9]
	vbroadcasti128	ymm12,XMMWORD PTR[32+r9]
	vpaddd	ymm12,ymm12,YMMWORD PTR[$L$avx2_init]
	cmp	rbx,6*32
	jbe	$L$seal_avx2_192
	cmp	rbx,10*32
	jbe	$L$seal_avx2_320
	vmovdqa	ymm1,ymm0
	vmovdqa	ymm2,ymm0
	vmovdqa	ymm3,ymm0
	vmovdqa	ymm5,ymm4
	vmovdqa	ymm6,ymm4
	vmovdqa	ymm7,ymm4
	vmovdqa	YMMWORD PTR[(160+64)+rbp],ymm4
	vmovdqa	ymm9,ymm8
	vmovdqa	ymm10,ymm8
	vmovdqa	ymm11,ymm8
	vmovdqa	YMMWORD PTR[(160+96)+rbp],ymm8
	vmovdqa	ymm15,ymm12
	vpaddd	ymm14,ymm15,YMMWORD PTR[$L$avx2_inc]
	vpaddd	ymm13,ymm14,YMMWORD PTR[$L$avx2_inc]
	vpaddd	ymm12,ymm13,YMMWORD PTR[$L$avx2_inc]
	vmovdqa	YMMWORD PTR[(160+160)+rbp],ymm12
	vmovdqa	YMMWORD PTR[(160+192)+rbp],ymm13
	vmovdqa	YMMWORD PTR[(160+224)+rbp],ymm14
	vmovdqa	YMMWORD PTR[(160+256)+rbp],ymm15
	mov	r10,10
$L$seal_avx2_init_rounds::
	vmovdqa	YMMWORD PTR[(160+128)+rbp],ymm8
	vmovdqa	ymm8,YMMWORD PTR[$L$rol16]
	vpaddd	ymm3,ymm3,ymm7
	vpaddd	ymm2,ymm2,ymm6
	vpaddd	ymm1,ymm1,ymm5
	vpaddd	ymm0,ymm0,ymm4
	vpxor	ymm15,ymm15,ymm3
	vpxor	ymm14,ymm14,ymm2
	vpxor	ymm13,ymm13,ymm1
	vpxor	ymm12,ymm12,ymm0
	vpshufb	ymm15,ymm15,ymm8
	vpshufb	ymm14,ymm14,ymm8
	vpshufb	ymm13,ymm13,ymm8
	vpshufb	ymm12,ymm12,ymm8
	vpaddd	ymm11,ymm11,ymm15
	vpaddd	ymm10,ymm10,ymm14
	vpaddd	ymm9,ymm9,ymm13
	vpaddd	ymm8,ymm12,YMMWORD PTR[((160+128))+rbp]
	vpxor	ymm7,ymm7,ymm11
	vpxor	ymm6,ymm6,ymm10
	vpxor	ymm5,ymm5,ymm9
	vpxor	ymm4,ymm4,ymm8
	vmovdqa	YMMWORD PTR[(160+128)+rbp],ymm8
	vpsrld	ymm8,ymm7,20
	vpslld	ymm7,ymm7,32-20
	vpxor	ymm7,ymm7,ymm8
	vpsrld	ymm8,ymm6,20
	vpslld	ymm6,ymm6,32-20
	vpxor	ymm6,ymm6,ymm8
	vpsrld	ymm8,ymm5,20
	vpslld	ymm5,ymm5,32-20
	vpxor	ymm5,ymm5,ymm8
	vpsrld	ymm8,ymm4,20
	vpslld	ymm4,ymm4,32-20
	vpxor	ymm4,ymm4,ymm8
	vmovdqa	ymm8,YMMWORD PTR[$L$rol8]
	vpaddd	ymm3,ymm3,ymm7
	vpaddd	ymm2,ymm2,ymm6
	vpaddd	ymm1,ymm1,ymm5
	vpaddd	ymm0,ymm0,ymm4
	vpxor	ymm15,ymm15,ymm3
	vpxor	ymm14,ymm14,ymm2
	vpxor	ymm13,ymm13,ymm1
	vpxor	ymm12,ymm12,ymm0
	vpshufb	ymm15,ymm15,ymm8
	vpshufb	ymm14,ymm14,ymm8
	vpshufb	ymm13,ymm13,ymm8
	vpshufb	ymm12,ymm12,ymm8
	vpaddd	ymm11,ymm11,ymm15
	vpaddd	ymm10,ymm10,ymm14
	vpaddd	ymm9,ymm9,ymm13
	vpaddd	ymm8,ymm12,YMMWORD PTR[((160+128))+rbp]
	vpxor	ymm7,ymm7,ymm11
	vpxor	ymm6,ymm6,ymm10
	vpxor	ymm5,ymm5,ymm9
	vpxor	ymm4,ymm4,ymm8
	vmovdqa	YMMWORD PTR[(160+128)+rbp],ymm8
	vpsrld	ymm8,ymm7,25
	vpslld	ymm7,ymm7,32-25
	vpxor	ymm7,ymm7,ymm8
	vpsrld	ymm8,ymm6,25
	vpslld	ymm6,ymm6,32-25
	vpxor	ymm6,ymm6,ymm8
	vpsrld	ymm8,ymm5,25
	vpslld	ymm5,ymm5,32-25
	vpxor	ymm5,ymm5,ymm8
	vpsrld	ymm8,ymm4,25
	vpslld	ymm4,ymm4,32-25
	vpxor	ymm4,ymm4,ymm8
	vmovdqa	ymm8,YMMWORD PTR[((160+128))+rbp]
	vpalignr	ymm7,ymm7,ymm7,4
	vpalignr	ymm11,ymm11,ymm11,8
	vpalignr	ymm15,ymm15,ymm15,12
	vpalignr	ymm6,ymm6,ymm6,4
	vpalignr	ymm10,ymm10,ymm10,8
	vpalignr	ymm14,ymm14,ymm14,12
	vpalignr	ymm5,ymm5,ymm5,4
	vpalignr	ymm9,ymm9,ymm9,8
	vpalignr	ymm13,ymm13,ymm13,12
	vpalignr	ymm4,ymm4,ymm4,4
	vpalignr	ymm8,ymm8,ymm8,8
	vpalignr	ymm12,ymm12,ymm12,12
	vmovdqa	YMMWORD PTR[(160+128)+rbp],ymm8
	vmovdqa	ymm8,YMMWORD PTR[$L$rol16]
	vpaddd	ymm3,ymm3,ymm7
	vpaddd	ymm2,ymm2,ymm6
	vpaddd	ymm1,ymm1,ymm5
	vpaddd	ymm0,ymm0,ymm4
	vpxor	ymm15,ymm15,ymm3
	vpxor	ymm14,ymm14,ymm2
	vpxor	ymm13,ymm13,ymm1
	vpxor	ymm12,ymm12,ymm0
	vpshufb	ymm15,ymm15,ymm8
	vpshufb	ymm14,ymm14,ymm8
	vpshufb	ymm13,ymm13,ymm8
	vpshufb	ymm12,ymm12,ymm8
	vpaddd	ymm11,ymm11,ymm15
	vpaddd	ymm10,ymm10,ymm14
	vpaddd	ymm9,ymm9,ymm13
	vpaddd	ymm8,ymm12,YMMWORD PTR[((160+128))+rbp]
	vpxor	ymm7,ymm7,ymm11
	vpxor	ymm6,ymm6,ymm10
	vpxor	ymm5,ymm5,ymm9
	vpxor	ymm4,ymm4,ymm8
	vmovdqa	YMMWORD PTR[(160+128)+rbp],ymm8
	vpsrld	ymm8,ymm7,20
	vpslld	ymm7,ymm7,32-20
	vpxor	ymm7,ymm7,ymm8
	vpsrld	ymm8,ymm6,20
	vpslld	ymm6,ymm6,32-20
	vpxor	ymm6,ymm6,ymm8
	vpsrld	ymm8,ymm5,20
	vpslld	ymm5,ymm5,32-20
	vpxor	ymm5,ymm5,ymm8
	vpsrld	ymm8,ymm4,20
	vpslld	ymm4,ymm4,32-20
	vpxor	ymm4,ymm4,ymm8
	vmovdqa	ymm8,YMMWORD PTR[$L$rol8]
	vpaddd	ymm3,ymm3,ymm7
	vpaddd	ymm2,ymm2,ymm6
	vpaddd	ymm1,ymm1,ymm5
	vpaddd	ymm0,ymm0,ymm4
	vpxor	ymm15,ymm15,ymm3
	vpxor	ymm14,ymm14,ymm2
	vpxor	ymm13,ymm13,ymm1
	vpxor	ymm12,ymm12,ymm0
	vpshufb	ymm15,ymm15,ymm8
	vpshufb	ymm14,ymm14,ymm8
	vpshufb	ymm13,ymm13,ymm8
	vpshufb	ymm12,ymm12,ymm8
	vpaddd	ymm11,ymm11,ymm15
	vpaddd	ymm10,ymm10,ymm14
	vpaddd	ymm9,ymm9,ymm13
	vpaddd	ymm8,ymm12,YMMWORD PTR[((160+128))+rbp]
	vpxor	ymm7,ymm7,ymm11
	vpxor	ymm6,ymm6,ymm10
	vpxor	ymm5,ymm5,ymm9
	vpxor	ymm4,ymm4,ymm8
	vmovdqa	YMMWORD PTR[(160+128)+rbp],ymm8
	vpsrld	ymm8,ymm7,25
	vpslld	ymm7,ymm7,32-25
	vpxor	ymm7,ymm7,ymm8
	vpsrld	ymm8,ymm6,25
	vpslld	ymm6,ymm6,32-25
	vpxor	ymm6,ymm6,ymm8
	vpsrld	ymm8,ymm5,25
	vpslld	ymm5,ymm5,32-25
	vpxor	ymm5,ymm5,ymm8
	vpsrld	ymm8,ymm4,25
	vpslld	ymm4,ymm4,32-25
	vpxor	ymm4,ymm4,ymm8
	vmovdqa	ymm8,YMMWORD PTR[((160+128))+rbp]
	vpalignr	ymm7,ymm7,ymm7,12
	vpalignr	ymm11,ymm11,ymm11,8
	vpalignr	ymm15,ymm15,ymm15,4
	vpalignr	ymm6,ymm6,ymm6,12
	vpalignr	ymm10,ymm10,ymm10,8
	vpalignr	ymm14,ymm14,ymm14,4
	vpalignr	ymm5,ymm5,ymm5,12
	vpalignr	ymm9,ymm9,ymm9,8
	vpalignr	ymm13,ymm13,ymm13,4
	vpalignr	ymm4,ymm4,ymm4,12
	vpalignr	ymm8,ymm8,ymm8,8
	vpalignr	ymm12,ymm12,ymm12,4

	dec	r10
	jnz	$L$seal_avx2_init_rounds
	vpaddd	ymm3,ymm3,YMMWORD PTR[$L$chacha20_consts]
	vpaddd	ymm7,ymm7,YMMWORD PTR[((160+64))+rbp]
	vpaddd	ymm11,ymm11,YMMWORD PTR[((160+96))+rbp]
	vpaddd	ymm15,ymm15,YMMWORD PTR[((160+256))+rbp]
	vpaddd	ymm2,ymm2,YMMWORD PTR[$L$chacha20_consts]
	vpaddd	ymm6,ymm6,YMMWORD PTR[((160+64))+rbp]
	vpaddd	ymm10,ymm10,YMMWORD PTR[((160+96))+rbp]
	vpaddd	ymm14,ymm14,YMMWORD PTR[((160+224))+rbp]
	vpaddd	ymm1,ymm1,YMMWORD PTR[$L$chacha20_consts]
	vpaddd	ymm5,ymm5,YMMWORD PTR[((160+64))+rbp]
	vpaddd	ymm9,ymm9,YMMWORD PTR[((160+96))+rbp]
	vpaddd	ymm13,ymm13,YMMWORD PTR[((160+192))+rbp]
	vpaddd	ymm0,ymm0,YMMWORD PTR[$L$chacha20_consts]
	vpaddd	ymm4,ymm4,YMMWORD PTR[((160+64))+rbp]
	vpaddd	ymm8,ymm8,YMMWORD PTR[((160+96))+rbp]
	vpaddd	ymm12,ymm12,YMMWORD PTR[((160+160))+rbp]

	vperm2i128	ymm11,ymm15,ymm11,013h
	vperm2i128	ymm15,ymm7,ymm3,002h
	vperm2i128	ymm3,ymm7,ymm3,013h
	vpand	ymm15,ymm15,YMMWORD PTR[$L$clamp]
	vmovdqa	YMMWORD PTR[(160+0)+rbp],ymm15
	mov	r8,r8
	call	poly_hash_ad_internal

	vpxor	ymm3,ymm3,YMMWORD PTR[rsi]
	vpxor	ymm11,ymm11,YMMWORD PTR[32+rsi]
	vmovdqu	YMMWORD PTR[rdi],ymm3
	vmovdqu	YMMWORD PTR[32+rdi],ymm11
	vperm2i128	ymm15,ymm6,ymm2,002h
	vperm2i128	ymm6,ymm6,ymm2,013h
	vperm2i128	ymm2,ymm14,ymm10,002h
	vperm2i128	ymm10,ymm14,ymm10,013h
	vpxor	ymm15,ymm15,YMMWORD PTR[((0+64))+rsi]
	vpxor	ymm2,ymm2,YMMWORD PTR[((32+64))+rsi]
	vpxor	ymm6,ymm6,YMMWORD PTR[((64+64))+rsi]
	vpxor	ymm10,ymm10,YMMWORD PTR[((96+64))+rsi]
	vmovdqu	YMMWORD PTR[(0+64)+rdi],ymm15
	vmovdqu	YMMWORD PTR[(32+64)+rdi],ymm2
	vmovdqu	YMMWORD PTR[(64+64)+rdi],ymm6
	vmovdqu	YMMWORD PTR[(96+64)+rdi],ymm10
	vperm2i128	ymm15,ymm5,ymm1,002h
	vperm2i128	ymm5,ymm5,ymm1,013h
	vperm2i128	ymm1,ymm13,ymm9,002h
	vperm2i128	ymm9,ymm13,ymm9,013h
	vpxor	ymm15,ymm15,YMMWORD PTR[((0+192))+rsi]
	vpxor	ymm1,ymm1,YMMWORD PTR[((32+192))+rsi]
	vpxor	ymm5,ymm5,YMMWORD PTR[((64+192))+rsi]
	vpxor	ymm9,ymm9,YMMWORD PTR[((96+192))+rsi]
	vmovdqu	YMMWORD PTR[(0+192)+rdi],ymm15
	vmovdqu	YMMWORD PTR[(32+192)+rdi],ymm1
	vmovdqu	YMMWORD PTR[(64+192)+rdi],ymm5
	vmovdqu	YMMWORD PTR[(96+192)+rdi],ymm9
	vperm2i128	ymm15,ymm4,ymm0,013h
	vperm2i128	ymm0,ymm4,ymm0,002h
	vperm2i128	ymm4,ymm12,ymm8,002h
	vperm2i128	ymm12,ymm12,ymm8,013h
	vmovdqa	ymm8,ymm15

	lea	rsi,QWORD PTR[320+rsi]
	sub	rbx,10*32
	mov	rcx,10*32
	cmp	rbx,4*32
	jbe	$L$seal_avx2_short_hash_remainder
	vpxor	ymm0,ymm0,YMMWORD PTR[rsi]
	vpxor	ymm4,ymm4,YMMWORD PTR[32+rsi]
	vpxor	ymm8,ymm8,YMMWORD PTR[64+rsi]
	vpxor	ymm12,ymm12,YMMWORD PTR[96+rsi]
	vmovdqu	YMMWORD PTR[320+rdi],ymm0
	vmovdqu	YMMWORD PTR[352+rdi],ymm4
	vmovdqu	YMMWORD PTR[384+rdi],ymm8
	vmovdqu	YMMWORD PTR[416+rdi],ymm12
	lea	rsi,QWORD PTR[128+rsi]
	sub	rbx,4*32
	mov	rcx,8
	mov	r8,2
	cmp	rbx,4*32
	jbe	$L$seal_avx2_tail_128
	cmp	rbx,8*32
	jbe	$L$seal_avx2_tail_256
	cmp	rbx,12*32
	jbe	$L$seal_avx2_tail_384
	cmp	rbx,16*32
	jbe	$L$seal_avx2_tail_512
	vmovdqa	ymm0,YMMWORD PTR[$L$chacha20_consts]
	vmovdqa	ymm4,YMMWORD PTR[((160+64))+rbp]
	vmovdqa	ymm8,YMMWORD PTR[((160+96))+rbp]
	vmovdqa	ymm1,ymm0
	vmovdqa	ymm5,ymm4
	vmovdqa	ymm9,ymm8
	vmovdqa	ymm2,ymm0
	vmovdqa	ymm6,ymm4
	vmovdqa	ymm10,ymm8
	vmovdqa	ymm3,ymm0
	vmovdqa	ymm7,ymm4
	vmovdqa	ymm11,ymm8
	vmovdqa	ymm12,YMMWORD PTR[$L$avx2_inc]
	vpaddd	ymm15,ymm12,YMMWORD PTR[((160+160))+rbp]
	vpaddd	ymm14,ymm12,ymm15
	vpaddd	ymm13,ymm12,ymm14
	vpaddd	ymm12,ymm12,ymm13
	vmovdqa	YMMWORD PTR[(160+256)+rbp],ymm15
	vmovdqa	YMMWORD PTR[(160+224)+rbp],ymm14
	vmovdqa	YMMWORD PTR[(160+192)+rbp],ymm13
	vmovdqa	YMMWORD PTR[(160+160)+rbp],ymm12
	vmovdqa	YMMWORD PTR[(160+128)+rbp],ymm8
	vmovdqa	ymm8,YMMWORD PTR[$L$rol16]
	vpaddd	ymm3,ymm3,ymm7
	vpaddd	ymm2,ymm2,ymm6
	vpaddd	ymm1,ymm1,ymm5
	vpaddd	ymm0,ymm0,ymm4
	vpxor	ymm15,ymm15,ymm3
	vpxor	ymm14,ymm14,ymm2
	vpxor	ymm13,ymm13,ymm1
	vpxor	ymm12,ymm12,ymm0
	vpshufb	ymm15,ymm15,ymm8
	vpshufb	ymm14,ymm14,ymm8
	vpshufb	ymm13,ymm13,ymm8
	vpshufb	ymm12,ymm12,ymm8
	vpaddd	ymm11,ymm11,ymm15
	vpaddd	ymm10,ymm10,ymm14
	vpaddd	ymm9,ymm9,ymm13
	vpaddd	ymm8,ymm12,YMMWORD PTR[((160+128))+rbp]
	vpxor	ymm7,ymm7,ymm11
	vpxor	ymm6,ymm6,ymm10
	vpxor	ymm5,ymm5,ymm9
	vpxor	ymm4,ymm4,ymm8
	vmovdqa	YMMWORD PTR[(160+128)+rbp],ymm8
	vpsrld	ymm8,ymm7,20
	vpslld	ymm7,ymm7,32-20
	vpxor	ymm7,ymm7,ymm8
	vpsrld	ymm8,ymm6,20
	vpslld	ymm6,ymm6,32-20
	vpxor	ymm6,ymm6,ymm8
	vpsrld	ymm8,ymm5,20
	vpslld	ymm5,ymm5,32-20
	vpxor	ymm5,ymm5,ymm8
	vpsrld	ymm8,ymm4,20
	vpslld	ymm4,ymm4,32-20
	vpxor	ymm4,ymm4,ymm8
	vmovdqa	ymm8,YMMWORD PTR[$L$rol8]
	vpaddd	ymm3,ymm3,ymm7
	vpaddd	ymm2,ymm2,ymm6
	vpaddd	ymm1,ymm1,ymm5
	vpaddd	ymm0,ymm0,ymm4
	vpxor	ymm15,ymm15,ymm3
	vpxor	ymm14,ymm14,ymm2
	vpxor	ymm13,ymm13,ymm1
	vpxor	ymm12,ymm12,ymm0
	vpshufb	ymm15,ymm15,ymm8
	vpshufb	ymm14,ymm14,ymm8
	vpshufb	ymm13,ymm13,ymm8
	vpshufb	ymm12,ymm12,ymm8
	vpaddd	ymm11,ymm11,ymm15
	vpaddd	ymm10,ymm10,ymm14
	vpaddd	ymm9,ymm9,ymm13
	vpaddd	ymm8,ymm12,YMMWORD PTR[((160+128))+rbp]
	vpxor	ymm7,ymm7,ymm11
	vpxor	ymm6,ymm6,ymm10
	vpxor	ymm5,ymm5,ymm9
	vpxor	ymm4,ymm4,ymm8
	vmovdqa	YMMWORD PTR[(160+128)+rbp],ymm8
	vpsrld	ymm8,ymm7,25
	vpslld	ymm7,ymm7,32-25
	vpxor	ymm7,ymm7,ymm8
	vpsrld	ymm8,ymm6,25
	vpslld	ymm6,ymm6,32-25
	vpxor	ymm6,ymm6,ymm8
	vpsrld	ymm8,ymm5,25
	vpslld	ymm5,ymm5,32-25
	vpxor	ymm5,ymm5,ymm8
	vpsrld	ymm8,ymm4,25
	vpslld	ymm4,ymm4,32-25
	vpxor	ymm4,ymm4,ymm8
	vmovdqa	ymm8,YMMWORD PTR[((160+128))+rbp]
	vpalignr	ymm7,ymm7,ymm7,4
	vpalignr	ymm11,ymm11,ymm11,8
	vpalignr	ymm15,ymm15,ymm15,12
	vpalignr	ymm6,ymm6,ymm6,4
	vpalignr	ymm10,ymm10,ymm10,8
	vpalignr	ymm14,ymm14,ymm14,12
	vpalignr	ymm5,ymm5,ymm5,4
	vpalignr	ymm9,ymm9,ymm9,8
	vpalignr	ymm13,ymm13,ymm13,12
	vpalignr	ymm4,ymm4,ymm4,4
	vpalignr	ymm8,ymm8,ymm8,8
	vpalignr	ymm12,ymm12,ymm12,12
	vmovdqa	YMMWORD PTR[(160+128)+rbp],ymm8
	vmovdqa	ymm8,YMMWORD PTR[$L$rol16]
	vpaddd	ymm3,ymm3,ymm7
	vpaddd	ymm2,ymm2,ymm6
	vpaddd	ymm1,ymm1,ymm5
	vpaddd	ymm0,ymm0,ymm4
	vpxor	ymm15,ymm15,ymm3
	vpxor	ymm14,ymm14,ymm2
	vpxor	ymm13,ymm13,ymm1
	vpxor	ymm12,ymm12,ymm0
	vpshufb	ymm15,ymm15,ymm8
	vpshufb	ymm14,ymm14,ymm8
	vpshufb	ymm13,ymm13,ymm8
	vpshufb	ymm12,ymm12,ymm8
	vpaddd	ymm11,ymm11,ymm15
	vpaddd	ymm10,ymm10,ymm14
	vpaddd	ymm9,ymm9,ymm13
	vpaddd	ymm8,ymm12,YMMWORD PTR[((160+128))+rbp]
	vpxor	ymm7,ymm7,ymm11
	vpxor	ymm6,ymm6,ymm10
	vpxor	ymm5,ymm5,ymm9
	vpxor	ymm4,ymm4,ymm8
	vmovdqa	YMMWORD PTR[(160+128)+rbp],ymm8
	vpsrld	ymm8,ymm7,20
	vpslld	ymm7,ymm7,32-20
	vpxor	ymm7,ymm7,ymm8
	vpsrld	ymm8,ymm6,20
	vpslld	ymm6,ymm6,32-20
	vpxor	ymm6,ymm6,ymm8
	vpsrld	ymm8,ymm5,20
	vpslld	ymm5,ymm5,32-20
	vpxor	ymm5,ymm5,ymm8
	vpsrld	ymm8,ymm4,20
	vpslld	ymm4,ymm4,32-20
	vpxor	ymm4,ymm4,ymm8
	vmovdqa	ymm8,YMMWORD PTR[$L$rol8]
	vpaddd	ymm3,ymm3,ymm7
	vpaddd	ymm2,ymm2,ymm6
	vpaddd	ymm1,ymm1,ymm5
	vpaddd	ymm0,ymm0,ymm4
	vpxor	ymm15,ymm15,ymm3
	vpxor	ymm14,ymm14,ymm2
	vpxor	ymm13,ymm13,ymm1
	vpxor	ymm12,ymm12,ymm0
	vpshufb	ymm15,ymm15,ymm8
	vpshufb	ymm14,ymm14,ymm8
	vpshufb	ymm13,ymm13,ymm8
	vpshufb	ymm12,ymm12,ymm8
	vpaddd	ymm11,ymm11,ymm15
	vpaddd	ymm10,ymm10,ymm14
	vpaddd	ymm9,ymm9,ymm13
	vpaddd	ymm8,ymm12,YMMWORD PTR[((160+128))+rbp]
	vpxor	ymm7,ymm7,ymm11
	vpxor	ymm6,ymm6,ymm10
	vpxor	ymm5,ymm5,ymm9
	vpxor	ymm4,ymm4,ymm8
	vmovdqa	YMMWORD PTR[(160+128)+rbp],ymm8
	vpsrld	ymm8,ymm7,25
	vpslld	ymm7,ymm7,32-25
	vpxor	ymm7,ymm7,ymm8
	vpsrld	ymm8,ymm6,25
	vpslld	ymm6,ymm6,32-25
	vpxor	ymm6,ymm6,ymm8
	vpsrld	ymm8,ymm5,25
	vpslld	ymm5,ymm5,32-25
	vpxor	ymm5,ymm5,ymm8
	vpsrld	ymm8,ymm4,25
	vpslld	ymm4,ymm4,32-25
	vpxor	ymm4,ymm4,ymm8
	vmovdqa	ymm8,YMMWORD PTR[((160+128))+rbp]
	vpalignr	ymm7,ymm7,ymm7,12
	vpalignr	ymm11,ymm11,ymm11,8
	vpalignr	ymm15,ymm15,ymm15,4
	vpalignr	ymm6,ymm6,ymm6,12
	vpalignr	ymm10,ymm10,ymm10,8
	vpalignr	ymm14,ymm14,ymm14,4
	vpalignr	ymm5,ymm5,ymm5,12
	vpalignr	ymm9,ymm9,ymm9,8
	vpalignr	ymm13,ymm13,ymm13,4
	vpalignr	ymm4,ymm4,ymm4,12
	vpalignr	ymm8,ymm8,ymm8,8
	vpalignr	ymm12,ymm12,ymm12,4
	vmovdqa	YMMWORD PTR[(160+128)+rbp],ymm8
	vmovdqa	ymm8,YMMWORD PTR[$L$rol16]
	vpaddd	ymm3,ymm3,ymm7
	vpaddd	ymm2,ymm2,ymm6
	vpaddd	ymm1,ymm1,ymm5
	vpaddd	ymm0,ymm0,ymm4
	vpxor	ymm15,ymm15,ymm3
	vpxor	ymm14,ymm14,ymm2
	vpxor	ymm13,ymm13,ymm1
	vpxor	ymm12,ymm12,ymm0
	vpshufb	ymm15,ymm15,ymm8
	vpshufb	ymm14,ymm14,ymm8
	vpshufb	ymm13,ymm13,ymm8
	vpshufb	ymm12,ymm12,ymm8
	vpaddd	ymm11,ymm11,ymm15
	vpaddd	ymm10,ymm10,ymm14
	vpaddd	ymm9,ymm9,ymm13
	vpaddd	ymm8,ymm12,YMMWORD PTR[((160+128))+rbp]
	vpxor	ymm7,ymm7,ymm11
	vpxor	ymm6,ymm6,ymm10
	vpxor	ymm5,ymm5,ymm9
	vpxor	ymm4,ymm4,ymm8
	vmovdqa	YMMWORD PTR[(160+128)+rbp],ymm8
	vpsrld	ymm8,ymm7,20
	vpslld	ymm7,ymm7,32-20
	vpxor	ymm7,ymm7,ymm8
	vpsrld	ymm8,ymm6,20
	vpslld	ymm6,ymm6,32-20
	vpxor	ymm6,ymm6,ymm8
	vpsrld	ymm8,ymm5,20
	vpslld	ymm5,ymm5,32-20
	vpxor	ymm5,ymm5,ymm8
	vpsrld	ymm8,ymm4,20
	vpslld	ymm4,ymm4,32-20
	vpxor	ymm4,ymm4,ymm8
	vmovdqa	ymm8,YMMWORD PTR[$L$rol8]
	vpaddd	ymm3,ymm3,ymm7
	vpaddd	ymm2,ymm2,ymm6
	vpaddd	ymm1,ymm1,ymm5
	vpaddd	ymm0,ymm0,ymm4
	vpxor	ymm15,ymm15,ymm3

	sub	rdi,16
	mov	rcx,9
	jmp	$L$seal_avx2_main_loop_rounds_entry
ALIGN	32
$L$seal_avx2_main_loop::
	vmovdqa	ymm0,YMMWORD PTR[$L$chacha20_consts]
	vmovdqa	ymm4,YMMWORD PTR[((160+64))+rbp]
	vmovdqa	ymm8,YMMWORD PTR[((160+96))+rbp]
	vmovdqa	ymm1,ymm0
	vmovdqa	ymm5,ymm4
	vmovdqa	ymm9,ymm8
	vmovdqa	ymm2,ymm0
	vmovdqa	ymm6,ymm4
	vmovdqa	ymm10,ymm8
	vmovdqa	ymm3,ymm0
	vmovdqa	ymm7,ymm4
	vmovdqa	ymm11,ymm8
	vmovdqa	ymm12,YMMWORD PTR[$L$avx2_inc]
	vpaddd	ymm15,ymm12,YMMWORD PTR[((160+160))+rbp]
	vpaddd	ymm14,ymm12,ymm15
	vpaddd	ymm13,ymm12,ymm14
	vpaddd	ymm12,ymm12,ymm13
	vmovdqa	YMMWORD PTR[(160+256)+rbp],ymm15
	vmovdqa	YMMWORD PTR[(160+224)+rbp],ymm14
	vmovdqa	YMMWORD PTR[(160+192)+rbp],ymm13
	vmovdqa	YMMWORD PTR[(160+160)+rbp],ymm12

	mov	rcx,10
ALIGN	32
$L$seal_avx2_main_loop_rounds::
	add	r10,QWORD PTR[((0+0))+rdi]
	adc	r11,QWORD PTR[((8+0))+rdi]
	adc	r12,1
	vmovdqa	YMMWORD PTR[(160+128)+rbp],ymm8
	vmovdqa	ymm8,YMMWORD PTR[$L$rol16]
	vpaddd	ymm3,ymm3,ymm7
	vpaddd	ymm2,ymm2,ymm6
	vpaddd	ymm1,ymm1,ymm5
	vpaddd	ymm0,ymm0,ymm4
	vpxor	ymm15,ymm15,ymm3
	vpxor	ymm14,ymm14,ymm2
	vpxor	ymm13,ymm13,ymm1
	vpxor	ymm12,ymm12,ymm0
	mov	rdx,QWORD PTR[((0+160+0))+rbp]
	mov	r15,rdx
	mulx	r14,r13,r10
	mulx	rdx,rax,r11
	imul	r15,r12
	add	r14,rax
	adc	r15,rdx
	vpshufb	ymm15,ymm15,ymm8
	vpshufb	ymm14,ymm14,ymm8
	vpshufb	ymm13,ymm13,ymm8
	vpshufb	ymm12,ymm12,ymm8
	vpaddd	ymm11,ymm11,ymm15
	vpaddd	ymm10,ymm10,ymm14
	vpaddd	ymm9,ymm9,ymm13
	vpaddd	ymm8,ymm12,YMMWORD PTR[((160+128))+rbp]
	vpxor	ymm7,ymm7,ymm11
	mov	rdx,QWORD PTR[((8+160+0))+rbp]
	mulx	rax,r10,r10
	add	r14,r10
	mulx	r9,r11,r11
	adc	r15,r11
	adc	r9,0
	imul	rdx,r12
	vpxor	ymm6,ymm6,ymm10
	vpxor	ymm5,ymm5,ymm9
	vpxor	ymm4,ymm4,ymm8
	vmovdqa	YMMWORD PTR[(160+128)+rbp],ymm8
	vpsrld	ymm8,ymm7,20
	vpslld	ymm7,ymm7,32-20
	vpxor	ymm7,ymm7,ymm8
	vpsrld	ymm8,ymm6,20
	vpslld	ymm6,ymm6,32-20
	vpxor	ymm6,ymm6,ymm8
	vpsrld	ymm8,ymm5,20
	vpslld	ymm5,ymm5,32-20
	add	r15,rax
	adc	r9,rdx
	vpxor	ymm5,ymm5,ymm8
	vpsrld	ymm8,ymm4,20
	vpslld	ymm4,ymm4,32-20
	vpxor	ymm4,ymm4,ymm8
	vmovdqa	ymm8,YMMWORD PTR[$L$rol8]
	vpaddd	ymm3,ymm3,ymm7
	vpaddd	ymm2,ymm2,ymm6
	vpaddd	ymm1,ymm1,ymm5
	vpaddd	ymm0,ymm0,ymm4
	vpxor	ymm15,ymm15,ymm3
	mov	r10,r13
	mov	r11,r14
	mov	r12,r15
	and	r12,3
	mov	r13,r15
	and	r13,-4
	mov	r14,r9
	shrd	r15,r9,2
	shr	r9,2
	add	r15,r13
	adc	r9,r14
	add	r10,r15
	adc	r11,r9
	adc	r12,0

$L$seal_avx2_main_loop_rounds_entry::
	vpxor	ymm14,ymm14,ymm2
	vpxor	ymm13,ymm13,ymm1
	vpxor	ymm12,ymm12,ymm0
	vpshufb	ymm15,ymm15,ymm8
	vpshufb	ymm14,ymm14,ymm8
	vpshufb	ymm13,ymm13,ymm8
	vpshufb	ymm12,ymm12,ymm8
	vpaddd	ymm11,ymm11,ymm15
	vpaddd	ymm10,ymm10,ymm14
	add	r10,QWORD PTR[((0+16))+rdi]
	adc	r11,QWORD PTR[((8+16))+rdi]
	adc	r12,1
	vpaddd	ymm9,ymm9,ymm13
	vpaddd	ymm8,ymm12,YMMWORD PTR[((160+128))+rbp]
	vpxor	ymm7,ymm7,ymm11
	vpxor	ymm6,ymm6,ymm10
	vpxor	ymm5,ymm5,ymm9
	vpxor	ymm4,ymm4,ymm8
	vmovdqa	YMMWORD PTR[(160+128)+rbp],ymm8
	vpsrld	ymm8,ymm7,25
	mov	rdx,QWORD PTR[((0+160+0))+rbp]
	mov	r15,rdx
	mulx	r14,r13,r10
	mulx	rdx,rax,r11
	imul	r15,r12
	add	r14,rax
	adc	r15,rdx
	vpslld	ymm7,ymm7,32-25
	vpxor	ymm7,ymm7,ymm8
	vpsrld	ymm8,ymm6,25
	vpslld	ymm6,ymm6,32-25
	vpxor	ymm6,ymm6,ymm8
	vpsrld	ymm8,ymm5,25
	vpslld	ymm5,ymm5,32-25
	vpxor	ymm5,ymm5,ymm8
	vpsrld	ymm8,ymm4,25
	vpslld	ymm4,ymm4,32-25
	vpxor	ymm4,ymm4,ymm8
	vmovdqa	ymm8,YMMWORD PTR[((160+128))+rbp]
	vpalignr	ymm7,ymm7,ymm7,4
	vpalignr	ymm11,ymm11,ymm11,8
	vpalignr	ymm15,ymm15,ymm15,12
	vpalignr	ymm6,ymm6,ymm6,4
	vpalignr	ymm10,ymm10,ymm10,8
	vpalignr	ymm14,ymm14,ymm14,12
	mov	rdx,QWORD PTR[((8+160+0))+rbp]
	mulx	rax,r10,r10
	add	r14,r10
	mulx	r9,r11,r11
	adc	r15,r11
	adc	r9,0
	imul	rdx,r12
	vpalignr	ymm5,ymm5,ymm5,4
	vpalignr	ymm9,ymm9,ymm9,8
	vpalignr	ymm13,ymm13,ymm13,12
	vpalignr	ymm4,ymm4,ymm4,4
	vpalignr	ymm8,ymm8,ymm8,8
	vpalignr	ymm12,ymm12,ymm12,12
	vmovdqa	YMMWORD PTR[(160+128)+rbp],ymm8
	vmovdqa	ymm8,YMMWORD PTR[$L$rol16]
	vpaddd	ymm3,ymm3,ymm7
	vpaddd	ymm2,ymm2,ymm6
	vpaddd	ymm1,ymm1,ymm5
	vpaddd	ymm0,ymm0,ymm4
	vpxor	ymm15,ymm15,ymm3
	vpxor	ymm14,ymm14,ymm2
	vpxor	ymm13,ymm13,ymm1
	vpxor	ymm12,ymm12,ymm0
	vpshufb	ymm15,ymm15,ymm8
	vpshufb	ymm14,ymm14,ymm8
	add	r15,rax
	adc	r9,rdx
	vpshufb	ymm13,ymm13,ymm8
	vpshufb	ymm12,ymm12,ymm8
	vpaddd	ymm11,ymm11,ymm15
	vpaddd	ymm10,ymm10,ymm14
	vpaddd	ymm9,ymm9,ymm13
	vpaddd	ymm8,ymm12,YMMWORD PTR[((160+128))+rbp]
	vpxor	ymm7,ymm7,ymm11
	vpxor	ymm6,ymm6,ymm10
	vpxor	ymm5,ymm5,ymm9
	mov	r10,r13
	mov	r11,r14
	mov	r12,r15
	and	r12,3
	mov	r13,r15
	and	r13,-4
	mov	r14,r9
	shrd	r15,r9,2
	shr	r9,2
	add	r15,r13
	adc	r9,r14
	add	r10,r15
	adc	r11,r9
	adc	r12,0
	vpxor	ymm4,ymm4,ymm8
	vmovdqa	YMMWORD PTR[(160+128)+rbp],ymm8
	vpsrld	ymm8,ymm7,20
	vpslld	ymm7,ymm7,32-20
	vpxor	ymm7,ymm7,ymm8
	vpsrld	ymm8,ymm6,20
	vpslld	ymm6,ymm6,32-20
	vpxor	ymm6,ymm6,ymm8
	add	r10,QWORD PTR[((0+32))+rdi]
	adc	r11,QWORD PTR[((8+32))+rdi]
	adc	r12,1

	lea	rdi,QWORD PTR[48+rdi]
	vpsrld	ymm8,ymm5,20
	vpslld	ymm5,ymm5,32-20
	vpxor	ymm5,ymm5,ymm8
	vpsrld	ymm8,ymm4,20
	vpslld	ymm4,ymm4,32-20
	vpxor	ymm4,ymm4,ymm8
	vmovdqa	ymm8,YMMWORD PTR[$L$rol8]
	vpaddd	ymm3,ymm3,ymm7
	vpaddd	ymm2,ymm2,ymm6
	vpaddd	ymm1,ymm1,ymm5
	vpaddd	ymm0,ymm0,ymm4
	vpxor	ymm15,ymm15,ymm3
	vpxor	ymm14,ymm14,ymm2
	vpxor	ymm13,ymm13,ymm1
	vpxor	ymm12,ymm12,ymm0
	vpshufb	ymm15,ymm15,ymm8
	vpshufb	ymm14,ymm14,ymm8
	vpshufb	ymm13,ymm13,ymm8
	mov	rdx,QWORD PTR[((0+160+0))+rbp]
	mov	r15,rdx
	mulx	r14,r13,r10
	mulx	rdx,rax,r11
	imul	r15,r12
	add	r14,rax
	adc	r15,rdx
	vpshufb	ymm12,ymm12,ymm8
	vpaddd	ymm11,ymm11,ymm15
	vpaddd	ymm10,ymm10,ymm14
	vpaddd	ymm9,ymm9,ymm13
	vpaddd	ymm8,ymm12,YMMWORD PTR[((160+128))+rbp]
	vpxor	ymm7,ymm7,ymm11
	vpxor	ymm6,ymm6,ymm10
	vpxor	ymm5,ymm5,ymm9
	mov	rdx,QWORD PTR[((8+160+0))+rbp]
	mulx	rax,r10,r10
	add	r14,r10
	mulx	r9,r11,r11
	adc	r15,r11
	adc	r9,0
	imul	rdx,r12
	vpxor	ymm4,ymm4,ymm8
	vmovdqa	YMMWORD PTR[(160+128)+rbp],ymm8
	vpsrld	ymm8,ymm7,25
	vpslld	ymm7,ymm7,32-25
	vpxor	ymm7,ymm7,ymm8
	vpsrld	ymm8,ymm6,25
	vpslld	ymm6,ymm6,32-25
	vpxor	ymm6,ymm6,ymm8
	add	r15,rax
	adc	r9,rdx
	vpsrld	ymm8,ymm5,25
	vpslld	ymm5,ymm5,32-25
	vpxor	ymm5,ymm5,ymm8
	vpsrld	ymm8,ymm4,25
	vpslld	ymm4,ymm4,32-25
	vpxor	ymm4,ymm4,ymm8
	vmovdqa	ymm8,YMMWORD PTR[((160+128))+rbp]
	vpalignr	ymm7,ymm7,ymm7,12
	vpalignr	ymm11,ymm11,ymm11,8
	vpalignr	ymm15,ymm15,ymm15,4
	vpalignr	ymm6,ymm6,ymm6,12
	vpalignr	ymm10,ymm10,ymm10,8
	vpalignr	ymm14,ymm14,ymm14,4
	vpalignr	ymm5,ymm5,ymm5,12
	vpalignr	ymm9,ymm9,ymm9,8
	vpalignr	ymm13,ymm13,ymm13,4
	vpalignr	ymm4,ymm4,ymm4,12
	vpalignr	ymm8,ymm8,ymm8,8
	mov	r10,r13
	mov	r11,r14
	mov	r12,r15
	and	r12,3
	mov	r13,r15
	and	r13,-4
	mov	r14,r9
	shrd	r15,r9,2
	shr	r9,2
	add	r15,r13
	adc	r9,r14
	add	r10,r15
	adc	r11,r9
	adc	r12,0
	vpalignr	ymm12,ymm12,ymm12,4

	dec	rcx
	jne	$L$seal_avx2_main_loop_rounds
	vpaddd	ymm3,ymm3,YMMWORD PTR[$L$chacha20_consts]
	vpaddd	ymm7,ymm7,YMMWORD PTR[((160+64))+rbp]
	vpaddd	ymm11,ymm11,YMMWORD PTR[((160+96))+rbp]
	vpaddd	ymm15,ymm15,YMMWORD PTR[((160+256))+rbp]
	vpaddd	ymm2,ymm2,YMMWORD PTR[$L$chacha20_consts]
	vpaddd	ymm6,ymm6,YMMWORD PTR[((160+64))+rbp]
	vpaddd	ymm10,ymm10,YMMWORD PTR[((160+96))+rbp]
	vpaddd	ymm14,ymm14,YMMWORD PTR[((160+224))+rbp]
	vpaddd	ymm1,ymm1,YMMWORD PTR[$L$chacha20_consts]
	vpaddd	ymm5,ymm5,YMMWORD PTR[((160+64))+rbp]
	vpaddd	ymm9,ymm9,YMMWORD PTR[((160+96))+rbp]
	vpaddd	ymm13,ymm13,YMMWORD PTR[((160+192))+rbp]
	vpaddd	ymm0,ymm0,YMMWORD PTR[$L$chacha20_consts]
	vpaddd	ymm4,ymm4,YMMWORD PTR[((160+64))+rbp]
	vpaddd	ymm8,ymm8,YMMWORD PTR[((160+96))+rbp]
	vpaddd	ymm12,ymm12,YMMWORD PTR[((160+160))+rbp]

	vmovdqa	YMMWORD PTR[(160+128)+rbp],ymm0
	add	r10,QWORD PTR[((0+0))+rdi]
	adc	r11,QWORD PTR[((8+0))+rdi]
	adc	r12,1
	mov	rdx,QWORD PTR[((0+160+0))+rbp]
	mov	r15,rdx
	mulx	r14,r13,r10
	mulx	rdx,rax,r11
	imul	r15,r12
	add	r14,rax
	adc	r15,rdx
	mov	rdx,QWORD PTR[((8+160+0))+rbp]
	mulx	rax,r10,r10
	add	r14,r10
	mulx	r9,r11,r11
	adc	r15,r11
	adc	r9,0
	imul	rdx,r12
	add	r15,rax
	adc	r9,rdx
	mov	r10,r13
	mov	r11,r14
	mov	r12,r15
	and	r12,3
	mov	r13,r15
	and	r13,-4
	mov	r14,r9
	shrd	r15,r9,2
	shr	r9,2
	add	r15,r13
	adc	r9,r14
	add	r10,r15
	adc	r11,r9
	adc	r12,0
	add	r10,QWORD PTR[((0+16))+rdi]
	adc	r11,QWORD PTR[((8+16))+rdi]
	adc	r12,1
	mov	rdx,QWORD PTR[((0+160+0))+rbp]
	mov	r15,rdx
	mulx	r14,r13,r10
	mulx	rdx,rax,r11
	imul	r15,r12
	add	r14,rax
	adc	r15,rdx
	mov	rdx,QWORD PTR[((8+160+0))+rbp]
	mulx	rax,r10,r10
	add	r14,r10
	mulx	r9,r11,r11
	adc	r15,r11
	adc	r9,0
	imul	rdx,r12
	add	r15,rax
	adc	r9,rdx
	mov	r10,r13
	mov	r11,r14
	mov	r12,r15
	and	r12,3
	mov	r13,r15
	and	r13,-4
	mov	r14,r9
	shrd	r15,r9,2
	shr	r9,2
	add	r15,r13
	adc	r9,r14
	add	r10,r15
	adc	r11,r9
	adc	r12,0

	lea	rdi,QWORD PTR[32+rdi]
	vperm2i128	ymm0,ymm7,ymm3,002h
	vperm2i128	ymm7,ymm7,ymm3,013h
	vperm2i128	ymm3,ymm15,ymm11,002h
	vperm2i128	ymm11,ymm15,ymm11,013h
	vpxor	ymm0,ymm0,YMMWORD PTR[((0+0))+rsi]
	vpxor	ymm3,ymm3,YMMWORD PTR[((32+0))+rsi]
	vpxor	ymm7,ymm7,YMMWORD PTR[((64+0))+rsi]
	vpxor	ymm11,ymm11,YMMWORD PTR[((96+0))+rsi]
	vmovdqu	YMMWORD PTR[(0+0)+rdi],ymm0
	vmovdqu	YMMWORD PTR[(32+0)+rdi],ymm3
	vmovdqu	YMMWORD PTR[(64+0)+rdi],ymm7
	vmovdqu	YMMWORD PTR[(96+0)+rdi],ymm11

	vmovdqa	ymm0,YMMWORD PTR[((160+128))+rbp]
	vperm2i128	ymm3,ymm6,ymm2,002h
	vperm2i128	ymm6,ymm6,ymm2,013h
	vperm2i128	ymm2,ymm14,ymm10,002h
	vperm2i128	ymm10,ymm14,ymm10,013h
	vpxor	ymm3,ymm3,YMMWORD PTR[((0+128))+rsi]
	vpxor	ymm2,ymm2,YMMWORD PTR[((32+128))+rsi]
	vpxor	ymm6,ymm6,YMMWORD PTR[((64+128))+rsi]
	vpxor	ymm10,ymm10,YMMWORD PTR[((96+128))+rsi]
	vmovdqu	YMMWORD PTR[(0+128)+rdi],ymm3
	vmovdqu	YMMWORD PTR[(32+128)+rdi],ymm2
	vmovdqu	YMMWORD PTR[(64+128)+rdi],ymm6
	vmovdqu	YMMWORD PTR[(96+128)+rdi],ymm10
	vperm2i128	ymm3,ymm5,ymm1,002h
	vperm2i128	ymm5,ymm5,ymm1,013h
	vperm2i128	ymm1,ymm13,ymm9,002h
	vperm2i128	ymm9,ymm13,ymm9,013h
	vpxor	ymm3,ymm3,YMMWORD PTR[((0+256))+rsi]
	vpxor	ymm1,ymm1,YMMWORD PTR[((32+256))+rsi]
	vpxor	ymm5,ymm5,YMMWORD PTR[((64+256))+rsi]
	vpxor	ymm9,ymm9,YMMWORD PTR[((96+256))+rsi]
	vmovdqu	YMMWORD PTR[(0+256)+rdi],ymm3
	vmovdqu	YMMWORD PTR[(32+256)+rdi],ymm1
	vmovdqu	YMMWORD PTR[(64+256)+rdi],ymm5
	vmovdqu	YMMWORD PTR[(96+256)+rdi],ymm9
	vperm2i128	ymm3,ymm4,ymm0,002h
	vperm2i128	ymm4,ymm4,ymm0,013h
	vperm2i128	ymm0,ymm12,ymm8,002h
	vperm2i128	ymm8,ymm12,ymm8,013h
	vpxor	ymm3,ymm3,YMMWORD PTR[((0+384))+rsi]
	vpxor	ymm0,ymm0,YMMWORD PTR[((32+384))+rsi]
	vpxor	ymm4,ymm4,YMMWORD PTR[((64+384))+rsi]
	vpxor	ymm8,ymm8,YMMWORD PTR[((96+384))+rsi]
	vmovdqu	YMMWORD PTR[(0+384)+rdi],ymm3
	vmovdqu	YMMWORD PTR[(32+384)+rdi],ymm0
	vmovdqu	YMMWORD PTR[(64+384)+rdi],ymm4
	vmovdqu	YMMWORD PTR[(96+384)+rdi],ymm8

	lea	rsi,QWORD PTR[512+rsi]
	sub	rbx,16*32
	cmp	rbx,16*32
	jg	$L$seal_avx2_main_loop

	add	r10,QWORD PTR[((0+0))+rdi]
	adc	r11,QWORD PTR[((8+0))+rdi]
	adc	r12,1
	mov	rdx,QWORD PTR[((0+160+0))+rbp]
	mov	r15,rdx
	mulx	r14,r13,r10
	mulx	rdx,rax,r11
	imul	r15,r12
	add	r14,rax
	adc	r15,rdx
	mov	rdx,QWORD PTR[((8+160+0))+rbp]
	mulx	rax,r10,r10
	add	r14,r10
	mulx	r9,r11,r11
	adc	r15,r11
	adc	r9,0
	imul	rdx,r12
	add	r15,rax
	adc	r9,rdx
	mov	r10,r13
	mov	r11,r14
	mov	r12,r15
	and	r12,3
	mov	r13,r15
	and	r13,-4
	mov	r14,r9
	shrd	r15,r9,2
	shr	r9,2
	add	r15,r13
	adc	r9,r14
	add	r10,r15
	adc	r11,r9
	adc	r12,0
	add	r10,QWORD PTR[((0+16))+rdi]
	adc	r11,QWORD PTR[((8+16))+rdi]
	adc	r12,1
	mov	rdx,QWORD PTR[((0+160+0))+rbp]
	mov	r15,rdx
	mulx	r14,r13,r10
	mulx	rdx,rax,r11
	imul	r15,r12
	add	r14,rax
	adc	r15,rdx
	mov	rdx,QWORD PTR[((8+160+0))+rbp]
	mulx	rax,r10,r10
	add	r14,r10
	mulx	r9,r11,r11
	adc	r15,r11
	adc	r9,0
	imul	rdx,r12
	add	r15,rax
	adc	r9,rdx
	mov	r10,r13
	mov	r11,r14
	mov	r12,r15
	and	r12,3
	mov	r13,r15
	and	r13,-4
	mov	r14,r9
	shrd	r15,r9,2
	shr	r9,2
	add	r15,r13
	adc	r9,r14
	add	r10,r15
	adc	r11,r9
	adc	r12,0

	lea	rdi,QWORD PTR[32+rdi]
	mov	rcx,10
	xor	r8,r8

	cmp	rbx,12*32
	ja	$L$seal_avx2_tail_512
	cmp	rbx,8*32
	ja	$L$seal_avx2_tail_384
	cmp	rbx,4*32
	ja	$L$seal_avx2_tail_256

$L$seal_avx2_tail_128::
	vmovdqa	ymm0,YMMWORD PTR[$L$chacha20_consts]
	vmovdqa	ymm4,YMMWORD PTR[((160+64))+rbp]
	vmovdqa	ymm8,YMMWORD PTR[((160+96))+rbp]
	vmovdqa	ymm12,YMMWORD PTR[$L$avx2_inc]
	vpaddd	ymm12,ymm12,YMMWORD PTR[((160+160))+rbp]
	vmovdqa	YMMWORD PTR[(160+160)+rbp],ymm12

$L$seal_avx2_tail_128_rounds_and_3xhash::
	add	r10,QWORD PTR[((0+0))+rdi]
	adc	r11,QWORD PTR[((8+0))+rdi]
	adc	r12,1
	mov	rdx,QWORD PTR[((0+160+0))+rbp]
	mov	r15,rdx
	mulx	r14,r13,r10
	mulx	rdx,rax,r11
	imul	r15,r12
	add	r14,rax
	adc	r15,rdx
	mov	rdx,QWORD PTR[((8+160+0))+rbp]
	mulx	rax,r10,r10
	add	r14,r10
	mulx	r9,r11,r11
	adc	r15,r11
	adc	r9,0
	imul	rdx,r12
	add	r15,rax
	adc	r9,rdx
	mov	r10,r13
	mov	r11,r14
	mov	r12,r15
	and	r12,3
	mov	r13,r15
	and	r13,-4
	mov	r14,r9
	shrd	r15,r9,2
	shr	r9,2
	add	r15,r13
	adc	r9,r14
	add	r10,r15
	adc	r11,r9
	adc	r12,0

	lea	rdi,QWORD PTR[16+rdi]
$L$seal_avx2_tail_128_rounds_and_2xhash::
	vpaddd	ymm0,ymm0,ymm4
	vpxor	ymm12,ymm12,ymm0
	vpshufb	ymm12,ymm12,YMMWORD PTR[$L$rol16]
	vpaddd	ymm8,ymm8,ymm12
	vpxor	ymm4,ymm4,ymm8
	vpsrld	ymm3,ymm4,20
	vpslld	ymm4,ymm4,12
	vpxor	ymm4,ymm4,ymm3
	vpaddd	ymm0,ymm0,ymm4
	vpxor	ymm12,ymm12,ymm0
	vpshufb	ymm12,ymm12,YMMWORD PTR[$L$rol8]
	vpaddd	ymm8,ymm8,ymm12
	vpxor	ymm4,ymm4,ymm8
	vpslld	ymm3,ymm4,7
	vpsrld	ymm4,ymm4,25
	vpxor	ymm4,ymm4,ymm3
	vpalignr	ymm12,ymm12,ymm12,12
	vpalignr	ymm8,ymm8,ymm8,8
	vpalignr	ymm4,ymm4,ymm4,4
	add	r10,QWORD PTR[((0+0))+rdi]
	adc	r11,QWORD PTR[((8+0))+rdi]
	adc	r12,1
	mov	rdx,QWORD PTR[((0+160+0))+rbp]
	mov	r15,rdx
	mulx	r14,r13,r10
	mulx	rdx,rax,r11
	imul	r15,r12
	add	r14,rax
	adc	r15,rdx
	mov	rdx,QWORD PTR[((8+160+0))+rbp]
	mulx	rax,r10,r10
	add	r14,r10
	mulx	r9,r11,r11
	adc	r15,r11
	adc	r9,0
	imul	rdx,r12
	add	r15,rax
	adc	r9,rdx
	mov	r10,r13
	mov	r11,r14
	mov	r12,r15
	and	r12,3
	mov	r13,r15
	and	r13,-4
	mov	r14,r9
	shrd	r15,r9,2
	shr	r9,2
	add	r15,r13
	adc	r9,r14
	add	r10,r15
	adc	r11,r9
	adc	r12,0
	vpaddd	ymm0,ymm0,ymm4
	vpxor	ymm12,ymm12,ymm0
	vpshufb	ymm12,ymm12,YMMWORD PTR[$L$rol16]
	vpaddd	ymm8,ymm8,ymm12
	vpxor	ymm4,ymm4,ymm8
	vpsrld	ymm3,ymm4,20
	vpslld	ymm4,ymm4,12
	vpxor	ymm4,ymm4,ymm3
	vpaddd	ymm0,ymm0,ymm4
	vpxor	ymm12,ymm12,ymm0
	vpshufb	ymm12,ymm12,YMMWORD PTR[$L$rol8]
	vpaddd	ymm8,ymm8,ymm12
	vpxor	ymm4,ymm4,ymm8
	vpslld	ymm3,ymm4,7
	vpsrld	ymm4,ymm4,25
	vpxor	ymm4,ymm4,ymm3
	vpalignr	ymm12,ymm12,ymm12,4
	vpalignr	ymm8,ymm8,ymm8,8
	vpalignr	ymm4,ymm4,ymm4,12
	add	r10,QWORD PTR[((0+16))+rdi]
	adc	r11,QWORD PTR[((8+16))+rdi]
	adc	r12,1
	mov	rdx,QWORD PTR[((0+160+0))+rbp]
	mov	r15,rdx
	mulx	r14,r13,r10
	mulx	rdx,rax,r11
	imul	r15,r12
	add	r14,rax
	adc	r15,rdx
	mov	rdx,QWORD PTR[((8+160+0))+rbp]
	mulx	rax,r10,r10
	add	r14,r10
	mulx	r9,r11,r11
	adc	r15,r11
	adc	r9,0
	imul	rdx,r12
	add	r15,rax
	adc	r9,rdx
	mov	r10,r13
	mov	r11,r14
	mov	r12,r15
	and	r12,3
	mov	r13,r15
	and	r13,-4
	mov	r14,r9
	shrd	r15,r9,2
	shr	r9,2
	add	r15,r13
	adc	r9,r14
	add	r10,r15
	adc	r11,r9
	adc	r12,0

	lea	rdi,QWORD PTR[32+rdi]
	dec	rcx
	jg	$L$seal_avx2_tail_128_rounds_and_3xhash
	dec	r8
	jge	$L$seal_avx2_tail_128_rounds_and_2xhash
	vpaddd	ymm0,ymm0,YMMWORD PTR[$L$chacha20_consts]
	vpaddd	ymm4,ymm4,YMMWORD PTR[((160+64))+rbp]
	vpaddd	ymm8,ymm8,YMMWORD PTR[((160+96))+rbp]
	vpaddd	ymm12,ymm12,YMMWORD PTR[((160+160))+rbp]
	vperm2i128	ymm3,ymm4,ymm0,013h
	vperm2i128	ymm0,ymm4,ymm0,002h
	vperm2i128	ymm4,ymm12,ymm8,002h
	vperm2i128	ymm12,ymm12,ymm8,013h
	vmovdqa	ymm8,ymm3

	jmp	$L$seal_avx2_short_loop

$L$seal_avx2_tail_256::
	vmovdqa	ymm0,YMMWORD PTR[$L$chacha20_consts]
	vmovdqa	ymm4,YMMWORD PTR[((160+64))+rbp]
	vmovdqa	ymm8,YMMWORD PTR[((160+96))+rbp]
	vmovdqa	ymm1,ymm0
	vmovdqa	ymm5,ymm4
	vmovdqa	ymm9,ymm8
	vmovdqa	ymm12,YMMWORD PTR[$L$avx2_inc]
	vpaddd	ymm13,ymm12,YMMWORD PTR[((160+160))+rbp]
	vpaddd	ymm12,ymm12,ymm13
	vmovdqa	YMMWORD PTR[(160+160)+rbp],ymm12
	vmovdqa	YMMWORD PTR[(160+192)+rbp],ymm13

$L$seal_avx2_tail_256_rounds_and_3xhash::
	add	r10,QWORD PTR[((0+0))+rdi]
	adc	r11,QWORD PTR[((8+0))+rdi]
	adc	r12,1
	mov	rax,QWORD PTR[((0+160+0))+rbp]
	mov	r15,rax
	mul	r10
	mov	r13,rax
	mov	r14,rdx
	mov	rax,QWORD PTR[((0+160+0))+rbp]
	mul	r11
	imul	r15,r12
	add	r14,rax
	adc	r15,rdx
	mov	rax,QWORD PTR[((8+160+0))+rbp]
	mov	r9,rax
	mul	r10
	add	r14,rax
	adc	rdx,0
	mov	r10,rdx
	mov	rax,QWORD PTR[((8+160+0))+rbp]
	mul	r11
	add	r15,rax
	adc	rdx,0
	imul	r9,r12
	add	r15,r10
	adc	r9,rdx
	mov	r10,r13
	mov	r11,r14
	mov	r12,r15
	and	r12,3
	mov	r13,r15
	and	r13,-4
	mov	r14,r9
	shrd	r15,r9,2
	shr	r9,2
	add	r15,r13
	adc	r9,r14
	add	r10,r15
	adc	r11,r9
	adc	r12,0

	lea	rdi,QWORD PTR[16+rdi]
$L$seal_avx2_tail_256_rounds_and_2xhash::
	vpaddd	ymm0,ymm0,ymm4
	vpxor	ymm12,ymm12,ymm0
	vpshufb	ymm12,ymm12,YMMWORD PTR[$L$rol16]
	vpaddd	ymm8,ymm8,ymm12
	vpxor	ymm4,ymm4,ymm8
	vpsrld	ymm3,ymm4,20
	vpslld	ymm4,ymm4,12
	vpxor	ymm4,ymm4,ymm3
	vpaddd	ymm0,ymm0,ymm4
	vpxor	ymm12,ymm12,ymm0
	vpshufb	ymm12,ymm12,YMMWORD PTR[$L$rol8]
	vpaddd	ymm8,ymm8,ymm12
	vpxor	ymm4,ymm4,ymm8
	vpslld	ymm3,ymm4,7
	vpsrld	ymm4,ymm4,25
	vpxor	ymm4,ymm4,ymm3
	vpalignr	ymm12,ymm12,ymm12,12
	vpalignr	ymm8,ymm8,ymm8,8
	vpalignr	ymm4,ymm4,ymm4,4
	vpaddd	ymm1,ymm1,ymm5
	vpxor	ymm13,ymm13,ymm1
	vpshufb	ymm13,ymm13,YMMWORD PTR[$L$rol16]
	vpaddd	ymm9,ymm9,ymm13
	vpxor	ymm5,ymm5,ymm9
	vpsrld	ymm3,ymm5,20
	vpslld	ymm5,ymm5,12
	vpxor	ymm5,ymm5,ymm3
	vpaddd	ymm1,ymm1,ymm5
	vpxor	ymm13,ymm13,ymm1
	vpshufb	ymm13,ymm13,YMMWORD PTR[$L$rol8]
	vpaddd	ymm9,ymm9,ymm13
	vpxor	ymm5,ymm5,ymm9
	vpslld	ymm3,ymm5,7
	vpsrld	ymm5,ymm5,25
	vpxor	ymm5,ymm5,ymm3
	vpalignr	ymm13,ymm13,ymm13,12
	vpalignr	ymm9,ymm9,ymm9,8
	vpalignr	ymm5,ymm5,ymm5,4
	add	r10,QWORD PTR[((0+0))+rdi]
	adc	r11,QWORD PTR[((8+0))+rdi]
	adc	r12,1
	mov	rax,QWORD PTR[((0+160+0))+rbp]
	mov	r15,rax
	mul	r10
	mov	r13,rax
	mov	r14,rdx
	mov	rax,QWORD PTR[((0+160+0))+rbp]
	mul	r11
	imul	r15,r12
	add	r14,rax
	adc	r15,rdx
	mov	rax,QWORD PTR[((8+160+0))+rbp]
	mov	r9,rax
	mul	r10
	add	r14,rax
	adc	rdx,0
	mov	r10,rdx
	mov	rax,QWORD PTR[((8+160+0))+rbp]
	mul	r11
	add	r15,rax
	adc	rdx,0
	imul	r9,r12
	add	r15,r10
	adc	r9,rdx
	mov	r10,r13
	mov	r11,r14
	mov	r12,r15
	and	r12,3
	mov	r13,r15
	and	r13,-4
	mov	r14,r9
	shrd	r15,r9,2
	shr	r9,2
	add	r15,r13
	adc	r9,r14
	add	r10,r15
	adc	r11,r9
	adc	r12,0
	vpaddd	ymm0,ymm0,ymm4
	vpxor	ymm12,ymm12,ymm0
	vpshufb	ymm12,ymm12,YMMWORD PTR[$L$rol16]
	vpaddd	ymm8,ymm8,ymm12
	vpxor	ymm4,ymm4,ymm8
	vpsrld	ymm3,ymm4,20
	vpslld	ymm4,ymm4,12
	vpxor	ymm4,ymm4,ymm3
	vpaddd	ymm0,ymm0,ymm4
	vpxor	ymm12,ymm12,ymm0
	vpshufb	ymm12,ymm12,YMMWORD PTR[$L$rol8]
	vpaddd	ymm8,ymm8,ymm12
	vpxor	ymm4,ymm4,ymm8
	vpslld	ymm3,ymm4,7
	vpsrld	ymm4,ymm4,25
	vpxor	ymm4,ymm4,ymm3
	vpalignr	ymm12,ymm12,ymm12,4
	vpalignr	ymm8,ymm8,ymm8,8
	vpalignr	ymm4,ymm4,ymm4,12
	vpaddd	ymm1,ymm1,ymm5
	vpxor	ymm13,ymm13,ymm1
	vpshufb	ymm13,ymm13,YMMWORD PTR[$L$rol16]
	vpaddd	ymm9,ymm9,ymm13
	vpxor	ymm5,ymm5,ymm9
	vpsrld	ymm3,ymm5,20
	vpslld	ymm5,ymm5,12
	vpxor	ymm5,ymm5,ymm3
	vpaddd	ymm1,ymm1,ymm5
	vpxor	ymm13,ymm13,ymm1
	vpshufb	ymm13,ymm13,YMMWORD PTR[$L$rol8]
	vpaddd	ymm9,ymm9,ymm13
	vpxor	ymm5,ymm5,ymm9
	vpslld	ymm3,ymm5,7
	vpsrld	ymm5,ymm5,25
	vpxor	ymm5,ymm5,ymm3
	vpalignr	ymm13,ymm13,ymm13,4
	vpalignr	ymm9,ymm9,ymm9,8
	vpalignr	ymm5,ymm5,ymm5,12
	add	r10,QWORD PTR[((0+16))+rdi]
	adc	r11,QWORD PTR[((8+16))+rdi]
	adc	r12,1
	mov	rax,QWORD PTR[((0+160+0))+rbp]
	mov	r15,rax
	mul	r10
	mov	r13,rax
	mov	r14,rdx
	mov	rax,QWORD PTR[((0+160+0))+rbp]
	mul	r11
	imul	r15,r12
	add	r14,rax
	adc	r15,rdx
	mov	rax,QWORD PTR[((8+160+0))+rbp]
	mov	r9,rax
	mul	r10
	add	r14,rax
	adc	rdx,0
	mov	r10,rdx
	mov	rax,QWORD PTR[((8+160+0))+rbp]
	mul	r11
	add	r15,rax
	adc	rdx,0
	imul	r9,r12
	add	r15,r10
	adc	r9,rdx
	mov	r10,r13
	mov	r11,r14
	mov	r12,r15
	and	r12,3
	mov	r13,r15
	and	r13,-4
	mov	r14,r9
	shrd	r15,r9,2
	shr	r9,2
	add	r15,r13
	adc	r9,r14
	add	r10,r15
	adc	r11,r9
	adc	r12,0

	lea	rdi,QWORD PTR[32+rdi]
	dec	rcx
	jg	$L$seal_avx2_tail_256_rounds_and_3xhash
	dec	r8
	jge	$L$seal_avx2_tail_256_rounds_and_2xhash
	vpaddd	ymm1,ymm1,YMMWORD PTR[$L$chacha20_consts]
	vpaddd	ymm5,ymm5,YMMWORD PTR[((160+64))+rbp]
	vpaddd	ymm9,ymm9,YMMWORD PTR[((160+96))+rbp]
	vpaddd	ymm13,ymm13,YMMWORD PTR[((160+192))+rbp]
	vpaddd	ymm0,ymm0,YMMWORD PTR[$L$chacha20_consts]
	vpaddd	ymm4,ymm4,YMMWORD PTR[((160+64))+rbp]
	vpaddd	ymm8,ymm8,YMMWORD PTR[((160+96))+rbp]
	vpaddd	ymm12,ymm12,YMMWORD PTR[((160+160))+rbp]
	vperm2i128	ymm3,ymm5,ymm1,002h
	vperm2i128	ymm5,ymm5,ymm1,013h
	vperm2i128	ymm1,ymm13,ymm9,002h
	vperm2i128	ymm9,ymm13,ymm9,013h
	vpxor	ymm3,ymm3,YMMWORD PTR[((0+0))+rsi]
	vpxor	ymm1,ymm1,YMMWORD PTR[((32+0))+rsi]
	vpxor	ymm5,ymm5,YMMWORD PTR[((64+0))+rsi]
	vpxor	ymm9,ymm9,YMMWORD PTR[((96+0))+rsi]
	vmovdqu	YMMWORD PTR[(0+0)+rdi],ymm3
	vmovdqu	YMMWORD PTR[(32+0)+rdi],ymm1
	vmovdqu	YMMWORD PTR[(64+0)+rdi],ymm5
	vmovdqu	YMMWORD PTR[(96+0)+rdi],ymm9
	vperm2i128	ymm3,ymm4,ymm0,013h
	vperm2i128	ymm0,ymm4,ymm0,002h
	vperm2i128	ymm4,ymm12,ymm8,002h
	vperm2i128	ymm12,ymm12,ymm8,013h
	vmovdqa	ymm8,ymm3

	mov	rcx,4*32
	lea	rsi,QWORD PTR[128+rsi]
	sub	rbx,4*32
	jmp	$L$seal_avx2_short_hash_remainder

$L$seal_avx2_tail_384::
	vmovdqa	ymm0,YMMWORD PTR[$L$chacha20_consts]
	vmovdqa	ymm4,YMMWORD PTR[((160+64))+rbp]
	vmovdqa	ymm8,YMMWORD PTR[((160+96))+rbp]
	vmovdqa	ymm1,ymm0
	vmovdqa	ymm5,ymm4
	vmovdqa	ymm9,ymm8
	vmovdqa	ymm2,ymm0
	vmovdqa	ymm6,ymm4
	vmovdqa	ymm10,ymm8
	vmovdqa	ymm12,YMMWORD PTR[$L$avx2_inc]
	vpaddd	ymm14,ymm12,YMMWORD PTR[((160+160))+rbp]
	vpaddd	ymm13,ymm12,ymm14
	vpaddd	ymm12,ymm12,ymm13
	vmovdqa	YMMWORD PTR[(160+160)+rbp],ymm12
	vmovdqa	YMMWORD PTR[(160+192)+rbp],ymm13
	vmovdqa	YMMWORD PTR[(160+224)+rbp],ymm14

$L$seal_avx2_tail_384_rounds_and_3xhash::
	add	r10,QWORD PTR[((0+0))+rdi]
	adc	r11,QWORD PTR[((8+0))+rdi]
	adc	r12,1
	mov	rax,QWORD PTR[((0+160+0))+rbp]
	mov	r15,rax
	mul	r10
	mov	r13,rax
	mov	r14,rdx
	mov	rax,QWORD PTR[((0+160+0))+rbp]
	mul	r11
	imul	r15,r12
	add	r14,rax
	adc	r15,rdx
	mov	rax,QWORD PTR[((8+160+0))+rbp]
	mov	r9,rax
	mul	r10
	add	r14,rax
	adc	rdx,0
	mov	r10,rdx
	mov	rax,QWORD PTR[((8+160+0))+rbp]
	mul	r11
	add	r15,rax
	adc	rdx,0
	imul	r9,r12
	add	r15,r10
	adc	r9,rdx
	mov	r10,r13
	mov	r11,r14
	mov	r12,r15
	and	r12,3
	mov	r13,r15
	and	r13,-4
	mov	r14,r9
	shrd	r15,r9,2
	shr	r9,2
	add	r15,r13
	adc	r9,r14
	add	r10,r15
	adc	r11,r9
	adc	r12,0

	lea	rdi,QWORD PTR[16+rdi]
$L$seal_avx2_tail_384_rounds_and_2xhash::
	vpaddd	ymm0,ymm0,ymm4
	vpxor	ymm12,ymm12,ymm0
	vpshufb	ymm12,ymm12,YMMWORD PTR[$L$rol16]
	vpaddd	ymm8,ymm8,ymm12
	vpxor	ymm4,ymm4,ymm8
	vpsrld	ymm3,ymm4,20
	vpslld	ymm4,ymm4,12
	vpxor	ymm4,ymm4,ymm3
	vpaddd	ymm0,ymm0,ymm4
	vpxor	ymm12,ymm12,ymm0
	vpshufb	ymm12,ymm12,YMMWORD PTR[$L$rol8]
	vpaddd	ymm8,ymm8,ymm12
	vpxor	ymm4,ymm4,ymm8
	vpslld	ymm3,ymm4,7
	vpsrld	ymm4,ymm4,25
	vpxor	ymm4,ymm4,ymm3
	vpalignr	ymm12,ymm12,ymm12,12
	vpalignr	ymm8,ymm8,ymm8,8
	vpalignr	ymm4,ymm4,ymm4,4
	vpaddd	ymm1,ymm1,ymm5
	vpxor	ymm13,ymm13,ymm1
	vpshufb	ymm13,ymm13,YMMWORD PTR[$L$rol16]
	vpaddd	ymm9,ymm9,ymm13
	vpxor	ymm5,ymm5,ymm9
	vpsrld	ymm3,ymm5,20
	vpslld	ymm5,ymm5,12
	vpxor	ymm5,ymm5,ymm3
	vpaddd	ymm1,ymm1,ymm5
	vpxor	ymm13,ymm13,ymm1
	vpshufb	ymm13,ymm13,YMMWORD PTR[$L$rol8]
	vpaddd	ymm9,ymm9,ymm13
	vpxor	ymm5,ymm5,ymm9
	vpslld	ymm3,ymm5,7
	vpsrld	ymm5,ymm5,25
	vpxor	ymm5,ymm5,ymm3
	vpalignr	ymm13,ymm13,ymm13,12
	vpalignr	ymm9,ymm9,ymm9,8
	vpalignr	ymm5,ymm5,ymm5,4
	add	r10,QWORD PTR[((0+0))+rdi]
	adc	r11,QWORD PTR[((8+0))+rdi]
	adc	r12,1
	mov	rax,QWORD PTR[((0+160+0))+rbp]
	mov	r15,rax
	mul	r10
	mov	r13,rax
	mov	r14,rdx
	mov	rax,QWORD PTR[((0+160+0))+rbp]
	mul	r11
	imul	r15,r12
	add	r14,rax
	adc	r15,rdx
	mov	rax,QWORD PTR[((8+160+0))+rbp]
	mov	r9,rax
	mul	r10
	add	r14,rax
	adc	rdx,0
	mov	r10,rdx
	mov	rax,QWORD PTR[((8+160+0))+rbp]
	mul	r11
	add	r15,rax
	adc	rdx,0
	imul	r9,r12
	add	r15,r10
	adc	r9,rdx
	mov	r10,r13
	mov	r11,r14
	mov	r12,r15
	and	r12,3
	mov	r13,r15
	and	r13,-4
	mov	r14,r9
	shrd	r15,r9,2
	shr	r9,2
	add	r15,r13
	adc	r9,r14
	add	r10,r15
	adc	r11,r9
	adc	r12,0
	vpaddd	ymm2,ymm2,ymm6
	vpxor	ymm14,ymm14,ymm2
	vpshufb	ymm14,ymm14,YMMWORD PTR[$L$rol16]
	vpaddd	ymm10,ymm10,ymm14
	vpxor	ymm6,ymm6,ymm10
	vpsrld	ymm3,ymm6,20
	vpslld	ymm6,ymm6,12
	vpxor	ymm6,ymm6,ymm3
	vpaddd	ymm2,ymm2,ymm6
	vpxor	ymm14,ymm14,ymm2
	vpshufb	ymm14,ymm14,YMMWORD PTR[$L$rol8]
	vpaddd	ymm10,ymm10,ymm14
	vpxor	ymm6,ymm6,ymm10
	vpslld	ymm3,ymm6,7
	vpsrld	ymm6,ymm6,25
	vpxor	ymm6,ymm6,ymm3
	vpalignr	ymm14,ymm14,ymm14,12
	vpalignr	ymm10,ymm10,ymm10,8
	vpalignr	ymm6,ymm6,ymm6,4
	vpaddd	ymm0,ymm0,ymm4
	vpxor	ymm12,ymm12,ymm0
	vpshufb	ymm12,ymm12,YMMWORD PTR[$L$rol16]
	vpaddd	ymm8,ymm8,ymm12
	vpxor	ymm4,ymm4,ymm8
	vpsrld	ymm3,ymm4,20
	vpslld	ymm4,ymm4,12
	vpxor	ymm4,ymm4,ymm3
	vpaddd	ymm0,ymm0,ymm4
	vpxor	ymm12,ymm12,ymm0
	vpshufb	ymm12,ymm12,YMMWORD PTR[$L$rol8]
	vpaddd	ymm8,ymm8,ymm12
	vpxor	ymm4,ymm4,ymm8
	vpslld	ymm3,ymm4,7
	vpsrld	ymm4,ymm4,25
	vpxor	ymm4,ymm4,ymm3
	vpalignr	ymm12,ymm12,ymm12,4
	vpalignr	ymm8,ymm8,ymm8,8
	vpalignr	ymm4,ymm4,ymm4,12
	add	r10,QWORD PTR[((0+16))+rdi]
	adc	r11,QWORD PTR[((8+16))+rdi]
	adc	r12,1
	mov	rax,QWORD PTR[((0+160+0))+rbp]
	mov	r15,rax
	mul	r10
	mov	r13,rax
	mov	r14,rdx
	mov	rax,QWORD PTR[((0+160+0))+rbp]
	mul	r11
	imul	r15,r12
	add	r14,rax
	adc	r15,rdx
	mov	rax,QWORD PTR[((8+160+0))+rbp]
	mov	r9,rax
	mul	r10
	add	r14,rax
	adc	rdx,0
	mov	r10,rdx
	mov	rax,QWORD PTR[((8+160+0))+rbp]
	mul	r11
	add	r15,rax
	adc	rdx,0
	imul	r9,r12
	add	r15,r10
	adc	r9,rdx
	mov	r10,r13
	mov	r11,r14
	mov	r12,r15
	and	r12,3
	mov	r13,r15
	and	r13,-4
	mov	r14,r9
	shrd	r15,r9,2
	shr	r9,2
	add	r15,r13
	adc	r9,r14
	add	r10,r15
	adc	r11,r9
	adc	r12,0
	vpaddd	ymm1,ymm1,ymm5
	vpxor	ymm13,ymm13,ymm1
	vpshufb	ymm13,ymm13,YMMWORD PTR[$L$rol16]
	vpaddd	ymm9,ymm9,ymm13
	vpxor	ymm5,ymm5,ymm9
	vpsrld	ymm3,ymm5,20
	vpslld	ymm5,ymm5,12
	vpxor	ymm5,ymm5,ymm3
	vpaddd	ymm1,ymm1,ymm5
	vpxor	ymm13,ymm13,ymm1
	vpshufb	ymm13,ymm13,YMMWORD PTR[$L$rol8]
	vpaddd	ymm9,ymm9,ymm13
	vpxor	ymm5,ymm5,ymm9
	vpslld	ymm3,ymm5,7
	vpsrld	ymm5,ymm5,25
	vpxor	ymm5,ymm5,ymm3
	vpalignr	ymm13,ymm13,ymm13,4
	vpalignr	ymm9,ymm9,ymm9,8
	vpalignr	ymm5,ymm5,ymm5,12
	vpaddd	ymm2,ymm2,ymm6
	vpxor	ymm14,ymm14,ymm2
	vpshufb	ymm14,ymm14,YMMWORD PTR[$L$rol16]
	vpaddd	ymm10,ymm10,ymm14
	vpxor	ymm6,ymm6,ymm10
	vpsrld	ymm3,ymm6,20
	vpslld	ymm6,ymm6,12
	vpxor	ymm6,ymm6,ymm3
	vpaddd	ymm2,ymm2,ymm6
	vpxor	ymm14,ymm14,ymm2
	vpshufb	ymm14,ymm14,YMMWORD PTR[$L$rol8]
	vpaddd	ymm10,ymm10,ymm14
	vpxor	ymm6,ymm6,ymm10
	vpslld	ymm3,ymm6,7
	vpsrld	ymm6,ymm6,25
	vpxor	ymm6,ymm6,ymm3
	vpalignr	ymm14,ymm14,ymm14,4
	vpalignr	ymm10,ymm10,ymm10,8
	vpalignr	ymm6,ymm6,ymm6,12

	lea	rdi,QWORD PTR[32+rdi]
	dec	rcx
	jg	$L$seal_avx2_tail_384_rounds_and_3xhash
	dec	r8
	jge	$L$seal_avx2_tail_384_rounds_and_2xhash
	vpaddd	ymm2,ymm2,YMMWORD PTR[$L$chacha20_consts]
	vpaddd	ymm6,ymm6,YMMWORD PTR[((160+64))+rbp]
	vpaddd	ymm10,ymm10,YMMWORD PTR[((160+96))+rbp]
	vpaddd	ymm14,ymm14,YMMWORD PTR[((160+224))+rbp]
	vpaddd	ymm1,ymm1,YMMWORD PTR[$L$chacha20_consts]
	vpaddd	ymm5,ymm5,YMMWORD PTR[((160+64))+rbp]
	vpaddd	ymm9,ymm9,YMMWORD PTR[((160+96))+rbp]
	vpaddd	ymm13,ymm13,YMMWORD PTR[((160+192))+rbp]
	vpaddd	ymm0,ymm0,YMMWORD PTR[$L$chacha20_consts]
	vpaddd	ymm4,ymm4,YMMWORD PTR[((160+64))+rbp]
	vpaddd	ymm8,ymm8,YMMWORD PTR[((160+96))+rbp]
	vpaddd	ymm12,ymm12,YMMWORD PTR[((160+160))+rbp]
	vperm2i128	ymm3,ymm6,ymm2,002h
	vperm2i128	ymm6,ymm6,ymm2,013h
	vperm2i128	ymm2,ymm14,ymm10,002h
	vperm2i128	ymm10,ymm14,ymm10,013h
	vpxor	ymm3,ymm3,YMMWORD PTR[((0+0))+rsi]
	vpxor	ymm2,ymm2,YMMWORD PTR[((32+0))+rsi]
	vpxor	ymm6,ymm6,YMMWORD PTR[((64+0))+rsi]
	vpxor	ymm10,ymm10,YMMWORD PTR[((96+0))+rsi]
	vmovdqu	YMMWORD PTR[(0+0)+rdi],ymm3
	vmovdqu	YMMWORD PTR[(32+0)+rdi],ymm2
	vmovdqu	YMMWORD PTR[(64+0)+rdi],ymm6
	vmovdqu	YMMWORD PTR[(96+0)+rdi],ymm10
	vperm2i128	ymm3,ymm5,ymm1,002h
	vperm2i128	ymm5,ymm5,ymm1,013h
	vperm2i128	ymm1,ymm13,ymm9,002h
	vperm2i128	ymm9,ymm13,ymm9,013h
	vpxor	ymm3,ymm3,YMMWORD PTR[((0+128))+rsi]
	vpxor	ymm1,ymm1,YMMWORD PTR[((32+128))+rsi]
	vpxor	ymm5,ymm5,YMMWORD PTR[((64+128))+rsi]
	vpxor	ymm9,ymm9,YMMWORD PTR[((96+128))+rsi]
	vmovdqu	YMMWORD PTR[(0+128)+rdi],ymm3
	vmovdqu	YMMWORD PTR[(32+128)+rdi],ymm1
	vmovdqu	YMMWORD PTR[(64+128)+rdi],ymm5
	vmovdqu	YMMWORD PTR[(96+128)+rdi],ymm9
	vperm2i128	ymm3,ymm4,ymm0,013h
	vperm2i128	ymm0,ymm4,ymm0,002h
	vperm2i128	ymm4,ymm12,ymm8,002h
	vperm2i128	ymm12,ymm12,ymm8,013h
	vmovdqa	ymm8,ymm3

	mov	rcx,8*32
	lea	rsi,QWORD PTR[256+rsi]
	sub	rbx,8*32
	jmp	$L$seal_avx2_short_hash_remainder

$L$seal_avx2_tail_512::
	vmovdqa	ymm0,YMMWORD PTR[$L$chacha20_consts]
	vmovdqa	ymm4,YMMWORD PTR[((160+64))+rbp]
	vmovdqa	ymm8,YMMWORD PTR[((160+96))+rbp]
	vmovdqa	ymm1,ymm0
	vmovdqa	ymm5,ymm4
	vmovdqa	ymm9,ymm8
	vmovdqa	ymm2,ymm0
	vmovdqa	ymm6,ymm4
	vmovdqa	ymm10,ymm8
	vmovdqa	ymm3,ymm0
	vmovdqa	ymm7,ymm4
	vmovdqa	ymm11,ymm8
	vmovdqa	ymm12,YMMWORD PTR[$L$avx2_inc]
	vpaddd	ymm15,ymm12,YMMWORD PTR[((160+160))+rbp]
	vpaddd	ymm14,ymm12,ymm15
	vpaddd	ymm13,ymm12,ymm14
	vpaddd	ymm12,ymm12,ymm13
	vmovdqa	YMMWORD PTR[(160+256)+rbp],ymm15
	vmovdqa	YMMWORD PTR[(160+224)+rbp],ymm14
	vmovdqa	YMMWORD PTR[(160+192)+rbp],ymm13
	vmovdqa	YMMWORD PTR[(160+160)+rbp],ymm12

$L$seal_avx2_tail_512_rounds_and_3xhash::
	add	r10,QWORD PTR[((0+0))+rdi]
	adc	r11,QWORD PTR[((8+0))+rdi]
	adc	r12,1
	mov	rdx,QWORD PTR[((0+160+0))+rbp]
	mov	r15,rdx
	mulx	r14,r13,r10
	mulx	rdx,rax,r11
	imul	r15,r12
	add	r14,rax
	adc	r15,rdx
	mov	rdx,QWORD PTR[((8+160+0))+rbp]
	mulx	rax,r10,r10
	add	r14,r10
	mulx	r9,r11,r11
	adc	r15,r11
	adc	r9,0
	imul	rdx,r12
	add	r15,rax
	adc	r9,rdx
	mov	r10,r13
	mov	r11,r14
	mov	r12,r15
	and	r12,3
	mov	r13,r15
	and	r13,-4
	mov	r14,r9
	shrd	r15,r9,2
	shr	r9,2
	add	r15,r13
	adc	r9,r14
	add	r10,r15
	adc	r11,r9
	adc	r12,0

	lea	rdi,QWORD PTR[16+rdi]
$L$seal_avx2_tail_512_rounds_and_2xhash::
	vmovdqa	YMMWORD PTR[(160+128)+rbp],ymm8
	vmovdqa	ymm8,YMMWORD PTR[$L$rol16]
	vpaddd	ymm3,ymm3,ymm7
	vpaddd	ymm2,ymm2,ymm6
	vpaddd	ymm1,ymm1,ymm5
	vpaddd	ymm0,ymm0,ymm4
	vpxor	ymm15,ymm15,ymm3
	vpxor	ymm14,ymm14,ymm2
	vpxor	ymm13,ymm13,ymm1
	vpxor	ymm12,ymm12,ymm0
	vpshufb	ymm15,ymm15,ymm8
	vpshufb	ymm14,ymm14,ymm8
	vpshufb	ymm13,ymm13,ymm8
	vpshufb	ymm12,ymm12,ymm8
	vpaddd	ymm11,ymm11,ymm15
	vpaddd	ymm10,ymm10,ymm14
	vpaddd	ymm9,ymm9,ymm13
	vpaddd	ymm8,ymm12,YMMWORD PTR[((160+128))+rbp]
	vpxor	ymm7,ymm7,ymm11
	vpxor	ymm6,ymm6,ymm10
	add	r10,QWORD PTR[((0+0))+rdi]
	adc	r11,QWORD PTR[((8+0))+rdi]
	adc	r12,1
	vpxor	ymm5,ymm5,ymm9
	vpxor	ymm4,ymm4,ymm8
	vmovdqa	YMMWORD PTR[(160+128)+rbp],ymm8
	vpsrld	ymm8,ymm7,20
	vpslld	ymm7,ymm7,32-20
	vpxor	ymm7,ymm7,ymm8
	vpsrld	ymm8,ymm6,20
	vpslld	ymm6,ymm6,32-20
	vpxor	ymm6,ymm6,ymm8
	vpsrld	ymm8,ymm5,20
	vpslld	ymm5,ymm5,32-20
	vpxor	ymm5,ymm5,ymm8
	vpsrld	ymm8,ymm4,20
	vpslld	ymm4,ymm4,32-20
	vpxor	ymm4,ymm4,ymm8
	vmovdqa	ymm8,YMMWORD PTR[$L$rol8]
	vpaddd	ymm3,ymm3,ymm7
	vpaddd	ymm2,ymm2,ymm6
	vpaddd	ymm1,ymm1,ymm5
	vpaddd	ymm0,ymm0,ymm4
	mov	rdx,QWORD PTR[((0+160+0))+rbp]
	mov	r15,rdx
	mulx	r14,r13,r10
	mulx	rdx,rax,r11
	imul	r15,r12
	add	r14,rax
	adc	r15,rdx
	vpxor	ymm15,ymm15,ymm3
	vpxor	ymm14,ymm14,ymm2
	vpxor	ymm13,ymm13,ymm1
	vpxor	ymm12,ymm12,ymm0
	vpshufb	ymm15,ymm15,ymm8
	vpshufb	ymm14,ymm14,ymm8
	vpshufb	ymm13,ymm13,ymm8
	vpshufb	ymm12,ymm12,ymm8
	vpaddd	ymm11,ymm11,ymm15
	vpaddd	ymm10,ymm10,ymm14
	vpaddd	ymm9,ymm9,ymm13
	vpaddd	ymm8,ymm12,YMMWORD PTR[((160+128))+rbp]
	vpxor	ymm7,ymm7,ymm11
	vpxor	ymm6,ymm6,ymm10
	vpxor	ymm5,ymm5,ymm9
	vpxor	ymm4,ymm4,ymm8
	vmovdqa	YMMWORD PTR[(160+128)+rbp],ymm8
	vpsrld	ymm8,ymm7,25
	vpslld	ymm7,ymm7,32-25
	vpxor	ymm7,ymm7,ymm8
	mov	rdx,QWORD PTR[((8+160+0))+rbp]
	mulx	rax,r10,r10
	add	r14,r10
	mulx	r9,r11,r11
	adc	r15,r11
	adc	r9,0
	imul	rdx,r12
	vpsrld	ymm8,ymm6,25
	vpslld	ymm6,ymm6,32-25
	vpxor	ymm6,ymm6,ymm8
	vpsrld	ymm8,ymm5,25
	vpslld	ymm5,ymm5,32-25
	vpxor	ymm5,ymm5,ymm8
	vpsrld	ymm8,ymm4,25
	vpslld	ymm4,ymm4,32-25
	vpxor	ymm4,ymm4,ymm8
	vmovdqa	ymm8,YMMWORD PTR[((160+128))+rbp]
	vpalignr	ymm7,ymm7,ymm7,4
	vpalignr	ymm11,ymm11,ymm11,8
	vpalignr	ymm15,ymm15,ymm15,12
	vpalignr	ymm6,ymm6,ymm6,4
	vpalignr	ymm10,ymm10,ymm10,8
	vpalignr	ymm14,ymm14,ymm14,12
	vpalignr	ymm5,ymm5,ymm5,4
	vpalignr	ymm9,ymm9,ymm9,8
	vpalignr	ymm13,ymm13,ymm13,12
	vpalignr	ymm4,ymm4,ymm4,4
	add	r15,rax
	adc	r9,rdx
	vpalignr	ymm8,ymm8,ymm8,8
	vpalignr	ymm12,ymm12,ymm12,12
	vmovdqa	YMMWORD PTR[(160+128)+rbp],ymm8
	vmovdqa	ymm8,YMMWORD PTR[$L$rol16]
	vpaddd	ymm3,ymm3,ymm7
	vpaddd	ymm2,ymm2,ymm6
	vpaddd	ymm1,ymm1,ymm5
	vpaddd	ymm0,ymm0,ymm4
	vpxor	ymm15,ymm15,ymm3
	vpxor	ymm14,ymm14,ymm2
	vpxor	ymm13,ymm13,ymm1
	vpxor	ymm12,ymm12,ymm0
	vpshufb	ymm15,ymm15,ymm8
	vpshufb	ymm14,ymm14,ymm8
	vpshufb	ymm13,ymm13,ymm8
	vpshufb	ymm12,ymm12,ymm8
	vpaddd	ymm11,ymm11,ymm15
	vpaddd	ymm10,ymm10,ymm14
	vpaddd	ymm9,ymm9,ymm13
	vpaddd	ymm8,ymm12,YMMWORD PTR[((160+128))+rbp]
	mov	r10,r13
	mov	r11,r14
	mov	r12,r15
	and	r12,3
	mov	r13,r15
	and	r13,-4
	mov	r14,r9
	shrd	r15,r9,2
	shr	r9,2
	add	r15,r13
	adc	r9,r14
	add	r10,r15
	adc	r11,r9
	adc	r12,0
	vpxor	ymm7,ymm7,ymm11
	vpxor	ymm6,ymm6,ymm10
	vpxor	ymm5,ymm5,ymm9
	vpxor	ymm4,ymm4,ymm8
	vmovdqa	YMMWORD PTR[(160+128)+rbp],ymm8
	vpsrld	ymm8,ymm7,20
	vpslld	ymm7,ymm7,32-20
	vpxor	ymm7,ymm7,ymm8
	vpsrld	ymm8,ymm6,20
	vpslld	ymm6,ymm6,32-20
	vpxor	ymm6,ymm6,ymm8
	vpsrld	ymm8,ymm5,20
	vpslld	ymm5,ymm5,32-20
	vpxor	ymm5,ymm5,ymm8
	vpsrld	ymm8,ymm4,20
	vpslld	ymm4,ymm4,32-20
	vpxor	ymm4,ymm4,ymm8
	vmovdqa	ymm8,YMMWORD PTR[$L$rol8]
	vpaddd	ymm3,ymm3,ymm7
	vpaddd	ymm2,ymm2,ymm6
	add	r10,QWORD PTR[((0+16))+rdi]
	adc	r11,QWORD PTR[((8+16))+rdi]
	adc	r12,1
	vpaddd	ymm1,ymm1,ymm5
	vpaddd	ymm0,ymm0,ymm4
	vpxor	ymm15,ymm15,ymm3
	vpxor	ymm14,ymm14,ymm2
	vpxor	ymm13,ymm13,ymm1
	vpxor	ymm12,ymm12,ymm0
	vpshufb	ymm15,ymm15,ymm8
	vpshufb	ymm14,ymm14,ymm8
	vpshufb	ymm13,ymm13,ymm8
	vpshufb	ymm12,ymm12,ymm8
	vpaddd	ymm11,ymm11,ymm15
	vpaddd	ymm10,ymm10,ymm14
	vpaddd	ymm9,ymm9,ymm13
	vpaddd	ymm8,ymm12,YMMWORD PTR[((160+128))+rbp]
	vpxor	ymm7,ymm7,ymm11
	vpxor	ymm6,ymm6,ymm10
	vpxor	ymm5,ymm5,ymm9
	vpxor	ymm4,ymm4,ymm8
	vmovdqa	YMMWORD PTR[(160+128)+rbp],ymm8
	vpsrld	ymm8,ymm7,25
	mov	rdx,QWORD PTR[((0+160+0))+rbp]
	mov	r15,rdx
	mulx	r14,r13,r10
	mulx	rdx,rax,r11
	imul	r15,r12
	add	r14,rax
	adc	r15,rdx
	vpslld	ymm7,ymm7,32-25
	vpxor	ymm7,ymm7,ymm8
	vpsrld	ymm8,ymm6,25
	vpslld	ymm6,ymm6,32-25
	vpxor	ymm6,ymm6,ymm8
	vpsrld	ymm8,ymm5,25
	vpslld	ymm5,ymm5,32-25
	vpxor	ymm5,ymm5,ymm8
	vpsrld	ymm8,ymm4,25
	vpslld	ymm4,ymm4,32-25
	vpxor	ymm4,ymm4,ymm8
	vmovdqa	ymm8,YMMWORD PTR[((160+128))+rbp]
	vpalignr	ymm7,ymm7,ymm7,12
	vpalignr	ymm11,ymm11,ymm11,8
	vpalignr	ymm15,ymm15,ymm15,4
	vpalignr	ymm6,ymm6,ymm6,12
	vpalignr	ymm10,ymm10,ymm10,8
	vpalignr	ymm14,ymm14,ymm14,4
	vpalignr	ymm5,ymm5,ymm5,12
	vpalignr	ymm9,ymm9,ymm9,8
	mov	rdx,QWORD PTR[((8+160+0))+rbp]
	mulx	rax,r10,r10
	add	r14,r10
	mulx	r9,r11,r11
	adc	r15,r11
	adc	r9,0
	imul	rdx,r12
	vpalignr	ymm13,ymm13,ymm13,4
	vpalignr	ymm4,ymm4,ymm4,12
	vpalignr	ymm8,ymm8,ymm8,8
	vpalignr	ymm12,ymm12,ymm12,4
















	add	r15,rax
	adc	r9,rdx




















	mov	r10,r13
	mov	r11,r14
	mov	r12,r15
	and	r12,3
	mov	r13,r15
	and	r13,-4
	mov	r14,r9
	shrd	r15,r9,2
	shr	r9,2
	add	r15,r13
	adc	r9,r14
	add	r10,r15
	adc	r11,r9
	adc	r12,0

	lea	rdi,QWORD PTR[32+rdi]
	dec	rcx
	jg	$L$seal_avx2_tail_512_rounds_and_3xhash
	dec	r8
	jge	$L$seal_avx2_tail_512_rounds_and_2xhash
	vpaddd	ymm3,ymm3,YMMWORD PTR[$L$chacha20_consts]
	vpaddd	ymm7,ymm7,YMMWORD PTR[((160+64))+rbp]
	vpaddd	ymm11,ymm11,YMMWORD PTR[((160+96))+rbp]
	vpaddd	ymm15,ymm15,YMMWORD PTR[((160+256))+rbp]
	vpaddd	ymm2,ymm2,YMMWORD PTR[$L$chacha20_consts]
	vpaddd	ymm6,ymm6,YMMWORD PTR[((160+64))+rbp]
	vpaddd	ymm10,ymm10,YMMWORD PTR[((160+96))+rbp]
	vpaddd	ymm14,ymm14,YMMWORD PTR[((160+224))+rbp]
	vpaddd	ymm1,ymm1,YMMWORD PTR[$L$chacha20_consts]
	vpaddd	ymm5,ymm5,YMMWORD PTR[((160+64))+rbp]
	vpaddd	ymm9,ymm9,YMMWORD PTR[((160+96))+rbp]
	vpaddd	ymm13,ymm13,YMMWORD PTR[((160+192))+rbp]
	vpaddd	ymm0,ymm0,YMMWORD PTR[$L$chacha20_consts]
	vpaddd	ymm4,ymm4,YMMWORD PTR[((160+64))+rbp]
	vpaddd	ymm8,ymm8,YMMWORD PTR[((160+96))+rbp]
	vpaddd	ymm12,ymm12,YMMWORD PTR[((160+160))+rbp]

	vmovdqa	YMMWORD PTR[(160+128)+rbp],ymm0
	vperm2i128	ymm0,ymm7,ymm3,002h
	vperm2i128	ymm7,ymm7,ymm3,013h
	vperm2i128	ymm3,ymm15,ymm11,002h
	vperm2i128	ymm11,ymm15,ymm11,013h
	vpxor	ymm0,ymm0,YMMWORD PTR[((0+0))+rsi]
	vpxor	ymm3,ymm3,YMMWORD PTR[((32+0))+rsi]
	vpxor	ymm7,ymm7,YMMWORD PTR[((64+0))+rsi]
	vpxor	ymm11,ymm11,YMMWORD PTR[((96+0))+rsi]
	vmovdqu	YMMWORD PTR[(0+0)+rdi],ymm0
	vmovdqu	YMMWORD PTR[(32+0)+rdi],ymm3
	vmovdqu	YMMWORD PTR[(64+0)+rdi],ymm7
	vmovdqu	YMMWORD PTR[(96+0)+rdi],ymm11

	vmovdqa	ymm0,YMMWORD PTR[((160+128))+rbp]
	vperm2i128	ymm3,ymm6,ymm2,002h
	vperm2i128	ymm6,ymm6,ymm2,013h
	vperm2i128	ymm2,ymm14,ymm10,002h
	vperm2i128	ymm10,ymm14,ymm10,013h
	vpxor	ymm3,ymm3,YMMWORD PTR[((0+128))+rsi]
	vpxor	ymm2,ymm2,YMMWORD PTR[((32+128))+rsi]
	vpxor	ymm6,ymm6,YMMWORD PTR[((64+128))+rsi]
	vpxor	ymm10,ymm10,YMMWORD PTR[((96+128))+rsi]
	vmovdqu	YMMWORD PTR[(0+128)+rdi],ymm3
	vmovdqu	YMMWORD PTR[(32+128)+rdi],ymm2
	vmovdqu	YMMWORD PTR[(64+128)+rdi],ymm6
	vmovdqu	YMMWORD PTR[(96+128)+rdi],ymm10
	vperm2i128	ymm3,ymm5,ymm1,002h
	vperm2i128	ymm5,ymm5,ymm1,013h
	vperm2i128	ymm1,ymm13,ymm9,002h
	vperm2i128	ymm9,ymm13,ymm9,013h
	vpxor	ymm3,ymm3,YMMWORD PTR[((0+256))+rsi]
	vpxor	ymm1,ymm1,YMMWORD PTR[((32+256))+rsi]
	vpxor	ymm5,ymm5,YMMWORD PTR[((64+256))+rsi]
	vpxor	ymm9,ymm9,YMMWORD PTR[((96+256))+rsi]
	vmovdqu	YMMWORD PTR[(0+256)+rdi],ymm3
	vmovdqu	YMMWORD PTR[(32+256)+rdi],ymm1
	vmovdqu	YMMWORD PTR[(64+256)+rdi],ymm5
	vmovdqu	YMMWORD PTR[(96+256)+rdi],ymm9
	vperm2i128	ymm3,ymm4,ymm0,013h
	vperm2i128	ymm0,ymm4,ymm0,002h
	vperm2i128	ymm4,ymm12,ymm8,002h
	vperm2i128	ymm12,ymm12,ymm8,013h
	vmovdqa	ymm8,ymm3

	mov	rcx,12*32
	lea	rsi,QWORD PTR[384+rsi]
	sub	rbx,12*32
	jmp	$L$seal_avx2_short_hash_remainder

$L$seal_avx2_320::
	vmovdqa	ymm1,ymm0
	vmovdqa	ymm2,ymm0
	vmovdqa	ymm5,ymm4
	vmovdqa	ymm6,ymm4
	vmovdqa	ymm9,ymm8
	vmovdqa	ymm10,ymm8
	vpaddd	ymm13,ymm12,YMMWORD PTR[$L$avx2_inc]
	vpaddd	ymm14,ymm13,YMMWORD PTR[$L$avx2_inc]
	vmovdqa	ymm7,ymm4
	vmovdqa	ymm11,ymm8
	vmovdqa	YMMWORD PTR[(160+160)+rbp],ymm12
	vmovdqa	YMMWORD PTR[(160+192)+rbp],ymm13
	vmovdqa	YMMWORD PTR[(160+224)+rbp],ymm14
	mov	r10,10
$L$seal_avx2_320_rounds::
	vpaddd	ymm0,ymm0,ymm4
	vpxor	ymm12,ymm12,ymm0
	vpshufb	ymm12,ymm12,YMMWORD PTR[$L$rol16]
	vpaddd	ymm8,ymm8,ymm12
	vpxor	ymm4,ymm4,ymm8
	vpsrld	ymm3,ymm4,20
	vpslld	ymm4,ymm4,12
	vpxor	ymm4,ymm4,ymm3
	vpaddd	ymm0,ymm0,ymm4
	vpxor	ymm12,ymm12,ymm0
	vpshufb	ymm12,ymm12,YMMWORD PTR[$L$rol8]
	vpaddd	ymm8,ymm8,ymm12
	vpxor	ymm4,ymm4,ymm8
	vpslld	ymm3,ymm4,7
	vpsrld	ymm4,ymm4,25
	vpxor	ymm4,ymm4,ymm3
	vpalignr	ymm12,ymm12,ymm12,12
	vpalignr	ymm8,ymm8,ymm8,8
	vpalignr	ymm4,ymm4,ymm4,4
	vpaddd	ymm1,ymm1,ymm5
	vpxor	ymm13,ymm13,ymm1
	vpshufb	ymm13,ymm13,YMMWORD PTR[$L$rol16]
	vpaddd	ymm9,ymm9,ymm13
	vpxor	ymm5,ymm5,ymm9
	vpsrld	ymm3,ymm5,20
	vpslld	ymm5,ymm5,12
	vpxor	ymm5,ymm5,ymm3
	vpaddd	ymm1,ymm1,ymm5
	vpxor	ymm13,ymm13,ymm1
	vpshufb	ymm13,ymm13,YMMWORD PTR[$L$rol8]
	vpaddd	ymm9,ymm9,ymm13
	vpxor	ymm5,ymm5,ymm9
	vpslld	ymm3,ymm5,7
	vpsrld	ymm5,ymm5,25
	vpxor	ymm5,ymm5,ymm3
	vpalignr	ymm13,ymm13,ymm13,12
	vpalignr	ymm9,ymm9,ymm9,8
	vpalignr	ymm5,ymm5,ymm5,4
	vpaddd	ymm2,ymm2,ymm6
	vpxor	ymm14,ymm14,ymm2
	vpshufb	ymm14,ymm14,YMMWORD PTR[$L$rol16]
	vpaddd	ymm10,ymm10,ymm14
	vpxor	ymm6,ymm6,ymm10
	vpsrld	ymm3,ymm6,20
	vpslld	ymm6,ymm6,12
	vpxor	ymm6,ymm6,ymm3
	vpaddd	ymm2,ymm2,ymm6
	vpxor	ymm14,ymm14,ymm2
	vpshufb	ymm14,ymm14,YMMWORD PTR[$L$rol8]
	vpaddd	ymm10,ymm10,ymm14
	vpxor	ymm6,ymm6,ymm10
	vpslld	ymm3,ymm6,7
	vpsrld	ymm6,ymm6,25
	vpxor	ymm6,ymm6,ymm3
	vpalignr	ymm14,ymm14,ymm14,12
	vpalignr	ymm10,ymm10,ymm10,8
	vpalignr	ymm6,ymm6,ymm6,4
	vpaddd	ymm0,ymm0,ymm4
	vpxor	ymm12,ymm12,ymm0
	vpshufb	ymm12,ymm12,YMMWORD PTR[$L$rol16]
	vpaddd	ymm8,ymm8,ymm12
	vpxor	ymm4,ymm4,ymm8
	vpsrld	ymm3,ymm4,20
	vpslld	ymm4,ymm4,12
	vpxor	ymm4,ymm4,ymm3
	vpaddd	ymm0,ymm0,ymm4
	vpxor	ymm12,ymm12,ymm0
	vpshufb	ymm12,ymm12,YMMWORD PTR[$L$rol8]
	vpaddd	ymm8,ymm8,ymm12
	vpxor	ymm4,ymm4,ymm8
	vpslld	ymm3,ymm4,7
	vpsrld	ymm4,ymm4,25
	vpxor	ymm4,ymm4,ymm3
	vpalignr	ymm12,ymm12,ymm12,4
	vpalignr	ymm8,ymm8,ymm8,8
	vpalignr	ymm4,ymm4,ymm4,12
	vpaddd	ymm1,ymm1,ymm5
	vpxor	ymm13,ymm13,ymm1
	vpshufb	ymm13,ymm13,YMMWORD PTR[$L$rol16]
	vpaddd	ymm9,ymm9,ymm13
	vpxor	ymm5,ymm5,ymm9
	vpsrld	ymm3,ymm5,20
	vpslld	ymm5,ymm5,12
	vpxor	ymm5,ymm5,ymm3
	vpaddd	ymm1,ymm1,ymm5
	vpxor	ymm13,ymm13,ymm1
	vpshufb	ymm13,ymm13,YMMWORD PTR[$L$rol8]
	vpaddd	ymm9,ymm9,ymm13
	vpxor	ymm5,ymm5,ymm9
	vpslld	ymm3,ymm5,7
	vpsrld	ymm5,ymm5,25
	vpxor	ymm5,ymm5,ymm3
	vpalignr	ymm13,ymm13,ymm13,4
	vpalignr	ymm9,ymm9,ymm9,8
	vpalignr	ymm5,ymm5,ymm5,12
	vpaddd	ymm2,ymm2,ymm6
	vpxor	ymm14,ymm14,ymm2
	vpshufb	ymm14,ymm14,YMMWORD PTR[$L$rol16]
	vpaddd	ymm10,ymm10,ymm14
	vpxor	ymm6,ymm6,ymm10
	vpsrld	ymm3,ymm6,20
	vpslld	ymm6,ymm6,12
	vpxor	ymm6,ymm6,ymm3
	vpaddd	ymm2,ymm2,ymm6
	vpxor	ymm14,ymm14,ymm2
	vpshufb	ymm14,ymm14,YMMWORD PTR[$L$rol8]
	vpaddd	ymm10,ymm10,ymm14
	vpxor	ymm6,ymm6,ymm10
	vpslld	ymm3,ymm6,7
	vpsrld	ymm6,ymm6,25
	vpxor	ymm6,ymm6,ymm3
	vpalignr	ymm14,ymm14,ymm14,4
	vpalignr	ymm10,ymm10,ymm10,8
	vpalignr	ymm6,ymm6,ymm6,12

	dec	r10
	jne	$L$seal_avx2_320_rounds
	vpaddd	ymm0,ymm0,YMMWORD PTR[$L$chacha20_consts]
	vpaddd	ymm1,ymm1,YMMWORD PTR[$L$chacha20_consts]
	vpaddd	ymm2,ymm2,YMMWORD PTR[$L$chacha20_consts]
	vpaddd	ymm4,ymm4,ymm7
	vpaddd	ymm5,ymm5,ymm7
	vpaddd	ymm6,ymm6,ymm7
	vpaddd	ymm8,ymm8,ymm11
	vpaddd	ymm9,ymm9,ymm11
	vpaddd	ymm10,ymm10,ymm11
	vpaddd	ymm12,ymm12,YMMWORD PTR[((160+160))+rbp]
	vpaddd	ymm13,ymm13,YMMWORD PTR[((160+192))+rbp]
	vpaddd	ymm14,ymm14,YMMWORD PTR[((160+224))+rbp]
	vperm2i128	ymm3,ymm4,ymm0,002h

	vpand	ymm3,ymm3,YMMWORD PTR[$L$clamp]
	vmovdqa	YMMWORD PTR[(160+0)+rbp],ymm3

	vperm2i128	ymm0,ymm4,ymm0,013h
	vperm2i128	ymm4,ymm12,ymm8,013h
	vperm2i128	ymm8,ymm5,ymm1,002h
	vperm2i128	ymm12,ymm13,ymm9,002h
	vperm2i128	ymm1,ymm5,ymm1,013h
	vperm2i128	ymm5,ymm13,ymm9,013h
	vperm2i128	ymm9,ymm6,ymm2,002h
	vperm2i128	ymm13,ymm14,ymm10,002h
	vperm2i128	ymm2,ymm6,ymm2,013h
	vperm2i128	ymm6,ymm14,ymm10,013h
	jmp	$L$seal_avx2_short

$L$seal_avx2_192::
	vmovdqa	ymm1,ymm0
	vmovdqa	ymm2,ymm0
	vmovdqa	ymm5,ymm4
	vmovdqa	ymm6,ymm4
	vmovdqa	ymm9,ymm8
	vmovdqa	ymm10,ymm8
	vpaddd	ymm13,ymm12,YMMWORD PTR[$L$avx2_inc]
	vmovdqa	ymm11,ymm12
	vmovdqa	ymm15,ymm13
	mov	r10,10
$L$seal_avx2_192_rounds::
	vpaddd	ymm0,ymm0,ymm4
	vpxor	ymm12,ymm12,ymm0
	vpshufb	ymm12,ymm12,YMMWORD PTR[$L$rol16]
	vpaddd	ymm8,ymm8,ymm12
	vpxor	ymm4,ymm4,ymm8
	vpsrld	ymm3,ymm4,20
	vpslld	ymm4,ymm4,12
	vpxor	ymm4,ymm4,ymm3
	vpaddd	ymm0,ymm0,ymm4
	vpxor	ymm12,ymm12,ymm0
	vpshufb	ymm12,ymm12,YMMWORD PTR[$L$rol8]
	vpaddd	ymm8,ymm8,ymm12
	vpxor	ymm4,ymm4,ymm8
	vpslld	ymm3,ymm4,7
	vpsrld	ymm4,ymm4,25
	vpxor	ymm4,ymm4,ymm3
	vpalignr	ymm12,ymm12,ymm12,12
	vpalignr	ymm8,ymm8,ymm8,8
	vpalignr	ymm4,ymm4,ymm4,4
	vpaddd	ymm1,ymm1,ymm5
	vpxor	ymm13,ymm13,ymm1
	vpshufb	ymm13,ymm13,YMMWORD PTR[$L$rol16]
	vpaddd	ymm9,ymm9,ymm13
	vpxor	ymm5,ymm5,ymm9
	vpsrld	ymm3,ymm5,20
	vpslld	ymm5,ymm5,12
	vpxor	ymm5,ymm5,ymm3
	vpaddd	ymm1,ymm1,ymm5
	vpxor	ymm13,ymm13,ymm1
	vpshufb	ymm13,ymm13,YMMWORD PTR[$L$rol8]
	vpaddd	ymm9,ymm9,ymm13
	vpxor	ymm5,ymm5,ymm9
	vpslld	ymm3,ymm5,7
	vpsrld	ymm5,ymm5,25
	vpxor	ymm5,ymm5,ymm3
	vpalignr	ymm13,ymm13,ymm13,12
	vpalignr	ymm9,ymm9,ymm9,8
	vpalignr	ymm5,ymm5,ymm5,4
	vpaddd	ymm0,ymm0,ymm4
	vpxor	ymm12,ymm12,ymm0
	vpshufb	ymm12,ymm12,YMMWORD PTR[$L$rol16]
	vpaddd	ymm8,ymm8,ymm12
	vpxor	ymm4,ymm4,ymm8
	vpsrld	ymm3,ymm4,20
	vpslld	ymm4,ymm4,12
	vpxor	ymm4,ymm4,ymm3
	vpaddd	ymm0,ymm0,ymm4
	vpxor	ymm12,ymm12,ymm0
	vpshufb	ymm12,ymm12,YMMWORD PTR[$L$rol8]
	vpaddd	ymm8,ymm8,ymm12
	vpxor	ymm4,ymm4,ymm8
	vpslld	ymm3,ymm4,7
	vpsrld	ymm4,ymm4,25
	vpxor	ymm4,ymm4,ymm3
	vpalignr	ymm12,ymm12,ymm12,4
	vpalignr	ymm8,ymm8,ymm8,8
	vpalignr	ymm4,ymm4,ymm4,12
	vpaddd	ymm1,ymm1,ymm5
	vpxor	ymm13,ymm13,ymm1
	vpshufb	ymm13,ymm13,YMMWORD PTR[$L$rol16]
	vpaddd	ymm9,ymm9,ymm13
	vpxor	ymm5,ymm5,ymm9
	vpsrld	ymm3,ymm5,20
	vpslld	ymm5,ymm5,12
	vpxor	ymm5,ymm5,ymm3
	vpaddd	ymm1,ymm1,ymm5
	vpxor	ymm13,ymm13,ymm1
	vpshufb	ymm13,ymm13,YMMWORD PTR[$L$rol8]
	vpaddd	ymm9,ymm9,ymm13
	vpxor	ymm5,ymm5,ymm9
	vpslld	ymm3,ymm5,7
	vpsrld	ymm5,ymm5,25
	vpxor	ymm5,ymm5,ymm3
	vpalignr	ymm13,ymm13,ymm13,4
	vpalignr	ymm9,ymm9,ymm9,8
	vpalignr	ymm5,ymm5,ymm5,12

	dec	r10
	jne	$L$seal_avx2_192_rounds
	vpaddd	ymm0,ymm0,ymm2
	vpaddd	ymm1,ymm1,ymm2
	vpaddd	ymm4,ymm4,ymm6
	vpaddd	ymm5,ymm5,ymm6
	vpaddd	ymm8,ymm8,ymm10
	vpaddd	ymm9,ymm9,ymm10
	vpaddd	ymm12,ymm12,ymm11
	vpaddd	ymm13,ymm13,ymm15
	vperm2i128	ymm3,ymm4,ymm0,002h

	vpand	ymm3,ymm3,YMMWORD PTR[$L$clamp]
	vmovdqa	YMMWORD PTR[(160+0)+rbp],ymm3

	vperm2i128	ymm0,ymm4,ymm0,013h
	vperm2i128	ymm4,ymm12,ymm8,013h
	vperm2i128	ymm8,ymm5,ymm1,002h
	vperm2i128	ymm12,ymm13,ymm9,002h
	vperm2i128	ymm1,ymm5,ymm1,013h
	vperm2i128	ymm5,ymm13,ymm9,013h
$L$seal_avx2_short::
	mov	r8,r8
	call	poly_hash_ad_internal
	xor	rcx,rcx
$L$seal_avx2_short_hash_remainder::
	cmp	rcx,16
	jb	$L$seal_avx2_short_loop
	add	r10,QWORD PTR[((0+0))+rdi]
	adc	r11,QWORD PTR[((8+0))+rdi]
	adc	r12,1
	mov	rax,QWORD PTR[((0+160+0))+rbp]
	mov	r15,rax
	mul	r10
	mov	r13,rax
	mov	r14,rdx
	mov	rax,QWORD PTR[((0+160+0))+rbp]
	mul	r11
	imul	r15,r12
	add	r14,rax
	adc	r15,rdx
	mov	rax,QWORD PTR[((8+160+0))+rbp]
	mov	r9,rax
	mul	r10
	add	r14,rax
	adc	rdx,0
	mov	r10,rdx
	mov	rax,QWORD PTR[((8+160+0))+rbp]
	mul	r11
	add	r15,rax
	adc	rdx,0
	imul	r9,r12
	add	r15,r10
	adc	r9,rdx
	mov	r10,r13
	mov	r11,r14
	mov	r12,r15
	and	r12,3
	mov	r13,r15
	and	r13,-4
	mov	r14,r9
	shrd	r15,r9,2
	shr	r9,2
	add	r15,r13
	adc	r9,r14
	add	r10,r15
	adc	r11,r9
	adc	r12,0

	sub	rcx,16
	add	rdi,16
	jmp	$L$seal_avx2_short_hash_remainder
$L$seal_avx2_short_loop::
	cmp	rbx,32
	jb	$L$seal_avx2_short_tail
	sub	rbx,32

	vpxor	ymm0,ymm0,YMMWORD PTR[rsi]
	vmovdqu	YMMWORD PTR[rdi],ymm0
	lea	rsi,QWORD PTR[32+rsi]

	add	r10,QWORD PTR[((0+0))+rdi]
	adc	r11,QWORD PTR[((8+0))+rdi]
	adc	r12,1
	mov	rax,QWORD PTR[((0+160+0))+rbp]
	mov	r15,rax
	mul	r10
	mov	r13,rax
	mov	r14,rdx
	mov	rax,QWORD PTR[((0+160+0))+rbp]
	mul	r11
	imul	r15,r12
	add	r14,rax
	adc	r15,rdx
	mov	rax,QWORD PTR[((8+160+0))+rbp]
	mov	r9,rax
	mul	r10
	add	r14,rax
	adc	rdx,0
	mov	r10,rdx
	mov	rax,QWORD PTR[((8+160+0))+rbp]
	mul	r11
	add	r15,rax
	adc	rdx,0
	imul	r9,r12
	add	r15,r10
	adc	r9,rdx
	mov	r10,r13
	mov	r11,r14
	mov	r12,r15
	and	r12,3
	mov	r13,r15
	and	r13,-4
	mov	r14,r9
	shrd	r15,r9,2
	shr	r9,2
	add	r15,r13
	adc	r9,r14
	add	r10,r15
	adc	r11,r9
	adc	r12,0
	add	r10,QWORD PTR[((0+16))+rdi]
	adc	r11,QWORD PTR[((8+16))+rdi]
	adc	r12,1
	mov	rax,QWORD PTR[((0+160+0))+rbp]
	mov	r15,rax
	mul	r10
	mov	r13,rax
	mov	r14,rdx
	mov	rax,QWORD PTR[((0+160+0))+rbp]
	mul	r11
	imul	r15,r12
	add	r14,rax
	adc	r15,rdx
	mov	rax,QWORD PTR[((8+160+0))+rbp]
	mov	r9,rax
	mul	r10
	add	r14,rax
	adc	rdx,0
	mov	r10,rdx
	mov	rax,QWORD PTR[((8+160+0))+rbp]
	mul	r11
	add	r15,rax
	adc	rdx,0
	imul	r9,r12
	add	r15,r10
	adc	r9,rdx
	mov	r10,r13
	mov	r11,r14
	mov	r12,r15
	and	r12,3
	mov	r13,r15
	and	r13,-4
	mov	r14,r9
	shrd	r15,r9,2
	shr	r9,2
	add	r15,r13
	adc	r9,r14
	add	r10,r15
	adc	r11,r9
	adc	r12,0

	lea	rdi,QWORD PTR[32+rdi]

	vmovdqa	ymm0,ymm4
	vmovdqa	ymm4,ymm8
	vmovdqa	ymm8,ymm12
	vmovdqa	ymm12,ymm1
	vmovdqa	ymm1,ymm5
	vmovdqa	ymm5,ymm9
	vmovdqa	ymm9,ymm13
	vmovdqa	ymm13,ymm2
	vmovdqa	ymm2,ymm6
	jmp	$L$seal_avx2_short_loop
$L$seal_avx2_short_tail::
	cmp	rbx,16
	jb	$L$seal_avx2_exit
	sub	rbx,16
	vpxor	xmm3,xmm0,XMMWORD PTR[rsi]
	vmovdqu	XMMWORD PTR[rdi],xmm3
	lea	rsi,QWORD PTR[16+rsi]
	add	r10,QWORD PTR[((0+0))+rdi]
	adc	r11,QWORD PTR[((8+0))+rdi]
	adc	r12,1
	mov	rax,QWORD PTR[((0+160+0))+rbp]
	mov	r15,rax
	mul	r10
	mov	r13,rax
	mov	r14,rdx
	mov	rax,QWORD PTR[((0+160+0))+rbp]
	mul	r11
	imul	r15,r12
	add	r14,rax
	adc	r15,rdx
	mov	rax,QWORD PTR[((8+160+0))+rbp]
	mov	r9,rax
	mul	r10
	add	r14,rax
	adc	rdx,0
	mov	r10,rdx
	mov	rax,QWORD PTR[((8+160+0))+rbp]
	mul	r11
	add	r15,rax
	adc	rdx,0
	imul	r9,r12
	add	r15,r10
	adc	r9,rdx
	mov	r10,r13
	mov	r11,r14
	mov	r12,r15
	and	r12,3
	mov	r13,r15
	and	r13,-4
	mov	r14,r9
	shrd	r15,r9,2
	shr	r9,2
	add	r15,r13
	adc	r9,r14
	add	r10,r15
	adc	r11,r9
	adc	r12,0

	lea	rdi,QWORD PTR[16+rdi]
	vextracti128	xmm0,ymm0,1
$L$seal_avx2_exit::
	vzeroupper
	jmp	$L$seal_sse_tail_16

chacha20_poly1305_seal_avx2	ENDP

.text$	ENDS
END
