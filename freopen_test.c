#include <stdio.h>
#include <string.h>
int main()
{
	FILE *fp;
	int re;
	//fp=freopen("xx","w",stdout);
	//close buf
//	setbuf(fp,NULL);
	re=dup2(1,2);
	fputs("aaaaaaaaaaa\n",stdout);
	//rewind(fp);
	//fseek(fp,3,0);
	fputs("ccc\n",stdout);
	fputs("bbbbb\n",stderr);
	//p can't in rodata
	char p[]="a:b=2:c=3:d:f";
	char *q;
	char *q1=p;
	while((q=strtok(q1,":")))
	{
		char x[10]={0};
		printf("%s\n",q);
		q1=NULL;
		strcpy(x,q);
		if((q=strtok(x,"=")))
		printf("%s\n",q);

	}
}
