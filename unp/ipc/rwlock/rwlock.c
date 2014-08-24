#include "rwlock.h"

int pthread_rwlock_init(pthread_rwlock_t *lock,pthread_rwlock_t *attr)
{
	if(attr != NULL)
		return(EINVAL);
	int result;
	result = pthread_mutex_init(&(lock->mutex),NULL);
	if(result != 0)
		pthread_mutex_destroy(&(lock->mutex));
	result = pthread_cond_init(&(lock->cond_r),NULL);
	result = pthread_cond_init(&(lock->cond_w),NULL);
	return result;
}
int pthread_rwlock_destroy(pthread_rwlock_t *lock)
{
	if(lock->magic != MAGIC)
		return(EINVAL);
	if(lock->nwait_r > 0 || lock->nwait_w >0 \
			||lock->ref != 0)
		return(EBUSY);
	pthread_mutex_destroy(&(lock->mutex));
	pthread_cond_destroy(&(lock->cond_r));
	pthread_cond_destroy(&(lock->cond_w));
	return 0;
}
int pthread_rwlock_rdlock(pthread_rwlock_t *lock)
{
	if(lock->magic != MAGIC)
		return(EINVAL);
	int result;
	result = pthread_mutex_lock(&(lock->mutex));
	if(result < 0)
		return result;
	//这里的while条件中，如果有写阻塞则也要cond_wait;
	//不用管读的状态
	while(lock->nwait_w > 0 || lock->ref == -1)
	{
		lock->nwait_r++;
		result = pthread_cond_wait(&lock->cond_r,&lock->mutex);
		//当条件满足后，则可以减去一个等待的读
		lock->nwait_r-- ;
		if(result != 0)
			break;
	}
	if(result == 0)
	{
		//使得结构体的状态变为读
		lock->ref++;
	}
	pthread_mutex_unlock(lock->mutex);
	return result;
}
int pthread_rwlock_wrlock(pthread_rwlock_t *lock)
{
	if(lock->magic != MAGIC)
		return EINVAL;
	pthread_mutex_lock(&lock->mutex);
	int result;
	while(lock->ref != 0)
	//这里只要没有当前读，不管有没有等待读。
	//还要判断是否有其他写。所以ref 不能是>0
	//应该是！=0
	{
		lock->nwait_w++;
		result = pthread_cond_wait(&lock->cond_w);
		lock->nwait_w--;
		if(result != 0)
			break;
	}
	if(result == 0)
		lock->ref = -1;
	pthread_mutex_unlock(&lock->mutex);
	return result;
}
int pthread_rwlock_unlock(pthread_rwlock_t *lock)
{
	if(lock->magic != MAGIC)
		return EINVAL;
	pthread_mutex_lock(&lock->mutex);
	if(lock->ref == -1)
		{
			lock->ref = 0;
			pthread_cond_broadcast(&lock->cond_w);
			pthread_cond_broadcast(&lock->cond_r);
		}
	else if(lock->ref > 0)
	{
		lock->ref --;
		if(lock->ref == 0)
		{
			pthread_cond_broadcast(&lock->cond_w);
		}
	}
	pthread_mutex_unlock(&lock->mutex);
}
