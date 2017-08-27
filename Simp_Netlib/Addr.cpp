/*************************************************************************
    > File Name: Addr.cpp
    > Author: ZY
    > Created Time: 2017年08月27日 星期日 22时35分42秒
 ************************************************************************/

#include"Addr.h"
#include<string.h>
Addr::Addr(const char*ip,int port):_ip(ip),_port(port){
	bzero(&_addr.sin_addr.s_addr,sizeof(_addr.sin_addr.s_addr));
	_addr.sin_family=AF_INET;
	_addr.sin_port=htons(port);
	_addr.sin_addr.s_addr=inet_addr(ip);
}

Addr::~Addr(){

}
