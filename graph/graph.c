#include "graph.h"
/*
 * 按行输入 第一行输入 0 2 3 0 0
 * 就是说第一个节点和第二个节点边的权重为2 
 * 第三个之间的边权重为3 
 * 其他无边
 *
 */
GRAPH* init_graph(int num)
{
	GRAPH *g = (GRAPH *)malloc(sizeof(GRAPH));
	g->node_num = num;
	g->edge_num = 0;
	g->n = (NODE *)malloc(sizeof(NODE)*num);
	int tmp = 0;
	for(tmp;tmp < num;tmp++)
	{
		g->n[tmp].vi = tmp+1;
	}
	int i = 0;
	while(scanf("%d",&tmp) && i < num*num-1)
	{
		if(tmp != 0)
		{
			EDGE *p_edge = (EDGE *) malloc(sizeof(EDGE));
			p_edge->vj = i%num + 1;
			p_edge->weight = tmp;
			p_edge->next_vj = NULL; 
			/*
			 * i/num 可以表示这是第几行输入
			 * i%num 表示这是这一行的第几个节点
			 * +1便于理解*/
			if(g->n[i/num].first_arc == NULL)
			{
				g->n[i/num].first_arc = p_edge;
			}
			else
			{
				EDGE *tmp_edge = g->n[i/num].first_arc;
				while(tmp_edge->next_vj != NULL)
				{
					tmp_edge = tmp_edge->next_vj;
				}
				tmp_edge->next_vj = p_edge;
			}
			g->edge_num++;
		}
		i++;
	}
	return g;
}
void show_graph(GRAPH *g)
{
	printf("GRAPH HAS %d nodes\nand has %d edges\n",g->node_num,g->edge_num);
	int i,j;
	int num = g->node_num;
	for(i = 0;i < num;i++)
	{
		EDGE *p_edge;
		p_edge = (g->n)[i].first_arc;
		while(p_edge != NULL)
		{
			printf("%d  ",p_edge->vj);
			p_edge = p_edge->next_vj;
		}
		printf("\n");
	}
	
}
int main(int argc,char *argv[])
{
	if(argc < 2)
	{
		printf("usage num\n");
		return -1;
	}
	int num = atoi(argv[1]);
	GRAPH *g = init_graph(num);
	show_graph(g);
}
