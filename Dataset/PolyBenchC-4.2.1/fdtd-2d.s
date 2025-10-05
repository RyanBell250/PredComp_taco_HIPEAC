	.file	"fdtd-2d.c"
	.text
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC4:
	.string	"==BEGIN DUMP_ARRAYS==\n"
.LC5:
	.string	"ex"
.LC6:
	.string	"begin dump: %s"
.LC7:
	.string	"%0.2lf "
.LC8:
	.string	"\nend   dump: %s\n"
.LC9:
	.string	"==END   DUMP_ARRAYS==\n"
.LC10:
	.string	"ey"
.LC11:
	.string	"hz"
	.text
	.globl	main
	.type	main, @function
main:
.LFB25:
	.cfi_startproc
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	subq	$88, %rsp
	.cfi_def_cfa_offset 144
	movl	%edi, 52(%rsp)
	movq	%rsi, 72(%rsp)
	movl	$8, %esi
	movl	$1200000, %edi
	call	polybench_alloc_data
	movq	%rax, 24(%rsp)
	movl	$8, %esi
	movl	$1200000, %edi
	call	polybench_alloc_data
	movq	%rax, 8(%rsp)
	movl	$8, %esi
	movl	$1200000, %edi
	call	polybench_alloc_data
	movq	%rax, 32(%rsp)
	movl	$8, %esi
	movl	$500, %edi
	call	polybench_alloc_data
	movq	%rax, 16(%rsp)
	movl	$0, %eax
.L2:
	pxor	%xmm0, %xmm0
	cvtsi2sdl	%eax, %xmm0
	movq	16(%rsp), %rdx
	movsd	%xmm0, (%rdx,%rax,8)
	addq	$1, %rax
	cmpq	$500, %rax
	jne	.L2
	movq	24(%rsp), %rsi
	movq	%rsi, %r12
	movq	8(%rsp), %rdi
	movq	%rdi, %rbp
	movq	32(%rsp), %r8
	movq	%r8, %rbx
	movl	$0, %ecx
	movsd	.LC0(%rip), %xmm2
	jmp	.L5
.L44:
	addl	$1, %ecx
	addq	$9600, %rsi
	addq	$9600, %rdi
	addq	$9600, %r8
	cmpl	$1000, %ecx
	je	.L43
.L5:
	movq	%rsi, %r10
	movq	%rdi, %r9
	movq	%r8, %rdx
	movl	$1, %eax
	pxor	%xmm1, %xmm1
	cvtsi2sdl	%ecx, %xmm1
.L4:
	pxor	%xmm0, %xmm0
	cvtsi2sdl	%eax, %xmm0
	mulsd	%xmm1, %xmm0
	divsd	%xmm2, %xmm0
	movsd	%xmm0, -8(%r10,%rax,8)
	leal	1(%rax), %r11d
	pxor	%xmm0, %xmm0
	cvtsi2sdl	%r11d, %xmm0
	mulsd	%xmm1, %xmm0
	divsd	.LC1(%rip), %xmm0
	movsd	%xmm0, -8(%r9,%rax,8)
	leal	2(%rax), %r11d
	pxor	%xmm0, %xmm0
	cvtsi2sdl	%r11d, %xmm0
	mulsd	%xmm1, %xmm0
	divsd	%xmm2, %xmm0
	movsd	%xmm0, -8(%rdx,%rax,8)
	addq	$1, %rax
	cmpq	$1201, %rax
	jne	.L4
	jmp	.L44
.L43:
	movq	16(%rsp), %rax
	movq	%rax, %rsi
	leaq	4000(%rax), %r13
	leaq	9600(%rbp), %r14
	leaq	9600000(%rbp), %r15
	leaq	9600000(%r12), %rax
	movq	%rax, 64(%rsp)
	leaq	9590400(%rbx), %r11
	jmp	.L6
.L45:
	addq	$9600, %rcx
	cmpq	%r15, %rcx
	je	.L10
.L8:
	movq	%rcx, %r8
	movq	%rdx, %rdi
	addq	$9600, %rdx
	movq	%rdx, %r9
	movl	$0, %eax
