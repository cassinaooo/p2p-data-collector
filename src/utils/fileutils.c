#include "fileutils.h"

/*
 * 'slurp' reads the file identified by 'path' into a character buffer
 * pointed at by 'buf', optionally adding a terminating NUL if
 * 'add_nul' is true. On success, the size of the file is returned; on
 * failure, -1 is returned and ERRNO is set by the underlying system
 * or library call that failed.
 *
 * WARNING: 'slurp' malloc()s memory to '*buf' which must be freed by
 * the caller.
 */

long slurp(char const* path, char **buf, int add_nul)
{
    FILE  *fp;
    size_t fsz;
    long   off_end;
    int    rc;

    /* Open the file */
    fp = fopen(path, "rb");
    if( NULL == fp ) {
        return -1L;
    }

    /* Seek to the end of the file */
    rc = fseek(fp, 0L, SEEK_END);
    if( 0 != rc ) {
        return -1L;
    }

    /* Byte offset to the end of the file (size) */
    if( 0 > (off_end = ftell(fp)) ) {
        return -1L;
    }
    fsz = (size_t)off_end;

    /* Allocate a buffer to hold the whole file */
    *buf = malloc( fsz+(int)add_nul );
    if( NULL == *buf ) {
        return -1L;
    }

    /* Rewind file pointer to start of file */
    rewind(fp);

    /* Slurp file into buffer */
    if( fsz != fread(*buf, 1, fsz, fp) ) {
        free(*buf);
        return -1L;
    }

    /* Close the file */
    if( EOF == fclose(fp) ) {
        free(*buf);
        return -1L;
    }

    if( add_nul ) {
        /* Make sure the buffer is NUL-terminated, just in case */
        buf[fsz] = '\0';
    }

    /* Return the file size */
    return (long)fsz;
}

/*
    runs a shell command in the form 
    split -b <slice_bytes> <filename> <filename>.part.
*/

void split(char const* filename, char const* slice_bytes){
    char command[1024];
    char converted_long[24];
    char destination_files[256];

    strcpy(destination_files, filename);

    strcat(destination_files, ".part.");

    strcpy(command, "split -b ");

    strcat(command, slice_bytes);

    strcat(command, " ");   

    strcat(command, filename);

    strcat(command, " ");

    strcat(command, destination_files);
   
    system(command);

}



void compressandsplit(char const* foldername, char const* slice_bytes){

}

void compress(char const* foldername){
    char destination[256];

    
}

void strfromlong(long ulong_value, char * str){
    const int n = snprintf(NULL, 0, "%lu", ulong_value);
    assert(n > 0);
    char buf[n+1];
    int c = snprintf(buf, n+1, "%lu", ulong_value);
    assert(buf[n] == '\0');
    assert(c == n);
    
    strcpy(str, buf); 
}