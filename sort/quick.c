#include <stdio.h>
#include <stdlib.h>
int partion(int *arr,int p,int q)
{
	int j;
	int mid=arr[q];
	j=q-1;
	while(p<q&&j>=p)
	{
		if(arr[p]>mid)
		{
			int tmp=0;
			tmp=arr[p];
			arr[p]=arr[j];
			arr[j]=tmp;
			j--;
		}
		else
			p++;
	}
	arr[p+1]=mid;
	return p;
}
int quicksort(int *arr,int p,int r)
{
	if(p>=r)
		return 1;
	int q=0;
	q=partion(arr,p,r);
	quicksort(arr,p,q-1);
	quicksort(arr,q+1,r);
}
int show(int *p,int len)
{
	int i=1;
	for(i=1;i<=len;i++)
	{
		printf("%d\n",p[i]);
	}
}
int main()
{
	int *p=(int *)calloc(sizeof(int),100000);
	int i=1;
	while(scanf("%d",&p[i]) != EOF)
		i++;
	int length = i-1;
	quicksort(p,1,length);
	show(p,length);
}
