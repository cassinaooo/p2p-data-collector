#include <protocoltypes.h>
#include "protocolutils.h"

Header *newheader(const char * clientname, const char * filename, __off_t filesize, const unsigned int checksum){

    debug("attempting to create new header %s %s %ld %ld\n", clientname, filename, filesize, checksum);
    
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
    debug("checksum: %u\n", h->checksum);
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

    debug("cksum for file %s with %ld bytes long was: %u\n", filename, size, cksum);

    return cksum;
}


Header *decodeHeader(const char *str){
    char client_name[265], file_name[255], file_size_str[64], checksum_str[64];
    __off_t file_size;
    long int checksum;

    int i = 0, break_point;

    while(str[i] != '|'){
        client_name[i] = str[i];
        i++;
    }

    client_name[i] = '\0';

    i++;

    break_point = i;

    while(str[i] != '|'){
        file_name[i - break_point] = str[i];
        i++;
    }

    file_name[i - break_point] = '\0';

    i++;

    break_point = i;

    while(str[i] != '|'){
        file_size_str[i - break_point] = str[i];
        i++;
    }

    file_size_str[i - break_point] = '\0';

    i++;

    break_point = i;

    while(str[i] != '\0'){
        checksum_str[i - break_point] = str[i];
        i++;
    }

    checksum_str[i - break_point] = '\0';


    file_size = atol(file_size_str);
    checksum = atol(checksum_str);

    return newheader(client_name, file_name, file_size, checksum);
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

void encodeHeader(Header *h, char *buf) {
    sprintf(buf, "%s|%s|%ld|%u", h->client_name, h->filename, h->filesize, h->checksum);
}

