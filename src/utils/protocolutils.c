#include "protocolutils.h"

Header *newheader(
        char * clientname, char * servername, 
        char * filename, int numberofslices, int slicemaxlen  
    ){
    
    Header *new = malloc(sizeof(Header));

    strcpy(new->clientname, clientname);
    strcpy(new->servername, servername);
    strcpy(new->filename, filename);

    new->numberofslices = numberofslices;
    new->slicemaxlen = slicemaxlen;
    
    return new;
} 

void printheader(const Header * h){
    printf("%s\n", "------ HEADER BEGIN -------");
    printf("clientname: %s\n", h->clientname);
    printf("servername: %s\n", h->servername);
    printf("filename: %s\n", h->filename);
    printf("numberofslices: %d\n", h->numberofslices);
    printf("slicemaxlen: %d\n", h->slicemaxlen);
    printf("%s\n\n", "------ HEADER END -------");     
}

Slice *newslice(int datasize, int sliceno, const char * slicename , const char * data){
    
    Slice *new = malloc(sizeof(Slice));

    new->slicesize = datasize;

    new->data = malloc( datasize * sizeof(char) );

    strcpy(new->slicename, slicename);

    strcpy(new->data, data);     
    
    return new;
} 

void printslice(const Slice * s){
    
    printf("%s\n", "------ SLICE BEGIN -------");
    printf("slicesize %d: ", s->slicesize);
    printf("data: %s\n", s->data);
    printf("%s\n\n", "------ SLICE END -------");     
}