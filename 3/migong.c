#include <stdio.h>
#include <stdlib.h>
typedef struct pos
{
	short int x;
	short int y;
	char o;
	char footp;
}pos;
int d=1;
int **p;
int **init()
{
	scanf("%d",&d);
	p=(int **)malloc(sizeof(int)*(d+1));
	int i=0;
	for(i=0;i<=d;i++)
	{
		p[i]=(int *)malloc(sizeof(int)*(d+1));
	}
	int j;
	for(i=1;i<=d;i++)
		for(j=1;j<=d;j++)
		{
			scanf("%d",&(p[i][j]));
		}
	return p;
}

void show()
{
	int i,j;
	for(i=1;i<=d;i++)
	{
for(j=1;j<=d;j++)
		(j!=d)?printf("%d ",p[i][j]):printf("%d\n",p[i][j]);
	}
	printf("OK\n");
}
pos *stack;
pos *end;
pos* push(pos pos_i)
{
	*end=pos_i;
	end++;
	return end;
}
pos* pop()
{
	if(end==stack)
	{
		return NULL;
	}
	return --end;
}
pos* gettop()
{
	return end-1;
}
int isexist(pos pos_x)
{
	pos *pos_p;
	if(end==stack)
	{
		return 0;
	}
	pos_p=end-1;
	while(pos_p>=stack)
	{
		if(pos_p->x==pos_x.x&&pos_p->y==pos_x.y)
			return 1;
		pos_p--;
	}
	return 0;
}

pos isok(pos *pos_p)
{
	int x,y;
	x=pos_p->x;
	y=pos_p->y;
	pos res;
	if(y+1<=d)
	{
		if(p[x][y+1]==0)
		{
			res.x=x;
			res.y=y+1;
			if(!isexist(res))
			{
				return res;
			}
		}
	}
	if(x+1<=d)
	{
		if(p[x+1][y]==0)
		{
			res.x=x+1;
			res.y=y;
			if(!isexist(res))
			return res;
		}
	}
	if(y-1>0)
	{
		if(p[x][y-1]==0)
		{
			res.x=x;
			res.y=y-1;
			if(!isexist(res))
			return res;
		}
	}
	if(x-1>0)
	{
		if(p[x-1][y]==0)
		{
			res.x=x-1;
			res.y=y;
			if(!isexist(res))
			return res;
		}
	}
	res.x=0;
	res.y=0;
	return res;
}
void show_stack()
{
	pos *pos_p=stack;
	while(pos_p<end)
	{
		printf("(%d,%d)-->",pos_p->x,pos_p->y);
		pos_p++;
	}
	printf("\n");
}
//
int main()
{
	init();
	show();
	
	stack=(pos*)malloc(sizeof(pos)*d*d);

	printf("ok\n");
	end=stack;
	pos first;
	first.x=1;
	first.y=1;
	first.o=p[1][1];
	first.footp=1;
	push(first);
	/*************/
	pos *pos_p=gettop();
	while(pos_p->x!=d||pos_p->y!=d)
	{
	pos next=isok(pos_p);
	printf("%d--%d\n",next.x,next.y);
	if(next.x==0)
	{
		pos *notpass=pop();
		if(notpass==stack)
		{
			printf("over\n");
			return 1;
		}
		if(notpass==NULL)
		{
			printf("no pass\n");
			return -1;
		}
		p[notpass->x][notpass->y]=1;
	}
	else
	{
		push(next);
		p[d][d]=0;
	}
	pos_p=gettop();
	if(pos_p->x==d&&pos_p->y==d)
	{
		printf("\n");
		show_stack();
		pos *notpass=pop();
		p[notpass->x][notpass->y]=1;
	}
	pos_p=gettop();
	}

}
