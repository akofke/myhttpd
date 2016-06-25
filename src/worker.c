/*
 * worker.c - defines worker functions which run in a thread and
 * wait in the thread pool until they are assigned a request.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "myhttpd.h"

#define H_RESP "HTTP/1.0 200 ok\n"
#define H_DATE "Date: %s\n"
#define H_SERVER "Server: myhttpd\n"
#define H_LAST_MODIFIED "Last-Modified: %s\n"
#define H_CONTENT_TYPE "Content-Type: %s\n"
#define H_CONTENT_LEN "Content-Length: %d\n"

#define H_DATE_FMT "%d/%b/%Y:%T %Z"
#define DATESTR_BUF_SIZE 256
#define MAX_HEADER_LEN 1024

const char *header_fmt = H_RESP H_DATE H_SERVER H_LAST_MODIFIED H_CONTENT_TYPE H_CONTENT_LEN "\n";  

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

    char *headerbuf[MAX_HEADER_LEN];
    int headersize;
    // headersize is number of chars written to header buf, not including null byte
    headersize = snprintf(headerbuf, MAX_HEADER_LEN, header_fmt, timestamp, lastmod, conttype, req->content_len);

    int resp_len = headersize + req->content_len;
    char *fbuf = malloc(resp_len);

    /*
     * header_end points to the terminating null byte of the header string
     * in the buffer
     */
    char *header_end = stpcpy(fbuf, headerbuf);

    /*
     * read the file into the response buffer, starting
     * (and overwriting) at the terminating null character
     * of the header
     */
    fread(header_end, req->content_len, 1, fp);

    int bytes_sent;
       
    while(resp_len > 0) {
        bytes_sent = send(req->sockfd, fbuf, resp_len, 0);
        if(bytes_sent < 0) {
            // handle errors...
        }

        fbuf += bytes_sent;
        resp_len -= bytes_sent;
    }

    free(fbuf);
    free(timestamp);
    free(lastmod);
    close(sockfd);
    close(fd);
    free_req(req);
}

const char *get_ext(const char *filename) {
    const char *dot = strrchar(filename, ".");
    if(!dot || dot == filename) {
        return "";
    }

    return &dot[1];
}
