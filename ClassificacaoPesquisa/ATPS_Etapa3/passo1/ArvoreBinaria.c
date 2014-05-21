#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <time.h>

#ifdef _WIN32
#define CLEAR "cls"
#else //In any other OS
#define CLEAR "clear"
#endif

#define WORDS "words"

#define MaxTam  10000000
#define LENGTH 45

time_t inicio, fim;
double ti_load = 0.0, ti_order = 0.0;

typedef char TipoChave[LENGTH];

typedef struct Registro {
  TipoChave Chave;
  /* outros componentes */
} Registro;

FILE *arq;
typedef Registro Vetor[MaxTam + 1];
Vetor R;

typedef struct No * Apontador;
typedef struct No {
  Registro Reg;
  Apontador Esq, Dir;
} No;

typedef Apontador TipoDicionario;


void Insere(Registro x, Apontador *p, int *comparacoes)
{ if (*p == NULL) 
  { *p = (Apontador)malloc(sizeof(No));
    (*p)->Reg = x; (*p)->Esq = NULL; (*p)->Dir = NULL;
    return;
  }
	(*comparacoes)++; // Comparacoes
  if (strcmp(x.Chave, (*p)->Reg.Chave) < 0) 
  { 
		Insere(x, &(*p)->Esq, comparacoes); 
		return; 
	}
	(*comparacoes)++;  // Comparacoes
  if (strcmp(x.Chave, (*p)->Reg.Chave) > 0)
  	Insere(x, &(*p)->Dir, comparacoes);
  else
    printf("Erro : Registro ja existe na arvore\n");
} 


void Inicializa(Apontador *Dicionario)
{ *Dicionario = NULL;
}



void TestaI(No *p, TipoChave pai)
{ 
	if (p == NULL)
  	return;
  if (p->Esq != NULL) 
  { if (strcmp(p->Reg.Chave, p->Esq->Reg.Chave) < 0) 
    { printf("Erro: Pai %s menor que filho a esquerda %s\n", p->Reg.Chave, p->Esq->Reg.Chave);
      exit(1);
    }
  }
  if (p->Dir != NULL) 
  { 
		if (strcmp(p->Reg.Chave, p->Dir->Reg.Chave) > 0) 
    { printf("Erro: Pai %s maior que filho a direita %s\n",  p->Reg.Chave, p->Dir->Reg.Chave);
    	exit(1);
    }
  }
  TestaI(p->Esq, p->Reg.Chave);
  TestaI(p->Dir, p->Reg.Chave);
}


void Testa(No *p)
{ 
	if (p != NULL)
	  TestaI(p, p->Reg.Chave);
}

double rand0a1() {
  double resultado=  (double) rand()/ RAND_MAX; /* Dividir pelo maior inteiro */
  if(resultado>1.0) resultado = 1.0;
  return resultado;
}

void Permut(Registro *A, int n, int *trocas) {
  int i,j;
  TipoChave b;
  for(i = n; i>0; i --) 
    { j = (i * rand0a1());
			(*trocas)++;   // Trocas
      strcpy(b, A[i].Chave);
			(*trocas)++;   // Trocas
      strcpy(A[i].Chave, A[j].Chave);
			(*trocas)++;   // Trocas
      strcpy(A[j].Chave, b);
    }
}

void NotaText(Apontador p)
{ if (p == NULL){
       printf("<>");
     return;
  }
  printf("<%s", p->Reg.Chave);
  NotaText(p->Esq);
  NotaText(p->Dir);
  printf(">");
} 


void loadFile(char *file , Registro *A, int *n){
    FILE *fp = fopen(file, "r");
    if (fp == NULL)
    {
        printf("Could not open %s.\n", file);
        exit(1);
    }
    int index = 0, misspellings = 0, words = 0;
    char word[LENGTH+1];
    int c;
    for (c = fgetc(fp); c != EOF; c = fgetc(fp))
    {   if (isalpha(c) || (c == '\'' && index > 0))
        {
            word[index] = c;
            index++;
            if (index > LENGTH)
            {
                while ((c = fgetc(fp)) != EOF && isalpha(c));
                index = 0;
            }
        }

        else if (isdigit(c))
        {
            while ((c = fgetc(fp)) != EOF && isalnum(c));

            index = 0;
        }

        else if (index > 0)
        {
            word[index] = '\0';

            if(++(*n) < MaxTam-1){
    	    		strncpy(A[*n].Chave, word,index+1); 
			    	}
            index = 0;
        }
    }
    
    if (ferror(fp))
    {
        fclose(fp);
        printf("Error reading %s.\n", file);
        exit(2);
    }
   
    fclose(fp);
}

int main(int argc, char *argv[])
{
  No *Dicionario;
  Registro x;
  int i, max = 0, comparacoes = 0, trocas = 0;

  Inicializa(&Dicionario);

 	char *dict = (argc == 2) ? argv[1] : WORDS;

  // load File
  inicio = time(NULL);
  loadFile(dict, R, &max);
  fim = time(NULL); //Isto deve ficar no final 

	// calculate time to load
  ti_load = difftime(fim, inicio);
  
	printf("\nArquivo [%s] carregado! ", dict);
	fflush(stdin);
	getchar();  

	// Ordenar
  inicio = time(NULL);
  Permut(R, max, &trocas);
	printf("\n");

	/* Insere cada chave na arvore e testa sua integridade apos cada insercao */
  for (i = 0; i < max; i++) 
  { strcpy(x.Chave, R[i].Chave);
    Insere(x, &Dicionario, &comparacoes);
    printf("Inseriu chave: %s\n", x.Chave);
   	Testa(Dicionario);	
  }
	
  fim = time(NULL); //Isto deve ficar no final 
  
  // calculate time to order
  ti_order = difftime(fim, inicio);

	printf("\n");
  NotaText(Dicionario);

	printf("\n");
  // report benchmarks    
	printf("\n");
	printf("TIME IN load:         %.4f (s)\n", ti_load);
	printf("TIME IN order:         %.4f (s)\n", ti_order);
  printf("TIME IN TOTAL:        %.4f (s)\n", ti_load + ti_order);
  printf("TROCAS:   %d\n", trocas);
  printf("COMPARACOES:   %d", comparacoes);
  fflush(stdin);
  getchar();

  return 0;
} 

