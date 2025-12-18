#ifndef GET_NUMS_H
#define GET_NUMS_H

#include "sys_hdrs.h"
#define NO_TRAILING 1
#define NON_NEG_ONLY 2
#define ONLY_DIGITS 4
#define POS_ONLY 8
#define PURE NO_TRAILING | ONLY_DIGITS

#define VALID_NUMBER 0
#define FATAL_ERROR -1
#define TRAILING_CHARS_FOUND -2
#define OUT_OF_RANGE -3
#define NO_DIGITS_FOUND -4
#define NEG_NUM_FOUND -5

/**
 * get_long()
 * On success, it returns VALID_NUMBER and stores the resulting number in *value; otherwise it returns
 * one of the nonzero error codes and puts a suitable message into *msg. Flags is used to decide whether
 * trailing chars, neg values, and zeros for strings without any digits are allowed or should be errors.
 * @param char*     arg     [IN] string to parse
 * @param int       flags   [IN] Flag specifying how to handle anomalies
 * @param long*     value   [OUT] Return long int
 * @param char*     msg     [OUT] If not empty, error messageS
 * @return int      VALID_NUMBER or a neg error code indicating the type of error
 */

int get_long(char *arg, int flags, long *value, char *msg);

int  get_int(char *arg, int flags, int *value, char *msg );

int  get_dbl(char *arg, int flags, double *value, char *msg );

void lltostr(long long int num, char* str, int width);

#endif
