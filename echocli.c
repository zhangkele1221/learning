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
            nletf -=  nwritten; 
        }
        return count;// 返回写了多少
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
	
	int n;
	struct packet sendbuf;
	struct packet recvbuf;
	memset(&sendbuf,0,sizeof(sendbuf));
	memset(&recvbuf,0,sizeof(recvbuf));

//	char sendbuf[1024] = {0};
//	char recvbuf[1024] = {0};

	while(fgets(sendbuf.buf,sizeof(sendbuf),stdin) !=NULL)
	{	
		 n = strlen(sendbuf.buf);
		 sendbuf.len = htonl(n);
   		 //writen(sock,sendbuf,sizeof(sendbuf));// 修改了strlen 发送定长包
		writen(sock,&sendbuf,4+n); 
		
           int ret = readn(sock,&recvbuf.len,4);
           if(ret == -1)
               ERR_EXIT("read");
           else if(ret < 4)
           {
                printf("client_close\n");
                break;
           }
    
           n = ntohl(recvbuf.len);
           ret = readn(sock,recvbuf.buf,n);
           if(ret == -1)
               ERR_EXIT("read");
           else if(ret < n)
           {
              printf("client close\n");
              break;
		   }

		   fputs(recvbuf.buf,stdout);
		   memset(&sendbuf,0,sizeof(sendbuf));
		   memset(&recvbuf,0,sizeof(recvbuf));
	}

	close(sock);
	return 0;

}




