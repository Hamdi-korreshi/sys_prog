#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "usage: %s file1 file2\n", argv[0]);
        exit(1);
    }
    printf("about to copy %s to %s\n", argv[0], argv[1]);
    return 0;
}
