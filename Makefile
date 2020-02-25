CC = gcc

all: cordic.o
	$(CC) -o CORDIC cordic.o

cordic.o: cordic.c cordic.h
	$(CC) -c cordic.c
