// worker.h (2015-01-26)
// Yan Gaofeng (yangaofeng@360.cn)

#ifndef ECHO_SERVER_WORKER_H_
#define ECHO_SERVER_WORKER_H_

namespace echo_server {

class Worker {
public:
    Worker() 
        : write_fd_(fd_[0]), 
        read_fd_(fd_[1]), 
        epoll_fd_(-1)
    { fd_[0] = -1; fd_[1] = -1; }

    ~Worker();

    bool Init();
    bool AddClient(int fd);

    int epoll_fd() const { return epoll_fd_; }

private:
    static void *Run(void *arg);
    static void Handler(int fd, short which, void *arg);
    void EventLoop();
    void HandleServerEvent(int fd, short which);

private:
    pthread_t tid_;
    int fd_[2];
    const int &write_fd_;
    const int &read_fd_;

    int epoll_fd_;

    //std::map<int, Client *> clients_;

};

} //echo_server

#endif //ECHO_SERVER_WORKER_H_

