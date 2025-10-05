	.file	"syrk.c"
# GNU C17 (GCC) version 9.2.0 (x86_64-pc-linux-gnu)
#	compiled by GNU C version 9.2.0, GMP version 6.1.0, MPFR version 3.1.4, MPC version 1.0.3, isl version isl-0.18-GMP

# GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
# options passed:  -I utilities -I ./linear-algebra/blas/syrk
# -imultiarch x86_64-linux-gnu -D LARGE_DATASET
# ./linear-algebra/blas/syrk/syrk.c -mtune=generic -march=x86-64
# -auxbase-strip O3.s -O3 -fverbose-asm
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
	movl	%edi, 20(%rsp)	# tmp431, %sfp
# ./linear-algebra/blas/syrk/syrk.c:105:   POLYBENCH_2D_ARRAY_DECL(C,DATA_TYPE,N,N,n,n);
	movl	$3240000, %edi	#,
# ./linear-algebra/blas/syrk/syrk.c:97: {
	movq	%rsi, 40(%rsp)	# tmp432, %sfp
# ./linear-algebra/blas/syrk/syrk.c:105:   POLYBENCH_2D_ARRAY_DECL(C,DATA_TYPE,N,N,n,n);
	movl	$8, %esi	#,
	call	polybench_alloc_data	#
# ./linear-algebra/blas/syrk/syrk.c:106:   POLYBENCH_2D_ARRAY_DECL(A,DATA_TYPE,N,M,n,m);
	movl	$8, %esi	#,
	movl	$2700000, %edi	#,
# ./linear-algebra/blas/syrk/syrk.c:105:   POLYBENCH_2D_ARRAY_DECL(C,DATA_TYPE,N,N,n,n);
	movq	%rax, %r13	# tmp433, C
# ./linear-algebra/blas/syrk/syrk.c:106:   POLYBENCH_2D_ARRAY_DECL(A,DATA_TYPE,N,M,n,m);
	call	polybench_alloc_data	#
	movdqa	.LC3(%rip), %xmm2	#, tmp416
# ./linear-algebra/blas/syrk/syrk.c:36:   for (i = 0; i < n; i++)
	xorl	%edx, %edx	# i
	pxor	%xmm3, %xmm3	# tmp242
	movdqa	%xmm3, %xmm7	# tmp242, tmp246
# ./linear-algebra/blas/syrk/syrk.c:106:   POLYBENCH_2D_ARRAY_DECL(A,DATA_TYPE,N,M,n,m);
	movq	%rax, %r14	# tmp434, A
	movdqa	.LC1(%rip), %xmm6	#, tmp413
	movdqa	.LC2(%rip), %xmm10	#, tmp415
	pcmpgtd	%xmm2, %xmm7	# tmp416, tmp246
	movdqa	.LC0(%rip), %xmm5	#, vect_vec_iv_.36
	movapd	.LC4(%rip), %xmm8	#, tmp417
	.p2align 4,,10
	.p2align 3
.L2:
	movd	%edx, %xmm4	# i, i
	leaq	12000(%rax), %rcx	#, _367
	pshufd	$0, %xmm4, %xmm9	# i, vect_cst__329
# ./linear-algebra/blas/syrk/syrk.c:97: {
	movdqa	%xmm5, %xmm4	# vect_vec_iv_.36, vect_vec_iv_.47
	movdqa	%xmm9, %xmm11	# vect_cst__329, tmp424
	psrlq	$32, %xmm11	#, tmp424
	.p2align 4,,10
	.p2align 3
.L3:
	movdqa	%xmm4, %xmm1	# vect_vec_iv_.47, vect_vec_iv_.47
	movdqa	%xmm3, %xmm13	# tmp242, tmp243
	movdqa	%xmm7, %xmm12	# tmp246, tmp248
	addq	$32, %rax	#, ivtmp.150
