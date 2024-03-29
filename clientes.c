#include "clientes.h"

Cliente *criaCliente(int cod, char *nome, char *data)
{
    Cliente *c = (Cliente *)malloc(sizeof(Cliente));

	if (c) memset(c, 0, sizeof(Cliente));

	c->cod = cod;
	strcpy(c->nome, nome);
	strcpy(c->data_n, data);
	return c;
}

void salva(Cliente *p, FILE *out)
{
    fwrite(&p->cod, sizeof(int), 1, out);
    fwrite(p->nome, sizeof(char), sizeof(p->nome), out);
    fwrite(p->data_n, sizeof(char), sizeof(p->data_n), out);

    free(p);
    // return NULL;
}
Cliente *le(FILE *in)
{
    Cliente *c = (Cliente *)malloc(sizeof(Cliente));
    if (0 >= fread(&c->cod, sizeof(int), 1, in))
    {
        free(c);
        printf("sefudeu\n");
        return NULL;
    }
    fread(c->nome, sizeof(char), sizeof(c->nome), in);
    fread(c->data_n, sizeof(char), sizeof(c->data_n), in);

    return c;
}

void le_tudo(FILE *in){
    Cliente *c = (Cliente *)malloc(sizeof(Cliente));
    int bytes_lidos = fread(&c->cod, sizeof(int), 1, in);
    printf("Bytes lidos = %ld\n", fread(&c->cod, sizeof(int), 1, in));
    while(1){
        if(bytes_lidos > 0){  
            printf("No if\n");
            fread(c->nome, sizeof(char), sizeof(c->nome), in);
            fread(c->data_n, sizeof(char), sizeof(c->data_n), in);
            printf("\n\nCliente:\nCod: %d\nNome: %s\nData_n:%s\n", (c->cod), c->nome, c->data_n);
            bytes_lidos = fread(&c->cod, sizeof(int), 1, in);
        }
    }
}

void imprime(Cliente *p)
{
    //PERSONALIZEM, ISSO É SÓ O BÁSICO
    printf("%d %s %s\n", p->cod, p->nome, p->data_n);
}
int tamanho()
{
    return sizeof(int)
    + (sizeof(char)* 50)
    + (sizeof(char)* 20);
}
