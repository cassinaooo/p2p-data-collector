#ifndef __PROTOCOL_TYPES__
#define __PROTOCOL_TYPES__

#include <unistd.h>

typedef struct {
    char client_name[256];
    char filename[256];
    __off_t filesize;
    unsigned int checksum;
} Header;

#endif