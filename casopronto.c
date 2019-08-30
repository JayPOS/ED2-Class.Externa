
void casoPronto()
{
	FILE* p;
	p = fopen("arquivo.dat", "w+b");
	int aux;
	char nome[15];

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
	ord(p);
	fclose(p);

	for (int i = 1; i < 6; ++i){
		FILE *part = fopen(gera_nome(nome, i), "rb");
		printf("ARQUIVO %d\n", i);
		imprimeArq(part);
		fclose(part);
	}
}