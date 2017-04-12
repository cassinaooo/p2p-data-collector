#include <protocoltypes.h>
#include "receiver.h"

#define PORT "35000"  // the port users will be connecting to
#define BACKLOG 10     // how many pending connections queue will hold
#define ROOT_DIR "/home/cassiano/redes/files/received"


/**
 * aguarda conexoes na porta PORT, ate um connect ser realizado do outro lado
 * apos isso recupera todos os dados enviados do sender e os salva na pasta ROOT_DIR, com
 * o host que as enviou propriamente identificado, mais info em protocolutils.h e fileutils.h
 */
void recvfile(){
    int status, sockfd, new_fd;
    char destination_folder[256], destination_file[256], buffer[BUFSIZ], encoded_header[1024];
    ssize_t bytes_read;
    __off_t remain_data;

    Header *header;

    debug("AWAITING CONNECTIONS ON PORT %s\n", PORT);

    sockfd = newlistensocket(PORT);
    status = listen(sockfd, BACKLOG);

    if(status < 0){
        error("listen error: %s\n", strerror(sockfd));
    }

    // socket to a new connection, blocks until a connection to PORT is made
    new_fd  = newrecvsocket(sockfd);

    bytes_read = recv(new_fd, encoded_header, sizeof(encoded_header), 0);

    if(bytes_read < 0){
        error("encoded header recv error: %s\n", strerror(new_fd));
    }

    header = decodeHeader(encoded_header);

    debug ("HEADER RECEBIDO\n");
    printheader(header);

    makefolder(header->client_name, ROOT_DIR, destination_folder);

    debug("folder to save: %s\n", destination_folder);

    getfinalfilename(destination_folder, header->filename, destination_file);
    
    FILE *received_fd = fopen(destination_file, "w");

    if (received_fd == NULL){
        error("Failed to open file --> %s\n", strerror(errno));
    }

    remain_data = header->filesize;

    int i = 0;
    while (((bytes_read = recv(new_fd, buffer, BUFSIZ, 0)) > 0) && (remain_data > 0)){

        fwrite(buffer, sizeof(char), bytes_read, received_fd);
        remain_data -= bytes_read;

        if(++i % 100 == 0){
            debug("remaining data: %d bytes\n", remain_data);
        }
    }

    // if we dont close the file, the last fwrite isnt done
    fclose(received_fd);

    if(cksum(destination_file) == header->checksum){
        debug("Checksums match, ending connection.\n");
    }else{
        error("checksums didnt match!\n");
        error("cksum: %u, size: %ld\n", cksum(destination_file), cksum(destination_file));
        error("header cksum: %u, size: %ld\n", header->checksum, sizeof(header->checksum));
    }
    
    close(sockfd);
    close(new_fd);
}