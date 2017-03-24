#include "receiver.h"

#define PORT "35000"  // the port users will be connecting to
#define BACKLOG 10     // how many pending connections queue will hold

void recvfile(){
    int status;
    int sockfd;

    sockfd = newlistensocket(PORT);
    
    status = listen(sockfd, BACKLOG);

    if(status < 0){
        fprintf(stderr, "listen error: %s\n", strerror(sockfd));
    }

    // socket to a new connection, blocks until a connection to PORT is made
    int new_fd = newrecvsocket(sockfd);

    Header *h = malloc(sizeof(Header));
    int msg_size = sizeof(Header);

    printf("aguardando mensagem de tamanho: %d\n", msg_size);

    status = recv(new_fd, h, msg_size, 0);

    if(status < 0){
        fprintf(stderr, "recv error: %s\n", strerror(new_fd));
    }

    printf ("HEADER RECEBIDO\n");

    printheader(h);

    if(status == 0){
        printf("%s\n", "connection closed");
        exit(0);
    }
}