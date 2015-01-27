// time_diff-inl.h (2015-01-21)
// Yan Gaofeng (yangaofeng@360.cn)

#include <assert.h>
#include <unistd.h>

namespace xlib {
namespace event {

inline TimeDiff::TimeDiff() 
    : us_(0)
{
}

inline TimeDiff::TimeDiff(int64_t us) 
    : us_(us)
{
}

inline TimeDiff::TimeDiff(const struct timeval &t) {
    us_ = t.tv_sec * kMicroseconds + t.tv_usec;
}

TimeDiff TimeDiff::Seconds(int64_t s)
{
    return TimeDiff(s * kMicroseconds);
}

TimeDiff TimeDiff::Milliseconds(int64_t ms)
{
    return TimeDiff(ms * kMilliseconds);
}

TimeDiff TimeDiff::Microseconds(int64_t us)
{
    return TimeDiff(us);
}

int64_t TimeDiff::ToSeconds() const
{
    return us_ / kMicroseconds;
}

int64_t TimeDiff::ToMilliseconds() const
{
    return us_ / kMilliseconds;
}

int64_t TimeDiff::ToMicroseconds() const
{
    return us_;
}

void TimeDiff::To(struct timeval *t) const {
    assert(t != NULL);
    t->tv_sec = us_ / kMicroseconds;
    t->tv_usec = us_ % kMicroseconds;
}


inline bool TimeDiff::IsZero() const {
    return us_ == 0;
}

inline bool TimeDiff::operator < (const TimeDiff &rhs) const
{
    return us_ < rhs.us_;
}

inline bool TimeDiff::operator == (const TimeDiff &rhs) const
{
    return us_ == rhs.us_;
}

inline TimeDiff TimeDiff::operator += (const TimeDiff &rhs)
{
    us_ += rhs.us_;
    return *this;
}

inline TimeDiff TimeDiff::operator -= (const TimeDiff &rhs)
{
    us_ -= rhs.us_;
    return *this;
}

inline TimeDiff TimeDiff::operator *= (int n)
{
    us_ *= n;
    return *this;
}

inline TimeDiff TimeDiff::operator /= (int n)
{
    us_ /= n;
    return *this;
}

inline TimeDiff::operator timeval() const
{
    timeval tv;
    To(&tv);
    return tv;
}

} // evnet
} // xlib

