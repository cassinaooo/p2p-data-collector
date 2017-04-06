#include "protocolutils.h"

Header *newheader(const char * clientname, const char * filename, const int filesize, const unsigned int checksum){
    
    Header *new = malloc(sizeof(Header));

    strcpy(new->c_name, clientname);
    strcpy(new->filename, filename);

    new->filesize = filesize;
    new->checksum = checksum;
    
    return new;
} 

void printheader(const Header * h){
    printf("%s\n", "------ HEADER BEGIN -------");
    printf("clientname: %s\n", h->c_name);
    printf("filename: %s\n", h->filename);
    printf("filesize: %d\n", h->filesize);
    printf("checksum: %ud\n", h->checksum);    
    printf("%s\n\n", "------ HEADER END -------");     
}