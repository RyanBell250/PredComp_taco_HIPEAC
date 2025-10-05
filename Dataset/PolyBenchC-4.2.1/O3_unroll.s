	.file	"syrk.c"
# GNU C17 (GCC) version 9.2.0 (x86_64-pc-linux-gnu)
#	compiled by GNU C version 9.2.0, GMP version 6.1.0, MPFR version 3.1.4, MPC version 1.0.3, isl version isl-0.18-GMP

# GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
# options passed:  -I utilities -I ./linear-algebra/blas/syrk
# -imultiarch x86_64-linux-gnu -D LARGE_DATASET
# ./linear-algebra/blas/syrk/syrk.c -mtune=generic -march=x86-64
# -auxbase-strip O3_unroll.s -O3 -funroll-loops -fverbose-asm
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
# -fif-conversion2 -findirect-inlining -finline -finline-atomics
# -finline-functions -finline-functions-called-once
# -finline-small-functions -fipa-bit-cp -fipa-cp -fipa-cp-clone -fipa-icf
# -fipa-icf-functions -fipa-icf-variables -fipa-profile -fipa-pure-const
# -fipa-ra -fipa-reference -fipa-reference-addressable -fipa-sra
# -fipa-stack-alignment -fipa-vrp -fira-hoist-pressure
# -fira-share-save-slots -fira-share-spill-slots
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
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC11:
	.string	"==BEGIN DUMP_ARRAYS==\n"
.LC12:
	.string	"C"
.LC13:
	.string	"begin dump: %s"
.LC14:
	.string	"%0.2lf "
.LC15:
	.string	"\nend   dump: %s\n"
.LC16:
	.string	"==END   DUMP_ARRAYS==\n"
	.section	.text.startup,"ax",@progbits
	.p2align 4
	.globl	main
	.type	main, @function
main:
.LFB25:
	.cfi_startproc
	pushq	%r15	#
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	pushq	%r14	#
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	pushq	%r13	#
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	pushq	%r12	#
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	pushq	%rbp	#
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	pushq	%rbx	#
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	subq	$56, %rsp	#,
	.cfi_def_cfa_offset 112
# ./linear-algebra/blas/syrk/syrk.c:97: {
	movl	%edi, 12(%rsp)	# tmp620, %sfp
# ./linear-algebra/blas/syrk/syrk.c:105:   POLYBENCH_2D_ARRAY_DECL(C,DATA_TYPE,N,N,n,n);
	movl	$3240000, %edi	#,
# ./linear-algebra/blas/syrk/syrk.c:97: {
	movq	%rsi, 40(%rsp)	# tmp621, %sfp
# ./linear-algebra/blas/syrk/syrk.c:105:   POLYBENCH_2D_ARRAY_DECL(C,DATA_TYPE,N,N,n,n);
	movl	$8, %esi	#,
	call	polybench_alloc_data	#
# ./linear-algebra/blas/syrk/syrk.c:106:   POLYBENCH_2D_ARRAY_DECL(A,DATA_TYPE,N,M,n,m);
	movl	$8, %esi	#,
	movl	$2700000, %edi	#,
# ./linear-algebra/blas/syrk/syrk.c:105:   POLYBENCH_2D_ARRAY_DECL(C,DATA_TYPE,N,N,n,n);
	movq	%rax, %r14	# tmp622, C
# ./linear-algebra/blas/syrk/syrk.c:106:   POLYBENCH_2D_ARRAY_DECL(A,DATA_TYPE,N,M,n,m);
	call	polybench_alloc_data	#
	movdqa	.LC3(%rip), %xmm2	#, tmp416
# ./linear-algebra/blas/syrk/syrk.c:36:   for (i = 0; i < n; i++)
	xorl	%edx, %edx	# i
	pxor	%xmm3, %xmm3	# tmp242
	movdqa	%xmm3, %xmm7	# tmp242, tmp246
# ./linear-algebra/blas/syrk/syrk.c:106:   POLYBENCH_2D_ARRAY_DECL(A,DATA_TYPE,N,M,n,m);
	movq	%rax, %r15	# tmp623, A
	movdqa	.LC1(%rip), %xmm6	#, tmp413
	movdqa	.LC2(%rip), %xmm10	#, tmp415
	pcmpgtd	%xmm2, %xmm7	# tmp416, tmp246
	movdqa	.LC0(%rip), %xmm5	#, vect_vec_iv_.36
	movapd	.LC4(%rip), %xmm8	#, tmp417
	.p2align 4,,10
	.p2align 3
.L2:
	movd	%edx, %xmm4	# i, i
# ./linear-algebra/blas/syrk/syrk.c:97: {
	movdqa	%xmm5, %xmm15	# vect_vec_iv_.36, vect_vec_iv_.47
	leaq	12000(%rax), %rcx	#, _367
	pshufd	$0, %xmm4, %xmm9	# i, vect_cst__329
	movdqa	%xmm9, %xmm11	# vect_cst__329, tmp424
	psrlq	$32, %xmm11	#, tmp424
	.p2align 4,,10
	.p2align 3
.L3:
	movdqa	%xmm15, %xmm1	# vect_vec_iv_.47, vect_vec_iv_.47
	movdqa	%xmm7, %xmm13	# tmp246, tmp248
	addq	$32, %rax	#, ivtmp.150
# ./linear-algebra/blas/syrk/syrk.c:38:       A[i][j] = (DATA_TYPE) ((i*j+1)%n) / n;
	movdqa	%xmm1, %xmm0	# vect_vec_iv_.47, tmp232
	psrlq	$32, %xmm1	#, tmp234
	paddd	%xmm6, %xmm15	# tmp413, vect_vec_iv_.47
	pmuludq	%xmm9, %xmm0	# vect_cst__329, tmp232
	pmuludq	%xmm11, %xmm1	# tmp424, tmp233
	pshufd	$8, %xmm0, %xmm4	#, tmp232, tmp230
	pshufd	$8, %xmm1, %xmm12	#, tmp233, tmp231
	movdqa	%xmm3, %xmm1	# tmp242, tmp243
	punpckldq	%xmm12, %xmm4	# tmp231, vect__49.48
	movdqa	%xmm3, %xmm12	# tmp242, tmp256
