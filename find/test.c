#include "main.h"
int main()
{
	int ch;
	char word[LIMIT];
	while((ch=getchar())!=EOF)
	{
		ungetc(ch,stdin);
		getword(word,LIMIT);
		printf("%s\n",word);
	}
}
