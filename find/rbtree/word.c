#include <stdio.h>
int getword(char *word,int limit)
{
	int ch;
	//ignore the space
label:while(isspace(ch=getchar()))
	      ;
     	 if(ch == EOF)
      	{
	      return -1;
     	}
	if(ch!=EOF)
		*word++ = ch;
	if(!isalnum(ch))
	{
		if(ch == '\n')
		{
			word--;
			goto label;	
		}
		*word = '\0';
		return word[0];
	}
	for( ; --limit > 0; word++)
	{
		if(!isalnum(*word = getchar()))
		{
			if(*word == '\'' || *word == '-' )
			continue;
			ungetc(*word,stdin);
			break;
		}
	}
	*word='\0';
	return word[0];
	
}
