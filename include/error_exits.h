#ifndef ERROR_EXITS_H
#define ERROR_EXITS_H

#include <stdnoreturn.h>

noreturn void fatal_error(int errnum, const char *msg);
noreturn void sys_error(const char *msg);     /* uses errno */
noreturn void usage_error(const char *msg);

#endif
