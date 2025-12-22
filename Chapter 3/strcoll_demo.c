#define _GNU_SOURCE
#include "common_hdrs.h"

int main(int argc, char *argv[]) {
    char *smallest;
    char usage_msg[256];
    int i = 1,j;

    if (argc < 3 ){
        sprintf(usage_msg, "%s string string ...\n", basename(argv[0]));
        usage_error(usage_msg);
    }
    if (NULL == setlocale(LC_COLLATE, ""))
        fatal_error(LOCALE_ERROR, "setlocale() could not set the given locale");

    smallest = argv[i];
    for (j= i + 1; j <= argc; j++) {
        if ( strcoll(smallest, argv[j]) > 0)
            smallest = argv[j];
    }
    printf("%s\n", smallest);
    return 0;
}