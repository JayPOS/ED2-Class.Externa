#include "inter.h"
#define FOLHA eh_folha(Elem *esq, Elem *dir) ((esq == NULL && dir == NULL) : 1 ? 0)

#define DESATIVADO 0

Inter *inicializar(int tam)
{
  Inter *interc = (Inter *)malloc(sizeof(Inter));
  interc->tam = tam;
  interc->particoes = (Elem **)malloc(sizeof(Elem *)*tam);
  printf("%d\n", ((2*tam)-1));
  interc->heap = (Elem **)malloc(sizeof(Elem *)*((2*tam)-1));
  return interc;
}
Inter *preparaParts(Inter *inter)
{
  int i;
  for (i = 1; i < inter->tam; i++)
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
    inter->heap[i] = (Elem *)malloc(sizeof(Elem));
    if (i < inter->tam-1)
    {
      inter->heap[i]->part = NULL;
      inter->heap[i]->p = (Cliente *)malloc(sizeof(Cliente));
      inter->heap[i]->p->cod = DESATIVADO;
    }
    else
    {
      inter->heap[i]->part = inter->particoes[i-(inter->tam-1)]->part;
      // inter->heap[i]->p = (Cliente *)malloc(sizeof(Cliente));
      inter->heap[i]->p = inter->particoes[i-(inter->tam-1)]->p;
    }
  }
  return inter;
}
Elem *ordena_inicio(Elem **heap, int inicio)
{
  if (heap[inicio]->part == NULL)
  {
    heap[2*(inicio+1)] = ordena_inicio(heap, 2*(inicio+1));
    heap[(2*(inicio+1))+1] = ordena_inicio(heap, (2*(inicio+1)+1));
    if (heap[2*(inicio+1)]->p->cod < heap[(2*(inicio+1))+1]->p->cod)
    {
      return heap[2*(inicio+1)];
    }
    else
    {
      return heap[(2*(inicio+1))+1];
    }
    
  }
  else
  {
    return heap[inicio];
  }

  //pai = inicio
  //esq = 2*inicio-1
  //dir = 2*inicio

}
Inter *insere_heap(Elem *Raiz)
{
  
}
int intercalar(int part_num)
{
  if (part_num != 0)
  {
    Inter *inter = inicializar(part_num);
    inter = preparaParts(inter);
    inter = preparaHeap(inter);
    inter->heap[0] = ordena_inicio(inter->heap, 0);
    printf("code: %d\n", inter->heap[0]->p->cod);
  }
  else
  {
    printf("N tem partições!\n");
    return 0;
  }
  return 1;
}

