// dispatch_thread.cc (2013-12-25)
// Yan Gaofeng (yangaofeng@360.cn)

#include "dispatcher.h"

void Dispatcher::Start()
{
    tid_ = pthread_self();

    workers_.reset(new Worker[thread_num_]);

    struct timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = 100*1000;

    evtimer_add(timer_, &tv);

    event_base_dispatch(event_base_);
}

void Dispatcher::OnTimer(int fd, short event, void *arg)
{
    CHECK_NOTNULL(arg);
    Dispatcher *self = (Dispatcher *)arg;
    self->DoTimer();
}

void Dispatcher::DoTimer()
{
    int index = (last_thread_ + 1) % thread_num_;       //memcached中线程负载均衡算法
    last_thread_ = index;

    LOG(INFO) << "thread " << tid_ << " send a messag";
    write(workers_[index].write_fd()
            , "Hello world!"
            , sizeof("Hello world!") - 1);

    struct timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = 100*1000;

    evtimer_assign(timer_, event_base_, OnTimer, this);
    evtimer_add(timer_, &tv);
}

