# CPU

## What is this project?

A processor is a project that processes your assembly commands. For example, you enter push 5 and to begin with, this line will be assembled and then processed by my processor, which will create and fill the stack.

## How to use it?

If you want to use this program you need to download directory CPU.

If you want to write something useful on my processor you need to go to the folder "txt files" and in test.asm you can write your code in assembly language.

Then you need to compile assembler and then cpu. 

You can do it like that: 
                          
                           cd assembler
                           make
                           cd ..
                           cd cpu   
                           make
Sorry for two make in one project in next update I promise to fix that.

## What commands does my project understand?

*push
*pop
*add
*sub
*div
*mul
*out
*end
*jmp
*je
*jne
*inc
*dec
*cmp

There are not so many commands but they are enough to write the simplest codes.
