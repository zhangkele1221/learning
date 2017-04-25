/*************************************************************************
    > File Name: vector.cpp
    > Author: ZY
    > Created Time: 2017年04月20日 星期四 22时04分51秒
 *******************************************************************/
/*
vector 是什么 
  是一个线性的容器  和动态的数组类似 它的元素存储在 是一块连续的内存空间  
  可以自动增长／缩小空间
      优点
	  1 可以使用下标访问个别元素
	  2 迭代器按照不同的方式便列容器
	  3 可以在容器的末尾增加删除元素
	

和其他标准的顺序容器相比，vector 能更有效访问容器内的元素和在末尾添加和删除

元素；而在其他位置添加和删除元素，vector 则不及其他顺序容器，在迭代器和引用也不比
lists 支持的好。
*/


#include<iostream>
#include<vector>
using namespace std;

/*
int main(){
	int a[7]={1,2,3,4,5,6,7};
	vector<int> ivector(a,a+7);
	//vector 的赋值并不可以像数组一样用花括号方便地完成赋值，
      // 这里借用了数组来初始化这个 
    // vector初始化方式 vector<elementType> intvec(begin,end); 
     // 这样可以用起来看上去还是比较习惯的。
	//	vector<int>::iterator iter;
	for (iter=ivector.begin();iter!=ivector.end();iter++){
		cout<<*iter<<" ";
	}
	cout<<endl;
	ivector[5]=1;
	单个 vector 的赋值，这个方式看上去还是和数组一样的
	也可以这么写 ivector.at(5)=1; 但是就是不习惯 
	cout<<ivector[5]<<endl<<ivector.size()<<endl;
	for (iter=ivector.begin();iter!=ivector.end();iter++){
		cout<<*iter<<" ";
	}
	cout<<endl;
	for(int i=0;i<5;i++){
		cout<<ivector[i]<<" ";
	}
	cout<<endl;
	return 0;
}

*/


// for_each 的遍历举例。

/*

#include <algorithm>

void print(int n)
{
	cout<<n<<" ";
}

int main(){
	int a[7]={1,2,3,4,5,6,7};
	vector<int> ivector(a,a+7);//( 0  ~  end()    )
	vector<int>::iterator iter;
	for_each(ivector.begin(),ivector.end(),print);// 用 for_each 进行遍历
	cout<<endl;

	ivector[5]=1;
	cout<<ivector[5]<<endl<<ivector.size()<<endl;
	for_each(ivector.begin(),ivector.end(),print);// 用 for_each 进行遍历
	return 0;
}

结果：
1 2 3 4 5 6 7
1
7
1 2 3 4 5 1 7

*/

// vector 是个模板类，可以存放任何类型的对象。
//在 vector 中存放结构体时，可以按照自定义的排序方式排序
// vector 中存放结构体时的排序

/*
#include<algorithm>

typedef struct rect{
	int id;
	int length;
	int width;
	bool operator< (const rect &a) const{
	if(id!=a.id)
		return id<a.id;
	else{
		if(length!=a.length)
			return length<a.length;
		else
			return width<a.width;
		}
	}
}Rect;
int main(){
	vector<Rect> vec;
	Rect rect;
	rect.id=2;
	rect.length=3;
	rect.width=4;
	vec.push_back(rect);
	rect.id=1;
	rect.length=2;
	rect.width=3;
	vec.push_back(rect);
	vector<Rect>::iterator it=vec.begin();
	cout<<(*it).id<<' '<<(*it).length<<' '<<(*it).width<<endl;
	sort(vec.begin(),vec.end());
	cout<<(*it).id<<' '<<(*it).length<<' '<<(*it).width<<endl;
	return 0;
}
*/

/*
vec 中存放的是结构体 Rect。vec 未进行排序前，将会按照 push_back 的时

间顺序排序，并不会自动排序。排序后，可以按照结构体中对 rect 的重载方式进行排序：按
照 id、length、width 升序排序，然后用 <algorithm> 中的 sort 函数排序
*/


/*
结构体外定义比较函数。

typedef struct rect{
int id;
int length;
int width;
}Rect;

int cmp(Rect a,Rect b){
	if(a.id!=b.id)
		return a.id<b.id;
	else{
	if(a.length!=b.length)
		return a.length<b.length;
	else
		return a.width<b.width;
	}
}

	sort(vec.begin(),vec.end(),cmp);

*/


//  2. vector 的查找

