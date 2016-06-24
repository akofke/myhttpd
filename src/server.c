#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <signal.h>

#define BACKLOG 20
#define BUF_SIZE 1024
#define RECV_FLAGS 0

void serve_connections(int sockfd);
int sockfd;

void cleanup(int signal) {
    close(sockfd);
    exit(130);
}

/*
 * Setup server to accept connections
 */
void setup_server(const char *port) {
    struct addrinfo *info;
    //get_server_addrinfo(port, info); 
    struct addrinfo hints;
    int status;

    // ensure hints struct is empty
    memset(&hints, 0, sizeof hints);

    /*
     * Suggest to getaddrinfo() that we don't care about IPv4 or IPv6,
     * we want to use stream sockets, and we don't want to set a different
     * IP address
     */
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    if((status = getaddrinfo(NULL, port, &hints, &info)) != 0) {
        fprintf(stderr, "Error getting server addrinfo: %s", gai_strerror(status));
        exit(1);
    }

    /* create a socket.
     * socket() call takes the domain (PF_INET), the socket type (SOCK_STREAM),
     * and the protocol (redundant; PF_INET or 0)
     */
    if((sockfd = socket(info->ai_family, info->ai_socktype, info->ai_protocol)) < 0) {
        perror("error getting socket file descriptor");
        exit(1);
    }

    // bind to socket
    if(bind(sockfd, info->ai_addr, info->ai_addrlen) == -1) {
        perror("error binding to socket");
        exit(1);
    }

    int yes = 1;
    if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof yes) == -1) {
        perror("error setting socket option");
        exit(1);
    }

    freeaddrinfo(info);
    signal(SIGINT, cleanup);
    serve_connections(sockfd);

}

/*
 * Main server loop
 */
void serve_connections(int sockfd) {

    while(1) {
        // listen on socket
        if(listen(sockfd, BACKLOG) == -1) {
            perror("error listening on socket");
            exit(1);
        }

        // accept incoming connection
        struct sockaddr_in remote_addr;
        socklen_t addr_size = sizeof remote_addr;
        char remote_ip_str[INET6_ADDRSTRLEN];
        int accepted_fd;
        if((accepted_fd = accept(sockfd, (struct sockaddr *)&remote_addr, &addr_size)) == -1) {
            perror("error accepting connection");
            exit(1);
        }

        if(inet_ntop(remote_addr.sin_family, &(remote_addr.sin_addr), remote_ip_str, sizeof remote_ip_str) == NULL) {
            perror("error converting ipaddr to string");
            exit(1);
        }

        printf("Accepted connection from %s\n", remote_ip_str);


        // read from connection
        char recv_buf[BUF_SIZE];
        memset(recv_buf, 0, BUF_SIZE);
        int recv_retval;
        if((recv_retval = recv(accepted_fd, recv_buf, BUF_SIZE, RECV_FLAGS)) == -1) {
            perror("error while recieving from client");
            exit(1);
        } else if(recv_retval == 0) {
            // TODO: probably want to implement some other behavior here
            fprintf(stderr, "client has closed the connection");
            continue;
        }


        // debug
        printf("%s\n", recv_buf);
        close(accepted_fd);

        char *req = strdup(recv_buf);

        char *line;
        printf("%s\n", strsep(&req, "\n"));
        /* while((line = strsep(&req, "\n") != NULL)) { */
        /*     printf("%s\n", line); */
        /* } */

        // add_request(recv_buf, 0 /*whatever method louis uses to get the length of a request, call it here instead*/, accepted_fd);
    }

}

void parse_request(char *req) {
    char *req_firstline = strtok(req, "\n");

}

int get_content_len();

