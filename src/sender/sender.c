#include "sender.h"

#define PORT "35000" // the port to connect to
#define HOST "192.168.1.2" 
// no trailing slashes here, pls
#define BACKUP_FOLDER "/home/providence/cassiano_proj_redes/files/to_send"

void sendfiles(){
    int sockfd, file_descriptor;
    long file_size;
    char file_to_send[256], hostname[50], file_basename[256];

    __off_t remain_data, offset;
    ssize_t sent_bytes;
    Header *h;

    debug("CONNECTING TO HOST: %s ON PORT %s\n", HOST, PORT);

    sockfd = newsendsocket(PORT, HOST);
    compress(BACKUP_FOLDER, file_to_send);
    gethostname(hostname, sizeof(hostname));
    debug("reading file: %s\n", file_to_send);

    file_size = getfd(file_to_send, &file_descriptor);

    if( file_size < 0L ) {
        error("File read failed\n");
        exit(1);
    }        

    debug("file was %ld bytes long\n", file_size);

    getbasename(file_to_send, file_basename);

    // read file to calculate checksum

    h = newheader(hostname, file_basename, file_size, cksum(file_to_send));

    char encoded_header[1024];
    encodeHeader(h, encoded_header);

    debug("ENVIANDO HEADER:\n");

    printheader(h);

    sent_bytes = send(sockfd, encoded_header, sizeof(encoded_header), 0);

    free(h);

    if(sent_bytes < 0){
        error("send error on header: %s\n", strerror(sockfd));
        exit(1);
    } 

    offset = 0;

    remain_data = file_size;

    int i = 0;
    while (((sent_bytes = sendfile(sockfd, file_descriptor, &offset, BUFSIZ)) > 0)
           && (remain_data > 0)){

        remain_data -= sent_bytes;
        
        if(++i % 100 == 0) {
            debug("remaining data: %d bytes\n", remain_data);
        }
    }

    close(file_descriptor);
    close(sockfd);
}
