CC = gcc
FLAG = -Wall

all: main

main: main.c
	$(CC) clientes.c inter.c -o main main.c FLAG