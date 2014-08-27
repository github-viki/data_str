#include <stdio.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <net/if.h>
#include <errno.h>
#include <unistd.h>
#include <bits/errno.h>
#include <arpa/inet.h>
typedef struct ifinfo
{
	char name[10];
	char mac[32];
	char ipv4[20];
	char ipv6[64];
	char bcast[20];
	char mask[20];
}ifinfo;
int insight_ifinfo(struct ifconf *p,ifinfo *);
//返回值为接口个数
int get_if_info(struct ifconf *p);
