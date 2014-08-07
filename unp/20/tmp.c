#include "unp.h"
int main()
{
	printf("%d\n",if_nametoindex("eth0"));
	printf("%d\n",if_nametoindex("lo"));
	printf("%d\n",if_nametoindex("eth1"));
}
