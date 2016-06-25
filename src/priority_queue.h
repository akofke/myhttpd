#ifndef PQ_H
#define PQ_H

#include <semaphore.h>

#include "http_parser.h"

struct q_node {
    HTTPreq *req;
    struct q_node *next;
}

struct q_node *req_queue;

void add_request(HTTPreq *req);
HTTPreq *remove_request();

#endif
