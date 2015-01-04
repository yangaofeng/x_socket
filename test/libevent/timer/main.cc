// main.cc (2013-12-26)
// Yan Gaofeng (yangaofeng@360.cn)

#include <time.h>
#include <event2/event.h>
#include <iostream>

using namespace std;

struct event_base *base;
struct event *timer;
struct timeval tv;

void OnTimer(int fd, short what, void *arg)
{
    cout << "Hello" << endl;

    evtimer_assign(timer, base, OnTimer, NULL);
    evtimer_add(timer, &tv);
}

int main(int argc, char *argv[])
{
    base = event_base_new();
    timer = evtimer_new(base
            , OnTimer
            , NULL);
    tv.tv_sec = 1;
    tv.tv_usec = 0;
    evtimer_add(timer, &tv);

    event_base_dispatch(base);

    evtimer_del(timer);
    event_free(timer);
    event_base_free(base);

    return 0;
}