# ./linear-algebra/blas/syrk/syrk.c:38:       A[i][j] = (DATA_TYPE) ((i*j+1)%n) / n;
	movdqa	%xmm1, %xmm0	# vect_vec_iv_.47, tmp232
	psrlq	$32, %xmm1	#, tmp234
	movdqa	%xmm7, %xmm14	# tmp246, tmp261
	pmuludq	%xmm9, %xmm0	# vect_cst__329, tmp232
	pmuludq	%xmm11, %xmm1	# tmp424, tmp233
	paddd	%xmm6, %xmm4	# tmp413, vect_vec_iv_.47
	pshufd	$8, %xmm1, %xmm1	#, tmp233, tmp231
	pshufd	$8, %xmm0, %xmm0	#, tmp232, tmp230
	punpckldq	%xmm1, %xmm0	# tmp231, vect__49.48
# ./linear-algebra/blas/syrk/syrk.c:38:       A[i][j] = (DATA_TYPE) ((i*j+1)%n) / n;
	paddd	%xmm10, %xmm0	# tmp415, vect__50.49
	movdqa	%xmm0, %xmm1	# vect__50.49, tmp239
	punpckldq	%xmm0, %xmm1	# vect__50.49, tmp239
	pcmpgtd	%xmm1, %xmm13	# tmp239, tmp243
	pmuludq	%xmm1, %xmm12	# tmp239, tmp248
	pmuludq	%xmm2, %xmm1	# tmp416, tmp249
	pmuludq	%xmm2, %xmm13	# tmp416, tmp247
	paddq	%xmm12, %xmm13	# tmp248, tmp247
	movdqa	%xmm0, %xmm12	# vect__50.49, tmp252
	psllq	$32, %xmm13	#, tmp247
	punpckhdq	%xmm0, %xmm12	# vect__50.49, tmp252
	paddq	%xmm13, %xmm1	# tmp247, tmp237
	pmuludq	%xmm12, %xmm14	# tmp252, tmp261
	movdqa	%xmm3, %xmm13	# tmp242, tmp256
	pcmpgtd	%xmm12, %xmm13	# tmp252, tmp256
	pmuludq	%xmm2, %xmm12	# tmp416, tmp262
	pmuludq	%xmm2, %xmm13	# tmp416, tmp260
	paddq	%xmm14, %xmm13	# tmp261, tmp260
	psllq	$32, %xmm13	#, tmp260
	paddq	%xmm13, %xmm12	# tmp260, tmp250
	shufps	$221, %xmm12, %xmm1	#, tmp250, vect_patt_321.50
	paddd	%xmm0, %xmm1	# vect__50.49, vect_patt_322.51
	psrad	$10, %xmm1	#, vect_patt_322.51
	movdqa	%xmm1, %xmm12	# vect_patt_322.51, vect_patt_323.52
	pslld	$3, %xmm1	#, tmp269
	psubd	%xmm12, %xmm1	# vect_patt_323.52, tmp270
	pslld	$5, %xmm1	#, tmp271
	paddd	%xmm12, %xmm1	# vect_patt_323.52, vect_patt_324.53
	pslld	$3, %xmm1	#, tmp273
	psubd	%xmm1, %xmm0	# tmp273, vect_patt_325.54
# ./linear-algebra/blas/syrk/syrk.c:38:       A[i][j] = (DATA_TYPE) ((i*j+1)%n) / n;
	cvtdq2pd	%xmm0, %xmm1	# vect_patt_325.54, vect__52.55
# ./linear-algebra/blas/syrk/syrk.c:38:       A[i][j] = (DATA_TYPE) ((i*j+1)%n) / n;
	divpd	%xmm8, %xmm1	# tmp417, vect__57.56
# ./linear-algebra/blas/syrk/syrk.c:38:       A[i][j] = (DATA_TYPE) ((i*j+1)%n) / n;
	pshufd	$238, %xmm0, %xmm0	#, vect_patt_325.54, tmp278
	cvtdq2pd	%xmm0, %xmm0	# tmp278, vect__52.55
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
	movq	%r13, %rbx	# C, ivtmp.75
	movq	%r13, %rax	# C, ivtmp.145
