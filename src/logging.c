#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define LOG_FMT "%s [%s] [%s] \"%s\" %s %d\n"
#define DATE_FMT "%d/%b/%Y:%T %z"
#define DATESTR_BUF_SIZE 256

FILE *log_file = NULL;

// ugly way of doing this
int log_to_stdout = 0;

/*
 * Open the log file and keep the open file pointer, since we will be making many logging calls.
 * The main function must open the logging file at server startup, and close it when the server exits.
 * Note the file may be
 */
int open_logging(const char *filename){
    if((log_file = fopen(filename, "w")) == NULL) {
        perror("error opening log file");
        return -1;
    }

    return 0;
}

int close_logging(){
    if(fclose(log_file) != 0){
        // something went really wrong or the calls were made in the wrong order
        abort();
    }

    return 0;
}

void log_request(char * remote_ip, time_t enq_time, time_t assn_time, char *req, char *status, int resp_size){

    struct tm *enq_gmtime = malloc(sizeof struct tm);
    struct tm *assn_gmtime = malloc(sizeof struct tm);
    gmtime_r(enq_time, enq_gmtime);
    gmtime_r(enq_time, enq_gmtime);
    char enq_time_str[DATESTR_BUF_SIZE];
    char assn_time_str[DATESTR_BUF_SIZE];

    if(strftime(enq_time_str, DATESTR_BUF_SIZE, DATE_FMT, enq_gmtime) == 0){
        fprintf(stderr, "Date str buffer was too small\n");
        abort();
    }
    
    if(strftime(assn_time_str, DATESTR_BUF_SIZE, DATE_FMT, assn_gmtime) == 0){
        fprintf(stderr, "Date str buffer was too small\n");
        abort();
    }

    if(log_file != NULL){
        fprintf(log_file, LOG_FMT, remote_ip, enq_time_str, assn_time_str, req, status, resp_size);
    }

    if(log_to_stdout) {
        fprintf(stdout, LOG_FMT, remote_ip, enq_time_str, assn_time_str, req, status, resp_size);
    }

    free(enq_gmtime);
    free(assn_gmtime);


}
