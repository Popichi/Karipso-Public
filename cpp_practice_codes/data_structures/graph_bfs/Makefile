# The compiler: use g++ for a C++ program and gcc for a C program.
CC = g++

# Compiler flags:
# -g: This flag adds debugging information to the executable file.
# -Wall: This flag is used to turn on most of the compiler warnings.
# -std=c++11: This flag is used to compile the C++ program using the C++11 standards.
CFLAGS = -g -Wall -std=c++11

graph_bfs: main.o anil_graph_bfs.o anil_cursor_list.o
	$(CC) $(CFLAGS) -o graph_bfs main.o anil_graph_bfs.o anil_cursor_list.o

main.o: main.cpp anil_graph_bfs.h anil_cursor_list.h
	$(CC) $(CFLAGS) -c main.cpp

anil_graph_bfs.o: anil_graph_bfs.h anil_graph_bfs.cpp anil_cursor_list.h anil_cursor_list.cpp
	$(CC) $(CFLAGS) -c anil_graph_bfs.cpp anil_cursor_list.cpp

anil_cursor_list.o: anil_cursor_list.h anil_cursor_list.cpp
	$(CC) $(CFLAGS) -c anil_cursor_list.cpp

clean:
	rm *.o *.h.gch graph_bfs graph_log.txt