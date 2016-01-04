	.file	"rop2.c"
	.comm	rop,4,4
	.text
	.globl	get_rdx
	.type	get_rdx, @function
get_rdx:
.LFB2:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
#APP
# 9 "rop2.c" 1
	mov %rdx, %rax;
# 0 "" 2
#NO_APP
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	get_rdx, .-get_rdx
	.globl	main
	.type	main, @function
main:
.LFB3:
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
	movl	$5, rop(%rip)
	movq	-48(%rbp), %rax
	addq	$8, %rax
	movq	(%rax), %rcx
	leaq	-32(%rbp), %rax
	movl	$56, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	memcpy
	leaq	-32(%rbp), %rax
	addq	$30, %rax
	movl	$2, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	memset
	leaq	-32(%rbp), %rax
	addq	$35, %rax
	movl	$5, %edx
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
	addq	$51, %rax
	movl	$5, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	memset
	movq	-24(%rbp), %rbx
	xorq	%fs:40, %rbx
	je	.L3
	call	__stack_chk_fail
.L3:
	addq	$40, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3:
	.size	main, .-main
	.section	.rodata
.LC0:
	.string	"rax is %#lx\n"
	.text
	.globl	test
	.type	test, @function
test:
.LFB4:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
#APP
# 26 "rop2.c" 1
	mov %rax, %rdx;
# 0 "" 2
#NO_APP
	movl	$0, %eax
	call	get_rdx
	movq	%rax, %rsi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	movl	$0, %edi
	call	exit
	.cfi_endproc
.LFE4:
	.size	test, .-test
	.ident	"GCC: (Ubuntu 4.8.4-2ubuntu1~14.04) 4.8.4"
	.section	.note.GNU-stack,"",@progbits