# ./linear-algebra/blas/syrk/syrk.c:39:   for (i = 0; i < n; i++)
	xorl	%edx, %edx	# i
	movdqa	.LC5(%rip), %xmm10	#, tmp418
	pxor	%xmm3, %xmm3	# tmp296
	movapd	.LC7(%rip), %xmm8	#, tmp420
	movdqa	%xmm3, %xmm7	# tmp296, tmp300
	pcmpgtd	%xmm2, %xmm7	# tmp419, tmp300
	.p2align 4,,10
	.p2align 3
.L6:
	movd	%edx, %xmm4	# i, i
	leaq	14400(%rax), %rcx	#, _356
	pshufd	$0, %xmm4, %xmm9	# i, vect_cst__289
	movdqa	%xmm5, %xmm4	# vect_vec_iv_.36, vect_vec_iv_.36
	movdqa	%xmm9, %xmm11	# vect_cst__289, tmp423
	psrlq	$32, %xmm11	#, tmp423
	.p2align 4,,10
	.p2align 3
.L5:
	movdqa	%xmm4, %xmm1	# vect_vec_iv_.36, vect_vec_iv_.36
	movdqa	%xmm3, %xmm12	# tmp296, tmp297
	movdqa	%xmm7, %xmm13	# tmp300, tmp302
	addq	$32, %rax	#, ivtmp.134
# ./linear-algebra/blas/syrk/syrk.c:41:       C[i][j] = (DATA_TYPE) ((i*j+2)%m) / m;
	movdqa	%xmm1, %xmm0	# vect_vec_iv_.36, tmp286
	psrlq	$32, %xmm1	#, tmp288
	movdqa	%xmm7, %xmm14	# tmp300, tmp315
	pmuludq	%xmm9, %xmm0	# vect_cst__289, tmp286
	pmuludq	%xmm11, %xmm1	# tmp423, tmp287
	paddd	%xmm6, %xmm4	# tmp413, vect_vec_iv_.36
	pshufd	$8, %xmm1, %xmm1	#, tmp287, tmp285
	pshufd	$8, %xmm0, %xmm0	#, tmp286, tmp284
	punpckldq	%xmm1, %xmm0	# tmp285, vect__62.37
# ./linear-algebra/blas/syrk/syrk.c:41:       C[i][j] = (DATA_TYPE) ((i*j+2)%m) / m;
	paddd	%xmm10, %xmm0	# tmp418, vect__63.38
	movdqa	%xmm0, %xmm1	# vect__63.38, tmp293
	punpckldq	%xmm0, %xmm1	# vect__63.38, tmp293
	pcmpgtd	%xmm1, %xmm12	# tmp293, tmp297
	pmuludq	%xmm1, %xmm13	# tmp293, tmp302
	pmuludq	%xmm2, %xmm1	# tmp419, tmp303
	pmuludq	%xmm2, %xmm12	# tmp419, tmp301
	paddq	%xmm13, %xmm12	# tmp302, tmp301
	movdqa	%xmm3, %xmm13	# tmp296, tmp310
	psllq	$32, %xmm12	#, tmp301
	paddq	%xmm12, %xmm1	# tmp301, tmp291
	movdqa	%xmm0, %xmm12	# vect__63.38, tmp306
	punpckhdq	%xmm0, %xmm12	# vect__63.38, tmp306
	pcmpgtd	%xmm12, %xmm13	# tmp306, tmp310
	pmuludq	%xmm12, %xmm14	# tmp306, tmp315
	pmuludq	%xmm2, %xmm12	# tmp419, tmp316
	pmuludq	%xmm2, %xmm13	# tmp419, tmp314
	paddq	%xmm14, %xmm13	# tmp315, tmp314
	psllq	$32, %xmm13	#, tmp314
	paddq	%xmm13, %xmm12	# tmp314, tmp304
	shufps	$221, %xmm12, %xmm1	#, tmp304, vect_patt_282.39
	psrad	$5, %xmm1	#, vect_patt_283.40
	movdqa	%xmm1, %xmm12	# vect_patt_283.40, tmp322
	pslld	$1, %xmm12	#, tmp322
	paddd	%xmm1, %xmm12	# vect_patt_283.40, tmp323
	pslld	$4, %xmm12	#, tmp324
	psubd	%xmm1, %xmm12	# vect_patt_283.40, tmp325
	pslld	$3, %xmm12	#, tmp326
	psubd	%xmm1, %xmm12	# vect_patt_283.40, tmp326
	movdqa	%xmm12, %xmm1	# tmp326, vect_patt_284.41
	pslld	$2, %xmm1	#, tmp328
	psubd	%xmm1, %xmm0	# tmp328, vect_patt_285.42
