#include <stdio.h>
#include <stdlib.h>
#include "x_socket.h"

int main(int argc, char *argv[])
{
    int max_conns = 100000;
    int i = 0;
    int port = -1;
    int *conns = NULL;
    int fd = -1;
    int j = 0;

    if (argc < 2) {
        printf("usage: %s <port> [max_connect]\n", argv[0]);
        return -1;
    }

    port = atoi(argv[1]);

    if (argc == 3 ) {
        max_conns = atoi(argv[2]);
    } 

    conns = (int *)malloc(sizeof(int) * max_conns);
    if (conns == NULL) {
        printf("malloc failed");
        return -1;
    }

    fd = x_create_tcp_server("0.0.0.0", port);
    if (fd == -1) {
        perror("create tcp server error");
        return -1;
    }

    i = 0;
    while (1) {
        conns[i] = x_accept(fd, NULL, NULL);
        if (conns[i] == -1) {
            perror("accept error");
            break;
        }
        i++;
        if (i >= max_conns) {
            break;
        }
    }

    for (j = 0; j < i; j++) {
        x_close(conns[j]);
    }

    printf("accept %d connect\n", i + 1);

    free(conns);

    return 0;
}
