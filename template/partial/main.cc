// main.cc (2014-01-14)
// Yan Gaofeng (yangaofeng@360.cn)

#include <iostream>

using namespace std;

template<class T>
void f(T t)
{
    cout << "base" << endl;
}

template<class T>
void f(T *t)
{
    cout << "pointer" << endl;

    T b;
    b = 100;
    cout << b << endl;
    //cout << typeid(b) << endl;
}

template<class T>
void f(const T *t)
{
    cout << "const pointer" << endl;


    T x = 100;
    T *y = &x;
    cout << x << sizeof(x) << endl;
    cout << y << sizeof(y) << endl;
    //cout << typeid(x) << endl;
}

int main()
{
    int a = 1;
    const int b = 2;
    f(a);
    f(&a);
    f(&b);

    return 0;
}

