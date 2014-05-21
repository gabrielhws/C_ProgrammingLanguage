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
#include <sys/time.h>
#include <ctype.h>
#include <sys/resource.h>

#define MaxTam          10

// prototype
double calculate(const struct rusage *b, const struct rusage *a);
// benchmarks
double ti_load = 0.0, ti_sort = 0.0;

// structs for timing data
struct rusage before, after;
    

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

void Selecao(Item *A, Indice *n)
{ Indice i, j, Min;
  Item x;
  for (i = 1; i <= *n - 1; i++) 
    { Min = i;
      for (j = i + 1; j <= *n; j++) if (A[j].Chave < A[Min].Chave) Min = j;
      x = A[Min]; A[Min] = A[i]; A[i] = x;
    }
}

void Imprime(Item *V, Indice *n)
{ for (i = 1; i <= *n; i++)
    printf("%d ", V[i].Chave);  printf("\n");
}

int main(int argc, char *argv[]){ 

  n = MaxTam;   /*Tamanho do arranjo a ser ordenado*/
  
  // load File
  getrusage(RUSAGE_SELF, &before);
    
  arq = fopen("vetor.txt","r");
  printf("Vetor a ser pesquisado:\n\n");
  for (i = 1; i <= n; i++) {
    fscanf(arq, "%d", &A[i].Chave);
    printf("%10d\n", A[i].Chave);
  }
  getrusage(RUSAGE_SELF, &after);	 
  
  // calculate time to load
  ti_load = calculate(&before, &after);
  
  
  printf("Desordenado : ");
  Imprime(A, &n);
  printf("Selecao   \n");
  // Sort
  getrusage(RUSAGE_SELF, &before);
  Selecao(A, &n);
  getrusage(RUSAGE_SELF, &after);
  printf("Ordenado : ");
  Imprime(A, &n);
  // calculate time to sort
  ti_sort = calculate(&before, &after);
  
    // report benchmarks
    printf("TIME IN load:         %.2f\n", ti_load);
    printf("TIME IN sort:        %.2f\n", ti_sort);
    printf("TIME IN TOTAL:        %.2f\n\n", 
     ti_load + ti_sort);
  
  system("PAUSE");
  return 0;
}

/*
 * Returns number of seconds between b and a.
 */

double
calculate(const struct rusage *b, const struct rusage *a)
{
    if (b == NULL || a == NULL)
        return 0;
    else
        return ((((a->ru_utime.tv_sec * 1000000 + a->ru_utime.tv_usec) -
                 (b->ru_utime.tv_sec * 1000000 + b->ru_utime.tv_usec)) +
                ((a->ru_stime.tv_sec * 1000000 + a->ru_stime.tv_usec) -
                 (b->ru_stime.tv_sec * 1000000 + b->ru_stime.tv_usec)))
                / 1000000.0);
}


/*
double ti_load = 0.0, ti_sort = 0.0;

#include<time.h>
time_t inicio, fim;
int t;
inicio = time(NULL);]
fim = time(NULL); //Isto deve ficar no final
ti_load = difftime(fim, inicio);
fprintf(stdout, "O tempo de execucao em segundos é %.2f\n", ti_load);
*/
