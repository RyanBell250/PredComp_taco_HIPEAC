	.file	"crc_32.c"
	.text
	.globl	updateCRC32
	.type	updateCRC32, @function
updateCRC32:
.LFB22:
	.cfi_startproc
	xorl	%esi, %edi
	movzbl	%dil, %edi
	shrq	$8, %rsi
	movq	%rsi, %rax
	xorq	crc_32_tab(,%rdi,8), %rax
	ret
	.cfi_endproc
.LFE22:
	.size	updateCRC32, .-updateCRC32
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"r"
	.text
	.globl	crc32file
	.type	crc32file, @function
crc32file:
.LFB23:
	.cfi_startproc
	pushq	%r14
	.cfi_def_cfa_offset 16
	.cfi_offset 14, -16
	pushq	%r13
	.cfi_def_cfa_offset 24
	.cfi_offset 13, -24
	pushq	%r12
	.cfi_def_cfa_offset 32
	.cfi_offset 12, -32
	pushq	%rbp
	.cfi_def_cfa_offset 40
	.cfi_offset 6, -40
	pushq	%rbx
	.cfi_def_cfa_offset 48
	.cfi_offset 3, -48
	movq	%rdi, %r13
	movq	%rsi, %r14
	movq	%rdx, %rbp
	movq	$0, (%rdx)
	movl	$.LC0, %esi
	call	fopen
	testq	%rax, %rax
	je	.L9
	movq	%rax, %r12
	movl	$4294967295, %ebx
	jmp	.L3
.L9:
	movq	%r13, %rdi
	call	perror
	movl	$-1, %eax
	jmp	.L2
.L5:
	addq	$1, 0(%rbp)
	xorl	%ebx, %eax
	movzbl	%al, %eax
	shrq	$8, %rbx
	xorq	crc_32_tab(,%rax,8), %rbx
.L3:
	movq	%r12, %rdi
	call	getc
	cmpl	$-1, %eax
	jne	.L5
	movq	%r12, %rdi
	call	ferror
	testl	%eax, %eax
	jne	.L10
.L6:
	movq	%r12, %rdi
	call	fclose
	notq	%rbx
	movq	%rbx, (%r14)
	movl	$0, %eax
.L2:
	popq	%rbx
	.cfi_remember_state
	.cfi_def_cfa_offset 40
	popq	%rbp
	.cfi_def_cfa_offset 32
	popq	%r12
	.cfi_def_cfa_offset 24
	popq	%r13
	.cfi_def_cfa_offset 16
	popq	%r14
	.cfi_def_cfa_offset 8
	ret
.L10:
	.cfi_restore_state
	movq	%r13, %rdi
	call	perror
	movq	$-1, 0(%rbp)
	jmp	.L6
	.cfi_endproc
.LFE23:
	.size	crc32file, .-crc32file
	.globl	crc32buf
	.type	crc32buf, @function
crc32buf:
.LFB24:
	.cfi_startproc
	movl	$4294967295, %eax
	testq	%rsi, %rsi
	je	.L12
	addq	%rdi, %rsi
.L13:
	movl	%eax, %edx
	xorb	(%rdi), %dl
	movzbl	%dl, %edx
	shrq	$8, %rax
	xorq	crc_32_tab(,%rdx,8), %rax
	addq	$1, %rdi
	cmpq	%rdi, %rsi
	jne	.L13
.L12:
	notq	%rax
	ret
	.cfi_endproc
.LFE24:
	.size	crc32buf, .-crc32buf
	.section	.rodata.str1.1
.LC1:
	.string	"%08lX %7ld %s\n"
	.text
	.globl	main1
	.type	main1, @function
main1:
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
	subq	$24, %rsp
	.cfi_def_cfa_offset 64
	cmpl	$1, %edi
	jle	.L20
	movq	%rsi, %rbx
	movl	%edx, %r12d
	leal	-2(%rdi), %eax
	leaq	8(%rsi,%rax,8), %r13
	movl	$0, %ebp
	jmp	.L19
.L23:
	movq	(%rbx), %rcx
	movq	(%rsp), %rdx
	movq	8(%rsp), %rsi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	printf
.L18:
	cmpq	%rbx, %r13
	je	.L17
.L19:
	addq	$8, %rbx
	movq	%rsp, %rdx
	leaq	8(%rsp), %rsi
	movq	(%rbx), %rdi
	call	crc32file
	orl	%eax, %ebp
	testl	%r12d, %r12d
	je	.L18
	jmp	.L23
.L20:
	movl	$0, %ebp
.L17:
	testl	%ebp, %ebp
	setne	%al
	movzbl	%al, %eax
	addq	$24, %rsp
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
	.cfi_endproc
.LFE25:
	.size	main1, .-main1
	.section	.rodata
	.align 32
	.type	crc_32_tab, @object
	.size	crc_32_tab, 2048
