/*
 * worker.c - defines worker functions which run in a thread and
 * wait in the thread pool until they are assigned a request.
 */

#include <stdio.h>
#include <stdlib.h>

#define H_RESP "HTTP/1.0 200 ok\n"
#define H_DATE "Date: %s\n"
#define H_SERVER "Server: myhttpd\n"
#define H_LAST_MODIFIED "Last-Modified: %s\n"
#define H_CONTENT_TYPE "Content-Type: %s\n"
#define H_CONTENT_LEN "Content-Length: %d\n"

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

    char *fbuf = malloc(req->content_len);



}
