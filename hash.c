#include <stdio.h>
#include <stdlib.h>

void initHash(FILE* a, int tam){
	int x = -1;
	for (int i = 0; i < tam; ++i){
		fwrite(&x, sizeof(int), 1, a);
	}
}

int funcHash(int num, int tam){
	return (num%tam);
}

int insereHash_linear(FILE* h, FILE* c, int ct, int tam, int qtd){
	int chave = funcHash(ct, tam), aux = 0;
	for (int i = 0; i < tam; ++i){
		chave = funcHash(chave+i, tam);
		fseek(h, chave*sizeof(int), SEEK_SET);
		fread(&aux, sizeof(int), 1, h);
		if(aux == -1){
			fseek(h, chave*sizeof(int), SEEK_SET);
			fwrite(&qtd, sizeof(int), 1, h);
			fwrite(&ct, sizeof(int), 1, c);
			return 1;
		}
	}
	return 0;
}

int insereHash_quadratica(FILE* h, FILE* c, int ct, int tam, int qtd){
	int chave = funcHash(ct, tam), aux = 0;
	for (int i = 0; aux != -1; ++i){
		chave = funcHash(chave+(2*i)+(5*i*i), tam);
		fseek(h, chave*sizeof(int), SEEK_SET);
		fread(&aux, sizeof(int), 1, h);
		if(aux == -1){
			fseek(h, chave*sizeof(int), SEEK_SET);
			fwrite(&qtd, sizeof(int), 1, h);
			fwrite(&ct, sizeof(int), 1, c);
			return 1;
		}
	}
	return 0;
}

int insereHash_dupla(FILE* h, FILE* c, int ct, int tam, int qtd){
	int chave = funcHash(ct, tam), aux = 0, chave2 = funcHash(chave, tam);;
	for (int i = 0; i < aux != -1; ++i){
		chave = funcHash(chave+(i*chave2), tam);
		fseek(h, chave*sizeof(int), SEEK_SET);
		fread(&aux, sizeof(int), 1, h);
		if(aux == -1){
			fseek(h, chave*sizeof(int), SEEK_SET);
			fwrite(&qtd, sizeof(int), 1, h);
			fwrite(&ct, sizeof(int), 1, c);
			return 1;
		}
	}
	return 0;
}

void imprimeHash(FILE* h, FILE* c){
	int x;
	Cliente* clt;
	rewind(h); rewind(c);
	while(fread(&x, sizeof(int), 1, h) == 1){
		if(x != -1){
			printf("Posi Hash: %d\n", x);
		}
	}
}

int main(){
	int p = 0, tamHash = 10, qtd = 0, x;
	FILE* hash;
	FILE* registros;

	hash = fopen("hash.dat", "w+b");
	registros = fopen("clientes.dat", "w+b");

	initHash(hash, tamHash);

	
	srand(1);
	
	for (int i = 0; i < 10; ++i){
		x = rand() % 10;
		if(insereHash_quadratica(hash, registros, x, tamHash, qtd) == 1)
			qtd++;
		printf("%d ", x);
	}
	printf("\n");
	rewind(hash);
	rewind(registros);
	int i = 0;
	while(fread(&x, sizeof(int), 1, hash) == 1){
		printf("posi (%d): %d - ", i, x);
		fread(&x, sizeof(int), 1, registros);
		printf("%d\n", x);
		i++;
	}

	return 0;
}