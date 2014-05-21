#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MaxTam 50000

typedef long ChaveTipo;
typedef struct Item {
	ChaveTipo Chave;
	/* outros componentes */
} Item;

typedef int Indice;
typedef Item Vetor[MaxTam + 1];
Vetor A, B;
Indice i, n;

void estatisticas(char metodo[], int qtde, long comp, long trocas, clock_t start, clock_t end)
{
	clock_t time = ( end - start ) / (CLOCKS_PER_SEC/1000);

	printf("\n\t\tMetodo utilizado: %s", metodo);
	printf("\n\t\tQtde de elementos ordenados: %d", qtde); 
	printf("\n\t\tNumero de comparacoes: %d", comp); 
	printf("\n\t\tNumero de trocas: %d", trocas);
	printf("\n\t\tTempo gasto para ordenacao (ms): %d", time);
}

/**
(1) Bolha
**/
void BubbleSort(Item *A, Indice *n)
{
	Indice i, j;
	Item x;
	int k = *n - 1;

	long int comp = 0, trocas = 0;
	clock_t end, start;

	start = clock();

	for(i = 1; i <= *n; i++)
	{
		for(j = 0; j <= k; j++)
		{
			comp++;
			if(A[j].Chave > A[j+1].Chave)
			{
				trocas++;
				x = A[j];
				trocas++;
				A[j] = A[j+1];
				trocas++;
				A[j+1]=x;
			}
		}
		k--;
	}

	end = clock();

	estatisticas("Bolha", *n, comp, trocas, start, end);
}

/**
(2) Inser��o
**/
void Insercao(Item *A, Indice *n)
{ 
	Indice i, j;
	Item x;


	long int comp = 0, trocas = 0;
	clock_t end, start;

	start = clock();

	for (i = 2; i <= *n; i++) 
	{ 	
		trocas++;
		x = A[i];
		j = i - 1;
		trocas++;
		A[0] = x;   /* sentinela */

		comp++;
		while (x.Chave < A[j].Chave) 
		{ 
			trocas++;
			A[j+1] = A[j];
			j--;
		}

		trocas++;
		A[j+1] = x;
	} 


	end = clock();

	estatisticas("Insercao", *n, comp, trocas, start, end);
}

/**
(3) Selecao
**/
void Selecao(Item *A, Indice *n)
{ 
	Indice i, j, Min;
	Item x;

	long int comp = 0, trocas = 0;
	clock_t end, start;

	start = clock();
	for (i = 1; i <= *n - 1; i++) 
	{ 
		Min = i;
		for (j = i + 1; j <= *n; j++)
		{ 	
			comp++;
			if (A[j].Chave < A[Min].Chave) Min = j;
		}

		trocas++;
		x = A[Min]; 
		trocas++;
		A[Min] = A[i]; 
		trocas++;				
		A[i] = x;
	}

	end = clock();

	estatisticas("Selecao", *n, comp, trocas, start, end);
}

/**
(4) QuickSort
**/
void Particao(Indice Esq, Indice Dir, Indice *i, Indice *j, Item *A, long int *comp, long int *trocas)
{ 
	Item x, w;
	*i = Esq; 
	*j = Dir;
	(*trocas)++;  // trocas realizadas
	x = A[(*i + *j) / 2];   /* obtem o pivo x */
	(*comp)++;
	do 
	{ 
		(*comp)++;  // compara��es
		while (x.Chave > A[*i].Chave) (*i)++;
		(*comp)++;  // compara��es
		while (x.Chave < A[*j].Chave) (*j)--;
		(*comp)++;   
		if (*i <= *j) 
		{ 
			(*trocas)++;  // trocas realizadas
			w = A[*i]; 
			(*trocas)++;  // trocas realizadas
			A[*i] = A[*j]; 
			(*trocas)++;  // trocas realizadas
			A[*j] = w;
			(*i)++; (*j)--;
		}
	} while (*i <= *j);
}

void Ordena(Indice Esq, Indice Dir, Item *A, long int *comp, long int *trocas)
{ 
	Indice i, j;
	Particao(Esq, Dir, &i, &j, A, comp, trocas);
	(*comp)++;
	if (Esq < j) Ordena(Esq, j, A, comp, trocas);
	(*comp)++;
	if (i < Dir) Ordena(i, Dir, A, comp, trocas);
}

void QuickSort(Item *A, Indice *n)
{ 
	long int comp = 0, trocas = 0;
	clock_t end, start;

	start = clock();

	Ordena(1, *n, A, &comp, &trocas);


	end = clock();

	estatisticas("QuickSort", *n, comp, trocas, start, end);
}


