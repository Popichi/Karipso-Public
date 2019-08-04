andyqull: main.o anil_dynamic_queue_ll.o
	g++ main.o anil_dynamic_queue_ll.o -o andyqull

main.o: main.cpp
	g++ -c -g main.cpp

anil_dynamic_queue_ll.o: anil_dynamic_queue_ll.cpp anil_dynamic_queue_ll.h
	g++ -c -g anil_dynamic_queue_ll.cpp

clean:
	rm *.o andyqull