# ./linear-algebra/blas/syrk/syrk.c:41:       C[i][j] = (DATA_TYPE) ((i*j+2)%m) / m;
	cvtdq2pd	%xmm0, %xmm1	# vect_patt_285.42, vect__65.43
# ./linear-algebra/blas/syrk/syrk.c:41:       C[i][j] = (DATA_TYPE) ((i*j+2)%m) / m;
	divpd	%xmm8, %xmm1	# tmp420, vect__70.44
# ./linear-algebra/blas/syrk/syrk.c:41:       C[i][j] = (DATA_TYPE) ((i*j+2)%m) / m;
	pshufd	$238, %xmm0, %xmm0	#, vect_patt_285.42, tmp333
	cvtdq2pd	%xmm0, %xmm0	# tmp333, vect__65.43
# ./linear-algebra/blas/syrk/syrk.c:41:       C[i][j] = (DATA_TYPE) ((i*j+2)%m) / m;
	divpd	%xmm8, %xmm0	# tmp420, vect__70.44
# ./linear-algebra/blas/syrk/syrk.c:41:       C[i][j] = (DATA_TYPE) ((i*j+2)%m) / m;
	movups	%xmm1, -32(%rax)	# vect__70.44, MEM[base: _277, offset: 0B]
	movups	%xmm0, -16(%rax)	# vect__70.44, MEM[base: _277, offset: 16B]
	cmpq	%rcx, %rax	# _356, ivtmp.134
	jne	.L5	#,
# ./linear-algebra/blas/syrk/syrk.c:39:   for (i = 0; i < n; i++)
	addl	$1, %edx	#, i
# ./linear-algebra/blas/syrk/syrk.c:39:   for (i = 0; i < n; i++)
	cmpl	$1800, %edx	#, i
	jne	.L6	#,
	leaq	8(%r13), %rsi	#, ivtmp.121
	movq	%rbx, 32(%rsp)	# ivtmp.75, %sfp
	movq	%r14, %rdi	# A, ivtmp.120
	movq	%r13, %rax	# C, ivtmp.119
	movsd	.LC10(%rip), %xmm1	#, tmp422
	movl	$1, %r15d	#, ivtmp.127
	xorl	%r11d, %r11d	# ivtmp.114
	movq	%rsi, %rbx	# ivtmp.121, ivtmp.121
	movapd	.LC9(%rip), %xmm4	#, tmp428
# ./linear-algebra/blas/syrk/syrk.c:85:       C[i][j] *= beta;
	movsd	.LC8(%rip), %xmm3	#, tmp429
	.p2align 4,,10
	.p2align 3
.L7:
	movl	%r15d, %esi	# ivtmp.127, _320
	testq	%r11, %r11	# ivtmp.114
	je	.L30	#,
	movl	%r15d, %edx	# ivtmp.127, bnd.27
	movq	%rax, %rcx	# ivtmp.119, ivtmp.109
	shrl	%edx	#
	salq	$4, %rdx	#, tmp392
	addq	%rax, %rdx	# ivtmp.119, _41
	.p2align 4,,10
	.p2align 3
