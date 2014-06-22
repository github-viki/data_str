#ifndef MAIN
#define MAIN
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <strings.h>
int getword(char *,int);
typedef struct treenode
{
	struct treenode *left;
	struct treenode *right;
	struct treenode *parent;
	int count;
	char *word;
}treenode;
extern treenode *HEADER;
#define LIMIT 30
treenode *min_node(treenode *);
treenode *tree_successor(treenode *x);
treenode *init_word(treenode *header,char *word);
void init_tree();
void show_tree(treenode *h);
treenode *del_node(treenode *);
treenode * add_node(char *);
#endif
