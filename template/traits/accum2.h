// accum2.h (2013-07-09)
// Yan Gaofeng (yangaofeng@360.cn)

#ifndef __ACCUM2_H__
#define __ACCUM2_H__

#include "accumtraits2.h"

template <typename T>
inline
typename AccumulationTraits<T>::AccT accum(T const *beg
        , T const *end)
{
    typedef typename AccumulationTraits<T>::AccT AccT;

    AccT total = AccumulationTraits<T>::zero;
    while (beg != end) {
        total += *beg;
        ++beg;
    }

    return total;
}

#endif /*__ACCUM2_H__*/

