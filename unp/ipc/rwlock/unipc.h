#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>
int get_mq_attr(mqd_t);
int send_mq_msg(mqd_t,char *);
int recv_mq_msg(mqd_t);
