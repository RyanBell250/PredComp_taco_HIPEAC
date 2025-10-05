	.file	"syrk.c"
# GNU C17 (GCC) version 9.2.0 (x86_64-pc-linux-gnu)
#	compiled by GNU C version 9.2.0, GMP version 6.1.0, MPFR version 3.1.4, MPC version 1.0.3, isl version isl-0.18-GMP

# GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
# options passed:  -I utilities -I ./linear-algebra/blas/syrk
# -imultiarch x86_64-linux-gnu -D LARGE_DATASET
# ./linear-algebra/blas/syrk/syrk.c -mtune=generic -march=x86-64
# -auxbase-strip O3_unroll_nolinline.s -O3 -funroll-loops -fno-inline
# -fverbose-asm
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
# -frename-registers -freorder-blocks -freorder-blocks-and-partition
# -freorder-functions -frerun-cse-after-loop
# -fsched-critical-path-heuristic -fsched-dep-count-heuristic
# -fsched-group-heuristic -fsched-interblock -fsched-last-insn-heuristic
# -fsched-rank-heuristic -fsched-spec -fsched-spec-insn-heuristic
# -fsched-stalled-insns-dep -fschedule-fusion -fschedule-insns2
# -fsemantic-interposition -fshow-column -fshrink-wrap
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
# -funit-at-a-time -funroll-loops -funswitch-loops -funwind-tables
# -fverbose-asm -fversion-loops-for-strides -fweb -fzero-initialized-in-bss
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
	movapd	%xmm1, %xmm3	# tmp399, beta
	movapd	%xmm0, %xmm2	# tmp398, alpha
	pushq	%r14	#
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	movq	%rdi, %r9	# tmp400, ivtmp.80
	movq	%rsi, %r14	# tmp401, A
# ./linear-algebra/blas/syrk/syrk.c:83:   for (i = 0; i < _PB_N; i++) {
	xorl	%r15d, %r15d	# i
# ./linear-algebra/blas/syrk/syrk.c:68: void kernel_syrk(int n, int m,
	pushq	%r13	#
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	unpcklpd	%xmm1, %xmm1	# vect_cst__188
	pushq	%r12	#
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	leaq	8(%rdi), %r12	#, ivtmp.81
	pushq	%rbp	#
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
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
	movq	-32(%rsp), %rdx	# %sfp, ivtmp.88
	movl	%edx, %r13d	# ivtmp.88, _227
	testl	%r15d, %r15d	# i
	je	.L17	#,
	movl	%edx, %ebx	# ivtmp.88, bnd.27
# ./linear-algebra/blas/syrk/syrk.c:85:       C[i][j] *= beta;
	movq	%r9, %rsi	# ivtmp.80, ivtmp.70
	shrl	%ebx	#
	salq	$4, %rbx	#, tmp225
	leaq	(%rbx,%r9), %rcx	#, _206
	subq	$16, %rbx	#, tmp247
	shrq	$4, %rbx	#, tmp245
	addq	$1, %rbx	#, tmp248
	andl	$7, %ebx	#, tmp249
	je	.L4	#,
	cmpq	$1, %rbx	#, tmp249
	je	.L83	#,
	cmpq	$2, %rbx	#, tmp249
	je	.L84	#,
	cmpq	$3, %rbx	#, tmp249
	je	.L85	#,
	cmpq	$4, %rbx	#, tmp249
	je	.L86	#,
	cmpq	$5, %rbx	#, tmp249
	je	.L87	#,
	cmpq	$6, %rbx	#, tmp249
	je	.L88	#,
	movupd	(%r9), %xmm0	# MEM[base: _201, offset: 0B], vect__9.33
	leaq	16(%r9), %rsi	#, ivtmp.70
	mulpd	%xmm1, %xmm0	# vect_cst__188, vect__9.33
	movups	%xmm0, (%r9)	# vect__9.33, MEM[base: _201, offset: 0B]
.L88:
	movupd	(%rsi), %xmm4	# MEM[base: _201, offset: 0B], vect__9.33
	addq	$16, %rsi	#, ivtmp.70
	mulpd	%xmm1, %xmm4	# vect_cst__188, vect__9.33
	movups	%xmm4, -16(%rsi)	# vect__9.33, MEM[base: _201, offset: 0B]
.L87:
	movupd	(%rsi), %xmm5	# MEM[base: _201, offset: 0B], vect__9.33
	addq	$16, %rsi	#, ivtmp.70
	mulpd	%xmm1, %xmm5	# vect_cst__188, vect__9.33
	movups	%xmm5, -16(%rsi)	# vect__9.33, MEM[base: _201, offset: 0B]
.L86:
	movupd	(%rsi), %xmm6	# MEM[base: _201, offset: 0B], vect__9.33
	addq	$16, %rsi	#, ivtmp.70
	mulpd	%xmm1, %xmm6	# vect_cst__188, vect__9.33
	movups	%xmm6, -16(%rsi)	# vect__9.33, MEM[base: _201, offset: 0B]
.L85:
	movupd	(%rsi), %xmm7	# MEM[base: _201, offset: 0B], vect__9.33
	addq	$16, %rsi	#, ivtmp.70
	mulpd	%xmm1, %xmm7	# vect_cst__188, vect__9.33
	movups	%xmm7, -16(%rsi)	# vect__9.33, MEM[base: _201, offset: 0B]
.L84:
	movupd	(%rsi), %xmm8	# MEM[base: _201, offset: 0B], vect__9.33
	addq	$16, %rsi	#, ivtmp.70
	mulpd	%xmm1, %xmm8	# vect_cst__188, vect__9.33
	movups	%xmm8, -16(%rsi)	# vect__9.33, MEM[base: _201, offset: 0B]
