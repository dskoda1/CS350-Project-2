# CS350-Project-2
Lab5/ Program 2

Contributors:
David Skoda
Nick Cortina

Upon issuing the make command, 2 executables will be created: one that simulates memory, and one that generates test cases. Our test case generator will write lines to a file for use with the memory simulator. The memory simulator will simulate page replacement, and after reading all the instructions in a given file, it will print out the page fault rates for 3 different page replacement strategies: random, least recently used, and first in first out.

Instructions to run the test case generator:

./input_gen <number of processes> <process address size> <number of references> <pattern> <file name>

Number of processes is the total number of processes that are created, and process address size is the size of each process' address space. Number of references refers to the total number of reference commands that will be in the file. Pattern is the style of references that will be put i nthe file and can be 0, 1, or 2. 0 denotes having mostly locality of reference, 1 denotes total random access, and 2 denotes random process issuing references with locality. File name is the name of the file that the generator will write to.

The test case generator will output lines to the file as described in the program assignment, with examples of each command type listed below:
START 2 4
REFERENCE 3 2
TERMINATE 1

Instructions to run the memory simulator:

./program2 <frames of memory> <input file>

Frames of memory is the number of frames that our simulated memory will have. Input file is the name of the file to read commands from.

The memory simulator will output lines to stdout in the format specified by the program assignment, with an example below:
Page Fault Rates:
RANDOM: 59%
LRU: 57%
FIFO: 57%


Keep in mind that whatever file name is used to generate test cases must be the same file name that is used when running the memory simulator if the desired action is using the two programs together.
