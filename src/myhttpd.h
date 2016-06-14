// listenerthread.c functions
int server();

// selectorthread.c functions
int selectorthread(int numthread, bool sorttype); // sorttype: true for FCFS, false for SJF

// handlerthread.c functions
int handlerequest(char request[]);
