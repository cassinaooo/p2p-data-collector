#include "protocolutils.h"

Header *newheader(const char * clientname, const char * filename, __off_t filesize, const long int checksum){
    
    Header *new = malloc(sizeof(Header));

    strcpy(new->client_name, clientname);
    strcpy(new->filename, filename);

    new->filesize = filesize;
    new->checksum = checksum;
    
    return new;
} 

void printheader(const Header * h){
    debug("%s\n", "------ HEADER BEGIN -------");
    debug("clientname: %s\n", h->client_name);
    debug("filename: %s\n", h->filename);
    debug("filesize: %ld\n", h->filesize);
    debug("checksum: %ud\n", h->checksum);
    debug("%s\n\n", "------ HEADER END -------");
}


unsigned int crc32b(unsigned char *message, size_t size) {
    int i, j;
    unsigned int byte, crc;
    int mask;

    i = 0;
    crc = 0xFFFFFFFF;

    while (i < size) {
        byte = message[i];            // Get next byte.
        crc = crc ^ byte;
        for (j = 7; j >= 0; j--) {    // Do eight times.
            mask = -(crc & 1);
            crc = (crc >> 1) ^ (0xEDB88320 & mask);
        }
        i = i + 1;
    }

    return ~crc;
}

unsigned int cksum(const char *filename){
    unsigned char *filebytes = NULL;

    unsigned long size = slurp(filename, &filebytes, 0);
    unsigned int cksum = crc32b(filebytes, size);

    debug("cksum for file %s with %ld bytes long was: %d\n", filename, size, cksum);

    return cksum;
}


void debug(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    fputs("D: ", stdout);
    vprintf(fmt, args);
    va_end(args);
    fflush(stdout);
}

void error(char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    fputs("E: ", stderr);
    vfprintf(stderr, fmt, args);
    va_end(args);
    fflush(stderr);
}

