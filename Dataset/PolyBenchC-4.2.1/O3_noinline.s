	.file	"syrk.c"
# GNU C17 (GCC) version 9.2.0 (x86_64-pc-linux-gnu)
#	compiled by GNU C version 9.2.0, GMP version 6.1.0, MPFR version 3.1.4, MPC version 1.0.3, isl version isl-0.18-GMP

# GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
# options passed:  -I utilities -I ./linear-algebra/blas/syrk
# -imultiarch x86_64-linux-gnu -D LARGE_DATASET
# ./linear-algebra/blas/syrk/syrk.c -mtune=generic -march=x86-64
# -auxbase-strip O3_noinline.s -O3 -fno-inline -fverbose-asm
# options enabled:  -faggressive-loop-optimizations -falign-functions
# -falign-jumps -falign-labels -falign-loops -fassume-phsa
# -fasynchronous-unwind-tables -fauto-inc-dec -fbranch-count-reg
# -fcaller-saves -fcode-hoisting -fcombine-stack-adjustments -fcommon
# -fcompare-elim -fcprop-registers -fcrossjumping -fcse-follow-jumps
# -fdefer-pop -fdelete-null-pointer-checks -fdevirtualize
# -fdevirtualize-speculatively -fdwarf2-cfi-asm -fearly-inlining
# -feliminate-unused-debug-types -fexpensive-optimizations
# -fforward-propagate -ffp-int-builtin-inexact -ffunction-cse -fgcse
# -fgcse-after-reload -fgcse-lm -fgnu-runtime -fgnu-unique
# -fguess-branch-probability -fhoist-adjacent-loads -fident -fif-conversion
# -fif-conversion2 -findirect-inlining -finline-atomics -finline-functions
# -finline-functions-called-once -finline-small-functions -fipa-bit-cp
# -fipa-cp -fipa-cp-clone -fipa-icf -fipa-icf-functions -fipa-icf-variables
# -fipa-profile -fipa-pure-const -fipa-ra -fipa-reference
# -fipa-reference-addressable -fipa-sra -fipa-stack-alignment -fipa-vrp
# -fira-hoist-pressure -fira-share-save-slots -fira-share-spill-slots
# -fisolate-erroneous-paths-dereference -fivopts -fkeep-static-consts
# -fleading-underscore -flifetime-dse -floop-interchange
# -floop-unroll-and-jam -flra-remat -flto-odr-type-merging -fmath-errno
# -fmerge-constants -fmerge-debug-strings -fmove-loop-invariants
# -fomit-frame-pointer -foptimize-sibling-calls -foptimize-strlen
# -fpartial-inlining -fpeel-loops -fpeephole -fpeephole2 -fplt
# -fpredictive-commoning -fprefetch-loop-arrays -free -freg-struct-return
# -freorder-blocks -freorder-blocks-and-partition -freorder-functions
# -frerun-cse-after-loop -fsched-critical-path-heuristic
# -fsched-dep-count-heuristic -fsched-group-heuristic -fsched-interblock
# -fsched-last-insn-heuristic -fsched-rank-heuristic -fsched-spec
# -fsched-spec-insn-heuristic -fsched-stalled-insns-dep -fschedule-fusion
# -fschedule-insns2 -fsemantic-interposition -fshow-column -fshrink-wrap
# -fshrink-wrap-separate -fsigned-zeros -fsplit-ivs-in-unroller
# -fsplit-loops -fsplit-paths -fsplit-wide-types -fssa-backprop
# -fssa-phiopt -fstdarg-opt -fstore-merging -fstrict-aliasing
# -fstrict-volatile-bitfields -fsync-libcalls -fthread-jumps
# -ftoplevel-reorder -ftrapping-math -ftree-bit-ccp -ftree-builtin-call-dce
# -ftree-ccp -ftree-ch -ftree-coalesce-vars -ftree-copy-prop -ftree-cselim
# -ftree-dce -ftree-dominator-opts -ftree-dse -ftree-forwprop -ftree-fre
# -ftree-loop-distribute-patterns -ftree-loop-distribution
# -ftree-loop-if-convert -ftree-loop-im -ftree-loop-ivcanon
# -ftree-loop-optimize -ftree-loop-vectorize -ftree-parallelize-loops=
# -ftree-partial-pre -ftree-phiprop -ftree-pre -ftree-pta -ftree-reassoc
# -ftree-scev-cprop -ftree-sink -ftree-slp-vectorize -ftree-slsr -ftree-sra
# -ftree-switch-conversion -ftree-tail-merge -ftree-ter -ftree-vrp
# -funit-at-a-time -funswitch-loops -funwind-tables -fverbose-asm
# -fversion-loops-for-strides -fzero-initialized-in-bss
# -m128bit-long-double -m64 -m80387 -malign-stringops
# -mavx256-split-unaligned-load -mavx256-split-unaligned-store
# -mfancy-math-387 -mfp-ret-in-387 -mfxsr -mglibc -mieee-fp
# -mlong-double-80 -mmmx -mno-sse4 -mpush-args -mred-zone -msse -msse2
# -mstv -mtls-direct-seg-refs -mvzeroupper

	.text
	.p2align 4
	.type	kernel_syrk.constprop.0, @function
