/**********************************************
 > File Name: bridge.cpp
 > Author: ZY
 > Created Time: 2017年03月22日 星期三 21时13分27秒
*******************************************/

/******************************************************************************
 定义:将抽象部分与它的实现部分分离，使它们都可以独立地变化。考虑装操作系统，有多种配置的计算机，同样也有多款操作系统。如何运用桥接模式呢？可以将操作系统和计算机分别抽象出来，让它们各自发展，减少它们的耦合度。当然了，两者之间有标准的接口。这样设计，不论是对于计算机，还是操作系统都是非常有利的。
******************************************************************************/


#include<iostream>
using namespace std;
//操作系统
class OS
{
    public:
	virtual void InstallOS_Imp(){}
};
class WindowOS:public OS
{
	public:
	void InstallOS_Imp() {cout<<"安装windows操作系统"<<endl;}
};
class LinuxOS:public OS
{
	public:
		void InstallOS_Imp(){cout<<"安装Linux操作系统"<<endl;}
};


class UnixOS:public OS
{
	public:
		void InstallOS_Imp(){cout<<"安装Unix操作系统"<<endl;}
		
};

//计算机
class computer
{
	public:
		virtual void InstallOS_Imp(OS*os){}
};

class Dellcomputer:public computer
{
	public:
		void InstallOS_Imp(OS*os){
			os->InstallOS_Imp();
		}
};

class Applecomputer:public computer
{
	public:
		void InstallOS_Imp(OS* os){
			os->InstallOS_Imp();
		}
};

class HPcomputer:public computer
{
	public:
		void InstallOS_Imp(OS*os){
			os->InstallOS_Imp();
		}
};


int main()
{
	OS* os1= new WindowOS();
	OS* os2= new LinuxOS();
	computer * computer1 = new Applecomputer();
	computer1->InstallOS_Imp(os1);
	computer1->InstallOS_Imp(os2);

	return 0;
}



