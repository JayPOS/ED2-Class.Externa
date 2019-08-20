#include <stdio.h>
#include <stdlib.h>
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

FILE* ord (FILE* in){
	Memoria **v = (Memoria **) malloc(sizeof(Memoria *)*MAX);
	int i_men=0, men=0, ice = 0;

	for (int i = 0; i < MAX; ++i){
		v[i] = (Memoria *) malloc(sizeof(Memoria));
		v[i]->congelado = 0;
		fread(v[i]->p.cod, sizeof(int), 1, in);
	}

	FILE* part = fopen("part1.dat", "ab");
	while(){ //implementar o Le
		//i_men = func(implementar função para achar o menor) (CHECAR se tá congelado)
		men = v[i_men]->p.cod;
		fwrite(v[i_men].p.cod, sizeof(int), 1, part);
		fread(v[i_men].p.cod, sizeof(int), 1, in);	//salvando prox do in no vetor
		if(v[i_men]->p.cod < men){
			v[i_men]->congelado = 1;
			ice++;
		}
		if(ice == MAX){
			fclose(part);
			FILE* part = fopen("part2.dat", "ab"); //implementar um jeito de criar partição com nome em ordem crescente (strcat)
			for (int i = 0; i < MAX; ++i){
				v[i]->congelado = 0;
			}
			ice = 0;
		}
	}
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