kernel_syrk.constprop.0:
.LFB12:
	.cfi_startproc
	pushq	%r15	#
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	leaq	8(%rsi), %rax	#, ivtmp.83
	movapd	%xmm1, %xmm4	# beta, vect_cst__188
	movapd	%xmm0, %xmm2	# tmp231, alpha
	pushq	%r14	#
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	movapd	%xmm1, %xmm3	# tmp232, beta
	movq	%rdi, %r11	# tmp233, ivtmp.80
# ./linear-algebra/blas/syrk/syrk.c:83:   for (i = 0; i < _PB_N; i++) {
	xorl	%r14d, %r14d	# i
# ./linear-algebra/blas/syrk/syrk.c:68: void kernel_syrk(int n, int m,
	pushq	%r13	#
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	unpcklpd	%xmm4, %xmm4	# vect_cst__188
	movq	%rsi, %r13	# tmp234, A
	pushq	%r12	#
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	pushq	%rbp	#
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	leaq	8(%rdi), %rbp	#, ivtmp.81
	pushq	%rbx	#
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	movq	%rax, -16(%rsp)	# ivtmp.83, %sfp
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	movq	$1, -32(%rsp)	#, %sfp
	movq	$0, -24(%rsp)	#, %sfp
	.p2align 4,,10
	.p2align 3
.L2:
	movq	-32(%rsp), %rax	# %sfp, ivtmp.88
	movl	%eax, %r12d	# ivtmp.88, _227
	testl	%r14d, %r14d	# i
	je	.L17	#,
	movl	%eax, %edx	# ivtmp.88, bnd.27
# ./linear-algebra/blas/syrk/syrk.c:85:       C[i][j] *= beta;
	movq	%r11, %rax	# ivtmp.80, ivtmp.70
	shrl	%edx	#
	salq	$4, %rdx	#, tmp225
	addq	%r11, %rdx	# ivtmp.80, _206
	.p2align 4,,10
	.p2align 3
.L4:
	movupd	(%rax), %xmm0	# MEM[base: _201, offset: 0B], vect__9.33
	addq	$16, %rax	#, ivtmp.70
	mulpd	%xmm4, %xmm0	# vect_cst__188, vect__9.33
	movups	%xmm0, -16(%rax)	# vect__9.33, MEM[base: _201, offset: 0B]
	cmpq	%rdx, %rax	# _206, ivtmp.70
	jne	.L4	#,
	movl	%r12d, %eax	# _227, tmp.29
	andl	$-2, %eax	#, tmp.29
	testb	$1, %r12b	#, _227
	je	.L3	#,
.L16:
	cltq
	leaq	(%r11,%rax,8), %rax	#, _35
	movsd	(%rax), %xmm0	# MEM[(double[1800] *)_35], tmp179
	mulsd	%xmm3, %xmm0	# beta, tmp179
	movsd	%xmm0, (%rax)	# tmp179, MEM[(double[1800] *)_35]
.L3:
	movq	-32(%rsp), %rdx	# %sfp, tmp183
	movl	%r12d, %eax	# _227, niters_vector_mult_vf.16
	subq	-24(%rsp), %rdx	# %sfp, tmp183
	movl	%r12d, %edi	# _227, bnd.15
	andl	$-2, %eax	#,
	imulq	$12000, %rdx, %rdx	#, tmp183, _22
	shrl	%edi	#
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	xorl	%r8d, %r8d	# ivtmp.55
	imulq	$12000, %rax, %r10	#, _123, tmp187
	movq	-16(%rsp), %r9	# %sfp, ivtmp.83
	movl	%eax, -36(%rsp)	# niters_vector_mult_vf.16, %sfp
	salq	$4, %rdi	#, tmp186
	addq	%r11, %rdi	# ivtmp.80, _87
	leaq	-12000(%rdx), %rsi	#, tmp226
	leaq	-8(%r9), %rcx	#, ivtmp.65
	movq	%rsi, -48(%rsp)	# tmp226, %sfp
	addq	%r13, %r10	# A, _125
	leaq	(%r11,%rax,8), %rsi	#, _190
	.p2align 4,,10
	.p2align 3
.L6:
	leaq	-8(%r9), %rbx	#, tmp206
	movslq	%r8d, %rdx	# ivtmp.55,
	leaq	0(%r13,%r8,8), %rax	#, ivtmp.41
	cmpq	%rbx, %rbp	# tmp206, ivtmp.81
	setbe	%r15b	#, tmp208
	cmpq	%r9, %r11	# ivtmp.60, ivtmp.80
	setnb	%bl	#, tmp210
	orl	%r15d, %ebx	# tmp208, tmp211
	cmpl	$1, %r14d	#, i
	seta	%r15b	#, tmp213
	testb	%r15b, %bl	# tmp213, tmp211
	je	.L18	#,
	movq	-48(%rsp), %rbx	# %sfp, tmp226
	addq	%r9, %rbx	# ivtmp.60, tmp216
	cmpq	%rbx, %r11	# tmp216, ivtmp.80
	setnb	%r15b	#, tmp218
	cmpq	%rax, %rbp	# ivtmp.41, ivtmp.81
	setbe	%bl	#, tmp220
	orb	%bl, %r15b	# tmp220, tmp218
	je	.L18	#,
	movsd	(%rcx), %xmm1	# MEM[base: _131, offset: 0B], _47
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	movq	%r11, %rbx	# ivtmp.80, ivtmp.46
	mulsd	%xmm2, %xmm1	# alpha, _47
	unpcklpd	%xmm1, %xmm1	# vect__22.21
	.p2align 4,,10
	.p2align 3
