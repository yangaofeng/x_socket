// work_thread.cc (2013-12-25)
// Yan Gaofeng (yangaofeng@360.cn)

#include "worker.h"

void Worker::Start()
{
    int fd[2];
    int rc = socketpair(AF_LOCAL, SOCK_STREAM, 0, fd);
    CHECK(rc == 0);

    read_fd_ = fd[1];
    write_fd_ = fd[0];

    rc = event_assign(event()
            , event_base()
            , read_fd_
            , EV_READ | EV_PERSIST
            , OnRead 
            , (void *)this);
    CHECK(rc == 0);

    rc = event_add(event_, NULL);
    CHECK(rc == 0);

    rc = pthread_create(&tid_, NULL, worker_thread, this);
    CHECK(rc == 0);
}

void Worker::OnRead(int fd, short which, void *arg)
{
    CHECK_NOTNULL(arg);
    Worker *self = (Worker *)arg;
    self->DoRead();
}

void Worker::DoRead()
{
    int ret;
    char buf[128];
    ret = read(read_fd_, buf, 128);
    if (ret > 0) {
        buf[ret] = '\0';
        LOG(INFO) << "thread " << tid_ << " receive message : " << buf;
    }
    else if (ret == 0) {
        LOG(ERROR) << "read_fd_ closed: " << read_fd_;
    }
    else {
        LOG(ERROR) << "read error: " << strerror(errno);
    }

    return;
}

void *Worker::worker_thread(void *arg)
{
    CHECK_NOTNULL(arg);
    Worker *self = (Worker *)arg;

    self->Run();

    return NULL;
}

void Worker::Run()
{
    tid_ = pthread_self();
    event_base_dispatch(event_base_);
}