.L9:
	movupd	(%rcx), %xmm0	# MEM[base: _37, offset: 0B], vect__26.33
	addq	$16, %rcx	#, ivtmp.109
	mulpd	%xmm4, %xmm0	# tmp428, vect__26.33
	movups	%xmm0, -16(%rcx)	# vect__26.33, MEM[base: _37, offset: 0B]
	cmpq	%rdx, %rcx	# _41, ivtmp.109
	jne	.L9	#,
	movl	%esi, %edx	# _320, tmp.29
	andl	$-2, %edx	#, tmp.29
	testb	$1, %sil	#, _320
	je	.L8	#,
.L21:
	movslq	%edx, %rdx	# tmp.29, tmp.29
	leaq	(%rax,%rdx,8), %rdx	#, _93
	movsd	(%rdx), %xmm0	# MEM[(double[1800] *)_93], tmp339
	mulsd	%xmm3, %xmm0	# tmp429, tmp339
	movsd	%xmm0, (%rdx)	# tmp339, MEM[(double[1800] *)_93]
.L8:
	movl	%esi, %edx	# _320, bnd.15
	movq	%r15, %r9	# ivtmp.127, tmp345
	leaq	8(%rdi), %r8	#, ivtmp.99
	shrl	%edx	#
	subq	%r11, %r9	# ivtmp.114, tmp345
	salq	$4, %rdx	#, tmp348
	imulq	$12000, %r9, %r9	#, tmp345, _69
	leaq	(%rdx,%rax), %rcx	#, _214
	movq	%rcx, 8(%rsp)	# _214, %sfp
	movl	%esi, %ecx	# _320, niters_vector_mult_vf.16
	andl	$-2, %ecx	#,
	leaq	-12000(%r9), %r10	#, tmp425
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	imulq	$12000, %rcx, %rdx	#, _201, tmp349
	movl	%ecx, 16(%rsp)	# niters_vector_mult_vf.16, %sfp
	leaq	(%rax,%rcx,8), %rbp	#, _113
	movq	%r10, 24(%rsp)	# tmp425, %sfp
	addq	%r14, %rdx	# A, _203
	movq	%rdx, (%rsp)	# _203, %sfp
	xorl	%edx, %edx	# ivtmp.94
	.p2align 4,,10
	.p2align 3
.L11:
	leaq	-8(%r8), %r9	#, tmp374
	movslq	%edx, %r10	# ivtmp.94,
	leaq	(%r14,%rdx,8), %rcx	#, ivtmp.88
	cmpq	%r9, %rbx	# tmp374, ivtmp.121
	setbe	%r9b	#, tmp376
	cmpq	%r8, %rax	# ivtmp.99, ivtmp.119
	setnb	%r12b	#, tmp378
	orl	%r12d, %r9d	# tmp378, tmp379
	cmpl	$1, %r11d	#, ivtmp.114
	seta	%r12b	#, tmp381
	testb	%r12b, %r9b	# tmp381, tmp379
	je	.L31	#,
	movq	24(%rsp), %r9	# %sfp, tmp425
	addq	%r8, %r9	# ivtmp.99, tmp384
	cmpq	%r9, %rax	# tmp384, ivtmp.119
	setnb	%r12b	#, tmp386
	cmpq	%rcx, %rbx	# ivtmp.88, ivtmp.121
	setbe	%r9b	#, tmp388
	orb	%r9b, %r12b	# tmp388, tmp386
	je	.L31	#,
	movsd	(%rdi,%rdx,8), %xmm2	# MEM[base: _34, index: ivtmp.94_224, step: 8, offset: 0B], _139
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	movq	%rax, %r9	# ivtmp.119, ivtmp.85
	mulsd	%xmm1, %xmm2	# tmp422, _139
	unpcklpd	%xmm2, %xmm2	# vect__37.21
