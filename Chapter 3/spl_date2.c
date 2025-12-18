#define _GNU_SOURCE
#include "common_hdrs.h"

void getformat(int nargs, char *argvec[], char *format_str) {
    char err_msg[MAXLEN];
    if (argvec[nargs-1][0]=='+') {
        if ( strlen(argvec[nargs-1] + 1) < MAXLEN) {
            strncpy(format_str,argvec[nargs-1]+1, MAXLEN-1);
        }
        else {
            sprintf(err_msg, "Format string length is too long\n");
            fatal_error(BAD_FORMAT_ERROR, err_msg);
        }
    }
    else {
        sprintf(err_msg, "%s: Format should be +\"format-string\"\n", basename(argvec[0]));
        fatal_error(BAD_FORMAT_ERROR, err_msg);
    }
}

int main(int argc, char *argv[]) {
    char formatted_date[200];
    time_t current_time;
    struct tm *broken_down_time;
    char format_str[MAXLEN];

    if (argc < 2) {
        strcpy(format_str, "%c");
    }
    else
        getformat(argc, argv, format_str);
    
    current_time = time(NULL);

    if ((broken_down_time = localtime(&current_time)) == NULL) {
        fatal_error(EOVERFLOW, "localtime");
    }
    
    if ( 0 == strftime(formatted_date, sizeof(formatted_date), format_str, broken_down_time)) {
        fatal_error(EXIT_FAILURE, "Conversion to a date-time string" 
            " failed or produced an empty string\n");
    }
    printf("%s\n", formatted_date);
    return 0;
}