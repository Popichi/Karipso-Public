trie: main.o anil_trie.o
	g++ main.o anil_trie.o -o trie

main.o: main.cpp
	g++ -c -g -std=c++11 main.cpp

anil_trie.o: anil_trie.cpp anil_trie.h
	g++ -c -g -std=c++11 anil_trie.cpp

clean:
	rm *.o trie trie_log.txt