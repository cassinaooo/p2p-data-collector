#ifndef __PROTOCOL_TYPES__
#define __PROTOCOL_TYPES__

typedef struct {
    char clientname[255];
    char servername[255];
    char filename[255];
    int numberofslices;
    int slicemaxlen;
} Header;

typedef struct {
    int slicesize;
    char slicename[255];
    char *data;
} Slice;

#endif