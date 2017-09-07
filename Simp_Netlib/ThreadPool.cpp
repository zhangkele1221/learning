/*************************************************************************
    > File Name: ThreadPool.cpp
    > Author: ZY
    > Created Time: 2017年09月07日 星期四 20时56分31秒
 ************************************************************************/

#include"ThreadPool.h"
#include"Thread.h"
#include<functional>


ThreadPool::ThreadPool(int pool_size):
	    m_pool_size(pool_size),
		    m_task_cond_var(m_task_mutex)
{

	    init();
}
ThreadPool::~ThreadPool()
{

	    if(m_pool_state!=STOPPED)
	    {
			destroy();
		}
}

int ThreadPool::init()
{

	    //todo :lazy loading threads instead of creating threads at once
       cout<<m_pool_size<<" in initialize_threadpool() threads created by the thread pool"<<endl;
	   m_pool_state=STARTED;
       m_ThreadVec.reserve(m_pool_size);
	   for(int i=0;i<m_pool_size;i++){
			Thread thread(std::bind(&ThreadPool::workerThread,this));//member function must use '&'
            m_ThreadVec.push_back(thread);
            m_ThreadVec.back().run();
        }
        return 0;
}

int ThreadPool::destroy()
{
       m_task_mutex.lock();
	   m_pool_state=STOPPED;
       m_task_mutex.unlock();
       cout<<"in destroy_threadpool() Brocasting STOP signals to all threads..."<<endl;
	   m_task_cond_var.wakeAll();

	   int ret=-1;
	   for(int i=0;i<m_pool_size;i++)
	   {
		   ret=m_ThreadVec[i].join();
		   cout<<"in destroy_threadpool() pthread_join() returned "<<ret<<":"<<strerror(errno)<<std::endl;
																								  m_task_cond_var.wakeAll();//trying waking up a bunch of threads that are still waiting
                                                                                                }
        cout<<m_pool_size<<" in destroy_threadpool() threads exited from the threadpool"<<std::endl;                                                                                            return 0;
		}

int ThreadPool::addTask(const Task& task)
{                                           
	m_task_mutex.lock();    //todo :put a limit on how many task canbe added at most
	m_tasks.push_back(task);
	m_task_cond_var.wakeOne();//wake up one thread that is waiting
	m_task_mutex.unlock();
	
	return 0;
}

void ThreadPool::workerThread(){
		cout<<"in execute_thread() starting thread "<<pthread_self()<<std::endl;
		while(m_pool_state==STARTED){
		//to pick a task
			cout<<"in execute_thread() locking: "<<pthread_self()<<std::endl;
			m_task_mutex.lock();
		//we need to put pthread_cond_wait in a loop for two reasons:
		//1 there can be spurious wakeups(due to signal/ENITR)
		//2 when mutex is released for waiting ,another thread can be waken up
		//from a signal/broadcast and that thread can messup the condition.
	//so when the currrnt thread wakes up the condition may no longer be actually true
		while((m_pool_state==STARTED)&&(m_tasks.empty())){
		//wait until there is a task in the queue                 
	    //unlock mutex while wait,then lock it back when signaled       
			cout<<"in execute_thread() unlock and waiting:"<<pthread_self()<<std::endl;
			m_task_cond_var.wait();                 
			cout<<"in execute_thread() signaled and locking"<<endl;

		}

		if(m_pool_state==STOPPED){
		  cout<<"in execute_thread() unlocking and exiting"<<pthread_self()<<std::endl;
		  m_task_mutex.unlock();
		  pthread_exit(NULL);
		}

		Task task=m_tasks.front();
		m_tasks.pop_front();
		cout<<"in execute_thread() unlocking: "<<pthread_self()<<std::endl;
		m_task_mutex.unlock();
		task.run();
		
		}
		return ;
}

size_t ThreadPool::dequeSize()
{
	MutexLockGuard lockguard(m_task_mutex);
	return m_tasks.size();
}

