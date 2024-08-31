CC= gcc
CFLAGS = -g -Wall -fsanitize=address

spchk.o: spchk.c
	$(CC) $(CFLAGS) spchk.c -o spchk
clean:
	rm -f spchk.o