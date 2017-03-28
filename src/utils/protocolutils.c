#include "protocolutils.h"

Header *newheader(const char * clientname, const char * filename, const int numberofslices,const int slicemaxlen){
    
    Header *new = malloc(sizeof(Header));

    strcpy(new->c_name, clientname);
    strcpy(new->filename, filename);

    new->numberofslices = numberofslices;
    new->slicemaxlen = slicemaxlen;
    
    return new;
} 

void printheader(const Header * h){
    printf("%s\n", "------ HEADER BEGIN -------");
    printf("clientname: %s\n", h->c_name);
    printf("filename: %s\n", h->filename);
    printf("numberofslices: %d\n", h->numberofslices);
    printf("slicemaxlen: %d\n", h->slicemaxlen);
    printf("%s\n\n", "------ HEADER END -------");     
}

void newslice(Slice *new, const int slicenumber, const int totalslices, const char * slicename , const char * data){
    
    new->slicenumber = slicenumber;
    
    new->totalslices = totalslices;

    strcpy(new->slicename, slicename);

    strcpy(new->data, data);
} 

void printslice(const Slice * s){
    
    printf("%s\n", "------ SLICE BEGIN -------");
    
    printf("slice: %d/%d\n", s->slicenumber, s->totalslices); 
    printf("slicename: %s\n", s->slicename);
    
    printf("%s\n\n", "------ SLICE END -------");     
}