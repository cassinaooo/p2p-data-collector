#include "receiver.h"

#define PORT "35000"  // the port users will be connecting to
#define BACKLOG 10     // how many pending connections queue will hold
#define ROOT_DIR "/home/cassiano/redes/files/received"

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

    Header *header = malloc(sizeof(Header));

    printf("AWAITING CONNECTIONS ON PORT %s\n", PORT);

    status = recv(new_fd, header, sizeof(Header), 0);

    if(status < 0){
        fprintf(stderr, "header recv error: %s\n", strerror(new_fd));
    }

    printf ("HEADER RECEBIDO\n");

    printheader(header);

    char destination[256];

    makefolder(header->c_name, ROOT_DIR, destination);

    printf("folder to save: %s\n", destination);
    fflush(stdout);

    Slice *s = malloc(sizeof(Slice));

    int bytesread;
    char filename[256];

    for(int msg = 0; msg < header->numberofslices; msg++){
        bytesread = recv(new_fd, s, sizeof(Slice), 0);

        if(bytesread < 0){
            fprintf(stderr, "slice %d recv error: %s\n", msg, strerror(new_fd));
        }
        
        printf("slice n: %d, size: %d\n", msg+1, s->datasize);
        printslice(s);
        fflush(stdout);
        getbasename(s->slicename, filename);
        save_data(destination, filename, s->data, s->datasize);
    }

    close(sockfd);
    close(new_fd);    

    if(status == 0){
        printf("%s\n", "connection closed");
        exit(0);
    }
}