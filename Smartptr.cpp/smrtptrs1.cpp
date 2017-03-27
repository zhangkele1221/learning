/**********************************************
 > File Name: smrtptrs1.cpp
 > Author: ZY
 > Created Time: 2017年03月24日 星期五 10时14分39秒
*******************************************/


#include<iostream>
#include<string>
#include<memory>

using namespace std;

int main()
{
	auto_ptr<string> films[5] =
	{
		auto_ptr<string> (new string ("Fow1 Balls")),
		auto_ptr<string> (new string ("Duck Walks")),
		auto_ptr<string> (new string ("Chicken Runs")),
		auto_ptr<string> (new string ("Turkey Errors")),
		auto_ptr<string> (new string ("Goose Eggs"))
	};
   
    /*在这里可以换成其他智能指针 进行研究  调试！！！！！！！*/
	auto_ptr<string> pwin;
	pwin = films[2];//  films[2]  loses ownership;  失去所有权

	cout<<"The nominees for best avian baseball film are\n";
	for(int i=0;i<5;i++)
		cout<<*films[i]<<endl;
	cout<<"The winer is"<<*pwin<<"!\n";
	cin.get();

	return 0;
}
//运行下发现程序崩溃了，原因在上面注释已经说的很清楚，films[2]已经是空指针了，下面输出访问空指针当然会崩溃了。但这里如果把auto_ptr换成shared_ptr或unique_ptr后，程序就不会崩溃，原因如下：

//使用shared_ptr时运行正常，因为shared_ptr采用引用计数，pwin和films[2]都指向同一块内存，在释放空间时因为事先要判断引用计数值的大小因此不会出现多次删除一个对象的错误。

//使用unique_ptr时编译出错，与auto_ptr一样，unique_ptr也采用所有权模型，但在使用unique_ptr时，程序不会等到运行阶段崩溃，而在编译器因下述代码行出现错误：

/*
unique_ptr<string> pwin;
pwin = films[2];   // films[2] loses ownership.
*/

//这就是为何要摒弃auto_ptr的原因，一句话总结就是：避免潜在的内存崩溃问题。


//4. unique_ptr为何优于auto_ptr？
/*
可能大家认为前面的例子已经说明了unique_ptr为何优于auto_ptr，也就是安全问题，下面再叙述的清晰一点。
请看下面的语句:
*/
/*
auto_ptr<string> p1(new string ("auto") ； //#1
auto_ptr<string> p2;                       //#2
p2 = p1;                                   //#3
*/

//在语句#3中，p2接管string对象的所有权后，p1的所有权将被剥夺。前面说过，这是好事，可防止p1和p2的析构函数试图刪同—个对象；

//但如果程序随后试图使用p1，这将是件坏事，因为p1不再指向有效的数据。

//下面来看使用unique_ptr的情况：

//unique_ptr<string> p3 (new string ("auto");   //#4
//unique_ptr<string> p4；                       //#5
//p4 = p3;                                      //#6

//编译器认为语句#6非法，避免了p3不再指向有效数据的问题。因此，unique_ptr比auto_ptr更安全。

//但unique_ptr还有更聪明的地方。
//有时候，会将一个智能指针赋给另一个并不会留下危险的悬挂指针。假设有如下函数定义：
/*
unique_ptr<string> demo(const char * s)
{
    unique_ptr<string> temp (new string (s))； 
    return temp；
}
*/

/*
unique_ptr<string> ps;
ps = demo('Uniquely special")；
*/
//demo()返回一个临时unique_ptr，然后ps接管了原本归返回的unique_ptr所有的对象，而返回时临时的 unique_ptr 被销毁，也就是说没有机会使用 unique_ptr 来访问无效的数据，换句话来说，这种赋值是不会出现任何问题的，即没有理由禁止这种赋值。实际上，编译器确实允许这种赋值，这正是unique_ptr更聪明的地方。

/**************************************************************************
总之，党程序试图将一个 unique_ptr 赋值给另一个时，如果源 unique_ptr 是个临时右值，编译器允许这么做；如果源 unique_ptr 将存在一段时间，编译器将禁止这么做，比如：
**************************************************************************/

