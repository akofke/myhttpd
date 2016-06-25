#ifndef HTTPPARSER_H
#define HTTPPARSER_H

typedef struct HTTPreq {
    char *verb;
    char *path;
    char *firstline;

    char *ipaddr;
    int connfd;

    struct stat *file_stat;

} HTTPreq;

HTTPreq *parse_request(char *req);

#endif