.L10:
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	movsd	(%rax), %xmm0	# MEM[base: _80, offset: 0B], MEM[base: _80, offset: 0B]
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	movupd	(%rbx), %xmm5	# MEM[base: _68, offset: 0B], tmp302
	addq	$16, %rbx	#, ivtmp.46
	addq	$24000, %rax	#, ivtmp.41
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	movhpd	-12000(%rax), %xmm0	# MEM[base: _80, offset: 12000B], tmp199
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	mulpd	%xmm1, %xmm0	# vect__22.21, vect__27.22
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	addpd	%xmm5, %xmm0	# tmp302, vect__28.23
	movups	%xmm0, -16(%rbx)	# vect__28.23, MEM[base: _68, offset: 0B]
	cmpq	%rdi, %rbx	# _87, ivtmp.46
	jne	.L10	#,
	cmpl	%r12d, -36(%rsp)	# _227, %sfp
	je	.L9	#,
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	movsd	(%rcx), %xmm0	# MEM[base: _131, offset: 0B], tmp189
	mulsd	%xmm2, %xmm0	# alpha, tmp189
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	mulsd	(%r10,%rdx,8), %xmm0	# *_125, tmp191
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	addsd	(%rsi), %xmm0	# MEM[(double[1800] *)_190], tmp192
	movsd	%xmm0, (%rsi)	# tmp192, MEM[(double[1800] *)_190]
.L9:
	addq	$1, %r8	#, ivtmp.55
	addq	$8, %r9	#, ivtmp.60
	addq	$8, %rcx	#, ivtmp.65
# ./linear-algebra/blas/syrk/syrk.c:86:     for (k = 0; k < _PB_M; k++) {
	cmpq	$1500, %r8	#, ivtmp.55
	jne	.L6	#,
# ./linear-algebra/blas/syrk/syrk.c:83:   for (i = 0; i < _PB_N; i++) {
	addl	$1, %r14d	#, i
	addq	$1, -24(%rsp)	#, %sfp
	addq	$14400, %r11	#, ivtmp.80
	addq	$14408, %rbp	#, ivtmp.81
	addq	$12000, -16(%rsp)	#, %sfp
	addq	$1, -32(%rsp)	#, %sfp
# ./linear-algebra/blas/syrk/syrk.c:83:   for (i = 0; i < _PB_N; i++) {
	cmpl	$1800, %r14d	#, i
	jne	.L2	#,
# ./linear-algebra/blas/syrk/syrk.c:93: }
	popq	%rbx	#
	.cfi_remember_state
	.cfi_def_cfa_offset 48
	popq	%rbp	#
	.cfi_def_cfa_offset 40
	popq	%r12	#
	.cfi_def_cfa_offset 32
	popq	%r13	#
	.cfi_def_cfa_offset 24
	popq	%r14	#
	.cfi_def_cfa_offset 16
	popq	%r15	#
	.cfi_def_cfa_offset 8
	ret	
	.p2align 4,,10
	.p2align 3
.L18:
	.cfi_restore_state
# ./linear-algebra/blas/syrk/syrk.c:85:       C[i][j] *= beta;
	movq	%r11, %rdx	# ivtmp.80, ivtmp.40
	.p2align 4,,10
	.p2align 3
.L8:
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	movsd	(%rcx), %xmm0	# MEM[base: _28, offset: 0B], tmp194
	addq	$8, %rdx	#, ivtmp.40
	addq	$12000, %rax	#, ivtmp.41
	mulsd	%xmm2, %xmm0	# alpha, tmp194
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	mulsd	-12000(%rax), %xmm0	# MEM[base: _41, offset: 0B], tmp195
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	addsd	-8(%rdx), %xmm0	# MEM[base: _49, offset: 0B], tmp196
	movsd	%xmm0, -8(%rdx)	# tmp196, MEM[base: _49, offset: 0B]
# ./linear-algebra/blas/syrk/syrk.c:87:       for (j = 0; j <= i; j++)
	cmpq	%rbp, %rdx	# ivtmp.81, ivtmp.40
	jne	.L8	#,
	jmp	.L9	#
.L17:
# ./linear-algebra/blas/syrk/syrk.c:84:     for (j = 0; j <= i; j++)
	xorl	%eax, %eax	# tmp.29
	jmp	.L16	#
	.cfi_endproc
.LFE12:
	.size	kernel_syrk.constprop.0, .-kernel_syrk.constprop.0
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"==BEGIN DUMP_ARRAYS==\n"
.LC1:
	.string	"C"
.LC2:
	.string	"begin dump: %s"
.LC3:
	.string	"%0.2lf "
.LC4:
	.string	"\nend   dump: %s\n"
.LC5:
	.string	"==END   DUMP_ARRAYS==\n"
	.text
	.p2align 4
	.type	print_array.constprop.0, @function
print_array.constprop.0:
.LFB11:
	.cfi_startproc
	pushq	%r12	#
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
# ./linear-algebra/blas/syrk/syrk.c:53:   POLYBENCH_DUMP_START;
	movq	stderr(%rip), %rcx	# stderr,
	movl	$22, %edx	#,
