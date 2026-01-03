#include <locale.h>
#define _GNU_SOURCE
#include <langinfo.h>
#include "common_hdrs.h"

int main(int argc, char*argv) {
    char* mylocale;
    if ((mylocale= setlocale(LC_TIME, "")) == NULL)
        fatal_error(LOCALE_ERROR, "setlocale() could not set the given locale");
    printf("The current locale is %s\n", mylocale);
    
    for (int dayofweek= DAY_1; dayofweek < DAY_1+7; dayofweek++)
        printf("%s\n", nl_langinfo(dayofweek));
    return 0;
}
