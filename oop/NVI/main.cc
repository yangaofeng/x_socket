// main.cc (2015-08-17)
// Yan Gaofeng (yangaofeng@360.cn)

#include <iostream>

using namespace std;

/*
 * 参考《Effective C++》条款35
 *
 * */

class B {
public:
    void SayHello() const {
        cout << "ready to call SayHello" << endl;
        DoSayHello();
        cout << "after call SayHello" << endl;
    }

private:
    virtual void DoSayHello() const  = 0;
    //virtual void SayHello() const {
    //    cout << "hello world" << endl;
    //}
};

class D : public B {
public:

private:
    virtual void DoSayHello() const {
        cout << "hello world, derive calss" << endl;
    }
};

int main()
{
    D d;
    d.SayHello();

    return 0;
}

