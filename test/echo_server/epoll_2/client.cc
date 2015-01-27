// client.cc (2015-01-26)
// Yan Gaofeng (yangaofeng@360.cn)

#include <unistd.h>
#include <stdio.h>
#include <assert.h>
#include <sys/epoll.h>

#include "worker.h"
#include "x_socket.h"

#include "client.h"

#define BUFFER "HTTP/1.1 200 OK\r\nContent-Length: 5\r\nConnection: close\r\nContent-Type: text/html\r\n\r\nHello"
#define BUFFER_SIZE 87

namespace echo_server {

Client::~Client() {
    if (fd_ != -1) {
        //fprintf(stdout, "close fd %d \n", fd_);
        epoll_ctl(worker_->epoll_fd(), EPOLL_CTL_DEL, fd_, NULL);
        x_close(fd_);
    }
}

bool Client::Init()
{
    struct epoll_event ev;
    ev.data.fd = fd_;
    ev.data.ptr = (void *)&event_;
    ev.events = EPOLLIN | EPOLLET;
    int rc = epoll_ctl(worker_->epoll_fd(), EPOLL_CTL_ADD, fd_, &ev);
    if (rc == -1) {
        perror("client init failed");
        return false;
    }

    return true;
}

void Client::Handler(int fd, short which, void *arg)
{
    assert(arg != NULL);
    Client *cli = static_cast<Client *>(arg);
    cli->ProcessEvent(fd, which);
}

void Client::ProcessEvent(int fd, short which)
{
    bool ok = true;

    do {
        int recv_bytes = x_recvbytes(fd_, buf_, sizeof(buf_));
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

        int send_bytes = x_send(fd_, (char *)BUFFER, BUFFER_SIZE);
        if (send_bytes != BUFFER_SIZE) {
            //perror("echo message to client failed");
            fprintf(stderr, "send_bytes = %d, BUFFER size=%d\n", 
                    send_bytes, BUFFER_SIZE);
            ok = false;
            break;
        }

    } while(false);

    //short connect, close socket
    delete this;
}

} //echo_server
