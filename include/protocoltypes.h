#ifndef __PROTOCOL_TYPES__
#define __PROTOCOL_TYPES__

typedef struct {
    char c_name[256];
    char filename[256];
    int filesize;
    unsigned int checksum;
} Header;

#endif