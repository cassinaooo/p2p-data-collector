#ifndef __PROTOCOL_TYPES__
#define __PROTOCOL_TYPES__

typedef struct {
    char c_name[255];
    char filename[255];
    int numberofslices;
    int slicemaxlen;
} Header;

typedef struct {
    unsigned int checksum;
    int slicenumber;
    int totalslices;
    char slicename[256];
    char data[256000];
} Slice;

#endif