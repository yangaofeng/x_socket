// main.cc (2013-09-03)
// Yan Gaofeng (yangaofeng@360.cn)

#include <stdio.h>
#include <uuid/uuid.h>

int main()
{
    uuid_t uu;
    uuid_generate(uu);

    int i;
    unsigned char *p = (unsigned char *)uu;
    printf("uuid size: %d\n", sizeof(uu));
    for (i = 0; i < sizeof(uu); i++) {
        printf("%02x", *p);
        p++;
    }

    printf("\n");

    return 0;
}

