#include "sender.h"

#define PORT "35000" // the port to connect to
#define HOST "localhost" 
// no trailing slashes here, pls
#define BACKUP_FOLDER "/home/cassiano/redes/files/to_send"
#define SLICE_LEN 256000

void sendfile(){
    int status;

    printf("CONNECTING TO HOST: %s ON PORT %s\n", HOST, PORT);

    int sockfd = newsendsocket(PORT, HOST);

    int len, bytes_sent;
    char parts_folder[256];
    char hostname[50];

    char **files = malloc(1024 * sizeof(char *));

    for(int i = 0; i < 1024; i++){
        files[i] = malloc(256 * sizeof(char));
    }

    compressandsplit(BACKUP_FOLDER, parts_folder, SLICE_LEN);
    listfilesbyfolder(parts_folder, files);
    
    gethostname(hostname, sizeof(hostname));

    int files_count;
    for(files_count = 0; files[files_count] != '\0'; files_count++);

    Header *h = newheader(hostname, BACKUP_FOLDER, files_count, SLICE_LEN);

    Slice *s = malloc(sizeof(Slice));

    char *buf;
    int file_size;
    
    printf("ENVIANDO HEADER:\n");
    printheader(h);

    printf("size of slice: %lu\n", sizeof(Slice));
    fflush(stdout);

    len = sizeof(Header);

    bytes_sent = send(sockfd, h, len, 0);

    free(h);    

    for(int msg = 0; msg < files_count; msg++){
        file_size = slurp(files[msg], &buf, false);

        if( file_size < 0L ) {
            perror("File read failed");
            exit(1);
        }

        newslice(s, msg, files_count, files[msg], buf, file_size);

        s->checksum = 0;
        
        printslice(s);

        bytes_sent = send(sockfd, s, sizeof(Slice), 0);

        if(bytes_sent < 0){
            fprintf(stderr, "send error on slice %d: %s\n", msg, strerror(sockfd));
            exit(1);
        }

        printf("enviei um slice de tamanho: %d\n",bytes_sent);
        fflush(stdout);
        usleep(500000); // meio segundo
    }        

    close(sockfd);
}
