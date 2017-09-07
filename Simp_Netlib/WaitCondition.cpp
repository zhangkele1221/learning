/*************************************************************************
    > File Name: WaitCondition.cpp
    > Author: ZY
    > Created Time: 2017年09月06日 星期三 17时28分09秒
 ************************************************************************/

#include"WaitCondition.h"

WaitCondition::WaitCondition(MutexLock& mutexlock):
	    m_mutex_lock(mutexlock)
{

	    CHECK(pthread_cond_init(&m_cond_var,NULL));
}

WaitCondition::~WaitCondition()
{

	    CHECK(pthread_cond_destroy(&m_cond_var));
}

void WaitCondition::wait()
{
 //防止多个线程同时请求pthread_cond_wait()的竞争条件（Race   Condition）在调用pthread_cond_wait()前必须由本线程加锁（pthread_mutex_lock()而在更新条件等待队列以前，mutex保持锁定状态，并在线程挂起进入等待前解锁。在条件满足从而离开pthread_cond_wait()之前，mutex将被重新加锁，以与进入pthread_cond_wait()前的加锁动作对应。   
	    CHECK(pthread_cond_wait(&m_cond_var,m_mutex_lock.getMutex()));
}

bool WaitCondition::waitTime(long seconds, long nanoseconds)
{

	    timespec now;
		clock_gettime(CLOCK_REALTIME,&now);//from 1970.1.1 0:0:0
		
		const timespec timeout{
		now.tv_sec+static_cast<time_t>(seconds),now.tv_nsec+nanoseconds};

		return ETIMEDOUT==pthread_cond_timedwait(&m_cond_var,
				m_mutex_lock.getMutex(),&timeout);
}

void WaitCondition::wakeOne()
{

	    CHECK(pthread_cond_signal(&m_cond_var));
}

void WaitCondition::wakeAll()
{

	    CHECK(pthread_cond_broadcast(&m_cond_var));
}








