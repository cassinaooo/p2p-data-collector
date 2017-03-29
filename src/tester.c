#include "tester.h"

/*
 * Demonstrates a call to 'slurp'.
 */
void filereadertest(){
    long  file_size;
    char *buf;

    /* Try the first command-line argument as a file name */
    file_size = slurp("/home/labvcr2/cassiano/networks/input.txt", &buf, false);

    /* Bail if we get a negative file size back from slurp() */
    if( file_size < 0L ) {
        perror("File read failed");
    }

    /* Remember to free() memory allocated by slurp() */
    free( buf );
}

void testslicecreation(){
    Slice *s = malloc(sizeof(Slice));
    
    newslice(s, 0, 10, "slicename", "1234", 4);

    printslice(s);
}

void splitfile(){
    char parts_folder[256];

    compressandsplit("/home/labvcr2/cassiano/networks/files/to_send", parts_folder, 256000);

    char **files = malloc(1024 * sizeof(char *));

    for(int i = 0; i < 1024; i++){
        files[i] = malloc(256 * sizeof(char));
    }

    listfilesbyfolder(parts_folder, files);

    for(int i = 0; files[i] != '\0'; i++){
        printf("%s\n", files[i]);
    }
}

void test(){
    testslicecreation();
}