#include "unp.h"

int main(int argc,char *argv[])
{
	if(argc < 3)
	{
		printf("ip port\n");
		return -1;
	}
	int port = atoi(argv[2]);
	int sockfd;
	sockfd = socket(AF_INET,SOCK_DGRAM,0);
	int on =1;
	setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on));
	struct sockaddr_in servaddr;
	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(port);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	if(bind(sockfd,(struct sockaddr *)& servaddr,sizeof(struct sockaddr_in)) < 0)
	{
		perror("bind");
		return -1;
	}
	struct sockaddr_in clientaddr;
	char buf[1024] = {'\0'};
	for(;;)
	{
	socklen_t len = sizeof(struct sockaddr_in);
	ssize_t n;
	n = recvfrom(sockfd,buf,1024,0,(struct sockaddr *)&clientaddr,&len);
	if(n < 0)
	{
		perror("recvfrom");
		exit(-1);
	}
	//printf("%d\n",htons(clientaddr.sin_port));
	char ip[20];
	inet_ntop(AF_INET,&(clientaddr.sin_addr),ip,20);
	printf("%s:%d\n",ip,htons(clientaddr.sin_port));
	//发送多播数据报
	inet_pton(AF_INET,"224.0.1.1",&(clientaddr.sin_addr));
	n = sendto(sockfd,buf,n,0,(struct sockaddr *)&clientaddr,len);
	if(n < 0)
	{
		perror("sendto");
		exit(-1);
	}
	}
}
