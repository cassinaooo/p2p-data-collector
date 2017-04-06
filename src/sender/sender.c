#include "sender.h"

#define PORT "35000" // the port to connect to
#define HOST "localhost" 
// no trailing slashes here, pls
#define BACKUP_FOLDER "/home/cassiano/redes/files/to_send"
#define SLICE_LEN 256000

void sendfiles(){
    int status;

    printf("CONNECTING TO HOST: %s ON PORT %s\n", HOST, PORT);
    fflush(stdout);    

    int sockfd = newsendsocket(PORT, HOST);

    char file_to_send[256];
    compress(BACKUP_FOLDER, file_to_send);

    char hostname[50];    
    gethostname(hostname, sizeof(hostname));

    int file_descriptor, remain_data;
        
    printf("reading file: %s\n", file_to_send);

    remain_data = getfd(file_to_send, &file_descriptor);

    if( remain_data < 0L ) {
        perror("File read failed\n");
        exit(1);
    }        

    printf("file was %d bytes long\n", remain_data);
    fflush(stdout);

    char file_basename[256];

    getbasename(file_to_send, file_basename);

    Header *h = newheader(hostname, file_basename, remain_data, 0);
    
    printf("ENVIANDO HEADER:\n");
    printheader(h);
    fflush(stdout);    

    int sent_bytes = send(sockfd, h, sizeof(Header), 0);
    free(h);

    if(sent_bytes < 0){
        fprintf(stderr, "send error on header: %s\n", strerror(sockfd));
        exit(1);
    } 

    off_t offset = 0;
    sent_bytes = 0;

    /* Sending file data */
    while (((sent_bytes = sendfile(sockfd, file_descriptor, &offset, BUFSIZ)) > 0) && (remain_data > 0)){
        fprintf(stdout, "1. Server sent %d bytes from file's data, offset is now : %ld and remaining data = %d\n", sent_bytes, (long int)offset, remain_data);
        remain_data -= sent_bytes;
        fprintf(stdout, "2. Server sent %d bytes from file's data, offset is now : %ld and remaining data = %d\n", sent_bytes, (long int)offset, remain_data);
        fflush(stdout);              
    }

    close(sockfd);
}
