// main.cc (2015-01-22)
// Yan Gaofeng (yangaofeng@360.cn)

#include <iostream>

#include "skip_list.h"

using namespace std;

int main(int argc, char *argv[])
{
    SkipList list;

    //list.Insert(5, 5);
    //list.Insert(1, 1);
    //list.Insert(3, 3);
    //list.Insert(8, 8);
    //list.Insert(4, 4);
    //list.Insert(9, 9);
    //list.Insert(12, 12);
    //list.Insert(2, 2);
    //list.Insert(15, 15);
    //list.Insert(0, 0);
    //list.Insert(13, 13);
    //list.Insert(6, 6);
    //list.Insert(7, 7);
    //list.Insert(10, 10);
    //list.Insert(11, 11);
    //list.Insert(14, 14);

    for (int i = 10000 - 1; i >= 0; i--) {
        list.Insert(i, i);
    }

    Key k[] = {
        8, 88, 273, 697, 777, 921, 
        1233, 2188, 3555, 4976, 6216,
        7899, 8233, 9002, 9527, 9999};
        //8001, 8002, 8003, 8004, 8005,
        //9555, 9556, 9557, 9558, 9559};
    Value v;

    for (int i = 0; i < sizeof(k)/sizeof(Key); i++) {
        cout << "start search key: " << k[i] << endl;
        bool ok = list.Search(k[i], &v);
        if (!ok) {
            return -1;
        }
    }


    //SkipList::Iterator it(list);

    //while (it.Valid()) {
    //    cout << "key: " << it.key() 
    //        << ", value: "<< it.value() 
    //        << ", level: " << it.level() << endl;
    //    it.Next();
    //}

    return 0;
}

