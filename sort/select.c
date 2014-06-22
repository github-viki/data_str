#include <stdio.h>
#include <stdlib.h>
void select_sort(int *p,int length)
{
	int i=1;
	int tmp=0;
	int j=0;
	for(i;i<=length;i++)
	{
		j=i+1;
		tmp=i;
		while(j<=length)
		{
			if(p[j]<p[tmp])
				tmp=j;
			j++;
		}
		if(tmp)
		{
			p[0]=p[i];
			p[i]=p[tmp];
			p[tmp]=p[0];
		}
	}
}

int show(int *p,int length)
{
	while(length>0)
	{
		printf("%5d\n",p[length--]);
	}
}
int main()
{
	int *p=(int *)calloc(sizeof(int),100000);
	int i=1;
	while(scanf("%d",&p[i]) != EOF )
		i++;
	int length=i-1;
	select_sort(p,length);
	show(p,length);

}
