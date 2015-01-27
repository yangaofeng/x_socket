// main.cc (2015-01-22)
// Yan Gaofeng (yangaofeng@360.cn)
#include <iostream>
#include <set>

using namespace std;

int main(int argc, char *argv[])
{
    set<pair<int, int> > s;
    s.insert(make_pair(0, 1));
    s.insert(make_pair(0, 1));
    s.insert(make_pair(0, 0));
    s.insert(make_pair(0, 3));
    s.insert(make_pair(1, 0));
    s.insert(make_pair(1, 5));
    s.insert(make_pair(3, 8));

    set<pair<int, int> >::iterator it;
    for (it = s.begin(); it != s.end(); it++) {
        cout << it->first << ":" << it->second << endl;
    }

    return 0;
}
