#include <stdio.h>

int main()
{
	int a = 10;
	//Conteudo da variável a. 
	printf("Conteudo: %d\n", a);
	
	/*O endereço da variável a (int) */
	printf("Endereço: %d\n: ", &a);
	
	/*O endereço da variavel a (hexa)*/
	printf("Endereço: %x\n", &a);
	
	return (0);
}