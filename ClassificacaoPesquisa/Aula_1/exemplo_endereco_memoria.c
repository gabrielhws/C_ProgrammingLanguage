#include <stdio.h>

int main()
{
	int a = 10;
	//Conteudo da vari�vel a. 
	printf("Conteudo: %d\n", a);
	
	/*O endere�o da vari�vel a (int) */
	printf("Endere�o: %d\n: ", &a);
	
	/*O endere�o da variavel a (hexa)*/
	printf("Endere�o: %x\n", &a);
	
	return (0);
}