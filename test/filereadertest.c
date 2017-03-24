#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "fileutils.h"

/*
 * Demonstrates a call to 'slurp'.
 */
void filereadertestmain(){
    long  file_size;
    char *buf;

    /* Try the first command-line argument as a file name */
    file_size = slurp("teste1Postgres.png", &buf, false);

    /* Bail if we get a negative file size back from slurp() */
    if( file_size < 0L ) {
        perror("File read failed");
    }

    for(int i = 0; i < file_size; i++){
        printf("%c", buf[i]);
    }

    /* Remember to free() memory allocated by slurp() */
    free( buf );
}

