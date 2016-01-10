/**
 * Author: Nalam V S S Krishna Chaitanya,
 * Details: CS13B021, IIT Madras.
 */

#include <stdio.h>

/**
 * This file just used to convert the instructions to hex code format by
 * disassembling and by finding the pattern in executable. The addresses beside
 * instructions are the place where we find them along with retq. jmp *%rax
 * need not end with retq as our code may have it.
 */

int main()
{
	asm
	(
		"mov %rsi, (%rdi);"
		"pop %rcx;"				// 0x00007ffff7b27ecf
		"pop %rax;"				// 0x00007ffff7a5d858
		"pop %rdx;"				// 0x00007ffff7ad1ee0
		"mov 48(%rax), %rax;"	// 0x00007ffff7b1ca6f
		"pop %rdi;"				// 0x00007ffff7a5bfe8
		"pop %rsi;"				// 0x00007ffff7a6884d
		"call mprotect;"
		"jmp *%rax;"			// 0x00007ffff7bbd8b3
		"retq;"
	);
}
