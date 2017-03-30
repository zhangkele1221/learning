/**********************************************
 > File Name: echoser.cpp
 > Author: ZY
 > Created Time: 2017年03月30日 星期四 15时16分07秒
*******************************************/

#include <sys/socket.h>
#include <sys/types.h>          /* See NOTES */
#include<string.h>
#include<stdio.h>
#include <arpa/inet.h>
#include <unistd.h>

int main()
{
	int sock;

      sock = socket( AF_INET, SOCK_STREAM ,0);
	  if(sock < 0)
		  printf("error socket");

	struct sockaddr_in  servaddr;
	memset(&servaddr,0,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(5188);
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	/*inet_aton("127.0.0.1",&servaddr.sin_addr)*/

	if(connect(sock,(struct sockaddr*)&servaddr,sizeof(servaddr) ) < 0)
		printf("error connect");

	char sendbuf[1024] = {0};
	char recvbuf[1024] = {0};

	while(fgets(sendbuf,sizeof(sendbuf),stdin) !=NULL)
	{
		write(sock,sendbuf,strlen(sendbuf));
		read(sock,recvbuf,sizeof(recvbuf));

		fputs(recvbuf,stdout);
		memset(sendbuf,0,sizeof(sendbuf));
		memset(recvbuf,0,sizeof(recvbuf));
	}

	close(sock);
	return 0;

}




