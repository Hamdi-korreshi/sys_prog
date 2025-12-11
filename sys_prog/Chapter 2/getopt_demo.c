#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

int main(int argc, char *argv[]) {
    int ch;
    char options[] = ":hb::c:1";
    int opt_h = 0;
    int opt_1 = 0;
    int opt_b = 0;
    int opt_c = 0;
    char b_arg[32] = "";
    char c_arg[32] = "";

    opterr = 0;
    while (TRUE) {
        ch = getopt(argc, argv, options);
        if (-1 == ch)
            break;
        switch (ch) {
            case 'h':
                opt_h = TRUE; break;
            case 'b':
                opt_b = TRUE;
                if ( 0 != optarg ) 
                    strcpy(b_arg, optarg); break;
            case 'c':
                opt_c = TRUE;
            case '1':
                opt_1 = TRUE; break;
            case '?':
                printf("Found invalid option %c\n", optopt); break;
            case ':':
                printf("Missing required arguments ");
        }
    }
}