.L9:
	movsd	(%r9,%rax), %xmm0
	subsd	(%rdi,%rax), %xmm0
	mulsd	.LC2(%rip), %xmm0
	movsd	(%r8,%rax), %xmm1
	subsd	%xmm0, %xmm1
	movsd	%xmm1, (%r8,%rax)
	addq	$8, %rax
	cmpq	$9600, %rax
	jne	.L9
	jmp	.L45
.L47:
	addq	$9600, %rdx
	addq	$9600, %rcx
	cmpq	64(%rsp), %rdx
	je	.L46
.L12:
	movq	%rdx, %r8
	movq	%rcx, %rdi
	movl	$8, %eax
.L11:
	movsd	(%rdi,%rax), %xmm0
	subsd	-8(%rdi,%rax), %xmm0
	mulsd	.LC2(%rip), %xmm0
	movsd	(%r8,%rax), %xmm1
	subsd	%xmm0, %xmm1
	movsd	%xmm1, (%r8,%rax)
	addq	$8, %rax
	cmpq	$9600, %rax
	jne	.L11
	jmp	.L47
.L46:
	movq	%rbp, %rcx
	movq	%r12, %rdi
	movq	%rbx, %rdx
	jmp	.L13
.L10:
	movq	%rbx, %rcx
	movq	%r12, %rdx
	jmp	.L12
.L48:
	movq	56(%rsp), %rdx
	addq	$9600, %rdx
	addq	$9600, %rdi
	cmpq	%rdx, %r11
	je	.L15
.L13:
	movq	%rdx, %r10
	movq	%rdi, %r9
	movq	%rcx, %r8
	addq	$9600, %rcx
	movq	%rcx, 40(%rsp)
	movl	$0, %eax
	movq	%rdx, 56(%rsp)
.L14:
	movsd	8(%r9,%rax), %xmm0
	subsd	(%r9,%rax), %xmm0
	movq	40(%rsp), %rdx
	addsd	(%rdx,%rax), %xmm0
	subsd	(%r8,%rax), %xmm0
	mulsd	.LC3(%rip), %xmm0
	movsd	(%r10,%rax), %xmm1
	subsd	%xmm0, %xmm1
	movsd	%xmm1, (%r10,%rax)
	addq	$8, %rax
	cmpq	$9592, %rax
	jne	.L14
	jmp	.L48
.L15:
	addq	$8, %rsi
	cmpq	%r13, %rsi
	je	.L16
.L6:
	movq	%rbp, %rax
.L7:
	movsd	(%rsi), %xmm0
	movsd	%xmm0, (%rax)
	addq	$8, %rax
	cmpq	%r14, %rax
	jne	.L7
	movq	8(%rsp), %rax
	leaq	9600(%rax), %rcx
	movq	%rbx, %rdx
	jmp	.L8
.L16:
	cmpl	$42, 52(%rsp)
	jle	.L17
	movq	72(%rsp), %rax
	movq	(%rax), %rax
	cmpb	$0, (%rax)
	je	.L49
.L17:
	movq	24(%rsp), %rdi
	call	free
	movq	8(%rsp), %rdi
	call	free
	movq	32(%rsp), %rdi
	call	free
	movq	16(%rsp), %rdi
	call	free
	movl	$0, %eax
	addq	$88, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%rbp
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	ret
.L49:
	.cfi_restore_state
	movq	stderr(%rip), %rcx
	movl	$22, %edx
	movl	$1, %esi
	movl	$.LC4, %edi
	call	fwrite
	movl	$.LC5, %edx
	movl	$.LC6, %esi
	movq	stderr(%rip), %rdi
	movl	$0, %eax
	call	fprintf
	movl	$0, %r14d
	jmp	.L18
.L19:
	movsd	(%r15,%r13,8), %xmm0
	movl	$.LC7, %esi
	movq	stderr(%rip), %rdi
	movl	$1, %eax
	call	fprintf
	addq	$1, %r13
	cmpq	$1200, %r13
	je	.L50
.L20:
	leal	(%r14,%r13), %edx
	movslq	%edx, %rax
	imulq	$1717986919, %rax, %rax
	sarq	$35, %rax
	movl	%edx, %ecx
	sarl	$31, %ecx
	subl	%ecx, %eax
	leal	(%rax,%rax,4), %eax
	sall	$2, %eax
	cmpl	%eax, %edx
	jne	.L19
	movq	stderr(%rip), %rsi
	movl	$10, %edi
	call	fputc
	jmp	.L19
