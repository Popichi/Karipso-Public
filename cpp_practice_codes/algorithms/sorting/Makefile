# The compiler: use g++ for a C++ program and gcc for a C program.
CC = g++

# Compiler flags:
# -g: This flag adds debugging information to the executable file.
# -Wall: This flag is used to turn on most of the compiler warnings.
# -std=c++11: This flag is used to compile the C++ program using the C++11 standards.
CFLAGS = -g -Wall -std=c++11

heapsort: main.o heapsort.o
	$(CC) $(CFLAGS) -o heapsort main.o heapsort.o

main.o: main.cpp heapsort.h
	$(CC) $(CFLAGS) -c main.cpp

heapsort.o: heapsort.h heapsort.cpp
	$(CC) $(CFLAGS) -c heapsort.cpp

clean:
	rm *.o *.h.gch heapsort heapsort.txt