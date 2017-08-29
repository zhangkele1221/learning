/*************************************************************************
    > File Name: Mutex.h
    > Author: ZY
    > Created Time: 2017年08月28日 星期一 18时02分39秒
 ************************************************************************/

#ifndef MUTEX_H
#define MUTEX_H

#include<pthread.h>

class MutexLock
{
public:
	MutexLock();
	~MutexLock();
	void lock();
	void trylock();
	void unlock();
	pthread_mutex_t* getMutex();

	//锁的是不可以copy 所以要禁止掉内部的copy相关的函数
	MutexLock(const MutexLock&)=delete;
	MutexLock(MutexLock&&)=delete;
	MutexLock& operator = (const MutexLock&)=delete;
	MutexLock& operator = (MutexLock&&)=delete;
private:
	pthread_mutex_t m_lock;
	volatile bool is_locked;
	//因为锁这个资源是用在多线程当中的 为了得到准确的值 要让编译器每次都要去内存读取
	//防止优化 读到不是真实的值
};


//RAII class MutexLockGuard
class MutexLockGuard{
public:
	explicit MutexLockGuard(MutexLock&);//需要 定义一个显示的拷贝构造
	～MutexLockGuard();

	MutexLockGuard(const MutexLockGuard&)=delete;
	MutexLockGuard(MutexLockGuard&&) =delete;
	MutexLockGuard& operator=(cosnt MutexLockGuard&)=delete;
	MutexLockGuard& operator=(cosnt MutexLockGuard&&)=delete;

private:
	MutexLockGuard& m_mutexlock;//上面的MutexLock不允许拷贝 只能引用了
}

#endif






