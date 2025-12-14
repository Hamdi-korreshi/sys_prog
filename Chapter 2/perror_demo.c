#include <stdio.h>
#include <unistd.h>

void main() {
    char name[4];
    size_t len = 3;
    int ret_val;

    ret_val = gethostname(name, len);
    if (-1 == ret_val) {
        perror("gethostname");
    }
    else {
        printf("%s\n", name);
    }
}