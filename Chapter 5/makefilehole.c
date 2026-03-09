#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define MESSAGE_SIZE 512
#define BUFFER_SIZE 10

int main(int argc, char *argv[]) {
    int fd;
    char buffer[BUFFER_SIZE];
    char message[MESSAGE_SIZE];
    
    if ( argc < 3) {
        sprintf(message, " %s <file-to-create>\n", basename(argv[0]));
        usage_error(message);
    }

    if (( fd = open(argv[1], O_WRONLY | O_CREAT | O_EXCL, 0644)) < 0)
        fatal_error(errno, "open");
        // copy string to buffer
        strncpy(buffer, "0123456789", BUFFER_SIZE);
        // write the number sequence at the start of the file
        if ( write(fd, buffer, BUFFER_SIZE) != BUFFER_SIZE) {
            fatal_error(errno, "write");
        }
        if ( lseek(fd, 1000000, SEEK_END) == -1) {
            fatal_error(errno, "lseek");
        }
        // write at the new end of the file
        if ( write(fd, buffer, BUFFER_SIZE) != BUFFER_SIZE) {
            fatal_error(errno, "write");
        }
        if ( close(fd) == -1)
            fatal_error(errno, "close");
        exit(EXIT_SUCCESS);
}