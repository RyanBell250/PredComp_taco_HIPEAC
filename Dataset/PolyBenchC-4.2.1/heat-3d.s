	.file	"heat-3d.c"
	.text
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC3:
	.string	"==BEGIN DUMP_ARRAYS==\n"
.LC4:
	.string	"A"
.LC5:
	.string	"begin dump: %s"
.LC6:
	.string	"%0.2lf "
.LC7:
	.string	"\nend   dump: %s\n"
.LC8:
	.string	"==END   DUMP_ARRAYS==\n"
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
	subq	$24, %rsp
	.cfi_def_cfa_offset 80
	movl	%edi, %r14d
	movq	%rsi, 8(%rsp)
	movl	$8, %esi
	movl	$1728000, %edi
	call	polybench_alloc_data
	movq	%rax, %r15
	movl	$8, %esi
	movl	$1728000, %edi
	call	polybench_alloc_data
	movq	%rax, %r9
	movq	%r15, (%rsp)
	movq	%r15, %r11
	movq	%rax, %r10
	movl	$0, %edx
	jmp	.L2
.L31:
	addl	$1, %esi
	addq	$960, %rcx
	cmpq	$115200, %rcx
	je	.L4
.L6:
	movq	%rcx, %r8
	movl	%esi, %edi
	leal	-120(%rsi), %r12d
.L3:
	pxor	%xmm0, %xmm0
	cvtsi2sdl	%edi, %xmm0
	mulsd	.LC0(%rip), %xmm0
	divsd	.LC1(%rip), %xmm0
	movsd	%xmm0, 0(%rbp,%r8)
	movsd	%xmm0, (%rbx,%r8)
	subl	$1, %edi
	addq	$8, %r8
	cmpl	%r12d, %edi
	jne	.L3
	jmp	.L31
.L4:
	addl	$1, %edx
	addq	$115200, %r10
	addq	$115200, %r11
	cmpl	$120, %edx
	je	.L24
.L2:
	movq	%r10, %rbp
	movq	%r11, %rbx
	leal	120(%rdx), %esi
	movl	$0, %ecx
	jmp	.L6
.L32:
	addq	$960, %rsi
	cmpq	$114248, %rsi
	je	.L8
.L11:
	movq	%rsi, %rdx
	leaq	944(%rsi), %r13
.L7:
	movsd	(%rdi,%rdx), %xmm4
	movapd	%xmm4, %xmm5
	addsd	%xmm4, %xmm5
	movsd	(%r12,%rdx), %xmm1
	subsd	%xmm5, %xmm1
	addsd	0(%rbp,%rdx), %xmm1
	mulsd	%xmm3, %xmm1
	movsd	960(%rdi,%rdx), %xmm0
	subsd	%xmm5, %xmm0
	addsd	-960(%rdi,%rdx), %xmm0
	mulsd	%xmm3, %xmm0
	addsd	%xmm0, %xmm1
	movsd	8(%rdi,%rdx), %xmm0
	subsd	%xmm5, %xmm0
	addsd	-8(%rdi,%rdx), %xmm0
	mulsd	%xmm3, %xmm0
	addsd	%xmm1, %xmm0
	addsd	%xmm4, %xmm0
	movsd	%xmm0, (%r11,%rdx)
	addq	$8, %rdx
	cmpq	%r13, %rdx
	jne	.L7
	jmp	.L32
.L8:
	addq	$115200, %rcx
	addq	$115200, %r8
	cmpq	%r10, %rcx
	je	.L33
.L9:
	movq	%rcx, %r12
	leaq	-115200(%rcx), %rdi
	leaq	-230400(%rcx), %rbp
	movq	%r8, %r11
	movl	$968, %esi
	jmp	.L11
.L33:
	leaq	230400(%rax), %rcx
	leaq	115200(%r15), %r8
	jmp	.L10
.L34:
	addq	$960, %rsi
	cmpq	$114248, %rsi
	je	.L13
.L15:
	movq	%rsi, %rdx
	leaq	944(%rsi), %r13
