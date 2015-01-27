// loop.h (2014-08-28)
// Li Xinjie (xjason.li@gmail.com)

#ifndef XLIB_EVENT_LOOP_H_
#define XLIB_EVENT_LOOP_H_

#include <event/time_diff.h>

namespace xlib {
namespace event {

class Watcher {
public:
    Watcher() {}
    virtual ~Watcher() {}
    // Returns true if watcher is started
    virtual bool IsPending() const = 0;
    // Starts the watcher,
    // Prerequires: IsPending() == false
    // Post: IsPending() == true
    virtual bool Start() = 0;
    // Stops the watcher
    // Prerequires: IsPending() == true
    // Post: IsPending() == false
    virtual bool Stop() = 0;
private:
    // Disable copying
    Watcher(const Watcher&);
    Watcher& operator=(const Watcher&);
};

// An I/O event persistent watcher.
class IoWatcher : virtual public Watcher {
public:
    typedef void (*Handler)(int fd, bool r, bool w, void *data);

    virtual ~IoWatcher() {}

    // Returns the watcher's file descriptor.
    virtual int fd() const = 0;
    // Returns true if the watcher has write event to care for.
    virtual bool HasRead() const = 0;
    // Returns true if the watcher has read event to care for.
    virtual bool HasWrite() const = 0;
    // Updates the I/O events
    // Prerequires: IsPending() == false
    virtual void Update(int fd, bool r, bool w) = 0;

    // Updates the I/O events
    // Prerequires: IsPending() == false
    void Update(bool r, bool w) { Update(fd(), r, w); }
};

// A timer event watcher.
class TimerWatcher : virtual public Watcher {
public:
    typedef void (*Handler)(void *data);

    virtual ~TimerWatcher() {}

    // Returns the time diff of the timer
    virtual TimeDiff time_diff() const = 0;
    // Returns true if the timer is repeated.
    virtual bool IsRepeated() const = 0;
    // Updates the I/O events
    // Prerequires: IsPending() == false
    virtual void Update(const TimeDiff& t, bool repeated) = 0;
};

// An event loop interface.
class Loop {
public:
    typedef IoWatcher::Handler IoHandler;
    typedef TimerWatcher::Handler TimerHandler;
    //typedef SignalWatcher::Handler SignalHandler;
    //typedef UserWatcher::Handler UserHandler;

    Loop() {}
    virtual ~Loop() {}

    virtual IoWatcher*
    NewIoWatcher(int fd, bool r, bool w, const IoHandler handler, void *data) = 0;

    virtual TimerWatcher*
    NewTimerWatcher(const TimeDiff& t, bool repeated, const TimerHandler h, void *data) = 0;

    virtual bool Run() = 0;
    virtual void Stop() = 0;

    enum ForkEvent {
        kForkPrepare,
        kForkParent,
        kForkChild,
    };
    virtual void AtFork(ForkEvent event) = 0;

private:
    Loop(const Loop&);
    Loop& operator=(const Loop&);
};

} // namespace event
} // namespace ldb

#endif // LDB_EVENT_LOOP_H_

