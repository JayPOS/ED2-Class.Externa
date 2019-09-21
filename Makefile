CC = gcc
FLAG = -Wall

all:
	$(CC) ./sources/clientes.c -o main main.c -Wall
