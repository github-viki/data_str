#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int *nextval(int n_len,char *n)
{
	int *next;
	next=(int *)malloc(sizeof(int)*n_len+1);
	next[1]=0;
	int i,j;
	i=1;j=0;
	while(i <= n_len)
	{
		if(j == 0|| n[i] == n[j])
		{
			i++;
			j++;
			if(n[i] == n[j])
			{
				next[i]=next[j];
			}
			else
			next[i]=j;
		}
		else
			j=next[j];
	}
	return next;
}
int main(int argc,char *argv[])
{
	if(argc<3)
	{
		printf("usage:kmp file string\n");
		return -1;
	}
	char *p=(char *)malloc(strlen(argv[2])+1);
	memcpy(p+1,argv[2],strlen(argv[2]));
	int *next;
	next=nextval(strlen(argv[2]),p);
	char *s=(char *)malloc(strlen(argv[1]+1));
	memcpy(s+1,argv[1],strlen(argv[1]));
	int i,j;
	for(i=1,j=1;i<=strlen(s)&&j<=strlne(p);i++,j++)
	{
		if(s[i]!=p[j])
		{
			j=next[j];
		}

	}
	if(j>strlen(p))
		printf("%d\n",i-strlen(p));
}
