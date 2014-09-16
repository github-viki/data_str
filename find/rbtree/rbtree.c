#include "rbtree.h"

rbnode *NIL;
rbnode *HEADER;
void init_rbtree()
{
	NIL=(rbnode *)malloc(sizeof(rbnode));
	bzero(NIL,sizeof(rbnode));
	NIL->color = B;
	NIL->left = NIL;
	NIL->right = NIL;
	NIL->parent = NIL;
}
//add new node to rbtree;
rbnode *insert_node(char *word)
{
	rbnode *p=HEADER;
	rbnode *c=p;
	//p保存的是即将插入节点的父节点
	while(c != NIL)
	{
		if(strcmp(c->word,word) == 0)
		{
			c->count++;
			return c;
		}
		else if(strcmp(c->word,word) <0)
		{
			p=c;
			c=c->right;
		}
		else
		{
			p=c;
			c=c->left;
		}
	}
	rbnode *new_node=(rbnode *)malloc(sizeof(rbnode));
	bzero(new_node,sizeof(rbnode));
	new_node->color = R;
	new_node->word = strdup(word);
	new_node->parent = p;
	new_node->left = NIL;
	new_node->right = NIL;
	new_node->count = 1;
	if(p == NIL)
	{
		HEADER=new_node;
		HEADER->color=B;
		return HEADER;
	}
	if(strcmp(p->word,word)>0)
		p->left=new_node;
	else
		p->right=new_node;
	//只有当new_node的父节点为红色的时候才需要调整。
	if(p->color == R)
		adjust_rb_tree(HEADER,new_node);
//	show_rbtree(HEADER);
//	printf("\n\n");
	return new_node;
}
//adjust 
//插入节点可能破坏的红黑性质有
//1.根节点是黑色节点
//2.红色节点的子节点不是黑色节点。
//
//
//红黑树的性质
//1.节点非黑即红
//2.根节点为黑
//3.即NULL节点都是黑色的
//4.红色节点的两个孩子必然是黑色
//5.所有到子节点的路径上，黑色节点的个数都是一样的。
void adjust_rb_tree(rbnode *h,rbnode *x)
{
	//如果其父节点为红色，则必然有祖父节点，且一定为黑色
	//所以剩余的两种情况，就要看其叔父节点的颜色了，叔父节点可能为空。
	//叔父节点为空的情况是说明叔父是黑色的。
	//因为所有的空节点都是黑色的额
	rbnode *son;
	rbnode *uncle;
	rbnode *parent;
	rbnode *grandfather;
	son = x;
	parent = x->parent;
	grandfather = parent->parent;
	while(parent->color == R && parent != HEADER)
	{
		if(parent == grandfather->left)
		{
			uncle = grandfather->right;
			//CASE1:叔父节点为红色
			if(uncle->color == R)
			{
				uncle->color = B;
				parent->color = B;
				grandfather->color = R;
				son = grandfather;
				parent = son->parent;
				if(parent == NIL)
				{
					son->color = B;
					return ;
				}
				grandfather = parent->parent;
			}
			//CASE2:叔父节点为黑色son为右孩子
			//CASE3:叔父节点为黑色son为左孩子
			else
			{
				if(son == parent->right)
				{
					
					left_rotate(HEADER,parent);
					//旋转后son变为parent，parent变为son；
					rbnode *tmp;
					tmp = son;
					son = parent;
					parent = tmp;
				}
				
				//CASE3
				//交换父节点和祖父节点的颜色，
				//然后右转
				//
				parent->color = B;//grandfather必然为黑色
				grandfather->color = R;//父节点的颜色为红色
				right_rotate(HEADER,grandfather);
			}
		}
		//父节点是右子节点
		else
		{
			uncle = grandfather->left;
			//CASE1:叔父节点为红色
			if(uncle->color == R)
			{
				uncle->color = B;
				parent->color = B;
				grandfather->color = R;
				son = grandfather;
				parent = son->parent;
				//递归到父节点
				if(parent == NIL)
				{
					son->color = B;
				}
				grandfather = parent->parent;
			}
			//CASE2:叔父节点为黑色son为右孩子
			//CASE3：叔父节点为黑色son为左孩子
			else
			{
				if(son == parent->left)
				{
					right_rotate(HEADER,parent);
					//旋转后son变为parent，parent变为son；
					rbnode *tmp;
					tmp = son;
					son = parent;
					parent = tmp;
					
				}
				
				//CASE3
				parent->color = B;
				grandfather->color = R;
				left_rotate(HEADER,grandfather);
				
			}
		}
	}
}
rbnode* find_node(rbnode *H,char *word)
{
	if(H == NIL)
		return NIL;
	if(strcmp(H->word,word) == 0)
		return H;
	else if(strcmp(H->word,word) <0)
		
		find_node(H->right,word);
	else
		find_node(H->left,word);
}
rbnode* find_min(rbnode *H)
{
	while(H->left != NIL)
	{
		H=H->left;
	}
	return H;
}
rbnode* tree_succesor(rbnode *z)
{
	if(z == NIL)
	{
		return NIL;
	}
	//如果有右子树则返回右子树的最小节点
	if(z->right != NIL)
		return find_min(z->right);
	//没有右子树的话，则返回最左祖先节点。
	rbnode *pz=z->parent;
	//pz==NIL说明根节点z没有右子树
	while(pz != NIL && z == pz->right)
	{
		z = pz;
		pz=pz->parent;
	}
	return pz;

}
void del_node(rbnode *h,rbnode *z)
{
	//y为要删除的节点
	rbnode *y=NULL;
	if(z->left == NIL || z->right == NIL)
		y=z;
	else
		y=tree_succesor(z);
	rbnode *x;
	if(y->left != NIL)
		x=y->left;
	else
		x=y->right;
	x->parent=y->parent;
	if(y->parent == NIL)
	{
		HEADER=x;
		HEADER->color=B;
		return;
	}
	if(y == y->parent->left)
		y->parent->left=x;
	else
		y->parent->right=x;
	if(strcmp(y->word,z->word) != 0)
	{
		strcpy(z->word,y->word);
	}
	//只有删除黑色节点 才会出错
	if(y->color == B)
		adjust_del_rbnode(HEADER,x);
	return;
	//y至多有一个子节点
}
void adjust_del_rbnode(rbnode *h,rbnode *x)
{
	//删除时主要看x的兄弟节点w;
	//必然有父节点和兄弟节点，如果没有父节点则为根节点，根据del_rbnode则不会跳到
	//adjust_del_rbnode 函数中。
	//case1:w为红色，则通过变色，旋转将w变为黑色。
	rbnode *w;
	while(x != HEADER && x->color == B)
	{
		if(x == x->parent->left)
		{
			w = x->parent->right;
			rbnode *pw=w->parent;
			//CASE1:w的颜色为红色
			//则wl和wr必然是根为黑色的子树
			//pw也必为黑色。
			//pw和w换色；
			//对pw左旋
			if(w->color == R)
			{
				pw->color = R;
				w->color =B;
				left_rotate(HEADER,pw);
				//左旋之后的变化。
				//x = pw;//x->parent;
				//此时 w为原来w的左孩子
				
				w = x->parent->right;//w->left 必然为黑色
				//w = w->right;
				//可以改写为，w = x->parent->right;
			}
			//CASE2 w为黑色 wl和wr也均为黑色
			if(w->left->color == B && w->right->color == B)
			{
				w->color = R;
				x = x->parent;
			}
			else
			{
				//CASE3 w为黑色，wl为红色，wr为黑色
				//要让wr为红色，CASE4会改变wr的颜色
				if(w->right->color == B)
				{
					w->color = R;
					w->left->color = B;
					right_rotate(HEADER,w);
					//旋转后w就要发生变化
					w = x->parent->right;
				}
				//case4 w为黑色，wl无论什么颜色，wr为红色。
				//将pw设置为黑色，w设置为pw的颜色。保证性质5.相当于是交换颜色。
				//将wr设置为黑色，增加了一重黑色。
				//则右旋减少一重黑色
				pw=w->parent;
				int tmp = w->color;
				w->color = pw->color;
				pw->color = tmp;
				w->right->color = B;
				left_rotate(HEADER,pw);
				x = HEADER;
			}
		}
		else
		{
			//w = x->parent->left;
			rbnode *pw=x->parent;
			w=pw->left;
			if(w->color == R)
			{
				w->color = B;
				w->parent->color = R;
				right_rotate(HEADER,w->parent);
				//这样更容易理解。
				w = pw->left;
			}
			//CASE2 w，wl和wr都为黑色。
			if(w->left->color == B && w->right->color == B)
			{
				w->color = R;
				x=x->parent;
			}
			//CASE3 wl 为黑色 wr为红色
			//一定要变成wl为红色，因为CASE4会改变wl的颜色为黑色
			else
			{
				if(w->left->color == B)
				{
					w->color = R;
					w->right->color = B;
					left_rotate(HEADER,w);
					w = pw->left;
				}
			//CASE4 wl 为红色 wr 任意色。
				int tmp = w->color;
				w->color = w->parent->color;
				w->parent->color = tmp;
				w->left->color = B;
				right_rotate(HEADER,w->parent);
				x = HEADER;
			}
		}

	}
	x->color = B;
}
void left_rotate(rbnode *h,rbnode *x)
{
	if(x == NULL || h == NULL)
	{
		return;
	}
	rbnode *y=x->right;
	x->right = y->left;
	y->left->parent = x;
	y->parent = x->parent;
	if(y->parent == NIL)
		HEADER=y;
	else
	{
		if(x == x->parent->left)
			x->parent->left=y;
		else
			x->parent->right=y;
	}
	x->parent=y;
	y->left=x;
}
void right_rotate(rbnode *h,rbnode *x)
{
	if(x == NULL || h == NULL )
		return;
	rbnode *y = x->left;
	y->right->parent=x;
	x->left=y->right;
	y->parent = x->parent;  
	if(x->parent == NIL)
	{
		HEADER=y;
	}
	else
	{
		if(x == x->parent->left)
			x->parent->left=y;
		else
			x->parent->right=y;
	}
	y->right=x;
	x->parent=y;

}
//先序遍历打印值
void show_rbtree(rbnode *h)
{
	if(h == NIL)
		return;
	printf("%s\t%s\t%s\t%s\t%s\t%d\n"
			,(h == NIL || h == NULL) ? "":h->word
			,(h->left == NIL || h->left == NULL) ? NULL:h->left->word
			,(h->right == NIL || h->right == NULL) ? NULL:h->right->word
			,(h->parent == NIL || h->parent == NULL) ? NULL:h->parent->word
			,h->color ? "B":"R"
			,h->count
			);
	show_rbtree(h->left);
	show_rbtree(h->right);
}