.L15:
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	movsd	(%rcx), %xmm0	# MEM[base: _194, offset: 0B], MEM[base: _194, offset: 0B]
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	movupd	(%r9), %xmm5	# MEM[base: _167, offset: 0B], tmp545
	addq	$24000, %rcx	#, ivtmp.88
	addq	$16, %r9	#, ivtmp.85
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	movhpd	-12000(%rcx), %xmm0	# MEM[base: _194, offset: 12000B], tmp367
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	mulpd	%xmm2, %xmm0	# vect__37.21, vect__42.22
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	addpd	%xmm5, %xmm0	# tmp545, vect__43.23
	movups	%xmm0, -16(%r9)	# vect__43.23, MEM[base: _167, offset: 0B]
	cmpq	8(%rsp), %r9	# %sfp, ivtmp.85
	jne	.L15	#,
	cmpl	%esi, 16(%rsp)	# _320, %sfp
	je	.L14	#,
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	movsd	(%rdi,%rdx,8), %xmm0	# MEM[base: _34, index: ivtmp.94_224, step: 8, offset: 0B], tmp351
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	movq	(%rsp), %rcx	# %sfp, _203
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	mulsd	%xmm1, %xmm0	# tmp422, tmp351
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	mulsd	(%rcx,%r10,8), %xmm0	# *_203, tmp355
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	addsd	0(%rbp), %xmm0	# MEM[(double[1800] *)_113], tmp356
	movsd	%xmm0, 0(%rbp)	# tmp356, MEM[(double[1800] *)_113]
.L14:
	addq	$1, %rdx	#, ivtmp.94
	addq	$8, %r8	#, ivtmp.99
# ./linear-algebra/blas/syrk/syrk.c:86:     for (k = 0; k < _PB_M; k++) {
	cmpq	$1500, %rdx	#, ivtmp.94
	jne	.L11	#,
	addq	$1, %r11	#, ivtmp.114
	addq	$14400, %rax	#, ivtmp.119
	addq	$1, %r15	#, ivtmp.127
	addq	$12000, %rdi	#, ivtmp.120
	addq	$14408, %rbx	#, ivtmp.121
# ./linear-algebra/blas/syrk/syrk.c:83:   for (i = 0; i < _PB_N; i++) {
	cmpq	$1800, %r11	#, ivtmp.114
	jne	.L7	#,
# ./linear-algebra/blas/syrk/syrk.c:123:   polybench_prevent_dce(print_array(n, POLYBENCH_ARRAY(C)));
	cmpl	$42, 20(%rsp)	#, %sfp
	movq	32(%rsp), %rbx	# %sfp, ivtmp.75
	jle	.L22	#,
# ./linear-algebra/blas/syrk/syrk.c:123:   polybench_prevent_dce(print_array(n, POLYBENCH_ARRAY(C)));
	movq	40(%rsp), %rax	# %sfp, argv
	movq	(%rax), %rax	# *argv_13(D), *argv_13(D)
	cmpb	$0, (%rax)	#, MEM[(const unsigned char * {ref-all})_3]
	je	.L46	#,
.L22:
# ./linear-algebra/blas/syrk/syrk.c:126:   POLYBENCH_FREE_ARRAY(C);
	movq	%r13, %rdi	# C,
	call	free	#
# ./linear-algebra/blas/syrk/syrk.c:127:   POLYBENCH_FREE_ARRAY(A);
	movq	%r14, %rdi	# A,
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
# ./linear-algebra/blas/syrk/syrk.c:85:       C[i][j] *= beta;
	movq	%rax, %r9	# ivtmp.119, ivtmp.80
.L13:
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	movsd	(%rdi,%rdx,8), %xmm0	# MEM[base: _34, index: ivtmp.94_224, step: 8, offset: 0B], tmp358
	addq	$8, %r9	#, ivtmp.80
	addq	$12000, %rcx	#, ivtmp.88
	mulsd	%xmm1, %xmm0	# tmp422, tmp358
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	mulsd	-12000(%rcx), %xmm0	# MEM[base: _15, offset: 0B], tmp361
# ./linear-algebra/blas/syrk/syrk.c:88:         C[i][j] += alpha * A[i][k] * A[j][k];
	addsd	-8(%r9), %xmm0	# MEM[base: _35, offset: 0B], tmp362
	movsd	%xmm0, -8(%r9)	# tmp362, MEM[base: _35, offset: 0B]
