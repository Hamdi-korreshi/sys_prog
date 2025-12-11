#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char*argv[]) {
    for (; argc >= 0; --argc) {
        printf("%s\n", argv[argc]);
    }
    return 0;
}
