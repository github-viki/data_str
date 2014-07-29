#include "main.h"
void main()
{
	init_tree();
	//sort_word_count(HEADER);
	printf("node    left    right   parent\n");
	show_tree(HEADER);

	/*x=del_node(x);
	if(x != NULL)
	printf("%s --%d\n",x->word,x->count);
	show_tree(HEADER);
	add_node("NAME");
	show_tree(HEADER);
	*/

}
