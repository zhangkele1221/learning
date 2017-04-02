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
#include<errno.h>
#include<stdlib.h>


 #define ERR_EXIT(m) \
        do\
        {\
           perror(m);\
           exit(EXIT_FAILURE);\
       }while(0)

/* struct packet
 {
  	int len;
    char buf[1024];
 };
*/

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
            nletf -=  nwritten; 
        }
        return count;// 返回写了多少
    }


 //自己封装一个函数recv_peek  设置flag 为MSG_PEEK 就是只查看缓存数据 不拿走      
 //查看后看情况 调用 read 函数进行读取哦
 //用到了recv函数该函数只能用与socket I/O
ssize_t  recv_peek(int sockfd,void *buf,size_t len )
 {
    while(1)
    {
        int  ret = recv(sockfd ,buf,len ,MSG_PEEK);
            if(ret == -1 && errno == EINTR)
                    continue;
            return ret;
    }
 }
//该函数也是只能用于socket I/O 因为用到了recv函数
//readline函数是在包尾加\n解决粘包问题
ssize_t  readline(int sockfd,void *buf,size_t maxline)
{ 
    int  ret ;
    int nread;
    char *bufp = (char*) buf;
    int nleft = maxline;
    while(1)
    {
        ret = recv_peek(sockfd,bufp,nleft);
        if(ret<0 )
            return ret;//ret<0直接返回 因为recv函数里面对ret<0已经进行了处理
        else if(ret ==0)
            return ret;
        nread = ret;
        int i;
        for(i= 0;i<nread;i++)
        {
            if(bufp[i] =='\n')
            {
                ret = readn(sockfd,bufp,i+1);
                if(ret !=i+1)
                    exit(EXIT_FAILURE);

                return ret;
            }
        }
        //当缓冲区中没有\n 该如何处理 
       if(nread > nleft) // 当出偷窥到的数据超过剩余数据 出错
            exit(EXIT_FAILURE);
        nleft -= nread;
        ret = readn(sockfd, bufp,nread);//读走偷窥到的数据
        if(ret != nread)     //若读取到的数据不等与偷窥到的数据  出错
            exit(EXIT_FAILURE);

        bufp += nread;  //读完后缓冲区指针偏移 继续偷窥查找 \n 循环执行
    }
    return -1;
}

void  echo_cli(int sock)
{
	 char sendbuf[1024] = {0};
    char recvbuf[1024] = {0};

    while(fgets(sendbuf,sizeof(sendbuf),stdin) !=NULL)
    {   
        writen(sock,sendbuf,strlen(sendbuf)); 
        
           int ret = readline(sock,recvbuf,sizeof(recvbuf));
           if(ret == -1)
               ERR_EXIT("readline");
           else if(ret == 0)
           {
                printf("client_close\n");
                break;
           }

           fputs(recvbuf,stdout);
           memset(&sendbuf,0,sizeof(sendbuf));
           memset(&recvbuf,0,sizeof(recvbuf));
    }
	
}


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
		
	struct sockaddr_in localaddr;
	socklen_t  addrlen = sizeof(localaddr);
	if(getsockname(sock,(struct sockaddr*)&localaddr,&addrlen )< 0 )
				ERR_EXIT("getsockname");
	 printf("ip=%s  port=%d\n",inet_ntoa(localaddr.sin_addr),
                                        ntohs(localaddr.sin_port));


	 echo_cli(sock);
	
	return 0;

}