# ./linear-algebra/blas/syrk/syrk.c:48: void print_array(int n,
	movq	%rdi, %r12	# tmp115, C
	pushq	%rbp	#
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
# ./linear-algebra/blas/syrk/syrk.c:53:   POLYBENCH_DUMP_START;
	movl	$1, %esi	#,
	movl	$.LC0, %edi	#,
# ./linear-algebra/blas/syrk/syrk.c:54:   POLYBENCH_DUMP_BEGIN("C");
	xorl	%ebp, %ebp	# ivtmp.110
# ./linear-algebra/blas/syrk/syrk.c:48: void print_array(int n,
	pushq	%rbx	#
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
# ./linear-algebra/blas/syrk/syrk.c:53:   POLYBENCH_DUMP_START;
	call	fwrite	#
# ./linear-algebra/blas/syrk/syrk.c:54:   POLYBENCH_DUMP_BEGIN("C");
	movq	stderr(%rip), %rdi	# stderr,
	movl	$.LC1, %edx	#,
	xorl	%eax, %eax	#
	movl	$.LC2, %esi	#,
	call	fprintf	#
	.p2align 4,,10
	.p2align 3
.L30:
# ./linear-algebra/blas/syrk/syrk.c:58: 	fprintf (POLYBENCH_DUMP_TARGET, DATA_PRINTF_MODIFIER, C[i][j]);
	xorl	%ebx, %ebx	# ivtmp.96
	jmp	.L35	#
	.p2align 4,,10
	.p2align 3
.L31:
# ./linear-algebra/blas/syrk/syrk.c:58: 	fprintf (POLYBENCH_DUMP_TARGET, DATA_PRINTF_MODIFIER, C[i][j]);
	movsd	(%r12,%rbx,8), %xmm0	# MEM[base: _12, index: ivtmp.96_20, step: 8, offset: 0B], MEM[base: _12, index: ivtmp.96_20, step: 8, offset: 0B]
	movl	$.LC3, %esi	#,
.L37:
	movl	$1, %eax	#,
	addq	$1, %rbx	#, ivtmp.96
	call	fprintf	#
# ./linear-algebra/blas/syrk/syrk.c:56:     for (j = 0; j < n; j++) {
	cmpq	$1800, %rbx	#, ivtmp.96
	je	.L38	#,
.L35:
	leal	0(%rbp,%rbx), %eax	#, tmp99
	movq	stderr(%rip), %rdi	# stderr, pretmp_40
	imull	$-858993459, %eax, %eax	#, tmp99, tmp111
	rorl	$2, %eax	#, tmp112
# ./linear-algebra/blas/syrk/syrk.c:57: 	if ((i * n + j) % 20 == 0) fprintf (POLYBENCH_DUMP_TARGET, "\n");
	cmpl	$214748364, %eax	#, tmp112
	ja	.L31	#,
# ./linear-algebra/blas/syrk/syrk.c:57: 	if ((i * n + j) % 20 == 0) fprintf (POLYBENCH_DUMP_TARGET, "\n");
	movq	%rdi, %rsi	# pretmp_40,
	movl	$10, %edi	#,
	call	fputc	#
# ./linear-algebra/blas/syrk/syrk.c:58: 	fprintf (POLYBENCH_DUMP_TARGET, DATA_PRINTF_MODIFIER, C[i][j]);
	movsd	(%r12,%rbx,8), %xmm0	# MEM[base: _12, index: ivtmp.96_20, step: 8, offset: 0B], MEM[base: _12, index: ivtmp.96_20, step: 8, offset: 0B]
	movl	$.LC3, %esi	#,
	movq	stderr(%rip), %rdi	# stderr,
	jmp	.L37	#
	.p2align 4,,10
	.p2align 3
.L38:
	addl	$1800, %ebp	#, ivtmp.110
	addq	$14400, %r12	#, ivtmp.109
# ./linear-algebra/blas/syrk/syrk.c:55:   for (i = 0; i < n; i++)
	cmpl	$3240000, %ebp	#, ivtmp.110
	jne	.L30	#,
# ./linear-algebra/blas/syrk/syrk.c:60:   POLYBENCH_DUMP_END("C");
	movq	stderr(%rip), %rdi	# stderr,
	movl	$.LC1, %edx	#,
	movl	$.LC4, %esi	#,
	xorl	%eax, %eax	#
	call	fprintf	#
# ./linear-algebra/blas/syrk/syrk.c:62: }
	popq	%rbx	#
	.cfi_def_cfa_offset 24
# ./linear-algebra/blas/syrk/syrk.c:61:   POLYBENCH_DUMP_FINISH;
	movl	$22, %edx	#,
# ./linear-algebra/blas/syrk/syrk.c:62: }
	popq	%rbp	#
	.cfi_def_cfa_offset 16
# ./linear-algebra/blas/syrk/syrk.c:61:   POLYBENCH_DUMP_FINISH;
	movq	stderr(%rip), %rcx	# stderr,
	movl	$1, %esi	#,
	movl	$.LC5, %edi	#,
# ./linear-algebra/blas/syrk/syrk.c:62: }
	popq	%r12	#
	.cfi_def_cfa_offset 8
# ./linear-algebra/blas/syrk/syrk.c:61:   POLYBENCH_DUMP_FINISH;
	jmp	fwrite	#
	.cfi_endproc
