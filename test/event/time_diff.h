// time_diff.h (2015-01-21)
// Yan Gaofeng (yangaofeng@360.cn)

#ifndef XLIB_EVENT_TIME_DIFF_H__
#define XLIB_EVENT_TIME_DIFF_H__

#include <sys/time.h>

namespace xlib {
namespace event {

class TimeDiff {
public:
    enum {
        kMilliseconds = 1000,
        kMicroseconds = 1000000
    };

    TimeDiff();
    TimeDiff(const struct timeval &t);

    static TimeDiff Seconds(int64_t s);
    static TimeDiff Milliseconds(int64_t ms);
    static TimeDiff Microseconds(int64_t us);

    int64_t ToSeconds() const;
    int64_t ToMilliseconds() const;
    int64_t ToMicroseconds() const;

    //conveter
    void To(struct timeval *t) const;

    //comparator
    bool IsZero() const;
    bool operator < (const TimeDiff &rhs) const;
    bool operator == (const TimeDiff &rhs) const;

    //Math operator
    TimeDiff operator += (const TimeDiff &rhs);
    TimeDiff operator -= (const TimeDiff &rhs);
    TimeDiff operator *= (int n);
    TimeDiff operator /= (int n);

    //Convertor
    operator timeval() const;

private:
    explicit TimeDiff(int64_t us);
    int64_t us_;
};


} // event
} // xlib

#include "time_diff-inl.h"

#endif //XLIB_EVENT_TIME_DIFF_H__

