#include <stdlib.h>
#include <stdio.h>
#include <string.h> /* memset */

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>


int main(){
    int status;
    int sock;
    struct addrinfo hints;
    struct addrinfo *res;  // will point to the results

    memset(&hints, 0, sizeof hints); // make sure the struct is empty

    hints.ai_family = AF_UNSPEC;     // don't care IPv4 or IPv6
    hints.ai_socktype = SOCK_STREAM; // TCP stream sockets
    hints.ai_flags = AI_PASSIVE;     // fill in my IP for me

    // port is the second argument of getaddrinfo, NULL defaults to the host IP address
    if ((status = getaddrinfo(NULL, "9999", &hints, &res)) != 0) {
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
        exit(1);
    }

    // res now points to a linked list of 1 or more struct addrinfos

    // ... do everything until you don't need res anymore ....

    sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

    if(sock == -1){
        // error checking
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(sock));
        exit(1);        
    }
    
    // bind it to the port we passed in to getaddrinfo():
    bind(sock, res->ai_addr, res->ai_addrlen);

    freeaddrinfo(res); // free the linked-list

    return 0;
}