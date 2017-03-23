
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

Slice *newslice(Header * header, int slice_no, const char * data){
    
    Slice *new = malloc(sizeof(Slice));

    new->data = malloc( header->slicemaxlen * sizeof(char) );

    strcpy(new->data, data);     

    new->slice_no = slice_no;
    
    return new;
} 

void printslice(const Slice * s){
    
    printf("%s\n", "------ SLICE BEGIN -------");
    printf("slice no: %d\n", s->slice_no);
    printf("data: %s\n", s->data);
    printf("%s\n\n", "------ SLICE END -------");     
}