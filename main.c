// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include "clientes.h"
#include "aux.c"
#include "inter.c"

#define LINHA "---------------------------------------"
#define CLEAR "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"

#define ARQUIVO 1
#define TERMINAL 2

//	PRAZO 3 DE SET!!!

//FUNÇÃO LOCALIZA A MENOR CHAVE


int substituicao(FILE* in)
{
	int min, arq = 1, chave_ant = -1, ice = 0;
	Memoria v[MAX];
	for (int i = 0; i < MAX; ++i){ //Carrega as n primeiras chaves
		v[i].p = le(in);
		v[i].congelado = 0;
	}

	FILE *part = fopen(gera_nome(arq), "w+b");
	min = menor(v, MAX);
	do{
		if(v[min].p->cod < chave_ant){ //verifica se a chave buscada é menor que a anterior caso sim congela
			v[min].congelado = 1;
			ice++;
		}
		if(ice == MAX){ // verifica se o vetor está todo congelado
			arq++;
			fclose(part);
			part = fopen(gera_nome(arq), "w+b");
			for (int i = 0; i < MAX; i++)
				v[i].congelado = 0;
			ice = 0;
		}
		min = menor(v, MAX);
		chave_ant = v[min].p->cod;
		salva(v[min].p, part);
	}while((v[min].p = le(in)) != NULL); //lê até o final do arquivo
	

	for (int i = 0; i < MAX-(ice+1); ++i){ //grava os registros não congelados no arquivo atual
		min = menor(v, MAX);
		salva(v[min].p, part);
		v[min].p = NULL;
	}

	for (int i = 0; i < MAX; ++i) //descongela tds q sobraram na memoria
		v[i].congelado = 0;

	if(vazio(v) != 1){
		arq++;
		fclose(part);
		FILE *part = fopen(gera_nome(arq), "w+b");
		for (int i = 0; vazio(v) != 1; ++i){ //grava tds q sobraram na memoria congelados em um novo arquivo
			min = menor(v, MAX);
			salva(v[min].p, part);
			v[min].p = NULL;
		}
	}
	fclose(part);
	return arq;
}

void casoPronto(int *part_num)
{
	FILE* p;
	p = fopen("arquivo.dat", "w+b");
	
	salva(criaCliente(29, "Bárbara", "19/05/2000"), p);
	salva(criaCliente(14, "João", "21/07/2000"), p);
	salva(criaCliente(76, "Natã", "23/09/1998"), p);
	salva(criaCliente(75, "Alana", "25/08/1976"), p);
	salva(criaCliente(59, "Jefferson", "14/07/1878"), p);
	salva(criaCliente(6, "Bárbara", "19/05/2000"), p);
	salva(criaCliente(7, "João", "21/07/2000"), p);
	salva(criaCliente(74, "Natã", "23/09/1998"), p);
	salva(criaCliente(48, "Alana", "25/08/1976"), p);
	salva(criaCliente(46, "Jefferson", "14/07/1878"), p);
	salva(criaCliente(10, "Bárbara", "19/05/2000"), p);
	salva(criaCliente(18, "João", "21/07/2000"), p);
	salva(criaCliente(56, "Natã", "23/09/1998"), p);
	salva(criaCliente(20, "Alana", "25/08/1976"), p);
	salva(criaCliente(26, "Jefferson", "14/07/1878"), p);
	salva(criaCliente(4, "Bárbara", "19/05/2000"), p);
	salva(criaCliente(21, "João", "21/07/2000"), p);
	salva(criaCliente(65, "Natã", "23/09/1998"), p);
	salva(criaCliente(22, "Alana", "25/08/1976"), p);
	salva(criaCliente(49, "Jefferson", "14/07/1878"), p);
	salva(criaCliente(11, "Bárbara", "19/05/2000"), p);
	salva(criaCliente(16, "João", "21/07/2000"), p);
	salva(criaCliente(8, "Natã", "23/09/1998"), p);
	salva(criaCliente(15, "Alana", "25/08/1976"), p);
	salva(criaCliente(5, "Jefferson", "14/07/1878"), p);
	salva(criaCliente(19, "Bárbara", "19/05/2000"), p);
	salva(criaCliente(50, "João", "21/07/2000"), p);
	salva(criaCliente(55, "Natã", "23/09/1998"), p);
	salva(criaCliente(25, "Alana", "25/08/1976"), p);
	salva(criaCliente(66, "Jefferson", "14/07/1878"), p);
	salva(criaCliente(57, "Bárbara", "19/05/2000"), p);
	salva(criaCliente(77, "João", "21/07/2000"), p);
	salva(criaCliente(12, "Natã", "23/09/1998"), p);
	salva(criaCliente(30, "Alana", "25/08/1976"), p);
	salva(criaCliente(17, "Jefferson", "14/07/1878"), p);
	salva(criaCliente(9, "Bárbara", "19/05/2000"), p);
	salva(criaCliente(54, "João", "21/07/2000"), p);
	salva(criaCliente(78, "Natã", "23/09/1998"), p);
	salva(criaCliente(43, "Alana", "25/08/1976"), p);
	salva(criaCliente(38, "Jefferson", "14/07/1878"), p);
	salva(criaCliente(51, "Bárbara", "19/05/2000"), p);
	salva(criaCliente(32, "João", "21/07/2000"), p);
	salva(criaCliente(58, "Natã", "23/09/1998"), p);
	salva(criaCliente(13, "Alana", "25/08/1976"), p);
	salva(criaCliente(73, "Jefferson", "14/07/1878"), p);
	salva(criaCliente(79, "Bárbara", "19/05/2000"), p);
	salva(criaCliente(27, "João", "21/07/2000"), p);
	salva(criaCliente(1, "Natã", "23/09/1998"), p);
	salva(criaCliente(3, "Alana", "25/08/1976"), p);
	salva(criaCliente(60, "Jefferson", "14/07/1878"), p);
	salva(criaCliente(36, "Bárbara", "19/05/2000"), p);
	salva(criaCliente(47, "João", "21/07/2000"), p);
	salva(criaCliente(31, "Natã", "23/09/1998"), p);
	salva(criaCliente(80, "Alana", "25/08/1976"), p);

	rewind(p);
	*part_num = substituicao(p);
	
	rewind(p);
	imprimeArq(p);

	for (int i = 1; i < 14; ++i){
		FILE *part = fopen(gera_nome(i), "rb");
		printf("\n\n%s\nARQUIVO %d\n%s\n", LINHA, i, LINHA);
		imprimeArq(part);
		fclose(part);
	}
	fclose(p);
}

