/*************************************************************************
    > File Name: WaitCondition.h
    > Author: ZY
    > Created Time: 2017年09月06日 星期三 17时19分14秒
 ************************************************************************/

#ifndef WAITCONDITION_H
#define WAITCONDITION_H

#include<pthread.h>
#include<assert.h>
#include<time.h>
#include<errno.h>
#include"Mutex.h"


#define CHECK(ret) ({__typeof__(ret) err=(ret);\
					assert(err==0);})


class WaitCondition
{
public:
	explicit WaitCondition(MutexLock&);
	~WaitCondition();

	void wait();
	bool waitTime(long seconds,long nanoseconds);//阻塞一定的时间
	void wakeOne();
	void wakeAll();

	WaitCondition(const WaitCondition&)=delete;
	WaitCondition(WaitCondition&&)=delete;
	WaitCondition& operator=(const WaitCondition&)=delete;
    WaitCondition& operator=(WaitCondition&&)=delete;

private:
	pthread_cond_t  m_cond_var;
	MutexLock& m_mutex_lock;
};

#endif

















