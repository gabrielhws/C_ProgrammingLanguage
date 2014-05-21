#include <stdio.h>

int main()
{
	int a=10;
	int b;
	
	b=&a;
	
	/* O conteudo da varavel b*/
	printf("O conteudo: %d\n", b);
	
	/*O endereco da variavel b (hexa)*/
	printf("Endereço %x\d", &b);
	
	return (0);
}