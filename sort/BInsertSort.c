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
	int low,high,mid;
	for(i=2;i<=length;i++)
	{
		p[0] = p[i];
		high = i-1;
		low = 1;
		while(low <= high)
		{
			mid = (low + high)/2;
			if(p[0] > p[mid]) low = mid+1;
			else high = mid -1;
		}
		int j = i-1;
		for(j;j >= low;j--) p[j+1] = p[j];
		p[low] = p[0];
		if(low == high+1)
		{
			printf("low == high+1\n");
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
