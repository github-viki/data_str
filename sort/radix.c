#include <stdio.h>
#include <stdlib.h>
//3
void show_heap(int *p,int length)
{
	while(length>0)
	{
		printf("%5d\n",p[length--]);
	}
} 
void count_sort_lt(int *a,int len)
{
	if(len<2)
		return;
	int c[100]={0};
	int *b=malloc(sizeof(len+1)*4);
	int i=1;
	for(i=1;i<=len;i++)
	{
		c[a[i]]++;
	}
	for(i=1;i<100;i++)
	{
		c[i]+=c[i-1];
	}
	for(i=1;i<=len;i++)
	{
		b[c[a[i]]]=a[i];
		c[a[i]]--;
	}
	for(i=1;i<=len;i++)
	{
		a[i]=b[i];
	}
	free(b);
}
int count_sort(int *a,int len,int d)
{
	int c[10]={0};//
	int *b=malloc((len+1)*4);
	int i=1;
	int j=0;
	int *pri=b;
	/*if(d==3)
	{
	for(i=1;i<=len;i++)
	{
		if(a[i]/100==0)
		{
			b[++j]=a[i];
		}
	}
	
	count_sort_lt(b,j);
	b=b+j;
	len=len-j;
	}
	*/
	if(d==1)
	{
		for(i=1;i<=len;i++)
		c[a[i]%10]++;
	}
	else
		if(d==2)
		{
			for(i=1;i<=len;i++)
				c[a[i]%100/10]++;

		}
		else
			if(d == 3)
			{
				for(i=1;i<=len;i++)
					c[a[i]/100]++;
			}
	for(i=1;i<10;i++)
	{
		c[i]=c[i-1]+c[i];
	}
	for(i=len;i>=1;i--)
	{
		if(d==1)
		{
			b[c[a[i]%10]]=a[i];
			c[a[i]%10]--;
		}
		else
			if(d==2)
			{
				b[c[a[i]%100/10]]=a[i];
				c[a[i]%100/10]--;
			}
			else
				if(d==3)
				{
					b[c[a[i]/100]]=a[i];
					c[a[i]/100]--;
				}

	}
	for(i=1;i<=len;i++)
	{
		a[i]=b[i];
	}
	free(pri);
}
int main()
{
	int *p=(int *)calloc(sizeof(int),100000);
	int i=1;
	while(scanf("%d",&p[i]) != EOF )
		i++;
	int length=i-1;
	int d;
	for(d=1;d<=3;d++)
	count_sort(p,length,d);
	show_heap(p,length);
}
