#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

void main() {
    char name[4];
    size_t len = 3;
    int ret_val;

    ret_val = gethostname(name, len);
    if (-1 == ret_val) {
        printf("gethostname failed: %s\n", strerror(errno));
    }
    else {
        printf("%s\n", name);
    }
}