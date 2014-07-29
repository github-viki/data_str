#include <stdio.h>
#include <stdlib.h>
#define MAX 0x7fffffff
void merge_sort(int *p,int ,int ,int);
void msort(int *p,int ,int);
void show_sort(int *p,int);
int main()
{
	int *p=(int *)calloc(sizeof(int),100000);
	int i=1;
	while(scanf("%d",&p[i]) != EOF )
		i++;
	int length=i-1;
	msort(p,1,length);
	show_sort(p,length);
}
void msort(int *p,int i,int j)
{
	if(i < j)
	{
		int mid = (i+j)/2;
		msort(p,i,mid);
		msort(p,mid+1,j);
		merge_sort(p,i,mid,j);
	}
}
void  merge_sort(int *p,int i,int j,int k)
{
	int *arr1 = (int *)malloc((j-i+2)*sizeof(int));
	int *arr2 = (int *)malloc((k-j+2)*sizeof(int));
	int m = 0;
	int n = i;
	int q = j;
	int r = k;
	while(n <= q )
	{
		arr1[m++] = p[n++];
	}
	arr1[m] = MAX;
	m = 0;
	q++;
	while(q <= r)
	{
		arr2[m++] = p[q++];
	}
	arr2[m] = MAX;
	m = 0;
	q = 0;
	while(arr1[m] != MAX && arr2[q] != MAX)
	{
		if(arr1[m] <= arr2[q])
		{
			p[i++] = arr1[m++];
		}
		else
		{
			p[i++] = arr2[q++];
		}
	}
	while(arr1[m] != MAX)
	{
		p[i++] = arr1[m++];
	}
	while(arr2[q] != MAX)
	{
		p[i++] = arr2[q++];
	}
	free(arr1);
	free(arr2);
}
void show_sort(int *p,int length)
{
	while(length>0)
	{
		printf("%5d\n",p[length--]);
	}
}
