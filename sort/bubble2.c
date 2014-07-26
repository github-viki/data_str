#include <stdio.h>
#include <stdlib.h>
#define true 1
#define false 0
#define swap(p,q)\
	do\
	{int tmp=p;p=q;q=tmp;}\
	while(0);
int bubble(int *p,int length);
int show(int *,int);
int main()
{
	int *p=(int *)calloc(sizeof(int),100000);
	int i=1;
	while(scanf("%d",&p[i]) != EOF )
		i++;
	int length=i-1;
	bubble(p,length);
	show(p,length);
}
int show(int *p,int length)
{
	while(length>0)
	{
		printf("%5d\n",p[length--]);
	}
}
int bubble(int *p,int length)
{
	/*
	 * if changed then continue;
	 * not then break;
	 * */
	int flag = 1;
	int i=0;
	int j;
	for(i;i < length;i++)
	{
		if(flag)
		{
			flag =0;
			for(j = 1;j < length-i;j++)
			{
				if(p[j] > p[j+1]) {swap(p[j],p[j+1]);flag = 1;}
			}
		}
	}
}
