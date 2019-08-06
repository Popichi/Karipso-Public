bisetr: main.o binary_search_tree.o
	g++ main.o binary_search_tree.o -o bisetr

main.o: main.cpp
	g++ -c -g main.cpp

binary_search_tree.o: binary_search_tree.cpp binary_search_tree.h
	g++ -c -g binary_search_tree.cpp

clean:
	rm *.o bisetr