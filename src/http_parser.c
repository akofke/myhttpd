#include <stdio.h>
#include <regex.h>
#include <string.h>

#define REQ_VERB "(GET|HEAD)"
#define REQ_PATH "([a-zA-Z0-9/]+)"
#define REQ_VERSION "HTTP/.+"
#define REQ_REGEX REQ_VERB REQ_PATH REQ_VERSION

regex_t req_regex;
void setup_parser() {
    if(regcomp(&req_regex, REQ_REGEX, 0)) {
        fprintf("Error compiling parser regex\n");
        exit(1);
    }
}

void cleanup_parser() {
    regfree(req_regex);
}

HTTPReq parse_request(char *req) {
   char *req_firstline = strtok(req, "\n"); 

}
