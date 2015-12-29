// main.cc (2015-12-28)
// Yan Gaofeng (yangaofeng@360.cn)

#include <unistd.h>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    std::string host_name;
    char buf[1024];
    int rc = gethostname(buf, sizeof(buf));
    if (rc != 0) {
        cout << "get hosthame failed, rc: " << rc << endl;
        return -1;
    }

    host_name = buf;
    cout << "host name: " << host_name << endl;

    return 0;
}
