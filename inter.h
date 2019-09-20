#ifndef INTER_H
#define INTER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "clientes.h"

#define HV 10000

typedef struct elem
{
	Cliente *p;
	FILE *part;
} Elem;

typedef struct heap
{
  Elem **particoes;
  int tam;
  Elem **heap;
} Inter;

Inter *inicializar(int tam);
Inter *preparaParts(Inter *inter);
Inter *preparaHeap(Inter *inter);
Elem *ordena_inicio(Elem **heap, int inicio);
void printaHeap(Inter *inter);
void printaParticao(Inter *inter);
Inter *insere_heap(Inter* i, FILE* file);
Inter* subir(Elem** heap, int inicio);
int intercalar(int part_num, FILE* file);

#endif 
