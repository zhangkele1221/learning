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



void echo_cli(int sock)
{
      struct sockaddr_in servaddr;
      memset(&servaddr,0,sizeof(servaddr));
      servaddr.sin_family = AF_INET;
      servaddr.sin_port = htons(5188);
      servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); //htonl(INADDR_ANY);
	  //udp设置connect可以解决ICMP异步错误 会有返回信息 可以在服务器不打开的情况下 客户端有  返回信息 
  	connect(sock,(struct sockaddr*)&servaddr,sizeof(servaddr) );
	  int ret;
	  char sendbuf[1024] = {0};
	  char recvbuf[1024] = {0};
	  while(fgets(sendbuf,sizeof(sendbuf), stdin) != NULL )
	  {
           /* sendto(sock,sendbuf,sizeof(sendbuf),0,
	          	 (struct sockaddr*)&servaddr,sizeof(servaddr));*/
			sendto(sock,sendbuf,strlen(sendbuf),0,NULL,0);
			ret = recvfrom(sock,recvbuf,sizeof(recvbuf),0,NULL,NULL);

			if(ret == -1)
			{
				if(errno == EINTR)
					continue;
				ERR_EXIT("recvfrom");
			}
			fputs(recvbuf,stdout);
			memset(sendbuf,0,sizeof(sendbuf));
			memset(recvbuf,0,sizeof(recvbuf));
	  }
	  close(sock);
	  
}


int main()
{
	int sock;
	if ((sock = socket(AF_INET,SOCK_DGRAM,0) ) < 0 )
		ERR_EXIT("socket");

	echo_cli(sock);

	return 0;

}








