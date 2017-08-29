/*************************************************************************
    > File Name: Mutex.cpp
    > Author: ZY
    > Created Time: 2017年08月29日 星期二 22时06分51秒
 ************************************************************************/

#include"Mutex.h"
#include<assert.h>


//__typeof__ 是c+11用来得到一个未知类型的  类型的方法  该宏函数用来对函数返回进行判断
#define CHECK(ret) ({__typeof__(ret) err=(ret);\
					assert(err==0);})

/***********************************************************/
MutexLock::MutexLock()
	    :is_locked(false)
{
	    CHECK(pthread_mutex_init(&m_lock,NULL));
}

MutexLock::~MutexLock()
{
	    //while(is_locked);
		assert(is_locked==false);
	    //unlock();
		pthread_mutex_destroy(&m_lock);//why CHECK the ret here will assert error?
}

void MutexLock::lock()
{
	    CHECK(pthread_mutex_lock(&m_lock));
		    is_locked=true;
}

void MutexLock::tryLock()
{
	    CHECK(pthread_mutex_trylock(&m_lock));
		    is_locked=true;
}

void MutexLock::unlock()
{
	    is_locked=false;//先设置解锁标志 再去解锁 防止 竞争
		CHECK(pthread_mutex_unlock(&m_lock));
}

pthread_mutex_t* MutexLock::getMutex()
{
	    return &m_lock;
}

/*************************MutexLockGuard***************************/
MutexLockGuard::MutexLockGuard(MutexLock& mutexlock)
	    :m_mutexlock(mutexlock)
{
	    m_mutexlock.lock();
}

MutexLockGuard::~MutexLockGuard(){

	    m_mutexlock.unlock();
}












