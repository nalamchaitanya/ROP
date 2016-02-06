#Return Oriented Programming(ROP)

##Introduction:

This project is based on [Introduction to Return Oriented Programming](http://codearcana.com/posts/2013/05/28/introduction-to-return-oriented-programming-rop.html) and [The Geometry of Innocent Flesh on the Bone:Return-into-libc without Function Calls](https://cseweb.ucsd.edu/~hovav/dist/geometry.pdf).

>What is Return Oriented Programming?

In our previous project of [Buffer OverFlow Attack](../BOFA) we have made the shellcode(which executes the shell) and overflowed the buffer with it and got a shell. This is done by injecting the code (shellcode) into the buffer and by giving it the permission to execute. However this is not possible because of the constraint **W xor X** which makes the memory either executable or writable but not both. There by making our injected code not to execute.

We circumvent this constraint by using the code that is already present in code segment of the executable and chaining them together by series of return instructions to execute the code we want. We call the small parts (generally one or two instructions) of the code segment ending with the ```retq``` instruction as **gadgets**. In the [Geometry Paper](https://cseweb.ucsd.edu/~hovav/dist/geometry.pdf) it is said that

>**In any sufficiently large body of x86 executable code there will exist sufficiently many useful code sequences (gadgets) that an attacker who controls the stack will be able to undertake any arbitrary computation.**

This attack works mainly on the ```retq``` instruction which pops one quad word from the stack and moves that value to ```%rip```. It is similar to the instruction ```pop %rip``` so that the next instruction executes from that point. We use this extensively for chaining the gadgets, so the name **Return Oriented Programming**.

The main difference between **Return to lib-c attack** and **Return Oriented Programming** is that the former one executes a whole function in the c library and then returns to another function i.e it chains function together however the later one chains gadgets together there by gaining more control over the execution.

**In this project we will do the Return Oriented Programming attacks inside the gdb as it disables the ASLR(Address Space Layout Randomization), which is done for an executable to keep the address space of the lib-c change randomly.**

##Requirements:

 You have to be familiar with how a stack functions and some facts about how the function calls are organized using stack. Stacks can be top-down or bottom-up based on the direction of growth of the stack after a push operation. If the rsp value is decreased it means stack is growing downward implies that it is a top-down stack and in the same way if the rsp value is increased then it is growing upward implies that it is a bottom-up stack.

 In this project I used **AT&T** syntax for assembly code which you can get familiarised using [Brennan's Guide to Inline Assembly](http://www.delorie.com/djgpp/doc/brennan/brennan_att_inline_djgpp.html). Basic Inline Assembly is enough as far as this project is concerned.

 We should be adding the gcc option ```-fno-stack-protector``` to prevent any canaries added to the functions.

 You should also be familiar with ```gdb``` as we will be using it throughout the project.

##SourceCode:

The main goal of the project is to give executable permissions to the data segment of the program, which contains the [shellcode](https://github.com/nvsskchaitanya/BOFA#shellcodec) and then execute the shellcode to get the shell. We will do it step by step through the files.

The main problem of the 64-bit addressing is that it has a lot of NULL bytes in its address example ```0x000000000040602d``` which makes it hard to tailor the string which overflows the buffer as these NULL bytes terminate the string. For this reason I always put spaces ```0x20``` instead of NULL bytes so that in the program I will replace it with NULL bytes using memset.

###[firstROP.c](./firstROP.c)

This file is to demonstrate how to change return address of the function by overflowing the buffer and executing a function which is not at all called.

###[callARG.c](./callARG.c)
The point to note is that arguments are kept in registers while calling functions and not on stack. So we can't change the arguments of a function by modifying stack. So the Calling Arguments section in this [paper](http://codearcana.com/posts/2013/05/28/introduction-to-return-oriented-programming-rop.html) is not implemented.

Now that we can change the return addresses of the function it's time to find gadgets and execute the instructions. But wait what instructions should we find, what is our final goal? The answer is [above](https://github.com/nvsskchaitanya/ROP#sourcecode). So how do we executable permissions to data segment?

###[mprotect.c](./mprotect.c),[mprotect.s](./mprotect.s)

This file demonstrates how to change the permissions of the data segment using a function called mprotect. Use man pages for more information. From the mprotect.s file we can see the arguments passed to mprotect via registers. We have to find the gadgets and chain them such that we have to execute this mprotect function and then execute the shellcode. We will do this step by step.

>**How do we find whether a sequence of instructions exists?**

The solution lies in gdb. There exists a gdb utility [find](https://sourceware.org/gdb/onlinedocs/gdb/Searching-Memory.html) which helps to search the memory for certain byte sequences. Use ```help find``` in gdb for more information. First we have to find the byte code sequences for corresponding instructions and then search for them in the binary.

We use [instr2hex.c](./instr2hex.c) to find the Hex Code for the x86 instructions. We write the instructions in the asm block and disassemble the compiled file for the raw code with [/r flag](https://sourceware.org/gdb/onlinedocs/gdb/Machine-Code.html). We then search for the raw code (Hex Code) in the executable using the appropriate flags and length to be searched. We generally put the length to search as large as possible as we don't know exact ending of code segment. I take the address of the function *system* as start address.

Here is an example for you. Remember that whatever instruction sequences we search for they must end with ```retq``` instruction. Now we search for ```pop %rdx``` ending with ```retq``` instruction. Let's disassemble the compiled file. We have to find the code sequences during the runtime as that is the time when the libraries are loaded. So we keep a breakpoint and run the program. And at the breakpoint we disassemble the main function in instr2hex.c with /r flag. From the disassembly we found out that the code to search for is ```0xc35a``` because of the [little endian format](https://en.wikipedia.org/wiki/Endianness).

```
$ gdb -q ./instr2hex
Reading symbols from ./instr2hex...done.
(gdb) b 5
Breakpoint 1 at 0x400541: file instr2hex.c, line 5.
(gdb) r
Starting program: /home/nalamchaitanya/rop/instr2hex

Breakpoint 1, main () at instr2hex.c:5
5		asm
(gdb) disas /r main
Dump of assembler code for function main:
   0x000000000040053d <+0>:	55	push   %rbp
   0x000000000040053e <+1>:	48 89 e5	mov    %rsp,%rbp
=> 0x0000000000400541 <+4>:	48 89 37	mov    %rsi,(%rdi)
   0x0000000000400544 <+7>:	59	pop    %rcx
   0x0000000000400545 <+8>:	58	pop    %rax
   0x0000000000400546 <+9>:	55	push   %rbp
   0x0000000000400547 <+10>:	5c	pop    %rsp
   0x0000000000400548 <+11>:	5a	pop    %rdx                     <------ "pop %rdx = 0x5a"
   0x0000000000400549 <+12>:	48 8b 40 30	mov    0x30(%rax),%rax
   0x000000000040054d <+16>:	5f	pop    %rdi
   0x000000000040054e <+17>:	5e	pop    %rsi
   0x000000000040054f <+18>:	e8 ec fe ff ff	callq  0x400440 <mprotect@plt>
   0x0000000000400554 <+23>:	ff e0	jmpq   *%rax
   0x0000000000400556 <+25>:	c3	retq                            <------ "retq = 0xc3"
   0x0000000000400557 <+26>:	5d	pop    %rbp
   0x0000000000400558 <+27>:	c3	retq
End of assembler dump.
(gdb) p system
$1 = {<text variable, no debug info>} 0x7ffff7a5b640 <__libc_system>
(gdb) find /h 0x7ffff7a5b640, +99999999, 0xc35a
0x7ffff7ad1ee0 <__opendirat+64>
0x7ffff7b1d145 <__lll_lock_wait_private+37>
0x7ffff7b2bcd2 <__GI_ruserpass+130>
warning: Unable to access 16000 bytes of target memory at 0x7ffff7bd3c54, halting search.
3 patterns found.
```

In the above snippet we found the address of the system ```0x7ffff7a5b640``` and took it as start address for searching and kept a large amount of memory (+99999999) to search. ```/h``` signifies that we are searching for half words. The pattern is ```0xc35a```. From the result it has found 3 patterns at the corresponding addresses. Let us take the first address, i.e ```0x7ffff7ad1ee0``` and use it.

###[Loading a Constant to a Register](./rop1.c),[Instr to Hex Code](./instr2hex.c)

This file demonstrates how to load an arbitrary value into ```%rdx``` register. Since we found out the address of ```0xc35a``` pattern we now use it. Put the value which has to be moved into ```%rdx``` register on the stack and use the instruction ```pop %rdx``` which moves the value into the register by popping the stack. Since it is followed by a ```retq``` instruction it returns to the address on top of stack. In this case we keep a test function to test whether the value has been moved into register or not. Similarly you can do for other registers also.

###[Loading from memory to Register](./rop2.c)

This file prints the value in the variable by doing a rop attack. This uses the code snippet "mov 48(%rax), %rax;" which moves a value from memory to address. Then prints the value in %rax in a round about manner by moving to and fro from %rdx register.

###[Calling mprotect by ROP and then executing shellcode](./rop3.c)

This file chains the gadgets and puts the register values as required for mprotect function and then executes mprotect then it also executes the shellcode and spawns the shell. Refer [instr2hex.c](./instr2hex.c) for address reference.
