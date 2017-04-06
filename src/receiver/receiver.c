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

    int bytes_read = recv(new_fd, header, sizeof(Header), 0);

    if(bytes_read < 0){
        fprintf(stderr, "header recv error: %s\n", strerror(new_fd));
    }

    printf ("HEADER RECEBIDO\n");

    printheader(header);

    char destination_folder[256], destination_file[256];

    makefolder(header->c_name, ROOT_DIR, destination_folder);

    printf("folder to save: %s\n", destination_folder);
    fflush(stdout);

    getfinalfilename(destination_folder, header->filename, destination_file);
    
    FILE *received_fd = fopen(destination_file, "w");

    if (received_fd == NULL){
        fprintf(stderr, "Failed to open file foo --> %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    int remain_data = header->filesize;
    char buffer[BUFSIZ];

    while (((bytes_read = recv(new_fd, buffer, BUFSIZ, 0)) > 0) && (remain_data > 0)){
            fwrite(buffer, sizeof(char), bytes_read, received_fd);
            remain_data -= bytes_read;
            fprintf(stdout, "Receive %d bytes and we hope :- %d bytes\n", bytes_read, remain_data);
    }
    
    close(sockfd);
    close(new_fd);

    if(status == 0){
        printf("%s\n", "connection closed");
        exit(0);
    }
}