#include <errno.h>
#include <locale.h>
#include <stdio.h>
#define _GNU_SOURCE
#define _XOPEN_SOURCE 500
#include "common_hdrs.h"
#include <pwd.h>

int main(int argc, char *argv[]) {
    struct passwd *psswd_struct;

    // set the locale time define by the env
    if (NULL == setlocale(LC_TIME, ""))
        fatal_error(LOCALE_ERROR, "setlocale() could not set the give locale");
    setpwent(); // init the iter for the password db
    errno = 0;
    while ( (psswd_struct = getpwent()) != NULL) {
        // print the pw_name member of the struct
        printf("%s\n", psswd_struct->pw_name);
        errno = 0;
    }

    if (errno != 0 && errno != ENOENT) {
        fatal_error(errno, "getpwent");
    }

    endpwent(); // close db pointer
    return 0;
}