#include <stdio.h>

int main(int argc, char*argv[]) {
    argc--;
    for (; argc >= 0; --argc) {
        printf("%s\n", argv[argc]);
    }
    return 0;
}