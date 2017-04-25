/*************************************************************************
    > File Name: insert_pair.cpp
    > Author: ZY
    > Created Time: 2017年04月16日 星期日 22时54分00秒
 ************************************************************************/

#include<map>
#include<string>
#include<iostream>
#include<vector>
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

/*
mapStudent.insert(map<int, string>::value_type (1, "student_one"));
mapStudent.insert(map<int, string>::value_type (1, "student_two"));

上面这两条语句执行后，map 中 1 这个关键字对应的值是 student_one，第二条语句并没
有生效，那么这就涉及如何知道 insert 语句是否插入成功的问题了，可以用 pair 来获得是否
插入成功，程序如下：
	pair<map<int, string>::iterator, bool> insert_pair;
	insert_pair = mapStudent.insert(map<int, string>::value_type (1, "student_one"));
*/

//用 pair 判断 insert 到 map 的数据是否插入成功
//通过insert函数返回值判断是否插入成功
/*
int main(){
	map<int, string> mapStudent;
	pair<map<int, string>::iterator, bool> insert_pair;
	insert_pair = mapStudent.insert(pair<int,string>(1,"student_one"));
	if(insert_pair.second == true){
		cout<<"Insert Successfully"<<endl;
	}
	else{
		cout<<"Insert Failure"<<endl;
	}
	insert_pair = mapStudent.insert(pair<int, string>(1, "student_two"));
	if(insert_pair.second == true){
		cout<<"Insert Successfully"<<endl;
	}else{
		cout<<"Insert Failure"<<endl;
	}
	map<int, string>::iterator iter;
	for(iter = mapStudent.begin(); iter != mapStudent.end(); iter++){
		cout<<iter->first<<" "<<iter->second<<endl;
	}
	return 0;
}
*/

//用 pair 判断 insert 到 map 的数据是否插入成功。pair 变量 insert_pair 中的第
//一个元素的类型是 map<int, string>::iterator，是和即将要判断的 map 中的 key、value 
//类型一致的一个 map 的迭代器。如果 insert 成功了，则 insert_pair.second 的结果为 true，
//否则则为false。同一个 key 已经有数据之后，再 insert 就会失败。
//而数组插入的方式，则是直接覆盖


//map 反向迭代器的使用举例。
/*
int main(){
	map<int,string> mapStudent;
	mapStudent[1] = "student_one";
	mapStudent[2] = "student_two";
	mapStudent[3] = "student_three";
	map<int, string>::reverse_iterator iter;
	for(iter = mapStudent.rbegin(); iter != mapStudent.rend(); iter++){
		cout<<iter->first<<" "<<iter->second<<endl;
	}
	return 0;
}
*/

//反向迭代器 reverse_iterator，它需要使用 rbegin() 和 rend() 方法
//指出反向遍历的起始位置和终止位置


//用数组方式遍历 map
/*
int iSize = mapStudent.size();
for(int i = 1; i <= iSize; i++)
*/

//用数组访问 vector 时，下标是从0 ～（size-1），而用数组访问 map，
//却是从 1~size，这是有所不同的，请使用者多加注意


//用 find 方法查找 map 中的数据
/*
int main(){
	map<int,string> mapStudent;
	mapStudent[1] = "student_one";
	mapStudent[2] = "student_two";
	mapStudent[3] = "student_three";
	map<int, string>::iterator iter=mapStudent.find(1);
	if(iter != mapStudent.end()){
		cout<<"Found, the value is "<<iter->second<<endl;
	}else{
		cout<<"Do not found"<<endl;
	}
	return 0;
}
*/
//用 find 函数来定位数据出现位置，它返回的一个迭代器，当数据出现时，
//它返回数据所在位置的迭代器；
//如果 map 中没有要查找的数据，它返回的迭代器等于 end 函数返回的迭代器。

//find 函数返回的是一个迭代器；找不到对应数据的时候，则会返回 mapStudent.end()


//用 erase 方法删除 map 中的元素
/*
for(;iter!=mapStudent.end();){
	if((*iter).second=="student_one"){
		mapStudent.erase(iter++);
	}
	else{
		++iter;
	}
}
*/
//mapStudent.erase(iter++); 中的 iter++，不是 erase(iter)，然后 iter++。
//因为 iter 指针被erase 之后就失效了，不能再用 iter++ ；
//也不是 erase(++iter)，这样就不是删 iter 原来指向的元素了


//让 map 中的元素按照 key 从大到小排序
/*
int main(){
	map<string, int, greater<string> > mapStudent;//less<string>
	mapStudent["LiMin"]=90;
	mapStudent["ZiLinMi"]=72;
	mapStudent["BoB"]=79;
	map<string, int>::iterator iter=mapStudent.begin();
	for(iter=mapStudent.begin();iter!=mapStudent.end();iter++){
		cout<<iter->first<<" "<<iter->second<<endl;
	}
	return 0;
}
*/

