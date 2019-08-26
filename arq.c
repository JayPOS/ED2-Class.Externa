#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "clientes.h"
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
	// PROBLEMA NA VARIAVEL NOME
	char str[100];
	sprintf(str, "%i", i);
	strcat(nome, str);
	strcat(nome, ".dat");

	return nome;
}

FILE* ord (FILE* in){
	Memoria v[MAX];
	int i_men = 0, ice = 0, qtd_arq = 1, men = 0;
    Cliente* aux;
    
    //Lendo registros
	for (int i = 0; i < MAX; ++i){
		v[i].congelado = 0;
		aux = le(in);
        if(aux!=NULL)    v[i].p = aux;
	}

	FILE* part = fopen(gera_nome(qtd_arq, "part"), "ab");
	
    while(le(in) != NULL){    //Tem coisa pra ler
		//retornamos o cursor em 1 registro (pois ele foi alterado na linha acima)
        fseek(in, -(tamanho()), SEEK_CUR);
        while(ice < MAX){
            i_men = menor(v, MAX);
            men = v[i_men].p->cod;
            salva(v[i_men].p, part);
            aux = le(in);
            if(aux != NULL)    v[i_men].p = aux;

            if(v[i_men].p->cod < men){
                v[i_men].congelado = 1;
                ice++;
            }
        }
        fclose(part);
        qtd_arq++;
        FILE* part = fopen(gera_nome(qtd_arq, "part"), "ab");
        for (int i = 0; i < MAX; ++i){
            v[i].congelado = 0;
        }
        ice = 0;
    }
}

int main(){
	FILE* p;
	p = fopen("arquivo.dat", "ab");
	int aux;

	salva(criaCliente(7, "Bárbara", "19/05/2000"), p);
	salva(criaCliente(7, "João", "21/07/2000"), p);
	salva(criaCliente(7, "Natã", "23/09/1998"), p);
	salva(criaCliente(7, "Alana", "25/08/1976"), p);
	salva(criaCliente(7, "Jefferson", "14/07/1878"), p);

	ord(p);
	
	/*for (int i = 0; i < 10; i++){
    // gerando valores aleatórios entre zero e 100
		aux = rand() % 100;
    	fwrite(&aux, sizeof(int), 1, p);
  	}*/

	return 0;
}