.L83:
	movupd	(%rsi), %xmm9	# MEM[base: _201, offset: 0B], vect__9.33
	addq	$16, %rsi	#, ivtmp.70
	mulpd	%xmm1, %xmm9	# vect_cst__188, vect__9.33
	movups	%xmm9, -16(%rsi)	# vect__9.33, MEM[base: _201, offset: 0B]
	cmpq	%rcx, %rsi	# _206, ivtmp.70
	je	.L112	#,
.L4:
	movupd	(%rsi), %xmm10	# MEM[base: _201, offset: 0B], vect__9.33
	movupd	16(%rsi), %xmm11	# MEM[base: _201, offset: 0B], vect__9.33
	subq	$-128, %rsi	#, ivtmp.70
	movupd	-96(%rsi), %xmm12	# MEM[base: _201, offset: 0B], vect__9.33
	movupd	-80(%rsi), %xmm13	# MEM[base: _201, offset: 0B], vect__9.33
	movupd	-64(%rsi), %xmm14	# MEM[base: _201, offset: 0B], vect__9.33
	movupd	-48(%rsi), %xmm15	# MEM[base: _201, offset: 0B], vect__9.33
	mulpd	%xmm1, %xmm10	# vect_cst__188, vect__9.33
	movupd	-32(%rsi), %xmm0	# MEM[base: _201, offset: 0B], vect__9.33
	movupd	-16(%rsi), %xmm4	# MEM[base: _201, offset: 0B], vect__9.33
	mulpd	%xmm1, %xmm11	# vect_cst__188, vect__9.33
	mulpd	%xmm1, %xmm12	# vect_cst__188, vect__9.33
	mulpd	%xmm1, %xmm13	# vect_cst__188, vect__9.33
	mulpd	%xmm1, %xmm14	# vect_cst__188, vect__9.33
	mulpd	%xmm1, %xmm15	# vect_cst__188, vect__9.33
	movups	%xmm10, -128(%rsi)	# vect__9.33, MEM[base: _201, offset: 0B]
	mulpd	%xmm1, %xmm0	# vect_cst__188, vect__9.33
	movups	%xmm11, -112(%rsi)	# vect__9.33, MEM[base: _201, offset: 0B]
	mulpd	%xmm1, %xmm4	# vect_cst__188, vect__9.33
	movups	%xmm12, -96(%rsi)	# vect__9.33, MEM[base: _201, offset: 0B]
	movups	%xmm13, -80(%rsi)	# vect__9.33, MEM[base: _201, offset: 0B]
	movups	%xmm14, -64(%rsi)	# vect__9.33, MEM[base: _201, offset: 0B]
	movups	%xmm15, -48(%rsi)	# vect__9.33, MEM[base: _201, offset: 0B]
	movups	%xmm0, -32(%rsi)	# vect__9.33, MEM[base: _201, offset: 0B]
	movups	%xmm4, -16(%rsi)	# vect__9.33, MEM[base: _201, offset: 0B]
	cmpq	%rcx, %rsi	# _206, ivtmp.70
	jne	.L4	#,
.L112:
	movl	%r13d, %eax	# _227, tmp.29
	andl	$-2, %eax	#, tmp.29
	testb	$1, %r13b	#, _227
	je	.L3	#,
.L16:
	cltq
	leaq	(%r9,%rax,8), %rdi	#, _35
	movsd	(%rdi), %xmm5	# MEM[(double[1800] *)_35], tmp179
	mulsd	%xmm3, %xmm5	# beta, tmp179
	movsd	%xmm5, (%rdi)	# tmp179, MEM[(double[1800] *)_35]
.L3:
	movq	-32(%rsp), %rbp	# %sfp, tmp183
	subq	-24(%rsp), %rbp	# %sfp, tmp183
	movl	%r13d, %edx	# _227, niters_vector_mult_vf.16
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	xorl	%r10d, %r10d	# ivtmp.55
	imulq	$12000, %rbp, %r8	#, tmp183, _22
	andl	$-2, %edx	#,
	movl	%r13d, %ebp	# _227, bnd.15
	movq	-16(%rsp), %r11	# %sfp, ivtmp.83
	imulq	$12000, %rdx, %rbx	#, _123, tmp187
	shrl	%ebp	#
	movl	%edx, -36(%rsp)	# niters_vector_mult_vf.16, %sfp
	salq	$4, %rbp	#, tmp186
	leaq	-8(%r11), %rsi	#, ivtmp.65
	leaq	-12000(%r8), %rcx	#, tmp226
	addq	%r9, %rbp	# ivtmp.80, _87
	leaq	(%r9,%rdx,8), %r8	#, _190
	movq	%rcx, -48(%rsp)	# tmp226, %sfp
	addq	%r14, %rbx	# A, _125
	.p2align 4,,10
	.p2align 3
