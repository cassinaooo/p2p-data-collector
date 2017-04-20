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
#include "protocolutils.h"

unsigned long slurp(char const* path, unsigned char **buf, int add_nul);
void compress(char const* foldername, char * compressed_filename);
void makefolder(const char *hostname, const char *basepath, char *resultingfolder);
void getbasename(const char * absolute_path, char * basename_buf);
void getfinalfilename(const char * basepath, const char * filename, char * resulting_filename);
__off_t getfd(const char *path, int *fd);
#endif