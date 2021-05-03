doubly_linked_list: main.o anil_doubly_linked_list.o
	g++ main.o anil_doubly_linked_list.o -o doubly_linked_list

main.o: main.cpp
	g++ -c -g -std=c++11 main.cpp

anil_doubly_linked_list.o: anil_doubly_linked_list.cpp anil_doubly_linked_list.h
	g++ -c -g -std=c++11 anil_doubly_linked_list.cpp

clean:
	rm *.o doubly_linked_list doubly_linked_list_log.txt