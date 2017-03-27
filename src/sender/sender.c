#include "sender.h"

#define PORT "35000" // the port to connect to
#define HOST "localhost" 

void sendfile(){
    int status;

    printf("CONNECTING TO HOST: %s ON PORT %s\n", HOST, PORT);

    int sockfd = newsendsocket(PORT, HOST);

    int len, bytes_sent;

    char original_folder_path[256];

    strcpy(original_folder_path, "/home/labvcr2/cassiano/networks/files/to_send");

    Header *h = newheader("192.168.1.1", "192.168.1.2", "file.txt", 10, 1024);

    printf("ENVIANDO HEADER:\n");
    printheader(h);

    len = sizeof(Header);

    bytes_sent = send(sockfd, h, len, 0);

    free(h);

    if(bytes_sent < 0){
        fprintf(stderr, "send error: %s\n", strerror(sockfd));
        exit(1);
    }



}