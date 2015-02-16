// epoll.h (2015-01-21)
// Yan Gaofeng (yangaofeng@360.cn)

#ifndef XLIB_EVENT_EPOLL_H__
#define XLIB_EVENT_EPOLL_H__

#include <sys/epoll.h>

#include <set>

#include "loop.h"

namespace xlib {
namespace event {
namespace epoll {



// An I/O event persistent watcher.
class IoWatcher : public event::IoWatcher {
public:
    typedef void (*Handler)(int fd, bool r, bool w, void *data);

    IoWatcher(Loop *loop, int fd, bool r, bool w, const Handler h, void *data);
    virtual ~IoWatcher();

    virtual bool Start();
    virtual bool Stop();

    virtual int fd() const { return fd_; }
    virtual bool IsPending() const { return pending_; }
    virtual bool HasRead() const { return r_; }
    virtual bool HasWrite() const { return w_; }
    // Prerequires: IsPending() == false
    virtual void Update(int fd, bool r, bool w) {
        assert(!IsPending());
        fd_ = fd;
        r_ = r;
        w_ = w;
    }

private:
    static void Callback(const int events, void *data);

private:
    Loop *loop_;
    int fd_;
    bool r_;
    bool w_;
    Handler handler_;
    void *data_;

    bool pending_;
};

// A timer event watcher.
class TimerWatcher : public event::TimerWatcher {
public:
    typedef void (*Handler)(void *data);

    TimerWatcher(Loop *loop, const TimeDiff &t, bool repeater, const Handler handler, void *data);
    virtual ~TimerWatcher() {}

    virtual bool Start();
    virtual bool Stop();

    // Returns the time diff of the timer
    virtual TimeDiff time_diff() const;

    // Returns true if the timer is repeated.
    virtual bool IsRepeated() const;
    // Updates the I/O events
    // Prerequires: IsPending() == false
    virtual void Update(const TimeDiff& t, bool repeated);

private:
    TimeDiff time_;
    Handler handler_;
    bool repeated_;
};

// An event loop interface.
class Loop : public event::Loop {
public:
    typedef IoWatcher::Handler IoHandler;
    typedef TimerWatcher::Handler TimerHandler;

    Loop() : epfd_(epoll_create(0)), owner_epfd_(true) {}
    Loop(int epfd) : epfd_(epfd), owner_epfd_(false) {}
    Loop(int epfd, bool owner_epfd) : epfd_(epfd), owner_epfd_(owner_epfd) {}

    virtual ~Loop() { if (owner_epfd_ && epfd_ != -1) { close(epfd_); epfd_ = -1; } }

    virtual IoWatcher*
    NewIoWatcher(int fd, bool r, bool w, const IoHandler handler, void *data);

    virtual TimerWatcher*
    NewTimerWatcher(const TimeDiff& t, bool repeated, const TimerHandler handler, void *data);


    virtual bool Run();
    virtual void Stop();

    virtual void AtFork(ForkEvent event);

    int epfd() { return epfd_; }

    bool AddEvent();
    bool DelEvent();
    bool AddTimer();
    bool DelTimer();

private:
    friend class TimerWatcher;

    int epfd_;
    bool owner_epfd_;

    //timer manager
    std::set<std::pair<int64_t, IoWatcher *> > timers_;
};
} /*epoll*/
} /*event*/
} /*xlib*/

#endif /*LDB_EVENT_EPOLL_H__*/

