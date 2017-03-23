#include <string.h>

#include "sendersockets.h"

#define PORT "35000" // the port to connect to
#define HOST "localhost" 

int main(){
    int status;
    int sockfd = newsendsocket(PORT, HOST);

    char *msg = "ESSA EH A MENSAGEM";
    int len, bytes_sent;

    len = strlen(msg);
    bytes_sent = send(sockfd, msg, len, 0);

    if(bytes_sent < 0){
        fprintf(stderr, "send error: %s\n", strerror(status));
        exit(1);
    }

    return 0;
}