# ./linear-algebra/blas/syrk/syrk.c:38:       A[i][j] = (DATA_TYPE) ((i*j+1)%n) / n;
	paddd	%xmm10, %xmm4	# tmp415, vect__50.49
	movdqa	%xmm4, %xmm14	# vect__50.49, tmp239
	movdqa	%xmm4, %xmm0	# vect__50.49, tmp252
	punpckldq	%xmm4, %xmm14	# vect__50.49, tmp239
	punpckhdq	%xmm4, %xmm0	# vect__50.49, tmp252
	pcmpgtd	%xmm14, %xmm1	# tmp239, tmp243
	pmuludq	%xmm14, %xmm13	# tmp239, tmp248
	pmuludq	%xmm2, %xmm14	# tmp416, tmp249
	pcmpgtd	%xmm0, %xmm12	# tmp252, tmp256
	pmuludq	%xmm2, %xmm1	# tmp416, tmp247
	pmuludq	%xmm2, %xmm12	# tmp416, tmp260
	paddq	%xmm13, %xmm1	# tmp248, tmp451
	psllq	$32, %xmm1	#, tmp452
	paddq	%xmm14, %xmm1	# tmp249, tmp237
	movdqa	%xmm7, %xmm14	# tmp246, tmp261
	pmuludq	%xmm0, %xmm14	# tmp252, tmp261
	pmuludq	%xmm2, %xmm0	# tmp416, tmp262
	paddq	%xmm14, %xmm12	# tmp261, tmp453
	psllq	$32, %xmm12	#, tmp454
	paddq	%xmm0, %xmm12	# tmp262, tmp250
	shufps	$221, %xmm12, %xmm1	#, tmp250, vect_patt_321.50
	paddd	%xmm4, %xmm1	# vect__50.49, vect_patt_322.51
	psrad	$10, %xmm1	#, vect_patt_322.51
	movdqa	%xmm1, %xmm13	# vect_patt_322.51, vect_patt_323.52
	pslld	$3, %xmm1	#, tmp269
	psubd	%xmm13, %xmm1	# vect_patt_323.52, tmp270
	pslld	$5, %xmm1	#, tmp271
	paddd	%xmm13, %xmm1	# vect_patt_323.52, vect_patt_324.53
	pslld	$3, %xmm1	#, tmp273
	psubd	%xmm1, %xmm4	# tmp273, vect_patt_325.54
# ./linear-algebra/blas/syrk/syrk.c:38:       A[i][j] = (DATA_TYPE) ((i*j+1)%n) / n;
	cvtdq2pd	%xmm4, %xmm1	# vect_patt_325.54, vect__52.55
# ./linear-algebra/blas/syrk/syrk.c:38:       A[i][j] = (DATA_TYPE) ((i*j+1)%n) / n;
	divpd	%xmm8, %xmm1	# tmp417, vect__57.56
# ./linear-algebra/blas/syrk/syrk.c:38:       A[i][j] = (DATA_TYPE) ((i*j+1)%n) / n;
	pshufd	$238, %xmm4, %xmm4	#, vect_patt_325.54, tmp278
	cvtdq2pd	%xmm4, %xmm0	# tmp278, vect__52.55
# ./linear-algebra/blas/syrk/syrk.c:38:       A[i][j] = (DATA_TYPE) ((i*j+1)%n) / n;
	divpd	%xmm8, %xmm0	# tmp417, vect__57.56
# ./linear-algebra/blas/syrk/syrk.c:38:       A[i][j] = (DATA_TYPE) ((i*j+1)%n) / n;
	movups	%xmm1, -32(%rax)	# vect__57.56, MEM[base: _360, offset: 0B]
	movups	%xmm0, -16(%rax)	# vect__57.56, MEM[base: _360, offset: 16B]
	cmpq	%rcx, %rax	# _367, ivtmp.150
	jne	.L3	#,
# ./linear-algebra/blas/syrk/syrk.c:36:   for (i = 0; i < n; i++)
	addl	$1, %edx	#, i
# ./linear-algebra/blas/syrk/syrk.c:36:   for (i = 0; i < n; i++)
	cmpl	$1800, %edx	#, i
	jne	.L2	#,
	movdqa	.LC6(%rip), %xmm2	#, tmp419
	movq	%r14, %r12	# C, ivtmp.75
	movq	%r14, %rax	# C, ivtmp.145
# ./linear-algebra/blas/syrk/syrk.c:39:   for (i = 0; i < n; i++)
	xorl	%ebx, %ebx	# i
	movdqa	.LC5(%rip), %xmm15	#, tmp418
	pxor	%xmm3, %xmm3	# tmp296
	movapd	.LC7(%rip), %xmm8	#, tmp420
	movdqa	%xmm3, %xmm7	# tmp296, tmp300
	pcmpgtd	%xmm2, %xmm7	# tmp419, tmp300
	.p2align 4,,10
	.p2align 3
.L6:
	movd	%ebx, %xmm9	# i, i
	movdqa	%xmm5, %xmm4	# vect_vec_iv_.36, vect_vec_iv_.36
	leaq	14400(%rax), %rsi	#, _356
	pshufd	$0, %xmm9, %xmm10	# i, vect_cst__289
	movdqa	%xmm10, %xmm11	# vect_cst__289, tmp423
	psrlq	$32, %xmm11	#, tmp423
	.p2align 4,,10
	.p2align 3
.L5:
	movdqa	%xmm4, %xmm12	# vect_vec_iv_.36, vect_vec_iv_.36
	movdqa	%xmm3, %xmm1	# tmp296, tmp297
	addq	$32, %rax	#, ivtmp.134
# ./linear-algebra/blas/syrk/syrk.c:41:       C[i][j] = (DATA_TYPE) ((i*j+2)%m) / m;
	movdqa	%xmm12, %xmm14	# vect_vec_iv_.36, tmp286
	psrlq	$32, %xmm12	#, tmp288
	paddd	%xmm6, %xmm4	# tmp413, vect_vec_iv_.36
	pmuludq	%xmm10, %xmm14	# vect_cst__289, tmp286
	pmuludq	%xmm11, %xmm12	# tmp423, tmp287
	pshufd	$8, %xmm14, %xmm0	#, tmp286, tmp284
	pshufd	$8, %xmm12, %xmm13	#, tmp287, tmp285
	movdqa	%xmm7, %xmm12	# tmp300, tmp302
	punpckldq	%xmm13, %xmm0	# tmp285, vect__62.37
	movdqa	%xmm7, %xmm14	# tmp300, tmp315
