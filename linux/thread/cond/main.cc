#include <pthread.h>
#include <iostream>

const int SIZE = 100;
const int NUM = 200;

using namespace std;

class MyQueue {
public:
    MyQueue() : head_(0), tail_(0) {
        pthread_mutex_init(&mutex_, NULL);
        pthread_cond_init(&notempty_, NULL);
        pthread_cond_init(&notfull_, NULL);
    }

    ~MyQueue() {
        pthread_mutex_destroy(&mutex_);
        pthread_cond_destroy(&notempty_);
        pthread_cond_destroy(&notfull_);
    }

    void push(int i);
    int pop();

private:
    bool is_full() {
        return (tail_ + 1) % SIZE == head_;
    }

    bool is_empty() {
        return tail_ == head_;
    }

private:
    int buf_[SIZE];
    int head_;
    int tail_;
    pthread_mutex_t mutex_;   //互斥使用锁
    pthread_cond_t notempty_; //非空条件变量
    pthread_cond_t notfull_;  //队列不满条件变量
};

//尾部插入元素
void MyQueue::push(int i) {
    pthread_mutex_lock(&mutex_);
    while (is_full()) {
        cout << "queue is full, wait" << endl;
        pthread_cond_wait(&notfull_, &mutex_);
    }
    buf_[tail_] = i;
    tail_ = (tail_ + 1) % SIZE;
    //通知等待notempty_的线程，队列不空
    pthread_mutex_unlock(&mutex_);
    pthread_cond_signal(&notempty_);
}

//头部取元素
int MyQueue::pop() {
    pthread_mutex_lock(&mutex_);
    while (is_empty()) {
        cout << "queue is empty, wait" << endl;
        pthread_cond_wait(&notempty_, &mutex_);
    }
    int i = buf_[head_];
    head_ = (head_ + 1) % SIZE;
    //通知等待notfull_的线程，队列不满
    pthread_mutex_unlock(&mutex_);
    pthread_cond_signal(&notfull_);
    return i;
}

void *producer(void* args) {
    MyQueue* queue = (MyQueue*)args;
    for (int i = 0; i < NUM; ++i) {
        queue->push(i);
        cout << "push:" << i << endl;
    }
}

void *consumer(void* args) {
    MyQueue* queue = (MyQueue*)args;
    for (int i = 0; i < NUM; ++i) {
        cout << "pop:" << queue->pop() << endl;
    }
}

int main(int argc, char *argv[]) 
{
    MyQueue queue;

    pthread_t pro_thread;
    pthread_t con_thread;
    pthread_create(&pro_thread, NULL, producer, &queue);
    pthread_create(&con_thread, NULL, consumer, &queue);

    pthread_join(pro_thread, NULL);
    pthread_join(con_thread, NULL);

    cout << "End" << endl;
}