crc_32_tab:
	.quad	0
	.quad	1996959894
	.quad	3993919788
	.quad	2567524794
	.quad	124634137
	.quad	1886057615
	.quad	3915621685
	.quad	2657392035
	.quad	249268274
	.quad	2044508324
	.quad	3772115230
	.quad	2547177864
	.quad	162941995
	.quad	2125561021
	.quad	3887607047
	.quad	2428444049
	.quad	498536548
	.quad	1789927666
	.quad	4089016648
	.quad	2227061214
	.quad	450548861
	.quad	1843258603
	.quad	4107580753
	.quad	2211677639
	.quad	325883990
	.quad	1684777152
	.quad	4251122042
	.quad	2321926636
	.quad	335633487
	.quad	1661365465
	.quad	4195302755
	.quad	2366115317
	.quad	997073096
	.quad	1281953886
	.quad	3579855332
	.quad	2724688242
	.quad	1006888145
	.quad	1258607687
	.quad	3524101629
	.quad	2768942443
	.quad	901097722
	.quad	1119000684
	.quad	3686517206
	.quad	2898065728
	.quad	853044451
	.quad	1172266101
	.quad	3705015759
	.quad	2882616665
	.quad	651767980
	.quad	1373503546
	.quad	3369554304
	.quad	3218104598
	.quad	565507253
	.quad	1454621731
	.quad	3485111705
	.quad	3099436303
	.quad	671266974
	.quad	1594198024
	.quad	3322730930
	.quad	2970347812
	.quad	795835527
	.quad	1483230225
	.quad	3244367275
	.quad	3060149565
	.quad	1994146192
	.quad	31158534
	.quad	2563907772
	.quad	4023717930
	.quad	1907459465
	.quad	112637215
	.quad	2680153253
	.quad	3904427059
	.quad	2013776290
	.quad	251722036
	.quad	2517215374
	.quad	3775830040
	.quad	2137656763
	.quad	141376813
	.quad	2439277719
	.quad	3865271297
	.quad	1802195444
	.quad	476864866
	.quad	2238001368
	.quad	4066508878
	.quad	1812370925
	.quad	453092731
	.quad	2181625025
	.quad	4111451223
	.quad	1706088902
	.quad	314042704
	.quad	2344532202
	.quad	4240017532
	.quad	1658658271
	.quad	366619977
	.quad	2362670323
	.quad	4224994405
	.quad	1303535960
	.quad	984961486
	.quad	2747007092
	.quad	3569037538
	.quad	1256170817
	.quad	1037604311
	.quad	2765210733
	.quad	3554079995
	.quad	1131014506
	.quad	879679996
	.quad	2909243462
	.quad	3663771856
	.quad	1141124467
	.quad	855842277
	.quad	2852801631
	.quad	3708648649
	.quad	1342533948
	.quad	654459306
	.quad	3188396048
	.quad	3373015174
	.quad	1466479909
	.quad	544179635
	.quad	3110523913
	.quad	3462522015
	.quad	1591671054
	.quad	702138776
	.quad	2966460450
	.quad	3352799412
	.quad	1504918807
	.quad	783551873
	.quad	3082640443
	.quad	3233442989
	.quad	3988292384
	.quad	2596254646
	.quad	62317068
	.quad	1957810842
	.quad	3939845945
	.quad	2647816111
	.quad	81470997
	.quad	1943803523
	.quad	3814918930
	.quad	2489596804
	.quad	225274430
	.quad	2053790376
	.quad	3826175755
	.quad	2466906013
	.quad	167816743
	.quad	2097651377
	.quad	4027552580
	.quad	2265490386
	.quad	503444072
	.quad	1762050814
	.quad	4150417245
	.quad	2154129355
	.quad	426522225
	.quad	1852507879
	.quad	4275313526
	.quad	2312317920
	.quad	282753626
	.quad	1742555852
	.quad	4189708143
	.quad	2394877945
	.quad	397917763
	.quad	1622183637
	.quad	3604390888
	.quad	2714866558
	.quad	953729732
	.quad	1340076626
	.quad	3518719985
	.quad	2797360999
	.quad	1068828381
	.quad	1219638859
	.quad	3624741850
	.quad	2936675148
	.quad	906185462
	.quad	1090812512
	.quad	3747672003
	.quad	2825379669
	.quad	829329135
	.quad	1181335161
	.quad	3412177804
	.quad	3160834842
	.quad	628085408
	.quad	1382605366
	.quad	3423369109
	.quad	3138078467
	.quad	570562233
	.quad	1426400815
	.quad	3317316542
	.quad	2998733608
	.quad	733239954
	.quad	1555261956
	.quad	3268935591
	.quad	3050360625
	.quad	752459403
	.quad	1541320221
	.quad	2607071920
	.quad	3965973030
	.quad	1969922972
	.quad	40735498
	.quad	2617837225
	.quad	3943577151
	.quad	1913087877
	.quad	83908371
	.quad	2512341634
	.quad	3803740692
	.quad	2075208622
	.quad	213261112
	.quad	2463272603
	.quad	3855990285
	.quad	2094854071
	.quad	198958881
	.quad	2262029012
	.quad	4057260610
	.quad	1759359992
	.quad	534414190
	.quad	2176718541
	.quad	4139329115
	.quad	1873836001
	.quad	414664567
	.quad	2282248934
	.quad	4279200368
	.quad	1711684554
	.quad	285281116
	.quad	2405801727
	.quad	4167216745
	.quad	1634467795
	.quad	376229701
	.quad	2685067896
	.quad	3608007406
	.quad	1308918612
	.quad	956543938
	.quad	2808555105
	.quad	3495958263
	.quad	1231636301
	.quad	1047427035
	.quad	2932959818
	.quad	3654703836
	.quad	1088359270
	.quad	936918000
	.quad	2847714899
	.quad	3736837829
	.quad	1202900863
	.quad	817233897
	.quad	3183342108
	.quad	3401237130
	.quad	1404277552
	.quad	615818150
	.quad	3134207493
	.quad	3453421203
	.quad	1423857449
	.quad	601450431
	.quad	3009837614
	.quad	3294710456
	.quad	1567103746
	.quad	711928724
	.quad	3020668471
	.quad	3272380065
	.quad	1510334235
	.quad	755167117
	.ident	"GCC: (GNU) 9.2.0"
	.section	.note.GNU-stack,"",@progbits
