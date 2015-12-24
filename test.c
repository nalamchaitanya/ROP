#include <stdio.h>

char *use = "/bin/sh";
void main()
{
	system("/bin/sh");

	// system("d@");

	// char buff[8];
	// memcpy(buff,"\xdd\x05\x40\x00\x00\x00\x00\x00",8);
	// printf("%#lx\n",*((long*)buff));
}
