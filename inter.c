#include "inter.h"
#define FOLHA eh_folha(Elem *esq, Elem *dir) ((esq == NULL && dir == NULL) : 1 ? 0)

#define DESATIVADO 0

Inter *inicializar(int tam)
{
  Inter *interc = (Inter *)malloc(sizeof(Inter));
  interc->tam = tam;
  interc->particoes = (Elem **)malloc(sizeof(Elem *)*tam);
  printf("Tam heap = %d\n", ((2*tam)-1));
  interc->heap = (Elem **)malloc(sizeof(Elem *)*((2*tam)-1));
  return interc;
}
Inter *preparaParts(Inter *inter)
{
  printf("Em preparaParts\n");
  int i;
  for (i = 0; i < inter->tam; i++)    //Inicializando as particoes da heap
  {
    inter->particoes[i] = (Elem *)malloc(sizeof(Elem));
    inter->particoes[i]->part = fopen(gera_nome(i+1), "rb");
    inter->particoes[i]->p = le(inter->particoes[i]->part);
  }
  return inter;
}
Inter *preparaHeap(Inter *inter)
{
  int i;
  printf("Preparando heap...\n");
  for(i = 0; i < (2*inter->tam)-1; i++)
  {
    inter->heap[i] = (Elem *)malloc(sizeof(Elem));
    if (i < inter->tam-1)    //Nós internos (tam-1)
    {
      inter->heap[i]->part = NULL;
      inter->heap[i]->p = (Cliente *)malloc(sizeof(Cliente));
      inter->heap[i]->p->cod = DESATIVADO;
    }
    else    //Folhas (começando no 12 no casoPronto)
    {
      //printf("i = %d || part = %d\n", i, i-(inter->tam-1));
      inter->heap[i]->part = inter->particoes[i-(inter->tam-1)]->part;    //Atualizando pont de part dos elementos da heap
      // inter->heap[i]->p = (Cliente *)malloc(sizeof(Cliente));
      inter->heap[i]->p = inter->particoes[i-(inter->tam-1)]->p;
    }
  }
  return inter;
}
Elem *ordena_inicio(Elem **heap, int inicio)
{
  printf("indice pai: %d\n", inicio);    //Primeiro deve ser 0
  if (heap[inicio]->p->cod == DESATIVADO)
  {
    printf("Cod do pai desativado !!\n");
    printf("esq: %d || dir: %d\n", heap[2*(inicio+1)-1]->p->cod, heap[(2*(inicio+1))]->p->cod);
    heap[2*(inicio+1)-1] = ordena_inicio(heap, 2*(inicio+1)-1);
    heap[(2*(inicio+1))] = ordena_inicio(heap, (2*(inicio+1)));
    if (heap[2*(inicio+1)-1]->p->cod < heap[(2*(inicio+1))]->p->cod)
    {
      return heap[2*(inicio+1)-1];
    }
    else
    {
      return heap[(2*(inicio+1))];
    }
    
  }
  else
  {
    printf("Cod do pai não desativado :)\n");
    return heap[inicio];
  }

  //pai = inicio
  //esq = 2*inicio-1
  //dir = 2*inicio

}
void printaHeap(Inter *inter)
{
  int i;
  for (i = 0; i < (2*inter->tam)-1; i++)
  {
    printf("%d %d\n", i, inter->heap[i]->p->cod);
  }
}
void printaParticao(Inter *inter)
{
  int i;
  for (i = 0; i < inter->tam; i++)
  {
    //printf("%d %d\n", i, inter->particoes[i]->p->cod);
  }
  printf("\n");
}
Inter *insere_heap(Inter* inter, FILE* file)
{
  if(inter->heap[0]->p->cod != DESATIVADO){
      printf("Pai não desativado\n");
      int i=0;
      // Não está salvando
      salva(inter->heap[0]->p, file);    //salvando menor no file final
      le_tudo(file);
      
      // Procurando cod do heap[0] como folha
      for(i=0;i<inter->tam;i++){
          if(inter->particoes[i]->p == inter->heap[0]->p){
              //Folha com o menor valor = prox cliente da part da folha com menor valor 
             inter->heap[i+(inter->tam-1)]->p = le(inter->particoes[i]->part);
          }
          inter = subir(inter->heap, i+(inter->tam-1));
      }
  }
  else{
      printf("Ordenar heap para retirar menor !\n");
  }
  return NULL;
}

Inter* subir(Elem** heap, int inicio){
    return NULL;
}
int intercalar(int part_num, FILE* file)
{
  if (part_num != 0)
  {
    Inter *inter = inicializar(part_num);
    inter = preparaParts(inter);
    inter = preparaHeap(inter);
    printf("Printando 1ª heap:\n");
    printaHeap(inter);
    //printf("\n");
    printf("\nEntrando em ordena_inicio :\n");
    inter->heap[0] = ordena_inicio(inter->heap, 0);
    printf("\nPrintando 2ª heap:\n");
    printaHeap(inter);
    printf("A ser tirado: %d\n", inter->heap[0]->p->cod);
    printf("Chamando insere_heap\n");
    insere_heap(inter, file);
  }
  else
  {
    printf("N tem partições!\n");
    return 0;
  }
  return 1;
}

