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
  int id;
} Elem;

typedef struct heap
{
  Elem **particoes;
  int tam;
  Elem **heap;
} Inter;

Inter *inicializar(int tam);
Inter *insere_heap();
Inter *preparaParts(Inter *i);
Inter *preparaHeap(Inter *i);
int intercalar();

#endif 