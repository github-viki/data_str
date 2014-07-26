#include <stdio.h>
#include <stdlib.h>
int partion(int *p,int low,int high)
{
	while(low < high)
	{
		p[0] = p[low];
		while(low < high && p[high] >= p[0])
		{
			high--;
		}	
		p[low] = p[high];
		while(low < high && p[low] <= p[0])
		{
			low++;
		}
		p[high] = p[low];
		//the last
		p[low] = p[0];
	}
		return low;
}
int quicksort(int *p,int low,int high)
{
	if(low < high)
	{
		int mid=partion(p,low,high);
		quicksort(p,mid+1,high);
		quicksort(p,low,mid-1);
		return 1;
	}
	else
		return 0;
}
void show_sort(int *p,int length)
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
	while(scanf("%d",&p[i]) != EOF)
		i++;
	int length = i-1;
	quicksort(p,1,length);
	show_sort(p,length);
}
