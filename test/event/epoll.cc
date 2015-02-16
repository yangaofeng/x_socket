// epoll.cc (2015-01-21)
// Yan Gaofeng (yangaofeng@360.cn)

#include <event/epoll.h>

namespace xlib {
namespace event {
namespace epoll {

/////////////////////////////////////////////////////////////////////////
//Loop implement
//

IoWatcher* Loop::NewIoWatcher(int fd, bool r, bool w, const IoHandler h, void *data)
{
    return new IoWatcher(this, fd, r, w, h, data);
}

TimerWatcher* Loop::NewTimerWatcher(const TimeDiff& t, bool repeated, const TimerHandler handler, void *data)
{
    return new TimerWatcher(this, t, repeated, handler, data);
}

bool Loop::Run()
{
    struct epoll_event events[512];

    while (!quit_) {

        int timeout = -1;
        if (!timers_.empty()) {
            TimeDiff t = timers_.begin();
            timeout = (int)t.ToMilliseconds();
        }

        struct timeval tv1;
        int rc = gettimeofday(&tv, NULL);
        if (rc == -1) {
            //error log
            return;
        }

        int read_timeout = timeout;

        int count = epoll_wait(epfd, events, 512, real_timeout);
        if (count == -1) {
            //log
            return false;
        }
        
        if (count == 0) {
            //process timer event
            continue;
        }

        struct  timeval tv2;
        rc = gettimeofday(&tv2, NULL);
        if (rc == -1) {
            //error log
            return false;
        }

        int used_time = ((tv2.tv_sec - tv1.tv_sec) * 1000) + ((tv2.tv_usec - tv1.tv.usec) / 1000);
        real_timeout -= used_time;
        assert(real_timeout >= 0);
        if (real_timeout == 0) {
            //process timer event
        }

        //process io event
        for (int i = 0; i < count; i++) {
            IoWatcher::Callback(events[i].events, events[i].ptr);
        }
    }

    return true;
}

void Loop::Stop()
{
    quit_ = false;
    close(epfd);
}

void IoWatcher::Callback(const int events, void *data);
{
    IoWatcher *iw = (IoWatcher *)data;
    iw->handler_(iw->fd(), events & EPOLLIN, events & EPOLLOUT, iw->data());
}

IoWatcher::IoWatcher(Loop *loop, int fd, bool r, bool w, const Handler handler, void *data)
    : loop_(loop), 
    fd_(fd), 
    r_(r), 
    w_(w), 
    handler_(handler), 
    data_(data), 
    pending_(false)
{
}

IoWatcher::~IoWatcher()
{
    Stop();
}

bool IoWatcher::Start()
{
    assert(!IsPending());

    struct epoll_event ee;
    if (r_) {
        ee.events |= EPOLLIN;
    }

    if (w_) {
        ee.events |= EPOLLOUT;
    }

    ee.data.ptr = (void *)this;
    int rc = epoll_ctl(loop_->epfd(), EPOLL_CTL_ADD, fd_, &ee);
    if (rc == -1) {
        return false;
    }

    pending_ = true;

    return true;
}

bool IoWatcher::Stop()
{
    int rc = epoll_ctl(loop_->epfd_, EPOLL_CTL_DEL, fd_, NULL);
    if (rc == -1) {
        return false;
    }

    pending_ = false;

    return true;
}


//////////////////////////////////////////////////////////////////////////////
//timer watcher implement
//
bool TimerWatcher::Start()
{
    std::pair<std::multimap::iterator, bool> result
        = loop_->timers_.insert(std::make_pair(time_.ToMicroseconds(), this));
    if (!result.second) {
        return false;
    }

    return true;
}

bool TimerWatcher::Stop()
{
    std::set<std::pair<int64_t, IoWatcher *> >::iterator pos;
    pos = loop_->timers_.find(std::make_pair(time_.ToMicroseconds(), this));
    if (pos == loop_->timers_.end()) {
        return false;
    }

    loop_->timers_.erase(pos);
    return true;
}

TimeDiff TimerWatcher::time_diff()
{
    return timer_diff_;
}

bool TimerWatcher::IsRepeated()
{
    //used by Loop::Run logic
    return repeated_;
}

void TimerWatcher::Update(const TimeDiff& t, bool repeated)
{
    time_ = t;
    repeated_ = repeated;
}

} // epoll
} // event
} // xlib

