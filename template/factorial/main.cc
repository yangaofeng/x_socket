// main.cc (2015-05-16)
// Yan Gaofeng (yangaofeng@360.cn)

//from Effective c++

#include <iostream>

using namespace std;

template <unsigned n>
struct Factorial {
    enum { value = n * Factorial<n-1>::value };
};

template <>
struct Factorial<0> {
    enum { value = 1 };
};

int main()
{
    cout << Factorial<5>::value << endl;
    cout << Factorial<10>::value << endl;

    return 0;
}
