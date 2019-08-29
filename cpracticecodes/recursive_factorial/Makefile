CFLAGS= -Wall -Wextra -Werror -pedantic
CC= gcc $( CFLAGS )

rec_fac: rec_fac.o
	$(CC) -o rec_fac rec_fac.o
rec_fac.o: rec_fac.c
	$(CC) -c rec_fac.c
clean:
	rm -f rec_fac rec_fac.o
