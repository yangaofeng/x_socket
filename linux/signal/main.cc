// main.cc (2015-12-11)
// Yan Gaofeng (yangaofeng@360.cn)

#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <iostream>

using namespace std;

void sig_handler(int sig)
{
    cout << "sig handler called, sig: " << sig << endl;
}

int main(int argc, char *argv[])
{
    signal(SIGCHLD, sig_handler);

    pid_t pid = fork();
    if (pid == -1) {
        cout << "fork error: " << strerror(errno) << endl;
        return -1;
    } else if (pid == 0) {
        //child process
        sleep(5);
        return 0;
    } else {
        int status = 0;
        int rc = wait(&status);
        if (rc == -1) {
            cout << "wait error: " << strerror(errno) << endl;
        } else {
            cout << "wait success, rc: " << rc << endl;
        }
    }

    return 0;
}
