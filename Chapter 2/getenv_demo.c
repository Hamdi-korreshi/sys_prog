#include <stdio.h>
#include <stdlib.h>

int main() {
    char *path_to_home = getenv("HOME");
    if (NULL == path_to_home) 
        printf("The home var is not in the env\n");
    else
        printf("HOME=%s\n", path_to_home);
    return 0;
}
