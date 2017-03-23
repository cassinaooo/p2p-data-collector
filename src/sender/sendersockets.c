#include "sendersockets.h"

/* 
    returns a socket ready to make send calls
    to a specific port in a host
*/

int newsendsocket(char *port, char *host){
    int status;
    int sockfd;

    struct addrinfo hints;
    struct addrinfo *res;  // will point to the results

    memset(&hints, 0, sizeof hints); // make sure the struct is empty

    hints.ai_family = AF_UNSPEC;     // don't care IPv4 or IPv6
    hints.ai_socktype = SOCK_STREAM; // TCP stream sockets

    // port is the second argument of getaddrinfo, NULL defaults to the host IP address
    if ((status = getaddrinfo(host, port, &hints, &res)) != 0) {
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
        exit(1);
    }

    // res now points to a linked list of 1 or more struct addrinfos

    // ... do everything until you don't need res anymore ....

    sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

    if(sockfd < 0){
        // error checking
        fprintf(stderr, "getaddrinfo error: %s\n", strerror(sockfd));
        exit(1);        
    }

    // connect!
    

    if((status = connect(sockfd, res->ai_addr, res->ai_addrlen)) < 0){
        fprintf(stderr, "connect error: %s\n", strerror(sockfd));
        exit(1);    
    }

    freeaddrinfo(res); // free the linked-list

    return sockfd;
}

