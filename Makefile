CC = gcc

all: cordic.o
	$(CC) -o CORDIC cordic.o -lm

cordic.o: cordic.c cordic.h
	$(CC) -c cordic.c -lm

run:
	./CORDIC
