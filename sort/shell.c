#include <stdio.h>
#include <stdlib.h>
/*
 * add a shell a length
 * 5 3 1*/
void insert_sort(int *p,int ,int);
void show_sort(int *p,int);
int main()
{
	int *p=(int *)calloc(sizeof(int),100000);
	int i=1;
	while(scanf("%d",&p[i]) != EOF )
		i++;
	int length=i-1;
	insert_sort(p,length,200);
	insert_sort(p,length,20);
	insert_sort(p,length,7);
	insert_sort(p,length,1);
	show_sort(p,length);
}
void insert_sort(int *p,int length,int jump)
{
	int i;
	int j=0;
	for(i=2;i<=length;i+=jump)
	{
		p[0] = p[i];
		///j-jump must before the p[j-jump]>0
		//becaues if j-jump > 0 is FALSE
		//the p[j-jump] not be RUN;
		//or will SIGSERV
		for(j=i;(j-jump) > 0 && p[j-jump] > p[0];j-=jump)
		{
			p[j] = p[j-jump];
		}
		p[j] = p[0];
	}
}
void show_sort(int *p,int length)
{
	while(length>0)
	{
		printf("%5d\n",p[length--]);
	}
}
