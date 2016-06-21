#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

void get_server_addrinfo(char *port, struct addrinfo *info) {
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
}

int create_socket(struct addrinfo *info);

/*
 * Main server loop
 */
void serve(char *port) {
    // get local address info
    struct addrinfo *info;
    get_server_addrinfo(port, info);
    
    // create a socket

    // bind to socket
    
    // listen on socket

    // accept incoming connection

    // read from connection
}