# ./linear-algebra/blas/syrk/syrk.c:41:       C[i][j] = (DATA_TYPE) ((i*j+2)%m) / m;
	paddd	%xmm15, %xmm0	# tmp418, vect__63.38
	movdqa	%xmm0, %xmm9	# vect__63.38, tmp293
	movdqa	%xmm0, %xmm13	# vect__63.38, tmp306
	punpckldq	%xmm0, %xmm9	# vect__63.38, tmp293
	punpckhdq	%xmm0, %xmm13	# vect__63.38, tmp306
	pcmpgtd	%xmm9, %xmm1	# tmp293, tmp297
	pmuludq	%xmm9, %xmm12	# tmp293, tmp302
	pmuludq	%xmm2, %xmm9	# tmp419, tmp303
	pmuludq	%xmm13, %xmm14	# tmp306, tmp315
	pmuludq	%xmm2, %xmm1	# tmp419, tmp301
	paddq	%xmm12, %xmm1	# tmp302, tmp455
	psllq	$32, %xmm1	#, tmp456
	paddq	%xmm9, %xmm1	# tmp303, tmp291
	movdqa	%xmm3, %xmm9	# tmp296, tmp310
	pcmpgtd	%xmm13, %xmm9	# tmp306, tmp310
	pmuludq	%xmm2, %xmm13	# tmp419, tmp316
	pmuludq	%xmm2, %xmm9	# tmp419, tmp314
	paddq	%xmm14, %xmm9	# tmp315, tmp457
	psllq	$32, %xmm9	#, tmp458
	paddq	%xmm13, %xmm9	# tmp316, tmp304
	shufps	$221, %xmm9, %xmm1	#, tmp304, vect_patt_282.39
	psrad	$5, %xmm1	#, vect_patt_283.40
	movdqa	%xmm1, %xmm12	# vect_patt_283.40, tmp322
	pslld	$1, %xmm12	#, tmp322
	paddd	%xmm1, %xmm12	# vect_patt_283.40, tmp323
	pslld	$4, %xmm12	#, tmp324
	psubd	%xmm1, %xmm12	# vect_patt_283.40, tmp325
	pslld	$3, %xmm12	#, tmp326
	psubd	%xmm1, %xmm12	# vect_patt_283.40, tmp326
	pslld	$2, %xmm12	#, tmp328
	psubd	%xmm12, %xmm0	# tmp328, vect_patt_285.42
# ./linear-algebra/blas/syrk/syrk.c:41:       C[i][j] = (DATA_TYPE) ((i*j+2)%m) / m;
	cvtdq2pd	%xmm0, %xmm1	# vect_patt_285.42, vect__65.43
# ./linear-algebra/blas/syrk/syrk.c:41:       C[i][j] = (DATA_TYPE) ((i*j+2)%m) / m;
	divpd	%xmm8, %xmm1	# tmp420, vect__70.44
# ./linear-algebra/blas/syrk/syrk.c:41:       C[i][j] = (DATA_TYPE) ((i*j+2)%m) / m;
	pshufd	$238, %xmm0, %xmm0	#, vect_patt_285.42, tmp333
	cvtdq2pd	%xmm0, %xmm13	# tmp333, vect__65.43
# ./linear-algebra/blas/syrk/syrk.c:41:       C[i][j] = (DATA_TYPE) ((i*j+2)%m) / m;
	divpd	%xmm8, %xmm13	# tmp420, vect__70.44
# ./linear-algebra/blas/syrk/syrk.c:41:       C[i][j] = (DATA_TYPE) ((i*j+2)%m) / m;
	movups	%xmm1, -32(%rax)	# vect__70.44, MEM[base: _277, offset: 0B]
	movups	%xmm13, -16(%rax)	# vect__70.44, MEM[base: _277, offset: 16B]
	cmpq	%rsi, %rax	# _356, ivtmp.134
	jne	.L5	#,
# ./linear-algebra/blas/syrk/syrk.c:39:   for (i = 0; i < n; i++)
	addl	$1, %ebx	#, i
# ./linear-algebra/blas/syrk/syrk.c:39:   for (i = 0; i < n; i++)
	cmpl	$1800, %ebx	#, i
	jne	.L6	#,
	movq	%r14, 24(%rsp)	# C, %sfp
	movl	$1, %ebp	#, ivtmp.127
	movq	%r15, %rdi	# A, ivtmp.120
	movq	%r14, %rcx	# C, ivtmp.119
	movsd	.LC10(%rip), %xmm0	#, tmp422
	movapd	.LC9(%rip), %xmm1	#, tmp428
	leaq	8(%r14), %r10	#, ivtmp.121
	xorl	%r13d, %r13d	# ivtmp.114
# ./linear-algebra/blas/syrk/syrk.c:85:       C[i][j] *= beta;
	movsd	.LC8(%rip), %xmm4	#, tmp429
	movq	%r12, 32(%rsp)	# ivtmp.75, %sfp
	movq	%rbp, %r12	# ivtmp.127, ivtmp.127
	.p2align 4,,10
	.p2align 3
.L7:
	movl	%r12d, %r11d	# ivtmp.127, _320
	testq	%r13, %r13	# ivtmp.114
	je	.L30	#,
	movl	%r12d, %r8d	# ivtmp.127, bnd.27
	movq	%rcx, %rdx	# ivtmp.119, ivtmp.109
	shrl	%r8d	#
	salq	$4, %r8	#, tmp392
	leaq	(%r8,%rcx), %r9	#, _41
	subq	$16, %r8	#, tmp447
	shrq	$4, %r8	#, tmp445
	addq	$1, %r8	#, tmp448
	andl	$7, %r8d	#, tmp449
	je	.L9	#,
	cmpq	$1, %r8	#, tmp449
	je	.L98	#,
	cmpq	$2, %r8	#, tmp449
	je	.L99	#,
	cmpq	$3, %r8	#, tmp449
	je	.L100	#,
	cmpq	$4, %r8	#, tmp449
	je	.L101	#,
	cmpq	$5, %r8	#, tmp449
	je	.L102	#,
	cmpq	$6, %r8	#, tmp449
	je	.L103	#,
	movupd	(%rcx), %xmm5	# MEM[base: _37, offset: 0B], vect__26.33
	leaq	16(%rcx), %rdx	#, ivtmp.109
	mulpd	%xmm1, %xmm5	# tmp428, vect__26.33
	movups	%xmm5, (%rcx)	# vect__26.33, MEM[base: _37, offset: 0B]
.L103:
	movupd	(%rdx), %xmm6	# MEM[base: _37, offset: 0B], vect__26.33
	addq	$16, %rdx	#, ivtmp.109
	mulpd	%xmm1, %xmm6	# tmp428, vect__26.33
	movups	%xmm6, -16(%rdx)	# vect__26.33, MEM[base: _37, offset: 0B]
