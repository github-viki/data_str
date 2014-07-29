#include "rbtree.h"
int main(int argc,char *argv[])
{
	char word[20];
	init_rbtree();
	HEADER=NIL;
	while(getword(word,20)!= EOF)
	{
		insert_node(word);
	}
	show_rbtree(HEADER);
	/*rbnode *p=insert_node("wang");
	rbnode *s=insert_node("zhu");
	left_rotate(HEADER,HEADER);
	printf("%s\n",HEADER->word);
	show_rbtree(HEADER);
	right_rotate(HEADER,HEADER);
	show_rbtree(HEADER);
	printf("%s\n",HEADER->word);
	*/
	rbnode *p = find_node(HEADER,"a");
	if(p == NIL)
	{
		printf("can't find\n");
		return -1;
	}
	del_node(HEADER,p);
	show_rbtree(HEADER);

}
