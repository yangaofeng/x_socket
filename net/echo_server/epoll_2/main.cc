#include <signal.h> 

#include "echo_server.h"


#define PORT 9527

echo_server::EchoServer g_server(PORT, 10);

static void sig_term(int sig)
{
    g_server.Close();

    return;
}

int main(int argc, char *argv[])
{
    signal(SIGPIPE, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
    //signal(SIGINT, SIG_IGN);
    signal(SIGALRM, SIG_IGN);
    signal(SIGCONT, SIG_IGN);
    signal(SIGTERM, sig_term);

    if (!g_server.Init()) {
        return -1;
    }

    g_server.Run();

    return 0;
}
