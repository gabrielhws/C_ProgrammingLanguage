#include <stdio.h>
#include <stdlib.h>

void main(){
  char nome[20];
  printf("Informe o nome: ");
  fflush(stdin);
  scanf("%s", nome);
  printf("\n\nNome: %s\n\n", nome);
}
