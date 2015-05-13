// main.cc (2015-05-07)
// Yan Gaofeng (yangaofeng@360.cn)
#include <iostream>
#include <boost/function.hpp>

using namespace std;
using namespace boost;

int func1(int i) { return i * 5; }
bool func2(int i, double d) { return (i > d); }

int main()
{
    function1<int, int> f1;
    f1 = &func1;
    cout << f1(10) << endl;


    function2<bool, int, double> f2;
    f2 = &func2;
    cout << f2(10, 1.1) << endl;

    return 0;
}