.L50:
	addq	$9600, %r12
	addl	$1000, %r14d
	cmpl	$1000000, %r14d
	je	.L21
.L18:
	movq	%r12, %r15
	movl	$0, %r13d
	jmp	.L20
.L21:
	movl	$.LC5, %edx
	movl	$.LC8, %esi
	movq	stderr(%rip), %rdi
	movl	$0, %eax
	call	fprintf
	movq	stderr(%rip), %rcx
	movl	$22, %edx
	movl	$1, %esi
	movl	$.LC9, %edi
	call	fwrite
	movl	$.LC10, %edx
	movl	$.LC6, %esi
	movq	stderr(%rip), %rdi
	movl	$0, %eax
	call	fprintf
	movl	$0, %r13d
	jmp	.L22
.L52:
	movq	stderr(%rip), %rsi
	movl	$10, %edi
	call	fputc
.L23:
	movsd	(%r14,%r12,8), %xmm0
	movl	$.LC7, %esi
	movq	stderr(%rip), %rdi
	movl	$1, %eax
	call	fprintf
	addq	$1, %r12
	cmpq	$1200, %r12
	je	.L51
.L24:
	leal	0(%r13,%r12), %edx
	movslq	%edx, %rax
	imulq	$1717986919, %rax, %rax
	sarq	$35, %rax
	movl	%edx, %ecx
	sarl	$31, %ecx
	subl	%ecx, %eax
	leal	(%rax,%rax,4), %eax
	sall	$2, %eax
	cmpl	%eax, %edx
	jne	.L23
	jmp	.L52
.L51:
	addq	$9600, %rbp
	addl	$1000, %r13d
	cmpl	$1000000, %r13d
	je	.L25
.L22:
	movq	%rbp, %r14
	movl	$0, %r12d
	jmp	.L24
.L25:
	movl	$.LC10, %edx
	movl	$.LC8, %esi
	movq	stderr(%rip), %rdi
	movl	$0, %eax
	call	fprintf
	movl	$.LC11, %edx
	movl	$.LC6, %esi
	movq	stderr(%rip), %rdi
	movl	$0, %eax
	call	fprintf
	movl	$0, %r12d
	jmp	.L26
.L54:
	movq	stderr(%rip), %rsi
	movl	$10, %edi
	call	fputc
.L27:
	movsd	0(%r13,%rbp,8), %xmm0
	movl	$.LC7, %esi
	movq	stderr(%rip), %rdi
	movl	$1, %eax
	call	fprintf
	addq	$1, %rbp
	cmpq	$1200, %rbp
	je	.L53
.L28:
	leal	(%r12,%rbp), %edx
	movslq	%edx, %rax
	imulq	$1717986919, %rax, %rax
	sarq	$35, %rax
	movl	%edx, %ecx
	sarl	$31, %ecx
	subl	%ecx, %eax
	leal	(%rax,%rax,4), %eax
	sall	$2, %eax
	cmpl	%eax, %edx
	jne	.L27
	jmp	.L54
.L53:
	addq	$9600, %rbx
	addl	$1000, %r12d
	cmpl	$1000000, %r12d
	je	.L29
.L26:
	movq	%rbx, %r13
	movl	$0, %ebp
	jmp	.L28
.L29:
	movl	$.LC11, %edx
	movl	$.LC8, %esi
	movq	stderr(%rip), %rdi
	movl	$0, %eax
	call	fprintf
	jmp	.L17
	.cfi_endproc
.LFE25:
	.size	main, .-main
	.section	.rodata.cst8,"aM",@progbits,8
	.align 8
.LC0:
	.long	0
	.long	1083129856
	.align 8
.LC1:
	.long	0
	.long	1083359232
	.align 8
.LC2:
	.long	0
	.long	1071644672
	.align 8
.LC3:
	.long	1717986918
	.long	1072064102
	.ident	"GCC: (GNU) 9.2.0"
	.section	.note.GNU-stack,"",@progbits
