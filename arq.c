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
int menor(Memoria* v, int tam){
	int men = 0;
	for (int i = 0; i < tam; ++i){
		if(v[i].p->cod < v[men].p->cod && v[i].congelado != 1)
			men = i;
	}

	return men;
}

//FUNÇÃO PARA GERAR NOME PARA OS ARQUIVOS
char* gera_nome(int i){
	// PROBLEMA NA VARIAVEL NOME
	char *str = (char *)malloc(sizeof(char)*15);
	printf("b1\n");
	sprintf(str, "part%i.dat", i);
	printf("b2\n");
	// strcat(nome, str);
	// printf("b3\n");
	// strcat(nome, ".dat");
	// printf("b4\n");

	return str;
}

void ord (FILE* in){
	Memoria *v = (Memoria *)malloc(sizeof(Memoria)*MAX);
	int i_men = 0, ice = 0, qtd_arq = 1, men = 0;
    Cliente* aux;
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
	printf("a10.1\n");
	char *str = gera_nome(qtd_arq);
	FILE* part = fopen(str, "w+b");
	free(str);
	printf("a10\n");
	
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

            if(v[i_men].p->cod < men){
                v[i_men].congelado = 1;
                ice++;
				printf("a8\n");
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

int main(){
	FILE* p;
	p = fopen("arquivo.dat", "rb");
	int aux;

	salva(criaCliente(1, "Bárbara", "19/05/2000"), p);
	salva(criaCliente(6, "João", "21/07/2000"), p);
	salva(criaCliente(4, "Natã", "23/09/1998"), p);
	salva(criaCliente(7, "Alana", "25/08/1976"), p);
	salva(criaCliente(2, "Jefferson", "14/07/1878"), p);

	ord(p);
	
	// FILE *p;
	rewind(p);
	imprimeArq(p);
	printf("\n");
	imprimeArq(fopen("part1.dat", "rb"));
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
