/**********************************************
 > File Name: udp_echoser.c
 > Author: ZY
 > Created Time: 2017年04月05日 星期三 14时20分20秒
*******************************************/

#include <sys/socket.h>
#include <sys/types.h> 
#include<stdio.h>
#include<errno.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include <netinet/in.h>
#include <arpa/inet.h>

 #define ERR_EXIT(m) \
      do\
      {\
          perror(m);\
          exit(EXIT_FAILURE);\
      }while(0) 
void echo_srv(int sock)
{
	struct sockaddr_in  peeraddr;
	socklen_t  peerlen;
	int n;
	char recvbuf[1024] = {0};
	while(1)
	{
		peerlen = sizeof(peeraddr);
		memset(recvbuf,0,sizeof(recvbuf));
        n = recvfrom(sock,recvbuf,sizeof(recvbuf),0,
				      (struct sockaddr*)&peeraddr,&peerlen);
		if( n==-1 )
		{
			if(errno == EINTR)
				continue;
			ERR_EXIT("recvfrom");
		}
		else if(n > 0)
		{
			fputs(recvbuf,stdout);
			sendto(sock,recvbuf,n,0,(struct sockaddr*)&peeraddr,peerlen);

		}
	}
	
	close(sock);
}

int main()
{
	int sock;
	if ((sock = socket(AF_INET,SOCK_DGRAM  ,0) ) < 0 )
		ERR_EXIT("socket");
	struct sockaddr_in servaddr;
	memset(&servaddr,0,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(5188);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    
    if(bind(sock,(struct sockaddr*)&servaddr,sizeof(servaddr)) < 0 )
		ERR_EXIT("bind");

	echo_srv(sock);

	return 0;

}








