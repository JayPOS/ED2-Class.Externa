#ifndef CLIENTES_H
#define CLIENTES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAX 4
//	PRAZO 3 DE SET!!!

typedef struct cliente{
	int cod;
	char nome[50];
	char data_n[20];
} Cliente;

typedef struct Memoria{
	int congelado;
	Cliente p;
} Memoria;

//BLOCO COM AS FUNÇÕES MAIS BÁSICAS

Cliente *criaCliente(int cod, char *nome, char *data);
void salva(Cliente *p, FILE *out);
Cliente *le(FILE *in);
void imprime(Cliente *p);
int tamanho();

//BLOCO DAS FUNÇÕES DE ORDENAÇÃO;

FILE *criaParticao(int idPart);
int menor(Memoria *vetor);

#endif