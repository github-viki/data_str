#include "main.h"
treenode *HEADER=NULL;
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
//初始化二叉查找树
treenode *init_word(treenode *header,char *word)
{
	if(header == NULL)
	{
		header = (treenode *)malloc(sizeof(treenode));
		bzero(header,sizeof(treenode));
		header->word = strdup(word);
		header->count++;
	}
	else if(strcmp(header->word,word)==0)
	{
		header->count++;
	}
	else if(strcmp(header->word,word) < 0)
	{
		treenode *hr=init_word(header->right,word);
		if(header->right == NULL)
		{
			header->right=hr;
			hr->parent = header;
		}
	}
	else if(strcmp(header->word,word) > 0)
	{
		treenode *hl=init_word(header->left,word);
		if(header->left == NULL)
		{
			header->left=hl;
			hl->parent = header;
		}

	}
	return header;
}
//初始化树
void init_tree()
{
	int ch = 0;
	char word[LIMIT];
	while((ch = getchar()) != EOF)
	{
		ungetc(ch,stdin);
		if(!getword(word,LIMIT))
		{
			if(HEADER == NULL)
			{
				HEADER = (treenode *)malloc(sizeof(treenode));
				bzero(HEADER,sizeof(treenode));
				HEADER->word = strdup(word);
				if(HEADER->word == 0)
				{
					perror("strdup\n");
					return ;
				}
				HEADER->count++;
			}
			else
			init_word(HEADER,word);
		
		}
		else
			break;
	}
	return ;
}
//中序遍历
void show_tree(treenode *h)
{
	if(h==NULL)
	{
		printf("NULL\tNULL\tNULL\tNULL\t\n");
		return ;
	}
	if(h->left != NULL)
		show_tree(h->left);
	printf("%s\t%s\t%s\t%s\t\n"
			,h->word
			,h->left == NULL ? NULL:h->left->word
			,h->right ==NULL ? NULL:h->right->word
			,h->parent == NULL ? NULL:h->parent->word);
	if(h->right != NULL)
		show_tree(h->right);
}
//////////////////////////
treenode *word_count[1000]={0};
treenode **word_p=word_count;
//利用插入排序 
//按字符个数进行排序
void sort_word_count(treenode *h)
{

	if(h == NULL)
	{
		return;
	}
	if(h->left != NULL)
		sort_word_count(h->left);
	if(*word_p == 0)
	{
		*word_p=h;
	}
	else
	{
		treenode **i,**j;
		i=word_p;
		j=++word_p;
		while(h->count < (*i)->count && i>=word_count)
		{
			*j-- = *i--;
			if(i<word_count)
				break;
		}
		*j = h;
	}
	if(h->right != NULL)
		sort_word_count(h->right);
}
void show_sort()
{
	if(HEADER == NULL)
	{
		return;
	}
	word_p=word_count;
	while(*word_p != 0)
	{
		printf("%-10s--%5d\n",(*word_p)->word,(*word_p)->count);
		word_p++;
	}
}
//返回最小的元素
treenode *min_node(treenode *header)
{
	if(header == NULL)
	{
		return NULL;
	}
	treenode *h=header;
	while(h->left != NULL)
	{
		h=h->left;
	}
	return h;
}
//返回x的后继
treenode *tree_successor(treenode *x)
{
	//如果x有右子树
	//返回其右子树中的最小节点，即为其后继
	treenode *y;
	if(x == NULL)
		return NULL;
	if(x->right != NULL)
	{
		y=min_node(x->right);
		return y;
	}
	//如果x没有右子树，则返回其最近的“左”父节点
	else
	{
		y = x->parent;
		while(y != NULL && x == y->right)
		{
			x = y;
			y = y->parent;
		}
		return y;
	}
}
//add a "word" into the tree
treenode *add_node(char *word)
{
	treenode *p=HEADER;
	treenode *c=p;
	if(c == NULL)
	{
		return NULL;
	}
	while(c != NULL)
	{
		if(strcmp(c->word,word)==0)
			{c->count++;return c;}
		else if(strcmp(c->word,word)<0)
			{p=c;c=c->right;}
		else
			{p=c;c=c->left;}
	}
	treenode *new_node = (treenode *)malloc(sizeof(treenode));
	bzero(new_node,sizeof(treenode));
	new_node->word=strdup(word);
	if(new_node == NULL)
	{
		perror("malloc");
		return NULL;
	}
	if(strcmp(p->word,word)<0)
	{
		p->right=new_node;
		new_node->parent=p;
	}
	else
		if(strcmp(p->word,word)>0)
		{
			p->left=new_node;
			new_node->parent=p;
		}
	return new_node;
}
//delete a node;
treenode *del_node(treenode *x)
{
	if(x == NULL)
		return NULL;
	//如果左子树或者是右子树为空
	treenode *y;
	if(x->left == NULL || x->right == NULL)
	{
		y=x;
	}
	//左右子树都不为空，则删除x的后继y。
	//然后用y的值代替x的值
	else
	{
		y=tree_successor(x);
	//	printf("%s\n",y->word);
		//y不可能为空
	}
	//此时y不可能有两个子节点.
	treenode *z;
	if(y->left == NULL)
		z=y->right;
	else
		z=y->left;
	if(z != NULL)
		z->parent=y->parent;
	treenode *py = y->parent;
	if(py == NULL)
	{
		HEADER=z;
	}
	if(y == py->left)
	{
		py->left=z;
	}
	else
		py->right=z;
	if(strcmp(y->word,x->word)!=0)
	{
		strcpy(x->word,y->word);
	}
	return y;
}
