#include <stdio.h>

int main()
{
	int a = 10;
	int* c;
	
	/*O conteudo da vari�vel a*/
	printf("Conteudo: %d\n", a);
	
	c = &a;
	(*c) = 20;
	
	/*o conteudo da variavel a*/
	printf("Conteudo: %d\n", a);
	
	return (0);
}