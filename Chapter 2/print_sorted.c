#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare_len(const void *a, const void *b) {
    const char **sa = a;
    const char **sb = b;
    size_t la = strlen(*sa);
    size_t lb = strlen(*sb);
    if (la < lb) return -1;
    if (la > lb) return 1;
    return strcmp(*sa, *sb);
}

int main(int argc, char*argv[]) {
    qsort(&argv[1], argc-1, sizeof(argv), compare_len);
    for (int i = 1; i <argc; i++) {
        printf("%s\n", argv[i]);
    }
    return 0;
}
