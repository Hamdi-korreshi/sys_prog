#include <float.h>
#define _GNU_SOURCE
#include "common_hdrs.h"
// unsigned bit flags that are set and used to check
#define LDBL_POS_ONLY (1u <<3 )
#define LDBL_NO_EXP (1u << 2)

enum {
    GLD_OK           = 0,
    GLD_ERR_RANGE    = -1,  /* errno == ERANGE */
    GLD_ERR_NODIGITS = -2,  /* end == s */
    GLD_ERR_JUNK     = -3,  /* trailing junk not allowed */
    GLD_ERR_SPECIAL  = -4,  /* NaN or Inf rejected */
    GLD_ERR_SIGN     = -5,  /* violates NONNEG/POS/NEGZERO policy */
    GLD_ERR_FORMAT   = -6   /* violates NO_HEX/NO_EXP policy */
};

int get_longdbl(char *arg, int flags, long double *value, char *msg) {
    char *end = NULL;
    long double v;

    errno = 0;
    v = strtod(arg, &end);
    if (errno != 0) return GLD_ERR_RANGE; // overflow
    if (end == arg) return GLD_ERR_NODIGITS;     /* no digits */
    if (*end != '\0') return GLD_ERR_JUNK; // trailing crap
    if (v < LDBL_MIN || v > LDBL_MAX) return GLD_ERR_SPECIAL; // infinite or NaN
    if ((flags & LDBL_POS_ONLY) && v <= 0.0L) return GLD_ERR_SIGN; // positive only set
    if (flags & LDBL_NO_EXP) { // illegall such as e or hex
    for (const char *p = arg; p < end; ++p)
        if (*p == 'e' || *p == 'E')
            return GLD_ERR_FORMAT;
}
    *value = v;
    return GLD_OK;
}