.L6:
	leaq	-8(%r11), %rdi	#, tmp206
	movslq	%r10d, %rcx	# ivtmp.55,
	leaq	(%r14,%r10,8), %rax	#, ivtmp.41
	cmpq	%rdi, %r12	# tmp206, ivtmp.81
	setbe	%dil	#, tmp208
	cmpq	%r11, %r9	# ivtmp.60, ivtmp.80
	setnb	%dl	#, tmp210
	orl	%edi, %edx	# tmp208, tmp211
	cmpl	$1, %r15d	#, i
	seta	%dil	#, tmp213
	testb	%dil, %dl	# tmp213, tmp211
	je	.L18	#,
	movq	-48(%rsp), %rdx	# %sfp, tmp226
	leaq	(%rdx,%r11), %rdi	#, tmp216
	cmpq	%rdi, %r9	# tmp216, ivtmp.80
	setnb	%dil	#, tmp218
	cmpq	%rax, %r12	# ivtmp.41, ivtmp.81
	setbe	%dl	#, tmp220
	orb	%dl, %dil	# tmp220, tmp218
	je	.L18	#,
	movsd	(%rsi), %xmm8	# MEM[base: _131, offset: 0B], _47
	movq	%rbp, %rdi	# _87, tmp239
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	movq	%r9, %rdx	# ivtmp.80, ivtmp.46
	subq	%r9, %rdi	# ivtmp.80, tmp239
	mulsd	%xmm2, %xmm8	# alpha, _47
	subq	$16, %rdi	#, tmp240
	shrq	$4, %rdi	#, tmp238
	addq	$1, %rdi	#, tmp241
	unpcklpd	%xmm8, %xmm8	# vect__22.21
	andl	$3, %edi	#, tmp242
	je	.L10	#,
	cmpq	$1, %rdi	#, tmp242
	je	.L75	#,
	cmpq	$2, %rdi	#, tmp242
	je	.L76	#,
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	movsd	(%rax), %xmm6	# MEM[base: _80, offset: 0B], MEM[base: _80, offset: 0B]
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	movupd	(%r9), %xmm7	# MEM[base: _68, offset: 0B], tmp502
	leaq	16(%r9), %rdx	#, ivtmp.46
	addq	$24000, %rax	#, ivtmp.41
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	movhpd	-12000(%rax), %xmm6	# MEM[base: _80, offset: 12000B], tmp368
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	mulpd	%xmm8, %xmm6	# vect__22.21, vect__27.22
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	addpd	%xmm7, %xmm6	# tmp502, vect__28.23
	movups	%xmm6, (%r9)	# vect__28.23, MEM[base: _68, offset: 0B]
.L76:
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	movsd	(%rax), %xmm9	# MEM[base: _80, offset: 0B], MEM[base: _80, offset: 0B]
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	movupd	(%rdx), %xmm10	# MEM[base: _68, offset: 0B], tmp503
	addq	$16, %rdx	#, ivtmp.46
	addq	$24000, %rax	#, ivtmp.41
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	movhpd	-12000(%rax), %xmm9	# MEM[base: _80, offset: 12000B], tmp374
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	mulpd	%xmm8, %xmm9	# vect__22.21, vect__27.22
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	addpd	%xmm10, %xmm9	# tmp503, vect__28.23
	movups	%xmm9, -16(%rdx)	# vect__28.23, MEM[base: _68, offset: 0B]
.L75:
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	movsd	(%rax), %xmm11	# MEM[base: _80, offset: 0B], MEM[base: _80, offset: 0B]
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	movupd	(%rdx), %xmm12	# MEM[base: _68, offset: 0B], tmp504
	addq	$16, %rdx	#, ivtmp.46
	addq	$24000, %rax	#, ivtmp.41
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	movhpd	-12000(%rax), %xmm11	# MEM[base: _80, offset: 12000B], tmp380
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	mulpd	%xmm8, %xmm11	# vect__22.21, vect__27.22
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	addpd	%xmm12, %xmm11	# tmp504, vect__28.23
	movups	%xmm11, -16(%rdx)	# vect__28.23, MEM[base: _68, offset: 0B]
	cmpq	%rbp, %rdx	# _87, ivtmp.46
	je	.L111	#,
.L10:
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	movsd	(%rax), %xmm13	# MEM[base: _80, offset: 0B], MEM[base: _80, offset: 0B]
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	movupd	(%rdx), %xmm14	# MEM[base: _68, offset: 0B], tmp483
	addq	$64, %rdx	#, ivtmp.46
	addq	$96000, %rax	#, ivtmp.41
	movupd	-48(%rdx), %xmm0	# MEM[base: _68, offset: 0B], tmp484
	movupd	-32(%rdx), %xmm5	# MEM[base: _68, offset: 0B], tmp485
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	movhpd	-84000(%rax), %xmm13	# MEM[base: _80, offset: 12000B], tmp199
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	movupd	-16(%rdx), %xmm7	# MEM[base: _68, offset: 0B], tmp486
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	mulpd	%xmm8, %xmm13	# vect__22.21, vect__27.22
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	addpd	%xmm14, %xmm13	# tmp483, vect__28.23
	movups	%xmm13, -64(%rdx)	# vect__28.23, MEM[base: _68, offset: 0B]
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	movsd	-72000(%rax), %xmm15	# MEM[base: _80, offset: 0B], MEM[base: _80, offset: 0B]
	movhpd	-60000(%rax), %xmm15	# MEM[base: _80, offset: 12000B], tmp318
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	mulpd	%xmm8, %xmm15	# vect__22.21, vect__27.22
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	addpd	%xmm0, %xmm15	# tmp484, vect__28.23
	movups	%xmm15, -48(%rdx)	# vect__28.23, MEM[base: _68, offset: 0B]
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	movsd	-48000(%rax), %xmm4	# MEM[base: _80, offset: 0B], MEM[base: _80, offset: 0B]
	movhpd	-36000(%rax), %xmm4	# MEM[base: _80, offset: 12000B], tmp326
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	mulpd	%xmm8, %xmm4	# vect__22.21, vect__27.22
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	addpd	%xmm5, %xmm4	# tmp485, vect__28.23
	movups	%xmm4, -32(%rdx)	# vect__28.23, MEM[base: _68, offset: 0B]
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	movsd	-24000(%rax), %xmm6	# MEM[base: _80, offset: 0B], MEM[base: _80, offset: 0B]
	movhpd	-12000(%rax), %xmm6	# MEM[base: _80, offset: 12000B], tmp334
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	mulpd	%xmm8, %xmm6	# vect__22.21, vect__27.22
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	addpd	%xmm7, %xmm6	# tmp486, vect__28.23
	movups	%xmm6, -16(%rdx)	# vect__28.23, MEM[base: _68, offset: 0B]
	cmpq	%rbp, %rdx	# _87, ivtmp.46
	jne	.L10	#,
