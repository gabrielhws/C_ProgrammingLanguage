#include <stdio.h>

int main()
{
	int a = 10;
	int* c;
	
	c= &a;
	
	/*O conteudo da variavel c (hexa)*/
	printf("Conteudo: %x\n", c);
	
	return(0);
	
	/* Ponteiros s�o vari�veis que armazenam em seu conte�do apenas
	 endere�o (hexa)*/
}