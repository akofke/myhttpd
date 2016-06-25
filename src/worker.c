/*
 * worker.c - defines worker functions which run in a thread and
 * wait in the thread pool until they are assigned a request.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define H_RESP "HTTP/1.0 200 ok\n"
#define H_DATE "Date: %s\n"
#define H_SERVER "Server: myhttpd\n"
#define H_LAST_MODIFIED "Last-Modified: %s\n"
#define H_CONTENT_TYPE "Content-Type: %s\n"
#define H_CONTENT_LEN "Content-Length: %d\n"

#define H_DATE_FMT "%d/%b/%Y:%T %Z"
#define DATESTR_BUF_SIZE 256

#define HEADER_LEN strlen(header_fmt) + strlen(timestamp_str) + strlen(lastmod_str) + strlen(conttype) + 1


const char *header_fmt = H_RESP H_DATE H_SERVER H_LAST_MODIFIED H_CONTENT_TYPE H_CONTENT_LEN;  

void serve_request(HTTPreq *req) {
    if(S_ISREG(req->stat->st_mode)) {
        serve_file(req);
    } else {
        /*
         * Directories not implemented yet
         */
    }

}

void serve_file(HTTPreq *req) {
    
    FILE *fp;
    if((fp = fopen(req->path, "r")) == NULL) {
        // should be error checking, but not essential
        // since the file was already found by stat()
    }

    struct tm *timestamp = malloc(sizeof struct tm);
    struct tm *lastmod = malloc(sizeof struct tm);
    gmtime_r(time(NULL), timestamp);
    gmtime_r((time_t)(req->file_stat->st_mtim->tv_sec), lastmod);
    char timestamp_str[DATESTR_BUF_SIZE];
    char lastmod_str[DATESTR_BUF_SIZE];
    strftime(timestamp_str, DATESTR_BUF_SIZE, H_DATE_FMT, timestamp);
    strftime(lastmod_str, DATESTR_BUF_SIZE, H_DATE_FMT, lastmod);

    char *conttype;
    if(strcmp("html", get_ext(req->path)) == 0) {
        conttype = "text/html";
    } else if(strcmp("gif", get_ext(req->path)) == 0) {
        conttype = "image/gif";
    } else {
        // TODO: deal with unsupported filetypes
        conttype = "";
    }

    char *headerbuf = malloc(HEADER_LEN);
    snprintf(headerbuf, HEADER_LEN, header_fmt, timestamp, lastmod, )

    char *fbuf = malloc(req->content_len);



}

const char *get_ext(const char *filename) {
    const char *dot = strrchar(filename, ".");
    if(!dot || dot == filename) {
        return "";
    }

    return &dot[1];
}
