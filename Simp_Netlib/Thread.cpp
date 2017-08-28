/*************************************************************************
    > File Name: Thread.cpp
    > Author: ZY
    > Created Time: 2017年08月27日 星期日 23时01分01秒
 ************************************************************************/

#include"Thread.h"
#include<stdio.h>

ThreadData::ThreadData(const ThreadFunc &func):
	m_func(func)
{
	
}

void ThreadData::run()
{
	m_func();
}

/******************************************************************/
//独立的函数
void *startThread(void* arg)
{
	ThreadData* data = static_cast<ThreadData*>(arg);
	data->run();
	//删除数据
	return nullptr;//c++11 关键字 nullptr 用来避免 0 指针的二异性
}


/*********************************************************************/

Thread::Thread(const ThreadFunc& func):
	m_func(func),m_isRunning(false),m_joined(false),m_tid(0),m_data(nullptr)
{
	
}

Thread::~Thread()
{
	if(m_isRunning&&!m_joined){
		pthread_detach(m_tid);
	}
	if(m_data){
		delete m_data;
		m_data = nullptr;
	}
}

int Thread::run()
{
	assert(!m_isRunning);
	m_isRunning=true;
	m_data = new ThreadData(m_func);
	pthread_attr_t attr;
	pthread_attr_init(&attr);
//设置非分离线程 若是设置为分离detach线程了 可能pthread——create还没返回 该线程就over
//他over就将线程号 系统资源给了其他线程使用
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);
	if(pthread_create(&m_tid,&attr,startThread,static_cast<void*>(m_data))==0){
		printf("pthread_create ok \n");
		//while(1);  这里已经运行了一个 线程函数“m_data” 只是主进程 提前over看不出来
		return 0;
	}else{
		fprintf(stderr,"pthread_create\n");
		m_isRunning=false;
		delete m_data;
		m_data=nullptr;
		return -1;
	}
}

int Thread::join()
{
	assert(m_isRunning);
	assert(!m_joined);
	m_joined=true;
	return pthread_join(m_tid,NULL);
}

bool Thread::isRunning()
{
	return m_isRunning;
}

pthread_t Thread::getTid()
{
	return m_tid;
}