/**
(5) HeapSort
**/
void Refaz(Indice Esq, Indice Dir, Item *A, long int *comp, long int *trocas)
{ 
	Indice i = Esq;
	int j;
	Item x;
	j = i * 2;

	(*trocas)++;
	x = A[i];

	(*comp)++;
	while (j <= Dir) 
	{ 
		(*comp)++;
		if (j < Dir) 
		{ 
			(*comp)++;
			if (A[j].Chave < A[j+1].Chave) j++;
		}

		(*comp)++;
		if (x.Chave >= A[j].Chave)
		{
			(*trocas)++;
			goto L999;
		}

		(*trocas)++;      
		A[i] = A[j];
		i = j; 
		j = i * 2;
	}
L999: A[i] = x;
}

void Constroi(Item *A, Indice *n, long int *comp, long int *trocas)
{ 
	Indice Esq;
	Esq = *n / 2 + 1;
	(*comp)++;
	while (Esq > 1) 
	{ 
		Esq--;
		Refaz(Esq, *n, A, comp, trocas);
	}
}

void HeapSort(Item *A, Indice *n)
{ 
	Indice Esq, Dir;
	Item x;

	long int comp = 0, trocas = 0;
	clock_t end, start;

	start = clock();

	Constroi(A, n, &comp, &trocas);   /* constroi o heap */
	Esq = 1; Dir = *n;

	comp++; 
	while (Dir > 1) 
	{ /* ordena o vetor */
		trocas++;
		x = A[1]; 
		trocas++;
		A[1] = A[Dir]; 
		trocas++;
		A[Dir] = x;
		Dir--;
		Refaz(Esq, Dir, A, &comp, &trocas);
	}

	end = clock();

	estatisticas("HeapSort", *n, comp, trocas, start, end);
}


/** 
(6) ShellSort
**/
void ShellSort(Item *A, Indice *n)
{ 
	Indice i, j;
	int h = 1;
	Item x;

	long int comp = 0, trocas = 0;
	clock_t end, start;

	start = clock();

	do h = h * 3 + 1; while (h < *n);
	do { 
		h /= 3;
		for (i = h + 1; i <= *n; i++) 
		{ 	
			trocas++;
			x = A[i];
			j = i;
			comp++;
			while (A[j - h].Chave > x.Chave) 
			{ 
				trocas++;
				A[j] = A[j - h];
				j -= h;
				if (j <= h) goto L999;
			}
L999: A[j] = x;
		}
	} while (h != 1);

	end = clock();

	estatisticas("ShellSort", *n, comp, trocas, start, end);
}

/**
(7) MergeSort
**/
void Merge(Item *A, Indice n, long int *comp, long int *trocas) {
	Indice mid;
	Indice i, j, k;
	Item *tmp;
	int a;

	tmp = (Item*) malloc((n+1) * sizeof(Item));

	(*comp)++;
	if (tmp == NULL) {
		exit(1);
	}
	mid = (n / 2)+1;
	i = 1;
	j = mid;
	k = 1;

	(*comp)++;
	while (i < mid && j <= n) {		
		(*comp)++;
		if (A[i].Chave < A[j].Chave){			
			(*trocas)++;
			tmp[k] = A[i++];
		}
		else{		
			(*trocas)++;
			tmp[k] = A[j++];        
		}
		++k;
	}
	(*comp)++;
	if (i == mid){
		(*comp)++;
		while (j <= n) {		
			(*trocas)++;
			tmp[k++] = A[j++];
		}
	}
	else {
		(*comp)++;
		while (i < mid) {
			tmp[k++] = A[i++];                
		}
	}

	for (i = 1; i <= n; ++i) {		
		(*trocas)++;
		A[i] = tmp[i];
	}
	free(tmp);
}

void MergeSort(Item *A, Indice n, long int *comp, long int *trocas) {  
	int mid1,mid2;	

	(*comp)++;
	if (n > 1) {
		mid1 = n / 2;
		MergeSort(A, mid1, comp, trocas);
		mid2 = n - (n / 2);
		MergeSort(A + (mid1), mid2, comp, trocas);
		Merge(A, n, comp, trocas);
	}
}

/**
Menu: Exibi as op��es para o usu�rio selecionar a quantidade de itens do vetor
**/
int Menu()
{
	int op;

	printf("\n\t\t\tAlgoritmos de Ordenacao\n\n");
	printf("\t\tInicializar vetor: \n");
	printf("\t\t[1] 500 itens\n");
	printf("\t\t[2] 5.000 itens\n");
	printf("\t\t[3] 50.000 itens\n");
	printf("\t\t[9] Sair\n");
	printf("\t\tOpcao: ");
	fflush(stdin); // limpa a entrada de dados pelo teclado	
	scanf("%d", &op);

	return op;
}

/** 
Imprime: Imprime os valores do vetor passado por parametro
**/
void Imprime(Item *A, Indice *n)
{ 
	printf("\n");
	for (i = 1; i <= *n; i++)
		printf("%d ", A[i].Chave);
	printf("\n");
}

