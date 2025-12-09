#include <stdio.h>

int main(int argc, char *argv[]) {
    printf("%s arguments: \n", argv[0]);
    for (int i =0; i < argc; i++) {
        printf("%d: %s\n", i, argv[i]);
    }
    return 0;
}