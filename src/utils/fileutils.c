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

unsigned long slurp(char const* path, unsigned char **buf, int add_nul){
    FILE  *fp;
    size_t fsz;
    long   off_end;
    int    rc;

    /* Open the file */
    fp = fopen(path, "rb");
    if( NULL == fp ) {
        return 0;
    }

    /* Seek to the end of the file */
    rc = fseek(fp, 0L, SEEK_END);
    if( 0 != rc ) {
        return 0;
    }

    /* Byte offset to the end of the file (size) */
    if( 0 > (off_end = ftell(fp)) ) {
        return 0;
    }
    fsz = (size_t)off_end;

    /* Allocate a buffer to hold the whole file */
    *buf = malloc( fsz+(int)add_nul );
    if( NULL == *buf ) {
        return 0;
    }

    /* Rewind file pointer to start of file */
    rewind(fp);

    /* Slurp file into buffer */
    if( fsz != fread(*buf, 1, fsz, fp) ) {
        free(*buf);
        return 0;
    }

    /* Close the file */
    if( EOF == fclose(fp) ) {
        free(*buf);
        return 0;
    }

    if( add_nul ) {
        /* Make sure the buffer is NUL-terminated, just in case */
        buf[fsz] = '\0';
    }

    /* Return the file size */
    return (long)fsz;
}

/**
 * cria uma pasta para salvar os arquivos, e retorna o nome dela
 * !! essa funcao mudara para retornar <basepath>/<hostname> em breve !!
 *
 * @param hostname: o nome do host, exemplo: raspberrypi3
 * @param basepath o caminho para o diretório raiz, exemplo: /home/drone/files/received
 * @param resultingfolder: <basepath>/<hostname>/<timestamp>, exemplo: /home/drone/files/received/raspberrypi3/92127812812/
 */

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

    debug("%s\n", mkdir_command);

    strcpy(resultingfolder, destination_folder);

    system(mkdir_command);
}

/**
 * desmonta um caminho e retorna a ultima parte antes da ultima barra
 *
 * @param absolute_path: caminho absoluto para o arquivo, exemplo: /home/drone/arquivo.txt
 * @param basename_buf nome do arquivo, exemplo: arquivo.txt
 */

void getbasename(const char * absolute_path, char * basename_buf){
    char *extracted_base = basename(strdup( absolute_path ));

    strcpy(basename_buf, extracted_base);
}

/**
 * concatena basepath e filename
 *
 * @param basepath exemplo: /home/drone/files/received
 * @param filename exemplo: arquivo.txt
 * @param resulting_filename exemplo: /home/drone/files/received/arquivo.txt
 */

void getfinalfilename(const char * basepath, const char * filename, char * resulting_filename){
    char destination[256];

    strcpy(destination, basepath);
    strcat(destination, "/");
    strcat(destination, filename);    

    debug("Will save to: %s\n", destination);

    strcpy(resulting_filename, destination);
}

/**
 * roda um comando no sistema na forma, para comprimir uma pasta
 * tar cvf <compressed_filename>_<unix_timestamp>.tar.gz <foldername>
 *
 * @param foldername a pasta que deve ser comprimida
 * @param compressed_filename: o caminho absoluto para o arquivo recem criado
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

    strcpy(tar_command, "tar --absolute-names -cvf  ");

    strcat(tar_command, destination);

    strcat(tar_command, " ");
    
    strcat(tar_command, foldername);

    debug("%s\n", tar_command);
    
    system(tar_command);

    strcpy(compressed_filename, destination);
}

void notifysucces(char *folder){
    char touch_command[512];

    strcpy(touch_command, "touch ");
    strcat(touch_command, folder);
    strcat(touch_command, "/SUCCESS");

    debug("%s\n", touch_command);

    system(touch_command);
}

/**
 * pega o file: descriptor de um arquivo
 * @param path: caminho para o arquivo
 * @param fd: o descriptor
 * @return o tamanho do arquivo
 */

__off_t getfd(const char *path, int *fd){
    struct stat file_stat;

    *fd = open(path, O_RDONLY);

    if (*fd == NULL){
        error("Error opening file --> %s", strerror(errno));
        exit(EXIT_FAILURE);
    }

    /* Get file stats */
    if (fstat(*fd, &file_stat) < 0){
        error("Error fstat --> %s", strerror(errno));
        exit(EXIT_FAILURE);
    }

    return file_stat.st_size;
}
