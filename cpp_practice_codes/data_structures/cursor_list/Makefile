cursor_list: main.o anil_cursor_list.o
	g++ main.o anil_cursor_list.o -o cursor_list

main.o: main.cpp
	g++ -c -g -Wall -std=c++11 main.cpp

anil_cursor_list.o: anil_cursor_list.cpp anil_cursor_list.h
	g++ -c -g -Wall -std=c++11 anil_cursor_list.cpp

clean:
	rm *.o cursor_list cursor_list_log.txt

# cursor_list: main.o anil_cursor_list.o
# 	g++ main.o anil_cursor_list.o -o cursor_list

# main.o: main.cpp
# 	g++ -c -g -std=c++11 main.cpp

# anil_cursor_list.o: anil_cursor_list.cpp anil_cursor_list.h
# 	g++ -c -g -std=c++11 anil_cursor_list.cpp

# clean:
# 	rm *.o cursor_list cursor_list_log.txt