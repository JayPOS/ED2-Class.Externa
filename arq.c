#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "clientes.h"
#define MAX 4
//	PRAZO 3 DE SET!!!

//FUNÇÃO LOCALIZA A MENOR CHAVE
int menor(Memoria* v, int tam){
	int men = 0;
	for (int i = 0; i < tam; ++i){
		if(v[i].p->cod < v[men].p->cod && v[i].congelado != 1)
			men = i;
	}

	return men;
}

//FUNÇÃO PARA GERAR NOME PARA OS ARQUIVOS
char* gera_nome(int i, const char* nome){
	char str[100];
	sprintf(str, "%i", i);
	strcat(nome, str);
	strcat(nome, ".dat");

	return nome;
}

FILE* ord (FILE* in){
	Memoria v[MAX];
	int i_men = 0, ice = 0, qtd_arq = 1, men = 0;

	for (int i = 0; i < MAX; ++i){
		v[i].congelado = 0;
		v[i].p = le(in);
	}

	FILE* part = fopen("part1.dat", "ab");
	do {
		if(v[i_men].p->cod < men){
			v[i_men].congelado = 1;
			ice++;
		}
		i_men = menor(v, MAX);
		men = v[i_men].p->cod;
		salva(v[i_men].p, part);

		if(ice == MAX){
			fclose(part);
			qtd_arq++;
			FILE* part = fopen(gera_nome(qtd_arq, "part"), "ab");
			for (int i = 0; i < MAX; ++i){
				v[i].congelado = 0;
			}
			ice = 0;
		}
	}
	while ((v[i_men].p = le(in)) != NULL);
}

int main(){
	FILE* p;
	p = fopen("arquivo.dat", "ab");
	int aux;

	for (int i = 0; i < 10; i++){
    /* gerando valores aleatórios entre zero e 100 */
		aux = rand() % 100;
    	fwrite(&aux, sizeof(int), 1, p);
  	}

	return 0;
}