#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#define _GNU_SOURCE
#include <unistd.h>
#include "common_hdrs.h"
#define BUFFER_SIZE 100
#define MAX_SIZE 10000

int copy(char *buf, char *src, int start) {
    for(int i = start; i < start + 100; i++) {
        buf[i] = src[i];
    }
    return 0;
}

int main(int argc, char* argv[]) {
    BOOL done = FALSE;
    if (argc != 2) {
        usage_error("Usage: echo.out <filename>\n");
    }

    const char *filename = argv[1];
    int fd;
    char file_buffer[BUFFER_SIZE];
    char echo[MAX_SIZE];

    fd = open(filename, O_RDONLY);
    int keep = 0;
    if (fd == -1) {
        perror(errno);
    }
    int ret_val;
    while ( !done ) {
        ret_val = read(fd, file_buffer, 100);
        copy(echo, file_buffer, keep);
        keep+=100;
        if (ret_val == 0)
            done = TRUE;
        if (keep > MAX_SIZE)
            return -1;
    }
    printf("%s", echo);
    return 0;
}