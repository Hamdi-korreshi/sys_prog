#include <unistd.h>
#include <stdio.h>
#include <errno.h>

int main() {
    char name[256];
    size_t len = 150;
    int ret_val;

    ret_val = gethostname(name, len);
    if (-1 == ret_val) {
        switch (errno)
        {
        case EFAULT:
            printf("A bad address was passed for the string name\n");
            break;
        case EINVAL:
            printf("The length arg was negative\n");
            break;
        case ENAMETOOLONG:
            printf("The hostname is too long for the alloced array\n");
        default:
            break;
        }
    }
    else {
        printf("%s\n", name);
    }
}