#include <stdio.h>
#include <stdlib.h>
void insert_sort(int *p,int );
void show_sort(int *p,int);
int main()
{
	int *p=(int *)calloc(sizeof(int),100000);
	int i=1;
	while(scanf("%d",&p[i]) != EOF )
		i++;
	int length=i-1;
	insert_sort(p,length);
	show_sort(p,length);
}
void insert_sort(int *p,int length)
{
	int i;
	int j=0;
	for(i=2;i<=length;i++)
	{
		p[0] = p[i];
		for(j=i;p[j]<p[j-1];j--)
		{
			p[j]=p[j-1];
			p[j-1]=p[0];
		}
	}
}
void show_sort(int *p,int length)
{
	while(length>0)
	{
		printf("%5d\n",p[length--]);
	}
}
