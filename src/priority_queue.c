/*
 * Naive implementation of a priority queue using a linked list.
 * Eventually change to heap.
 */

#include <stdlib.h>
#include <stdio.h>

#include "priority_queue.h"
#include "http_parser.h"

#define PRIORITY_COND \
    ((options.policy == SJF) && (ptr->next>content_len < req->content_len)) 


/*
 * add error chcecking, return int
 */
void add_request(HTTPreq *req) {
    sem_wait(sem_reqlist_access);

    struct q_node *ptr = req_queue;

    if(ptr == NULL) {
        // list is empty

        req_queue = malloc(sizeof struct q_node);
        req_queue->req = req;
        req_queue->next = NULL;
    } else {
        while(ptr->next != NULL && PRIORITY_COND) {
            ptr = ptr->next;
        }

        /*
         * now ptr points to the last node or the last node with
         * priority higher (content length smaller) than req
         */

        struct q_node *newnode = malloc(sizeof struct q_node);
        newnode->req = req;

        newnode->next = ptr->next;
        ptr->next = newnode;
    }

    sem_post(sem_reqlist_access);
}

HTTPreq *remove_request() {
    sem_wait(sem_reqlist_access);

    struct q_node *first = req_queue;
    req_queue = first->next;
    HTTPreq r = req;

    free(first);
    sem_post(sem_reqlist_access);

    return r;

    
}
