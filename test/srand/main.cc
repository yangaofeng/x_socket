// main.cc (2015-01-22)
// Yan Gaofeng (yangaofeng@360.cn)

#include <iostream>
#include <time.h>
#include <stdlib.h>

using namespace std;

int main(int argc, char *argv[])
{
    srand(time(NULL));

    for (int i = 0; i < 10; i++) {
        int a = rand() % 10;
        cout << a << endl;
    }

    return 0;
}

