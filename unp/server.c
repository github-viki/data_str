#include "unp.h"
#define PORT 5000
void sighandler(int signo)
{
	int pid;
	int status;
	int r;
	//while((r = waitpid(-1,&status,WNOHANG)) > 0)
	while((r=wait(NULL))>0)
	{
		printf("get a pid\n");
		fflush(stdout);
	}
	return;
}
int main()
{
	struct sigaction act;
	bzero(&act,sizeof(act));
	act.sa_handler = sighandler;
	sigset_t mask;
	sigemptyset(&mask);
	act.sa_mask = mask;
#ifdef SA_RESTART
	act.sa_flags |= SA_RESTART;
#endif
	sigaction(SIGCHLD,&act,NULL);

	struct sockaddr_in serv_addr;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	int sockfd;
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	int on;
	setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,(void *)&on,sizeof(int));
	size_t len = sizeof(struct sockaddr);
	bind(sockfd,(struct sockaddr *)&serv_addr,len);
	listen(sockfd,10);
	for(;;)
	{
		int connfd = accept(sockfd,NULL,NULL);
		if(connfd < 0)
		{
			if(errno == EINTR)
			{
				perror("\n");
				return (-1);
				//continue;
			}
		}
		int pid = fork();
		if(pid == 0)
		{
			close(sockfd);
			char buf[1024];
			while(1)
			{
				bzero(buf,1024);
				ssize_t n = recv(connfd,buf,1024,0);
				if(n <= 0)
				{
					if(0 == n)
					{
						printf("recv fin\n");
						break;
					}
					perror("recv");
					break;
				}
				n = send(connfd,buf,n,0);
				if(n <= 0)
				{
					perror("send");
					break;
				}
				printf("%s\n",buf);
			}
			close(connfd);
			exit(0);
		}
		if(pid > 0)
		{
			close(connfd);
		}
	}
}
