#include <gnu/libc-version.h>
#include <stdio.h>

int main() {
    printf("This version of gnu libc is %s\n", gnu_get_libc_version());
    return 0;
}