/*
如果想自己写一个
Compare 的类，让 map 按照想要的顺序来存储，比如按照学生姓名的长短排序进行存储，那
么只要自己写一个函数对象，实现想要的逻辑，并在定义 map 的时候把 Compare 指定为自己
编写的这个就可以实现了，代码如下：
*/


//重定义 map 内部的 Compare 函数

struct CmpByKeyLength {
	bool operator()(const string& k1, const string& k2) {
		return k1.length() < k2.length();
	}
};
/*
int main(){
	map<string, int, CmpByKeyLength > mapStudent;
	mapStudent["LiMin"]=90;
	mapStudent["ZiLinMi"]=72;
	mapStudent["BoB"]=79;
	map<string, int>::iterator iter=mapStudent.begin();
	for(iter=mapStudent.begin();iter!=mapStudent.end();iter++){
			cout<<iter->first<<" "<<iter->second<<endl;
	}
	return 0;
}
*/

/*
key 是结构体的，如果没有重载小于号（<）操作，就会导致 insert 函数在编译时就无法
编译成功。其实，为了实现快速查找，map 内部本身就是按序存储的（比如红黑树）。在插入
<key, value> 键值对时，就会按照 key 的大小顺序进行存储。这也是作为 key 的类型必须能够
进行 < 运算比较的原因
*/

typedef struct tagStudentInfo
{
	int iID;
	string strName;
	bool operator < (tagStudentInfo const& r) const {
	// 这个函数指定排序策略，按 iID 排序，如果 iID 相等的话，按 strName 排序
	if(iID < r.iID) return true;
	if(iID == r.iID) return strName.compare(r.strName) < 0;
	return false;
}
}StudentInfo;// 学生信息

/*
int main(){
	// 用学生信息映射分数 
	map<StudentInfo, int>mapStudent;
	StudentInfo studentInfo;

	studentInfo.iID = 1;
	studentInfo.strName = "student_one";
	mapStudent[studentInfo]=90;

	studentInfo.iID = 2;
	studentInfo.strName = "student_two";
	mapStudent[studentInfo]=80;

	map<StudentInfo, int>::iterator iter=mapStudent.begin();
	for(;iter!=mapStudent.end();iter++){
		cout<<iter->first.iID<<" "<<iter->first.strName<<" "<<iter->second<<endl;
	}
	return 0;

}
*/


/*
//map 中pair的定义
template <class T1, class T2> struct pair
{
	typedef T1 first_type;
	typedef T2 second_type;

	T1 first;
	T2 second;
	pair() : first(T1()), second(T2()) {}
	pair(const T1& x, const T2& y) : first(x) ,second(y) {}
	template <class U, class V>
		pair(const pair<U ,V> &p): first(p.first),  second(p.second) {}
	
}
//STL 源码实现的pair 重载的< 运算符  且是先按照key 比较   如果key相等  再比较value 
template<class _T1, class _T2>
	inline bool
	operator<(const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y)
	{ return __x.first < __y.first
			|| (!(__y.first < __x.first) && __x.second < __y.second); }


//如果 pair类本身没有重载<符   那么按照下面重载< 符  可以实现pair类型按 value比较。
//  但是现在这样做不行  严格的编译器会报错
typedef pair<string,int > PAIR;
bool operator< (const PAIR& 1hs, const PAIR& 2hs) {
	return 1hs.second < 2hs.second;
}

//那么如何实现pair 的 value 比较呢？
//1写一个比较函数  2写一个函数对象
typedef pair<string, int> PAIR;

bool cmp_by_value(const PAIR& lhs,const PAIR& rhs){
	return lhs.second < rhs.second;  
}

struct CmpByValue{
	bool operator()(const PAIR& lhs ,const PAIR& rhs){
		return lhs.second < rhs.second;
	}
};

*/


//将 map 按 value 排序

typedef pair<string, int> PAIR;
	bool cmp_by_value(const PAIR& lhs, const PAIR& rhs) {
		return lhs.second < rhs.second;
}
struct CmpByValue {
	bool operator()(const PAIR& lhs, const PAIR& rhs) {
		return lhs.second < rhs.second;
}
};

typedef <class RandomAccessIterator ,class Compare>
void sort(RandomAccessIterator first,RandomAccessIterator last, Compare comp);


int main(){
	map<string, int> name_score_map;
	name_score_map["LiMin"] = 90;
	name_score_map["ZiLinMi"] = 79;
	name_score_map["BoB"] = 92;
	name_score_map.insert(make_pair("Bing",99));
	name_score_map.insert(make_pair("Albert",86));
	
	// 把 map 中元素转存到 vector 中
	vector<PAIR> name_score_vec(name_score_map.begin(), name_score_map.end());
	sort(name_score_vec.begin(), name_score_vec.end(), CmpByValue());
	//sort(name_score_vec.begin(), name_score_vec.end(), cmp_by_value); 也是可以的
	for (int i = 0; i != name_score_vec.size(); ++i) {
		cout<<name_score_vec[i].first<<" "<<name_score_vec[i].second<<endl;
	}
	return 0;
}

























