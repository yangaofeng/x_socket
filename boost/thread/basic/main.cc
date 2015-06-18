// main.cc (2015-06-18)
// Yan Gaofeng (yangaofeng@360.cn)

#include <boost/thread/thread.hpp>
#include <iostream>

/*
 * boost thread example
 * url : http://www.cppblog.com/shaker/archive/2007/10/06/33583.html
 */

void hello()
{
    std::cout <<
        "Hello world, I'm a thread!"
        << std::endl;
}

int main(int argc, char* argv[])
{
    boost::thread thrd(&hello);
    thrd.join();
    return 0;
}
