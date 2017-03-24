#include "sender.h"

#define PORT "35000" // the port to connect to
#define HOST "localhost" 

void sendfile(){
    int status;
    int sockfd = newsendsocket(PORT, HOST);

    char *msg = "ESSA EH A MENSAGEM";
    int len, bytes_sent;

    len = strlen(msg);

    printf ("mensagem de tamanho: %d\n", len);
    printf("mensagem em char: %s\n", msg);

    for(int i = 0; i < len; i++){
        printf("%x", msg[i]);
    }
    
    printf("\n");
    

    bytes_sent = send(sockfd, msg, len, 0);

    if(bytes_sent < 0){
        fprintf(stderr, "send error: %s\n", strerror(status));
        exit(1);
    }
}