.LFE11:
	.size	print_array.constprop.0, .-print_array.constprop.0
	.p2align 4
	.type	init_array.constprop.0, @function
init_array.constprop.0:
.LFB10:
	.cfi_startproc
# ./linear-algebra/blas/syrk/syrk.c:34:   *alpha = 1.5;
	movq	.LC7(%rip), %rax	#, tmp248
	movdqa	.LC11(%rip), %xmm2	#, tmp239
	pxor	%xmm4, %xmm4	# tmp139
	movdqa	%xmm4, %xmm7	# tmp139, tmp143
	movdqa	.LC9(%rip), %xmm5	#, tmp237
	movdqa	.LC10(%rip), %xmm11	#, tmp238
	movq	%rax, (%rdi)	# tmp248, *alpha_1(D)
	pcmpgtd	%xmm2, %xmm7	# tmp239, tmp143
# ./linear-algebra/blas/syrk/syrk.c:36:   for (i = 0; i < n; i++)
	xorl	%edi, %edi	# i
# ./linear-algebra/blas/syrk/syrk.c:35:   *beta = 1.2;
	movq	.LC8(%rip), %rax	#, tmp249
	movapd	.LC12(%rip), %xmm8	#, tmp240
	movdqa	.LC6(%rip), %xmm6	#, vect_vec_iv_.113
	movq	%rax, (%rsi)	# tmp249, *beta_2(D)
	leaq	12000(%rcx), %rsi	#, ivtmp.166
	.p2align 4,,10
	.p2align 3
.L40:
	movd	%edi, %xmm3	# i, i
# ./linear-algebra/blas/syrk/syrk.c:26: void init_array(int n, int m,
	movq	%rcx, %rax	# ivtmp.165, ivtmp.154
	pshufd	$0, %xmm3, %xmm9	# i, vect_cst__99
	movdqa	%xmm6, %xmm3	# vect_vec_iv_.113, vect_vec_iv_.124
	movdqa	%xmm9, %xmm10	# vect_cst__99, tmp236
	psrlq	$32, %xmm10	#, tmp236
	.p2align 4,,10
	.p2align 3
.L41:
	movdqa	%xmm3, %xmm1	# vect_vec_iv_.124, vect_vec_iv_.124
	movdqa	%xmm4, %xmm13	# tmp139, tmp140
	movdqa	%xmm7, %xmm12	# tmp143, tmp145
	addq	$32, %rax	#, ivtmp.154
# ./linear-algebra/blas/syrk/syrk.c:38:       A[i][j] = (DATA_TYPE) ((i*j+1)%n) / n;
	movdqa	%xmm1, %xmm0	# vect_vec_iv_.124, tmp129
	psrlq	$32, %xmm1	#, tmp131
	movdqa	%xmm7, %xmm14	# tmp143, tmp158
	pmuludq	%xmm9, %xmm0	# vect_cst__99, tmp129
	pmuludq	%xmm10, %xmm1	# tmp236, tmp130
	paddd	%xmm5, %xmm3	# tmp237, vect_vec_iv_.124
	pshufd	$8, %xmm1, %xmm1	#, tmp130, tmp128
	pshufd	$8, %xmm0, %xmm0	#, tmp129, tmp127
	punpckldq	%xmm1, %xmm0	# tmp128, vect__5.125
# ./linear-algebra/blas/syrk/syrk.c:38:       A[i][j] = (DATA_TYPE) ((i*j+1)%n) / n;
	paddd	%xmm11, %xmm0	# tmp238, vect__6.126
	movdqa	%xmm0, %xmm1	# vect__6.126, tmp136
	punpckldq	%xmm0, %xmm1	# vect__6.126, tmp136
	pcmpgtd	%xmm1, %xmm13	# tmp136, tmp140
	pmuludq	%xmm1, %xmm12	# tmp136, tmp145
	pmuludq	%xmm2, %xmm1	# tmp239, tmp146
	pmuludq	%xmm2, %xmm13	# tmp239, tmp144
	paddq	%xmm12, %xmm13	# tmp145, tmp144
	movdqa	%xmm0, %xmm12	# vect__6.126, tmp149
	psllq	$32, %xmm13	#, tmp144
	punpckhdq	%xmm0, %xmm12	# vect__6.126, tmp149
	paddq	%xmm13, %xmm1	# tmp144, tmp134
	pmuludq	%xmm12, %xmm14	# tmp149, tmp158
	movdqa	%xmm4, %xmm13	# tmp139, tmp153
	pcmpgtd	%xmm12, %xmm13	# tmp149, tmp153
	pmuludq	%xmm2, %xmm12	# tmp239, tmp159
	pmuludq	%xmm2, %xmm13	# tmp239, tmp157
	paddq	%xmm14, %xmm13	# tmp158, tmp157
	psllq	$32, %xmm13	#, tmp157
	paddq	%xmm13, %xmm12	# tmp157, tmp147
	shufps	$221, %xmm12, %xmm1	#, tmp147, vect_patt_91.127
	paddd	%xmm0, %xmm1	# vect__6.126, vect_patt_92.128
	psrad	$10, %xmm1	#, vect_patt_92.128
	movdqa	%xmm1, %xmm12	# vect_patt_92.128, vect_patt_93.129
	pslld	$3, %xmm1	#, tmp166
	psubd	%xmm12, %xmm1	# vect_patt_93.129, tmp167
	pslld	$5, %xmm1	#, tmp168
	paddd	%xmm12, %xmm1	# vect_patt_93.129, vect_patt_94.130
	pslld	$3, %xmm1	#, tmp170
	psubd	%xmm1, %xmm0	# tmp170, vect_patt_95.131
