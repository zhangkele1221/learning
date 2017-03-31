/**********************************************
 > File Name: String_self.cpp
 > Author: ZY
 > Created Time: 2017年03月28日 星期二 22时18分09秒
*******************************************/
/*
 *实现一个string类   具有比较  连接  输入 输出
 *实现上面的功能须要重载   "<"  ">" "==" "!="  "+=" <<  >> 赋值运算等
 *              编写各种运算符重载
 * */


#include<iostream>
#include<string.h>
using namespace std;


class String
{
public:
	String();//默认构造函数
	String(int n ,char c);//普通构造函数 n个字符相同的字符
	String(const char*  source);//....... 构造和source一样的字符串
	String(const String& s);//复制构造函数；
	String& operator = (char* s) ;//重载= 实现字符串的复制
	String& operator = (const String& s);//重载= 实现对象的赋值
	~String();//析够函数
	char& operator[](int i) ; //重载[] 实现数组运算
	const char& operator[](int i) const ;//重载[] 实现数组运算（对象为常量）
	String& operator += (const String& s); //+= 实现字符串相加
	String& operator += (const char* s);//+=  实现对象相加
	friend ostream& operator <<(ostream&out, String& s);//重载<<实现输出
	friend istream& operator >>(ostream&in , String& s);//>> 输入
	friend bool operator < (const String& left,const String& right); // <
	friend bool operator > (const String& left,const String& right);// >
	friend bool operator ==(const String& left,const String& right);//==
	friend bool operator != (const String& left,const String& right);//!=
	char* getData();//获取data指针
	int length();//获取对象的长度
private:
	int size;//data字符串长度
	char* data;
};


String::String()       //默认构造函数  构造空字符串
{
	data = new char[1];   //空字符串含有 '\0'含有一个元素
	*data = '\0';
	size = 0;
}

String::String(int n, char c)  //构造含有n个相同的字符串
{
	data = new char[n+1];
	char *temp = data;
	while(n--)
	{
		*temp++ = c;
	}
	*temp ='\0';
	size = n;
}

String::String(const char *source) //构造与source内容相同的字符串
{
	if(NULL == source)
	{
		data = new char[1];
		*data = '\n';
		size = 0;
	}
	else
	{
		size = strlen(source);
		data = new char[size+1];
		strcpy(data,source);
	}
}

String::String(const String &s)//复制构造函数
{
	data = new char[s.size +1];
	strcpy(data,s.data);
	size = s.size;
}


String& String:: operator =(char *s)//重载=  深copy一个字符串
{
	if(data !=NULL)
		delete []data;

	size = strlen(s);
	data = new  char[size+1];
	strcpy(data,s);
	return *this;

}

String& String::operator = (const String& s) //重载= 深copy一个对象
{
	if(this == &s)            //如果对象是自己就直接返回自己
	{
		return *this;
	}
	if(data !=NULL)    //释放data堆栈内存
	{
		delete []data;
	}
	size = strlen(s.data);
	data = new char[size+1];
	strcpy(data,s.data);
	return *this;    
}

String::~String()
{
	if(data !=NULL) //data不为NULL 释放空间
	{
		delete []data;
		data = NULL;
		size = 0;
	}

}

char & String::operator[](int i) //重载[]
{
	return data[i];
}

const char& String::operator[] (int i) const
{
	return data[i];
}

String& String::operator +=(const String& s)//重载 +=  连接对象s字符串成员
{
	int len = size + s.size + 1;
	char *temp = data;
	data = new char[len];
	size = len -1;
	strcpy(data,temp);
	strcat(data,s.data);
	delete []temp;
	return *this;
}

String& String::operator +=(const char *s) //重载 += 连接字符串
{
	if(s==NULL)  //但凡涉及到指针操作  就要注意 边界条件有效问题的出现
	{
		return *this;
	}
	int len = size + strlen(s)+ 1 ;
	char *temp = data;
	data = new char[len];
	size  = len -1;
	strcpy(data,temp);
	strcat(data,s);
	delete []temp;   //其实这里可以不加上[] 因为char是 一个内置类型
	return *this;
}

String::length()
{
	return size;
}

ostream& operator << (ostream &out , String &s) //重载<<
{
	for(int i = 0; i<s.length();i++)
	{
		cout <<s[i]<<" ";
	}
	return out;
}

istream& operator >> (istream&in ,String &s) //重载 >> 最多接受50个字符
{
	char p[50];
	in.getline(p,50);
	s = p;
	return in;
}

bool operator < (const String& left ,const String& right)//重载<
{
	int i =0;
	while(left[i]== right[i] &&left[i] !=0 && right[i] !=0)
	{
		i++;
	}
	return left[i]-right[i]<0 ? true : false;
}








