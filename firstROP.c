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

	buffer[108]='\0';
	buffer[111]='\0';
	buffer[110]='\0';
	buffer[109]='\0';

	// printf("%#lx\n",*(long*)(buffer+104));
}

int main(int argc,char **argv)
{
	vulnerable_function(argv[1]);
	return 0;
}