/*
#include<algorithm>
int main(){
vector<int> vec;
vec.push_back(1);
vec.push_back(2);
vec.push_back(3);
vec.push_back(4);
vec.push_back(5);
	vector<int>::iterator iter=find(vec.begin(),vec.end(),3);
	if ( iter==vec.end())
		cout << "Not found" << endl;
	else
		cout << "Found" << endl;
		
	return 0;
}


find 函数在 vector 中进行查找。注意 f ind 函数不属于 vector 的成员，
而存在于算法中，所以应加上头文件 #include <algorithm>

*/


//3. vector 的删除
//vector 中的删除，可以有 erase 或 pop_back 函数。
//erase 可以删除指定元素或指定位置的元素，而 pop_back 只能去掉数组的最后一个数据。
//erase 的函数原型有以下两种形式：

//iterator erase(iterator position)。
//iterator erase(iterator first, iterator last)

/*

for(vector<int>::iterator iter=veci.begin(); iter!=veci.end(); iter++){

	if( *iter == 3)
		veci.erase(iter);  //error   iter is  not to  piont!
}



for(vector<int>::iterator iter=vec.begin(); iter!=vec.end(); iter++){

	if( *iter == 3)
		iter = vec.erase(iter);
}
这段代码也是错误的：
① 无法删除两个连续的3 
② 当数字3位于 vector 最后位置的时候，也会出错（在 vec.end() 上执行 ++ 操作
}

*/


//使用 erase 删除 vector 中某个元素。

/*
#include<algorithm>


int main(){

	vector<int> vec;
	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);
	vec.push_back(4);
	vec.push_back(5);
	vector<int>::iterator iter=vec.begin();
	for(;iter!=vec.end();)
	{
		if(*iter==3)
		{
			iter=vec.erase(iter);//careful  （无法删除连续的3）
								//（当3在最后一个元素会出错）
		}
		else
		{
			++iter;
		}
	}
	for(iter=vec.begin();iter!=vec.end();iter++){

		cout<<*iter<<" ";
	}
	return 0;
}
*/
//使用 vec.erase(vec.begin()+i,vec.end()+j) 语句则是删除区间 [i,j-1] 间的元素。
//而 pop_back 只能去掉数组的最后一个数据






/*
					4. vector 的增加
vector 中的增加，可以有 insert 和 push_back。
insert 是插入元素到某个位置中，push_back 是在最后添加一个元素。

insert 的函数原型有以下 3 种形式：
	
	iterator insert( iterator loc, const TYPE &val );
// 在指定位置 loc 前插入值为 val 的元素 , 返回指向这个元素的迭代器
	
	void insert( iterator loc, size_type num, const TYPE &val );
// 在指定位置 loc 前插入 num 个值为 val 的元素
	
	void insert( iterator loc, input_iterator start, input_iterator end );
// 在指定位置 loc 前插入区间 [start, end) 的所有元素
*/


//　vector 的查增删用法举例。
/*
#include<algorithm>

void print( vector<int>v )
{
	vector<int>::iterator iter=v.begin();
	for(;iter!=v.end();iter++)
		cout<<*iter<<" ";
		cout<<endl;
}
int main(){
	vector<int> v; // 现在容器中有 0 个元素
	int values[] = {1,3,5,7};
    // 插入	[)   3. 5 into
	v.insert(v.end(), values+1, values+3); // 现在容器中有 2 个元素分别为 :3,5
	print(v);
	v.push_back(9); // 现在容器中有 3 个元素分别为 :3,5,9
	print(v);
    v.erase(v.begin()+1); // 现在容器中有 2 个元素分别为 :3,9
    print(v);
    v.insert(v.begin()+1, 4); // 现在容器中有 3 个元素分别为 :3,4,9
    print(v);
     //insert(pos , num, const vaul )
    v.insert(v.end()-1, 4, 6); // 现在容器中有 7 个元素分别为 :3,4,6,6,6,6,9
    print(v);
	// [)  ...........
	v.erase(v.begin()+1, v.begin()+3); // 现在容器中有 5 个元素分别为 :3,6,6,6,9
	print(v);
	
	v.pop_back(); // 现在容器中有 4 个元素分别为 :3,6,6,6
	print(v);

	v.clear(); // 现在容器中有 0 个元素
	print(v);

	if (true == v.empty()) // 如果容器为空则输出“null”
	{
		std::cout<<"null"<<std::endl;
	}
	return 0;
}
*/























