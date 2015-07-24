#include <stdio.h>
#include <stdlib.h>
#include "x_socket.h"

int main(int argc, char *argv[])
{
    int connections = 1;
    char *ip = NULL;
    int port = -1;
    int *conns = NULL;
    int i = 0;
    int j = 0;

    if (argc < 3) {
        printf("usage: %s <ip> <port> [connections]\n", argv[0]);
        return -1;
    }

    ip = argv[1];
    port = atoi(argv[2]);

    if (argc == 4 ) {
        connections = atoi(argv[3]);
    } 

    conns = (int *)malloc(sizeof(int) * connections);
    if (conns == NULL) {
        printf("malloc failed");
        return -1;
    }

    for (i = 0; i < connections; i++) {
        conns[i] = x_create_tcp_client(ip, port);
        if (conns[i] == -1) {
            perror("create tcp client error");
            break;
        }
        printf("create client fd: %d\n", conns[i]);
    }

    printf("create %d connect\n", i + 1);

    pause();

    for (j = 0; j < i; j++) {
        x_close(conns[j]);
    }

    free(conns);

    return 0;
}
