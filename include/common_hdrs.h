#ifndef COMMON_HDRS_H
#define COMMON_HDRS_H

#include "sys_hdrs.h"
#include "get_nums.h"
#include "error_exits.h"
#define STRING_MAX 1024
#define MAXLEN STRING_MAX

#ifdef FALSE
    #undef FALSE
#endif

#ifdef BOOL
    #undef BOOL
#endif
typedef enum {FALSE, TRUE} BOOL;

#define FORMAT "%c"
#define BAD_FORMAT_ERROR -1
#define TIME_ADJUST_ERROR -2
#define LOCALE_ERROR -3

#define READ_ERROR -4
#define MEM_ERROR -5

#endif
