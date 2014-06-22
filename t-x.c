#include <stdio.h>
void main()
{
	int i=0;
	for(i=0;i<30;i++)
		printf("%5d--%5d\n",i,(i+8-1)/8+1);
	int a=0;
	int b=0;
	scanf("%d%d",&a,&b);
	printf("%d,%d\n",a,b);
}
