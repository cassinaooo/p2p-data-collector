#ifndef __FILE_UTILS__
#define __FILE_UTILS__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <libgen.h>
#include <sys/sendfile.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>

long slurp(char const* path, char **buf, int add_nul);
void split(char const* filename, char const* slice_bytes, char * splitted_file_regex);
void compress(char const* foldername, char * compressed_filename);
void compressandsplit(char const * folder_path, char * parts_folder, int sizeofslices);
void listfilesbyfolder(char const * regex, char **files);
unsigned int checksum(void *buffer, size_t len, unsigned int seed);
void makefolder(const char *hostname, const char *basepath, char *resultingfolder);
void getbasename(const char * absolute_path, char * basename_buf);
void getfinalfilename(const char * basepath, const char * filename, char * resulting_filename);
int getfd();

#endif