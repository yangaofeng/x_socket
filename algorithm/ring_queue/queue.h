// queue.h (2014-07-02)
// Yan Gaofeng (yangaofeng@360.cn)

#include <vector>
#include <string>

const int MAX_QUEUE_SIZE = 1024;

class RingQueue{
public:
    RingQueue(int size);
    ~RingQueue() {}

    bool Empty()  { return count_ == 0; }
    bool Full() { return count_ == size_; }

    bool EnQueue(const std::string &elem);
    bool DeQueue(std::string *elem);

    int count() { return count_; }
    int size() { return size_; }

private:
    int size_;
    int front_;
    int rear_;
    int count_;

    std::vector<std::string> data_;
};
