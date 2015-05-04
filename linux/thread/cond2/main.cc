#include <stdint.h>
#include <sys/time.h>
#include <pthread.h>
#include <iostream>
#include <iomanip>

const int SIZE = 1000;
const int NUM = 1000000;

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
        //cout << "queue is full, wait" << endl;
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
        //cout << "queue is empty, wait" << endl;
        pthread_cond_wait(&notempty_, &mutex_);
    }
    int i = buf_[head_];
    head_ = (head_ + 1) % SIZE;
    //通知等待notfull_的线程，队列不满
    pthread_mutex_unlock(&mutex_);
    pthread_cond_signal(&notfull_);
    return i;
}

int64_t produce_time = 0;

void *producer(void* args) {
    MyQueue* queue = (MyQueue*)args;
    struct timeval tv1, tv2;
    gettimeofday(&tv1, NULL);
    for (int i = 0; i < NUM; ++i) {
        queue->push(i);
        //cout << "push:" << i << endl;
    }
    gettimeofday(&tv2, NULL);
    produce_time = (tv2.tv_sec - tv1.tv_sec) * 1000000 + (tv2.tv_usec - tv1.tv_usec);
}

int64_t consume_time = 0;

void *consumer(void* args) {
    MyQueue* queue = (MyQueue*)args;
    struct timeval tv1, tv2;
    gettimeofday(&tv1, NULL);
    for (int i = 0; i < NUM; ++i) {
        int e = queue->pop();
        //cout << "pop:" << e << endl;
    }
    gettimeofday(&tv2, NULL);
    consume_time = (tv2.tv_sec - tv1.tv_sec) * 1000000 + (tv2.tv_usec - tv1.tv_usec);
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

    cout << std::fixed << setprecision(3) << "push used time: " << (float)produce_time / 1000 << "ms" << endl;
    cout << std::fixed << setprecision(3) << "pop used time: " << (float)consume_time / 1000 << "ms" << endl;
    float avg = (float)(produce_time + consume_time) / 2 / 1000;
    cout << std::fixed << setprecision(3) << "average used time: " << avg << "ms" << endl;

    float x = (float)NUM / (avg / 1000);
    cout << std::fixed << setprecision(3) << "benchmark: " << x << "/s" << endl;

    return 0;
}

