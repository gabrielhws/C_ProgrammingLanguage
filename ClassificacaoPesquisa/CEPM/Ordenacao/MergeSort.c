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

void Merge(Item *A, Indice n) {
         
    Indice mid;
    Indice i, j, k;
    Item *tmp;
    tmp = (Item*) malloc((n+1) * sizeof(Item));
    if (tmp == NULL) {
        exit(1);
    }
    mid = n / 2;
    i = 0;
    j = mid;
    k = 0;
    while (i < mid && j <= n) {
        if (A[i].Chave < A[j].Chave){
           tmp[k] = A[i++];
        }
        else{
             tmp[k] = A[j++];
        }
        ++k;
    }
    if (i == mid){
        while (j <= n) {
            tmp[k++] = A[j++];
        }
    }
    else {
        while (i < mid) {
            tmp[k++] = A[i++];
        }
    }
    
    for (i = 0; i <= n; ++i) {
        A[i] = tmp[i];
    }
    free(tmp);
}
 
void MergeSort(Item *A, Indice n) {  
  int mid1,mid2;
  if (n > 1) {
    mid1 = n / 2;
    MergeSort(A, mid1);
    mid2 = n - (n / 2);
    MergeSort(A + (mid1), mid2);
    Merge(A, n);
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
  printf("MergeSort   \n");
  MergeSort(A, n);
  printf("Ordenado : ");
  Imprime(A, &n);
   
  fclose(arq);  
  system("PAUSE");
  return 0;
}
