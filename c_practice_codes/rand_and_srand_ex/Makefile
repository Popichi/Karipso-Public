CFLAGS= -Wall -Wextra -Werror -pedantic
CC= gcc $( CFLAGS )

rase: rand_and_srand_ex.o
	$(CC) -o rase rand_and_srand_ex.o
rand_and_srand_ex.o: rand_and_srand_ex.c
	$(CC) -c rand_and_srand_ex.c
clean:
	rm -f rase rand_and_srand_ex.o
