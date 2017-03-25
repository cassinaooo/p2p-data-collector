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
        slices[i] = newslice(h, i, "THIS IS SOME DATA!");
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
    split("/home/labvcr2/cassiano/networks/files/input.txt", "8");
}

void test(){
    splitfile();
}