#ifndef __ECHO_SERVER__
#define __ECHO_SERVER__

#include <pthread.h>
#include <vector>

namespace echo_server {

class Worker;

class EchoServer{
public:
    EchoServer(int port, int worker_count)
        : port_(port)
        , worker_count_(worker_count)
        , listen_fd_(-1)
    {}

    ~EchoServer();

    bool Init();
    bool Run();
    void Close();

private:
    int port_;
    int worker_count_;

    int listen_fd_;
    pthread_t tid_;

    std::vector<Worker *> workers_;
};

}//namespace echo_server
#endif //__ECHO_SERVER__

