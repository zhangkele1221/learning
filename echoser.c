/**********************************************
 > File Name: echoser.cpp
 > Author: ZY
 > Created Time: 2017年03月30日 星期四 15时16分07秒
*******************************************/


#include<errno.h>
#include <sys/socket.h>
#include <sys/types.h>          /* See NOTES */
#include<string.h>
#include<stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include<stdlib.h>
#include<sys/un.h>

 #define ERR_EXIT(m) \
      do\
      {\
         perror(m);\
         exit(EXIT_FAILURE);\
     }while(0)
 
void echo_srv(int conn)
{
	int n;
	char recvbuf[1024];
	while(1)
	{
		memset(recvbuf,0,sizeof(recvbuf));
		n = read(conn,recvbuf,sizeof(recvbuf));
		if(n == -1)	
		{
			if(n == EINTR)
				continue;
			
			ERR_EXIT("read");
		}
		else if(n == 0)
		{
			printf("client close\n");
			break;
		}
		fputs(recvbuf,stdout);
		write(conn,recvbuf,strlen(recvbuf));

	}
}

int main()
{
	int listenfd;

      listenfd = socket( AF_UNIX, SOCK_STREAM ,0);
	  if(listenfd < 0)
		  ERR_EXIT("socket");

	struct sockaddr_un  servaddr;
	memset(&servaddr,0,sizeof(servaddr));
	servaddr.sun_family = AF_UNIX;
	strcpy(servaddr.sun_path,"test_socket");
	
	if(bind(listenfd, (struct sockaddr*)&servaddr,sizeof(servaddr)) < 0)
		ERR_EXIT("bind");

	if(listen(listenfd,SOMAXCONN) < 0 )
		ERR_EXIT("listenfd");

	int pid, conn;
	while(1)
	{
		conn = accept(listenfd,NULL,NULL);
		if(conn == -1)
		{
			if(conn == EINTR)
				continue ;
			ERR_EXIT("accept");
		}
		pid = fork();
		if(pid == -1)
			ERR_EXIT("fork");
		if(pid == 0)
		{
			close(listenfd);
			echo_srv(conn);
			exit(EXIT_SUCCESS);
		}
		close(conn);
	}

	return 0;

}











