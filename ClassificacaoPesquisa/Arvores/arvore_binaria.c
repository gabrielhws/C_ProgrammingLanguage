#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <sys/time.h>

typedef long TipoChave;
typedef struct Registro {
  TipoChave Chave;
  /* outros componentes */
} Registro;
typedef struct No * Apontador;
typedef struct No {
  Registro Reg;
  Apontador Esq, Dir;
} No;
typedef Apontador TipoDicionario;

void Pesquisa(Registro *x, Apontador *p)
{ if (*p == NULL) 
  { printf("Erro : Registro nao esta presente na arvore\n");
    return;
  }
  if (x->Chave < (*p)->Reg.Chave) 
  { Pesquisa(x, &(*p)->Esq);
    return;
  }
  if (x->Chave > (*p)->Reg.Chave)
  Pesquisa(x, &(*p)->Dir);
  else
    *x = (*p)->Reg;
} 

void Insere(Registro x, Apontador *p)
{ if (*p == NULL) 
  { *p = (Apontador)malloc(sizeof(No));
    (*p)->Reg = x; (*p)->Esq = NULL; (*p)->Dir = NULL;
    return;
  }
  if (x.Chave < (*p)->Reg.Chave) 
  { Insere(x, &(*p)->Esq); return; }
  if (x.Chave > (*p)->Reg.Chave)
  Insere(x, &(*p)->Dir);
  else
    printf("Erro : Registro ja existe na arvore\n");
} 


void Inicializa(Apontador *Dicionario)
{ *Dicionario = NULL;
}

void Antecessor(Apontador q, Apontador *r)
{ if ((*r)->Dir != NULL) 
  { Antecessor(q, &(*r)->Dir);
    return;
  }
  q->Reg = (*r)->Reg;
  q = *r;
  *r = (*r)->Esq;
  free(q);
} 

void Retira(Registro x, Apontador *p)
{  Apontador Aux;
  if (*p == NULL) 
  { printf("Erro : Registro nao esta na arvore\n");
    return;
  }
  if (x.Chave < (*p)->Reg.Chave) 
  { Retira(x, &(*p)->Esq); return; }
  if (x.Chave > (*p)->Reg.Chave)
  { Retira(x, &(*p)->Dir); return; }
  if ((*p)->Dir == NULL) 
  { Aux = *p;
    *p = (*p)->Esq;
    free(Aux);
    return;
  }
  if ((*p)->Esq != NULL) 
  { Antecessor(*p, &(*p)->Esq);
    return;
  }
  Aux = *p;
  *p = (*p)->Dir;
  free(Aux);
}  

void Central(Apontador p)
{ if (p == NULL)
  return;
  Central(p->Esq);
  printf("%ld\n", p->Reg.Chave);
  Central(p->Dir);
} 

void TestaI(No *p, int pai)
{ if (p == NULL)
  return;
  if (p->Esq != NULL) 
  { if (p->Reg.Chave < p->Esq->Reg.Chave) 
    { printf("Erro: Pai %ld menor que filho a esquerda %ld\n", p->Reg.Chave, p->Esq->Reg.Chave);
      exit(1);
    }
  }
  if (p->Dir != NULL) 
  { if (p->Reg.Chave > p->Dir->Reg.Chave) 
    { printf("Erro: Pai %ld maior que filho a direita %ld\n",  p->Reg.Chave, p->Dir->Reg.Chave);
    exit(1);
    }
  }
  TestaI(p->Esq, p->Reg.Chave);
  TestaI(p->Dir, p->Reg.Chave);
}


void Testa(No *p)
{ if (p != NULL)
  TestaI(p, p->Reg.Chave);
}

double rand0a1() {
  double resultado=  (double) rand()/ RAND_MAX; /* Dividir pelo maior inteiro */
  if(resultado>1.0) resultado = 1.0;
  return resultado;
}

void Permut( TipoChave A[], int n) {
  int i,j;
  TipoChave b;
  for(i = n; i>0; i --) 
    { j = (i * rand0a1());
      b = A[i];
      A[i] = A[j];
      A[j] = b;
    }
}

void NotaText(Apontador p)
{ if (p == NULL){
       printf("<>");
     return;
  }
  printf("<%ld", p->Reg.Chave);
  NotaText(p->Esq);
  NotaText(p->Dir);
  printf(">");
} 

#define max  10


int main(int argc, char *argv[])
{
  struct timeval t;
  No *Dicionario;
  Registro x;
  TipoChave vetor[max];
  int i, j, k, n;

  Inicializa(&Dicionario);

  /* Gera uma permutação aleatoria de chaves entre 1 e max */
 
  for (i = 0; i < max; i++)
    vetor[i] = i+1;
  
  //gettimeofday(&t,NULL);
  srand((unsigned int)t.tv_usec);
  Permut(vetor,max-1);

  /* Insere cada chave na arvore e testa sua integridade apos cada insercao */
  for (i = 0; i < max; i++) 
    { x.Chave = vetor[i];
      Insere(x, &Dicionario);
      printf("Inseriu chave: %d\n", x.Chave);
     Testa(Dicionario);
     getchar();
    }
    NotaText(Dicionario);
    
    getchar();

  /* Retira uma chave aleatoriamente e realiza varias pesquisas */
  for (i = 0; i <= max; i++) 
    { k = (int) (10.0*rand()/(RAND_MAX+1.0));
      n = vetor[k];
      x.Chave = n;
      Retira(x, &Dicionario);
      Testa(Dicionario);
      printf("Retirou chave: %ld\n", x.Chave);
      for (j = 0; j < max; j++) 
	{ x.Chave = vetor[(int) (10.0*rand()/(RAND_MAX+1.0))];
          if (x.Chave != n) 
	  { printf("Pesquisando chave: %ld\n", x.Chave);
	    Pesquisa(&x, &Dicionario);
	  }
	}
      x.Chave = n;
      Insere(x, &Dicionario);
      printf("Inseriu chave: %ld\n", x.Chave);
      Testa(Dicionario);
    }

  /* Retira a raiz da arvore ate que ela fique vazia */
  for (i = 0; i < max; i++) 
    { x.Chave = Dicionario->Reg.Chave;
      Retira(x, &Dicionario);
      Testa(Dicionario);
      printf("Retirou chave: %ld\n", x.Chave);
    }
    getchar();
  return 0;
} 
