#include "rbtree.h"
int main(int argc,char *argv[])
{
	char word[20];
	init_rbtree();
	HEADER=NIL;
	while(getword(word,20)!= EOF)
	{
		printf("%s\n",word);
		insert_node(word);
	}
	show_rbtree(HEADER);
	rbnode *min=find_min(HEADER);
	while(min != NIL)
	{
		printf("%s\n",min->word);
		min=tree_succesor(min);
	}
	min = find_node(HEADER,"ren");
	if(min == NIL)
	{
		return -1;
	}
	printf("find is %s\n",min->word);
	del_node(HEADER,min);
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
}
