#include "common_hdrs.h"
#include <pwd.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    uid_t userid;
    struct passwd *psswd_struct; // save pointer returned by getpwuid

    // to grab user name, we retrieve userID associated with process
    // which is the same of the user who run this cmd
    userid = getuid();

    psswd_struct = getpwuid(userid);

    // print out user id with the name in the same format as the id command
    printf("uid=%d(%s)\n", userid, psswd_struct->pw_name);
    return 0;
}