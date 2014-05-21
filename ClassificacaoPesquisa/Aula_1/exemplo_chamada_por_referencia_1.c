#include <stdio.h>

void Imprime_Linhas(int *n);
int main()
{
	int a = 5;
	Imprime_linhas(&a);
	printf("\Programa Teste");
	Imprime_Linhas(&a);
	return (0);
}
void Imprime_Linhas (int* n)
{
	int i;
	for(i=0;i<(*n); i++)
	{
		printf("\n ------------------\n");
		(*n) = 1;
	}
}