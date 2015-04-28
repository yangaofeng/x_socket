// worker.cc (2015-01-26)
// Yan Gaofeng (yangaofeng@360.cn)

#include <unistd.h>
#include <pthread.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <stdio.h>

#include "x_socket.h"
#include "client.h"
#include "event.h"
#include "worker.h"

#define MAXFDS 5000
#define EVENTSIZE 100

namespace echo_server {

Worker::~Worker()
{
    if (fd_[0] != -1) {
        close(fd_[0]);
        fd_[0] = -1;
    }

    if (fd_[1] != -1) {
        close(fd_[0]);
        fd_[1] = -1;
    }

    return;
}

bool Worker::Init()
{
    int ret = socketpair(AF_LOCAL, SOCK_STREAM, 0, fd_);
    if (ret == -1) {
        perror("socketpair()");
        return false;
    }

    epoll_fd_ = epoll_create(MAXFDS);
    if (epoll_fd_ == -1) {
        perror("worker epoll_fd_ create failed");
        return false;
    }

    struct epoll_event ev;
    ev.data.fd = read_fd_;
    ev.data.ptr = static_cast<void *>(new Event(read_fd_, this, Handler));
    ev.events = EPOLLIN | EPOLLET;
    epoll_ctl(epoll_fd_, EPOLL_CTL_ADD, read_fd_, &ev);

    pthread_create(&tid_, NULL, Run, this);

    return true;
}

void Worker::Handler(int fd, short which, void *arg)
{
    assert(arg != NULL);
    Worker *worker = static_cast<Worker *>(arg);
    worker->HandleServerEvent(fd, which);

    return;
}


void *Worker::Run(void *arg)
{
    Worker *worker = static_cast<Worker *>(arg);
    worker->EventLoop();

    return NULL;
}

bool Worker::AddClient(int fd)
{
    assert(fd != -1);

    int bytes = x_send(write_fd_, (char *)&fd, sizeof(int));
    if (bytes != sizeof(int)) {
        perror("send error");
        return false;
    }

    return true;
}

void Worker::EventLoop()
{
    struct epoll_event events[EVENTSIZE];
    while (1) {
        int nfds = epoll_wait(epoll_fd_, events, EVENTSIZE, -1); 
        for (int i = 0; i < nfds; i++) {
            if (events[i].events & EPOLLIN) {
                Event *e = static_cast<Event *>(events[i].data.ptr);
                e->HandleEvent();
            }
            else {
                fprintf(stderr, "invaid event type, fd=%d\n", events[i].data.fd);
            }
        }
    }
}

void Worker::HandleServerEvent(int fd, short which)
{
    if (fd != read_fd_) {
        fprintf(stderr, "Handler error : fd != worker->read_fd\n");
        return;
    }

    int cfd = 0;
    int bytes = x_recv(fd, (char *)&cfd, sizeof(int));
    if (bytes != sizeof(int)) {
        fprintf(stderr, "thread %llu receive fd failed\n", (unsigned long long)tid_);
        return;
    }

    x_set_sock_no_block(cfd);

    Client *cli = new Client(cfd, this);
    assert(cli != NULL);
    //worker->clients_.insert(std::make_pair<int, Client *>(cfd, cli));
    if (!cli->Init()) {
        fprintf(stderr, "client init failed\n");
        return;
    }
}

} //echo_server

