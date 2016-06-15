#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    int c;
    while((c = getopt(argc, argv, "dhl:r:t:n:s:")) != -1) {
        switch(c) {
            case 'd':
                // debugging mode
                break;
            case 'h':
                // help, usage
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
                break;
            default:
                // something went very wrong if we are here
                abort();

        }

    }
}
