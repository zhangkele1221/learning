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

class Thread{
public:
	typedef std::function<void()> ThreadFunc;
	explicit Thread(const ThreadFunc& func);
	~Thread();


	int run();
	int join();
	bool isRunning();
	pthread_t getTid();


private:
	ThreadFunc m_func;
	bool m_isRunning;
	bool m_joined;
	pthread_t m_tid;
	ThreadData* m_data;
};

#endif






