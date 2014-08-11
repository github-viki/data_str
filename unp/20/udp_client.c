#include "unp.h"
void set_non_block(int sockfd)
{
	int flags;
	flags = fcntl(sockfd,F_GETFL,0);
	if(flags == -1)
	{perror("fcntl getfl");return ;}
	flags |= O_NONBLOCK;
	if(fcntl(sockfd,F_SETFL,flags)<0)
	{
		perror("fcntl setfl");
		return;
	}
	return;
}
int main(int argc, char *argv[])
{
	if(argc < 3)
	{
		printf("ip port \n");
		return -1;
	}
	int sockfd;
	sockfd = socket(AF_INET,SOCK_DGRAM,0);
	int on = 1;
	setsockopt(sockfd,SOL_SOCKET,SO_BROADCAST,&on,sizeof(on));
	setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on));
	set_non_block(sockfd);
	set_non_block(0);
	add_to_mcast(sockfd,"224.0.1.1");
	int epfd;
	epfd = epoll_create(10);
	struct epoll_event events[10];
	struct epoll_event event;
	bzero(&event,sizeof(event));
	event.data.fd = sockfd;
	event.events = EPOLLIN|EPOLLET;
	epoll_ctl(epfd,EPOLL_CTL_ADD,sockfd,&event);
	event.data.fd = 0;
	epoll_ctl(epfd,EPOLL_CTL_ADD,0,&event);

	struct sockaddr_in servaddr;
	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	int port = atoi(argv[2]);
	servaddr.sin_port = htons(port);
	inet_pton(AF_INET,argv[1],&(servaddr.sin_addr));
	/*connect udp
	 * xx
	if(connect(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr)) < 0)
	{
		perror("connect");
		return -1;
	}*/
	int i = 0; 
	while((i = epoll_wait(epfd,events,10,-1)))
	{
		int j = 0;
		for(j;j<i;j++)
		{
		if(events[j].data.fd == 0)
		{
			char buf[102400];
			while(1)
			{
				if(fgets(buf,1024,stdin) == NULL)
				{
				if(errno != EAGAIN)
				{
					perror("fgets\n");
					return -1;
				}
				else

					break;
				}
			}
			buf[102399] = 'a';
			ssize_t n = sendto(sockfd,buf,1024,0,(struct sockaddr *)&servaddr,sizeof(struct sockaddr));
			//ssize_t n = send(sockfd,buf,1024,0);
			if(n < 0)
			{
			perror("sendto");
			return -1;
			}
			socklen_t len = sizeof(struct sockaddr);
			n = recvfrom(sockfd,buf,n,0,NULL,NULL);
			if(n <= 0)
			{
				if(errno !=EAGAIN)
				{
					perror("recv");
					return -1;
				}
			}
		}
		else
		{
			while(1)
			{
				ssize_t n;
				char buf[1024];
				bzero(buf,1024);
				n = recvfrom(sockfd,buf,n,0,NULL,NULL);
				if(n < 0)
				{
					if(errno != EAGAIN)
					{
						perror("recvfrom");
						return -1;
					}
					else
						break;
				}
				fputs(buf,stdout);
			}
		}
		}
	}

}
