#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    printf("I am a thread with thread ID %d \n", gettid());
}