.L111:
	cmpl	%r13d, -36(%rsp)	# _227, %sfp
	je	.L9	#,
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	movsd	(%rsi), %xmm8	# MEM[base: _131, offset: 0B], tmp189
	mulsd	%xmm2, %xmm8	# alpha, tmp189
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	mulsd	(%rbx,%rcx,8), %xmm8	# *_125, tmp191
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	addsd	(%r8), %xmm8	# MEM[(double[1800] *)_190], tmp192
	movsd	%xmm8, (%r8)	# tmp192, MEM[(double[1800] *)_190]
.L9:
	addq	$1, %r10	#, ivtmp.55
	addq	$8, %r11	#, ivtmp.60
	addq	$8, %rsi	#, ivtmp.65
# ./linear-algebra/blas/syrk/syrk.c:86:     for (k = 0; k < _PB_M; k++) {
	cmpq	$1500, %r10	#, ivtmp.55
	jne	.L6	#,
# ./linear-algebra/blas/syrk/syrk.c:83:   for (i = 0; i < _PB_N; i++) {
	addl	$1, %r15d	#, i
	addq	$1, -24(%rsp)	#, %sfp
	addq	$14400, %r9	#, ivtmp.80
	addq	$14408, %r12	#, ivtmp.81
	addq	$12000, -16(%rsp)	#, %sfp
	addq	$1, -32(%rsp)	#, %sfp
# ./linear-algebra/blas/syrk/syrk.c:83:   for (i = 0; i < _PB_N; i++) {
	cmpl	$1800, %r15d	#, i
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
	movq	%r12, %rcx	# ivtmp.81, tmp232
# ./linear-algebra/blas/syrk/syrk.c:85:       C[i][j] *= beta;
	movq	%r9, %rdi	# ivtmp.80, ivtmp.40
	subq	%r9, %rcx	# ivtmp.80, tmp232
	subq	$8, %rcx	#, tmp233
	shrq	$3, %rcx	#, tmp231
	addq	$1, %rcx	#, tmp234
	andl	$7, %ecx	#, tmp235
	je	.L8	#,
	cmpq	$1, %rcx	#, tmp235
	je	.L77	#,
	cmpq	$2, %rcx	#, tmp235
	je	.L78	#,
	cmpq	$3, %rcx	#, tmp235
	je	.L79	#,
	cmpq	$4, %rcx	#, tmp235
	je	.L80	#,
	cmpq	$5, %rcx	#, tmp235
	je	.L81	#,
	cmpq	$6, %rcx	#, tmp235
	je	.L82	#,
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	movsd	(%rsi), %xmm9	# MEM[base: _28, offset: 0B], tmp338
	leaq	8(%r9), %rdi	#, ivtmp.40
	addq	$12000, %rax	#, ivtmp.41
	mulsd	%xmm2, %xmm9	# alpha, tmp338
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	mulsd	-12000(%rax), %xmm9	# MEM[base: _41, offset: 0B], tmp339
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	addsd	(%r9), %xmm9	# MEM[base: _49, offset: 0B], tmp341
	movsd	%xmm9, (%r9)	# tmp341, MEM[base: _49, offset: 0B]
.L82:
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	movsd	(%rsi), %xmm10	# MEM[base: _28, offset: 0B], tmp342
	addq	$8, %rdi	#, ivtmp.40
	addq	$12000, %rax	#, ivtmp.41
	mulsd	%xmm2, %xmm10	# alpha, tmp342
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	mulsd	-12000(%rax), %xmm10	# MEM[base: _41, offset: 0B], tmp343
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	addsd	-8(%rdi), %xmm10	# MEM[base: _49, offset: 0B], tmp345
	movsd	%xmm10, -8(%rdi)	# tmp345, MEM[base: _49, offset: 0B]
.L81:
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	movsd	(%rsi), %xmm11	# MEM[base: _28, offset: 0B], tmp346
	addq	$8, %rdi	#, ivtmp.40
	addq	$12000, %rax	#, ivtmp.41
	mulsd	%xmm2, %xmm11	# alpha, tmp346
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	mulsd	-12000(%rax), %xmm11	# MEM[base: _41, offset: 0B], tmp347
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	addsd	-8(%rdi), %xmm11	# MEM[base: _49, offset: 0B], tmp349
	movsd	%xmm11, -8(%rdi)	# tmp349, MEM[base: _49, offset: 0B]
.L80:
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	movsd	(%rsi), %xmm12	# MEM[base: _28, offset: 0B], tmp350
	addq	$8, %rdi	#, ivtmp.40
	addq	$12000, %rax	#, ivtmp.41
	mulsd	%xmm2, %xmm12	# alpha, tmp350
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	mulsd	-12000(%rax), %xmm12	# MEM[base: _41, offset: 0B], tmp351
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	addsd	-8(%rdi), %xmm12	# MEM[base: _49, offset: 0B], tmp353
	movsd	%xmm12, -8(%rdi)	# tmp353, MEM[base: _49, offset: 0B]
.L79:
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	movsd	(%rsi), %xmm13	# MEM[base: _28, offset: 0B], tmp354
	addq	$8, %rdi	#, ivtmp.40
	addq	$12000, %rax	#, ivtmp.41
	mulsd	%xmm2, %xmm13	# alpha, tmp354
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	mulsd	-12000(%rax), %xmm13	# MEM[base: _41, offset: 0B], tmp355
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	addsd	-8(%rdi), %xmm13	# MEM[base: _49, offset: 0B], tmp357
	movsd	%xmm13, -8(%rdi)	# tmp357, MEM[base: _49, offset: 0B]
