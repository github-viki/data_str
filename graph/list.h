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
	int (*list_get)(int ,struct list *);
	void* value[];
}LIST,*PLIST;

