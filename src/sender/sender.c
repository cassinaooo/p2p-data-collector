#include "sender.h"

#define PORT "35000" // the port to connect to
#define HOST "localhost" 
// no trailing slashes here, pls
#define BACKUP_FOLDER "/home/cassiano/redes/files/to_send"
#define SLICE_LEN 256000

void sendfile(){
    int status;

    printf("CONNECTING TO HOST: %s ON PORT %s\n", HOST, PORT);
    fflush(stdout);    

    int sockfd = newsendsocket(PORT, HOST);

    char file_to_send[256];
    compress(BACKUP_FOLDER, file_to_send);

    char hostname[50];    
    gethostname(hostname, sizeof(hostname));

    char *buf;
    int file_size;
        
    file_size = slurp(file_to_send, &buf, false);

    Header *h = newheader(hostname, BACKUP_FOLDER, file_size, 0);
    
    printf("ENVIANDO HEADER:\n");
    printheader(h);
    fflush(stdout);    

    int bytes_sent;
    bytes_sent = send(sockfd, h, sizeof(Header), 0);
    free(h);    

    if(bytes_sent < 0){
        fprintf(stderr, "send error on header: %s\n", strerror(sockfd));
        exit(1);
    }  
    
    printf("reading file: %s\n", file_to_send);
    fflush(stdout); 

    printf("file was %d bytes long\n", file_size);
    fflush(stdout);
    
    if( file_size < 0L ) {
        perror("File read failed\n");
        exit(1);
    }

    printf("sending file...\n");
    fflush(stdout);

    bytes_sent = send(sockfd, buf, file_size, 0);
    free(buf);    
    
    if(bytes_sent < 0){
        fprintf(stderr, "send error on data: %s\n", strerror(sockfd));
        exit(1);
    }   

    close(sockfd);
}