# ./linear-algebra/blas/syrk/syrk.c:38:       A[i][j] = (DATA_TYPE) ((i*j+1)%n) / n;
	cvtdq2pd	%xmm0, %xmm1	# vect_patt_95.131, vect__8.132
# ./linear-algebra/blas/syrk/syrk.c:38:       A[i][j] = (DATA_TYPE) ((i*j+1)%n) / n;
	divpd	%xmm8, %xmm1	# tmp240, vect__14.133
# ./linear-algebra/blas/syrk/syrk.c:38:       A[i][j] = (DATA_TYPE) ((i*j+1)%n) / n;
	pshufd	$238, %xmm0, %xmm0	#, vect_patt_95.131, tmp175
	cvtdq2pd	%xmm0, %xmm0	# tmp175, vect__8.132
# ./linear-algebra/blas/syrk/syrk.c:38:       A[i][j] = (DATA_TYPE) ((i*j+1)%n) / n;
	divpd	%xmm8, %xmm0	# tmp240, vect__14.133
# ./linear-algebra/blas/syrk/syrk.c:38:       A[i][j] = (DATA_TYPE) ((i*j+1)%n) / n;
	movups	%xmm1, -32(%rax)	# vect__14.133, MEM[base: _19, offset: 0B]
	movups	%xmm0, -16(%rax)	# vect__14.133, MEM[base: _19, offset: 16B]
	cmpq	%rsi, %rax	# ivtmp.166, ivtmp.154
	jne	.L41	#,
# ./linear-algebra/blas/syrk/syrk.c:36:   for (i = 0; i < n; i++)
	addl	$1, %edi	#, i
	addq	$12000, %rcx	#, ivtmp.165
	leaq	12000(%rax), %rsi	#, ivtmp.166
# ./linear-algebra/blas/syrk/syrk.c:36:   for (i = 0; i < n; i++)
	cmpl	$1800, %edi	#, i
	jne	.L40	#,
	movdqa	.LC14(%rip), %xmm2	#, tmp242
	pxor	%xmm4, %xmm4	# tmp193
	movq	%rdx, %rsi	# C, ivtmp.149
# ./linear-algebra/blas/syrk/syrk.c:39:   for (i = 0; i < n; i++)
	xorl	%ecx, %ecx	# i
	movdqa	%xmm4, %xmm7	# tmp193, tmp197
	leaq	14400(%rdx), %rdx	#, ivtmp.150
	movdqa	.LC13(%rip), %xmm11	#, tmp241
	movapd	.LC15(%rip), %xmm8	#, tmp243
	pcmpgtd	%xmm2, %xmm7	# tmp242, tmp197
	.p2align 4,,10
	.p2align 3
.L42:
	movd	%ecx, %xmm3	# i, i
# ./linear-algebra/blas/syrk/syrk.c:36:   for (i = 0; i < n; i++)
	movq	%rsi, %rax	# ivtmp.149, ivtmp.138
	pshufd	$0, %xmm3, %xmm9	# i, vect_cst__69
	movdqa	%xmm6, %xmm3	# vect_vec_iv_.113, vect_vec_iv_.113
	movdqa	%xmm9, %xmm10	# vect_cst__69, tmp234
	psrlq	$32, %xmm10	#, tmp234
	.p2align 4,,10
	.p2align 3
.L43:
	movdqa	%xmm3, %xmm1	# vect_vec_iv_.113, vect_vec_iv_.113
	movdqa	%xmm4, %xmm12	# tmp193, tmp194
	movdqa	%xmm7, %xmm13	# tmp197, tmp199
	addq	$32, %rax	#, ivtmp.138
# ./linear-algebra/blas/syrk/syrk.c:41:       C[i][j] = (DATA_TYPE) ((i*j+2)%m) / m;
	movdqa	%xmm1, %xmm0	# vect_vec_iv_.113, tmp183
	psrlq	$32, %xmm1	#, tmp185
	movdqa	%xmm7, %xmm14	# tmp197, tmp212
	pmuludq	%xmm9, %xmm0	# vect_cst__69, tmp183
	pmuludq	%xmm10, %xmm1	# tmp234, tmp184
	paddd	%xmm5, %xmm3	# tmp237, vect_vec_iv_.113
	pshufd	$8, %xmm1, %xmm1	#, tmp184, tmp182
	pshufd	$8, %xmm0, %xmm0	#, tmp183, tmp181
	punpckldq	%xmm1, %xmm0	# tmp182, vect__19.114
