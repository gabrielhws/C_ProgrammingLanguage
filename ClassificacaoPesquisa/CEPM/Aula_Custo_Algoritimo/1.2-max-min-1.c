#include <stdio.h>
#define n  10

typedef int Vetor[n];

Vetor A;
FILE *arq;
int i, Max, Min;

void MaxMin1(Vetor A, int *Max, int *Min)
{ int i;
  *Max = A[0]; *Min = A[0];
  for (i = 1; i < n; i++)
    { if (A[i] > *Max) *Max = A[i];
      if (A[i] < *Min) *Min = A[i];
    }
}

int main()
{
  arq = fopen("vetor.txt","r");
  printf("Vetor a ser pesquisado:\n\n");
  for (i = 1; i <= n; i++)
    {
    fscanf(arq, "%d", &A[i-1]);
    printf("%10d\n", A[i-1]);
    }
  MaxMin1( A, &Max, &Min);
  printf("\nChave de maior valor = %d\n", Max);
  printf("Chave de menor valor = %d\n", Min);
  fclose(arq);
  return(0);
}
