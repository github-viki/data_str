/*
 * 求幂集算法
 * 输出说明
 * 0 为不存在的值
 * 如求3个元素的幂集的情况
 * 123
 * 120
 * 100
 * 130
 * 230
 * 200
 * 300
 * 000*/
#include <stdio.h>
#include <stdlib.h>
struct list;
struct list *init_int(int);
struct list *init_char(int);
void output_int(struct list *);
void output_char(struct list *);
void list_insert_int(void *,struct list *);
void list_delete_int(int index,struct list *);
void list_free(struct list *);
int list_get_int(int index,struct list *);
typedef struct list
{
	int len;
	struct list* (*init)(int);
	void (*output)(struct list*);
	void (*list_insert)(void *,struct list *);
	void (*list_delete)(int index,struct list *);
	void (*list_free)(struct list *);
	void (*list_get)(int ,struct list *);
	void* value[];
}LIST,*PLIST;
void list_free(struct list *p)
{
	//free(p->value);
}
struct list *init_int(int len)
{
	struct list *l;
	l = (struct list*)malloc(sizeof(LIST)+len*sizeof(int));
	l->len = len;
	l->output = output_int;
	l->list_insert = list_insert_int;
	l->list_delete = list_delete_int;
	l->list_free = list_free;
	return l;
}
struct list *init_char(int len)
{
	struct list *l;
	l = (struct list*)malloc(sizeof(LIST)+len*sizeof(char));
	return l;
}
void output_int(struct list *p)
{
	int i=0;
	while(i < p->len)
	{
		printf("%d ",((int *)(p->value))[i]);
		i++;
	}
	printf("\n");
}
void output_char(struct list *p)
{
	int i=0;
	while(i < p->len)
	{
		printf("%c ",((char *)(p->value))[i]);
		i++;
	}
	printf("\n");
}
void list_insert_int(void *arg,LIST *p)
{
	int a =*(int *)arg;
	int i=0;
	while(i < p->len)
	{
		if(((int *)(p->value))[i] == 0)
		{
			((int *)(p->value))[i] = a;
			break;
		}
		i++;
	}
}
void list_delete_int(int index,LIST *p)
{
	int i = index;
	while(i < p->len && ((int *)(p->value))[i] != 0)
	{
		if(i <= 0)
		{
			i = 1;
			continue;
		}
		((int *)(p->value))[i-1] = ((int *)(p->value))[i];
		i++;
	}
	((int *)(p->value))[i-1] = 0;
	
}
int list_get_int(int index,LIST *p)
{
	if(index <= p->len)
	{
		return (((int *)(p->value))[--index]);
	}
}
int list_del_end_int(LIST *p)
{
	int len = p->len;
	while(((int *)(p->value))[--len] == 0)
	{}
	((int *)(p->value))[len] = 0;
	return 0;
}
int powerset(PLIST src,PLIST dst,int index)
{

	if(index > dst->len)
	{
		dst->output(dst);
		return;
	}
	dst->list_insert((int *)(src->value)+index-1,dst);
	powerset(src,dst,index+1);
	list_del_end_int(dst);
	powerset(src,dst,index+1);

}
int main(int argc,char *argv[])
{
	int num;
	num = atoi(argv[1]);
	PLIST a = init_int(num);
	int i=1;
	for(i;i<=num;i++)
		a->list_insert(&i,a);
	PLIST b = init_int(num);
	powerset(a,b,1);
}
