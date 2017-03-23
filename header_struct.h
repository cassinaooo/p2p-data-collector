struct header {
    char client_name[255];
    char server_name[255];
    char filename[255];
    int filelen;
    int fileslicessize;
};

struct slice {
    int slice_no;
    int slice_size;
    char *data;
};