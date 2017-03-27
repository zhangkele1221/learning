/**********************************************
 > File Name: smart_txt1.cpp
 > Author: ZY
 > Created Time: 2017年03月23日 星期四 23时00分39秒
*******************************************/


#include<iostream>
using namespace std;

//2. C++智能指针简单介绍
/*
STL一共给我们提供了四种智能指针：auto_ptr、unique_ptr、shared_ptr和
weak_ptr（本文章暂不讨论）。
模板auto_ptr是C++98提供的解决方案，C+11已将将其摒弃，并提供了另外两种解决方案。
然而，虽然auto_ptr被摒弃，但它已使用了好多年：同时，如果您的编译器不支持
其他两种解决力案，auto_ptr将是唯一的选择。
*/

//所有的智能指针类都有一个explicit构造函数，以指针作为参数。
//比如auto_ptr的类模板原型为：
templet<class T>
class auto_ptr {
  explicit auto_ptr(X* p = 0) ; 
  ...
};
//因此不能自动将指针转换为智能指针对象，必须显式调用：
shared_ptr<double> pd; 
double *p_reg = new double;
pd = p_reg;                               // not allowed (implicit conversion)
pd = shared_ptr<double>(p_reg);           // allowed (explicit conversion)
shared_ptr<double> pshared = p_reg;       // not allowed (implicit conversion)
shared_ptr<double> pshared(p_reg);        // allowed (explicit conversion)



//对全部三种智能指针都应避免的一点：
string vacation("I wandered lonely as a cloud.");
shared_ptr<string> pvac(&vacation);   // No
//pvac过期时，程序将把delete运算符用于非堆内存，这是错误的。



//3. 为什么摒弃auto_ptr？
auto_ptr< string> ps (new string ("I reigned lonely as a cloud.”）;
auto_ptr<string> vocation; 
vocaticn = ps;

/*
上述赋值语句将完成什么工作呢？如果ps和vocation是常规指针，则两个指针将指向同
一个string对象。这是不能接受的，因为程序将试图删除同一个对象两次——一次是ps过期
时，另一次是vocation过期时。要避免这种问题，方法有多种：

   定义陚值运算符，使之执行深复制。这样两个指针将指向不同的对象，其中的一个对象是另一个对象的副本，缺点是浪费空间，所以智能指针都未采用此方案。
   建立所有权（ownership）概念。对于特定的对象，只能有一个智能指针可拥有，这样只有拥有对象的智能指针的构造函数会删除该对象。然后让赋值操作转让所有权。这就是用于auto_ptr和uniqiie_ptr 的策略，但unique_ptr的策略更严格。
   创建智能更高的指针，跟踪引用特定对象的智能指针数。这称为引用计数。例如，赋值时，计数将加1，而指针过期时，计数将减1,。当减为0时才调用delete。这是shared_ptr采用的策略。
当然，同样的策略也适用于复制构造函数。
每种方法都有其用途，但为何说要摒弃auto_ptr呢？
*/


//看下面一个实例next！！！！








