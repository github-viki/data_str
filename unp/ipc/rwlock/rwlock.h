#include <stdio.h>
typedef struct 
{
	pthread_muetx_t mutex;
	pthread_cond_t cond_r;
	pthread_cond_t cond_w;
	int magic;
	int nwait_r;
	int nwait_w;
	/*
	 * -1代表为写
	 *  0中间态
	 *  大于0 代表正有多少读*/
	int ref;
}pthread_rwlock_t;
#define MAGIC 0X12345678
#define PTHREAD_RWLOCK_INITIALIZER {PTHREAD_MUTEX_INITIALIZER,\
PTHREAD_COND_INITIALIZER,PTHREAD_COND_INITIALIZER,MAGIC,\
0,0,0}
typedef struct pthread_rwlockattr_t;
int pthread_rwlock_init(pthread_rwlock_t *,pthread_rwlockattr_t*);
int pthread_rwlock_destroy(pthread_rwlock_t *);
int pthread_rwlock_rdlock(pthread_rwlock_t *);
int pthread_rwlock_tryrdlock(pthread_rwlock_t *);
int pthread_rwlock_wrlock(pthread_rwlock_t *,pthread_rwlockattr_t *);
int pthread_rwlock_trywrlock(pthread_rwlock_t *);
int pthread_rwlock_unlock(pthread_rwlock_t *);
