#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
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
    if (argc  < 2) {
        usage_error("Usage: echo.out <filename>+\n");
    }


    for (int i = 1; i < argc; i++) {
        int fd;
        char file_buffer[BUFFER_SIZE];
        char echo[MAX_SIZE+1];
        const char *filename = argv[i];
        fd = open(filename, O_RDONLY);
        int keep = 0;
        if (fd == -1) {
            perror("open file went wrong");
            exit(EXIT_FAILURE);
        }
        ssize_t ret_val;
        while ((ret_val = read(fd, file_buffer, sizeof(file_buffer))) > 0 ) {
            if (ret_val + keep > MAX_SIZE) {
                fprintf(stderr, "File too large for echo buffer");
                close(fd);
                return 1;
            }
            for ( ssize_t j = 0; j < ret_val; j++) {
                echo[keep + j] = file_buffer[j];
            }
            keep += (int)ret_val;
        }
        echo[keep] = '\0';
        printf("%s", echo);
        close(fd);
    }
    return 0;
}