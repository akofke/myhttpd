#define USE_STDOUT log_to_stdout = 1

int log_to_stdout;

int open_logging(const char *filename);
int close_logging();
int log_request(char *remote_ip, time_t enq_time, time_t assn_time, char *req, char *status, int resp_size);
