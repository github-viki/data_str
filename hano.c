#include <stdio.h>
int move(char a,int i,char b)
{
	printf("move %d %c--%c\n",i,a,b);
	return 1;
}
int hano(int n,char a,char b,char c)
{
	if(n==1)
	{
		move(a,n,c);
		return 1;
	}
	hano(n-1,a,c,b);
	move(a,n,c);
	hano(n-1,b,a,c);
}
int main()
{
	hano(5,'a','b','c');
}
