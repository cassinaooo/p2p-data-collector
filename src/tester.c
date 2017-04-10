#include <protocoltypes.h>
#include "tester.h"

void testHeaderDecoding(){
    Header *h;

    h = decodeHeader("cliente|nome_do_arquivo|222222|444444");

    printheader(h);
}

void testHeaderEncoding(){
    Header *h = newheader("cliente", "nome_do_arquivo", 222222, 444444);
    char buf[1024];

    encodeHeader(h, buf);

    debug(buf);
}

void testHeaderEncodingDecoding(){
    Header *header1 = newheader("cliente", "nome_do_arquivo", 222222, 444444);
    char buf[1024];

    encodeHeader(header1, buf);

    Header *header2 = decodeHeader(buf);

    if(strcmp(header1->client_name,header2->client_name) == 0){
        debug("client equals\n");
    }

    if(strcmp(header1->filename,header2->filename) == 0){
        debug("filename equals\n");
    }

    if(header1->filesize == header2->filesize){
        debug("filesize equals\n");
    }

    if(header1->checksum == header2->checksum){
        debug("checksum equals\n");
    }
}

void test(){
    testHeaderEncodingDecoding();
}