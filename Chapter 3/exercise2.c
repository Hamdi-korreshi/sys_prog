#include <locale.h>
#define _GNU_SOURCE
#include "common_hdrs.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int compare_len(const void *a, const void *b) {
    const char **sa = a;
    const char **sb = b;
    return strcoll(*sa, *sb);
}

int main(int argc, char *argv[]) {
    setlocale(LC_COLLATE, "");
    qsort(&argv[1], argc-1, sizeof(argv), compare_len);
    for (int i = 1; i <argc; i++) {
        printf("%s\n", argv[i]);
    }
}