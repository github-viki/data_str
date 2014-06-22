#include <stdio.h>
#include <stdlib.h>
int row[200];
int col[200];
int MIN=0x80000000;
void show_arr(int **p,int x)
{
	int i,j;
	for(i=0;i<row[x];i++)
	{
		for(j=0;j<col[x];j++)
		{
			printf("%d ",p[i][j]);
		}
		printf("\n");
	}
}
int adjust_arr(int **p,int x)
{
	int i,j;
	int **q=(int **)malloc(sizeof(int)*row[x]);
	for(i=0;i<row[x];i++)
	{
		q[i]=(int *)malloc(sizeof(int)*col[x]);
	}
	i=0;
	q[0][0]=p[0][0];
	for(i=1;i<row[x];i++)
		q[i][0]=q[i-1][0]+p[i][0];
	for(i=0;i<row[x];i++)
		for(j=1;j<col[x];j++)
			q[i][j]=MIN;
	int flag=0;
	for(j=1;j<col[x];j++)
	{
		int l=0;
		int tmp=0;
		{
			for(l=0;l<row[x];l++)
			{
				tmp=q[l][j-1]+p[l][j];
				tmp >q[l][j] ? q[l][j]=tmp:tmp;
				for(i=l+1;i<row[x];i++)
				{
					tmp+=p[i][j];
					if(tmp>q[i][j])
						q[i][j]=tmp;
				}
			}
			for(l=row[x]-1;l>=0;l--)
			{
				tmp=q[l][j-1]+p[l][j];
				tmp > q[l][j] ? q[l][j]=tmp:tmp;
				for(i=l-1;i>=0;i--)
				{
					tmp+=p[i][j];
					if(tmp>q[i][j])
						q[i][j]=tmp;
				}
			}
		}
	}

	int result=q[0][col[x]-1];
	for(i=0;i<row[x];i++)
		free(q[i]);
	free(q);
	return result;
}

void main()
{
	int group;
	scanf("%d",&group);
	int i=0;
	int j=0;
	int **p[200];
	int k=0;
	for(i;i<group;i++)
	{
		j=0;
		k=0;
		scanf("%d %d",&row[i],&col[i]);
		if(row[i]==0||col[i]==0)
		{
			exit(-1);
		}
		p[i]=(int **)malloc(sizeof(int)*row[i]);
		int tmp1;
		
		for(tmp1=0;tmp1<row[i];tmp1++)
			p[i][tmp1]=(int *)malloc(sizeof(int)*col[i]);  
		
		for(j=0;j<row[i];j++)
		{
			for(k=0;k<col[i];k++)
				{
					scanf("%d",&p[i][j][k]);
				}
		}
	}
	
	for(i=0;i<group;i++)
		printf("Case #%d:\n%d\n",i+1,adjust_arr(p[i],i));
}

