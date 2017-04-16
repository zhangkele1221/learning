/**********************************************
 > File Name: TCP_Serv_select.c
 > Author: ZY
 > Created Time: 2017年04月12日 星期三 15时31分28秒

（1）服务器
       传统的单进程服务器一旦accept了客户端的TCP连接后，就转入客户请求的处理，
处理完成后才能再一次的调用accept来接受下一个客户端的TCP连接和请求。
       为了更加提高单进程server的性能，本程序使用select这种IO复用的模式，同时监听已经
连接的socket端口和正在监听的服务器listening端口，这样一来，就可以大大提升sever处理并发
请求的能力。

      本例中，如果我们在某次select中捕获到listenfd的IO状态有变，也就是说有新的客户端连接，我们不会马上做客户端的请求处理，而是把连接到的socket fd插入到select的监听集合中，然后继续探测其他监听集有IO状态变化（这里的其他监听集就是每个已经连接的客户端的socket fd的状态），如果有变化则马上处理client的请求。这样做的好处是我们及时处理了已连接的客户端的请求，而不是被新连接的客户端的请求所抢占，反正旧客户端被饿死的情况发生。
      本例是在单进程服务器上使用select，所以适合简单客户请求处理，也就是短连接的情况，如果需要长时间服务于多个客户，可以使用fork加以辅助

*******************************************/


//server.cpp
#include<sys/types.h>
#include<sys/socket.h>
#include<strings.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<errno.h>
#include<signal.h>
#include<sys/wait.h>
#include<pthread.h>

#define LISTEN_PORT 84

void str_echo(int sockfd)            // 服务器收到客户端的消息后的响应
{
    ssize_t n;
    char line[512];

    printf("ready to read\n");

    while( (n=read(sockfd,line,512))>0 )
    {
        line[n]='\0';
        printf("Client Diary: %s\n",line);

        char msgBack[512];
        snprintf(msgBack,sizeof(msgBack),"recv: %s\n",line);
        write(sockfd,msgBack,strlen(msgBack));
        bzero(&line,sizeof(line));
    }

    printf("end read\n");

}

void sig_child(int signo)         //父进程对子进程结束的信号处理
{
    pid_t pid;
    int   stat;

    while( (pid=waitpid(-1,&stat,WNOHANG))>0)
    printf("child %d terminated\n",pid);

    return;
}


int main(int argc, char **argv)
{

    int listenfd, connfd;
    pid_t childpid;
    socklen_t chilen;

    struct sockaddr_in chiaddr,servaddr;

    //values for select
    int i,maxi,maxfd,sockfd;
    int nready,client[FD_SETSIZE];
    ssize_t n;
    fd_set rset,allset;
    //values for select

    listenfd=socket(AF_INET,SOCK_STREAM,0);
    if(listenfd==-1)
    {
        printf("socket established error: %s\n",(char*)strerror(errno));    
    }

    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family=AF_INET;
    servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
    servaddr.sin_port=htons(LISTEN_PORT);

    int bindc=bind(listenfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
    if(bindc==-1)
    {
        printf("bind error: %s\n",strerror(errno));
    }

    listen(listenfd,SOMAXCONN);               //limit是SOMAXCONN

    //initial "select" elements
    maxfd=listenfd;                     //新增listenfd，所以更新当前的最大fd
    maxi=-1;
    for(i=0;i<FD_SETSIZE;i++)
    client[i] = -1;
    FD_ZERO(&allset);
    FD_SET(listenfd,&allset);    
    //initial "select" elements

    signal(SIGCHLD,sig_child);
    for(;;)
    {
        rset=allset;   //rset和allset的搭配使得新加入的fd要等到下次select才会被监听
        nready=select(maxfd+1,&rset,NULL,NULL,NULL); //一开始select监听的是监听口
        //如果有timeout设置，那么每次select之前都要再重新设置一下timeout的值
        //因为select会修改timeout的值。
        
        if(FD_ISSET(listenfd,&rset))
        {
            chilen=sizeof(chiaddr);

            connfd=accept(listenfd,(struct sockaddr*)&chiaddr,&chilen);
            //阻塞在accept，直到三次握手成功了才返回
            if(connfd==-1)
            printf("accept client error: %s\n",strerror(errno));
            else        
            printf("client connected\n");

            for(i=0;i<FD_SETSIZE;i++)
            {
                if (client[i]<0)
                {
                    client[i]=connfd;    //找一个最小的插进入，并且缓存在client中，这样就不需要遍历所有fd，包括为0位的，来查看是否ISSET
                    break;
                }
            }
            if(i==FD_SETSIZE)
            {
                printf("too many clients\n");
                exit(0);
            }
            FD_SET(connfd,&allset);   //新加入的描述符，还没判断是否可以或者写，所以后面使用rset而不是allset

            if(connfd>maxfd)    //maxfd是为了下次select，作为参数使用
              maxfd=connfd;
            if(i>maxi)            //maxi是为了减少遍历所监听fd的次数
              maxi=i;
            if(--nready<=0) //nready用来辅助计数，这样就不要遍历整个client数组
              continue;
        }


        for(i=0;i<=maxi;i++)
        {
            if( (sockfd=client[i]) <0)
            continue;
            if(FD_ISSET(sockfd,&rset))
            {
                //单进程的环境下，不可以阻塞在这里，可以选择非阻塞，线程，超时.也就无法防范拒绝服务的攻击
                //比较适合短连接的情况
                
                //单进程不使用fork的情况！                
                //test fork
                //                if((childpid=fork())==0)
                {
                    close(listenfd);
                    printf("client from %s\n",inet_ntoa(chiaddr.sin_addr));
                    str_echo(connfd);
                    close(connfd);

                    exit(0);    
                }
                //                else if (childpid<0)
                //                printf("fork error: %s\n",strerror(errno));
                close(connfd);
                //test fork
                
                FD_CLR(sockfd,&allset);                  //清除，表示已被处理
                client[i]=-1;
                
                printf("can read : %d,%d,%d\n",i,sockfd,nready);
                if(--nready<=0)      //nready用来辅助计数，这样就不要遍历整个client数组
                break;
            }
        }
    }
}