.L102:
	movupd	(%rdx), %xmm15	# MEM[base: _37, offset: 0B], vect__26.33
	addq	$16, %rdx	#, ivtmp.109
	mulpd	%xmm1, %xmm15	# tmp428, vect__26.33
	movups	%xmm15, -16(%rdx)	# vect__26.33, MEM[base: _37, offset: 0B]
.L101:
	movupd	(%rdx), %xmm2	# MEM[base: _37, offset: 0B], vect__26.33
	addq	$16, %rdx	#, ivtmp.109
	mulpd	%xmm1, %xmm2	# tmp428, vect__26.33
	movups	%xmm2, -16(%rdx)	# vect__26.33, MEM[base: _37, offset: 0B]
.L100:
	movupd	(%rdx), %xmm8	# MEM[base: _37, offset: 0B], vect__26.33
	addq	$16, %rdx	#, ivtmp.109
	mulpd	%xmm1, %xmm8	# tmp428, vect__26.33
	movups	%xmm8, -16(%rdx)	# vect__26.33, MEM[base: _37, offset: 0B]
.L99:
	movupd	(%rdx), %xmm3	# MEM[base: _37, offset: 0B], vect__26.33
	addq	$16, %rdx	#, ivtmp.109
	mulpd	%xmm1, %xmm3	# tmp428, vect__26.33
	movups	%xmm3, -16(%rdx)	# vect__26.33, MEM[base: _37, offset: 0B]
.L98:
	movupd	(%rdx), %xmm7	# MEM[base: _37, offset: 0B], vect__26.33
	addq	$16, %rdx	#, ivtmp.109
	mulpd	%xmm1, %xmm7	# tmp428, vect__26.33
	movups	%xmm7, -16(%rdx)	# vect__26.33, MEM[base: _37, offset: 0B]
	cmpq	%r9, %rdx	# _41, ivtmp.109
	je	.L127	#,
.L9:
	movupd	(%rdx), %xmm10	# MEM[base: _37, offset: 0B], vect__26.33
	movupd	16(%rdx), %xmm11	# MEM[base: _37, offset: 0B], vect__26.33
	subq	$-128, %rdx	#, ivtmp.109
	movupd	-96(%rdx), %xmm9	# MEM[base: _37, offset: 0B], vect__26.33
	movupd	-80(%rdx), %xmm14	# MEM[base: _37, offset: 0B], vect__26.33
	movupd	-64(%rdx), %xmm12	# MEM[base: _37, offset: 0B], vect__26.33
	movupd	-48(%rdx), %xmm13	# MEM[base: _37, offset: 0B], vect__26.33
	mulpd	%xmm1, %xmm10	# tmp428, vect__26.33
	movupd	-32(%rdx), %xmm5	# MEM[base: _37, offset: 0B], vect__26.33
	movupd	-16(%rdx), %xmm6	# MEM[base: _37, offset: 0B], vect__26.33
	mulpd	%xmm1, %xmm11	# tmp428, vect__26.33
	mulpd	%xmm1, %xmm9	# tmp428, vect__26.33
	mulpd	%xmm1, %xmm14	# tmp428, vect__26.33
	mulpd	%xmm1, %xmm12	# tmp428, vect__26.33
	mulpd	%xmm1, %xmm13	# tmp428, vect__26.33
	movups	%xmm10, -128(%rdx)	# vect__26.33, MEM[base: _37, offset: 0B]
	mulpd	%xmm1, %xmm5	# tmp428, vect__26.33
	movups	%xmm11, -112(%rdx)	# vect__26.33, MEM[base: _37, offset: 0B]
	mulpd	%xmm1, %xmm6	# tmp428, vect__26.33
	movups	%xmm9, -96(%rdx)	# vect__26.33, MEM[base: _37, offset: 0B]
	movups	%xmm14, -80(%rdx)	# vect__26.33, MEM[base: _37, offset: 0B]
	movups	%xmm12, -64(%rdx)	# vect__26.33, MEM[base: _37, offset: 0B]
	movups	%xmm13, -48(%rdx)	# vect__26.33, MEM[base: _37, offset: 0B]
	movups	%xmm5, -32(%rdx)	# vect__26.33, MEM[base: _37, offset: 0B]
	movups	%xmm6, -16(%rdx)	# vect__26.33, MEM[base: _37, offset: 0B]
	cmpq	%r9, %rdx	# _41, ivtmp.109
	jne	.L9	#,
.L127:
	movl	%r11d, %eax	# _320, tmp.29
	andl	$-2, %eax	#, tmp.29
	testb	$1, %r11b	#, _320
	je	.L8	#,
.L21:
	cltq
	leaq	(%rcx,%rax,8), %r14	#, _93
	movsd	(%r14), %xmm15	# MEM[(double[1800] *)_93], tmp339
	mulsd	%xmm4, %xmm15	# tmp429, tmp339
	movsd	%xmm15, (%r14)	# tmp339, MEM[(double[1800] *)_93]
.L8:
	movq	%r12, %rsi	# ivtmp.127, tmp345
	movl	%r11d, %r8d	# _320, niters_vector_mult_vf.16
	leaq	8(%rdi), %rbx	#, ivtmp.99
	movl	%r11d, %r9d	# _320, bnd.15
	subq	%r13, %rsi	# ivtmp.114, tmp345
	andl	$-2, %r8d	#, niters_vector_mult_vf.16
	shrl	%r9d	#
	imulq	$12000, %rsi, %rbp	#, tmp345, _69
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	movl	%r8d, %eax	# niters_vector_mult_vf.16, _201
	movl	%r8d, 8(%rsp)	# niters_vector_mult_vf.16, %sfp
	salq	$4, %r9	#, tmp348
	imulq	$12000, %rax, %rdx	#, _201, tmp349
	addq	%rcx, %r9	# ivtmp.119, _214
	leaq	(%rcx,%rax,8), %r14	#, _113
	subq	$12000, %rbp	#, tmp425
	movq	%rbp, 16(%rsp)	# tmp425, %sfp
	addq	%r15, %rdx	# A, _203
	movq	%rdx, (%rsp)	# _203, %sfp
	xorl	%edx, %edx	# ivtmp.94
	.p2align 4,,10
	.p2align 3
