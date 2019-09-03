#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "clientes.h"

#define LINHA "---------------------------------------"
#define CLEAR "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"

#define ARQUIVO 1
#define TERMINAL 2



Cliente *ler_txt(FILE *in)
{
	Cliente *aux = (Cliente *)malloc(sizeof(Cliente));
	if(fscanf(in, "%d %s %s", &aux->cod, aux->nome, aux->data_n) <= 0)
		return NULL;

	return aux;
}
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

int menor(Memoria *v, int tam){
	int men = 0;
	for (int i = 0; i < tam; ++i){
		if(v[i].p != NULL && v[i].congelado != 1){
			men = i;
			break;
		}
	}
	for (int i = 0; i < tam; ++i){
		if(v[i].p != NULL && v[i].congelado != 1 && v[i].p->cod < v[men].p->cod)
			men = i;
	}
	return men;
}

//FUNÇÃO PARA GERAR NOME PARA OS ARQUIVOS
char* gera_nome(int i){
	// PROBLEMA NA VARIAVEL NOME
	char *str = (char *)malloc(sizeof(char)*15);
	sprintf(str, "part%i.dat", i);
	return str;
}

// FUNÇÕES PARA O MENU:
void criar_registro(int tipo)
{
	if (tipo == ARQUIVO)
	{
		char nomeArq[100];
		char nomeDest[100];
		
		printf("%sDigite o nome do arquivo txt: ", CLEAR);
		scanf("%s", nomeArq);
		printf("%s\nDigite o nome do novo registro: ", LINHA);
		scanf("%s", nomeDest);

		FILE *f1 = fopen(nomeArq, "r");
		if (f1 != NULL)
		{
			FILE *f2 = fopen(nomeDest, "wb");
			Cliente *aux = ler_txt(f1);
			do
			{
				salva(aux, f2);
				aux = ler_txt(f1);
			} while (aux != NULL);
			
			fclose(f2);
		}
		else
		{
			printf("Arquivo Inexistente!\n");
			exit(1);
		}
		fclose(f1);
	}
	if (tipo == TERMINAL)
	{
		char nomeDest[100];
		int qtd, i;
		Cliente **c;

		printf("\n%s\nDigite o nome do novo registro: ", LINHA);
		scanf("%s", nomeDest);

		FILE *f1 = fopen(nomeDest, "wb");

		printf("\n%s\nDigite a quantidade de elementos: ", LINHA);
		scanf("%d", &qtd);

		c = (Cliente **)malloc(sizeof(Cliente *)*qtd);

		printf("%s", CLEAR);
		for (i = 0; i < qtd; i++)
		{
			c[i] = (Cliente *)malloc(sizeof(Cliente));
			printf("Digite o código do cliente: ");
			scanf("%d", &c[i]->cod);
			printf("%s\nDigite o nome do cliente: ", LINHA);
			scanf("%s", c[i]->nome);
			printf("%s\nDigite a data de nascimento do cliente: ", LINHA);
			scanf("%s", c[i]->data_n);
			printf("%s\n%s\n", LINHA, LINHA);
			salva(c[i], f1);
		}
		printf("%s", CLEAR);
		free(c);
		fclose(f1);
	}
}

void imprime_reg(char *nome)
{
	FILE *file = fopen(nome, "rb");
	if (file == NULL)
		printf("Arquivo não existe!!\n");
	else
	{
		imprimeArq(file);
	}
}

void modificaReg()
{
	int escolha = -1;
	// char nomeArq[100];
	while(escolha != 0)
	{
		printf("%sEscolha a modificação:\n%s\n", CLEAR, LINHA);
		printf("1- Adicionar elemento\n");
		printf("2- Modificar Registro\n");
		printf("3- Deletar Registro\n");
        printf("4- Deletar Partições\n");
        printf("0- Voltar\n");
		printf("%s\nOpção: ", LINHA);
		scanf("%d", &escolha);

		switch (escolha)
		{
		case 1:
			{
				char nomeArq[100];
				Cliente *aux = (Cliente *)malloc(sizeof(Cliente));
				FILE *f;
				
				printf("%sDigite o nome do arquivo: ", CLEAR);
				scanf("%s", nomeArq);
				f = fopen(nomeArq, "ab");

				printf("\n%s\nDigite o código do Cliente: ", LINHA);
				scanf(" %d", &aux->cod);
				printf("%s\nDigite o nome do Cliente: ", LINHA);
				scanf("%s", aux->nome);
				printf("%s\nDigite o data de nascimento do Cliente: ", LINHA);
				scanf("%s", aux->data_n);

				salva(aux, f);
				fclose(f);
				free(aux);

				break;
			}
		case 2:
			{
                 printf("Ainda não está pronto!\n\nDigite -1 para voltar: ");
				while (escolha != -1)
				{
					scanf("%d", &escolha);
				}
				printf("%s", CLEAR);
			}
		case 3:
			{
                char nome[40];
                char comando[50];
                printf("%sDigite o nome do registro a ser removido: ", CLEAR);
                scanf("%s", nome);
                sprintf(comando ,"rm -r %s", nome);
                system(comando);
                printf("\n\nDigite -1 para voltar: ");
				while (escolha != -1)
				{
					scanf("%d", &escolha);
				}
				printf("%s", CLEAR);
				break;
			}
        case 4:
            {
                int cont = 1;
                char nome[40];
                char comando[50];
                FILE *aux;
                sprintf(nome, "part%d.dat", cont);
                do
                {
                    aux = fopen(nome, "rb");
                    if (aux != NULL)
                    {
                        fclose(aux);
                        sprintf(comando, "rm -r %s", nome);
                        system(comando);
                        cont++;
                        sprintf(nome, "part%d.dat", cont);
                    }

                } while (aux != NULL);
                printf("\n\nDigite -1 para voltar: ");
				while (escolha != -1)
				{
					scanf("%d", &escolha);
				}
				printf("%s", CLEAR);
				break;
                
            }
		}

	}

}