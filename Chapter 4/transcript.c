#include "error_exits.h"
#include "get_nums.h"
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#define _GNU_SOURCE
#include "common_hdrs.h"
#ifndef BUFFER_SIZE
#define BUFFER_SIZE 4096
#endif
#define MESSAGE_SIZE 512
#define PERMISSIONS S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH // equals to rw-rw-r--
// compile with gcc -DBUFFER_SIZE=4096 spl_cpl.c -I ../include -L ../lib -lspl -o spl_cp1
// -DBUFFER_SIZE is used in conjection with the ifndef the -I and everything else are used for including libraries
int main(int argc, char* argv[]) {
    int source_fd; // source file descriptor 
    int target_fd; // target file desciptor and the one that will be written to
    int num_bytes_read; // ret val of the read()
    int num_bytes_written; // ret val of the write()
    mode_t permissions = PERMISSIONS; // assigning the permissions for the copied file
    char buffer[BUFFER_SIZE]; // for writing and transfering
    char message[MESSAGE_SIZE]; // error messaging string

    if (argc < 2) {
        sprintf(message, "%s <file>", basename(argv[0]));
        usage_error(message);
    }

    // opening file to read from
    errno = 0;
    source_fd = 
    // open target file for reading
    if (( target_fd = open(argv[2], O_WRONLY| O_CREAT | O_TRUNC, permissions)) == -1) {
        sprintf(message, "unable to open %s for reading", argv[2]);
        fatal_error(errno, message);
    }

    // transfer loop with BUFFER_SIZE bytes from source to target
    errno = 0;
    while((num_bytes_read = read(source_fd, buffer, BUFFER_SIZE)) > 0) {
        errno = 0;
        num_bytes_written = write(target_fd, buffer, num_bytes_read);
        printf(buffer, "%s");
        if (errno != 0)
            fatal_error(errno, "copy");
        else if ( num_bytes_written != num_bytes_read) {
            sprintf(message, "write error to %s \n", argv[2]);
            fatal_error(-1, message);
        }
    }

    if (num_bytes_read == -1)
        fatal_error(errno, "error reading");

    // closing files
    if (close(source_fd) == -1) {
        sprintf(message, "error closing source file %s", argv[1]);
        fatal_error(errno, message);
    }
    errno = 0;
    if (fsync(target_fd) == -1 && errno != EINVAL) //flush data to device, guarantees write to disk (non-volatile), einval is there for the /dev/tty test
        fatal_error(errno, "fsync");
     

    if (close(target_fd) == -1) {
        sprintf(message, "error closing source file %s", argv[2]);
        fatal_error(errno, message);
    }

    return 0;
}