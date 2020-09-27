CC := gcc
CFLAGS := -g -Wall

.PHONY : all
all : main

main : main.o linkedlist.o
	$(CC) $(CFLAGS) main.o linkedlist.o -o main

main.o : main.c
	$(CC) $(CFLAGS) -c main.c -o main.o

linkedlist.o : linkedlist.c
	$(CC) $(CFLAGS) -c linkedlist.c -o linkedlist.o

.PHONY : clean
clean :
	rm main main.o linkedlist.o