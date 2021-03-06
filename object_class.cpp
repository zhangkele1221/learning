					   对象和类
面向对象编程
	采用oop方法时 首先从从用户的角度去考虑对象—— 描述对象所需要的数据 
以及与数据交互所需要的操作  完成对接口的描述后  需要确定如何实现接口
和数据的存储 。最后 使用新的设计方案创建出程序。


类声明：以数据成员的方式描述数据部分，以成员函数（被称为方法）的方式
描述公有接口。
类方法定义：描述如何实现类成员函数

   1访问控制
关键字private和public描述的类成员。 使用类对象的程序都可以直接访问公
有部分， 但是只能通过公有成员函数（或者友元函数）来访问对象的私有成员
因此  公有成员函数是程序和对象的私有成员之间的桥梁，提供了对象和程序
之间的接口。 防止程序直接访问数据被称为数据隐藏。

	数据放在私有部分   类中默认的访问权限为private可以不写 

	.实现类成员函数
定义成员函数时 使用作用域运算符：： 来标识函数所属的类
类方法可以访问类的private组件

     void Stock：：update(double price) 

 使用非成员函数访问私有数据成员————编译器禁止这样做。（友元函数除外）
	 
    将一个成员函数定义为私有成员是为了保护这个成员函数  这个函数也是
相对的固定 一般不需要做调整    private成员函数一般是用来被公有成员函数
直接调用  减少了代码的编写。

    内联方法    （其-定义-位于类声明中的函数都将自动成为内联函数。）    
也可以在类声明之外定义成员函数，并使其成为内联函数，只需在类实现部分
中定义函数时使用iline限定符即可。
	class Stock
   ｛
	  private ：
	  ........
	  void set_tot()；
	｝
	 inline void Stock：：set_tot()
	 {
		 total_val = shares * share_val;
	 }
	 内联函数要求每个使用他们的文件都要对其进行定义．　最好的方法就是
	 将内联函数定义放在定义类的头文件中
＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊

	（所创建的每个新对象都有自己的存储空间，用于存储其内部变量和类成员；
但同一个类的所有对象共享一组方法，即每种方法只有一个副本．－－－－－
－－－－简言之－－－同一个类的　不同对象都有各自不同的数据成员存储区
但是成员方法都是存储在公有的存储区域．）自己的理解！！！！！！！！！

**********************************************************************
							小结
指定类设计的第一步是提供类声明。类声明类似结构声明，可以包括数据成员和
函数成员。1 声明有私有部分，其中的私有成员只能通过成员函数进行访问。
 2 声明还有公有部分，其中公有成员可以被使用类对象的程序直接访问。
 通常 数据成员被放在私有部分，成员被放在公有部分。---比较典型声明格式。
 class className
｛
private：
    data member declarations  //数据隐藏
public：
	member  function prototypes//公有接口
 ｝；
  
**********************************************************************



				类的构造函数和析构函数
例子
	int year =2001；
	struct thing
	｛
		char *pn；
		int m；
    ｝；
	thing bob = ｛“wodog”，-23｝；
	如果是类对象的话就不能这样初始化成员数据了，因为类对象不能这样访问
	私有的数据成员啊！程序只能通过成员函数来访问私有的数据成员 
	so 这样就有了构造函数的出现了  you know！！
	类的构造函数是专门用于构造新的对象，将值赋给他们的数据成员。
	
	构造函数的申明和定义就不说了！！！！！
	
	使用构造函数
　　1  Stock food = Stock("world",250,50);//显示调用构造函数
	2  Stock gar("world",280,60);//隐式调用构造函数
	
	3  Stock *p = new Stock("world",250,50);
	//该对象没有名字但是初始化一个对象后返回一个对象的地址给ｐ
	//被指针管理和使用！！！！！
无法使用一个对象调用一个构造函数　因为构造函数出现在对象之前，
对象是不存在的．ＳＯ构造函数是用来创建对象的，而不是被对象调用的．

	默认构造函数
