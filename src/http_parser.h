#ifndef HTTPPARSER_H
#define HTTPPARSER_H

typedef enum {GET, HEAD, NOT_SUPPORTED} http_verb;

typedef struct HTTPreq {
    http_verb verb;
    char *path;
    char *firstline;

    char *ipaddr;
    int connfd;

    unsigned int content_len;
    struct stat *file_stat;

    int error;

} HTTPreq;

HTTPreq *parse_request(char *req);

#endif
