/*************************************************************************
    > File Name: Thread.h
    > Author: ZY
    > Created Time: 2017年08月27日 星期日 22时46分39秒
 ************************************************************************/

#ifndef THREAD_H
#define THREAD_H
#include<pthread.h>
#include<functional>
#include<assert.h>
class ThreadData{
public:
	typedef std::function<void()> ThreadFunc;//定义了一个函数模板
	explicit ThreadData(const ThreadFunc &func);
	void run();

private:
	ThreadFunc m_func;
};
