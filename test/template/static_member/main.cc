// main.cc (2013-07-02)
// Yan Gaofeng (yangaofeng@360.cn)

#include <iostream>

using namespace std;

template <typename T> struct testClass {
    static int data_;
};

template <> int testClass<char>::data_ = 1;
template <> int testClass<long>::data_ = 2;

int main(int argc, char *argv[])
{
    cout << boolalpha << (1==testClass<char>::data_) << endl;
    cout << boolalpha << (2==testClass<long>::data_) << endl;

    return 0;
}

