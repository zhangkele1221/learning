/*************************************************************************
    > File Name: insert_set.cpp
    > Author: ZY
    > Created Time: 2017年04月18日 星期二 12时55分58秒
 ************************************************************************/

#include<iostream>
#include<string>
#include<set>
#include<iterator>
#include<string.h>

using namespace std;

struct strLess{
	bool operator()(const char *s1,const char *s2) const {
		return strcmp(s1,s2) < 0;
	}
};

void printSet(set<int> s){
	copy(  s.begin(), s.end(), ostream_iterator<int>(cout,", ")  );
	/*
	  set<int>::iterator iter;
	  for(iter=s.begin();iter!=s.end();iter++)
		cout<<"set["<<iter-s.begin()<<"]="<<*iter<<", ";//ERROR
	  cout<<*iter<<", ";
	 * */
	cout<<endl;
}

int main()
{
	//创建set对象 有5中方式 若比较函数对象以及内存分配器未出现  就表示采用系统默认方式
	//创建空的set对象  元素类型为 int
	set<int> s1;
	//创建空的set 对象，元素类型 char*，比较函数对象 (即排序准则) 为自定义 strLess
	set<const char*,strLess> s2(strLess);

	// 利用 set 对象 s1, 拷贝生成 set 对象 s2
	set<int> s3(s1);

	//用迭代区间 [&first, &last) 所指的元素，创建一个 set 对象
	int iArray[] = {13,32,19};
	set<int> s4(iArray,iArray + 3);
    
	//用迭代区间 [&first, &last) 所指的元素，
	//及比较函数对象 strLess，创建一个 set 对象
	 const char* szArray[] = {"hello", "dog", "bird" };
	 set<const char*, strLess> s5(szArray, szArray + 3, strLess() );
	
   /*
// 元素插入：
	//1, 插入 value，返回 pair 配对对象，
	//可以根据 .second 判断是否插入成功。( 提示:value 不能与set 容器内元素重复 )
	pair<iterator,bool> insert(value)
	//2.在pos 位置之前插入 value，返回新元素位置，但不一定能插入成功
	iterator insert(&pos,value)
	//3,将迭代区间 [&first, &last) 内所有的元素，插入到 set 容器]
	void insert[&first,&last);
*/

	 cout<<"s1.insert() : "<<endl;
	 int i ;
	 for(i=0;i<5;i++)
		s1.insert(i*10);
	 printSet(s1);

     cout<<"s1.insert(20).second = "<<endl;


	if (s1.insert(20).second)
		cout<<"Insert OK!"<<endl;
	else
		cout<<"Insert Failed!"<<endl;
		cout<<"s1.insert(50).second = "<<endl;
	
	if (s1.insert(50).second){
		cout<<"Insert OK!"<<endl;
		printSet(s1);
	}else
		cout<<"Insert Failed!"<<endl;

	 
  cout<<"pair<set<int>::iterator, bool> p;\np = s1.insert(60);\nif (p.second):"<<endl;
	pair<set<int>::iterator, bool> p;
 	p = s1.insert(60);

	if (p.second){
		cout<<"Insert OK!"<<endl;
		printSet(s1);
	}
	else
		cout<<"Insert Failed!"<<endl;



/* 元素删除
1,size_type erase(value) 移除 set 容器内元素值为 value 的所有元素，返回移除的元素个数
2,void erase(&pos) 移除 pos 位置上的元素，无返回值
3,void erase(&first, &last) 移除迭代区间 [&first, &last) 内的元素，无返回值
4,void clear()， 移除 set 容器内所有元素 */
	cout<<"\ns1.erase(70) = "<<endl;
		s1.erase(70);
		printSet(s1);
	cout<<"s1.erase(60) = "<<endl;
		s1.erase(60);
		printSet(s1);
	cout<<"set<int>::iterator iter = s1.begin();\ns1.erase(iter) = "<<endl;
		set<int>::iterator iter = s1.begin();
		s1.erase(iter);
		printSet(s1);






/* 元素查找
count(value) 返回 set 对象内元素值为 value 的元素个数
iterator find(value) 返回 value 所在位置，找不到 value 将返回 end()
lower_bound(value),upper_bound(value), equal_range(value)*/
cout<<"\ns1.count(10) = "<<s1.count(10)<<", s1.count(80) = "<<s1.count(80)<<endl;
	cout<<"s1.find(10) : ";

if (s1.find(10) != s1.end())
	cout<<"OK!"<<endl;
else
	cout<<"not found!"<<endl;
	cout<<"s1.find(80) : ";

if (s1.find(80) != s1.end())
	cout<<"OK!"<<endl;
else
	cout<<"not found!"<<endl;



/* 其他常用函数 */
cout<<"\ns1.empty()="<<s1.empty()<<", s1.size()="<<s1.size()<<endl;
	set<int> s9;
		s9.insert(100);
	cout<<"s1.swap(s9) :"<<endl;
	
	s1.swap(s9);
	cout<<"s1: "<<endl;
	printSet(s1);
	
	cout<<"s9: "<<endl;
	printSet(s9);


	return 0;
}



