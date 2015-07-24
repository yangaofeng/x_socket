#include <stdlib.h>
#include <unistd.h>

int main()
{
    char *buf = (char *)malloc(100);
    usleep(1);
    free(buf);
    return 0;
}
