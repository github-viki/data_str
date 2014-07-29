#include <stdio.h>
#include <stdlib.h>
#define LEFT(i) (i<<1)
#define RIGHT(i) ((i<<1)+1)
#define PARENT(i) (i>>1)
#define SWAP(i,j) do\
	{int tmp;\
	tmp=i;i=j;j=tmp;\
	}while(0)
int heap_max(int *,int length,int index);
void heap_init(int *,int);
void heap_sort(int *,int);
void show_heap(int *p,int);
int main()
{
	int *p=(int *)calloc(sizeof(int),100000);
	int i=1;
	while(scanf("%d",&p[i]) != EOF )
		i++;
	int length=i-1;
	heap_init(p,length);
	heap_sort(p,length);
	show_heap(p,length);
}
int heap_max(int *p,int length,int index)
{
	int l,r;
	int largest;
	l = LEFT(index);
	r = RIGHT(index);
	if(l > length)
		return 0;
	if(r > length)
	{
		largest = l;
	}
	else
		largest = p[l] > p[r] ? l:r;
	if(p[index] < p[largest])
	{
		SWAP(p[index],p[largest]);
		return largest;
	}
	return 0;
}
void heap_init(int *p,int length)
{
	int s;
	//from n/2 start to adjust the heap
	s = length/2;
	for(s;s>0;s--)
	{
		int next = s;
		while (next != 0 && next <= length/2)
		{
			next = heap_max(p,length,next);
		}
	}
}
void heap_sort(int *p,int length)
{
	int i;
	for(i = 1;i <= length;i++)
	{
		SWAP(p[1],p[length-i+1]);
		int next=1;
		while(next != 0 && next <= (length-i)/2)
		{
			next = heap_max(p,length-i,next);
		}
	}
}
void show_heap(int *p,int length)
{
	while(length > 0)
		printf("%5d\n",p[length--]);
}
