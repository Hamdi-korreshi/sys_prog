#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <math.h>
#include "common_hdrs.h"

char *remove_hex(char *hex, int length) {
    char *check = index(hex, 'x'); 
    if ( check != NULL && (length > 2) && (check[1] != 'x')) {
        return check+1;
    }
    else return hex;
}

int power(int num, int exp) {
    return num * pow(16, exp);
}

int main(int argc, char* argv[]) {
    if ( argc < 2 ) {
        fprintf(stderr, "Usage: %s [hex num]+ \n", argv[0]);
        exit(EXIT_FAILURE);
    }
    for (int i = 1; i < argc; i++) {
        char *pruned = remove_hex(argv[i], strlen(argv[i]));
        int length = strlen(pruned);
        char *buck = pruned;
        int not_allowed_flag = 0;
        int converted = 0;
        int k =0;
        while ( k < length) {
            switch(buck[k]) {
                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                    converted+= power(buck[k]-'0', length-k-1);
                    break;
                case 'a':
                    converted+= power(10, length-k-1);
                    break;
                case 'b':
                    converted+= power(11, length-k-1);
                    break;
                case 'c':
                    converted+= power(12, length-k-1);
                    break;
                case 'd':
                    converted+= power(13, length-k-1);
                    break;
                case 'e':
                    converted+= power(14, length-k-1);
                    break;
                case 'f':
                    converted+= power(15, length-k-1);
                    break;
                default:
                    not_allowed_flag = 1;
                    break;
            }
            if (not_allowed_flag) {
                break;
            }
            else k++;
        }
        if (not_allowed_flag)
            printf("%s: not a valid number\n", pruned);
        else
            printf("%s = %d\n", pruned, converted);
    }
    return 0;
}