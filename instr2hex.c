#include <stdio.h>

int main()
{
	asm
	(
		"mov %rsi, (%rdi);"
		"pop %rcx;"
		"pop %rax;"
		"retq;"
	);
}
