#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <assert.h>
#include <string.h>

#include "logging.h"
#include "myhttpd.h"
#include "server.h"
#include "scheduler.h"

#define DEFAULT_PORT "8080"
#define DEFAULT_TIME_DELAY 60
#define DEFAULT_THREADNUM 4
#define DEFAULT_SCHED_POLICY FCFS

void usage(int is_err);

int main(int argc, char *argv[]) {

    myhttpd_opts opts;

    /*
     * Find the directory myhttpd was invoked in,
     * to set the default document root
     */
    if(getcwd(opts.doc_root, PATH_STRSIZE) == NULL) {
        perror("error getting current working directory");
        exit(1);
    }

    opts.debug_mode = 0;
    opts.q_time_delay = DEFAULT_TIME_DELAY;
    opts.numthreads = DEFAULT_THREADNUM;
    opts.policy = DEFAULT_SCHED_POLICY;

    strcpy(opts.myhttpd_port, DEFAULT_PORT);
    printf("%s\n", opts.doc_root);

    int c;
    while((c = getopt(argc, argv, "dhl:p:r:t:n:s:")) != -1) {
        switch(c) {
            case 'd':
                // debugging mode
                opts.debug_mode = 1;
                break;
            case 'h':
                // help, usage
                usage(0);
                break;
            case 'l':
                // logging

                // we don't want buffer overflow
                assert(strlen(optarg) < PATH_STRSIZE);
                strcpy(opts.logfile_path, optarg);
                break;
            case 'p':
                // port

                assert(strlen(optarg) < MAX_PORT_LEN);
                strcpy(opts.myhttpd_port, optarg);
                break;
            case 'r':
                // root directory

                assert(strlen(optarg) < PATH_STRSIZE);
                strcpy(opts.doc_root, optarg);
                break;
            case 't':
                // queuing time
                /* TODO: atoi cannot detect errors so this isn't the
                 * best solution. If I have time I'll convert this to strtol
                 */

                opts.q_time_delay = atoi(optarg);
                break;
            case 'n':
                // number of worker threads

                opts.numthreads = atoi(optarg);
                break;
            case 's':
                // scheduling policy

                if(strcmp(optarg, "FCFS") == 0) { opts.policy = FCFS; }
                else if (strcmp(optarg, "SJF") == 0) {opts.policy = SJF; }
                else {
                    fprintf(stderr, "Invalid scheduling policy\n\n");
                    usage(1);
                }
                break;
            case '?':
                // handle bad options
                usage(1);
                break;
            default:
                // something went very wrong if we are here
                fprintf(stderr, "error getting command line opts");
                abort();

        }

    }

    if (!opts.debug_mode) {
        /*
         * Daemonize the process using daemon() standard library call
         * TODO: only fork if -d option is not set
         */
        if(daemon(0,0) < 0) {
            fprintf(stderr, "error forking daemon process");
            exit(1);
        }

        sleep(20);

    }
    
    if (strcmp(opts.policy, "FCFS") == 0)
        sjf = 0;
    else
        sjf = 1;
    threadlimit = opts.numthreads;
    pthread_t schedulerthread;
    pthread_create(&schedulerthread, NULL, &run_scheduler, NULL);
    
    setup_server(opts.myhttpd_port);

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
