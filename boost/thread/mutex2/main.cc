#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/bind.hpp>
#include <iostream>

/*
 * boost thread example, use bind replace functor
 * 
 * url: http://www.cppblog.com/shaker/archive/2007/10/06/33583.html
 *
 */

boost::mutex io_mutex;

void count(int id)
{
    for (int i = 0; i < 10; ++i)
    {
        boost::mutex::scoped_lock
            lock(io_mutex);
        std::cout << id << ": " <<
            i << std::endl;
    }
}

int main(int argc, char* argv[])
{
    boost::thread thrd1(
            boost::bind(&count, 1));
    boost::thread thrd2(
            boost::bind(&count, 2));
    thrd1.join();
    thrd2.join();
    return 0;
}