void menu()
{
	int escolha = -1;
	int tipo;
	int part_num = 0;
	char nome[100];
	while(escolha != 0)
	{
		printf("\n%s\n\n1- Criar Registro\n", LINHA);
		printf("2- Imprimir Registro\n");
		printf("3- Modificar Arquivos\n");
		printf("4- Rodar Caso Pronto\n");
		printf("5- Rodar Algoritmo\n");
		printf("6- Intercalar\n");
		printf("0- Sair\n\n%s\n", LINHA);
		printf("Opção: ");
		if(!scanf("%d", &escolha))
			break;

		switch(escolha)
		{
			case 1:
				printf("%s", CLEAR);
				printf("1- Arquivo\n");
				printf("2- Entrada Padrão\n");
				printf("\n%s\nOpção: ", LINHA);
				scanf("%d", &tipo);
				criar_registro(tipo);
				break;
			case 2:
				printf("%s", CLEAR);
				printf("Digite o nome do arquivo que contêm o registro: ");
				scanf("%s", nome);
				printf("\n\n");
				imprime_reg(nome);
				printf("\n\nDigite -1 para voltar: ");
				while (escolha != -1)
				{
					scanf("%d", &escolha);
				}
				printf("%s", CLEAR);
				break;
			case 3:
				{
					// printf("%sAinda não está pronto!\n\n", CLEAR);
					modificaReg(&part_num);
					printf("%s", CLEAR);
				}
				break;
			case 4:
				printf("%s", CLEAR);
				casoPronto(&part_num);
				printf("\n\nDigite -1 para voltar: ");
				while (escolha != -1)
				{
					scanf("%d", &escolha);
				}
				printf("%s", CLEAR);
				break;
			case 5:
				{
					int i;
					char nome[100];
					FILE *file;

					printf("%sDigite o nome do registro: ", CLEAR);
					scanf("%s", nome);

					file = fopen(nome, "rb");
					if (file == NULL)
					{
						printf("Arquivo não pode ser aberto!\n");
						printf("\n\nDigite -1 para voltar: ");
						while (escolha != -1)
						{
							scanf("%d", &escolha);
						}
					}
					else
					{
						part_num = substituicao(file);
						for (i = 1; i <= part_num; i++)
						{
							printf("\n\n%s\nARQUIVO %d\n%s\n", LINHA, i, LINHA);
							imprime_reg(gera_nome(i));
						}
						printf("\n\nDigite -1 para voltar: ");
						while (escolha != -1)
						{
							scanf("%d", &escolha);
						}
					}
					break;
				}
			case 6:
			{
				int i;
				char nome[100];
				FILE *file;

				printf("%sDigite o nome do arquivo para intercalar (partições devem existir): ", CLEAR);
				scanf("%s", nome);

				file = fopen(nome, "wb");
				if (file == NULL)
				{
					printf("Arquivo não pode ser aberto!\n");
					printf("\n\nDigite -1 para voltar: ");
					while (escolha != -1)
					{
						scanf("%d", &escolha);
					}
				}
				else
				{
					intercalar(part_num);
					printf("\n\nDigite -1 para voltar: ");
					while (escolha != -1)
					{
						scanf("%d", &escolha);
					}
				}
				
			}
		}
	}
}
int main()
{
	// casoPronto();
	menu();
	return 0;
}
