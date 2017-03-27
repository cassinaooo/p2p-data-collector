#include "tester.h"

Header *testheadercreation(){
    Header *h = newheader("192.168.1.1", "192.168.1.2", "file.txt", 10, 1024);
    printheader(h);
    return h;
}

void testslicecreation(Header *h){
    int slsize = h->numberofslices;
    int slmaxlen = h->slicemaxlen;

    Slice * slices[slsize];
    
    for(int i = 0; i < slsize; i++){
        slices[i] = newslice(slmaxlen, i, "slice.file","THIS IS SOME DATA!");
    }

    for(int i = 0; i < slsize; i++){
        printslice(slices[i]);
    }
}

void protocolutilstest(){
    Header *h = testheadercreation();
    testslicecreation(h);
}

/*
 * Demonstrates a call to 'slurp'.
 */
void filereadertest(){
    long  file_size;
    char *buf;

    /* Try the first command-line argument as a file name */
    file_size = slurp("/home/labvcr2/cassiano/networks/input.txt", &buf, false);

    /* Bail if we get a negative file size back from slurp() */
    if( file_size < 0L ) {
        perror("File read failed");
    }

    for(int i = 0; i < file_size; i++){
        printf("%c", buf[i]);
    }

    /* Remember to free() memory allocated by slurp() */
    free( buf );
}

void splitfile(){
    char parts_regex[256];

    compressandsplit("/home/labvcr2/cassiano/networks/files/to_send", parts_regex);

    char **files = malloc(1024 * sizeof(char *));

    for(int i = 0; i < 1024; i++){
        files[i] = malloc(256 * sizeof(char));
    }

    listfilesbyregex(parts_regex, files);

    for(int i = 0; files[i] != '\0'; i++){
        printf("%s\n", files[i]);
    }
}



void test(){
    splitfile();
}