.L78:
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	movsd	(%rsi), %xmm14	# MEM[base: _28, offset: 0B], tmp358
	addq	$8, %rdi	#, ivtmp.40
	addq	$12000, %rax	#, ivtmp.41
	mulsd	%xmm2, %xmm14	# alpha, tmp358
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	mulsd	-12000(%rax), %xmm14	# MEM[base: _41, offset: 0B], tmp359
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	addsd	-8(%rdi), %xmm14	# MEM[base: _49, offset: 0B], tmp361
	movsd	%xmm14, -8(%rdi)	# tmp361, MEM[base: _49, offset: 0B]
.L77:
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	movsd	(%rsi), %xmm15	# MEM[base: _28, offset: 0B], tmp362
	addq	$8, %rdi	#, ivtmp.40
	addq	$12000, %rax	#, ivtmp.41
	mulsd	%xmm2, %xmm15	# alpha, tmp362
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	mulsd	-12000(%rax), %xmm15	# MEM[base: _41, offset: 0B], tmp363
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	addsd	-8(%rdi), %xmm15	# MEM[base: _49, offset: 0B], tmp365
	movsd	%xmm15, -8(%rdi)	# tmp365, MEM[base: _49, offset: 0B]
# ./linear-algebra/blas/syrk/syrk.c:87:       for (j = 0; j <= i; j++)
	cmpq	%r12, %rdi	# ivtmp.81, ivtmp.40
	je	.L9	#,
.L8:
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	movsd	(%rsi), %xmm0	# MEM[base: _28, offset: 0B], tmp194
	addq	$64, %rdi	#, ivtmp.40
	addq	$96000, %rax	#, ivtmp.41
	mulsd	%xmm2, %xmm0	# alpha, tmp194
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	mulsd	-96000(%rax), %xmm0	# MEM[base: _41, offset: 0B], tmp195
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	addsd	-64(%rdi), %xmm0	# MEM[base: _49, offset: 0B], tmp196
	movsd	%xmm0, -64(%rdi)	# tmp196, MEM[base: _49, offset: 0B]
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	movsd	(%rsi), %xmm4	# MEM[base: _28, offset: 0B], tmp274
	mulsd	%xmm2, %xmm4	# alpha, tmp274
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	mulsd	-84000(%rax), %xmm4	# MEM[base: _41, offset: 0B], tmp275
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	addsd	-56(%rdi), %xmm4	# MEM[base: _49, offset: 0B], tmp277
	movsd	%xmm4, -56(%rdi)	# tmp277, MEM[base: _49, offset: 0B]
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	movsd	(%rsi), %xmm5	# MEM[base: _28, offset: 0B], tmp280
	mulsd	%xmm2, %xmm5	# alpha, tmp280
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	mulsd	-72000(%rax), %xmm5	# MEM[base: _41, offset: 0B], tmp281
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	addsd	-48(%rdi), %xmm5	# MEM[base: _49, offset: 0B], tmp283
	movsd	%xmm5, -48(%rdi)	# tmp283, MEM[base: _49, offset: 0B]
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	movsd	(%rsi), %xmm6	# MEM[base: _28, offset: 0B], tmp286
	mulsd	%xmm2, %xmm6	# alpha, tmp286
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	mulsd	-60000(%rax), %xmm6	# MEM[base: _41, offset: 0B], tmp287
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	addsd	-40(%rdi), %xmm6	# MEM[base: _49, offset: 0B], tmp289
	movsd	%xmm6, -40(%rdi)	# tmp289, MEM[base: _49, offset: 0B]
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	movsd	(%rsi), %xmm7	# MEM[base: _28, offset: 0B], tmp292
	mulsd	%xmm2, %xmm7	# alpha, tmp292
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	mulsd	-48000(%rax), %xmm7	# MEM[base: _41, offset: 0B], tmp293
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	addsd	-32(%rdi), %xmm7	# MEM[base: _49, offset: 0B], tmp295
	movsd	%xmm7, -32(%rdi)	# tmp295, MEM[base: _49, offset: 0B]
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	movsd	(%rsi), %xmm8	# MEM[base: _28, offset: 0B], tmp298
	mulsd	%xmm2, %xmm8	# alpha, tmp298
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	mulsd	-36000(%rax), %xmm8	# MEM[base: _41, offset: 0B], tmp299
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	addsd	-24(%rdi), %xmm8	# MEM[base: _49, offset: 0B], tmp301
	movsd	%xmm8, -24(%rdi)	# tmp301, MEM[base: _49, offset: 0B]
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	movsd	(%rsi), %xmm9	# MEM[base: _28, offset: 0B], tmp304
	mulsd	%xmm2, %xmm9	# alpha, tmp304
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	mulsd	-24000(%rax), %xmm9	# MEM[base: _41, offset: 0B], tmp305
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	addsd	-16(%rdi), %xmm9	# MEM[base: _49, offset: 0B], tmp307
	movsd	%xmm9, -16(%rdi)	# tmp307, MEM[base: _49, offset: 0B]
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	movsd	(%rsi), %xmm10	# MEM[base: _28, offset: 0B], tmp310
	mulsd	%xmm2, %xmm10	# alpha, tmp310
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	mulsd	-12000(%rax), %xmm10	# MEM[base: _41, offset: 0B], tmp311
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	addsd	-8(%rdi), %xmm10	# MEM[base: _49, offset: 0B], tmp313
	movsd	%xmm10, -8(%rdi)	# tmp313, MEM[base: _49, offset: 0B]
# ./linear-algebra/blas/syrk/syrk.c:87:       for (j = 0; j <= i; j++)
	cmpq	%r12, %rdi	# ivtmp.81, ivtmp.40
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
.L122:
# ./linear-algebra/blas/syrk/syrk.c:58: 	fprintf (POLYBENCH_DUMP_TARGET, DATA_PRINTF_MODIFIER, C[i][j]);
	xorl	%ebx, %ebx	# ivtmp.96
	jmp	.L127	#
	.p2align 4,,10
	.p2align 3
