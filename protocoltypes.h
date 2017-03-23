
typedef struct {
    char clientname[255];
    char servername[255];
    char filename[255];
    int numberofslices;
    int slicemaxlen;
} Header;

typedef struct {
    int slice_no;
    char *data;
} Slice;
