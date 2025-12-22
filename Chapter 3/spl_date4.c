#include "error_exits.h"
#include <locale.h>
#include <stdio.h>
#define _GNU_SOURCE
#include "common_hdrs.h"

#define FORMAT "%c"
#define MAXLEN STRING_MAX
#define BAD_FORMAT_ERROR    -1
#define TIME_ADJUST_ERROR   -2

int parse_time_adjustment(/* IN */ char *time_adj_str, /* OUT */ struct tm *datetm) {
    char *delim = " \t";
    char *token;
    int number;
    char err_msg[STRING_MAX];
    int flags = ONLY_DIGITS | NO_TRAILING;
    int res;
    token = strtok(time_adj_str, delim);

    while ( token != NULL) {
        res = get_int(token, flags, &number, err_msg);
        if (VALID_NUMBER != res) {
            fatal_error(res, err_msg);
        }
        token = strtok(NULL, delim);
        if (NULL == token)
            fatal_error(TIME_ADJUST_ERROR, "missing a time unit\n");
        if (NULL != strstr(token, "year")) datetm->tm_year += number;
        else if (NULL != strstr(token, "month")) datetm->tm_mon += number;
        else if (NULL != strstr(token, "week")) datetm->tm_mday += 7*number;
        else if (NULL != strstr(token, "day")) datetm->tm_mday += number;
        else if (NULL != strstr(token, "hour")) datetm->tm_hour += number;
        else if (NULL != strstr(token, "minute")) datetm->tm_min += number;
        else if (NULL != strstr(token, "second")) datetm->tm_sec += number;
        else fatal_error(TIME_ADJUST_ERROR, "Found invalid time time_unit in amount to adjust the time\n");
        token = strtok(NULL, delim);
    }
    return 0;
}

int adjust_time(struct tm *datetm, struct tm *time_to_add) {
    datetm->tm_year += time_to_add->tm_year;
    datetm->tm_mon += time_to_add->tm_mon;
    datetm->tm_mday += time_to_add->tm_mday;
    datetm->tm_hour += time_to_add->tm_hour;
    datetm->tm_min += time_to_add->tm_min;
    datetm->tm_sec += time_to_add->tm_sec;

    errno = 0;
    mktime(datetm);
    if (errno != 0) {
        fatal_error(errno, NULL);
    }
    return 0;
}

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
        sprintf(err_msg, "%s: Format should be +\"format-string\"\n", argvec[0]);
        fatal_error(BAD_FORMAT_ERROR, err_msg);
    }
}

int main(int argc, char *argv[]) {
    /* global var that sets the locale, updating all the time functions to use that*/
    char *mylocale;
    if ( (mylocale = setlocale(LC_TIME, "")) == NULL)
        fatal_error(LOCALE_ERROR, "setlocale() could not set the given locale");
    char formatted_date[MAXLEN];
    time_t current_time;
    struct tm *broken_down_time;
    struct tm time_adj = {0};
    char format_str[MAXLEN];
    char usage_msg[512];
    char ch;
    char options[] = ":d:h"; // the firs colon means turn off error message, second one after d means d needs a argument. 
    // h by itself says that h is optional options 
    BOOL d_option = FALSE;
    char *d_arg;
    int d_arg_length;

    opterr = 0;
    while(TRUE) {
        ch = getopt(argc, argv, options);
        if ( -1 == ch)
            break;
        switch ( ch ) {
            case 'd':
                d_option = TRUE;
                d_arg_length = strlen(optarg);
                d_arg = malloc(d_arg_length * sizeof(char));
                if ( NULL == d_arg )
                    fatal_error(EXIT_FAILURE, "calloc could not allocate memory\n");
                strcpy(d_arg,optarg);
                break;
            case 'h':
                sprintf(usage_msg, "%s [ -d <time adjustments> ]"
                    " [+\"format specification\"]", basename(argv[0]));
                usage_error(usage_msg);
            case '?':
                fprintf(stderr, "Found invalid option %c\n", optopt);
                sprintf(usage_msg, "%s [ -d <time adjustments> ]"
                    " [+\"format specification\"]", basename(argv[0]));
                usage_error(usage_msg);
            case ':':
                fprintf(stderr, "Missing required argument to -d\n");
                sprintf(usage_msg, "%s [ -d <time adjustments> ]"
                    " [+\"format specification\"]", basename(argv[0]));
                usage_error(usage_msg);
        }
    }
    if ( 0 == argc - optind ) {
        strcpy(format_str, "%c");
    }
    else {
        getformat(argc, argv, format_str);
    }

    current_time = time(NULL);
    broken_down_time = localtime(&current_time);
    if ( broken_down_time == NULL) {
        fatal_error(EOVERFLOW, "localtime");
    }
    if (d_option) {
        parse_time_adjustment(d_arg, &time_adj);
        adjust_time(broken_down_time, &time_adj);
        free(d_arg);
    }
    
    if ( 0 == strftime(formatted_date, sizeof(formatted_date), format_str, broken_down_time)) {
        fatal_error(EXIT_FAILURE, "Conversion to a date-time string" 
            " failed or produced an empty string\n");
    }
    printf("%s\n", formatted_date);
    return 0;
}
