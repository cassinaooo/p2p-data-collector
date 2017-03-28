#include "fileutils.h"
#include <time.h> 

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



void getparentdir(const char * compressed_file, char * parentdir){

    //char *dummy  = strdup( compressed_file );
    
    char *dname = dirname(strdup( compressed_file ));

    strcpy(parentdir, dname);
}

void makefolder(const char *hostname, const char *basepath, char *resultingfolder){
    char mkdir_command[512];
    char destination_folder[256];

    strcpy(mkdir_command, "mkdir -p ");

    strcpy(destination_folder, basepath);    
    strcat(destination_folder, "/");
    strcat(destination_folder, hostname);
    strcat(destination_folder, "/");

    char timestamp[15];

    sprintf(timestamp, "%lu", (unsigned long) time(NULL));
    strcat(destination_folder, timestamp);  

    strcat(mkdir_command, destination_folder);  

    printf("%s\n", mkdir_command);

    strcpy(resultingfolder, destination_folder);

    //system(mkdir_command);
}

void getfilenamenoextension(const char * compressed_file, char * basename_buf){
    
    char *extracted_base = basename(strdup( compressed_file ));
    
    int i;

    for(i = 0; extracted_base[i] != '\0' && extracted_base[i] != '.'; i++);

    extracted_base[i] = '\0';

    strcpy(basename_buf, extracted_base);
}


/*
    runs a shell command in the form 
    split -b <slice_bytes> <filename> <filename_parent_dir>/<filename>_parts/segment.
*/

void split(char const* filename, char const* slice_bytes, char * parts_folder){
    char split_command[1024];
    char mkdir_command[1024];
    
    char destination_files[256];
    char parent_dir[256];
    char basename[256];
    
    getfilenamenoextension(filename, basename);
    getparentdir(filename, parent_dir);

    sprintf(destination_files, "%s/%s_parts/", parent_dir, basename);

    // creates parts_directory

    strcpy(mkdir_command, "mkdir -p ");
    
    strcat(mkdir_command, destination_files);

    printf("%s\n", mkdir_command);

    system(mkdir_command);

    // runs split command

    strcpy(split_command, "split -b ");

    strcat(split_command, slice_bytes);

    strcat(split_command, " ");   

    strcat(split_command, filename);

    strcat(split_command, " ");

    strcat(split_command, destination_files);

    strcat(split_command, "segment.");
    
    printf("%s\n", split_command);
   
    system(split_command);

    strcpy(parts_folder, destination_files);
}


void compressandsplit(char const * folder_path, char * parts_folder, int sizeofslices){
    char compressed_file[256];
    char sizeofslices_str[30];

    sprintf(sizeofslices_str, "%d", sizeofslices);

    compress(folder_path, compressed_file);
    split(compressed_file, sizeofslices_str, parts_folder);
}

/*
    runs a shell command in the form 
    tar cvf <compressed_filename>_<unix_timestamp>.tar.gz <foldername>
*/

void compress(char const* foldername, char * compressed_filename){
    char destination[256];
    char tar_command[1024];

    char timestamp[15];

    sprintf(timestamp, "%lu", (unsigned long) time(NULL));
    
    strcpy(destination, foldername);

    strcat(destination,"_");
    
    strcat(destination,timestamp);

    strcat(destination, ".tar.gz");

    strcpy(tar_command, "tar -cvf ");

    strcat(tar_command, destination);

    strcat(tar_command, " ");
    
    strcat(tar_command, foldername);

    printf("%s\n", tar_command);
    
    system(tar_command);

    strcpy(compressed_filename, destination);
}

void listfilesbyfolder(char const *parts_folder, char **files){

    FILE *fp;
    char path[1035];

    /* Open the command for reading. */

    char ls_command[512];

    strcpy(ls_command, "/bin/ls ");

    strcat(ls_command, parts_folder);

    strcat(ls_command, "*");

    printf("%s\n", ls_command);    

    fp = popen(ls_command, "r");

    if (fp == NULL) {
        printf("Failed to run command\n" );
        exit(1);
    }

    int line_idx = 0;
    /* Read the output a line at a time - output it. */
    while (fgets(path, sizeof(path)-1, fp) != NULL) {
        path[strlen(path) - 1] = '\0';
        strcpy(files[line_idx++], path);
    }

    files[line_idx] = '\0';

    pclose(fp);
}

unsigned int checksum(void *buffer, size_t len, unsigned int seed){
    unsigned char *buf = (unsigned char *)buffer;
    size_t i;

    for (i = 0; i < len; ++i)
        seed += (unsigned int)(*buf++);
    return seed;
}