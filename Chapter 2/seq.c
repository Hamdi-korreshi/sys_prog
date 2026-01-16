#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
void error_check(char *endptr, char *check) {
    if ( errno != 0) {
        perror("strtol");
        exit(EXIT_FAILURE);
    }
    if ( endptr == check) {
        fprintf(stderr, "No digits were found\n");
        exit(EXIT_FAILURE);
    }
    if ( *endptr != "\0" )
        printf("characters following the number: \"%s\"\n", endptr);
}

int main( int argc, char *argv[]) {
    if ( argc < 3 || argc > 4) {
        printf("usage ./seq num1 num2\n");
        exit(EXIT_FAILURE);
    }
    char *endptr;
    errno = 0;
    int num1 = strtol(argv[1], &endptr, 0);
    error_check(endptr, argv[1]);
    errno = 0;
    int num2 = strtol(argv[2], &endptr, 0);
    printf("Num1: %d, num2: %d\n", num1, num2);
    if (num1 >= num2) {
        fprintf(stderr, "Num1 needs to be bigger then num2\n");
        exit(EXIT_FAILURE);
    }
    for(int i= num1; i <= num2; i++) {
        printf("%d ",i);
    }
    printf("\n");
    return 0;
}