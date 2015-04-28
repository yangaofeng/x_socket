// main.cc (2013-07-09)
// Yan Gaofeng (yangaofeng@360.cn)

#include <iostream>
#include "max.hpp"

inline int const &max(int const &a, int const &b)
{
    return a < b ? b : a;
}

template <typename T>
inline T const &max(T const &a, T const &b, T const &c)
{
    return ::max(::max(a, b), c);
}


int main()
{
    int a = 1;
    int b = 2;
    std::cout << ::max(a, b) << std::endl;

    double f1 = 3.4;
    double f2 = -6.7;
    std::cout << ::max(f1, f2) << std::endl;

    std::string str1 = "mathematics";
    std::string str2 = "math";
    std::cout << ::max(str1, str2) << std::endl;

    std::cout << ::max<double>(4, 4.7) << std::endl;


    std::cout << ::max(7, 42, 68) << std::endl;
    std::cout << ::max(7.0, 42.0) << std::endl;
    std::cout << ::max('a', 'b') << std::endl;

    std::cout << ::max<>(7, 42) << std::endl;
    std::cout << ::max<double>(7, 42) << std::endl;

    std::cout << ::max<double>('a', 42.7) << std::endl;

    return 0;
}

