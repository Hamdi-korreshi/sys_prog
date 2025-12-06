#include <stdio.h>
#include <stdlib.h>

int main() {
    char *shell = getenv("SHELL");
    printf("The current env is %s \n", shell);
    return 0;
}
