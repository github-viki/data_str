#include "unipc.h"
int main(int argc,char *argv[])
{
	mqd_t fd = open_mq(argv[1]);	
	recv_mq_msg(fd);
}
