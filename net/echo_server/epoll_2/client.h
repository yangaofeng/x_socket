// client.h (2015-01-26)
// Yan Gaofeng (yangaofeng@360.cn)

#ifndef ECHO_SERVER_CLIENT_H_
#define ECHO_SERVER_CLIENT_H_

#include "event.h"

namespace echo_server {

class Worker;

class Client {
public:
    Client(int fd, Worker *worker) 
        : fd_(fd), event_(fd, this, Handler), worker_(worker) 
    {}

    ~Client();

    bool Init();

private:
    static void Handler(int fd, short which, void *arg);
    void ProcessEvent(int fd, short which);

private:
    int fd_;
    Event event_;
    char buf_[1024];
    Worker *worker_;
};

} //echo_server

#endif //ECHO_SERVER_CLIENT_H_
