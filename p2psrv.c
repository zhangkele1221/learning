/**********************************************
 > File Name: echoser.cpp
 > Author: ZY
 > Created Time: 2017年03月30日 星期四 15时16分07秒
*******************************************/

#include <sys/socket.h>
#include <sys/types.h>          /* See NOTES */
#include <string.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <signal.h>

#define ERR_EXIT(m) \
        do\
        {\
		   perror(m);\
	       exit(EXIT_FAILURE);\
        }while(0) 


void handler(int sig)
{
	printf("recv a sig = %d\n",sig);
	exit(0);
}


int main()
{
	int listenfd;

      listenfd = socket( AF_INET, SOCK_STREAM ,0);
	  if(listenfd < 0)
		  printf("error socket");

	struct sockaddr_in  servaddr;
	memset(&servaddr,0,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(5188);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	/*servaddr.sin_addr.s_addr = inet_addr("127.0.0.1")*/
	/*inet_aton("127.0.0.1",&servaddr.sin_addr)*/

	int on = 1;
	//设置REUSEADDR选项 可以使服务器不必等待TIME——WAIT状态消失再重启动服务器 
	if(setsockopt(listenfd, SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on))< 0 )
		printf("REUSEADDR  error\n");

	if(bind(listenfd,(struct sockaddr*)&servaddr,sizeof(servaddr))< 0)
		printf("error bind\n");

	 if( listen(listenfd,SOMAXCONN ) < 0 )
		printf("error listen ");
	//主动套接子   和   被动套接子的  区别  	
 
	//accept函数从已完成连接队列返回第一个连接  如果已经完成连接队列为空则阻塞
	struct sockaddr_in peeraddr;
	socklen_t  peerlen = sizeof(peeraddr);
	int conn;//链接的套接子
	if( (conn = accept(listenfd,(struct sockaddr*)&peeraddr, &peerlen) )<0 )
		 printf("error accept");
	     //打印客户端地址  和  端口
         printf("ip=%s  port=%d\n",inet_ntoa(peeraddr.sin_addr),
		                                ntohs(peeraddr.sin_port));


	pid_t pid;
	pid = fork();
	if(pid == -1)
		ERR_EXIT("fork");
	if(pid == 0)
	{	
		signal(SIGUSR1,handler);
		char sendbuf[1024] = {0};
		while(fgets(sendbuf,sizeof(sendbuf),stdin) !=NULL)
		{
			write(conn,sendbuf,strlen(sendbuf));
			memset(sendbuf,0,sizeof(sendbuf));
		}
		printf("child close\n");
		exit(0);
	}
	else
	{
	      char recvbuf[1024];
		  while(1)
	   	  {
		      memset(recvbuf,0,sizeof(recvbuf));
			  int ret = read(conn,recvbuf,sizeof(recvbuf));
       		  if(ret == -1)
				  ERR_EXIT("read");
			  else if(ret == 0)
			  {
				  printf("peer close\n");
					break;
			  }
			  fputs(recvbuf,stdout);
		  }
		printf("parent close\n");
	//这里为了子进程也能顺利退出加上了信号通知子进程的 某个函数 然后在处理
		kill(pid,SIGUSR1);
		exit(0);
	}
	
	return 0;
}
 



