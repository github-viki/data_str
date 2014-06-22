#include <stdio.h>
#define MAXNUM 15
void print_hori_histogram( int nw[MAXNUM+1])
{
	int i;
	int j;
	for(i = 1; i < MAXNUM+1; i++)
	{
		printf("%3d ",i);
		for(j=0;j<nw[i];j++)
			printf("*");
		printf("\n");
	}
}
void main()
{
	int nc=0;//c counts every words
	int nw[MAXNUM+1]={0};//words count
	char c;
	while((c=getchar()) != EOF)
	{
		if(c == ' ' || c == '\t' || c == '\n')
		{
			if(nc > MAXNUM)
			{
				nw[MAXNUM]++;
			}
			if(nc != 0)
			nw[nc]++;
			nc=0;
		}
		else
			nc++;
	}
	print_hori_histogram(nw);
}
