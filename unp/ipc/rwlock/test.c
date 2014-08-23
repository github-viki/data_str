#include "unipc.h"
#define N 1000000
//argv[1]线程写
//argv[2]线程读
//采用互斥锁
//是一个单缓冲
int buf[N];
struct 
{
	pthread_mutex_t mutex;
	pthread_cond_t cond;
	int nready;
	int hasread;
}get={
	PTHREAD_MUTEX_INITIALIZER,
	PTHREAD_COND_INITIALIZER,
	0,
	0
};
struct 
{
	pthread_mutex_t mutex;
	int index;
}put = {PTHREAD_MUTEX_INITIALIZER,0};
void catch_sigint(int signo)
{
	if(signo == SIGINT)
	{
		fflush(stdout);
		exit(0);
	}

}
void *producer(void *arg)
{
	for(;;)
	{
	pthread_mutex_lock(&put.mutex);
	if( put.index >= N)
	{
		pthread_mutex_unlock(&put.mutex);
		return NULL;
	}
	buf[put.index ++] = put.index;
	pthread_mutex_unlock(&put.mutex);
	pthread_mutex_lock(&get.mutex);
	if(get.nready - get.hasread == 0)
	{
		pthread_cond_broadcast(&get.cond);
	}
	get.nready++;
	//printf("%u %d\n",pthread_self(),put.index);
	pthread_mutex_unlock(&get.mutex);
	(*((int *)arg))++;
	}
	return NULL;
}
void *consumer(void *arg)                                            
{
	for(;;)
	{
	int result;
	result = pthread_mutex_lock(&get.mutex);
	if(get.hasread >= N)
	{
		pthread_mutex_unlock(&get.mutex);
		return NULL;
	}
	while(get.nready - get.hasread == 0)
		
	{
		//这里应该加一个判断是否可以结束。
		//因为当另外一个read线程读了所有的数据，此时写进程就不会再新加任何数据。
		//所以 加一个判断
		if(get.hasread >= N)
		{
			pthread_mutex_unlock(&get.mutex);
			return NULL;
		}
		pthread_cond_wait(&(get.cond),&(get.mutex));
	}
	get.hasread++;
	pthread_mutex_unlock(&get.mutex);
	(*((int *)arg))++;
	}
	return NULL;
}
int main(int argc,char *argv[])
{
	struct sigaction act;
	bzero(&act,sizeof(act));
	act.sa_handler = catch_sigint;
	sigaction(SIGINT,&act,NULL);
	int npro = 1;
	int ncon =1;
	npro =  atoi(argv[1]);
	ncon = atoi(argv[2]);
	pthread_t *ttid = (pthread_t *) malloc(sizeof(pthread_t)*(npro+ncon));
	int *count = (int *) malloc(sizeof(int)*(npro+ncon));
	int i = 0;
	for(i;i<ncon;i++)
	{
		pthread_create(&ttid[i],NULL,consumer,&count[i]);
	}
	i=0;
	for(i;i<npro;i++)
	{
		pthread_create(&ttid[i+ncon],NULL,producer,&count[i+ncon]);
	}
	for(i=0;i<npro+ncon;i++)
	{
		pthread_join(ttid[i],NULL);
	}
	for(i=0;i<npro+ncon;i++)
		printf("count[%d] :%d \n",i,count[i]);
}	
