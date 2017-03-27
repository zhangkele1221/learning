/**********************************************
 > File Name: smrtptrs.cpp
 > Author: ZY
 > Created Time: 2017年03月23日 星期四 21时52分01秒
*******************************************/


#include<iostream>
#include<memory>
#include<string>

using namespace std;

class Report
{
	private:
		string str;
	public:
		Report(const string s):str(s)
	    {
			cout<<"createed object\n";
	    }
		~Report(){
			cout<<"deleted object\n";
		}
		void comment() const{
			cout<<str<<endl;
		}
};

int main()
{

	{
    auto_ptr<Report> ps (new Report("Using suto_ptr"));
	ps->comment();
	}
	
	{
    shared_ptr<Report> ps (new Report("Using shared_ptr"));
	ps->comment();
	}
	{
	unique_ptr<Report> ps1 (new Report("Using unique_ptr"));
	ps1->comment();
	}
	return 0;

}
