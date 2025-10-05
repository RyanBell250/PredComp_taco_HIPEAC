	.file	"jacobi-1d.c"
	.text
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC4:
	.string	"==BEGIN DUMP_ARRAYS==\n"
.LC5:
	.string	"A"
.LC6:
	.string	"begin dump: %s"
.LC7:
	.string	"%0.2lf "
.LC8:
	.string	"\nend   dump: %s\n"
.LC9:
	.string	"==END   DUMP_ARRAYS==\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB25:
	.cfi_startproc
	pushq	%r13
	.cfi_def_cfa_offset 16
	.cfi_offset 13, -16
	pushq	%r12
	.cfi_def_cfa_offset 24
	.cfi_offset 12, -24
	pushq	%rbp
	.cfi_def_cfa_offset 32
	.cfi_offset 6, -32
	pushq	%rbx
	.cfi_def_cfa_offset 40
	.cfi_offset 3, -40
	subq	$8, %rsp
	.cfi_def_cfa_offset 48
	movl	%edi, %r12d
	movq	%rsi, %r13
	movl	$8, %esi
	movl	$2000, %edi
	call	polybench_alloc_data
	movq	%rax, %rbx
	movl	$8, %esi
	movl	$2000, %edi
	call	polybench_alloc_data
	movq	%rax, %rbp
	movl	$0, %eax
	movsd	.LC1(%rip), %xmm2
.L2:
	pxor	%xmm0, %xmm0
	cvtsi2sdl	%eax, %xmm0
	movsd	.LC0(%rip), %xmm1
	addsd	%xmm0, %xmm1
	divsd	%xmm2, %xmm1
	movsd	%xmm1, (%rbx,%rax,8)
	addsd	.LC2(%rip), %xmm0
	divsd	%xmm2, %xmm0
	movsd	%xmm0, 0(%rbp,%rax,8)
	addq	$1, %rax
	cmpq	$2000, %rax
	jne	.L2
	movl	$500, %edx
	jmp	.L3
.L5:
	movsd	0(%rbp,%rax), %xmm0
	addsd	8(%rbp,%rax), %xmm0
	addsd	16(%rbp,%rax), %xmm0
	mulsd	.LC3(%rip), %xmm0
	movsd	%xmm0, 8(%rbx,%rax)
	addq	$8, %rax
	cmpq	$15984, %rax
	jne	.L5
	subl	$1, %edx
	je	.L6
.L3:
	movl	$0, %eax
.L4:
	movsd	(%rbx,%rax), %xmm0
	addsd	8(%rbx,%rax), %xmm0
	addsd	16(%rbx,%rax), %xmm0
	mulsd	.LC3(%rip), %xmm0
	movsd	%xmm0, 8(%rbp,%rax)
	addq	$8, %rax
	cmpq	$15984, %rax
	jne	.L4
	movl	$0, %eax
	jmp	.L5
.L6:
	cmpl	$42, %r12d
	jle	.L7
	movq	0(%r13), %rax
	cmpb	$0, (%rax)
	je	.L15
.L7:
	movq	%rbx, %rdi
	call	free
	movq	%rbp, %rdi
	call	free
	movl	$0, %eax
	addq	$8, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 40
	popq	%rbx
	.cfi_def_cfa_offset 32
	popq	%rbp
	.cfi_def_cfa_offset 24
	popq	%r12
	.cfi_def_cfa_offset 16
	popq	%r13
	.cfi_def_cfa_offset 8
	ret
.L15:
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
	movl	$0, %r12d
	jmp	.L9
.L8:
	movsd	(%rbx,%r12,8), %xmm0
	movl	$.LC7, %esi
	movq	stderr(%rip), %rdi
	movl	$1, %eax
	call	fprintf
	addq	$1, %r12
	cmpq	$2000, %r12
	je	.L16
.L9:
	movslq	%r12d, %rax
	imulq	$1717986919, %rax, %rax
	sarq	$35, %rax
	movl	%r12d, %edx
	sarl	$31, %edx
	subl	%edx, %eax
	leal	(%rax,%rax,4), %eax
	sall	$2, %eax
	cmpl	%r12d, %eax
	jne	.L8
	movq	stderr(%rip), %rsi
	movl	$10, %edi
	call	fputc
	jmp	.L8
.L16:
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
	jmp	.L7
	.cfi_endproc
.LFE25:
	.size	main, .-main
	.section	.rodata.cst8,"aM",@progbits,8
	.align 8
.LC0:
	.long	0
	.long	1073741824
	.align 8
.LC1:
	.long	0
	.long	1084178432
	.align 8
.LC2:
	.long	0
	.long	1074266112
	.align 8
.LC3:
	.long	1513202878
	.long	1070945607
	.ident	"GCC: (GNU) 9.2.0"
	.section	.note.GNU-stack,"",@progbits
