/**********************************************
 > File Name: auto_ptr1_STL.cpp
 > Author: ZY
 > Created Time: 2017年03月23日 星期四 14时47分19秒
*******************************************/


#include<iostream>
#include<string.h>
using namespace std;


template <class T>
class SmartPtr
{
public:
	SmartPtr(T *p = 0);//构造函数
	SmartPtr(const SmartPtr& src);//拷贝构造函数
	SmartPtr & operator =(const SmartPtr& rhs);//赋值函数 重载运算符
	T* operator ->();//重载->
	T& operator *(); //重载*
	~SmartPtr();
private:
	void decRef()
	{
		if(--*m_pRef==0)
		{
			delete m_ptr;
			delete m_pRef;
		}
	}
	T* m_ptr; //保存对象指针
	size_t *m_pRef;//保存引用计数
};


template <class T>
SmartPtr<T>::SmartPtr(T*p) //普通构造函数
{
	m_ptr = p; //m_ptr 与p 指向统一个内存
	m_pRef = new size_t(1);  //m_pRef 初始化为1
	cout<<"SmartPtr: 普通构造函数............."<<endl;
}

template<class T>
SmartPtr<T>::SmartPtr(const SmartPtr<T>& src) //拷贝构造函数
{
	m_ptr = src.m_ptr; //m_ptr  src.mptr指向统一个内存
	m_pRef++;
	m_pRef = src.m_pRef;// 拷贝引用
	cout<<"SmartPtr: 拷贝构造函数的调用........"<<endl;
}

template <class T>
SmartPtr<T>::~SmartPtr() //析构函数
{
	decRef(); //引用计数减去1 如果引用为0 则释放内存
	cout<<"SmartPtr: 析构函数的调用............."<<endl;
}

template <class T>
T* SmartPtr<T>::operator ->()
{
	cout<<"SmartPtr: 重载->调用............."<<endl;

	if(m_ptr)
		return m_ptr;
	//m_ptr为NULL时  抛出异常
//	throw cout<<"access through NULL pointer"<<endl;;
}

template <class T>
T& SmartPtr<T>::operator *()
{

	cout<<"SmartPtr: 重载*调用............."<<endl;

	if(m_ptr)
		return *m_ptr;
	//同上处理
//	throw cout<<"deletreference of NULL  pointer"<<endl;;
}

template <class T>
SmartPtr<T>& SmartPtr<T>:: operator = (const SmartPtr<T>& rhs)//赋值函数
{
	cout<<"SmartPtr: 重载 = 调用............."<<endl;

	++*rhs.m_pRef;  //rhs的引用加1
	decRef();//自身指向的原指针的引用减1
	m_ptr  = rhs.m_ptr;  //m_ptr 和rhs指向统一个对象
	m_pRef = rhs.m_pRef;//复制引用
	return *this;
}

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
      {                                     //{  
         if(name !=NULL)                     //           if(NULL!=name)
         {                                        //          delete name;
          delete name;//释放原来的内存      // name  = new char[strlen(namestr)   +1]  
         }                                      //  strcpy(name,namestr)
          name = new char[strlen(namestr)+1];     //  return  *this;
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
//	SmartPtr<Test> t1;//空指针
	SmartPtr<Test> t2(new Test("terry"));
	SmartPtr<Test> t3(new Test("john"));

/*	try
	{
		t1->ShowName();//空指针抛出异常
	}catch (const exception& err)
    {
        cout <<err.what()<<endl;
	}
*/
    t2->ShowName();//
	*t2 ="David";  //t2给对象赋值
	t2->ShowName();
	t2=t3;
   
	cout<<"End of main....."<<endl;

	return 0;
}























