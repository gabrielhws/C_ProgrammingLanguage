//-----------------------------------------------------------------
// Classifica��o e Pesquisa
//
// T�tulo: Algorito de Sele��o
// Assunto: Orden��o interna, algoritmo Sele��o 
//
// Aluno(s):  Gabriel Ferreira RA: 2504108449
// nome do aluno 000000
//
//Data: 13/08/2013
//-----------------------------------------------------------------


#include   <limits.h>
#include <stdio.h>
#define MaxTam 10  /*Constante*/

typedef long ChaveTipo;  /*defini��o do tipo de chave long*/
typedef struct Item { /*defini��o da estrutura Item que cont�m uma chave*/
  ChaveTipo Chave;
  /* outros componentes */
} Item;

typedef int Indice; /*defini��o do Indice do tipo int*/
typedef Item Vetor[MaxTam + 1];
Vetor A;
Indice i, n;
FILE *arq; 

void Selecao(Item *A, Indice *n)
{ Indice i, j, Min;
  Item x;
  for (i = 1; i <= *n - 1; i++) 
    { Min = i;
      for (j = i + 1; j <= *n; j++)
	{ 
		if (A[j].Chave < A[Min].Chave) 
		{
			Min = j;
	      		x = A[Min]; 
			A[Min] = A[i]; 
			A[i] = x;
		}
	}
    }
}

void Imprime(Item *V, Indice *n)
{ 
	for (i = 1; i <= *n; i++)
	    printf("%d ", V[i].Chave);  printf("\n");
}

int main(int argc, char *argv[]){ 

  n = MaxTam;   /*Tamanho do arranjo a ser ordenado*/
 
  arq = fopen("vetor.txt","r");
  printf("Vetor a ser pesquisado:\n\n");
  for (i = 1; i <= n; i++) {
    fscanf(arq, "%d", &A[i].Chave);
    printf("%10d\n", A[i].Chave);
  }
	 
  printf("Desordenado : ");
  Imprime(A, &n);
  printf("Selecao   \n");
  Selecao(A, &n);
  printf("Ordenado : ");
  Imprime(A, &n);
  
  system("PAUSE");
  return 0;
}
