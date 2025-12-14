#include <stdio.h>
#include <unistd.h>
#include <limits.h>

void main() {
    char name[HOST_NAME_MAX+1];
    size_t len = HOST_NAME_MAX+1;
    int ret_val;

    ret_val = gethostname(name, len);
    if (-1 == ret_val) {
        perror("gethostname");
    }
    else {
        printf("%s\n", name);
    }
}