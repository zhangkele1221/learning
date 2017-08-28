/*************************************************************************
    > File Name: test.cpp
    > Author: ZY
    > Created Time: 2017年08月28日 星期一 15时45分22秒
 ************************************************************************/

#include<iostream>
#include"Thread.h"

using namespace std;

void fun(){
	cout<<"helloworld!"<<endl;
}


int main(){
	cout<<"starting..........."<<endl;
	Thread  th1(fun);
	th1.run();
	cout<<"end Threadtest------1"<<endl;
	

	
	return 0;
}