.L123:
# ./linear-algebra/blas/syrk/syrk.c:58: 	fprintf (POLYBENCH_DUMP_TARGET, DATA_PRINTF_MODIFIER, C[i][j]);
	movsd	(%r12,%rbx,8), %xmm0	# MEM[base: _12, index: ivtmp.96_20, step: 8, offset: 0B], MEM[base: _12, index: ivtmp.96_20, step: 8, offset: 0B]
	movl	$.LC3, %esi	#,
.L129:
	movl	$1, %eax	#,
	addq	$1, %rbx	#, ivtmp.96
	call	fprintf	#
# ./linear-algebra/blas/syrk/syrk.c:56:     for (j = 0; j < n; j++) {
	cmpq	$1800, %rbx	#, ivtmp.96
	je	.L130	#,
.L127:
	leal	0(%rbp,%rbx), %eax	#, tmp99
	movq	stderr(%rip), %rdi	# stderr, pretmp_40
	imull	$-858993459, %eax, %edx	#, tmp99, tmp111
	rorl	$2, %edx	#, tmp112
# ./linear-algebra/blas/syrk/syrk.c:57: 	if ((i * n + j) % 20 == 0) fprintf (POLYBENCH_DUMP_TARGET, "\n");
	cmpl	$214748364, %edx	#, tmp112
	ja	.L123	#,
# ./linear-algebra/blas/syrk/syrk.c:57: 	if ((i * n + j) % 20 == 0) fprintf (POLYBENCH_DUMP_TARGET, "\n");
	movq	%rdi, %rsi	# pretmp_40,
	movl	$10, %edi	#,
	call	fputc	#
# ./linear-algebra/blas/syrk/syrk.c:58: 	fprintf (POLYBENCH_DUMP_TARGET, DATA_PRINTF_MODIFIER, C[i][j]);
	movsd	(%r12,%rbx,8), %xmm0	# MEM[base: _12, index: ivtmp.96_20, step: 8, offset: 0B], MEM[base: _12, index: ivtmp.96_20, step: 8, offset: 0B]
	movl	$.LC3, %esi	#,
	movq	stderr(%rip), %rdi	# stderr,
	jmp	.L129	#
	.p2align 4,,10
	.p2align 3
.L130:
	addl	$1800, %ebp	#, ivtmp.110
	addq	$14400, %r12	#, ivtmp.109
# ./linear-algebra/blas/syrk/syrk.c:55:   for (i = 0; i < n; i++)
	cmpl	$3240000, %ebp	#, ivtmp.110
	jne	.L122	#,
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
	movq	.LC7(%rip), %rax	#, tmp256
	pxor	%xmm4, %xmm4	# tmp139
	movdqa	.LC11(%rip), %xmm2	#, tmp239
# ./linear-algebra/blas/syrk/syrk.c:36:   for (i = 0; i < n; i++)
	xorl	%r9d, %r9d	# i
	movdqa	%xmm4, %xmm7	# tmp139, tmp143
	movdqa	.LC9(%rip), %xmm5	#, tmp237
	movdqa	.LC10(%rip), %xmm11	#, tmp238
# ./linear-algebra/blas/syrk/syrk.c:34:   *alpha = 1.5;
	movq	%rax, (%rdi)	# tmp256, *alpha_1(D)
	pcmpgtd	%xmm2, %xmm7	# tmp239, tmp143
# ./linear-algebra/blas/syrk/syrk.c:35:   *beta = 1.2;
	movq	.LC8(%rip), %rdi	#, tmp257
	movapd	.LC12(%rip), %xmm8	#, tmp240
	movdqa	.LC6(%rip), %xmm6	#, vect_vec_iv_.113
	movq	%rdi, (%rsi)	# tmp257, *beta_2(D)
	leaq	12000(%rcx), %rsi	#, ivtmp.166
	.p2align 4,,10
	.p2align 3
.L132:
	movd	%r9d, %xmm3	# i, i
# ./linear-algebra/blas/syrk/syrk.c:26: void init_array(int n, int m,
	movq	%rcx, %r8	# ivtmp.165, ivtmp.154
	movdqa	%xmm6, %xmm15	# vect_vec_iv_.113, vect_vec_iv_.124
	pshufd	$0, %xmm3, %xmm9	# i, vect_cst__99
	movdqa	%xmm9, %xmm10	# vect_cst__99, tmp236
	psrlq	$32, %xmm10	#, tmp236
	.p2align 4,,10
	.p2align 3
.L133:
	movdqa	%xmm15, %xmm1	# vect_vec_iv_.124, vect_vec_iv_.124
	movdqa	%xmm7, %xmm13	# tmp143, tmp145
	addq	$32, %r8	#, ivtmp.154
# ./linear-algebra/blas/syrk/syrk.c:38:       A[i][j] = (DATA_TYPE) ((i*j+1)%n) / n;
	movdqa	%xmm1, %xmm0	# vect_vec_iv_.124, tmp129
	psrlq	$32, %xmm1	#, tmp131
	paddd	%xmm5, %xmm15	# tmp237, vect_vec_iv_.124
	pmuludq	%xmm9, %xmm0	# vect_cst__99, tmp129
	pmuludq	%xmm10, %xmm1	# tmp236, tmp130
	pshufd	$8, %xmm0, %xmm3	#, tmp129, tmp127
	pshufd	$8, %xmm1, %xmm12	#, tmp130, tmp128
	movdqa	%xmm4, %xmm1	# tmp139, tmp140
	punpckldq	%xmm12, %xmm3	# tmp128, vect__5.125
	movdqa	%xmm4, %xmm12	# tmp139, tmp153
