graph: main.o anil_graph.o
	g++ main.o anil_graph.o -o graph

main.o: main.cpp
	g++ -c -g -Wall -std=c++11 main.cpp

anil_graph.o: anil_graph.cpp anil_graph.h anil_cursor_list.cpp anil_cursor_list.h
	g++ -c -g -Wall -std=c++11 anil_graph.cpp anil_cursor_list.cpp

clean:
	rm *.o graph graph_log.txt
