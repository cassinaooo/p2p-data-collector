#ifndef __PROTOCOL_TYPES__
#define __PROTOCOL_TYPES__

typedef struct {
    char c_name[256];
    char filename[256];
    int numberofslices;
    int slicemaxlen;
} Header;

typedef struct {
    unsigned int checksum;
    int slicenumber;
    int totalslices;
    int datasize;
    char slicename[256];
    char data[256000];
} Slice;

#endif