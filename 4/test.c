#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
	char *p=(char *)malloc(10);
	char *q="123456789";
	memcpy(p,q,10);
	printf("%d--%d\n",strlen(p),strlen(q));
}
