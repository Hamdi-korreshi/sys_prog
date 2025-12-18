#define _GNU_SOURCE
#include "common_hdrs.h"

int main(int argc, char *argv[]) {
    char formatted_date[200];
    time_t current_time;
    struct tm *broken_down_time;
    char format_str[MAXLEN];

    strcpy(format_str, "%c");
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