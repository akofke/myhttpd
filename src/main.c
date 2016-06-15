#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

void usage(int is_err);

int main(int argc, char *argv[]) {
    int c;
    while((c = getopt(argc, argv, "dhl:r:t:n:s:")) != -1) {
        switch(c) {
            case 'd':
                // debugging mode
                break;
            case 'h':
                // help, usage
                usage(0);
                break;
            case 'l':
                // logging
                break;
            case 'p':
                // port
                break;
            case 'r':
                // root directory
                break;
            case 't':
                // queuing time
                break;
            case 'n':
                // number of worker threads
                break;
            case 's':
                // scheduling policy
                break;
            case '?':
                // handle bad options
                usage(1);
                break;
            default:
                // something went very wrong if we are here
                abort();

        }

    }
}

void usage(int is_err) {
    /* prints usage and help. Prints to stdout or stderr depending on if its invoked
     * as an error or from -h.
     * TODO: add more help
     */
    char *msg = "Usage: myhttpd "
        "[-d] [-h] [-l file] [-p port] [-r dir] [-t time] [-n threadnum] [-s sched]"; 

    fprintf((is_err) ? stderr : stdout, "%s\n", msg);
    exit(is_err);
}
