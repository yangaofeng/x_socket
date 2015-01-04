#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/epoll.h>

#include <event.h>

#include <map>

#include "x_socket.h"
#include "echo_server.h"

#define PORT 9527
#define MAXFDS 5000
#define EVENTSIZE 100

#define BUFFER "HTTP/1.1 200 OK\r\nContent-Length: 5\r\nConnection: close\r\nContent-Type: text/html\r\n\r\nHello"
#define BUFFER_SIZE 87

namespace echo_server {

class EchoServer::Event{
public:
    Event(int fd, void *arg, EchoServer::EventHandler handler)
        : fd_(fd)
        , arg_(arg)
        , handler_(handler) {}

    ~Event() {}

    void Handler() {
        handler_(fd_, 0, arg_);
    }

private:
    int fd_;
    void *arg_;
    EchoServer::EventHandler handler_; 
};

class EchoServer::Worker {
public:
    Worker(): write_fd_(fd_[0]), read_fd_(fd_[1]), epoll_fd_(-1) {fd_[0] = -1; fd_[1] = -1;}
    ~Worker();
    bool Init();
    bool AddClient(int fd);

private:
    static void *Run(void *arg);
    static void HandleWorkerEvent(int fd, short which, void *arg);

    friend class Client;

private:
    pthread_t tid_;
    int fd_[2];
    const int &write_fd_;
    const int &read_fd_;

    int epoll_fd_;

    //std::map<int, Client *> clients_;
};

class EchoServer::Client {
public:
    Client(int fd, Worker *worker) : fd_(fd), worker_(worker) {}
    ~Client() {
        if (fd_ != -1) {
            //fprintf(stdout, "close fd %d \n", fd_);
            epoll_ctl(worker_->epoll_fd_, EPOLL_CTL_DEL, fd_, NULL);
            x_close(fd_);
        }
    }

    bool Init() {
        struct epoll_event ev;
        ev.data.fd = fd_;
        ev.data.ptr = static_cast<void *>(new EchoServer::Event(fd_, this, HandleClientEvent));
        ev.events = EPOLLIN | EPOLLET;
        epoll_ctl(worker_->epoll_fd_, EPOLL_CTL_ADD, fd_, &ev);

        return true;
    }

private:
    static void HandleClientEvent(int fd, short which, void *arg) {
        assert(arg != NULL);

        Client *cli = static_cast<Client *>(arg);

        bool ok = true;

        do {
            int recv_bytes = x_recvbytes(cli->fd_, cli->buf_, sizeof(cli->buf_));
            if (recv_bytes < 0) {
                perror("read client data failed");
                ok = false;
                break;
            }
            else if (recv_bytes == 0) {
                fprintf(stdout, "client has closed\n");
                ok = false;
                break;
            }

            int send_bytes = x_send(cli->fd_, BUFFER, BUFFER_SIZE);
            if (send_bytes != BUFFER_SIZE) {
                //perror("echo message to client failed");
                fprintf(stderr, "send_bytes = %d, BUFFER size=%ld\n", send_bytes, strlen(BUFFER));
                ok = false;
                break;
            }

        } while(false);

        //if (!ok) {
            //cli->worker->clients_.erase(cli->fd);
            //event_del(&cli->ev_);
            delete cli;
        //}

        return;
    }

private:
    int fd_;
    char buf_[1024];
    Worker *worker_;
};


EchoServer::Worker::~Worker()
{
    if (fd_[0] != -1) {
        close(fd_[0]);
    }
    if (fd_[1] != -1) {
        close(fd_[0]);
    }

    return;
}

bool EchoServer::Worker::Init()
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
    ev.data.ptr = static_cast<void *>(new EchoServer::Event(read_fd_, this, HandleWorkerEvent));
    ev.events = EPOLLIN | EPOLLET;
    epoll_ctl(epoll_fd_, EPOLL_CTL_ADD, read_fd_, &ev);

    pthread_create(&tid_, NULL, Run, this);

    return true;
}

void EchoServer::Worker::HandleWorkerEvent(int fd, short which, void *arg)
{
    assert(arg != NULL);
    Worker *worker = static_cast<Worker *>(arg);
    if (fd != worker->read_fd_) {
        fprintf(stderr, "HandleWorkerEvent error : fd != worker->read_fd\n");
        return;
    }

    int cfd = 0;
    int bytes = x_recv(fd, (char *)&cfd, sizeof(int));
    if (bytes != sizeof(int)) {
        fprintf(stderr, "thread %llu receive fd failed\n", (unsigned long long)worker->tid_);
        return;
    }

    x_set_sock_no_block(cfd);

    Client *cli = new Client(cfd, worker);
    assert(cli != NULL);
    //worker->clients_.insert(std::make_pair<int, Client *>(cfd, cli));
    if (!cli->Init()) {
        fprintf(stderr, "client init failed\n");
        return;
    }

    return;
}


void *EchoServer::Worker::Run(void *arg)
{
    Worker *worker = static_cast<Worker *>(arg);

    worker->tid_ = pthread_self();

    struct epoll_event events[EVENTSIZE];
    while (1) {
        int nfds = epoll_wait(worker->epoll_fd_, events, EVENTSIZE, -1); 
        for (int i = 0; i < nfds; i++) {
            if (events[i].events & EPOLLIN) {
                EchoServer::Event *echo_ev = static_cast<EchoServer::Event *>(events[i].data.ptr);
                echo_ev->Handler();
            }
            else {
                fprintf(stderr, "invaid event type, fd=%d\n", events[i].data.fd);
            }
        }
    }

    return NULL;
}

bool EchoServer::Worker::AddClient(int fd)
{
    assert(fd != -1);

    int bytes = x_send(write_fd_, (char *)&fd, sizeof(int));
    if (bytes != sizeof(int)) {
        perror("send error");
        return false;
    }

    return true;
}

bool EchoServer::Init()
{
    epoll_fd_ = epoll_create(MAXFDS);
    if (epoll_fd_ == -1) {
        perror("epoll_create error");
        return false;
    }

    //init main thread
    listen_fd_ = x_create_tcp_server("0.0.0.0", port_);
    if (listen_fd_ == -1) {
        return false;
    }

    tid_ = pthread_self();

    //init worker thread
    for (int i = 0; i < worker_count_; i++) {
        Worker *worker = new Worker();
        if (worker == NULL) {
            perror("new error");
            return false;
        }

        bool ok = worker->Init();
        if (!ok) {
            delete worker;
            return false;
        }

        workers_.push_back(worker);
    }

    return true;
}

bool EchoServer::Run()
{
    char ip[64] = {0};
    int port = 0;
    int index = 0;
    while (1) {
        int fd = x_accept(listen_fd_, ip, &port);
        if (fd == -1) {
            perror("accept errror");
            break;
        }
    
        //fprintf(stdout, "accept a client, fd=%d, ip=%s, port=%d \n", fd, ip, port);
        //dispatch to worker thread
        workers_[index]->AddClient(fd);
        index = (index + 1) % workers_.size();
    }

    return true;
}

void EchoServer::Close()
{
    if (listen_fd_ != -1) {
        x_close(listen_fd_);
    }

    return;
}

EchoServer::~EchoServer()
{
    if (workers_.size() > 0) {
        std::vector<Worker *>::iterator it;
        for (it = workers_.begin(); it != workers_.end(); it++) {
            delete *it;
        }
    }

    return;
}

}//namespace echo_server

