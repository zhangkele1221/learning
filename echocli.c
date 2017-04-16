/**********************************************
 > File Name: echocli.c
 > Author: ZY
 > Created Time: 2017年04月05日 星期三 20时55分51秒
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
void echo_cli(int sock)
{
	char sendbuf[1024] = {0};
	char recvbuf[1024] = {0};
	while(fgets(sendbuf,sizeof(sendbuf),stdin) != NULL)
	{
		write(sock,sendbuf,strlen(sendbuf));
		read(sock,recvbuf,sizeof(recvbuf));
		fputs(recvbuf,stdout);
		memset(sendbuf,0,sizeof(sendbuf));
		memset(recvbuf,0,sizeof(recvbuf));
	}
	close(sock);
}

int main( )
{
	int sock;
	if((sock = socket(PF_UNIX,SOCK_STREAM,0) )< 0 )
		ERR_EXIT("SOCKET");

	struct sockaddr_un servaddr;
	memset(&servaddr,0,sizeof(servaddr));
	servaddr.sun_family = AF_UNIX;
	strcpy(servaddr.sun_path,"test_socket");
	
	if(connect(sock,(struct sockaddr*)&servaddr,sizeof(servaddr)) < 0)
		ERR_EXIT("connect");

	echo_cli(sock);
	return 0;
}






