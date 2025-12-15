#include "error_exits.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

noreturn void fatal_error(int errnum, const char *msg)
{
    fprintf(stderr, "fatal: %s: %s\n", msg, strerror(errnum));
    exit(EXIT_FAILURE);
}

noreturn void sys_error(const char *msg)
{
    fatal_error(errno, msg);
}

noreturn void usage_error(const char *msg)
{
    fprintf(stderr, "usage: %s\n", msg);
    exit(EXIT_FAILURE);
}
