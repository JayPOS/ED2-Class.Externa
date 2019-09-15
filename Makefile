<<<<<<< HEAD
CC = gcc
FLAG = -Wall

all:
	$(CC) clientes.c inter.c -o main main.c FLAG
=======
CC=gcc
FLAGS= -Wall

all:
	$(CC) clientes.c -o main main.c $(FLAGS)
>>>>>>> master
