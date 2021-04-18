stack_dynamic_array: main.o anil_stack_dynamic_array.o
	g++ main.o anil_stack_dynamic_array.o -o stack_dynamic_array

main.o: main.cpp
	g++ -c -g -std=c++11 main.cpp

anil_stack_dynamic_array.o: anil_stack_dynamic_array.cpp anil_stack_dynamic_array.h
	g++ -c -g -std=c++11 anil_stack_dynamic_array.cpp

clean:
	rm *.o stack_dynamic_array