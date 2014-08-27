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
	printf("GRAPH HAS %d nodes\nand has %d edges\n",g->node_num,g->edge_num/2);
	int i,j;
	int num = g->node_num;
	for(i = 0;i < num;i++)
	{
		EDGE *p_edge;
		p_edge = (g->n)[i].first_arc;
		printf("%d相连的顶点：",i+1);
		while(p_edge != NULL)
		{
			printf("%d ",p_edge->vj);
			p_edge = p_edge->next_vj;
		}
		printf("\n");
	}
	
}
//标志是否被访问过
//用于小端机器
char *flag;
void DFS(int i,GRAPH *g)
{
	printf("%d\n",i+1);
	flag[i] = 1;
	EDGE *p = g->n[i].first_arc;
	while(p != NULL)
	{
		//因为采用连接表，有可能指向已经访问过的节点，所以要用while循环
		//然后再进行递归
		//如果采用if(p!= null)的话，p就有可能指向一个visited节点。
		//从而flag检测无法通过，无法进行DFS。
		//printf("%d\n",g->n[i].first_arc->vj-1);
		if(flag[p->vj-1] == 0)
			DFS(p->vj-1,g);
		p = p->next_vj;
	}
}
void DFS_travel(GRAPH *g)
{
	flag = (char *) malloc(sizeof(g->node_num));
	bzero(flag,g->node_num);
	int i=0;
	for(i;i < g->node_num;i++)
	{
		if(flag[i] == 0)
		{
			DFS(i,g);
		}
	}
	free(flag);
}
/*
 * 用list模拟队列*/
void BFS(GRAPH *g)
{
	int i=0;
	flag = (char *) malloc(sizeof(g->node_num));
	bzero(flag,g->node_num);
	LIST *queue = init_int(g->node_num);
	i = 0;
	int j;
	for(j= 0;j < g->node_num;j++)
	{
		if(flag[j] == 0)
		{
			printf("%d ",g->n[j].vi);
			flag[j] = 1;
			queue->list_insert(&(g->n[j].vi),queue);
			while(( queue->list_get(1,queue)) != 0)
			{
				i = queue->list_get(1,queue);
				i--;
				//因为会做为下标 所以减1；
				queue->list_delete(1,queue);
				EDGE *tmp = g->n[i].first_arc;
				while(tmp != NULL)
				{
					if(flag[tmp->vj - 1] == 0)
					{
						printf("%d ",tmp->vj);
						flag[tmp->vj - 1] = 1;
						queue->list_insert(&(tmp->vj),queue);
					}
					tmp = tmp->next_vj;
				}
			}
		}
	}
	printf("\n");
}
void DIJ(int index,GRAPH *g)
{
	unsigned int MAX = 0xffffffff;
	/*
	 * 表示所有的点都未找到最短路径*/
	flag = (char *)malloc(sizeof(g->node_num));
	bzero(flag,g->node_num);
	/*
	 * 表示最新加入最短路径集合的点*/
	int lastvj = 0;
	/*
	 * path 二维数组代表从index点到各点的最短路径*/
	int **path;
	path = (int **) malloc(sizeof(int *) * g->node_num);
	int i;
	for(i = 0;i < g->node_num;i++)
	{
		path[i] = (int *)malloc(sizeof(int)*g->node_num);
		bzero(path[i],g->node_num*sizeof(int));
	}
	i = index - 1;
	flag[i] = 1;
	unsigned int *dis = (unsigned int *)malloc(sizeof(int)*g->node_num);
	int j = 0;
	EDGE *tmp;
	tmp = g->n[0].first_arc;
	for(i;i < g->node_num;i++)
	{
		path[i][j] = index - 1;
		dis[i] = MAX;
	}

	dis[0] = 0;

	while(tmp != NULL)
	{
		dis[tmp->vj-1] = tmp->weight;
		tmp = tmp->next_vj;
	}
	unsigned int min = MAX;
	for(i = 1;i < g->node_num;i++)
	{
		for(j = 0;j < g->node_num;j++)
		{
			if(flag[j] == 0 && min >dis[j])
			{
				min = dis[j];
				lastvj = j;
				printf("%d\n",lastvj);
			}
		}
		flag[lastvj] = 1;
		for(j = 0;j < g->node_num;j++)
		{
			unsigned int tmp_dis = MAX;
			EDGE *tmp;
			tmp = g->n[lastvj].first_arc;
			while(tmp != NULL)
			{
				if(tmp->vj == j)
				{
					tmp_dis = tmp->weight;
					break;
				}
				tmp = tmp->next_vj;
			}
			if(flag[j] == 0 && dis[j]-dis[lastvj] > tmp_dis)
			{
				dis[j] = tmp_dis + dis[lastvj];
			}
		}
	}
	for(i=0;i<g->node_num;i++)
	{
		printf("%u ",dis[i]);
	}
	printf("\n");

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
	BFS(g);
	DIJ(1,g);
}
