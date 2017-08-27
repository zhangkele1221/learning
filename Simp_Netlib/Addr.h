/*************************************************************************
    > File Name: Addr.h
    > Author: ZY
    > Created Time: 2017年08月27日 星期日 22时27分14秒
 ************************************************************************/

#ifndef ADDR_H
#define ADDR_H

#include<arpa/inet.h>

class Addr{
public:
	Addr():_ip(0),_port(0){}
	explicit Addr(const char* ip ,int port);
	~Addr();

	struct sockaddr_in _addr;
	const char*  _ip;
	int _port;
};

#endif







