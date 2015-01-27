// event.h (2015-01-26)
// Yan Gaofeng (yangaofeng@360.cn)

#ifndef ECHO_SERVER_EVENT_H_
#define ECHO_SERVER_EVENT_H_

namespace echo_server {

class Event {
public:
    typedef void(*Handler)(int fd, short int which, void *arg);

    explicit Event(int fd, void *arg, Handler handler)
        : fd_(fd)
        , arg_(arg)
        , handler_(handler) {}

    ~Event() {}

    void HandleEvent() {
        handler_(fd_, 0, arg_);
    }

private:
    int fd_;
    void *arg_;
    Handler handler_; 
};

} // echo_server

#endif //ECHO_SERVER_EVENT_H_
