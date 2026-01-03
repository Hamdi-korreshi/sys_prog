#define _XOPEN_SOURCE 700
#include "common_hdrs.h"
#define TESTNUM 123456789.12
#define BASE0 ((locale_t) 0)

int main(int argc, char* argv[]) {
    time_t t;
    struct tm *tm;
    char buf[100];
    char err_msg[STRING_MAX];
    locale_t loc, newloc;

    if (argc < 2 ) {
        sprintf(err_msg, "Usage: %s locale1 [locale2]\n", argv[0]);
        usage_error(err_msg);
    }
    /* Create a new locale object, using the LC_NUMERIC settings
       from the locale specified in argv[1]. */
    if ( (loc = newlocale(LC_NUMERIC_MASK, argv[1], BASE0)) == BASE0)
        fatal_error(EXIT_FAILURE, "newlocale");
    
    if (argc > 2) {
        if ( (newloc = newlocale(LC_TIME_MASK, argv[2], loc)) == BASE0)
            fatal_error(EXIT_FAILURE, "newlocale");
        loc = newloc;
    }

    uselocale(loc);
    printf("With numeric settings of %s, number is: %'8.2f\n", argv[1], TESTNUM);
    t = time(NULL);

    if ( (tm = localtime(&t)) == NULL)
        fatal_error(EXIT_FAILURE, "localtime");
    if  ( 0 == strftime(buf, sizeof(buf), "%c", tm))
        fatal_error(EXIT_FAILURE, "strftime");
    printf("With time setting of %s, date/time is: %s\n", argv[2], buf);
    
    uselocale(LC_GLOBAL_LOCALE);
    freelocale(loc);
    return 0;
}