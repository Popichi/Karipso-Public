# The compiler: use g++ for a C++ program and gcc for a C program.
CC = g++

# Compiler flags:
# -g: This flag adds debugging information to the executable file.
# -Wall: This flag is used to turn on most of the compiler warnings.
# -std=c++11: This flag is used to compile the C++ program using the C++11 standards.
CFLAGS = -g -Wall -std=c++11

# The build target
#TARGET = myprogram

#all: $(TARGET)

#$(TARGET): $(TARGET).cpp
#	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c

#clean:
#	$(RM) $(TARGET)

graph: main.o anil_graph.o anil_cursor_list.o
	$(CC) $(CFLAGS) -o graph main.o anil_graph.o anil_cursor_list.o

main.o: main.cpp anil_graph.h anil_cursor_list.h
	$(CC) $(CFLAGS) -c main.cpp

anil_graph.o: anil_graph.h anil_graph.cpp anil_cursor_list.h anil_cursor_list.cpp
	$(CC) $(CFLAGS) -c anil_graph.cpp anil_cursor_list.cpp

anil_cursor_list.o: anil_cursor_list.h anil_cursor_list.cpp
	$(CC) $(CFLAGS) -c anil_cursor_list.cpp

clean:
	rm *.o *.h.gch graph graph_log.txt