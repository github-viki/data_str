#include "unp.h"
#define PORT 5000
#define IP "192.168.56.3"
void make_sock_non_block(int sockfd)
{
	int flags;
	flags = fcntl(sockfd,F_GETFL,0);
	if(flags == -1)
		return ;
	flags |= O_NONBLOCK;
	fcntl(sockfd,F_SETFL,flags);
	return;
}

int main(int argc,char *argv[])
{
	if(argc < 2)
	{
		printf("usage:ip\n");
		return -1;
	}
	struct sockaddr_in ser_addr;
	bzero(&ser_addr,sizeof(ser_addr));
	ser_addr.sin_family = AF_INET;
	ser_addr.sin_port = htons(PORT);
	inet_pton(AF_INET,argv[1],(void *)&(ser_addr.sin_addr));
	int sockfd;
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in clientaddr;
	bzero(&clientaddr,sizeof(clientaddr));
	clientaddr.sin_family = AF_INET;
	clientaddr.sin_port = htons(atoi(argv[2]));
	inet_pton(AF_INET,"127.0.0.1",(void *)&(clientaddr.sin_addr));
	int on = 1;
	setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on));
	bind(sockfd,(struct sockaddr *)&clientaddr,sizeof(clientaddr));
	if(connect(sockfd,(struct sockaddr *)&ser_addr,sizeof(ser_addr)) < 0)
	{
		perror("connect");
		return -1;
	}
	ssize_t n;
	char send_buf[1024];
	bzero(send_buf,1024);
	char recv_buf[1024];
	bzero(recv_buf,1024);
	/*
	 * epoll model to 
	 * monitor the all fd;
	 **/
	make_sock_non_block(0);
	make_sock_non_block(sockfd);
	int efd;
	efd = epoll_create(5);
	struct epoll_event event;
	struct epoll_event events[10];
	event.data.fd = 0;
	event.events = EPOLLIN|EPOLLET;
	epoll_ctl(efd,EPOLL_CTL_ADD,0,&event);
	bzero(&event,sizeof(event));
	event.data.fd = sockfd;
	event.events = EPOLLIN|EPOLLET;
	epoll_ctl(efd,EPOLL_CTL_ADD,sockfd,&event);

	while((n=epoll_wait(efd,events,10,-1)) > 0)
	{
		int i;
		for(i=0;i<n;i++)
		{
		if(events[i].data.fd == 0)
		{
			while(1)
			{	
			bzero(send_buf,1024);
			if((n=read(0,send_buf,1023)) > 0)
			{
				if(send(sockfd,send_buf,strlen(send_buf),0) < 0)
				{
					perror("send");
					int sock_err;
					int err_len=sizeof(int);
					getsockopt(sockfd,SOL_SOCKET,SO_ERROR,&sock_err,&err_len);
					printf("%d\n",sock_err);
					return -1;
				}
				else
				{
				}
			}
			
			else if(n == 0)
			{
				shutdown(sockfd,SHUT_WR);
				break;
			}
			else
			{
				if(errno == EAGAIN || errno == EWOULDBLOCK)
				{
					break;
				}
				else
					perror("read");
			}
			}

		}
		
		else
		{
			while(1)
			{
				bzero(recv_buf,1024);
			ssize_t n;
			n = recv(sockfd,recv_buf,1024,0);
			if(n< 0)
			{
				if(errno == EAGAIN)
				{
					break;
				}
				else
				{perror("recv");
				close(sockfd);
				return -1;}
			}
			else
				if(n == 0)
				{
					close(sockfd);
					return -1;
				}
			printf("%s",recv_buf);
			}
		}
		}
	}
	/*while(fgets(send_buf,1023,stdin))
	{
		printf("read %s\n",send_buf);
	if((n = send(sockfd,send_buf,strlen(send_buf),0)) <= 0)
	{
		perror("send");
		close(sockfd);
		return -1;
	}
	char buf[1024];
	bzero(buf,1024);
	if((n = recv(sockfd,buf,n,0)) < 0)
	{
		perror("recv");
		close(sockfd);
		return -1;
	}
	if(n == 0)
	{
		printf("serv close\n");
		close(sockfd);
		return 1;
	}
	printf("%s\n",buf);
	}
	close(sockfd);
	return 1;*/
}
