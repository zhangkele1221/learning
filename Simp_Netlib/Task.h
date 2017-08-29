/*************************************************************************
    > File Name: Task.h
    > Author: ZY
    > Created Time: 2017年08月29日 星期二 22时52分52秒
 ************************************************************************/

#ifndef TASK_H
#define TASK_H

#include<pthread.h>
#include<functional>

class Task
{
public:
	    typedef std::function<void()> FuncType;
	    explicit Task(const FuncType&);
	    ~Task();
				
		void run();
private:
	    FuncType m_func;

};
#endif