是未提供显示初始值时，用来创建对象的构造函数．也就是说它用于对象的声明
如果类中没有提供默认构造函数Ｃ＋＋编译器会提供默认的构造函数．
默认构造函数没有参数　因为声明中不包含值．
当且仅当没有定义任何构造函数时　编译器才会提供默认构造函数．
！！！！为类定义了构造函数后，程序员就必须为他提供默认构造函数．
如果提供了非默认构造函数，但是没有提供默认构造函数－－则声明对象时候
就会出错！！！．
也有可能就是想禁止创建未初始化的对象．
．．．．．．．．．．看书看书不写了这一点．．．．．．．．．．．．．


	析构函数



	 
	 
	 

	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 this指针
	 
this 是c++中的一个关键字 也是一个---const指针<<==>> *const this
即this值不可变----就是保存的对象的地址不可变化
this指针　指向当前对象通过它可以访问当前对象的所有成员。
所谓当前对象，是指正在使用的对象。
例如对于stu.show();，stu 就是当前对象，this 就指向 stu。
	 void Student::setname(char *name)
	 {
      this->name = name;
     }
本例中成员函数的参数和成员变量重名，只能通过 this 区分。
以成员函数setname(char *name)为例，它的形参是name，和成员变量name重名，
如果写作name = name;这样的语句，就是给形参name赋值，
而不是给成员变量name赋值。而写作this -> name = name;
后，=左边的name就是成员变量，右边的name就是形参，一目了然。
注意 this 是一个指针，要用->来访问成员变量或成员函数。

this 只能用在类的内部，通过 this 可以访问类的所有成员，
包括 private、protected、public 属性的。	 
	 
this 虽然用在类的内部，但是只有在对象被创建以后才会给 this 赋值，
并且这个赋值的过程是编译器自动完成的，不需要用户干预，
用户也不能显式地给 this 赋值。（很显然嘛 他是个常量嘛 定义必须初始化）	 
	void Student::printThis()
	{
     cout<<this<<endl;
    } 
	  Student *pstu1 = new Student;
      pstu1 -> printThis();
      cout<<pstu1<<endl;
     
	 Student *pstu2 = new Student;
     pstu2 -> printThis();
     cout<<pstu2<<endl;
	 
运行结果：
0x7b17d8
0x7b17d8

0x7b17f0
0x7b17f0
可以发现，this 确实指向了当前对象，而且对于不同的对象，
this 的值也不一样	 
	 
几点注意：
1 this 是 const 指针，它的值是不能被修改的，一切企图修改该指针的操作，
  如赋值、递增、递减等都是不允许的。
2 this 只能在成员函数内部使用，用在其他地方没有意义，也是非法的。
3 只有当对象被创建后 this 才有意义，
  因此不能在 static 成员函数中使用（后续会讲到 static 成员）。	 

再看一个例子  
	 top = stock1.big(stock2);
	 top = stock2.big(stock1);
	 
const Stock& Stock::big(const Stock &s) const
{
	if(s.value>value)
		return s;
	else
		return  *this;
}	 
当这个函数被调用的时候如上面stock1和stock2中任意一个调用的时候
this指针返回的是指向调用对象．	 

*****************************ok!!!!!!*****相信肯定懂了！！！！！**
this 到底是什么

1 this 实际上是成员函数的一个形参，在调用成员函数时将对象的地址
作为实参传递给 this。不过 this 这个形参是隐式的，它并不出现在代码中，
而是在编译阶段由编译器默默地将它添加到参数列表中。

2 this 作为隐式形参，本质上是成员函数的局部变量，
所以只能用在成员函数的内部，并且只有在通过对象调用成员函数时
才给 this 赋值。

****************************Ending  this**************************

	 
	 
	 
	 
	 
	                     使用类
	 
	 运算符重载
运算符重载是c++多态的一种形式。即和(函数重载)一起成为c++编译时多态.

所谓重载，就是赋予新的含义。函数重载（Function Overloading）可以让
一个函数名有多种功能，在不同情况下进行不同的操作。
运算符重载（Operator Overloading）也是一个道理，
同一个运算符可以有不同的功能。	 

