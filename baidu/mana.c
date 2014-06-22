#include <stdio.h>
#include <stdlib.h>
int T[200]={0};
typedef struct earning
{
	int dates;
	int earn;
}earning;
typedef struct irate
{
	int i;
	int j;
	int rate;
}irate;
earning e[2501];
irate r[2501];
int **choose_int(int m,int ***x);
int show_arr(int **p,int m)
{
	int i,j;
	for(i=0;i<m;i++)
	{
		for(j=0;j<m;j++)
		{
			printf("%d ",p[i][j]);
		}
		printf("\n");
	}
}
int sum_earn(int i,int n)
{
	int sum=0;
	int j=0;
	while(e[j].dates<i)
		sum+=e[j].earn;
	return sum;
}
int main()
{
	int t;
	scanf("%d",&t);
	int i;
	int n,m;
	for(i=0;i<t;i++)
	{
		scanf("%d %d",&n,&m);
		int tmpi;
		for(tmpi=0;tmpi<n;tmpi++)
		{
			scanf("%d %d",&(e[tmpi].dates),&(e[tmpi].earn));
		}
		for(tmpi=0;tmpi<m;tmpi++)
		{
			scanf("%d %d %d",&(r[tmpi].i),&(r[tmpi].j),&(r[tmpi].rate));
		}
		int **p;
		int **ret;
		p=choose_int(m,&ret);
		show_arr(p,m);
		show_arr(ret,m);
	}
}
int **choose_int(int m,int ***x)
{
	int **p=malloc(sizeof(int)*m);
	int **ret=malloc(sizeof(int)*m);
	int j;
	for(j=0;j<m;j++)
	{
		p[j]=(int *)malloc(sizeof(int)*m);
		ret[j]=(int *)malloc(sizeof(int)*m);
	}
	int k,i;
	for(j=1;j<m;j++)
	{
		for(i=0;i<j;i++)
		{
			for(k=i+1;k<j;k++)
			{
				if((r[k].i >= r[i].j) && (r[k].j <= r[j].i))
				{
					int tmp=0;
					tmp=p[i][k]+p[k][j]+r[k].rate;
					if(p[i][j] < tmp)
					{
						p[i][j]=tmp;
						ret[i][j]=k;
					}
				}
			}
		}
	}
	*x=ret;
	return p;
}
