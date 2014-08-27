#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "list.h"
typedef struct edge
{
	int vj;//adj node;
	struct edge *next_vj;//next adj edge
	int weight;//weight value;
}EDGE;
typedef struct node
{
	int vi;
	EDGE *first_arc;
}NODE;
typedef struct graph
{
	int kind;
	int node_num,edge_num;
	NODE *n;
}GRAPH;
GRAPH * init_graph(int num);
void show_graph(GRAPH *);
