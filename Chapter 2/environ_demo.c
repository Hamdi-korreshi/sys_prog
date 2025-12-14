#include <stdlib.h>
#include <stdio.h>

extern **environ;

int main() {
    char **envp = environ;
    while (NULL != *envp) {
        printf("%s\n", *envp);
        envp++;
    }
    return 0;
}