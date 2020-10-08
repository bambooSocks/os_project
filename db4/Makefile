CC := gcc
CFLAGS := -g -Wall -std=c11

.PHONY : all
all : main

main : main.o linkedlist.o io.o
	$(CC) $(CFLAGS) main.o linkedlist.o io.o -o main

main.o : main.c
	$(CC) $(CFLAGS) -c main.c -o main.o

linkedlist.o : linkedlist.c
	$(CC) $(CFLAGS) -c linkedlist.c -o linkedlist.o

io.o : io.c
	$(CC) $(CFLAGS) -c io.c -o io.o

.PHONY : clean
clean :
	rm main main.o linkedlist.o
