/*************************************************************************
    > File Name: echosrv_poll.cpp
    > Author: ZY
    > Created Time: 2017年04月16日 星期日 14时03分31秒
 ************************************************************************/



#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <sys/wait.h>
#include <poll.h>

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#include <vector>
#include <iostream>

using namespace std;

#define  ERR_EXIT(m) \
	do \
	{	\
			perror(m);\
			exit(EXIT_FAILURE); \
	} while(0)

typedef  std::vector<struct pollfd> PollFdList;

int main(void)
{
	signal(SIGPIPE, SIG_IGN);
	signal(SIGCHLD, SIG_IGN);

	int listenfd;

	if ((listenfd = socket(PF_INET, SOCK_STREAM | SOCK_NONBLOCK | SOCK_CLOEXEC, 
							IPPROTO_TCP)) < 0)
		ERR_EXIT("socket");

	struct sockaddr_in servaddr;
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(5188);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	int on = 1;
	if(setsockopt(listenfd, SOL_SOCKET ,SO_REUSEADDR, &on,sizeof(on)) < 0)
		ERR_EXIT("setsockoopt");
	
	if (bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)
		ERR_EXIT("bind");
	if (listen(listenfd, SOMAXCONN) < 0)
		ERR_EXIT("listen");

//poll  函数的使用的方法
	struct pollfd  pfd;
	pfd.fd = listenfd;
	pfd.events = POLLIN ;

/*****这里运用了STL中的vector类模板创建一个类 方便删除已关闭的描述符号*********
*******因为数组删除一个元素没有vector方便**************************/
	PollFdList  pollfds ;
	pollfds.push_back(pfd);

	int nready;
	struct sockaddr_in  peeraddr;
	socklen_t  peerlen;
	int connfd;

	while (1)
	{
		nready = poll(&*pollfds.begin(), pollfds.size(), -1 );
		if (nready == -1)
		{
			if (errno == EINTR)
			     continue;

			ERR_EXIT("poll");
		}
		if (nready == 0)  //没有发生 或者说超时   因为我们设置的是 负数so是永远等待
			 continue;

/*****数组中的第0个元素 关于listenfd描述符有情况发生 将其放入accept4中**********/
		if (pollfds[0].revents & POLLIN )
		{
			peerlen = sizeof(peeraddr);
			connfd = accept4(listenfd ,(struct sockaddr*)&peeraddr,
							&peerlen, SOCK_NONBLOCK | SOCK_CLOEXEC );

			if (connfd == -1)
				ERR_EXIT("accept4");

		//将接收到的connfd放到  数组中去监测
		pfd.fd = connfd;
		pfd.events = POLLIN ;
		pfd.revents = 0 ;
		pollfds.push_back(pfd);
		--nready ;  //将返回值 nready 减1   因为nready为返回的就绪的描述符数目 

 		//连接ok   打印已链接的客户端的地址
		cout<<"ip="<<inet_ntoa(peeraddr.sin_addr)<<
				" port="<<ntohs(peeraddr.sin_port)<<std::endl;
		
		if(nready == 0 )
			continue;
		
		}

		//遍历描述符    要知道这里为什么要 it = poolfds.begin()+1 吗？
		//因为第0个是listenfd  描述符  后面的才是connfd描述符
		for(PollFdList::iterator it=pollfds.begin()+1;
				it !=pollfds.end() && nready > 0; ++it)
		{
			if(it->revents & POLLIN )
			{
				--nready;
				connfd = it->fd;
				char buf[1024] = {0};
				int ret = read(connfd , buf , 1024);
				if(ret == -1)
					ERR_EXIT("read");
				if(ret == 0)
				{
					    cout<<"client close"<<endl;
						it = pollfds.erase(it);//知道为什么要踢出吗？
						--it; //要知道这里为什么  -- ！！！！

						close(connfd);
						continue;
				}
				
				    cout<<buf;
					write(connfd, buf, strlen(buf));

			}
		}

	}

	return 0;

}

