#include "list.h"
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
	l->list_get = list_get_int;
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