.L11:
	leaq	-8(%rbx), %rsi	#, tmp374
	movslq	%edx, %rbp	# ivtmp.94,
	leaq	(%r15,%rdx,8), %rax	#, ivtmp.88
	cmpq	%rsi, %r10	# tmp374, ivtmp.121
	setbe	%sil	#, tmp376
	cmpq	%rbx, %rcx	# ivtmp.99, ivtmp.119
	setnb	%r8b	#, tmp378
	orl	%r8d, %esi	# tmp378, tmp379
	cmpl	$1, %r13d	#, ivtmp.114
	seta	%r8b	#, tmp381
	testb	%r8b, %sil	# tmp381, tmp379
	je	.L31	#,
	movq	16(%rsp), %rsi	# %sfp, tmp425
	addq	%rbx, %rsi	# ivtmp.99, tmp384
	cmpq	%rsi, %rcx	# tmp384, ivtmp.119
	setnb	%r8b	#, tmp386
	cmpq	%rax, %r10	# ivtmp.88, ivtmp.121
	setbe	%sil	#, tmp388
	orb	%sil, %r8b	# tmp388, tmp386
	je	.L31	#,
	movsd	(%rdi,%rdx,8), %xmm2	# MEM[base: _34, index: ivtmp.94_224, step: 8, offset: 0B], _139
	movq	%r9, %r8	# _214, tmp439
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	movq	%rcx, %rsi	# ivtmp.119, ivtmp.85
	subq	%rcx, %r8	# ivtmp.119, tmp439
	mulsd	%xmm0, %xmm2	# tmp422, _139
	subq	$16, %r8	#, tmp440
	shrq	$4, %r8	#, tmp438
	addq	$1, %r8	#, tmp441
	unpcklpd	%xmm2, %xmm2	# vect__37.21
	andl	$3, %r8d	#, tmp442
	je	.L15	#,
	cmpq	$1, %r8	#, tmp442
	je	.L90	#,
	cmpq	$2, %r8	#, tmp442
	je	.L91	#,
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	movsd	(%rax), %xmm8	# MEM[base: _194, offset: 0B], MEM[base: _194, offset: 0B]
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	movupd	(%rcx), %xmm3	# MEM[base: _167, offset: 0B], tmp763
	leaq	16(%rcx), %rsi	#, ivtmp.85
	addq	$24000, %rax	#, ivtmp.88
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	movhpd	-12000(%rax), %xmm8	# MEM[base: _194, offset: 12000B], tmp590
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	mulpd	%xmm2, %xmm8	# vect__37.21, vect__42.22
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	addpd	%xmm3, %xmm8	# tmp763, vect__43.23
	movups	%xmm8, (%rcx)	# vect__43.23, MEM[base: _167, offset: 0B]
.L91:
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	movsd	(%rax), %xmm7	# MEM[base: _194, offset: 0B], MEM[base: _194, offset: 0B]
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	movupd	(%rsi), %xmm10	# MEM[base: _167, offset: 0B], tmp764
	addq	$16, %rsi	#, ivtmp.85
	addq	$24000, %rax	#, ivtmp.88
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	movhpd	-12000(%rax), %xmm7	# MEM[base: _194, offset: 12000B], tmp596
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	mulpd	%xmm2, %xmm7	# vect__37.21, vect__42.22
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	addpd	%xmm10, %xmm7	# tmp764, vect__43.23
	movups	%xmm7, -16(%rsi)	# vect__43.23, MEM[base: _167, offset: 0B]
.L90:
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	movsd	(%rax), %xmm11	# MEM[base: _194, offset: 0B], MEM[base: _194, offset: 0B]
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	movupd	(%rsi), %xmm9	# MEM[base: _167, offset: 0B], tmp765
	addq	$16, %rsi	#, ivtmp.85
	addq	$24000, %rax	#, ivtmp.88
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	movhpd	-12000(%rax), %xmm11	# MEM[base: _194, offset: 12000B], tmp602
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	mulpd	%xmm2, %xmm11	# vect__37.21, vect__42.22
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	addpd	%xmm9, %xmm11	# tmp765, vect__43.23
	movups	%xmm11, -16(%rsi)	# vect__43.23, MEM[base: _167, offset: 0B]
	cmpq	%r9, %rsi	# _214, ivtmp.85
	je	.L126	#,
.L15:
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	movsd	(%rax), %xmm14	# MEM[base: _194, offset: 0B], MEM[base: _194, offset: 0B]
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	movupd	(%rsi), %xmm12	# MEM[base: _167, offset: 0B], tmp745
	addq	$64, %rsi	#, ivtmp.85
	addq	$96000, %rax	#, ivtmp.88
	movupd	-48(%rsi), %xmm5	# MEM[base: _167, offset: 0B], tmp746
	movupd	-32(%rsi), %xmm15	# MEM[base: _167, offset: 0B], tmp747
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	movhpd	-84000(%rax), %xmm14	# MEM[base: _194, offset: 12000B], tmp367
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	movupd	-16(%rsi), %xmm3	# MEM[base: _167, offset: 0B], tmp748
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	mulpd	%xmm2, %xmm14	# vect__37.21, vect__42.22
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	addpd	%xmm12, %xmm14	# tmp745, vect__43.23
	movups	%xmm14, -64(%rsi)	# vect__43.23, MEM[base: _167, offset: 0B]
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	movsd	-72000(%rax), %xmm13	# MEM[base: _194, offset: 0B], MEM[base: _194, offset: 0B]
	movhpd	-60000(%rax), %xmm13	# MEM[base: _194, offset: 12000B], tmp533
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	mulpd	%xmm2, %xmm13	# vect__37.21, vect__42.22
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	addpd	%xmm5, %xmm13	# tmp746, vect__43.23
	movups	%xmm13, -48(%rsi)	# vect__43.23, MEM[base: _167, offset: 0B]
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	movsd	-48000(%rax), %xmm6	# MEM[base: _194, offset: 0B], MEM[base: _194, offset: 0B]
	movhpd	-36000(%rax), %xmm6	# MEM[base: _194, offset: 12000B], tmp541
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	mulpd	%xmm2, %xmm6	# vect__37.21, vect__42.22
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	addpd	%xmm15, %xmm6	# tmp747, vect__43.23
	movups	%xmm6, -32(%rsi)	# vect__43.23, MEM[base: _167, offset: 0B]
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	movsd	-24000(%rax), %xmm8	# MEM[base: _194, offset: 0B], MEM[base: _194, offset: 0B]
	movhpd	-12000(%rax), %xmm8	# MEM[base: _194, offset: 12000B], tmp549
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	mulpd	%xmm2, %xmm8	# vect__37.21, vect__42.22
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	addpd	%xmm3, %xmm8	# tmp748, vect__43.23
	movups	%xmm8, -16(%rsi)	# vect__43.23, MEM[base: _167, offset: 0B]
	cmpq	%r9, %rsi	# _214, ivtmp.85
	jne	.L15	#,
	.p2align 4,,10
	.p2align 3
