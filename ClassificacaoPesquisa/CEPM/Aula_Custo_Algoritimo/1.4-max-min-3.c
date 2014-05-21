#include <stdio.h>
#define n   10

typedef int Vetor[n];
Vetor A;
FILE *arq;
int i, Max, Min;

void MaxMin3(Vetor A, int *Max, int *Min)
{ int i, FimDoAnel;
  if ((n & 1) > 0)
  { A[n] = A[n - 1]; FimDoAnel = n;
  }
  else FimDoAnel = n - 1;
  if (A[0] > A[1])
  { *Max = A[0]; *Min = A[1]; }
  else { *Max = A[1]; *Min = A[0];}
  i = 3;
  while (i <= FimDoAnel)
    { if (A[i - 1] > A[i])
      { if (A[i - 1] > *Max) *Max = A[i - 1];
        if (A[i] < *Min) *Min = A[i];
      }
      else { if (A[i - 1] < *Min) *Min = A[i - 1];
             if (A[i] > *Max) *Max = A[i];
           }
      i += 2;
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
  MaxMin3(A,&Max,&Min);
  printf("\nChave de maior valor = %d\n", Max);
  printf("Chave de menor valor = %d\n", Min);
  fclose(arq);
  return (0);
}  /* maxmin */
