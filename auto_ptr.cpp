/**********************************************
 > File Name: auto_ptr.cpp
 > Author: ZY
 > Created Time: 2017年03月23日 星期四 12时09分42秒
*******************************************/


#include<iostream>
#include<string.h>
#include<memory>

using namespace std;

class  Test
{
public:
	Test(){name = NULL;}
	Test(const char* strname)
	{
		name = new char[strlen(strname)+1];
		strcpy(name,strname);
	}
	Test& operator = (const char *namestr)//Test & operator =(const char*Namestr)
	{									  //{  
		if(name !=NULL)                     //           if(NULL!=name)
		{                                        //          delete name;
			delete name;//释放原来的内存      // name  = new char[strlen(namestr)+1]  
		}                                      //  strcpy(name,namestr)
		name = new char[strlen(namestr)+1];		//  return  *this;
		strcpy(name,namestr);
		return  *this;
	}
	void ShowName(){
		cout<<name<<endl;
	}
	~Test()
	{
		if(NULL!=name)
		{
			delete name;
		}
		name = NULL;
		cout<<"delete name "<<endl;
	}

private:
	char *name;
};
int main()
{
	auto_ptr<Test> TestPtr(new Test("Terry"));
//	auto_ptr<Test> TestPtr = new Test("Terry");  //编译出错
	
	TestPtr->ShowName();   //使用智能指针调用showname方法
	
	*TestPtr = "David";  //使用智能指针改变字符串的内容
	TestPtr->ShowName();


	int y=1;
	int x=0;
	y=y/x;
	return 0;
}












