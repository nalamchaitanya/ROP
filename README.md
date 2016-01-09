#Return Oriented Programming(ROP)

##Introduction:

This project is based on [Introduction to Return Oriented Programming](http://codearcana.com/posts/2013/05/28/introduction-to-return-oriented-programming-rop.html) and [The Geometry of Innocent Flesh on the Bone:Return-into-libc without Function Calls](https://cseweb.ucsd.edu/~hovav/dist/geometry.pdf).

>What is Return Oriented Programming?

In our previous project of [Buffer OverFlow Attack](../BOFA) we have made the shellcode(which executes the shell) and overflowed the buffer with it and got a shell. This is done by injecting the code (shellcode) into the buffer and by giving it the permission to execute. However this is not possible because of the constraint **W xor X** which makes the memory either executable or writable but not both. There by making our injected code not to execute.

We circumvent this constraint by using the code that is already present in code segment of the executable and chaining them together by series of return instructions to execute the code we want. We call the small parts (generally one or two instructions) of the code segment ending with the ```retq``` instruction as **gadgets**. In the [Geometry Paper](https://cseweb.ucsd.edu/~hovav/dist/geometry.pdf) it is said that

>**In any sufficiently large body of x86 executable code there will exist sufficiently many useful code sequences (gadgets) that an attacker who controls the stack will be able to undertake any arbitrary computation.**

This attack works mainly on the ```retq``` instruction which pops one quad word from the stack and moves that value to ```%rip```. It is similar to the instruction ```pop %rip``` so that the next instruction executes from that point. We use this extensively for chaining the gadgets, so the name **Return Oriented Programming**.

The main difference between **Return to lib-c attack** and **Return Oriented Programming** is that the former one executes a whole function in the c library and then returns to another function i.e it chains function together however the later one chains gadgets together there by gaining more control over the execution.

In this project we will do the Return Oriented Programming attacks inside the gdb as it disables the ASLR(Address Space Layout Randomization) which is done for an executable to keep the address space of the lib-c change randomly.

##Requirements:

 You have to be familiar with how a stack functions and some facts about how the function calls are organized using stack. Stacks can be top-down or bottom-up based on the direction of growth of the stack after a push operation. If the rsp value is decreased it means stack is growing downward implies that it is a top-down stack and in the same way if the rsp value is increased then it is growing upward implies that it is a bottom-up stack.

 In this project I used **AT&T** syntax for assembly code which you can get familiarised using [Brennan's Guide to Inline Assembly](http://www.delorie.com/djgpp/doc/brennan/brennan_att_inline_djgpp.html). Basic Inline Assembly is enough as far as this project is concerned.

 We should be adding the gcc option ```-fno-stack-protector``` to prevent any canaries added to the functions.

##SourceCode:

The main goal of the project is to give executable permissions to the data segment of the program, which contains the [shellcode](https://github.com/nvsskchaitanya/BOFA#shellcodec) and then execute the shellcode to get the shell. We will do it step by step through the files.

The main problem of the 64-bit addressing is that it has a lot of NULL bytes in its address example ```0x000000000040602d``` which makes it hard to tailor the string which overflows the buffer as these NULL bytes terminate the string. For this reason I always put spaces ```0x20``` instead of NULL bytes so that in the program I will replace it with NULL bytes using memset.

###[firstROP.c](./firstROP.c)

This file is to demonstrate how to change return address of the function by overflowing the buffer and executing a function which is not at all called.
