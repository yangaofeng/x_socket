// queue.cc (2014-07-02)
// Yan Gaofeng (yangaofeng@360.cn)

#include "queue.h"

RingQueue::RingQueue(int size) 
    : size_(size), 
    front_(0), 
    rear_(0), 
    count_(0)
{
    data_.resize(size_);
}

bool RingQueue::EnQueue(const std::string &elem)
{
    if (Full()) {
        return false;
    }

    data_[rear_] = elem;
    rear_ = (rear_+ 1) % size_;
    count_++;

    return true;
}

bool RingQueue::DeQueue(std::string *elem)
{
    if (Empty()) {
        return false;
    }

    *elem = data_[front_];
    front_ = (front_ + 1) % size_;
    count_--;

    return true;
}

