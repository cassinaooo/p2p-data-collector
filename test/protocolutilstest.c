#include "protocolutils.h"

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

void protocolutilstestmain(){
    Header *h = testheadercreation();
    testslicecreation(h);
}


