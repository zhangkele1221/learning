/**********************************************
 > File Name: echosrv3.c
 > Author: ZY
 > Created Time: 2017年04月02日 星期日 17时27分02秒
*******************************************/

/**********************************************
 > File Name: echoser.cpp
 > Author: ZY
 > Created Time: 2017年03月30日 星期四 15时16分07秒
*******************************************/
#include<stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>          /* See NOTES */
#include<string.h>
#include<stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include<signal.h>
#include <sys/types.h>
#include <sys/wait.h>

#define ERR_EXIT(m) \
	do\
	{\
		perror(m);\
		exit(EXIT_FAILURE);\
	}while(0)

void  echo_srv(int conn)
{
  char recvbuf[1024];
      while(1)
      {
        memset(recvbuf,0,sizeof(recvbuf));
        int ret = read(conn,recvbuf,sizeof(recvbuf));
		if(ret == 0)
		{
			printf("client_close\n");
			break;
		}
		else if(ret == -1)
			ERR_EXIT("read");

		fputs(recvbuf,stdout);
        write(conn,recvbuf,ret); 
       }
}

/*******************************************************
//当多个子进程出现的时候  wait 函数就不够使用啦！
// 你就可以用 waitpid 函数来处理多个僵尸进程！！！！！！ 
// waitpid 提供了wait函数3没有的功能 
// 1 waipid可等待特定的进程 2 提供了非阻塞版本 3 作业控制
*********************************************************/
void handle_sigchld(int sig)
{
	wait(NULL);
	while(waitpid(-1,NULL,WNOHANG)> 0)
		;
}


int main()
{
	signal(SIGCHLD,handle_sigchld);
	 // signal(SIGCHLD,SIG_IGN);
	int listenfd;  
      listenfd = socket( AF_INET, SOCK_STREAM ,0);
	  if(listenfd < 0)
		  printf("error socket");

	struct sockaddr_in  servaddr;
	memset(&servaddr,0,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(5188);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

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
  
     pid_t  pid;
     while(1)
     {
        if( (conn = accept(listenfd,(struct sockaddr*)&peeraddr, &peerlen) )<0 )
		 printf("error accept");
	     //打印客户端地址  和  端口
        printf("ip=%s  port=%d\n",inet_ntoa(peeraddr.sin_addr),
	                                ntohs(peeraddr.sin_port));
		pid=fork();
		if(pid < 0)printf("fork error\n");
		
		if(pid == 0)
		{
	  		close(listenfd);//因为子进程无需监听 所以可以关闭这个描述符
			echo_srv(conn);
			exit(0);
 	  	}
		else
			close(conn);//父进程关闭这个连接描述符号 因为子进程继承了父亲的描述符

	}

	return 0;

}






















