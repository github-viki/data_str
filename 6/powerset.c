#include "list.h"
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
	if(argc < 2)
	{
		printf("usage powerset 3");
	}
	int num;
	num = atoi(argv[1]);
	PLIST a = init_int(num);
	int i=1;
	for(i;i<=num;i++)
		a->list_insert(&i,a);
	PLIST b = init_int(num);
	powerset(a,b,1);
}
