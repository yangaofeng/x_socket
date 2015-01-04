#include <signal.h> 
#include <boost/scoped_ptr.hpp>

#include "echo_server.h"

boost::scoped_ptr<echo_server::EchoServer> server;

static void sig_term(int sig)
{
    server->Close();

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

    server.reset(new echo_server::EchoServer(9527, 10));
    if (!server->Init()) {
        return -1;
    }

    server->Run();

    return 0;
}
