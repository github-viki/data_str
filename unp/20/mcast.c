#include "unp.h"
int add_to_mcast(int sockfd,char *ip)
{
	struct ip_mreq mcast;
	bzero(&mcast,sizeof(mcast));
	struct in_addr maddr;
	if(inet_pton(AF_INET,ip,&maddr) < 0)
	{
		perror("inet_pton");
		return -1;
	}
	mcast.imr_multiaddr = maddr;
	if(setsockopt(sockfd,IPPROTO_IP,IP_ADD_MEMBERSHIP,&mcast,sizeof(mcast)) < 0)
	{
		perror("add membership");
		return -1;
	}
}
