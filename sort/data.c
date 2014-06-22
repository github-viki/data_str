#include <stdio.h>
#include <stdlib.h>
int main()
{
	int i;
	for(i=0;i<999;i++)
	{
		i%10==9 ? printf("\n%-5d  ",rand()+1%10+rand()%10*10+rand()%10*100) : printf("%-5d  ",rand()%10+rand()%10*10+rand()%10*100);
	}
}
