#include "inter.h"

#define DESATIVADO 0

Inter *inicializar(int tam)
{
  Inter *interc = (Inter *)malloc(sizeof(Inter));
  interc->tam = tam;
  interc->particoes = (Elem **)malloc(sizeof(Elem *)*tam);
  interc->heap = (Elem **)malloc(sizeof(Elem *)*((2*tam)-1));
  return interc;
}
Inter *preparaParts(Inter *inter)
{
  int i;
  for (i = 0; i < inter->tam; i++)
  {
    inter->particoes[i] = (Elem *)malloc(sizeof(Elem));
    inter->particoes[i]->part = fopen(gera_nome(i), "rb");
    inter->particoes[i]->p = le(inter->particoes[i]->part);
  }
  return inter;
}
Inter *preparaHeap(Inter *inter)
{
  int i;
  for(i = 0; i < (2*inter->tam)-1; i++)
  {
    
    if (i < inter->tam-1)
    {
      inter->heap[i]->part = NULL;
      inter->heap[i]->p = (Cliente *)malloc(sizeof(Cliente));
      inter->heap[i]->p->cod = DESATIVADO;
    }
    else
    {
      inter->heap[i]->part = inter->particoes[i-(inter->tam-1)]->part;
      inter->heap[i]->p = (Cliente *)malloc(sizeof(Cliente));
      inter->heap[i]->p = inter->particoes[i-(inter->tam-1)]->p;
    }
  }
  return inter;
}
Inter *insere_heap()
{
  
}

