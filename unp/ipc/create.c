#include "unipc.h"
int main(int argc,char *argv[])
{
	if(argc < 2)
	{
		printf("usage:filename");
		return -1;
	}
	mqd_t fd;
	fd = open_mq(argv[1]);
	get_mq_attr(fd);
	int i = 0;
	while(i < 11)
	{
		send_mq_msg(fd,"1");
	}
	mq_close(fd);
}
