#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <event.h>

#include <map>

#include "x_socket.h"
#include "echo_server.h"

#define BUFFER "HTTP/1.1 200 OK\r\nContent-Length: 5\r\nConnection: close\r\nContent-Type: text/html\r\n\r\nHello"
#define BUFFER_SIZE 87

namespace echo_server {

class EchoServer::Worker {
public:
    Worker():base_(NULL), write_fd_(fd_[0]), read_fd_(fd_[1]) {fd_[0] = -1; fd_[1] = -1;}
    ~Worker();
    bool Init();
    bool AddClient(int fd);

private:
    static void *Run(void *arg);
    static void HandleWorkerEvent(int fd, short which, void *arg);

    friend class Client;

private:
    pthread_t tid_;
    struct event_base *base_;
    struct event event_;
    int fd_[2];
    const int &write_fd_;
    const int &read_fd_;

    //std::map<int, Client *> clients_;
};

class EchoServer::Client {
public:
    Client(int fd, Worker *worker) : fd_(fd), worker_(worker) {}
    ~Client() {
        if (fd_ != -1) {
            //fprintf(stdout, "close fd %d \n", fd_);
            x_close(fd_);
        }
    }

    bool Init() {
        event_set(&ev_
                , fd_
                , EV_READ | EV_PERSIST
                , HandleClientEvent
                , this);

        event_base_set(worker_->base_, &ev_);

        if (event_add(&ev_, 0) == -1) {
            perror("Worker::Init:: event_add()");
            return false;
        }

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
            event_del(&cli->ev_);
            delete cli;
        //}

        return;
    }

private:
    int fd_;
    struct event ev_;
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

    if (base_ != NULL) {
        event_base_free(base_);
        base_ = NULL;
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

    base_ = event_init();
    if (base_ == NULL) {
        perror("event_init()");
        return 1;
    }

    event_set(&event_
            , read_fd_
            , EV_READ | EV_PERSIST
            , HandleWorkerEvent
            , this);

    event_base_set(base_, &event_);

    if (event_add(&event_, 0) == -1) {
        perror("Worker::Init::event_add()");
        return 1;
    }

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

    int client_fd = 0;
    int bytes = x_recv(fd, (char *)&client_fd, sizeof(int));
    if (bytes != sizeof(int)) {
        fprintf(stderr, "thread %llu receive fd failed\n", (unsigned long long)worker->tid_);
        return;
    }

    Client *cli = new Client(client_fd, worker);
    assert(cli != NULL);
    //worker->clients_.insert(std::make_pair<int, Client *>(client_fd, cli));
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

    event_base_loop(worker->base_, 0);

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
    base_ = event_init();
    if (base_ == NULL) {
        perror("event_init( base )");
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

        x_set_sock_no_block(fd);
    
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

