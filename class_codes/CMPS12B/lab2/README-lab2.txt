###############################################
# Anil Celik Maral - amaral
# amaral@ucsc.edu
# 1454995
# Lab - 2
# Lab: Friday, 9:00am - 10:00am
# Lab Partner: None
# Date: 04/27/17
###############################################

Files that are for lab2: README-lab2.txt, Makefile and arraylist.c
Note: "make" and "make all" commands compile the program and create an exacutable named "arraylist"
. "make clean" removes arraylist.o and arraylist exacutable.

-Answers to Questions from Valgrind Section-

4)All the invalid reads and writes come from the mistake on line 343 which allocates space for
the string using calloc as, "myString = calloc(stringSize, sizeof(char));". The problems is due
to how "strlen()" function works as it gives the value of "stringSize" variable right before the
calloc call. The function "strlen() computes the length of the" given "string up to, but not
including the terminating null character". Therefore, when line 343 was executed, it didn't
consider the fact that every string terminates with the null character "\0" and assigned a size
that was one less than the required size. When the calloc() was called, it didn't assign enough
memory for a C-style string. This caused problems when another function was writing to this 
memory location for the string or when it tried to read from the memory location. This problem
can be solved by simply adding one more bytes to the allocated memory. Since calloc() knows the
type of the variable that we want to allocate memory for, we can simply add "1" to the "stringSize"
; as a result, the correct code for line 343 is, "myString = calloc(stringSize + 1, sizeof(char));".

5)Valgrind says that the leaked chunk of memory was allocated on line 444 by realloc() which is 
used in the function demonstrateRealloc() which is also called by the main() function on line 537.
This leak is caused due to the usage of NULL pointer as an argument instead of the pointer of the 
previously allocated space on line 483 where realloc() acts like malloc() and overwrites the 
pointer(myVar) of the previous memory location instead of reallocating the space for it. This is
a classic example of why one should always use a temporary variable in cases like this.

-What the program does, arraylist.c-
The program start by dynamically allocating space for an eight integer long(4-bytes) array. Also,
it initializes the length and the capacity of the array. Moreover, a temporary pointer is created
so that it can be used later for safe reallocation. The reason for is that there is possibilty
that realloc() will return "NULL" if it fails. This would wipe out the knowledge for the address
of the previously allocated space and would make it impossible to access that address to free()
it. Program checks if the first allocation succeeded or not. It only starts the program if it
has successfully allocated space. Afterward, it ask for a choice between print, insert and
quit. Print, well, prints the members of the array. Quit free()s the allocated space and
return the control to the OS. Insert lets the user add an integer to the array. In insert,
input is saved into a different variable that the one for choice between insert, print and quit.
After each addition to the integer array, we check to see if the capacity is full. If it is,
we use the doubling algorithm to reallocated twice the size of the previous capacity. If this
reallocation succeeds, we save this pointer as the original pointer. This is to prote ct our
original pointer in case realloc() return "NULL". The program ask for the choice between
quit, insert and print after each print and insert section is completed. The only way to end
the program is to enter "Q". This way the memory is freed and control is given back to OS.