//实现运算符 “+“ 重载
complex complex::operator+(const complex &A) const
{
    complex B;
    B.m_real = this->m_real + A.m_real;
    B.m_imag = this->m_imag + A.m_imag;
    return B;
}
当执行c3 = c1 + c2;语句时，编译器检测到+号左边（+号具有左结合性，
所以先检测左边）是一个 complex 对象，就会调用成员函数operator+()，
也就是转换为下面的形式：
c3 = c1.operator+(c2); //c1 是要调用函数的对象，c2 是函数的实参。

上面的运算符重载还可以有更加简练的定义形式：
complex complex::operator+(const complex &A)const
{
 return complex(this->m_real + A.m_real, this->m_imag + A.m_imag);
}
return 语句中的
complex(this->m_real + A.m_real, this->m_imag + A.m_imag)
会创建一个临时对象，这个对象没有名称，是一个匿名对象。
在创建临时对象过程中调用构造函数，
return 语句将该临时对象作为函数返回值。

返回值不是引用的原因是*******
不要返回一个局部变量或者是临时变量的引用ok
因为 局部变量和临时变量 函数执行玩后会over 引用就不知道是引用什么了


运算符重载函数不仅可以作为类的成员函数，还可以作为全局函数。


//在类中声明为友元函数
//运算符重载函数不是 complex 类的成员函数，但是却用到了 complex 类
//的 private 成员变量，所以必须在 complex 类中将该函数声明为友元函数。
friend complex operator+(const complex &A, const complex &B);

//在全局范围内重载+
complex operator+(const complex &A, const complex &B)
{
    complex C;
    C.m_real = A.m_real + B.m_real;
    C.m_imag = A.m_imag + B.m_imag;
    return C;
}
当执行c3 = c1 + c2;语句时，编译器检测到+号两边都是 complex 对象，
就会转换为类似下面的函数调用：
c3 = operator+(c1, c2);


*****************************注意*******************************
1 运算符sizeof、条件运算符: ?成员选择符.和域解析运算符::
.*成员指针运算符  const_cast dynamic_cast reinterpret_cast 
static_cast 　typrid(RTTI运算符)等不能被重载。

2 重载不能改变运算符的优先级和结合性

3 重载不会改变运算符的用法，原有有几个操作数、操作数在左边还是在右边，
这些都不会改变。

4 运算符重载函数既可以作为类的成员函数，也可以作为全局函数。
将运算符重载函数作为类的成员函数时，二元运算符的参数只有一个，
一元运算符不需要参数。之所以少一个参数，是因为这个参数是隐含的 this 
另外，将运算符重载函数作为全局函数时，
一般都需要在类中将该函数声明为友元函数。原因很简单（up写了代码自己看）

5 箭头运算符->、下标运算符[ ]、函数调用运算符( )、
赋值运算符=只能以成员函数的形式重载

	
	
    	友元 
**友元函数（让函数成为友元，即赋予该函数与类的成员函数相同的访问限制）
**友元类
**友元成员函数

先看个例子
Time Time::operator+(const Time & t) const
 {
      Time sum;
      sum.minutes = minutes + t.minutes;
      sum.houre = houre + t.houre + sum.minutes / 60;
      sum.minutes %=60;
      return sum ;
  
 }

 如果出现 A= B * 2.75;//怎么办呢？
将被转换为　　A = Ｂ.operator*(2.75);
但是出现　A= 2.75 * B ;//怎么转换呢？　2.75不是Time类型的对象啊！

有一种很好的解决办法*****--- 非成员函数  该函数不是由对象调用的而是
它使用的所有值都是显示参数．
A= 2.75 * B；　
将被转换为　A = operator*(2.75,B);  
 继续转换为<<=========>>Time operator *(double m, const Time & t);
即2.75*Time  这样就带来了问题 他是不能访问私有成员数据的因为他是
非成员函数哦    so ！！！！友元函数登场咯！！！
















	 