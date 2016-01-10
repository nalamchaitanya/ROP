/**
 * Author: Nalam V S S Krishna Chaitanya,
 * Details: CS13B021, IIT Madras.
 */

#include <stdio.h>
#include <sys/mman.h>	// System Library for memory management.

// Shellcode to be executed.

char shellcode2[] =
"\xeb\x27\x5b\x48\x89\x5b\x08\x48\x31\xc0\x88\x63\x07\x48\x89\x43\x10\x89\xc2"
"\xb0\x3b\x48\x8b\x7b\x08\x48\x8d\x73\x08\x0f\x05\x48\x31\xc9\x48\x89\xcf\xb0"
"\x3c\x0f\x05\xe8\xd4\xff\xff\xff\x2f\x62\x69\x6e\x2f\x73\x68\x20\x20\x20\x20"
"\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20";

/**
 * This file demonstrates how to change the permissions of the data segment
 * using a function called mprotect.
 */

int main()
{
	// Getting the address of the Shellcode and rounding it off to a page.

	unsigned long addr = (unsigned long)shellcode2 & 0xfffffffffffff000;

	// addr is the rounded off address that consists the shellcode. The length
	// of the memory to change the permissions is 2 pages. Giving the execute
	// and write permissions to the segment.

	mprotect((void*)addr,2*0x1000,PROT_EXEC|PROT_WRITE);

	// Decalaring a void function pointer and setting its address to the
	// shellcode and call the function which then executes the shellcode.

	void (*funcptr)();
	funcptr = shellcode2;
	(*funcptr)();
}
