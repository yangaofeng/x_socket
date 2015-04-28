// main.cc (2013-07-09)
// Yan Gaofeng (yangaofeng@360.cn)

#include <iostream>
#include "accum2.h"

int main()
{
    int num[] = {1,2,3,4,5};
    std::cout << "the average value of the integer values is "
        << accum(&num[0], &num[5]) / 5 << std::endl;

    char name[] = "templates";
    int length = sizeof(name) - 1;

    std::cout << "the average value of the characters in \""
        << name << "\" is "
        << accum(&name[0], &name[length]) / length
        << std::endl;

    float fnum[] = {1.1, 2.2, 3,3, 4.4, 5.5};
    std::cout << "the average value of the float values is "
        << accum(&fnum[0], &fnum[5]) / 5 << std::endl;


    return 0;
}

