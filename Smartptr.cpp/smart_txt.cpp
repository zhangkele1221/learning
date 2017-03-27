/**********************************************
 > File Name: smart.cpp
 > Author: ZY
 > Created Time: 2017年03月23日 星期四 21时22分39秒
*******************************************/


//1智能指针背后的设计思想

void remodel(std::string & str)
{
	std::string *ps = new std::string(str);
	....
		if(weird_thing())
			throw exception();
	str = *ps;
	delete ps;
	return ;
}
//当出现异常时 delete将不被执行 so 内存泄漏   当remodel()函数终止时候（不管出现
//异常终止） 本地变量都将栈内存中删除  因此指针ps占据的内存将被释放。 如果ps指向
//的堆空间内存也被释放那就完美了啊。     如果ps有一个析构函数，该析构函数将ps过期
//时候释放它指向的内存。    因此 ps他是一个常规指针   不是有析构函数的类对象。  
//如果他是对象 则可以在对象过期时，  让他的析构函数删除指针指向的内存。 
//这就是auto_ptr  unique_ptr  和shared_ptr背后的思想！！！！！！！！！！！！！1


//因此要转换remodel函数 须要按照先面3个步骤进行
//1包含头文件memory；
//2将指向string的指针替换为指向string的智能指针对象
//3 删除delete对象

#include<memory>
void remodel(std:: string &str)
{
	std::auto_ptr<std::string> ps (new std:: string (str));
	..........
		if(weird_thing())
			throw exception();
	str= *ps;
	//delete ps;   //不须要使用这样的方法了 
     return ;


}

//看一个实例下面!!!!next  下一个文档!!!!





