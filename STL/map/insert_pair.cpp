/*************************************************************************
    > File Name: insert_pair.cpp
    > Author: ZY
    > Created Time: 2017年04月16日 星期日 22时54分00秒
 ************************************************************************/


#include<map>
#include<string>
#include<iostream>
using namespace std;



//用 insert 函数插入 pair 数据
/*
int main()
{
	map<int,string> mapStusent;
	mapStusent.insert(pair<int,string>(1,"student_one"));
	mapStusent.insert(pair<int,string>(2,"student_two"));
	mapStusent.insert(pair<int,string>(3,"student_three"));
	map<int,string>::iterator  iter;
	for(iter = mapStusent.begin();iter !=mapStusent.end();iter++){
		cout<<iter->first<<" "<<iter->second<<endl;
	}

	return 0;
}
*/


//声明了一个 key 为 int 类型，value 为 string 类型的 map，用 insert 函数插入
//pair 数据，且需要在 insert 的参数中将 (1, "student_one") 转换为 pair 数据再进行插入

//用 insert 函数插入 value_type 数据
/*
int main()
{
	map<int, string> mapStudent;
	mapStudent.insert(map<int, string>::value_type (1,"student_one"));
	mapStudent.insert(map<int, string>::value_type (2,"student_two"));
	mapStudent.insert(map<int, string>::value_type (3,"student_three"));
	map<int, string>::iterator iter;
	for(iter = mapStudent.begin(); iter != mapStudent.end(); iter++){
	cout<<iter->first<<" "<<iter->second<<endl;
	}

	return  0;
}

*/



// 声明了一个 key 为 int 类型，value 为 string 类型的 map，用 insert 函数插入
//value_type 数据，且需要在 insert 的参数中将 (1, "student_one") 
//转换为 map<int, string>::value_type 数据再进行插入。

//map 中用数组方式插入数据。
/*
int main(){
	map<int, string> mapStudent;
	mapStudent[1] = "student_one";
	mapStudent[2] = "student_two";
	mapStudent[3] = "student_three";
	map<int, string>::iterator iter;
	for(iter = mapStudent.begin(); iter != mapStudent.end(); iter++){
	cout<<iter->first<<" "<<iter->second<<endl;
	}
	return 0;
}

*/