/*
unique_ptr<string> pu1(new string ("hello world"));
unique_ptr<string> pu2;
pu2 = pu1;                                      // #1 not allowed
unique_ptr<string> pu3;
pu3 = unique_ptr<string>(new string ("You"));   // #2 allowed
*/
//其中#1留下悬挂的unique_ptr(pu1)，这可能导致危害。而#2不会留下悬挂的unique_ptr，因为它调用 unique_ptr 的构造函数，该构造函数创建的临时对象在其所有权让给 pu3 后就会被销毁。这种随情况而已的行为表明，unique_ptr 优于允许两种赋值的auto_ptr 。

//当然，您可能确实想执行类似于#1的操作，仅当以非智能的方式使用摒弃的智能指针时（如解除引用时），这种赋值才不安全。要安全的重用这种指针，可给它赋新值。C++有一个标准库函数std::move()，让你能够将一个unique_ptr赋给另一个。下面是一个使用前述demo()函数的例子，该函数返回一个unique_ptr<string>对象：
     //使用move后，原来的指针仍转让所有权变成空指针，可以对其重新赋值。
/*
unique_ptr<string> ps1, ps2;
ps1 = demo("hello");
ps2 = move(ps1);
ps1 = demo("alexia");
cout << *ps2 << *ps1 << endl;
*/


/*********************5. 如何选择智能指针？*******************************

在掌握了这几种智能指针后，大家可能会想另一个问题：在实际应用中，应使用哪种智能指针呢？
下面给出几个使用指南。

（1）如果程序要使用多个指向同一个对象的指针，应选择shared_ptr。这样的情况包括：

0 有一个指针数组，并使用一些辅助指针来标示特定的元素，如最大的元素和最小的元素；
1 两个对象包含都指向第三个对象的指针；
2 STL容器包含指针。很多STL算法都支持复制和赋值操作，这些操作可用于shared_ptr，但不能用于unique_ptr（编译器发出warning）和auto_ptr（行为不确定）。如果你的编译器没有提供shared_ptr，可使用Boost库提供的shared_ptr。

（2）如果程序不需要多个指向同一个对象的指针，则可使用unique_ptr。如果函数使用new分配内存，并返还指向该内存的指针，将其返回类型声明为unique_ptr是不错的选择。这样，所有权转让给接受返回值的unique_ptr，而该智能指针将负责调用delete。可将unique_ptr存储到STL容器在那个，只要不调用将一个unique_ptr复制或赋给另一个算法（如sort()）。例如，可在程序中使用类似于下面的代码段。


unique_ptr<int> make_int(int n)
{
    return unique_ptr<int>(new int(n));
}
void show(unique_ptr<int> &p1)
{
    cout << *a << ' ';
}
int main()
{
    ...
    vector<unique_ptr<int> > vp(size);
    for(int i = 0; i < vp.size(); i++)
        vp[i] = make_int(rand() % 1000);        // copy temporary unique_ptr
    vp.push_back(make_int(rand() % 1000));     // ok because arg is temporary
    for_each(vp.begin(), vp.end(), show);           // use for_each()
    ...
}

其中push_back调用没有问题，因为它返回一个临时unique_ptr，该unique_ptr被赋给vp中的一个unique_ptr。另外，如果按值而不是按引用给show()传递对象，for_each()将非法，因为这将导致使用一个来自vp的非临时unique_ptr初始化pi，而这是不允许的。前面说过，编译器将发现错误使用unique_ptr的企图。

在unique_ptr为右值时，可将其赋给shared_ptr，这与将一个unique_ptr赋给一个需要满足的条件相同。与前面一样，在下面的代码中，make_int()的返回类型为unique_ptr<int>

unique_ptr<int> pup(make_int(rand() % 1000));   // ok
shared_ptr<int> spp(pup);                       // not allowed, pup as lvalue
shared_ptr<int> spr(make_int(rand() % 1000));   // ok

模板shared_ptr包含一个显式构造函数，可用于将右值unique_ptr转换为shared_ptr。shared_ptr将接管原来归unique_ptr所有的对象。


在满足unique_ptr要求的条件时，也可使用auto_ptr，但unique_ptr是更好的选择。如果你的编译器没有unique_ptr，可考虑使用Boost库提供的scoped_ptr，它与unique_ptr类似。



*****************************************************************************/
/*************************Smartpiont  Ending***********************************/

