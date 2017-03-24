#include "sender.h"

#define PORT "35000" // the port to connect to
#define HOST "localhost" 

void sendfile(){
    int status;
    int sockfd = newsendsocket(PORT, HOST);

    int len, bytes_sent;

    Header *h = newheader("192.168.1.1", "192.168.1.2", "file.txt", 10, 1024);

    printf("ENVIANDO HEADER:\n");
    printheader(h);

    len = sizeof(Header);

    printf ("mensagem de tamanho: %d\n", len);

    bytes_sent = send(sockfd, h, len, 0);

    if(bytes_sent < 0){
        fprintf(stderr, "send error: %s\n", strerror(status));
        exit(1);
    }
}