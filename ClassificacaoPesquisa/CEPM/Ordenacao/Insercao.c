//-----------------------------------------------------------------
// Classificação e Pesquisa
//
// Título: Algorito de Seleção
// Assunto: Ordenção interna, algoritmo Seleção 
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

void Insercao(Item *A, Indice *n)
{ Indice i, j;
  Item x;
  for (i = 2; i <= *n; i++) 
    { x = A[i];
      j = i - 1;
      A[0] = x;   /* sentinela */
      while (x.Chave < A[j].Chave) 
        { A[j+1] = A[j];
          j--;
        }
      A[j+1] = x;
    } 
}
void Shellsort(Item *A, Indice *n)
{ int i, j;
  int h = 1;
  Item x;
  do h = h * 3 + 1; while (h < *n);
  do 
    { h /= 3;
      for (i = h + 1; i <= *n; i++) 
        { x = A[i];
          j = i;
          while (A[j - h].Chave > x.Chave) 
            { A[j] = A[j - h];
	      j -= h;
	      if (j <= h) goto L999;
	    }
          L999: A[j] = x;
	}
    } while (h != 1);
}
void Particao(Indice Esq, Indice Dir, Indice *i, Indice *j, Item *A)

{ Item x, w;
  *i = Esq; *j = Dir;
  x = A[(*i + *j) / 2];   /* obtem o pivo x */
  do 
    { while (x.Chave > A[*i].Chave) (*i)++;
      while (x.Chave < A[*j].Chave) (*j)--;
      if (*i <= *j) 
      { w = A[*i]; A[*i] = A[*j]; A[*j] = w;
        (*i)++; (*j)--;
      }
    } while (*i <= *j);
}

void Ordena(Indice Esq, Indice Dir, Item *A)
{ Indice i, j;
  Particao(Esq, Dir, &i, &j, A);
  if (Esq < j) Ordena(Esq, j, A);
  if (i < Dir) Ordena(i, Dir, A);
}
void QuickSort(Item *A, Indice *n)
{ Ordena(1, *n, A);
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
  printf("Insercao   \n");
  Insercao(A, &n);
  printf("Ordenado : ");
  Imprime(A, &n);
   
  fclose(arq);  
  system("PAUSE");
  return 0;
}
