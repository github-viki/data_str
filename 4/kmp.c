#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int *next;
int *nextval(int n_len,char *n)
{
	next=(int *)malloc(sizeof(int)*(n_len+1));
	next[1]=0;
	int i,j;
	i=1;j=0;
	while(i<n_len)
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
	i=1;
	while(i<=n_len)
	{
		printf("%5d ",next[i++]);
	}
	printf("\n");
	return next;
}
int select_sub(char *s,char *m)
{

	int i=1,j=1;
	while(i<=strlen(s)&&j<=strlen(m))
	{
		if(j == 0 || s[i] == m[j])
		{
			i++;
			j++;
		}
		else 
		{
			j=next[j];
		}

	}
	if(j>strlen(m))
		return i-strlen(m);
	else return 0;

}
int main(int argc,char *argv[])
{
	if(argc<3)
	{
		printf("usage:kmp file string\n");
		return -1;
	}
	next=nextval(strlen(argv[2]),argv[2]);
	FILE *fp;
	fp=fopen(argv[1],"r");
	fseek(fp,0,SEEK_END);
	long length=ftell(fp);
	printf("file lengt %d\n",length);
	fseek(fp,0,SEEK_SET);
	int linenum[length];
	char *p=(char *)malloc(strlen(argv[2])+1);
	memcpy(p+1,argv[2],strlen(argv[2]));
	char *s=(char *)malloc(length+1);
	s[0]='\n';
	char *s1=s+1;
	char tmp[1024];
	int line=1;
	while(fgets(tmp,1024,fp))
	{
		printf("%d\n",strlen(tmp));
		linenum[line++]=strlen(tmp);
		memcpy(s1,tmp,strlen(tmp));
		s1=s1+strlen(tmp);
	}
	printf("line:%d\n",line-1);
	s1=s;
	printf("pos1:%d\n",select_sub(s1,argv[2]));
	while(s1 < (s+length))
	{
		int pos=select_sub(s1,argv[2]);
		printf("pos1:%d\n",pos);
		if(pos == 0)
			break;
		s1=s1+pos+strlen(argv[2]);
		int linen=1;
		while(pos>linenum[linen]&&linenum[linen]!=0)
		{
			pos-=linenum[linen++];
		}
		printf("%d--%d\n",linen-1,pos);
	}
}
