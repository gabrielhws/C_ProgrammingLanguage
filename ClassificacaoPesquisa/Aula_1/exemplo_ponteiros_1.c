#include <stdio.h>

int main()
{
	int a = 10;
	int* c;
	
	c= &a;
	
	/*O conteudo da variavel c (hexa)*/
	printf("Conteudo: %x\n", c);
	
	return(0);
	
	/* Ponteiros são variáveis que armazenam em seu conteúdo apenas
	 endereço (hexa)*/
}