.L126:
	cmpl	%r11d, 8(%rsp)	# _320, %sfp
	je	.L14	#,
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	movsd	(%rdi,%rdx,8), %xmm2	# MEM[base: _34, index: ivtmp.94_224, step: 8, offset: 0B], tmp351
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	movq	(%rsp), %rax	# %sfp, _203
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	mulsd	%xmm0, %xmm2	# tmp422, tmp351
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	mulsd	(%rax,%rbp,8), %xmm2	# *_203, tmp355
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	addsd	(%r14), %xmm2	# MEM[(double[1800] *)_113], tmp356
	movsd	%xmm2, (%r14)	# tmp356, MEM[(double[1800] *)_113]
.L14:
	addq	$1, %rdx	#, ivtmp.94
	addq	$8, %rbx	#, ivtmp.99
# ./linear-algebra/blas/syrk/syrk.c:86:     for (k = 0; k < _PB_M; k++) {
	cmpq	$1500, %rdx	#, ivtmp.94
	jne	.L11	#,
	addq	$1, %r13	#, ivtmp.114
	addq	$14400, %rcx	#, ivtmp.119
	addq	$1, %r12	#, ivtmp.127
	addq	$12000, %rdi	#, ivtmp.120
	addq	$14408, %r10	#, ivtmp.121
# ./linear-algebra/blas/syrk/syrk.c:83:   for (i = 0; i < _PB_N; i++) {
	cmpq	$1800, %r13	#, ivtmp.114
	jne	.L7	#,
# ./linear-algebra/blas/syrk/syrk.c:123:   polybench_prevent_dce(print_array(n, POLYBENCH_ARRAY(C)));
	cmpl	$42, 12(%rsp)	#, %sfp
	movq	24(%rsp), %r14	# %sfp, C
	movq	32(%rsp), %r12	# %sfp, ivtmp.75
	jle	.L22	#,
# ./linear-algebra/blas/syrk/syrk.c:123:   polybench_prevent_dce(print_array(n, POLYBENCH_ARRAY(C)));
	movq	40(%rsp), %r11	# %sfp, argv
	movq	(%r11), %rdx	# *argv_13(D), *argv_13(D)
	cmpb	$0, (%rdx)	#, MEM[(const unsigned char * {ref-all})_3]
	je	.L137	#,
.L22:
# ./linear-algebra/blas/syrk/syrk.c:126:   POLYBENCH_FREE_ARRAY(C);
	movq	%r14, %rdi	# C,
	call	free	#
# ./linear-algebra/blas/syrk/syrk.c:127:   POLYBENCH_FREE_ARRAY(A);
	movq	%r15, %rdi	# A,
	call	free	#
# ./linear-algebra/blas/syrk/syrk.c:130: }
	addq	$56, %rsp	#,
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	xorl	%eax, %eax	#
	popq	%rbx	#
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
.L31:
	.cfi_restore_state
	movq	%r10, %rbp	# ivtmp.121, tmp432
# ./linear-algebra/blas/syrk/syrk.c:85:       C[i][j] *= beta;
	movq	%rcx, %r8	# ivtmp.119, ivtmp.80
	subq	%rcx, %rbp	# ivtmp.119, tmp432
	subq	$8, %rbp	#, tmp433
	shrq	$3, %rbp	#, tmp431
	addq	$1, %rbp	#, tmp434
	andl	$7, %ebp	#, tmp435
	je	.L13	#,
	cmpq	$1, %rbp	#, tmp435
	je	.L92	#,
	cmpq	$2, %rbp	#, tmp435
	je	.L93	#,
	cmpq	$3, %rbp	#, tmp435
	je	.L94	#,
	cmpq	$4, %rbp	#, tmp435
	je	.L95	#,
	cmpq	$5, %rbp	#, tmp435
	je	.L96	#,
	cmpq	$6, %rbp	#, tmp435
	je	.L97	#,
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	movsd	(%rdi,%rdx,8), %xmm7	# MEM[base: _34, index: ivtmp.94_224, step: 8, offset: 0B], tmp554
	leaq	8(%rcx), %r8	#, ivtmp.80
	addq	$12000, %rax	#, ivtmp.88
	mulsd	%xmm0, %xmm7	# tmp422, tmp554
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	mulsd	-12000(%rax), %xmm7	# MEM[base: _15, offset: 0B], tmp555
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	addsd	(%rcx), %xmm7	# MEM[base: _35, offset: 0B], tmp557
	movsd	%xmm7, (%rcx)	# tmp557, MEM[base: _35, offset: 0B]
.L97:
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	movsd	(%rdi,%rdx,8), %xmm10	# MEM[base: _34, index: ivtmp.94_224, step: 8, offset: 0B], tmp559
	addq	$8, %r8	#, ivtmp.80
	addq	$12000, %rax	#, ivtmp.88
	mulsd	%xmm0, %xmm10	# tmp422, tmp559
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	mulsd	-12000(%rax), %xmm10	# MEM[base: _15, offset: 0B], tmp560
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	addsd	-8(%r8), %xmm10	# MEM[base: _35, offset: 0B], tmp562
	movsd	%xmm10, -8(%r8)	# tmp562, MEM[base: _35, offset: 0B]
.L96:
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	movsd	(%rdi,%rdx,8), %xmm11	# MEM[base: _34, index: ivtmp.94_224, step: 8, offset: 0B], tmp564
	addq	$8, %r8	#, ivtmp.80
	addq	$12000, %rax	#, ivtmp.88
	mulsd	%xmm0, %xmm11	# tmp422, tmp564
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	mulsd	-12000(%rax), %xmm11	# MEM[base: _15, offset: 0B], tmp565
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	addsd	-8(%r8), %xmm11	# MEM[base: _35, offset: 0B], tmp567
	movsd	%xmm11, -8(%r8)	# tmp567, MEM[base: _35, offset: 0B]
.L95:
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	movsd	(%rdi,%rdx,8), %xmm9	# MEM[base: _34, index: ivtmp.94_224, step: 8, offset: 0B], tmp569
	addq	$8, %r8	#, ivtmp.80
	addq	$12000, %rax	#, ivtmp.88
	mulsd	%xmm0, %xmm9	# tmp422, tmp569
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	mulsd	-12000(%rax), %xmm9	# MEM[base: _15, offset: 0B], tmp570
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	addsd	-8(%r8), %xmm9	# MEM[base: _35, offset: 0B], tmp572
	movsd	%xmm9, -8(%r8)	# tmp572, MEM[base: _35, offset: 0B]