/**
PressEnter: Solicita ao usu�rio a inser��o de um caracter para prosseguir
**/
void PressEnter()
{
	printf("\t[ENTER]");
	fflush(stdin);
	getchar();
	system("cls");
}

/**
GerarNumeros: Gera os valores e incializa os vetores 
com a quantidade de indices passada por parametro
**/
void GerarNumeros(Item *A, Indice *n)
{
	Indice i;

	for(i=1; i <= *n; i++)
		A[i].Chave = rand() % MaxTam + 1;
}

void Clone(Item *A, Item *B, Indice n)
{	
	Indice i;

	for(i=1; i <= n; i++)
		B[i].Chave = A[i].Chave;
}

void Inverte(Item *A, Indice n)
{
	Indice i, j;
	Item tmp;
	
	for(i=1; i <=n; i++)
	{
		for(j = i+1; j <= n; j++)
			if(A[i].Chave < A[j].Chave)
			{
				tmp = A[j];
				A[j] = A[i];
				A[i] = tmp;               
        		 }
	}
}

void tmp(Indice n)
{
	int op;
	long int comp = 0, trocas = 0;
	clock_t end, start;

	GerarNumeros(A, &n);

	do {
		system("cls");
		printf("\n\t\t\tAlgoritmos\n\n");
	
		printf("\n\t\t1) QuickSort");	
		printf("\n\t\t2) Insercao");	
		printf("\n\t\t3) ShellSort");
		printf("\n\t\t4) HeapSort");
		printf("\n\t\t5) MergeSort\n");

		printf("\n\t\t9) Voltar");

		printf("\n\t\tOpcao: ");
		fflush(stdin);
		scanf("%d", &op);

		switch(op)
		{
		case 1: 
			Clone(A, B, n);		
			printf("\n\n\t\tPior Caso:");
			QuickSort(B, &n);

			printf("\n\n\t\tMelhor Caso:");
			QuickSort(B, &n);

			Inverte(B, n);

			printf("\n\n\t\tDecrescente: \n");
			QuickSort(B, &n);
					
			PressEnter();
			break;	
		
		case 2: 	
			Clone(A, B, n);
			printf("\n\n\t\tPior Caso:");
			Insercao(B, &n);

			printf("\n\n\t\tMelhor Caso:");
			Insercao(B, &n);

			Inverte(B, n);
			
			printf("\n\n\t\tDecrescente: \n");
			Insercao(B, &n);
			
			PressEnter();	
			break;
		case 3: 	
			Clone(A, B, n);	
			printf("\n\n\t\tPior Caso:");	
			ShellSort(B, &n);

			printf("\n\n\t\tMelhor Caso:");
			ShellSort(B, &n);

			Inverte(B, n);
			
			printf("\n\n\t\tDecrescente: \n");
			ShellSort(B, &n);
			PressEnter();		
			break;	
		case 4: 	
			Clone(A, B, n);	
			printf("\n\n\t\tPior Caso:");	
			HeapSort(B, &n);

			printf("\n\n\t\tMelhor Caso:");
			HeapSort(B, &n);

			Inverte(B, n);
			
			printf("\n\n\t\tDecrescente: \n");
			HeapSort(B, &n);
			PressEnter();
			break;
		case 5:
			Clone(A, B, n);		
			printf("\n\n\t\tPior Caso:");	
			start = clock();	
			MergeSort(B, n, &comp, &trocas);	
			end = clock();
			estatisticas("MergeSort", n, comp, trocas, start, end);
			printf("\n\n\t\tMelhor Caso:");
			comp = 0; trocas=0;
			start = clock();
			MergeSort(B, n, &comp, &trocas);
			end = clock();
			estatisticas("MergeSort", n, comp, trocas, start, end);
	
			Inverte(B, n);

			printf("\n\n\t\tDecrescente: \n");
			comp = 0; trocas=0;
			start = clock();
			MergeSort(B, n, &comp, &trocas);
			end = clock();
			estatisticas("MergeSort", n, comp, trocas, start, end);

			PressEnter();
			break;
		case 9: printf("\n\t\tVoltando ao menu principal."); PressEnter();	break;
		}

	} while (op != 9); 
}



/** 
Main: Parte principal da aplica��o
**/
int main(int argc, char *argv[])
{
	int op;

	do {
		op = Menu();
		switch(op){
		case 1: tmp(500);	break;
		case 2: tmp(5000);	break;
		case 3: tmp(50000);	break;
		case 9: printf("\n\t\tFinalizando sistema..."); PressEnter(); break;
		default: printf("Opcao [%d] errada!! Escolha 1,2,3,4 ou 9", op); PressEnter();		
		}
	} while(op != 9); 

	return 0;
}
			
