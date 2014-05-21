//-----------------------------------------------------------------
// Classificação e Pesquisa
//
// Título: Algorito HeapSort
// Assunto: Ordenção interna, HeapSort
//
// Aluno(s):  RA:
// nome do aluno 000000
//
//Data: 13/08/2013
//-----------------------------------------------------------------


#include   <limits.h>
#include <stdio.h>
#define MaxTam          10

typedef long ChaveTipo;
typedef struct Item {
  ChaveTipo Chave;
  /* outros componentes */
} Item;

typedef int Indice;
typedef Item Vetor[MaxTam + 1];
Vetor A;
Indice i, n;
FILE *arq;

void Refaz(Indice Esq, Indice Dir, Item *A)
{ Indice i = Esq;
  int j;
  Item x;
  j = i * 2;
  x = A[i];
  while (j <= Dir) 
    { if (j < Dir) 
      { if (A[j].Chave < A[j+1].Chave)
	j++;
      }
      if (x.Chave >= A[j].Chave) goto L999;
      A[i] = A[j];
      i = j; j = i * 2;
    }
  L999: A[i] = x;
}
void Constroi(Item *A, Indice *n)
{ Indice Esq;
  Esq = *n / 2 + 1;
  while (Esq > 1) 
    { Esq--;
      Refaz(Esq, *n, A);
    }
}

void Heapsort(Item *A, Indice *n)
{ Indice Esq, Dir;
  Item x;
  Constroi(A, n);   /* constroi o heap */
  Esq = 1; Dir = *n;
  while (Dir > 1) 
    { /* ordena o vetor */
      x = A[1]; A[1] = A[Dir]; A[Dir] = x;
      Dir--;
      Refaz(Esq, Dir, A);
    }
}

void Imprime(Item *V, Indice *n)
{ for (i = 1; i <= *n; i++)
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
  printf("HeapSort   \n");
  Heapsort(A, &n);
  printf("Ordenado : ");
  Imprime(A, &n);
   
  fclose(arq);  
  system("PAUSE");
  return 0;
}