# ./linear-algebra/blas/syrk/syrk.c:41:       C[i][j] = (DATA_TYPE) ((i*j+2)%m) / m;
	paddd	%xmm11, %xmm0	# tmp241, vect__20.115
	movdqa	%xmm0, %xmm1	# vect__20.115, tmp190
	punpckldq	%xmm0, %xmm1	# vect__20.115, tmp190
	pcmpgtd	%xmm1, %xmm12	# tmp190, tmp194
	pmuludq	%xmm1, %xmm13	# tmp190, tmp199
	pmuludq	%xmm2, %xmm1	# tmp242, tmp200
	pmuludq	%xmm2, %xmm12	# tmp242, tmp198
	paddq	%xmm13, %xmm12	# tmp199, tmp198
	movdqa	%xmm4, %xmm13	# tmp193, tmp207
	psllq	$32, %xmm12	#, tmp198
	paddq	%xmm12, %xmm1	# tmp198, tmp188
	movdqa	%xmm0, %xmm12	# vect__20.115, tmp203
	punpckhdq	%xmm0, %xmm12	# vect__20.115, tmp203
	pcmpgtd	%xmm12, %xmm13	# tmp203, tmp207
	pmuludq	%xmm12, %xmm14	# tmp203, tmp212
	pmuludq	%xmm2, %xmm12	# tmp242, tmp213
	pmuludq	%xmm2, %xmm13	# tmp242, tmp211
	paddq	%xmm14, %xmm13	# tmp212, tmp211
	psllq	$32, %xmm13	#, tmp211
	paddq	%xmm13, %xmm12	# tmp211, tmp201
	shufps	$221, %xmm12, %xmm1	#, tmp201, vect_patt_31.116
	psrad	$5, %xmm1	#, vect_patt_18.117
	movdqa	%xmm1, %xmm12	# vect_patt_18.117, tmp219
	pslld	$1, %xmm12	#, tmp219
	paddd	%xmm1, %xmm12	# vect_patt_18.117, tmp220
	pslld	$4, %xmm12	#, tmp221
	psubd	%xmm1, %xmm12	# vect_patt_18.117, tmp222
	pslld	$3, %xmm12	#, tmp223
	psubd	%xmm1, %xmm12	# vect_patt_18.117, tmp223
	movdqa	%xmm12, %xmm1	# tmp223, vect_patt_17.118
	pslld	$2, %xmm1	#, tmp225
	psubd	%xmm1, %xmm0	# tmp225, vect_patt_4.119
# ./linear-algebra/blas/syrk/syrk.c:41:       C[i][j] = (DATA_TYPE) ((i*j+2)%m) / m;
	cvtdq2pd	%xmm0, %xmm1	# vect_patt_4.119, vect__22.120
# ./linear-algebra/blas/syrk/syrk.c:41:       C[i][j] = (DATA_TYPE) ((i*j+2)%m) / m;
	divpd	%xmm8, %xmm1	# tmp243, vect__28.121
# ./linear-algebra/blas/syrk/syrk.c:41:       C[i][j] = (DATA_TYPE) ((i*j+2)%m) / m;
	pshufd	$238, %xmm0, %xmm0	#, vect_patt_4.119, tmp230
	cvtdq2pd	%xmm0, %xmm0	# tmp230, vect__22.120
# ./linear-algebra/blas/syrk/syrk.c:41:       C[i][j] = (DATA_TYPE) ((i*j+2)%m) / m;
	divpd	%xmm8, %xmm0	# tmp243, vect__28.121
# ./linear-algebra/blas/syrk/syrk.c:41:       C[i][j] = (DATA_TYPE) ((i*j+2)%m) / m;
	movups	%xmm1, -32(%rax)	# vect__28.121, MEM[base: _61, offset: 0B]
	movups	%xmm0, -16(%rax)	# vect__28.121, MEM[base: _61, offset: 16B]
	cmpq	%rdx, %rax	# ivtmp.150, ivtmp.138
	jne	.L43	#,
# ./linear-algebra/blas/syrk/syrk.c:39:   for (i = 0; i < n; i++)
	addl	$1, %ecx	#, i
	addq	$14400, %rsi	#, ivtmp.149
	leaq	14400(%rax), %rdx	#, ivtmp.150
# ./linear-algebra/blas/syrk/syrk.c:39:   for (i = 0; i < n; i++)
	cmpl	$1800, %ecx	#, i
	jne	.L42	#,
# ./linear-algebra/blas/syrk/syrk.c:42: }
	ret	
	.cfi_endproc
.LFE10:
	.size	init_array.constprop.0, .-init_array.constprop.0
	.section	.text.startup,"ax",@progbits
	.p2align 4
	.globl	main
	.type	main, @function
main:
.LFB9:
	.cfi_startproc
	pushq	%r13	#
	.cfi_def_cfa_offset 16
	.cfi_offset 13, -16
	movq	%rsi, %r13	# tmp98, argv
# ./linear-algebra/blas/syrk/syrk.c:105:   POLYBENCH_2D_ARRAY_DECL(C,DATA_TYPE,N,N,n,n);
	movl	$8, %esi	#,
# ./linear-algebra/blas/syrk/syrk.c:97: {
	pushq	%r12	#
	.cfi_def_cfa_offset 24
	.cfi_offset 12, -24
	pushq	%rbp	#
	.cfi_def_cfa_offset 32
	.cfi_offset 6, -32
	pushq	%rbx	#
	.cfi_def_cfa_offset 40
	.cfi_offset 3, -40
	movl	%edi, %ebx	# tmp97, argc
# ./linear-algebra/blas/syrk/syrk.c:105:   POLYBENCH_2D_ARRAY_DECL(C,DATA_TYPE,N,N,n,n);
	movl	$3240000, %edi	#,
