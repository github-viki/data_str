#include "unp.h" 
void make_sock_non_block(int sockfd)
{
	int flags;
	flags = fcntl(sockfd,F_GETFL,0);
	if(flags == -1)
		return ;
	flags |= O_NONBLOCK;
	if(fcntl(sockfd,F_SETFL,flags)<0)
		perror("fcntl setfl");
	return;
}

int main()
{
	make_sock_non_block(0);
	int epfd;
	epfd = epoll_create(1);
	if(epfd < 0)
	{
		perror("epoll_create");
		return -1;
	}
	struct epoll_event event;
	event.data.fd = 0;
	event.events = EPOLLIN|EPOLLET;
	if(epoll_ctl(epfd,EPOLL_CTL_ADD,0,&event) < 0)
	{
		perror("epoll_ctl");
		return -1;
	}
	int n;
	while(n=epoll_wait(epfd,&event,5,-1) > 0)
	{
		while(1)
		{
		char buf[1024]={0};
		ssize_t m;
		if((m=read(0,buf,1024))>0)
		{
			printf("%s\n",buf);
		}
		if(m < 0)
		{
			if(errno == EAGAIN)
			{
				break;
			}
			else
			{
				perror("a");
			}
		}
		}
	}
	if(n<=0)
	{
		perror("wait");
	}
}
