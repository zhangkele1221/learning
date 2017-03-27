/**********************************************
 > File Name: this.cpp
 > Author: ZY
 > Created Time: 2017年03月25日 星期六 14时17分37秒
*******************************************/


#include<iostream>
using namespace std;

class Student
{
public:
	void setname(char* name);
	void setage(int age);
	void setscore(float score);
	void show();
private:
	char *name;
	int age;
	float score;
};
void Student::setname(char *name)
{
	this->name=name;
}
void Student::setage(int age)
{
	this->age=age;
}
void Student::setscore(float score)
{
	this->score=score;
}
void Student::show()
{
	cout<<this->name<<"的年临时"<<this->age<<"，成绩是"<<this->score<<endl;
}

int main()
{
	Student *pstu=new Student;
	pstu->setname("张勇");
	pstu->setage(19);
	pstu->setscore(98);
	pstu->show();
	return 0;
}