# ./linear-algebra/blas/syrk/syrk.c:97: {
	subq	$24, %rsp	#,
	.cfi_def_cfa_offset 64
# ./linear-algebra/blas/syrk/syrk.c:105:   POLYBENCH_2D_ARRAY_DECL(C,DATA_TYPE,N,N,n,n);
	call	polybench_alloc_data	#
# ./linear-algebra/blas/syrk/syrk.c:106:   POLYBENCH_2D_ARRAY_DECL(A,DATA_TYPE,N,M,n,m);
	movl	$8, %esi	#,
	movl	$2700000, %edi	#,
# ./linear-algebra/blas/syrk/syrk.c:105:   POLYBENCH_2D_ARRAY_DECL(C,DATA_TYPE,N,N,n,n);
	movq	%rax, %rbp	# tmp99, C
# ./linear-algebra/blas/syrk/syrk.c:106:   POLYBENCH_2D_ARRAY_DECL(A,DATA_TYPE,N,M,n,m);
	call	polybench_alloc_data	#
# ./linear-algebra/blas/syrk/syrk.c:109:   init_array (n, m, &alpha, &beta, POLYBENCH_ARRAY(C), POLYBENCH_ARRAY(A));
	leaq	8(%rsp), %rsi	#, tmp101
	movq	%rsp, %rdi	#,
	movq	%rbp, %rdx	# C,
	movq	%rax, %rcx	# A,
# ./linear-algebra/blas/syrk/syrk.c:106:   POLYBENCH_2D_ARRAY_DECL(A,DATA_TYPE,N,M,n,m);
	movq	%rax, %r12	# tmp100, A
# ./linear-algebra/blas/syrk/syrk.c:109:   init_array (n, m, &alpha, &beta, POLYBENCH_ARRAY(C), POLYBENCH_ARRAY(A));
	call	init_array.constprop.0	#
# ./linear-algebra/blas/syrk/syrk.c:115:   kernel_syrk (n, m, alpha, beta, POLYBENCH_ARRAY(C), POLYBENCH_ARRAY(A));
	movsd	(%rsp), %xmm0	# alpha,
	movq	%r12, %rsi	# A,
	movq	%rbp, %rdi	# C,
	movsd	8(%rsp), %xmm1	# beta,
	call	kernel_syrk.constprop.0	#
# ./linear-algebra/blas/syrk/syrk.c:123:   polybench_prevent_dce(print_array(n, POLYBENCH_ARRAY(C)));
	cmpl	$42, %ebx	#, argc
	jle	.L49	#,
# ./linear-algebra/blas/syrk/syrk.c:123:   polybench_prevent_dce(print_array(n, POLYBENCH_ARRAY(C)));
	movq	0(%r13), %rax	# *argv_13(D), *argv_13(D)
	cmpb	$0, (%rax)	#, MEM[(const unsigned char * {ref-all})_3]
	je	.L51	#,
.L49:
# ./linear-algebra/blas/syrk/syrk.c:126:   POLYBENCH_FREE_ARRAY(C);
	movq	%rbp, %rdi	# C,
	call	free	#
# ./linear-algebra/blas/syrk/syrk.c:127:   POLYBENCH_FREE_ARRAY(A);
	movq	%r12, %rdi	# A,
	call	free	#
# ./linear-algebra/blas/syrk/syrk.c:130: }
	addq	$24, %rsp	#,
	.cfi_remember_state
	.cfi_def_cfa_offset 40
	xorl	%eax, %eax	#
	popq	%rbx	#
	.cfi_def_cfa_offset 32
	popq	%rbp	#
	.cfi_def_cfa_offset 24
	popq	%r12	#
	.cfi_def_cfa_offset 16
	popq	%r13	#
	.cfi_def_cfa_offset 8
	ret	
.L51:
	.cfi_restore_state
# ./linear-algebra/blas/syrk/syrk.c:123:   polybench_prevent_dce(print_array(n, POLYBENCH_ARRAY(C)));
	movq	%rbp, %rdi	# C,
	call	print_array.constprop.0	#
	jmp	.L49	#
	.cfi_endproc
.LFE9:
	.size	main, .-main
	.section	.rodata.cst16,"aM",@progbits,16
	.align 16
.LC6:
	.long	0
	.long	1
	.long	2
	.long	3
	.section	.rodata.cst8,"aM",@progbits,8
	.align 8
.LC7:
	.long	0
	.long	1073217536
	.align 8
.LC8:
	.long	858993459
	.long	1072902963
	.section	.rodata.cst16
	.align 16
.LC9:
	.long	4
	.long	4
	.long	4
	.long	4
	.align 16
.LC10:
	.long	1
	.long	1
	.long	1
	.long	1
	.align 16
.LC11:
	.long	-1851608123
	.long	-1851608123
	.long	-1851608123
	.long	-1851608123
	.align 16
.LC12:
	.long	0
	.long	1083973632
	.long	0
	.long	1083973632
	.align 16
.LC13:
	.long	2
	.long	2
	.long	2
	.long	2
	.align 16
.LC14:
	.long	91625969
	.long	91625969
	.long	91625969
	.long	91625969
	.align 16
.LC15:
	.long	0
	.long	1083666432
	.long	0
	.long	1083666432
	.ident	"GCC: (GNU) 9.2.0"
	.section	.note.GNU-stack,"",@progbits
