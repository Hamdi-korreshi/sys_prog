#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    char *forwardslashptr;
    char *suffixptr = NULL;

    forwardslashptr = strrchr(argv[0], '/');
    if ( forwardslashptr != NULL)
        suffixptr = forwardslashptr +1;
    else
        suffixptr = argv[0];
    if (*suffixptr == '\0') 
        fprintf(stderr, "Prog name ends in a / charater \n");
    else
        printf("Prog name is %s\n", suffixptr);
    return 0;
}