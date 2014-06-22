#include <stdio.h>
#include <stdlib.h>
void heap_init(int *,int);
void show_heap(int *,int);
int main()
{
	int *p=(int *)calloc(sizeof(int),100000);
	int i=1;
	while(scanf("%d",&p[i]) != EOF )
		i++;
	int length=i-1;
	heap_init(p,length);
	show_heap(p,length);
}
void heap_adjust(int *p,int source,int last)
{
	int tmp=p[source];
	int i=source;
	int j=0;
	for(j=2*i;j<=last;j*=2)
	{
		if((p[j]< p[j+1]) && (j < last)) j++;
		if(tmp < p[j])
		{	
			p[j/2]=p[j];
			p[j]=tmp;
		}
	}

}
void heap_init(int *p,int length)
{
	int i=0;
	for(i=length/2;i>0;i--)
		heap_adjust(p,i,length);
	int last=length;
	for(last;last>1;last--)
	{
		int tmp=p[1];
		p[1]=p[last];
		p[last]=tmp;
		heap_adjust(p,1,last-1);
	}
}
void show_heap(int *p,int length)
{
	while(length>0)
	{
		printf("%5d\n",p[length--]);
	}
}