# ./linear-algebra/blas/syrk/syrk.c:38:       A[i][j] = (DATA_TYPE) ((i*j+1)%n) / n;
	paddd	%xmm11, %xmm3	# tmp238, vect__6.126
	movdqa	%xmm3, %xmm14	# vect__6.126, tmp136
	movdqa	%xmm3, %xmm0	# vect__6.126, tmp149
	punpckldq	%xmm3, %xmm14	# vect__6.126, tmp136
	punpckhdq	%xmm3, %xmm0	# vect__6.126, tmp149
	pcmpgtd	%xmm14, %xmm1	# tmp136, tmp140
	pmuludq	%xmm14, %xmm13	# tmp136, tmp145
	pmuludq	%xmm2, %xmm14	# tmp239, tmp146
	pcmpgtd	%xmm0, %xmm12	# tmp149, tmp153
	pmuludq	%xmm2, %xmm1	# tmp239, tmp144
	pmuludq	%xmm2, %xmm12	# tmp239, tmp157
	paddq	%xmm13, %xmm1	# tmp145, tmp244
	psllq	$32, %xmm1	#, tmp245
	paddq	%xmm14, %xmm1	# tmp146, tmp134
	movdqa	%xmm7, %xmm14	# tmp143, tmp158
	pmuludq	%xmm0, %xmm14	# tmp149, tmp158
	pmuludq	%xmm2, %xmm0	# tmp239, tmp159
	paddq	%xmm14, %xmm12	# tmp158, tmp246
	psllq	$32, %xmm12	#, tmp247
	paddq	%xmm0, %xmm12	# tmp159, tmp147
	shufps	$221, %xmm12, %xmm1	#, tmp147, vect_patt_91.127
	paddd	%xmm3, %xmm1	# vect__6.126, vect_patt_92.128
	psrad	$10, %xmm1	#, vect_patt_92.128
	movdqa	%xmm1, %xmm13	# vect_patt_92.128, vect_patt_93.129
	pslld	$3, %xmm1	#, tmp166
	psubd	%xmm13, %xmm1	# vect_patt_93.129, tmp167
	pslld	$5, %xmm1	#, tmp168
	paddd	%xmm13, %xmm1	# vect_patt_93.129, vect_patt_94.130
	pslld	$3, %xmm1	#, tmp170
	psubd	%xmm1, %xmm3	# tmp170, vect_patt_95.131
# ./linear-algebra/blas/syrk/syrk.c:38:       A[i][j] = (DATA_TYPE) ((i*j+1)%n) / n;
	cvtdq2pd	%xmm3, %xmm1	# vect_patt_95.131, vect__8.132
# ./linear-algebra/blas/syrk/syrk.c:38:       A[i][j] = (DATA_TYPE) ((i*j+1)%n) / n;
	divpd	%xmm8, %xmm1	# tmp240, vect__14.133
# ./linear-algebra/blas/syrk/syrk.c:38:       A[i][j] = (DATA_TYPE) ((i*j+1)%n) / n;
	pshufd	$238, %xmm3, %xmm3	#, vect_patt_95.131, tmp175
	cvtdq2pd	%xmm3, %xmm0	# tmp175, vect__8.132
# ./linear-algebra/blas/syrk/syrk.c:38:       A[i][j] = (DATA_TYPE) ((i*j+1)%n) / n;
	divpd	%xmm8, %xmm0	# tmp240, vect__14.133
# ./linear-algebra/blas/syrk/syrk.c:38:       A[i][j] = (DATA_TYPE) ((i*j+1)%n) / n;
	movups	%xmm1, -32(%r8)	# vect__14.133, MEM[base: _19, offset: 0B]
	movups	%xmm0, -16(%r8)	# vect__14.133, MEM[base: _19, offset: 16B]
	cmpq	%rsi, %r8	# ivtmp.166, ivtmp.154
	jne	.L133	#,
# ./linear-algebra/blas/syrk/syrk.c:36:   for (i = 0; i < n; i++)
	addl	$1, %r9d	#, i
	addq	$12000, %rcx	#, ivtmp.165
	leaq	12000(%r8), %rsi	#, ivtmp.166
# ./linear-algebra/blas/syrk/syrk.c:36:   for (i = 0; i < n; i++)
	cmpl	$1800, %r9d	#, i
	jne	.L132	#,
	movdqa	.LC14(%rip), %xmm2	#, tmp242
	pxor	%xmm4, %xmm4	# tmp193
	movq	%rdx, %r11	# C, ivtmp.149
# ./linear-algebra/blas/syrk/syrk.c:39:   for (i = 0; i < n; i++)
	xorl	%ecx, %ecx	# i
	movdqa	%xmm4, %xmm7	# tmp193, tmp197
	leaq	14400(%rdx), %rdx	#, ivtmp.150
	movdqa	.LC13(%rip), %xmm11	#, tmp241
	movapd	.LC15(%rip), %xmm8	#, tmp243
	pcmpgtd	%xmm2, %xmm7	# tmp242, tmp197
	.p2align 4,,10
	.p2align 3
.L134:
	movd	%ecx, %xmm9	# i, i
# ./linear-algebra/blas/syrk/syrk.c:36:   for (i = 0; i < n; i++)
	movq	%r11, %r10	# ivtmp.149, ivtmp.138
	movdqa	%xmm6, %xmm3	# vect_vec_iv_.113, vect_vec_iv_.113
	pshufd	$0, %xmm9, %xmm15	# i, vect_cst__69
	movdqa	%xmm15, %xmm10	# vect_cst__69, tmp234
	psrlq	$32, %xmm10	#, tmp234
	.p2align 4,,10
	.p2align 3
.L135:
	movdqa	%xmm3, %xmm12	# vect_vec_iv_.113, vect_vec_iv_.113
	movdqa	%xmm4, %xmm1	# tmp193, tmp194
	addq	$32, %r10	#, ivtmp.138
