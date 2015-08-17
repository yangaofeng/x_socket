// main.cc (2015-08-07)
// Yan Gaofeng (yangaofeng@360.cn)

#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;

int main()
{
    std::ostringstream os;
    //os << std::setfill("0") << std::setw(5) << 1;
    os << std::setfill('0') << std::setw(5) << 1;
    cout << os.str() << endl;
}
