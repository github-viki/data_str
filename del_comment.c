#include <stdio.h>
void rm_comment()
{
	int c;
	c = getchar();
	
		if(c == '/')
		{
			while((c = getchar()) != EOF)
			{	
				if(c == '\n')
				{
					ungetc(c,stdin);
					return;
				}
			}
		}
		else if(c == '*')
		{
			while((c = getchar()) != EOF)
			{
				if(c == '*')
				{
					int next;
					next = getchar();
					if(next == EOF)
					{
						return;
					}
					if(next == '/')
					{
						next = getchar();
						if(next != '\n')
							ungetc(next,stdin);
						return;
					}
					else
						ungetc(c,stdin);
				}
			}
		}
	
}
void ed_quota(int c)
{
	putchar(c);
	int d;
	while((d = getchar()) != c )
		putchar(d);
	putchar(d);
}
void main()
{
	int c;
	while((c = getchar()) != EOF)
	{
		if(c == '/')
		{
			int next;
			next = getchar();
			if(next == EOF)
			{
				return;
			}
			if(next == '/' || next == '*')
			{
				ungetc(next,stdin);
				rm_comment();
			}
			else
				putchar(c);
			
		}
		else if(c == '\"')
			{
				ed_quota(c);
			}
		else
		putchar(c);
	}
}