.L94:
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	movsd	(%rdi,%rdx,8), %xmm14	# MEM[base: _34, index: ivtmp.94_224, step: 8, offset: 0B], tmp574
	addq	$8, %r8	#, ivtmp.80
	addq	$12000, %rax	#, ivtmp.88
	mulsd	%xmm0, %xmm14	# tmp422, tmp574
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	mulsd	-12000(%rax), %xmm14	# MEM[base: _15, offset: 0B], tmp575
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	addsd	-8(%r8), %xmm14	# MEM[base: _35, offset: 0B], tmp577
	movsd	%xmm14, -8(%r8)	# tmp577, MEM[base: _35, offset: 0B]
.L93:
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	movsd	(%rdi,%rdx,8), %xmm12	# MEM[base: _34, index: ivtmp.94_224, step: 8, offset: 0B], tmp579
	addq	$8, %r8	#, ivtmp.80
	addq	$12000, %rax	#, ivtmp.88
	mulsd	%xmm0, %xmm12	# tmp422, tmp579
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	mulsd	-12000(%rax), %xmm12	# MEM[base: _15, offset: 0B], tmp580
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	addsd	-8(%r8), %xmm12	# MEM[base: _35, offset: 0B], tmp582
	movsd	%xmm12, -8(%r8)	# tmp582, MEM[base: _35, offset: 0B]
.L92:
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	movsd	(%rdi,%rdx,8), %xmm13	# MEM[base: _34, index: ivtmp.94_224, step: 8, offset: 0B], tmp584
	addq	$8, %r8	#, ivtmp.80
	addq	$12000, %rax	#, ivtmp.88
	mulsd	%xmm0, %xmm13	# tmp422, tmp584
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	mulsd	-12000(%rax), %xmm13	# MEM[base: _15, offset: 0B], tmp585
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	addsd	-8(%r8), %xmm13	# MEM[base: _35, offset: 0B], tmp587
	movsd	%xmm13, -8(%r8)	# tmp587, MEM[base: _35, offset: 0B]
# ./linear-algebra/blas/syrk/syrk.c:87:       for (j = 0; j <= i; j++)
	cmpq	%r10, %r8	# ivtmp.121, ivtmp.80
	je	.L14	#,
.L13:
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	movsd	(%rdi,%rdx,8), %xmm5	# MEM[base: _34, index: ivtmp.94_224, step: 8, offset: 0B], tmp358
	addq	$64, %r8	#, ivtmp.80
	addq	$96000, %rax	#, ivtmp.88
	mulsd	%xmm0, %xmm5	# tmp422, tmp358
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	mulsd	-96000(%rax), %xmm5	# MEM[base: _15, offset: 0B], tmp361
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	addsd	-64(%r8), %xmm5	# MEM[base: _35, offset: 0B], tmp362
	movsd	%xmm5, -64(%r8)	# tmp362, MEM[base: _35, offset: 0B]
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	movsd	(%rdi,%rdx,8), %xmm6	# MEM[base: _34, index: ivtmp.94_224, step: 8, offset: 0B], tmp483
	mulsd	%xmm0, %xmm6	# tmp422, tmp483
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	mulsd	-84000(%rax), %xmm6	# MEM[base: _15, offset: 0B], tmp484
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	addsd	-56(%r8), %xmm6	# MEM[base: _35, offset: 0B], tmp486
	movsd	%xmm6, -56(%r8)	# tmp486, MEM[base: _35, offset: 0B]
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	movsd	(%rdi,%rdx,8), %xmm15	# MEM[base: _34, index: ivtmp.94_224, step: 8, offset: 0B], tmp490
	mulsd	%xmm0, %xmm15	# tmp422, tmp490
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	mulsd	-72000(%rax), %xmm15	# MEM[base: _15, offset: 0B], tmp491
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	addsd	-48(%r8), %xmm15	# MEM[base: _35, offset: 0B], tmp493
	movsd	%xmm15, -48(%r8)	# tmp493, MEM[base: _35, offset: 0B]
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	movsd	(%rdi,%rdx,8), %xmm8	# MEM[base: _34, index: ivtmp.94_224, step: 8, offset: 0B], tmp497
	mulsd	%xmm0, %xmm8	# tmp422, tmp497
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	mulsd	-60000(%rax), %xmm8	# MEM[base: _15, offset: 0B], tmp498
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	addsd	-40(%r8), %xmm8	# MEM[base: _35, offset: 0B], tmp500
	movsd	%xmm8, -40(%r8)	# tmp500, MEM[base: _35, offset: 0B]
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	movsd	(%rdi,%rdx,8), %xmm3	# MEM[base: _34, index: ivtmp.94_224, step: 8, offset: 0B], tmp504
	mulsd	%xmm0, %xmm3	# tmp422, tmp504
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	mulsd	-48000(%rax), %xmm3	# MEM[base: _15, offset: 0B], tmp505
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	addsd	-32(%r8), %xmm3	# MEM[base: _35, offset: 0B], tmp507
	movsd	%xmm3, -32(%r8)	# tmp507, MEM[base: _35, offset: 0B]
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	movsd	(%rdi,%rdx,8), %xmm2	# MEM[base: _34, index: ivtmp.94_224, step: 8, offset: 0B], tmp511
	mulsd	%xmm0, %xmm2	# tmp422, tmp511
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	mulsd	-36000(%rax), %xmm2	# MEM[base: _15, offset: 0B], tmp512
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	addsd	-24(%r8), %xmm2	# MEM[base: _35, offset: 0B], tmp514
	movsd	%xmm2, -24(%r8)	# tmp514, MEM[base: _35, offset: 0B]
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	movsd	(%rdi,%rdx,8), %xmm7	# MEM[base: _34, index: ivtmp.94_224, step: 8, offset: 0B], tmp518
	mulsd	%xmm0, %xmm7	# tmp422, tmp518
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	mulsd	-24000(%rax), %xmm7	# MEM[base: _15, offset: 0B], tmp519
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	addsd	-16(%r8), %xmm7	# MEM[base: _35, offset: 0B], tmp521
	movsd	%xmm7, -16(%r8)	# tmp521, MEM[base: _35, offset: 0B]
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	movsd	(%rdi,%rdx,8), %xmm10	# MEM[base: _34, index: ivtmp.94_224, step: 8, offset: 0B], tmp525
	mulsd	%xmm0, %xmm10	# tmp422, tmp525
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	mulsd	-12000(%rax), %xmm10	# MEM[base: _15, offset: 0B], tmp526
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	addsd	-8(%r8), %xmm10	# MEM[base: _35, offset: 0B], tmp528
	movsd	%xmm10, -8(%r8)	# tmp528, MEM[base: _35, offset: 0B]
