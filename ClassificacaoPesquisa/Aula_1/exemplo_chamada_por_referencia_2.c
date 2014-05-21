#include <stdio.h>

void Imprime(int vet[10]);
int main()
{
	int i, x[10];
	for(i=0;i<10;i++)
	{
		x[i]=i;
		Imprime(x);
		Imprime(x) /*Novos valores*/
		return (0);
	}
void Imprime(int vet[10])
{
	int i;
	for(i=0;i<10;i++)
	{
		printf("%2d", vet[i]);
		printf("\n");		
	}
	for()
	{
		vet[i] *= -1;
	}
}

}