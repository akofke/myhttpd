
int add_request(char *request, int length);
void* run_scheduler(void *arg);
int use_request();
void* handler_thread(void *arg);

int threadlimit;
int sjf;