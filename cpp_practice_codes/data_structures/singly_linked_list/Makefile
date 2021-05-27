singly_linked_list: main.o anil_singly_linked_list.o
	g++ main.o anil_singly_linked_list.o -o singly_linked_list

main.o: main.cpp
	g++ -c -g -std=c++11 main.cpp

anil_singly_linked_list.o: anil_singly_linked_list.cpp anil_singly_linked_list.h
	g++ -c -g -std=c++11 anil_singly_linked_list.cpp

clean:
	rm *.o singly_linked_list singly_linked_list_log.txt