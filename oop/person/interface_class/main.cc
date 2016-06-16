// main.cc (2016-06-16)
// Yan Gaofeng (yangaofeng@360.cn)

#include <iostream>
#include "person.h"
#include "real_person.h"

using namespace std;

int main(int argc, char *arg[])
{
    Person *p = new RealPerson("wangpeng", 18);

    cout << "name: " << p->name() << endl;
    cout << "age: " << p->age() << endl;

    delete p;

    return 0;
}
