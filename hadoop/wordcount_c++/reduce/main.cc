// main.cc (2016-05-10)
// Yan Gaofeng (yangaofeng@360.cn)

#include <iostream>
#include <map>

using namespace std;

int main(int argc, char *argv[])
{
    std::string key;
    std::string value;

    std::map<std::string, int> word_count;
    std::map<std::string, int>::iterator it;

    while (cin >> key) {
        cin >> value;

        it = word_count.find(key);
        if (it != word_count.end()) {
            (it->second)++;
        } else {
            word_count.insert(std::make_pair(key, 1));
        }
    }

    for (it = word_count.begin(); it != word_count.end(); it++) {
        cout << it->first << "\t" << it->second << endl;
    }

    return 0;
}
