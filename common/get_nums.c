#include "get_nums.h"
#include <errno.h>
#include <limits.h>
#include <stdlib.h>

int get_int(const char *s, int flags, int *out, const char **endp)
{
    char *end = NULL;
    long v;

    errno = 0;
    v = strtol(s, &end, 10);
    if (errno != 0) return -1;
    if (end == s)  return -2;          /* no digits */
    if ((flags & PURE) && *end != '\0') return -3;
    if (v < INT_MIN || v > INT_MAX) return -4;
    if ((flags & NON_NEG_ONLY) && v < 0) return -5;

    *out = (int)v;
    if (endp) *endp = end;
    return 0;
}
