#include <stdio.h>
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

HTTPreq parse_request(char *req) {
   char *req_firstline = strtok(req, "\n"); 

   HTTPreq http_req;

   // TODO: do this the proper way...
   http_req.verb = strtok(req_firstline, " ");
   http_req.path = expand_path(strtok(NULL, " "));
   //char *version = strtok(NULL, " ");

   return http_req;
}
