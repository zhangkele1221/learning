/**********************************************
 > File Name: bind_function.cpp
 > Author: ZY
 > Created Time: 2017年04月14日 星期五 17时57分31秒
*******************************************/

例子1：
class Foo
{
 public:
  void methodA();
  void methodInt(int a);
};
class Bar
{
 public:
  void methodB();
};

boost::function<void()> f1; // 无参数，无返回值

Foo foo;
f1 = boost::bind(&Foo::methodA, &foo);
f1(); // 调用 foo.methodA();
Bar bar;
f1 = boost::bind(&Bar::methodB, &bar);
f1(); // 调用 bar.methodB();

f1 = boost::bind(&Foo::methodInt, &foo, 42);
f1(); // 调用 foo.methodInt(42);

boost::function<void(int)> f2; // int 参数，无返回值
f2 = boost::bind(&Foo::methodInt, &foo, _1);
f2(53); // 调用 foo.methodInt(53);

例子2：
// 企鹅能游泳，也能跑
class Penguin
{
 public:
  void run();
  void swim();
};

// 麻雀能飞，也能跑
class Sparrow
{
 public:
  void fly();
  void run();
};

// 以 closure 作为接口
typedef boost::function<void()> FlyCallback;
typedef boost::function<void()> RunCallback;
typedef boost::function<void()> SwimCallback;

// 一个既用到run，也用到fly的客户class
class Foo
{
 public:
  Foo(FlyCallback flyCb, RunCallback runCb) : flyCb_(flyCb), runCb_(runCb)
  { }
 private:
  FlyCallback flyCb_;
  RunCallback runCb_;
};
 
// 一个既用到run，也用到swim的客户class
class Bar
{
 public:
  Bar(SwimCallback swimCb, RunCallback runCb) : swimCb_(swimCb), runCb_(runCb)
  { }
 private:
  SwimCallback swimCb_;
  RunCallback runCb_;
};

int main()
{
  Sparrow s;
  Penguin p;
  // 装配起来，Foo要麻雀，Bar要企鹅。
  Foo foo(bind(&Sparrow::fly, &s), bind(&Sparrow::run, &s));
  Bar bar(bind(&Penguin::swim, &p), bind(&Penguin::run, &p));
}


/*
不做总结，在一个新鲜事物面前，例子比阐述更有力量，你看了这两个例子，
你就明白了boost::function和bind是如何使用的了。
*/





