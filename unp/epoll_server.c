#include "unp.h"
#define epoll_event struct epoll_event
void make_sock_non_block(int sockfd)
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
int main(int argc,char *argv[])
{
	if(argc < 2)
	{
		printf("usage IP\n");
		return -1;
	}
	int sockfd;
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	//
	//
	const int on=1;
	setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on));
	/*
	 * create epoll
	 * */
	int epoll_fd;
	epoll_fd = epoll_create(10);
	epoll_event event;
	epoll_event events[10];
	event.data.fd = sockfd;
	event.events = EPOLLIN|EPOLLET;
	int ret = epoll_ctl(epoll_fd,EPOLL_CTL_ADD,sockfd,&event);
	if(ret < 0)
		perror("epoll_ctl");
	struct sockaddr_in serv_addr;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(5000);
	//serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	inet_pton(AF_INET,argv[1],(void *)&(serv_addr.sin_addr));
	if(bind(sockfd,(struct sockaddr *)&serv_addr,sizeof(struct sockaddr)) < 0)
	{
		perror("bind\n");
		return -1;
	}
	make_sock_non_block(sockfd);
	/*
	 * printf the SO_RECVBUF AND SO_SNBUF lenth*/
	int length ;
	int size =4;
	getsockopt(sockfd,SOL_SOCKET,SO_RCVBUF,&length,&size);
	printf("serv the SO_RECVBUF IS %d\n",length);
	getsockopt(sockfd,SOL_SOCKET,SO_SNDBUF,&length,&size);
	printf("serv the SO_sndVBUF IS %d\n",length);
	length=4096;
	setsockopt(sockfd,SOL_SOCKET,SO_RCVBUF,&length,size);
	listen(sockfd,10);
	while(1)
	{
		int n;
		n = epoll_wait(epoll_fd,events,10,-1);
		int i;
		for(i=0;i<n;i++)
		{
			if(sockfd == events[i].data.fd)
			{
				printf("Incoming........\n");
				while(1)
				{
					/*
					 * because apply ET mode so
					 * we while(1) to accept
					 * and the socket must be nonblock;*/

				int connfd;
				struct sockaddr_in clientaddr;
				bzero(&clientaddr,sizeof(struct sockaddr_in));
				socklen_t len = sizeof(clientaddr);
				connfd = accept(sockfd,(struct sockaddr *)&clientaddr,&len);

				if(connfd < 0 && (errno == EAGAIN || errno == EWOULDBLOCK))
				{
					printf("no more accept\n");
					break;
				}/*
				 * get the client*/
				char tmp_ip[20];
				inet_ntop(AF_INET,&(clientaddr.sin_addr),tmp_ip);
				printf("%s:%d\n",tmp_ip,htons(clientaddr.sin_port));
				make_sock_non_block(connfd);
				event.data.fd = connfd;
				event.events = EPOLLIN|EPOLLET;
				epoll_ctl(epoll_fd,EPOLL_CTL_ADD,connfd,&event);
				}
			}
			else
			{
				int connfd;
				connfd = events[i].data.fd;
				char buf[1024];
				while(1)
				{
					bzero(buf,1024);
					ssize_t n;
					if((n = read(connfd,buf,1024)) <= 0)
					{
						if (n == 0)
						{
							printf("client over\n");
							epoll_ctl(epoll_fd,EPOLL_CTL_DEL,connfd,NULL);
							close(connfd);
							break;
						}
						if (errno  == EAGAIN)
						{
							printf("no more data to read\n");
							break;
						}
						else
						{
							perror("recv");
							epoll_ctl(epoll_fd,EPOLL_CTL_DEL,connfd,NULL);
							close(connfd);
							return -1;
						}
					}
					else
					{
						send(connfd,buf,n,0);
						shutdown(connfd,SHUT_WR);
					}
				}
			}
		}
	}
}
