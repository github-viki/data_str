#ifndef RBTREE
#define RBTREE
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
typedef struct rbtreenode
{
	struct rbtreenode *left;
	struct rbtreenode *right;
	struct rbtreenode *parent;
	char color;
	char *word;
	int count;
}rbnode;
extern rbnode *HEADER;
extern rbnode *NIL;
#define B 1
#define R 0
void init_rbtree();
void adjust_rb_tree(rbnode *,rbnode *);
void left_rotate(rbnode *,rbnode *);
void right_rotate(rbnode *,rbnode *);
int getword(char *word,int limit);
void show_rbtree(rbnode *);
void left_rotate(rbnode *,rbnode *);
void right_rotate(rbnode *,rbnode *);
rbnode *find_min(rbnode *);
rbnode *find_node(rbnode *,char *);
rbnode *tree_succesor(rbnode *);
void del_node(rbnode *,rbnode *);
void adjust_del_rbnode(rbnode *,rbnode *);
#endif
