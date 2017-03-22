#include <stdlib.h>
#include <stdio.h>
#include <string.h> /* memset */

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#define PORT "9999"  // the port users will be connecting to
#define BACKLOG 10     // how many pending connections queue will hold

int main(){
    int status;
    int sockfd;
    struct addrinfo hints;
    struct addrinfo *res;  // will point to the results

    memset(&hints, 0, sizeof hints); // make sure the struct is empty

    hints.ai_family = AF_UNSPEC;     // don't care IPv4 or IPv6
    hints.ai_socktype = SOCK_STREAM; // TCP stream sockets
    hints.ai_flags = AI_PASSIVE;     // fill in my IP for me

    // port is the second argument of getaddrinfo, NULL defaults to the host IP address
    if ((status = getaddrinfo(NULL, PORT, &hints, &res)) != 0) {
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
        exit(1);
    }

    // res now points to a linked list of 1 or more struct addrinfos

    // ... do everything until you don't need res anymore ....

    sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

    if(sockfd == -1){
        // error checking
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(sockfd));
        exit(1);        
    }
    
    // bind it to the port we passed in to getaddrinfo():
    bind(sockfd, res->ai_addr, res->ai_addrlen);

    status = listen(sockfd, BACKLOG);

    if(status == -1){
        fprintf(stderr, "listen error: %s\n", gai_strerror(status));
    }

    struct sockaddr_storage their_addr;
    socklen_t addr_size;
    int new_fd;

    addr_size = sizeof their_addr;
    new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &addr_size);

    if(new_fd == -1){
        fprintf(stderr, "accept error: %s\n", gai_strerror(new_fd));
        exit(1);
    }

    char msg[200];
    int msg_size = sizeof msg;

    status = recv(new_fd, &msg, msg_size, 0);

    if(status == -1){
        fprintf(stderr, "recv error: %s\n", gai_strerror(status));
        exit(1);
    }

    printf("mensagem recebida: %s\n", msg);

    if(status == 0){
        printf("%s\n", "connection closed");
        exit(0);
    }

    freeaddrinfo(res); // free the linked-list

    return 0;
}