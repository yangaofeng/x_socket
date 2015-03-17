#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char source[] = "hello, world! welcome to china!";
    char delim[] = " ,!";

    char *s = strdup(source);
    char *t = s;
    char *token;
    for (token = strsep(&s, delim); token != NULL; token = strsep(&s, delim)) {
        if (*token == '\0') {
            printf("strsep return \\0\n");
            continue;
        }

        printf("%x, %s\n", token, token);
    }

    printf("\n");

    free(t);

    printf("%d, %d\n", *(""), '\0');

    return 0;
}
