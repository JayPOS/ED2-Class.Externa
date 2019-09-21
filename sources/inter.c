#include "headers/inter.h"

#define LINHA "---------------------------------------"
#define CLEAR "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"

#define DESATIVADO 0

int esq(int no)
{
    return 2*no+1;
}
int dir(int no)
{
    return 2*no+2;
}
int tamHeap(int n_folhas)
{
    return 2*n_folhas-1;
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
    printf("%d %d\n", i, inter->particoes[i]->p->cod);
  }
  printf("\n");
}

void salva2(Cliente *p, FILE *out)
{
    fwrite(&p->cod, sizeof(int), 1, out);
    fwrite(p->nome, sizeof(char), sizeof(p->nome), out);
    fwrite(p->data_n, sizeof(char), sizeof(p->data_n), out);

    // return NULL;
}

void libera(Inter *inter)
{
  int i;
  for (i = 0; i < inter->tam; i++)
    free(inter->particoes[i]);

  free(inter->particoes);
  free(inter->heap);
  free(inter);
}

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
  for (i = 0; i < inter->tam; i++)
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
Elem **alteraParts(Elem **parts, FILE *id, int tam)
{
    int i;
    for (i = 0; i < tam; i++)
    {
        if (parts[i]->part == id)
        {
            if (0 >= fread(&parts[i]->p->cod, sizeof(int), 1, id))
            {
                parts[i]->p->cod = HV;
                return parts;
            }
            fread(parts[i]->p->nome, sizeof(char), sizeof(parts[i]->p->nome), id);
            fread(parts[i]->p->data_n, sizeof(char), sizeof(parts[i]->p->data_n), id);
            break;
        }
    }
    return parts;
}
Elem *ordena_inicio(Elem **heap, int inicio)
{
  if (heap[inicio]->p->cod == DESATIVADO)
  {
    heap[2*(inicio+1)-1] = ordena_inicio(heap, 2*(inicio+1)-1);
    heap[(2*(inicio+1))] = ordena_inicio(heap, (2*(inicio+1)));
    if (heap[2*(inicio+1)-1]->p->cod < heap[(2*(inicio+1))]->p->cod)
    {
      if (heap[inicio]->p->cod == DESATIVADO)
        free(heap[inicio]->p);
      return heap[2*(inicio+1)-1];
    }
    else
    {
      if (heap[inicio]->p->cod == DESATIVADO)
        free(heap[inicio]->p);
      return heap[(2*(inicio+1))];
    }
    
  }
  else
  {
    return heap[inicio];
  }
}

Elem *attHeap(Elem **heap, int inicio, int tam)
{
    if (heap[inicio] == heap[0])
    {
        if (esq(inicio) < tamHeap(tam))
        {
            attHeap(heap, esq(inicio), tam);
            attHeap(heap, dir(inicio), tam);

            if (heap[esq(inicio)]->p->cod < heap[dir(inicio)]->p->cod)
            {
                heap[inicio] = heap[esq(inicio)];
            }
            else
            {
                heap[inicio] = heap[dir(inicio)];
            }
            
        }
    }
    return heap[inicio];
}

int intercalar(int part_num, FILE *file)
{
  if (part_num != 0)
  {
    Inter *inter = inicializar(part_num);
    inter = preparaParts(inter);
    inter = preparaHeap(inter);
    // printaHeap(inter);
    inter->heap[0] = ordena_inicio(inter->heap, 0);
    do
    {
        salva2(inter->heap[0]->p, file);
        inter->particoes = alteraParts(inter->particoes, inter->heap[0]->part, inter->tam);
        inter->heap[0] = attHeap(inter->heap, 0, inter->tam);
    }while(inter->heap[0]->p->cod != HV);
    printf("%sSucesso! O resultado foi armazenado em resultado.dat\n", CLEAR);
    // printf("\n");
    // printaHeap(inter);
    fclose(file);
    libera(inter);
  }
  else
  {
    printf("N tem partições!\n");
    return 0;
  }
  return 1;
}

