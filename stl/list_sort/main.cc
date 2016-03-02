// main.cc (2016-03-01)
// Yan Gaofeng (yangaofeng@360.cn)

#include <iostream>
#include <list>

using namespace std;

void Print(std::list<int> &l)
{
    cout << "print list start -----" << endl;
    std::list<int>::iterator it = l.begin();
    for (; it != l.end(); it++) {
        cout << *it << endl;
    }
    cout << "print list end -----" << endl;
}

bool cmp1(int a, int b)
{
    return a < b;
}

bool cmp2(int a, int b)
{
    return a > b;
}

int main(int argc, char *argv[])
{
    std::list<int> l;
    l.push_back(3);
    l.push_back(5);
    l.push_back(1);

    Print(l);

    l.sort(cmp1);
    Print(l);

    l.sort(cmp2);
    Print(l);

    return 0;
}
