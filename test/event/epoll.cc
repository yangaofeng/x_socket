// epoll.cc (2015-01-21)
// Yan Gaofeng (yangaofeng@360.cn)

#include <event/epoll.h>

namespace xlib {
namespace event {
namespace epoll {

IoWatcher* Loop::NewIoWatcher(int fd, bool r, bool w, const IoHandler h, void *data)
{
    return new IoWatcher(this, fd, r, w, h, data);
}

TimerWatcher* Loop::NewTimerWatcher(const TimeDiff& t, bool repeated, const TimerHandler handler, void *data)
{
    return = new TimerWatcher(this, t, repeater, handler, data);
}

bool Loop::Run()
{
    struct epoll_event events[512];

    while (!quit_) {
        int count = epoll_wait(epfd, events, 512, -1);
        if (count == -1) {
            return false;
            break;
        }

        //process timer event

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

bool TimerWatcher::Start()
{
    std::pair<std::multimap::iterator, bool> result
        = loop_->timers_.insert(std::make_pair(t.ToMicroseconds, this));
    if (!result.second) {
        return false;
    }

    return true;
}

bool TimerWatcher::Stop()
{
}

} // epoll
} // event
} // xlib

