#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

#include "http_parser.h"
#include "files.h"

/* #define REQ_VERB "(GET|HEAD)" */
/* #define REQ_PATH "([a-zA-Z0-9/]+)" */
/* #define REQ_VERSION "HTTP/.+" */
/* #define REQ_REGEX REQ_VERB REQ_PATH REQ_VERSION */
/*  */
/* regex_t req_regex; */
/* void setup_parser() { */
/*     if(regcomp(&req_regex, REQ_REGEX, 0)) { */
/*         fprintf("Error compiling parser regex\n"); */
/*         exit(1); */
/*     } */
/* } */
/*  */
/* void cleanup_parser() { */
/*     regfree(req_regex); */
/* } */

HTTPreq *parse_request(char *req) {

    /*
     * Allocate the request struct. The pointer to this
     * will be passed around and must eventually be freed
     * by the worker thread
     */
    HTTPreq *http_req = malloc(sizeof (HTTPreq));


    char *req_firstline = strtok(req, "\n"); 
    http_req->firstline = strdup(req_firstline);


    // TODO: do this the proper way...
    char *v = strtok(req_firstline, " ");
    if(strcmp(v, "GET") == 0) {
        http_req->verb = GET; 
    } else if(strcmp(v, "HEAD") == 0) {
        http_req->verb = HEAD;
    } else {
        http_req->verb = NOT_SUPPORTED;
        http_req->error = 1;
    }
    http_req->path = expand_path(strtok(NULL, " "));
    //char *version = strtok(NULL, " ");

    return http_req;
}

void free_req(HTTPreq *req) {
    free(req->path);
    free(req->firstline);
    free(req->ipaddr);
    free(req->file_stat);
    free(req);
}