.L12:
	movsd	(%rdi,%rdx), %xmm4
	movapd	%xmm4, %xmm5
	addsd	%xmm4, %xmm5
	movsd	(%r12,%rdx), %xmm1
	subsd	%xmm5, %xmm1
	addsd	0(%rbp,%rdx), %xmm1
	mulsd	%xmm2, %xmm1
	movsd	960(%rdi,%rdx), %xmm0
	subsd	%xmm5, %xmm0
	addsd	-960(%rdi,%rdx), %xmm0
	mulsd	%xmm2, %xmm0
	addsd	%xmm0, %xmm1
	movsd	8(%rdi,%rdx), %xmm0
	subsd	%xmm5, %xmm0
	addsd	-8(%rdi,%rdx), %xmm0
	mulsd	%xmm2, %xmm0
	addsd	%xmm1, %xmm0
	addsd	%xmm4, %xmm0
	movsd	%xmm0, (%r11,%rdx)
	addq	$8, %rdx
	cmpq	%rdx, %r13
	jne	.L12
	jmp	.L34
.L13:
	addq	$115200, %rcx
	addq	$115200, %r8
	cmpq	%r9, %rcx
	je	.L14
.L10:
	movq	%rcx, %r12
	leaq	-115200(%rcx), %rdi
	leaq	-230400(%rcx), %rbp
	movq	%r8, %r11
	movl	$968, %esi
	jmp	.L15
.L14:
	subl	$1, %ebx
	je	.L35
.L5:
	leaq	230400(%r15), %rcx
	leaq	115200(%rax), %r8
	jmp	.L9
.L24:
	movl	$500, %ebx
	movq	(%rsp), %rdi
	leaq	13824000(%rdi), %r10
	movsd	.LC2(%rip), %xmm3
	addq	$13824000, %r9
	movapd	%xmm3, %xmm2
	jmp	.L5
.L35:
	cmpl	$42, %r14d
	jle	.L17
	movq	8(%rsp), %rax
	movq	(%rax), %rax
	cmpb	$0, (%rax)
	je	.L36
.L17:
	movq	%r15, %rdi
	call	free
	movl	$0, %eax
	addq	$24, %rsp
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
.L36:
	.cfi_restore_state
	movq	stderr(%rip), %rcx
	movl	$22, %edx
	movl	$1, %esi
	movl	$.LC3, %edi
	call	fwrite
	movl	$.LC4, %edx
	movl	$.LC5, %esi
	movq	stderr(%rip), %rdi
	movl	$0, %eax
	call	fprintf
	movq	%r15, 8(%rsp)
	movq	(%rsp), %r15
	jmp	.L18
.L38:
	movq	stderr(%rip), %rsi
	movl	$10, %edi
	call	fputc
.L19:
	movsd	(%r14), %xmm0
	movl	$.LC6, %esi
	movq	stderr(%rip), %rdi
	movl	$1, %eax
	call	fprintf
	addl	$1, %ebp
	addq	$8, %r14
	cmpl	%ebp, %r12d
	je	.L37
.L20:
	movslq	%ebp, %rax
	imulq	$1717986919, %rax, %rax
	sarq	$35, %rax
	movl	%ebp, %edx
	sarl	$31, %edx
	subl	%edx, %eax
	leal	(%rax,%rax,4), %eax
	sall	$2, %eax
	cmpl	%eax, %ebp
	jne	.L19
	jmp	.L38
.L37:
	addl	$120, %r12d
	addq	$960, %r13
	cmpl	(%rsp), %r12d
	je	.L21
.L23:
	leal	-120(%r12), %ebp
	movq	%r13, %r14
	jmp	.L20
.L21:
	addl	$14400, %ebx
	addq	$115200, %r15
	cmpl	$1728000, %ebx
	je	.L22
.L18:
	leal	120(%rbx), %r12d
	movq	%r15, %r13
	leal	14520(%rbx), %eax
	movl	%eax, (%rsp)
	jmp	.L23
.L22:
	movq	8(%rsp), %r15
	movl	$.LC4, %edx
	movl	$.LC7, %esi
	movq	stderr(%rip), %rdi
	movl	$0, %eax
	call	fprintf
	movq	stderr(%rip), %rcx
	movl	$22, %edx
	movl	$1, %esi
	movl	$.LC8, %edi
	call	fwrite
	jmp	.L17
	.cfi_endproc
.LFE25:
	.size	main, .-main
	.section	.rodata.cst8,"aM",@progbits,8
	.align 8
.LC0:
	.long	0
	.long	1076101120
	.align 8
.LC1:
	.long	0
	.long	1079902208
	.align 8
.LC2:
	.long	0
	.long	1069547520
	.ident	"GCC: (GNU) 9.2.0"
	.section	.note.GNU-stack,"",@progbits