# ./linear-algebra/blas/syrk/syrk.c:87:       for (j = 0; j <= i; j++)
	cmpq	%r10, %r8	# ivtmp.121, ivtmp.80
	je	.L14	#,
	jmp	.L13	#
	.p2align 4,,10
	.p2align 3
.L30:
# ./linear-algebra/blas/syrk/syrk.c:84:     for (j = 0; j <= i; j++)
	xorl	%eax, %eax	# tmp.29
	jmp	.L21	#
.L137:
# ./linear-algebra/blas/syrk/syrk.c:53:   POLYBENCH_DUMP_START;
	movq	stderr(%rip), %rcx	# stderr,
	movl	$22, %edx	#,
	movl	$1, %esi	#,
# ./linear-algebra/blas/syrk/syrk.c:54:   POLYBENCH_DUMP_BEGIN("C");
	xorl	%r13d, %r13d	# ivtmp.76
# ./linear-algebra/blas/syrk/syrk.c:53:   POLYBENCH_DUMP_START;
	movl	$.LC11, %edi	#,
	call	fwrite	#
# ./linear-algebra/blas/syrk/syrk.c:54:   POLYBENCH_DUMP_BEGIN("C");
	movq	stderr(%rip), %rdi	# stderr,
	movl	$.LC12, %edx	#,
	xorl	%eax, %eax	#
	movl	$.LC13, %esi	#,
	call	fprintf	#
	.p2align 4,,10
	.p2align 3
.L23:
# ./linear-algebra/blas/syrk/syrk.c:58: 	fprintf (POLYBENCH_DUMP_TARGET, DATA_PRINTF_MODIFIER, C[i][j]);
	xorl	%ebx, %ebx	# ivtmp.61
	jmp	.L28	#
	.p2align 4,,10
	.p2align 3
.L24:
# ./linear-algebra/blas/syrk/syrk.c:58: 	fprintf (POLYBENCH_DUMP_TARGET, DATA_PRINTF_MODIFIER, C[i][j]);
	movsd	(%r12,%rbx,8), %xmm0	# MEM[base: _83, index: ivtmp.61_248, step: 8, offset: 0B], MEM[base: _83, index: ivtmp.61_248, step: 8, offset: 0B]
	movl	$.LC14, %esi	#,
.L135:
	movl	$1, %eax	#,
	addq	$1, %rbx	#, ivtmp.61
	call	fprintf	#
# ./linear-algebra/blas/syrk/syrk.c:56:     for (j = 0; j < n; j++) {
	cmpq	$1800, %rbx	#, ivtmp.61
	je	.L138	#,
.L28:
	leal	0(%r13,%rbx), %ecx	#, tmp394
	movq	stderr(%rip), %rdi	# stderr, pretmp_189
	imull	$-858993459, %ecx, %r9d	#, tmp394, tmp406
	rorl	$2, %r9d	#, tmp407
# ./linear-algebra/blas/syrk/syrk.c:57: 	if ((i * n + j) % 20 == 0) fprintf (POLYBENCH_DUMP_TARGET, "\n");
	cmpl	$214748364, %r9d	#, tmp407
	ja	.L24	#,
# ./linear-algebra/blas/syrk/syrk.c:57: 	if ((i * n + j) % 20 == 0) fprintf (POLYBENCH_DUMP_TARGET, "\n");
	movq	%rdi, %rsi	# pretmp_189,
	movl	$10, %edi	#,
	call	fputc	#
# ./linear-algebra/blas/syrk/syrk.c:58: 	fprintf (POLYBENCH_DUMP_TARGET, DATA_PRINTF_MODIFIER, C[i][j]);
	movsd	(%r12,%rbx,8), %xmm0	# MEM[base: _83, index: ivtmp.61_248, step: 8, offset: 0B], MEM[base: _83, index: ivtmp.61_248, step: 8, offset: 0B]
	movl	$.LC14, %esi	#,
	movq	stderr(%rip), %rdi	# stderr,
	jmp	.L135	#
	.p2align 4,,10
	.p2align 3
.L138:
	addl	$1800, %r13d	#, ivtmp.76
	addq	$14400, %r12	#, ivtmp.75
# ./linear-algebra/blas/syrk/syrk.c:55:   for (i = 0; i < n; i++)
	cmpl	$3240000, %r13d	#, ivtmp.76
	jne	.L23	#,
# ./linear-algebra/blas/syrk/syrk.c:60:   POLYBENCH_DUMP_END("C");
	movq	stderr(%rip), %rdi	# stderr,
	movl	$.LC12, %edx	#,
	movl	$.LC15, %esi	#,
	xorl	%eax, %eax	#
	call	fprintf	#
# ./linear-algebra/blas/syrk/syrk.c:61:   POLYBENCH_DUMP_FINISH;
	movl	$22, %edx	#,
	movl	$1, %esi	#,
	movq	stderr(%rip), %rcx	# stderr,
	movl	$.LC16, %edi	#,
	call	fwrite	#
# ./linear-algebra/blas/syrk/syrk.c:62: }
	jmp	.L22	#
	.cfi_endproc
.LFE25:
	.size	main, .-main
	.section	.rodata.cst16,"aM",@progbits,16
	.align 16
.LC0:
	.long	0
	.long	1
	.long	2
	.long	3
	.align 16
.LC1:
	.long	4
	.long	4
	.long	4
	.long	4
	.align 16
.LC2:
	.long	1
	.long	1
	.long	1
	.long	1
	.align 16
.LC3:
	.long	-1851608123
	.long	-1851608123
	.long	-1851608123
	.long	-1851608123
	.align 16
.LC4:
	.long	0
	.long	1083973632
	.long	0
	.long	1083973632
	.align 16
.LC5:
	.long	2
	.long	2
	.long	2
	.long	2
	.align 16
.LC6:
	.long	91625969
	.long	91625969
	.long	91625969
	.long	91625969
	.align 16
.LC7:
	.long	0
	.long	1083666432
	.long	0
	.long	1083666432
	.section	.rodata.cst8,"aM",@progbits,8
	.align 8
.LC8:
	.long	858993459
	.long	1072902963
	.section	.rodata.cst16
	.align 16
.LC9:
	.long	858993459
	.long	1072902963
	.long	858993459
	.long	1072902963
	.section	.rodata.cst8
	.align 8
.LC10:
	.long	0
	.long	1073217536
	.ident	"GCC: (GNU) 9.2.0"
	.section	.note.GNU-stack,"",@progbits
