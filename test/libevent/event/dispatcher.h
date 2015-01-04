// dispatch_thread.h (2013-12-25)
// Yan Gaofeng (yangaofeng@360.cn)
#ifndef __DISPATCHER_H__
#define __DISPATCHER_H__

#include <boost/scoped_array.hpp>
#include "worker.h"

class Dispatcher {
public:
    Dispatcher() : tid_(0)
                   , thread_num_(10)
                   , last_thread_(0)
    {
        event_base_ = event_base_new();
        CHECK_NOTNULL(event_base_);
        timer_= evtimer_new(event_base_, OnTimer, this);
        CHECK_NOTNULL(timer_);
    }

    ~Dispatcher() {
        event_base_free(event_base_);
        evtimer_del(timer_);
        event_free(timer_);
    }

    void Start();

    static void OnTimer(int fd, short event, void *arg);
    void DoTimer();

    pthread_t tid() { return tid_; }
    void set_tid(pthread_t tid) { tid_ = tid; }

private:
    pthread_t tid_;
    struct event_base *event_base_;
    struct event *timer_;

    const int thread_num_;
    int last_thread_;

    boost::scoped_array<Worker> workers_;
};

#endif /*__DISPATCHER_H__*/

