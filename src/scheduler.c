#include <semaphore.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include "scheduler.h"

struct node {
    struct request *request;
    struct node *next;
};

struct request {
    int len;
    int fd;
    char *req;
};

struct node *requestlist;
sem_t *sem_reqlist_access, *sem_noreq, *sem_nothread;

struct handler {
    pthread_t thread;
    sem_t *sem_thread;
    struct request *request;
    int available;
};

struct handler *threadarr;

int add_request(char *request, int length, int fdesc){ // request is the string of the HTML request, the length is the length of the request. length doesn't matter if using FCFS
    sem_wait(sem_reqlist_access);

    struct node *reqlist = requestlist;

    if (reqlist->next=NULL){
        reqlist->request->req=request;
        reqlist->request->len=length;
        reqlist->request->fd=fdesc;
    }
    else if (sjf){
        while (reqlist->next != NULL && length < reqlist->request->len)
            reqlist=reqlist->next;
        struct node *templist = reqlist->next;
        reqlist->next = malloc(sizeof(struct node));
        reqlist->next->request->req = request;
        reqlist->next->request->len = length;
        reqlist->request->fd = fdesc;
        reqlist->next->next = templist;
    }
    else {
        while (reqlist->next != NULL)
            reqlist = reqlist->next;
        struct node *templist = reqlist->next;
        reqlist->next = malloc(sizeof(struct node));
        reqlist->next->request->req = request;
        reqlist->next->request->len = length;
        reqlist->request->fd = fdesc;
        reqlist->next->next = templist;
    }

    sem_post(sem_noreq);
    sem_post(sem_reqlist_access);
    return 0; // No error
}

void* run_scheduler(void *arg){ //scheduling_criteria is 0 for FCFS, 1 for SJF, threadlimit is as passed into program

    // allocate memory for semaphores
    sem_reqlist_access = malloc(sizeof(sem_t));
    sem_noreq = malloc(sizeof(sem_t));
    sem_nothread = malloc(sizeof(sem_t));

    // initialize semaphores
    sem_init(sem_reqlist_access, 0, 1); 	// sem_reqlist_access is an intraproccess semaphore with initial value of 1
    sem_init(sem_noreq, 0, 0); 				// sem_noreq is an intraproccess semaphore with initial value of 0
    sem_init(sem_nothread, 0, threadlimit); // sem_nothread is an intraproccess semaphore with initial value equal to threadlimit

    // allocate memory for root of list
    requestlist = malloc(sizeof(struct node));
    requestlist->next = NULL;

    // allocate memory for handler threads
    threadarr = malloc(sizeof(struct handler)*threadlimit);

    // initalize and create handler threads
    for (int x = 0; x < threadlimit; x++){
        threadarr[x].available = 1;
        sem_init(threadarr[x].sem_thread, 0, 0);
        pthread_create(&(threadarr[x].thread), NULL, &handler_thread, &threadarr[x]);
    }

    while (1){
        sem_wait(sem_noreq);
        sem_wait(sem_nothread);
        use_request();
    }
}

int use_request(){
    sem_wait(sem_reqlist_access);
    struct node *reqlist = requestlist;
    struct request *requesttouse;

    if (reqlist->next==NULL){ //only root is occupied
        requesttouse=reqlist->request;
    }
    else {
        requesttouse=reqlist->request;
        requestlist = reqlist->next;

        free(reqlist);
    }

    sem_post(sem_reqlist_access);

    int i = 0;
    while (threadarr[i].available==0){
        i++;
    }
    threadarr[i].available = 0;
    threadarr[i].request=requesttouse;
    //int log_request(char *remote_ip, time_t enq_time, time_t assn_time, char *req, char *status, int resp_size);
    sem_post(threadarr[i].sem_thread);

    return 0;
}

void* handler_thread(void *arg){ //starting point for handler thread
    struct handler * handlerstatus = (struct handler *)arg;
    while (1){
        sem_wait(handlerstatus->sem_thread);
        //run_handler(handlerstatus->request->req, handlerstatus->request->len, handlerstatus->request->fd;);
        handlerstatus->available = 1;
        sem_post(sem_nothread);
    }
}
