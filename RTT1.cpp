/**********************************************
 > File Name: RTT1.cpp
 > Author: ZY
 > Created Time: 2017年03月31日 星期五 15时2分28秒
*******************************************/


#include<iostream>
#include<ctime>
#include<cstdlib>

using namespace std;

class Grand
{
private:
	int hold;
public:
	Grand(int h = 0) : hold(h) {}
	virtual void Speak() const { cout<<"I am a grand class!\n";}
	virtual int Value() const {return hold;}
};

class Superb : public Grand
{
public:
	Superb(int h=0) :Grand(h){}
	void Speak() const {cout<<"I am a spuerb class!\n";}
	virtual void Say() const
	{cout<<"I hold th superb value of "<<Value()<<"!\n";}
};

class Magnificent :public Superb
{
private:
	char ch;
public:
	Magnificent(int h=0,char c = 'A') :Superb(h),ch(c){}
	void Speak() const {cout << "I am a magnificent class!!\n";}
	void Say() const {cout<< "I hold the  character" 
					  <<ch<<"and the interger" <<Value()<< "!\n";}

};

Grand * GetOne()
{
	Grand * p;
	switch(rand() % 3)
	{
		case 0 :p = new Grand(rand() % 100);
				break;
		case 1 :p = new Superb(rand() % 100);
				break;
		case 2 :p = new Magnificent(rand() % 100 , 'A'+rand()% 26);
				break;

	}
	return p;
}

 int main()
 {
      std::srand(std::time(0));
      Grand * pg;
      Superb * ps;
      for (int i = 0; i < 5; i++)
      {
          pg = GetOne();
          pg->Speak();
			//这句代码涉及到了指针类型变化的问题  要搞懂！！！！！
			//什么时候可以变  什么时候会失败 等等！！！！！
          if( ps = dynamic_cast<Superb *>(pg)) //整个代码的核心就在这里
              ps->Say();
      }
      // std::cin.get();
      return 0;
 }






