CC=gcc
FLAGS= -Wall

all:
	$(CC) clientes.c -o main main.c $(FLAGS)
