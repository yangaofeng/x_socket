// work_thread.h (2013-12-25)
// Yan Gaofeng (yangaofeng@360.cn)

#ifndef __WORKER_H__
#define __WORKER_H__

#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <event2/event.h>
#include <glog/logging.h>

class Worker {
public:
    Worker() : tid_(0), read_fd_(-1), write_fd_(-1) {
        event_base_ = event_base_new();
        CHECK_NOTNULL(event_base_);
        event_ = event_new(event_base_, -1, 0, NULL, NULL);
        CHECK_NOTNULL(event_);
        Start();
    }

    ~Worker() {
        event_del(event_);
        event_free(event_);
        event_base_free(event_base_);
        close(read_fd_);
        close(write_fd_);
    }

    int write_fd() { return write_fd_; }

private:
    void Start();

    struct event_base *event_base() const { return event_base_; }
    struct event *event() const { return event_; }
    int read_fd() { return read_fd_; }
    void set_read_fd(int read_fd) { read_fd_ = read_fd; }
    void set_write_fd(int write_fd) { write_fd_ = write_fd; }
    pthread_t tid() { return tid_; }

    static void *worker_thread(void *arg);
    void Run();
    static void OnRead(int fd, short which, void *arg);
    void DoRead();

private:
    pthread_t tid_;
    struct event_base *event_base_;
    struct event *event_;
    int read_fd_;
    int write_fd_;
};

#endif /*__WORKER_H__*/

