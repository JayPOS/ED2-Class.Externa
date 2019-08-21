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
}
Cliente *le(FILE *in)
{
    Cliente *c = (Cliente *)malloc(sizeof(Cliente));
    if (0 >= fread(&c->cod, sizeof(int), 1, in))
    {
        free(c);
        return NULL;
    }
    fread(c->nome, sizeof(char), sizeof(c->nome), in);
    fread(c->data_n, sizeof(char), sizeof(c->data_n), in);

    return c;

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