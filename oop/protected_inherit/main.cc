// main.cc (2015-05-22)
// Yan Gaofeng (yangaofeng@360.cn)

#include <iostream>

using namespace std;

//下面的测试参考<<C++设计新思维>>
//1.7节,policy class的析构函数部分

class B {
public:
    B() { cout << "base constructor" << endl; }

protected:
    //保护成员只有派生类可以访问
    //将析构函数定义为protected，阻止从基类指针释放派生类对象
    //因为不能从基类指针定义派生类对象，这里就没有必须再把析构函数声明为虚函数
    ~B() { cout << "base destuctor" << endl; }
};

class D : public B {
public:
    D() { cout << "derived constructor" << endl; }
    ~D() { cout << "derived destructor" << endl; }
};

int main()
{
    D *d = new D();
    B *b = dynamic_cast<B *>(d);

    //无法通过编译，基类的析构函数为protected
    //delete b;

    //编译通过
    delete d;

    return 0;
}