# ./linear-algebra/blas/syrk/syrk.c:87:       for (j = 0; j <= i; j++)
	cmpq	%rbx, %r9	# ivtmp.121, ivtmp.80
	je	.L14	#,
	jmp	.L13	#
	.p2align 4,,10
	.p2align 3
.L30:
# ./linear-algebra/blas/syrk/syrk.c:84:     for (j = 0; j <= i; j++)
	xorl	%edx, %edx	# tmp.29
	jmp	.L21	#
.L46:
# ./linear-algebra/blas/syrk/syrk.c:53:   POLYBENCH_DUMP_START;
	movq	stderr(%rip), %rcx	# stderr,
	movl	$22, %edx	#,
	movl	$1, %esi	#,
# ./linear-algebra/blas/syrk/syrk.c:54:   POLYBENCH_DUMP_BEGIN("C");
	xorl	%r12d, %r12d	# ivtmp.76
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
	xorl	%ebp, %ebp	# ivtmp.61
	jmp	.L28	#
	.p2align 4,,10
	.p2align 3
.L24:
# ./linear-algebra/blas/syrk/syrk.c:58: 	fprintf (POLYBENCH_DUMP_TARGET, DATA_PRINTF_MODIFIER, C[i][j]);
	movsd	(%rbx,%rbp,8), %xmm0	# MEM[base: _83, index: ivtmp.61_248, step: 8, offset: 0B], MEM[base: _83, index: ivtmp.61_248, step: 8, offset: 0B]
	movl	$.LC14, %esi	#,
.L44:
	movl	$1, %eax	#,
	addq	$1, %rbp	#, ivtmp.61
	call	fprintf	#
# ./linear-algebra/blas/syrk/syrk.c:56:     for (j = 0; j < n; j++) {
	cmpq	$1800, %rbp	#, ivtmp.61
	je	.L47	#,
.L28:
	leal	(%r12,%rbp), %eax	#, tmp394
	movq	stderr(%rip), %rdi	# stderr, pretmp_189
	imull	$-858993459, %eax, %eax	#, tmp394, tmp406
	rorl	$2, %eax	#, tmp407
# ./linear-algebra/blas/syrk/syrk.c:57: 	if ((i * n + j) % 20 == 0) fprintf (POLYBENCH_DUMP_TARGET, "\n");
	cmpl	$214748364, %eax	#, tmp407
	ja	.L24	#,
# ./linear-algebra/blas/syrk/syrk.c:57: 	if ((i * n + j) % 20 == 0) fprintf (POLYBENCH_DUMP_TARGET, "\n");
	movq	%rdi, %rsi	# pretmp_189,
	movl	$10, %edi	#,
	call	fputc	#
# ./linear-algebra/blas/syrk/syrk.c:58: 	fprintf (POLYBENCH_DUMP_TARGET, DATA_PRINTF_MODIFIER, C[i][j]);
	movsd	(%rbx,%rbp,8), %xmm0	# MEM[base: _83, index: ivtmp.61_248, step: 8, offset: 0B], MEM[base: _83, index: ivtmp.61_248, step: 8, offset: 0B]
	movl	$.LC14, %esi	#,
	movq	stderr(%rip), %rdi	# stderr,
	jmp	.L44	#
	.p2align 4,,10
	.p2align 3
.L47:
	addl	$1800, %r12d	#, ivtmp.76
	addq	$14400, %rbx	#, ivtmp.75
# ./linear-algebra/blas/syrk/syrk.c:55:   for (i = 0; i < n; i++)
	cmpl	$3240000, %r12d	#, ivtmp.76
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
