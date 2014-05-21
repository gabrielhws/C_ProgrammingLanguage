#include <stdio.h>

int main()
{
	int i;
	char str[10];
	char* p;
	
	strcpy(str, "Aprovado");
	p = str;
	for(i=0;i<str[i];i++)
	{
		printf("%c", str[i]);
		printf("\n");
	}
	for(i=0;(*p);i++,p++)
	{
		printf("%c", (*p));;
	}
	return (0);
}