nclude <iostream>
#include <queue>
using namespace std;

#define N 5 //点的个数
#define M 4 //边的个数

int N, M;
queue<int> Q;//用于拓扑排序
//边结点结构
//struct Edge
//{
//	int start;//有向图的起点
//		int end;//有向图的终点
//			Edge *next;//指向同一个起点的下一条边
//				Edge(int s, int e):start(s),end(e),next(NULL){}
//				};
//				//顶点结点结构
//				struct Vertex
//				{
//					int InDegree;//入度，用于拓扑排序
//						int In;//若p参加聚会，以p为根的子树能得到的最大的喜欢值
//							int NotIn;//若p不去参加聚会，以p为根的子树能得到的最大的喜欢值
//								int Enthu;//结点p表示的雇员的喜欢值
//									Edge *head;//指向以该顶点为起点的下一条边
//										Vertex():InDegree(0),head(NULL){}
//										};
//										//图结构
//										struct Graph
//										{
//											Vertex *V[10+1];//N个顶点
//												Graph()
//													{
//															int i;
//																	for(i = 1; i <= N; i++)
//																				V[i] = new Vertex;
//																					}
//																					};
//																					//插入边
//																					void InsertEdge(Graph *G, Edge *E)
//																					{
//																						//如果没有相同起点的边
//																							if(G->V[E->start]->head == NULL)
//																									G->V[E->start]->head =E;
//																										//如果有，加入到链表中
//																											else
//																												{
//																														E->next = G->V[E->start]->head;
//																																G->V[E->start]->head = E;
//																																	}
//																																		G->V[E->end]->InDegree++;
//																																		}
//																																		//转置
//																																		Graph* Reverse(Graph *G)
//																																		{
//																																			Graph *ret = new Graph;
//																																				int i;
//																																					//遍历图G中的每一条边，以终点为起点，以起点为终点，加入到新图RET中
//																																						for(i = 1; i <= N; i++)
//																																							{
//																																									Edge *E = G->V[i]->head;
//																																											while(E)
//																																													{
//																																																Edge *e = new Edge(E->end, E->start);
//																																																			InsertEdge(ret, e);
//																																																						E = E->next;
//																																																								}
//																																																									}
//																																																										return ret;
//																																																										}
//																																																										//按照转置图的拓扑序列，依次求每个点的In[p]和NotIn[p]
//																																																										void Sub(Graph *G, Vertex *p)
//																																																										{
//																																																											//若p为一个叶子结点时，In[p] = Enthu[p]，NotIn[p] = 0
//																																																												p->In = p->Enthu;
//																																																													p->NotIn = 0;
//																																																														Edge *e = p->head;
//																																																															//若p有孩子
//																																																																while(e)
//																																																																	{
//																																																																			//In[p] = Enthu[p] + SUM(NotIn[p->child])
//																																																																					p->In = p->In + G->V[e->end]->NotIn;
//																																																																							//NotIn[p] = SUM(MAX(In[p->child], NotIn[p->child]))
//																																																																									p->NotIn = p->NotIn + max(G->V[e->end]->NotIn, G->V[e->end]->In);
//																																																																											e = e->next;
//																																																																												}
//																																																																												}
//																																																																												void DP(Graph *G1, Graph *G2)
//																																																																												{
//																																																																													//对转置图进行拓扑排序
//																																																																														while(!Q.empty())Q.pop();
//																																																																															int i, ret;
//																																																																																for(i = 1; i <= N; i++)
//																																																																																		if(G2->V[i]->InDegree == 0)
//																																																																																					Q.push(i);
//																																																																																						while(!Q.empty())
//																																																																																							{
//																																																																																									int q = Q.front();Q.pop();
//																																																																																											//按照转置图的拓扑序列，依次求每个点的In[p]和NotIn[p]
//																																																																																													Sub(G1, G1->V[q]);
//																																																																																															ret = max(G1->V[q]->In, G1->V[q]->NotIn);
//																																																																																																	//用于拓扑排序
//																																																																																																			Edge *e = G2->V[q]->head;
//																																																																																																					while(e)
//																																																																																																							{
//																																																																																																										G2->V[e->end]->InDegree--;
//																																																																																																													if(G2->V[e->end]->InDegree == 0)
//																																																																																																																	Q.push(e->end);
//																																																																																																																				e = e->next;
//																																																																																																																						}
//																																																																																																																							}
//																																																																																																																								//管理关系树的根结点root，即拓扑序列中的最后一个点，MAX(In[root], NotIn[root])即所求的值
//																																																																																																																									cout<<ret<<endl;
//																																																																																																																									}
//																																																																																																																									/*
//																																																																																																																									6 2 5 1 1
//																																																																																																																									1 2
//																																																																																																																									1 3
//																																																																																																																									3 4
//																																																																																																																									3 5
//																																																																																																																									*/
//																																																																																																																									int main()
//																																																																																																																									{
//																																																																																																																										while(cin>>N>>M)
//																																																																																																																											{
//																																																																																																																													//构造一个空的图
//																																																																																																																															Graph *G = new Graph;
//																																																																																																																																	int i, start, end;
//																																																																																																																																			//输入每个人的喜欢程度
//																																																																																																																																					for(i = 1; i <= N; i++)
//																																																																																																																																								cin>>G->V[i]->Enthu;
//																																																																																																																																										//输入边
//																																																																																																																																												for(i = 1; i <= M; i++)
//																																																																																																																																														{
//																																																																																																																																																	cin>>start>>end;
//																																																																																																																																																				Edge *E = new Edge(start, end);
//																																																																																																																																																							InsertEdge(G, E);
//																																																																																																																																																									}
//																																																																																																																																																											//转置
//																																																																																																																																																													Graph *G2 = Reverse(G);
//																																																																																																																																																															DP(G, G2);
//																																																																																																																																																																}
//																																																																																																																																																																	return 0;
//																																																																																																																																																																	}:q
//																																																																																																																																																																	:wq
//
