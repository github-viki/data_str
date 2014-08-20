#include "unipc.h"
int main(int argc,char *argv[])
{
	if(argc < 2)
	{
		printf("usage:filename");
		return -1;
	}
	mqd_t fd;
	mode_t fdmode = S_IRWXU|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH;
	if((fd = mq_open(argv[1],O_RDWR|O_NONBLOCK,fdmode,NULL)) == (mqd_t) -1)
	{
		perror("mq_open");
		return -1;
	}
	get_mq_attr(fd);
	int i = 0;
	while(i < 11)
	{
		send_mq_msg(fd,"1");
	}
	mq_close(fd);
}
