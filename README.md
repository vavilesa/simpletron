# simpletron

This program creates a simple machine with 100-word memory, each word is a four digit signed integer. And it can understand it own 
"Simpletron Machine Language" (SML). The first two digits of a word are an instruction, while the other two are a memory location


| Operation code	| Meaning |
|---|---|
| *Input/output* |	|
| const int read = 10; | Read a word from the keyboard into a specific location in memory |
| const int write = 11;	| Write a word from a specific location in memory to the screen |
| *Load and store* | 	|
| const int load = 20;| Load a word from a specific location in memory into the |accumulator.
| const int store = 21;	| Store a word from the accumulator into a specific location in memory |
| *Arithmetic* | |
| const int add = 30;	| Add a word from a specific location in memory to the word in the accumulator (leave result in accumulator). |
| const int subtract = 31; | Subtract a word from a specific location in memory from the word in the accumulator (leave result in accumulator). |
| const int divide = 32; | Divide a word from a specific location in memory into the word in the accumulator (leave result in accumulator). |
| const int multiply = 33; | Multiply a word from a specific location in memory by the word in the accumulator (leave result in accumulator). |
| *Transfer-of-control* | |	
| const int branch = 40; | Branch to a specific location in memory |
| const int branchneg = 41; | Branch to a specific location in memory if the accumulator is negative. |
| const int branchzero = 42; | Branch to a specific location in memory if the accumulator is zero. |
| const int halt = 43; | Halt—the program has completed its task. |
