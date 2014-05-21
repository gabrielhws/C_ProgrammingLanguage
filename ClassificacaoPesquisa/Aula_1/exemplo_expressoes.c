#include <stdio.h>

int main()
{
	int x, y=o;
	int* p;
	
	p=&y;
	x=(*p);
	x=4;
	(*p)++;
	x--;
	(*p) = (*p) + x;
	printf("y = %d\n", y);
	
	return (0);
}