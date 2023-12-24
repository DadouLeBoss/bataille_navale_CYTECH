CC = gcc
CFLAGS = -Wall -Wextra -std=c11

all: bataille_navale

bataille_navale: main.o bataille_navale.o
	$(CC) $(CFLAGS) -o $@ $^

main.o: main.c bataille_navale.h
	$(CC) $(CFLAGS) -c $<

bataille_navale.o: bataille_navale.c bataille_navale.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o bataille_navale
