#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <sys/types.h>

#include "x_socket.h"
#include "echo_server.h"
#include "worker.h"
#include "client.h"

namespace echo_server {

bool EchoServer::Init()
{
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

