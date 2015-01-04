// max.hpp (2013-07-09)
// Yan Gaofeng (yangaofeng@360.cn)

#ifndef __MAX_HPP__
#define __MAX_HPP__

template <typename T>
inline 
T const &max(T const &a, T const &b)
{
    return a < b ? b : a;
}

#endif /*__MAX_HPP__*/

