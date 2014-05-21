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

#define WORDS "../text/words"

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
  int FB; /* hdir - hesq*/
  Apontador Esq, Dir;
} No;

typedef Apontador TipoDicionario;

int Altura (Apontador p){
	int Alt_Esq, Alt_Dir;
	if (p == NULL) 
       return 0;
	else{ 
		Alt_Esq = Altura (p->Esq);
		Alt_Dir = Altura (p->Dir);
		if (Alt_Esq > Alt_Dir){
			return (1 + Alt_Esq);
		}
		else{
			return (1 + Alt_Dir);
		}
	}
}

int Calcula_FB(Apontador p){
    if(p == NULL)
      return 0;
    return (Altura(p->Esq)- Altura(p->Dir));
}

Apontador rotacao_direita(Apontador N3){
       Apontador N2 = N3->Esq;
       if(N2->Dir != NULL) 
          N3->Esq = N2->Dir;
       else 
           N3->Esq=NULL;
       N2->Dir = N3;
       return N2;
}

Apontador rotacao_esquerda(Apontador N1){
       Apontador N2 = N1->Dir;
       if(N2->Esq != NULL) 
          N1->Dir = N2->Esq;
       else 
          N1->Dir = NULL;
       N2->Esq = N1;
       
       return N2;
}

Apontador rotacao_dupla_direita (Apontador N3){
       Apontador N1 = N3->Esq;
       Apontador N2 = N1->Dir;
       if(N2->Esq != NULL) 
          N1->Dir= N2->Esq;
       else 
         N1->Dir=NULL;

       if(N2->Dir != NULL) 
           N3->Esq = N2->Dir;
       else 
         N3->Esq=NULL;

       N2->Esq = N1;
       N2->Dir = N3;
       
       return N2;
}

Apontador rotacao_dupla_esquerda (Apontador N1){
       Apontador N3 = N1->Dir;
       Apontador N2 = N3->Esq;
       if(N2->Esq != NULL) 
           N1->Dir = N2->Esq;
       else 
          N1->Dir = NULL;

       if(N2->Dir != NULL) 
          N3->Esq = N2->Dir;
       else 
          N3->Esq = NULL;
       N2->Esq = N1;
       N2->Dir = N3;
       return N2;
}

Apontador CorrigeAVL(Apontador p){
	if(p != NULL){
		p->FB = Calcula_FB(p);
		printf("No <%s> <FB %d>\n",p->Reg.Chave,p->FB);//getchar();     
		if(p->FB >= 2){
			p->Esq->FB = Calcula_FB(p->Esq);
   		    printf("No->Esq <%s> <FB %d>\n",p->Esq->Reg.Chave,p->Esq->FB);//getchar();     
			if(p->Esq->FB > 0){
                printf("Rotacionar Direita No <%s>",p->Reg.Chave);//getchar();     
				p = rotacao_direita(p);
			}else{
                printf("Rotacionar Dupla Direita No <%s>",p->Reg.Chave);//getchar();       
				p =  rotacao_dupla_direita(p);
			}
		}
		else if(p->FB <= -2){
			p->Dir->FB = Calcula_FB(p->Dir);
  		    printf("No->Dir <%s> <FB %d>\n",p->Dir->Reg.Chave,p->Dir->FB);//getchar();     
			if(p->Dir->FB < 0){
                printf("Rotacionar Esquerda No <%s>",p->Reg.Chave);//getchar();     
				p = rotacao_esquerda(p);
			}else{
                printf("Rotacionar Dupla Esquerda No <%s>",p->Reg.Chave);//getchar();                         
				p =  rotacao_dupla_esquerda(p);
			}
		}
		p->Esq = CorrigeAVL(p->Esq);
		p->Dir = CorrigeAVL(p->Dir);
    }
    return p;
}

void Seta_FB(Apontador p){
     if (p!= NULL){
		 p->FB = (Altura(p->Esq)- Altura(p->Dir));
		 Seta_FB(p->Esq);
		 Seta_FB(p->Dir);
     }
}

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

void Central(Apontador p)
{ if (p == NULL)
  return;
  Central(p->Esq);
  printf("%s <FB %d>\n", p->Reg.Chave,p->FB);
  Central(p->Dir);
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

int verifica_AVL(Apontador t) {
  if (t == NULL)
    return 1;
    
  return abs(Altura(t->Dir) - Altura(t->Esq)) <= 1;
}

void Testa(No *p){ 
     if(verifica_AVL(p) != 1){
        printf("III nao é AVL\n");
        getchar();
     }
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
    {   printf("Could not open %s.\n", file);
        exit(1);
    }
    int index = 0, misspellings = 0, words = 0;
    char word[LENGTH+1];
    int c;
    for (c = fgetc(fp); c != EOF; c = fgetc(fp))
    {   if (isalpha(c) || (c == '\'' && index > 0))
        {   word[index] = c;
            index++;
            if (index > LENGTH)
            {   while ((c = fgetc(fp)) != EOF && isalpha(c));
                index = 0;
            }
        }
				else if (isdigit(c))
        {   while ((c = fgetc(fp)) != EOF && isalnum(c));
            index = 0;
        }
        else if (index > 0)
        {   word[index] = '\0';
            if(++(*n) < MaxTam-1){
    	    		strncpy(A[*n].Chave, word,index+1); 
			    	}
            index = 0;
        }
    }    
    if (ferror(fp))
    {   fclose(fp);
        printf("Error reading %s.\n", file);
        exit(2);
    }   
    fclose(fp);
}

int main(int argc, char *argv[])
{
  No *Dicionario;
  Registro x;
  int i, j, k, n, max = 0, comparacoes = 0, trocas = 0;

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

  /* Insere cada chave na arvore e testa sua integridade apos cada insercao */
  for (i = 0; i < max; i++) 
    { strcpy(x.Chave, R[i].Chave);
      Insere(x, &Dicionario, &comparacoes);
      printf("Inseriu chave: %s\n", x.Chave);    
    }
  Testa(Dicionario);
  
  NotaText(Dicionario);
  printf("\n");
  Seta_FB(Dicionario);    
  Central(Dicionario);
  getchar();
  
  Dicionario = CorrigeAVL(Dicionario);
  Seta_FB(Dicionario);
  Central(Dicionario);
	
	fim = time(NULL); //Isto deve ficar no final 
  
  // calculate time to order
  ti_order = difftime(fim, inicio);

	printf("\n");
  NotaText(Dicionario);
  Testa(Dicionario);
  getchar();

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
