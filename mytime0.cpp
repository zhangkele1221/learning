/**********************************************
 > File Name: mytime0.cpp
 > Author: ZY
 > Created Time: 2017年03月26日 星期日 18时36分34秒
*******************************************/


#include<iostream>
using namespace std;



class Time
{
private:
	int houre;
	int minutes;
public:
	Time();
	Time(int h, int m =0);
	void AddMin(int m);
	void AddHr(int h=0 );
	void Reset(int h=0, int m=0);
//	Time Sum(const Time & t) const;
    Time operator+(const Time & t) const;
	void Show() const;
};

Time::Time()
{
	houre = minutes = 0;
}

Time::Time(int h,int m)
{
	houre = h;
	minutes = m ;
}

void Time::AddMin(int m)
{
	minutes +=m ;
	houre+= minutes / 60;
	minutes %=60;
}

void Time::AddHr(int h)
{
	houre +=h;
}
void Time::Reset(int h, int m)
{
	houre=h;
	minutes=m ;
}

/*sum函数 参数是引用 但返回的却不是引用  参数为引用的目的就是提高效率不多说
 *返回值不是引用的原因是*******不要返回一个局部变量或者是临时变量的引用ok
 *因为 局部变量和临时变量  函数执行玩后会over  引用就不知道是引用什么类ok
 * */

/*
Time Time::Sum(const Time & t) const
{
	Time sum ;
	sum.minutes = minutes + t.minutes;
	sum.houre = houre+t.houre+ sum.minutes / 60 ;
	sum.minutes %=60;
	return sum;
}
*/


//   对时间的运算  还需要一些其他的运算符 比如  ”-”  
/*   //Time operator-(const Time & t)const;
 *   //Time operator+(double n) const;
 * 
 * */



/*重载运算符定义！！！！
 * 
 * */
Time Time::operator+(const Time & t) const
{
	Time sum;
	sum.minutes = minutes + t.minutes;
	sum.houre = houre + t.houre + sum.minutes / 60;
	sum.minutes %=60;
	return sum ;

}

void Time::Show() const
{
	cout<< houre<<"houre,"<<minutes<<"minutes";
}

int main()
{
	Time planning;
	Time coding(2,40);
	Time fixing(5,55);
	Time total;

	cout<<"planning time = ";
	planning.Show();
	cout<<endl;

	cout<<"coding time =";
	coding.Show();
	cout<<endl;

	cout<<"fixing time = ";
	fixing.Show();
	cout<<endl;

//	total = coding.Sum(fixing);
	total = coding + fixing;            //调用了+运算符重载的方法
//	cout<<"coding.Sum(fixing) = ";
	cout<<"coding + fixing =";
	total.Show();
	cout<<endl;


	return 0;
}




