#include "unipc.h"
int get_mq_attr(mqd_t fd)
{
	struct mq_attr attr_info;
	if(mq_getattr(fd,&attr_info) == -1)
	{
		perror("getattr:");
		return -1;
	}
	printf("maxmsg:%ld\nmsgsize:%ld\ncurmsg:%ld\n",attr_info.mq_maxmsg,attr_info.mq_msgsize,attr_info.mq_curmsgs);
	return attr_info.mq_msgsize;
}
int send_mq_msg(mqd_t fd,char *msg)
{
	if(mq_send(fd,msg,strlen(msg),0) < 0)
	{
		if(errno == EAGAIN)
		{
			sleep(10);
		}
		perror("send\n");
		return -1;
	}
	return 0;
}
int recv_mq_msg(mqd_t fd)
{
	int msg_size = get_mq_attr(fd);
	char *buf = (char *)malloc(msg_size);
	if(mq_receive(fd,buf,msg_size,NULL) < 0)
	{
		perror("recv");
		return -1;
	}
	printf("%s\n",buf);
	free(buf);
}
