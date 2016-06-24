#ifndef HTTPPARSER_H
#define HTTPPARSER_H

typedef struct HTTPreq {
    char *verb;
    char *path;

    char *ipaddr;

    int sockfd;

    int content_len;

} HTTPreq;

HTTPreq parse_request(char *req);

#endif