# ./linear-algebra/blas/syrk/syrk.c:41:       C[i][j] = (DATA_TYPE) ((i*j+2)%m) / m;
	movdqa	%xmm12, %xmm14	# vect_vec_iv_.113, tmp183
	psrlq	$32, %xmm12	#, tmp185
	paddd	%xmm5, %xmm3	# tmp237, vect_vec_iv_.113
	pmuludq	%xmm15, %xmm14	# vect_cst__69, tmp183
	pmuludq	%xmm10, %xmm12	# tmp234, tmp184
	pshufd	$8, %xmm14, %xmm0	#, tmp183, tmp181
	pshufd	$8, %xmm12, %xmm13	#, tmp184, tmp182
	movdqa	%xmm7, %xmm12	# tmp197, tmp199
	punpckldq	%xmm13, %xmm0	# tmp182, vect__19.114
	movdqa	%xmm7, %xmm14	# tmp197, tmp212
# ./linear-algebra/blas/syrk/syrk.c:41:       C[i][j] = (DATA_TYPE) ((i*j+2)%m) / m;
	paddd	%xmm11, %xmm0	# tmp241, vect__20.115
	movdqa	%xmm0, %xmm9	# vect__20.115, tmp190
	movdqa	%xmm0, %xmm13	# vect__20.115, tmp203
	punpckldq	%xmm0, %xmm9	# vect__20.115, tmp190
	punpckhdq	%xmm0, %xmm13	# vect__20.115, tmp203
	pcmpgtd	%xmm9, %xmm1	# tmp190, tmp194
	pmuludq	%xmm9, %xmm12	# tmp190, tmp199
	pmuludq	%xmm2, %xmm9	# tmp242, tmp200
	pmuludq	%xmm13, %xmm14	# tmp203, tmp212
	pmuludq	%xmm2, %xmm1	# tmp242, tmp198
	paddq	%xmm12, %xmm1	# tmp199, tmp248
	psllq	$32, %xmm1	#, tmp249
	paddq	%xmm9, %xmm1	# tmp200, tmp188
	movdqa	%xmm4, %xmm9	# tmp193, tmp207
	pcmpgtd	%xmm13, %xmm9	# tmp203, tmp207
	pmuludq	%xmm2, %xmm13	# tmp242, tmp213
	pmuludq	%xmm2, %xmm9	# tmp242, tmp211
	paddq	%xmm14, %xmm9	# tmp212, tmp250
	psllq	$32, %xmm9	#, tmp251
	paddq	%xmm13, %xmm9	# tmp213, tmp201
	shufps	$221, %xmm9, %xmm1	#, tmp201, vect_patt_31.116
	psrad	$5, %xmm1	#, vect_patt_18.117
	movdqa	%xmm1, %xmm12	# vect_patt_18.117, tmp219
	pslld	$1, %xmm12	#, tmp219
	paddd	%xmm1, %xmm12	# vect_patt_18.117, tmp220
	pslld	$4, %xmm12	#, tmp221
	psubd	%xmm1, %xmm12	# vect_patt_18.117, tmp222
	pslld	$3, %xmm12	#, tmp223
	psubd	%xmm1, %xmm12	# vect_patt_18.117, tmp223
	pslld	$2, %xmm12	#, tmp225
	psubd	%xmm12, %xmm0	# tmp225, vect_patt_4.119
# ./linear-algebra/blas/syrk/syrk.c:41:       C[i][j] = (DATA_TYPE) ((i*j+2)%m) / m;
	cvtdq2pd	%xmm0, %xmm1	# vect_patt_4.119, vect__22.120
# ./linear-algebra/blas/syrk/syrk.c:41:       C[i][j] = (DATA_TYPE) ((i*j+2)%m) / m;
	divpd	%xmm8, %xmm1	# tmp243, vect__28.121
# ./linear-algebra/blas/syrk/syrk.c:41:       C[i][j] = (DATA_TYPE) ((i*j+2)%m) / m;
	pshufd	$238, %xmm0, %xmm0	#, vect_patt_4.119, tmp230
	cvtdq2pd	%xmm0, %xmm13	# tmp230, vect__22.120
# ./linear-algebra/blas/syrk/syrk.c:41:       C[i][j] = (DATA_TYPE) ((i*j+2)%m) / m;
	divpd	%xmm8, %xmm13	# tmp243, vect__28.121
# ./linear-algebra/blas/syrk/syrk.c:41:       C[i][j] = (DATA_TYPE) ((i*j+2)%m) / m;
	movups	%xmm1, -32(%r10)	# vect__28.121, MEM[base: _61, offset: 0B]
	movups	%xmm13, -16(%r10)	# vect__28.121, MEM[base: _61, offset: 16B]
	cmpq	%rdx, %r10	# ivtmp.150, ivtmp.138
	jne	.L135	#,
# ./linear-algebra/blas/syrk/syrk.c:39:   for (i = 0; i < n; i++)
	addl	$1, %ecx	#, i
	addq	$14400, %r11	#, ivtmp.149
	leaq	14400(%r10), %rdx	#, ivtmp.150
# ./linear-algebra/blas/syrk/syrk.c:39:   for (i = 0; i < n; i++)
	cmpl	$1800, %ecx	#, i
	jne	.L134	#,
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
	jle	.L141	#,
# ./linear-algebra/blas/syrk/syrk.c:123:   polybench_prevent_dce(print_array(n, POLYBENCH_ARRAY(C)));
	movq	0(%r13), %rax	# *argv_13(D), *argv_13(D)
	cmpb	$0, (%rax)	#, MEM[(const unsigned char * {ref-all})_3]
	je	.L143	#,
.L141:
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
.L143:
	.cfi_restore_state
# ./linear-algebra/blas/syrk/syrk.c:123:   polybench_prevent_dce(print_array(n, POLYBENCH_ARRAY(C)));
	movq	%rbp, %rdi	# C,
	call	print_array.constprop.0	#
	jmp	.L141	#
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
