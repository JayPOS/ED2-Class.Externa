#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "clientes.h"
//	PRAZO 3 DE SET!!!

//FUNÇÃO LOCALIZA A MENOR CHAVE
void imprimeArq(FILE *in)
{
	Cliente *aux = le(in);
	while (aux != NULL)
	{
		imprime(aux);
		aux = le(in);
	}
}
int vazio(Memoria *v)
{
	int i;
	for (i = 0; i < MAX; i++)
	{
		if (v[i].p != NULL)
			return 0;
	}
	return 1;
}
int menor(Memoria* v, int tam){
	int men = 0;
	for (int i = 0; i < tam; ++i){
		
		if(v[i].p->cod < v[men].p->cod && v[i].congelado != 1)
			men = i;
	}

	return men;
}
int menor2(Memoria* v, int tam){
	int men;
	int ini = 1;
	for (int i = 0; i < tam; ++i){
		if (v[i].p != NULL)
		{	
			if (ini == 1)
			{
				men = i;
				ini = 0;
			}
			else if(v[i].p->cod < v[men].p->cod && v[i].congelado != 1)
				men = i;
		}
	}

	return men;
}

int all_ice(Memoria *memo)
{
	int i;
	for (i = 0; i < MAX; i++)
	{
		if (memo[i].congelado == 0 && memo[i].p != NULL)
			return 0;
	}
	return 1;
}
Memoria *desgela(Memoria *memo)
{
	int i;
	for (i = 0; i < MAX; i++)
		memo[i].congelado = 0;
	return memo;
}

//FUNÇÃO PARA GERAR NOME PARA OS ARQUIVOS
char* gera_nome(int i){
	// PROBLEMA NA VARIAVEL NOME
	char *str = (char *)malloc(sizeof(char)*15);
	// printf("b1\n");
	sprintf(str, "part%i.dat", i);
	// printf("b2\n");
	// strcat(nome, str);
	// printf("b3\n");
	// strcat(nome, ".dat");
	// printf("b4\n");

	return str;
}

void ord (FILE* in){
	Cliente* aux;
	Memoria *v = (Memoria *)malloc(sizeof(Memoria)*MAX);
	int i_men = 0, ice = 0, qtd_arq = 1, men = 0;
	
	printf("a10.1\n");
	char *str = gera_nome(qtd_arq);
	FILE* part = fopen(str, "w+b");
	free(str);
	printf("a10\n");
    
    printf("a0\n");
    //Lendo registros
	for (int i = 0; i < MAX; ++i){
		v[i].congelado = 0;
		printf("a1\n");
		aux = le(in);
		printf("a2\n");

        if(aux!=NULL) v[i].p = aux;
		else break;
		
		printf("a3\n");
	}
	
    while(le(in) != NULL){    //Tem coisa pra ler
		//retornamos o cursor em 1 registro (pois ele foi alterado na linha acima)
		printf("a4\n");
        fseek(in, -(tamanho()), SEEK_CUR);
        while(ice < MAX){
			printf("a5\n");
            i_men = menor(v, MAX);
            men = v[i_men].p->cod;
            salva(v[i_men].p, part);
			printf("a6\n");
            aux = le(in);
			printf("a7\n");
            if(aux != NULL)    v[i_men].p = aux;

			if (v[i_men].p != NULL)
			{
				if(v[i_men].p->cod < men){
					v[i_men].congelado = 1;
					ice++;
					printf("a8\n");
				}
			}
        }
        fclose(part);
        qtd_arq++;
		printf("a9\n");
		str = gera_nome(qtd_arq);
		printf("a9.1\n");
        FILE* part = fopen(str, "w+b");
		printf("a9.2\n");
		free(str);
        for (int i = 0; i < MAX; ++i){
            v[i].congelado = 0;
        }
        ice = 0;
    }
}
void ord2(FILE *in)
{
	int partCont = 1;
	int men_cod, escrito;
	// int ice = 0;

	char *str = gera_nome(partCont);
	FILE *part = fopen(str, "w+b");
	free(str);

	Memoria *v = (Memoria *)malloc(sizeof(Memoria)*MAX);

	int i;
	for (i = 0; i < MAX; i++)
		v[i].p = le(in);

	while(!vazio(v))
	{
		// printf("entrou1\n");
		men_cod = menor2(v, MAX);
		// printf("entrou2\n");
		// printf("%d\n", v[men_cod].p->cod);
		// printf("entrou3\n");
		escrito = v[men_cod].p->cod;
		// printf("entrou4\n");
		salva(v[men_cod].p, part);
		// printf("entrou5\n");
		v[men_cod].p = le(in);
		// if (v[men_cod].p != NULL)
		// 	printf("leu = %d\n", v[men_cod].p->cod);
		// printf("entrou6\n");
		
		if(v[men_cod].p != NULL)
		{
			// printf("entrou7\n");
			if (v[men_cod].p->cod < escrito)
			{
				v[men_cod].congelado = 1;
				// printf("entrou8\n");
			}
				
		}
		
		if(all_ice(v) && !vazio(v))
		{
			// printf("entrou9\n");
			fclose(part);
			partCont++;
			char *str = gera_nome(partCont);
			part = fopen(str, "w+b");
			free(str);
			v = desgela(v);
		}
	}
	fclose(part);
}
int main(){
	FILE* p;
	p = fopen("arquivo.dat", "rb");
	int aux;

	salva(criaCliente(1, "Bárbara", "19/05/2000"), p);
	salva(criaCliente(6, "João", "21/07/2000"), p);
	salva(criaCliente(4, "Natã", "23/09/1998"), p);
	salva(criaCliente(7, "Alana", "25/08/1976"), p);
	salva(criaCliente(2, "Jefferson", "14/07/1878"), p);

	ord2(p);
	
	// FILE *p;
	rewind(p);
	imprimeArq(p);
	printf("\n");
	FILE *p2 = fopen("part1.dat", "r+b");
	rewind(p2);
	imprimeArq(p2);
	printf("\n");
	imprimeArq(fopen("part2.dat", "rb"));
	/*for (int i = 0; i < 10; i++){
    // gerando valores aleatórios entre zero e 100
		aux = rand() % 100;
    	fwrite(&aux, sizeof(int), 1, p);
  	}*/
	fclose(p);

	return 0;
}
