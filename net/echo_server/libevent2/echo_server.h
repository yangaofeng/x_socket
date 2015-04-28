#ifndef __ECHO_SERVER__
#define __ECHO_SERVER__

#include <pthread.h>
#include <event2/event.h>
#include <vector>

namespace echo_server {

class EchoServer{
public:
    EchoServer(int port, int worker_count)
        : port_(port)
        , worker_count_(worker_count)
        , listen_fd_(-1)
        , base_(event_base_new())  {}

    ~EchoServer();

    bool Init();
    bool Run();
    void Close();

    class Worker;
    class Client;

private:
    int port_;
    int worker_count_;

    int listen_fd_;
    pthread_t tid_;
    struct event_base *base_;

    std::vector<Worker *> workers_;
};

}//namespace echo_server
#endif //__ECHO_SERVER__

