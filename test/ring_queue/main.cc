// main.cc (2014-07-02)
// Yan Gaofeng (yangaofeng@360.cn)

#include <iostream>

#include "queue.h"

using namespace std;

void Print(RingQueue &q);

int main(int argc, char *argv[])
{
    RingQueue q(3);

    q.EnQueue("1");
    q.EnQueue("2");
    q.EnQueue("3");

    Print(q);

    q.EnQueue("5");
    q.EnQueue("6");
    q.EnQueue("7");
    q.EnQueue("8");
    Print(q);

    return 0;
}

void Print(RingQueue &q)
{
    cout << "queue size: " << q.size() << endl;
    cout << "queue elem count: " << q.count() << endl;

    int count = q.count();
    for (int i = 0; i < count; i++) {
        std::string elem;
        if (!q.DeQueue(&elem)) {
            cout << "de queue error" << endl;
            break;
        }
        cout << elem << endl;
    }
}

