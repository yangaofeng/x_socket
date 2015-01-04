// accum1.hpp (2013-07-09)
// Yan Gaofeng (yangaofeng@360.cn)
#ifndef __ACCUM1_HPP__
#define __ACCUM1_HPP__

template <typename T>
inline
T accum(T const *beg, T const *end)
{
    T total = T();
    while (beg != end) {
        total += *beg;
        ++beg;
    }

    return total;
}

#endif /*__ACCUM1_HPP__*/

