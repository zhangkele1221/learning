/*************************************************************************
    > File Name: Task.cpp
    > Author: ZY
    > Created Time: 2017年08月29日 星期二 22时57分21秒
 ************************************************************************/

#include"Task.h"


Task::Task(const FuncType& func):m_func(func)
{


}

Task::~Task()
{


}

void Task::run()
{

	    m_func();
}
