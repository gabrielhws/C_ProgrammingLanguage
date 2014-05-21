//-----------------------------------------------------------------
// Classificação e Pesquisa
//
// Título: ATPS Pesquisa
// Assunto: Pesquisa Binaria e Sequencial 
//
// Aluno(s):  RA:
// nome do aluno 000000
//
//Data: 23/09/2013
//-----------------------------------------------------------------


#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <conio.h>

#define MaxTam  10000000
#define LENGTH 45

#define WORDS "words"

#ifdef _WIN32
#define CLEAR "cls"
#else //In any other OS
#define CLEAR "clear"
#endif


time_t inicio, fim;
double ti_load = 0.0, ti_find = 0.0;

typedef char ChaveTipo[LENGTH];

typedef struct Item {
  ChaveTipo Chave;
  /* outros componentes */
} Item;

typedef int Indice;

typedef Item Vetor[MaxTam + 1];

Vetor A;
Indice i, n;
FILE *arq;

void Imprime(Item *V, Indice *n)
{ for (i = 1; i <= *n; i++)
    printf("%s ", V[i].Chave);  
    printf("\n");
     
}

Indice Pesquisa(ChaveTipo x, Item *A, Indice *n)
{ int i;
  
  strcpy(A[0].Chave,x);
  
  i = *n;
  do {i--;}  while (strcmp(A[i].Chave,x) != 0 );
  return i;
} 

Indice Binaria(ChaveTipo x, Item *A, Indice *n)
{ Indice i, Esq, Dir;
  if (*n == 0)
  return 0;
  else 
    { Esq = 1;
      Dir = *n;
      do 
	{ i = (Esq + Dir) / 2;
          if (strcmp(x,A[i].Chave) > 0)
	  Esq = i + 1;
	  else
	    Dir = i - 1;
        } while (strcmp(x,A[i].Chave) !=0 && Esq <= Dir);
      if (strcmp(x,A[i].Chave) == 0)
      return i;
      else
      return 0;
    }
} 

void loadFile(char *file ,Item *A, Indice *n){
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

int main(int argc, char *argv[]){ 
  
  printf("RUNNING  ");
    
  n = 0;   /*Tamanho do arranjo a ser ordenado*/
  int encontrados = 0;
  // load File
   inicio = time(NULL);
   char *dict = (argc == 3) ? argv[1] : WORDS;
   loadFile(dict,A,&n);
   //Imprime(A,&n);
   fim = time(NULL); //Isto deve ficar no final 
  
  // calculate time to load
  ti_load = difftime(fim, inicio);
  
  // Find
    inicio = time(NULL);
        char *file = (argc == 3) ? argv[2] : argv[1];
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
        {                           
            if (isalpha(c) || (c == '\'' && index > 0))
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
                ChaveTipo reg;
       	    	strncpy(reg, word,index+1);
                //printf("Word = %s\n",word);       	    	
                if(Pesquisa(reg,A, &n)){
                   encontrados++;
                }
                system(CLEAR);
                printf("RUNNING  %c",(encontrados %2 == 0) ? '/' : '\\');                                                     
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
    fim = time(NULL); //Isto deve ficar no final 
    ti_find = difftime(fim, inicio);
  
    // report benchmarks
    printf("TIME IN load:         %.2f (s)\n", ti_load);
    printf("TIME IN find:         %.2f (s)\n", ti_find);
    printf("TIME IN TOTAL:        %.2f (s)\n", 
     ti_load + ti_find);
    printf("DICIONARIO:           %d\n", n); 
    printf("TERMOS ENCONTRADOS:   %d\n\n", encontrados);     
  getchar();
  
  return 0;
}
