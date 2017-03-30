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

 #define ERR_EXIT(m) \
      do\
      {\
         perror(m);\
         exit(EXIT_FAILURE);\
     }while(0)

 struct packet
 {
    int len;
	char buf[1024];
 };


//这是在应用层设计类一个包装函数 解决粘包问题
ssize_t readn(int fd, void *buf,size_t count)
{
	size_t nletf = count;//**********不注释啦肯定要理解哦这段函数**
	ssize_t nread;
	char *bufp = (char*)buf;
	while(nletf > 0)
	{
		if( (nread = read(fd,bufp,nletf)) < 0 )
		{
			if(errno == EINTR)
				continue;
			return -1;
		}
		else if(nread == 0)// 还是不偷懒了注释下吧
			return count - nletf;//nleft变小了 count变大了表示读取了多少
		bufp += nread;  //指针位置要变动的
		nletf -= nread; 
	}
	return count;// 返回读取了多少
}

 //这是在应用层设计类一个包装函数 解决粘包问题
  ssize_t writen(int fd, const void *buf,size_t count)
  {
      size_t nletf = count;//**********不注释啦肯定要理解哦这段函数**
      ssize_t nwritten;
      char *bufp = (char*)buf;
      while(nletf > 0)
      {
          if( (nwritten = write(fd,bufp,nletf) ) < 0 )
          {
              if(errno == EINTR)
                  continue;
              return -1;
          }
          else if(nwritten == 0)// 还是不偷懒了注释下吧
              continue ; //nwritten 读取为0表示什么也没做 继续干吧少年
          bufp += nwritten;  //指针位置要变动的
          nletf -=	nwritten; 
      }
      return count;// 返回写了多少
  }



 void  do_service(int conn)
 {
	 struct packet recvbuf;
	 int n;
        while(1)
        {
         memset(&recvbuf,0,sizeof(recvbuf));
         int ret = readn(conn,&recvbuf.len,4);
         if(ret == -1)
			 ERR_EXIT("read");
		 else if(ret < 4)
         {
              printf("client_close\n");
              break;
         }
         
		 n = ntohl(recvbuf.len);
		 ret = readn(conn,recvbuf.buf,n);
		 if(ret == -1)
			 ERR_EXIT("read");
		 else if(ret < n)
		 {
			 printf("client close\n");
			 break;
		 }

          fputs(recvbuf.buf,stdout);
          writen(conn,&recvbuf,4+n); 
        
		}
 
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

//	char recvbuf[1024];
	while(1)
	{
		do_service(conn);
//		memset(recvbuf,0,sizeof(recvbuf));
//		int ret = read(conn,recvbuf,sizeof(recvbuf));
//		fputs(recvbuf,stdout);
//		write(conn,recvbuf,ret);
		
	}

	close(conn);
	close(listenfd);	
	return 0;

}




